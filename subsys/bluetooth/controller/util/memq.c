/*
 * Copyright (c) 2016-2017 Nordic Semiconductor ASA
 * Copyright (c) 2016 Vinayak Kariappa Chettimada
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * FIFO-style "memory queue" permitting enqueue at tail and dequeue from head.
 * Element's payload is a pointer to arbitrary memory.
 *
 * Implemented as a singly-linked list, with always one-more element.
 * The linked list must always contain at least one link-element, as emptiness
 * is given by head == tail.
 * For a queue to be valid, it must be initialized with an initial link-element.
 *
 * Invariant: The tail element's mem pointer is DontCare.
 *
 * Note that at enqueue, memory is not coupled with its accompanying
 * link-element, but the link-element before it!
 *
 * Call                    | State after call
 * ------------------------+-------------------------------
 * memq_init(I,H,T)        | H -> I[] <- T
 * memq_enqueue(A,a,T);    | H -> I[a] -> A[] <- T
 * memq_enqueue(B,b,T);    | H -> I[a] -> A[b] -> B[] <- T
 * memq_dequeue(T,H,dest); | H -> A[b] -> B[] <- T  # I and a as return and dest
 *
 *   where H is the pointer to Head link-element (oldest element).
 *   where T is the pointer to Tail link-element (newest element).
 *   where I[]  means the initial link-element, whose mem pointer is DontCare.
 *   where A[b] means the A'th link-element, whose mem pointer is b.
 */

#include <zephyr/types.h>
#include <stddef.h>

#include "memq.h"

/**
 * @brief Initialize a memory queue to be empty and valid.
 *
 * @param link[in]  Initial link-element. Not associated with any mem
 * @param head[out] Head of queue. Will be updated
 * @param tail[out] Tail of queue. Will be updated
 * @return          Initial link-element
 */
memq_link_t *memq_init(memq_link_t *link, memq_link_t **head, memq_link_t **tail)
{
	/* Head and tail pointer to the initial link - forms an empty queue */
	*head = *tail = link;

	return link;
}

/**
 * @brief De-initialize a memory queue to be empty and invalid.
 *
 * @param head[in,out] Head of queue. Will be updated
 * @param tail[in,out] Tail of queue. Will be updated
 * @return             If empty, return initial link-element. Otherwise NULL
 */
memq_link_t *memq_deinit(memq_link_t **head, memq_link_t **tail)
{
	memq_link_t *link;

	/* If head and tail are not equal, then queue is not empty */
	if (*head != *tail) {
		return NULL;
	}

	link = *head;
	*head = *tail = NULL;

	return link;
}

/**
 * @brief Enqueue at the tail of the queue
 * @details Enqueue is destructive so tail will change to new tail
 *
 * @param link[in]     Element to become the new tail. Not associated mem
 * @param mem[in]      Memory buffer. Will be owned by old tail
 * @param tail[in,out] Tail of queue. Will be updated to point to link
 * @return             New tail
 */
memq_link_t *memq_enqueue(memq_link_t *link, void *mem, memq_link_t **tail)
{
	/* Let the old tail element point to the new tail element */
	(*tail)->next = link;

	/* Let the old tail element point the the new memory */
	(*tail)->mem = mem;

	/* Update the tail-pointer to point to the new tail element.
	 * The new tail-element is not expected to point to anything sensible
	 */
	*tail = link;

	return link;
}

/**
 * @brief Non-destructive peek of head of queue.
 *
 * @param head[in] Pointer to head link-element of queue
 * @param tail[in] Pointer to tail link-element of queue
 * @param mem[out] The memory pointed to by head-element
 * @return         head or NULL if queue is empty
 */
memq_link_t *memq_peek(memq_link_t *head, memq_link_t *tail, void **mem)
{
	/* If head and tail are equal, then queue empty */
	if (head == tail) {
		return NULL;
	}

	/* Extract the head link-element's memory */
	if (mem) {
		*mem = head->mem;
	}

	return head; /* queue was not empty */
}

/**
 * @brief Remove and returns the head of queue.
 * @details Dequeue is destructive so head will change to new head
 *
 * @param tail[in]     Pointer to tail link-element of queue
 * @param head[in,out] Pointer to head link-element of queue. Will be updated
 * @param mem[out]     The memory pointed to by head-element
 * @return             head or NULL if queue is empty
 */
memq_link_t *memq_dequeue(memq_link_t *tail, memq_link_t **head, void **mem)
{
	memq_link_t *old_head;

	/* Use memq peek to get the old head and its mem */
	old_head = memq_peek(*head, tail, mem);
	if (old_head == NULL) {
		return NULL; /* queue is empty */
	}

	/* Update the head-pointer to point to the new head element */
	*head = old_head->next;

	return old_head;
}
