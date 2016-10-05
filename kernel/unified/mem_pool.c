/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @brief Memory pools.
 */

#include <kernel.h>
#include <nano_private.h>
#include <misc/debug/object_tracing_common.h>
#include <sched.h>
#include <wait_q.h>
#include <init.h>

#define _QUAD_BLOCK_AVAILABLE 0x0F
#define _QUAD_BLOCK_ALLOCATED 0x0

extern struct k_mem_pool _k_mem_pool_start[];
extern struct k_mem_pool _k_mem_pool_end[];
#if defined _HEAP_MEM_POOL
static struct k_mem_pool *heap_mem_pool = _HEAP_MEM_POOL;
#else
static struct k_mem_pool *heap_mem_pool;
#endif

static void init_one_memory_pool(struct k_mem_pool *pool);

/**
 *
 * @brief Initialize kernel memory pool subsystem
 *
 * Perform any initialization of memory pool that wasn't done at build time.
 *
 * @return N/A
 */
static int init_static_pools(struct device *unused)
{
	ARG_UNUSED(unused);
	struct k_mem_pool *pool;

	/* perform initialization for each memory pool */

	for (pool = _k_mem_pool_start;
	     pool < _k_mem_pool_end;
	     pool++) {
		init_one_memory_pool(pool);
	}
	return 0;
}

/**
 *
 * @brief Initialize the memory pool
 *
 * Initialize the internal memory accounting structures of the memory pool
 *
 * @param pool memory pool descriptor
 *
 * @return N/A
 */
static void init_one_memory_pool(struct k_mem_pool *pool)
{
	/*
	 * mark block set for largest block size
	 * as owning all of the memory pool buffer space
	 */

	int remaining_blocks = pool->nr_of_maxblocks;
	int j = 0;
	char *memptr = pool->bufblock;

	while (remaining_blocks >= 4) {
		pool->block_set[0].quad_block[j].mem_blocks = memptr;
		pool->block_set[0].quad_block[j].mem_status =
			_QUAD_BLOCK_AVAILABLE;
		j++;
		remaining_blocks -= 4;
		memptr +=
			OCTET_TO_SIZEOFUNIT(pool->block_set[0].block_size)
			* 4;
	}

	if (remaining_blocks != 0) {
		pool->block_set[0].quad_block[j].mem_blocks = memptr;
		pool->block_set[0].quad_block[j].mem_status =
			_QUAD_BLOCK_AVAILABLE >> (4 - remaining_blocks);
		/* non-existent blocks are marked as unavailable */
	}

	/*
	 * note: all other block sets own no blocks, since their
	 * first quad-block has a NULL memory pointer
	 */
	sys_dlist_init(&pool->wait_q);
	SYS_TRACING_OBJ_INIT(memory_pool, pool);
}

/**
 *
 * @brief Determines which block set corresponds to the specified data size
 *
 * Finds the block set with the smallest blocks that can hold the specified
 * amount of data.
 *
 * @return block set index
 */
static int compute_block_set_index(struct k_mem_pool *pool, int data_size)
{
	int block_size = pool->min_block_size;
	int offset = pool->nr_of_block_sets - 1;

	while (data_size > block_size) {
		block_size *= 4;
		offset--;
	}

	return offset;
}


/**
 *
 * @brief Return an allocated block to its block set
 *
 * @param ptr pointer to start of block
 * @param pool memory pool descriptor
 * @param index block set identifier
 *
 * @return N/A
 */
static void free_existing_block(char *ptr, struct k_mem_pool *pool, int index)
{
	struct k_mem_pool_quad_block *quad_block =
		pool->block_set[index].quad_block;
	char *block_ptr;
	int i, j;

	/*
	 * search block set's quad-blocks until the block is located,
	 * then mark it as unused
	 *
	 * note: block *must* exist, so no need to do array bounds checking
	 */

	for (i = 0; ; i++) {
		__ASSERT((i < pool->block_set[index].nr_of_entries) &&
			 (quad_block[i].mem_blocks != NULL),
			 "Attempt to free unallocated memory pool block\n");

		block_ptr = quad_block[i].mem_blocks;
		for (j = 0; j < 4; j++) {
			if (ptr == block_ptr) {
				quad_block[i].mem_status |= (1 << j);
				return;
			}
			block_ptr += OCTET_TO_SIZEOFUNIT(
				pool->block_set[index].block_size);
		}
	}
}


/**
 *
 * @brief Defragment the specified memory pool block sets
 *
 * Reassembles any quad-blocks that are entirely unused into larger blocks
 * (to the extent permitted).
 *
 * @param pool memory pool descriptor
 * @param start_block_set_index index of smallest block set to defragment
 * @param last_block_set_index index of largest block set to defragment
 *
 * @return N/A
 */
static void defrag(struct k_mem_pool *pool,
		   int start_block_set_index, int last_block_set_index)
{
	int i, j, k;
	struct k_mem_pool_quad_block *quad_block;

	/* process block sets from smallest to largest permitted sizes */

	for (j = start_block_set_index; j > last_block_set_index; j--) {

		quad_block = pool->block_set[j].quad_block;
		i = 0;

		do {
			/* block set is done if no more quad-blocks exist */

			if (quad_block[i].mem_blocks == NULL) {
				break;
			}

			/* reassemble current quad-block, if possible */

			if (quad_block[i].mem_status == _QUAD_BLOCK_AVAILABLE) {

				/*
				 * mark the corresponding block in next larger
				 * block set as free
				 */

				free_existing_block(
					quad_block[i].mem_blocks, pool, j - 1);

				/*
				 * delete the quad-block from this block set
				 * by replacing it with the last quad-block
				 *
				 * (algorithm works even when the deleted
				 * quad-block is the last quad_block)
				 */

				k = i;
				while ((k < pool->block_set[j].nr_of_entries) &&
				       (quad_block[k + 1].mem_blocks != NULL)) {
					k++;
				}

				quad_block[i].mem_blocks =
					quad_block[k].mem_blocks;
				quad_block[i].mem_status =
					quad_block[k].mem_status;

				quad_block[k].mem_blocks = NULL;

				/* loop & process replacement quad_block[i] */
			} else {
				i++;
			}

			/* block set is done if at end of quad-block array */

		} while (i < pool->block_set[j].nr_of_entries);
	}
}


/**
 *
 * @brief Allocate block from an existing block set
 *
 * @param block_set pointer to block set
 * @param unused_block_index the index of first unused quad-block
 *                     when allocation fails, it is the number of quad
 *                     blocks in the block set
 *
 * @return pointer to allocated block, or NULL if none available
 */
static char *get_existing_block(struct k_mem_pool_block_set *block_set,
				int *unused_block_index)
{
	char *found = NULL;
	int i = 0;
	int status;
	int free_bit;

	do {
		/* give up if no more quad-blocks exist */

		if (block_set->quad_block[i].mem_blocks == NULL) {
			break;
		}

		/* allocate a block from current quad-block, if possible */

		status = block_set->quad_block[i].mem_status;
		if (status != _QUAD_BLOCK_ALLOCATED) {
			/* identify first free block */
			free_bit = find_lsb_set(status) - 1;

			/* compute address of free block */
			found = block_set->quad_block[i].mem_blocks +
				(OCTET_TO_SIZEOFUNIT(free_bit *
					block_set->block_size));

			/* mark block as unavailable (using XOR to invert) */
			block_set->quad_block[i].mem_status ^=
				1 << free_bit;
#ifdef CONFIG_OBJECT_MONITOR
			block_set->count++;
#endif
			break;
		}

		/* move on to next quad-block; give up if at end of array */

	} while (++i < block_set->nr_of_entries);

	*unused_block_index = i;
	return found;
}


/**
 *
 * @brief Allocate a block, recursively fragmenting larger blocks if necessary
 *
 * @param pool memory pool descriptor
 * @param index index of block set currently being examined
 * @param start_index index of block set for which allocation is being done
 *
 * @return pointer to allocated block, or NULL if none available
 */
static char *get_block_recursive(struct k_mem_pool *pool,
				 int index, int start_index)
{
	int i;
	char *found, *larger_block;
	struct k_mem_pool_block_set *fr_table;

	/* give up if we've exhausted the set of maximum size blocks */

	if (index < 0) {
		return NULL;
	}

	/* try allocating a block from the current block set */

	fr_table = pool->block_set;
	i = 0;

	found = get_existing_block(&(fr_table[index]), &i);
	if (found != NULL) {
		return found;
	}

#ifdef CONFIG_MEM_POOL_AD_BEFORE_SEARCH_FOR_BIGGERBLOCK
	/*
	 * do a partial defragmentation of memory pool & try allocating again
	 * - do this on initial invocation only, not recursive ones
	 *   (since there is no benefit in repeating the defrag)
	 * - defrag only the blocks smaller than the desired size,
	 *   and only until the size needed is reached
	 *
	 * note: defragging at this time tries to preserve the memory pool's
	 * larger blocks by fragmenting them only when necessary
	 * (i.e. at the cost of doing more frequent auto-defragmentations)
	 */

	if (index == start_index) {
		defrag(pool, pool->nr_of_block_sets - 1, start_index);
		found = get_existing_block(&(fr_table[index]), &i);
		if (found != NULL) {
			return found;
		}
	}
#endif

	/* try allocating a block from the next largest block set */

	larger_block = get_block_recursive(pool, index - 1, start_index);
	if (larger_block != NULL) {
		/*
		 * add a new quad-block to the current block set,
		 * then mark one of its 4 blocks as used and return it
		 *
		 * note: "i" was earlier set to indicate the first unused
		 * quad-block entry in the current block set
		 */

		fr_table[index].quad_block[i].mem_blocks = larger_block;
		fr_table[index].quad_block[i].mem_status =
			_QUAD_BLOCK_AVAILABLE & (~0x1);
#ifdef CONFIG_OBJECT_MONITOR
		fr_table[index].count++;
#endif
		return larger_block;
	}

#ifdef CONFIG_MEM_POOL_AD_AFTER_SEARCH_FOR_BIGGERBLOCK
	/*
	 * do a partial defragmentation of memory pool & try allocating again
	 * - do this on initial invocation only, not recursive ones
	 *   (since there is no benefit in repeating the defrag)
	 * - defrag only the blocks smaller than the desired size,
	 *   and only until the size needed is reached
	 *
	 * note: defragging at this time tries to limit the cost of doing
	 * auto-defragmentations by doing them only when necessary
	 * (i.e. at the cost of fragmenting the memory pool's larger blocks)
	 */

	if (index == start_index) {
		defrag(pool, pool->nr_of_block_sets - 1, start_index);
		found = get_existing_block(&(fr_table[index]), &i);
		if (found != NULL) {
			return found;
		}
	}
#endif

	return NULL; /* can't find (or create) desired block */
}


/**
 *
 * @brief Examine threads that are waiting for memory pool blocks.
 *
 * This routine attempts to satisfy any incomplete block allocation requests for
 * the specified memory pool. It can be invoked either by the explicit freeing
 * of a used block or as a result of defragmenting the pool (which may create
 * one or more new, larger blocks).
 *
 * @return N/A
 */
static void block_waiters_check(struct k_mem_pool *pool)
{
	char *found_block;
	struct k_thread *waiter;
	struct k_thread *next_waiter;
	int offset;

	unsigned int key = irq_lock();
	waiter = (struct k_thread *)sys_dlist_peek_head(&pool->wait_q);

	/* loop all waiters */
	while (waiter != NULL) {
		uint32_t req_size = (uint32_t)(waiter->swap_data);

		/* locate block set to try allocating from */
		offset = compute_block_set_index(pool, req_size);

		/* allocate block (fragmenting a larger block, if needed) */
		found_block = get_block_recursive(pool, offset, offset);

		next_waiter = (struct k_thread *)sys_dlist_peek_next(
			&pool->wait_q, &waiter->k_q_node);

		/* if success : remove task from list and reschedule */
		if (found_block != NULL) {
			/* return found block */
			_set_thread_return_value_with_data(waiter, 0,
							   found_block);


			/*
			 * Schedule the thread. Threads will be rescheduled
			 * outside the function by k_sched_unlock()
			 */
			_unpend_thread(waiter);
			_abort_thread_timeout(waiter);
			_ready_thread(waiter);
		}
		waiter = next_waiter;
	}
	irq_unlock(key);
}


/**
 *
 * @brief Perform defragment memory pool request
 *
 * @return N/A
 */
void k_mem_pool_defrag(struct k_mem_pool *pool)
{
	k_sched_lock();

	/* do complete defragmentation of memory pool (i.e. all block sets) */
	defrag(pool, pool->nr_of_block_sets - 1, 0);

	/* reschedule anybody waiting for a block */
	block_waiters_check(pool);
	k_sched_unlock();
}


/**
 *
 * @brief Perform allocate memory pool block request
 *
 * @return N/A
 */
int k_mem_pool_alloc(struct k_mem_pool *pool, struct k_mem_block *block,
			  int size, int32_t timeout)
{
	char *found_block;
	int offset;

	k_sched_lock();
	/* locate block set to try allocating from */
	offset = compute_block_set_index(pool, size);

	/* allocate block (fragmenting a larger block, if needed) */
	found_block = get_block_recursive(pool, offset, offset);


	if (found_block != NULL) {
		k_sched_unlock();
		block->pool_id = pool;
		block->addr_in_pool = found_block;
		block->data = found_block;
		block->req_size = size;
		return 0;
	}

	/*
	 * no suitable block is currently available,
	 * so either wait for one to appear or indicate failure
	 */
	if (likely(timeout != TICKS_NONE)) {
		int result;
		unsigned int key = irq_lock();
		_sched_unlock_no_reschedule();

		_current->swap_data = (void *)size;
		_pend_current_thread(&pool->wait_q, timeout);
		result = _Swap(key);
		if (result == 0) {
			block->pool_id = pool;
			block->addr_in_pool = _current->swap_data;
			block->data = _current->swap_data;
			block->req_size = size;
		}
		return result;
	}
	k_sched_unlock();
	return -ENOMEM;
}


#define MALLOC_ALIGN (sizeof(uint32_t))

/**
 * @brief Allocate memory from heap pool
 *
 * This routine  provides traditional malloc semantics; internally it uses
 * the microkernel pool APIs on a dedicated HEAP pool
 *
 * @param size Size of memory requested by the caller.
 *
 * @retval address of the block if successful otherwise returns NULL
 */
void *k_malloc(uint32_t size)
{
	uint32_t new_size;
	uint32_t *aligned_addr;
	struct k_mem_block mem_block;

	__ASSERT(heap_mem_pool != NULL,
		"Try to allocate a block in undefined heap\n");

	/* The address pool returns, may not be aligned. Also
	*  pool_free requires both start address and size. So
	*  we end up needing 2 slots to save the size and
	*  start address in addition to padding space
	*/
	new_size =  size + (sizeof(uint32_t) << 1) + MALLOC_ALIGN - 1;

	if (k_mem_pool_alloc(heap_mem_pool, &mem_block, new_size,
			     TICKS_NONE) != 0) {
		return NULL;
	}

	/* Get the next aligned address following the address returned by pool*/
	aligned_addr = (uint32_t *) ROUND_UP(mem_block.addr_in_pool,
					     MALLOC_ALIGN);

	/* Save the size requested to the pool API, to be used while freeing */
	*aligned_addr = new_size;

	/* Save the original unaligned_addr pointer too */
	aligned_addr++;
	*((void **) aligned_addr) = mem_block.addr_in_pool;

	/* return the subsequent address */
	return ++aligned_addr;
}


/**
 *
 * @brief Perform return memory pool block request
 *
 * @param blockptr address of the memory block to be freed
 *
 * Marks a block belonging to a pool as free; if there are waiters that can use
 * the the block it is passed to a waiting task.
 *
 * @return N/A
 */
void k_mem_pool_free(struct k_mem_block *blockptr)
{
	int offset;
	struct k_mem_pool *pool = blockptr->pool_id;

	k_sched_lock();
	/* determine block set that block belongs to */
	offset = compute_block_set_index(pool, blockptr->req_size);

	/* mark the block as unused */
	free_existing_block(blockptr->addr_in_pool, pool, offset);

	/* reschedule anybody waiting for a block */
	block_waiters_check(pool);
	k_sched_unlock();
}


/**
 * @brief Free memory allocated through task_malloc
 *
 * @param ptr pointer to be freed
 *
 * @return NA
 */
void k_free(void *ptr)
{
	struct k_mem_block mem_block;

	__ASSERT(heap_mem_pool != NULL,
		"Try to free a block in undefined heap\n");

	mem_block.pool_id = heap_mem_pool;

	/* Fetch the pointer returned by the pool API */
	mem_block.addr_in_pool = *((void **) ((uint32_t *)ptr - 1));
	mem_block.data = *((void **) ((uint32_t *)ptr - 1));
	/* Further fetch the size asked from pool */
	mem_block.req_size = *((uint32_t *)ptr - 2);

	k_mem_pool_free(&mem_block);
}

SYS_INIT(init_static_pools, PRIMARY, CONFIG_KERNEL_INIT_PRIORITY_OBJECTS);
