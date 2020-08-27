/*
 * Copyright (c) 2016, Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 *
 * @brief Public kernel APIs.
 */

#ifndef ZEPHYR_INCLUDE_KERNEL_H_
#define ZEPHYR_INCLUDE_KERNEL_H_

#if !defined(_ASMLANGUAGE)
#include <kernel_includes.h>
#include <errno.h>
#include <stdbool.h>
#include <toolchain.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Kernel APIs
 * @defgroup kernel_apis Kernel APIs
 * @{
 * @}
 */

#if defined(CONFIG_COOP_ENABLED) && defined(CONFIG_PREEMPT_ENABLED)
#define _NUM_COOP_PRIO (CONFIG_NUM_COOP_PRIORITIES)
#define _NUM_PREEMPT_PRIO (CONFIG_NUM_PREEMPT_PRIORITIES + 1)
#elif defined(CONFIG_COOP_ENABLED)
#define _NUM_COOP_PRIO (CONFIG_NUM_COOP_PRIORITIES + 1)
#define _NUM_PREEMPT_PRIO (0)
#elif defined(CONFIG_PREEMPT_ENABLED)
#define _NUM_COOP_PRIO (0)
#define _NUM_PREEMPT_PRIO (CONFIG_NUM_PREEMPT_PRIORITIES + 1)
#else
#error "invalid configuration"
#endif

#define K_PRIO_COOP(x) (-(_NUM_COOP_PRIO - (x)))
#define K_PRIO_PREEMPT(x) (x)

#define K_ANY NULL
#define K_END NULL

#if defined(CONFIG_COOP_ENABLED) && defined(CONFIG_PREEMPT_ENABLED)
#define K_HIGHEST_THREAD_PRIO (-CONFIG_NUM_COOP_PRIORITIES)
#elif defined(CONFIG_COOP_ENABLED)
#define K_HIGHEST_THREAD_PRIO (-CONFIG_NUM_COOP_PRIORITIES - 1)
#elif defined(CONFIG_PREEMPT_ENABLED)
#define K_HIGHEST_THREAD_PRIO 0
#else
#error "invalid configuration"
#endif

#ifdef CONFIG_PREEMPT_ENABLED
#define K_LOWEST_THREAD_PRIO CONFIG_NUM_PREEMPT_PRIORITIES
#else
#define K_LOWEST_THREAD_PRIO -1
#endif

#define K_IDLE_PRIO K_LOWEST_THREAD_PRIO

#define K_HIGHEST_APPLICATION_THREAD_PRIO (K_HIGHEST_THREAD_PRIO)
#define K_LOWEST_APPLICATION_THREAD_PRIO (K_LOWEST_THREAD_PRIO - 1)

#ifdef CONFIG_OBJECT_TRACING
#define _OBJECT_TRACING_NEXT_PTR(type) struct type *__next;
#define _OBJECT_TRACING_LINKED_FLAG uint8_t __linked;
#define _OBJECT_TRACING_INIT \
	.__next = NULL,	     \
	.__linked = 0,
#else
#define _OBJECT_TRACING_INIT
#define _OBJECT_TRACING_NEXT_PTR(type)
#define _OBJECT_TRACING_LINKED_FLAG
#endif

#ifdef CONFIG_POLL
#define _POLL_EVENT_OBJ_INIT(obj) \
	.poll_events = SYS_DLIST_STATIC_INIT(&obj.poll_events),
#define _POLL_EVENT sys_dlist_t poll_events
#else
#define _POLL_EVENT_OBJ_INIT(obj)
#define _POLL_EVENT
#endif

struct k_thread;
struct k_mutex;
struct k_sem;
struct k_msgq;
struct k_mbox;
struct k_pipe;
struct k_queue;
struct k_fifo;
struct k_lifo;
struct k_stack;
struct k_mem_slab;
struct k_mem_pool;
struct k_timer;
struct k_poll_event;
struct k_poll_signal;
struct k_mem_domain;
struct k_mem_partition;
struct k_futex;

/**
 * @typedef k_thread_entry_t
 * @brief Thread entry point function type.
 *
 * A thread's entry point function is invoked when the thread starts executing.
 * Up to 3 argument values can be passed to the function.
 *
 * The thread terminates execution permanently if the entry point function
 * returns. The thread is responsible for releasing any shared resources
 * it may own (such as mutexes and dynamically allocated memory), prior to
 * returning.
 *
 * @param p1 First argument.
 * @param p2 Second argument.
 * @param p3 Third argument.
 *
 * @return N/A
 */

#ifdef CONFIG_THREAD_MONITOR
struct __thread_entry {
	k_thread_entry_t pEntry;
	void *parameter1;
	void *parameter2;
	void *parameter3;
};
#endif

/* can be used for creating 'dummy' threads, e.g. for pending on objects */
struct _thread_base {

	/* this thread's entry in a ready/wait queue */
	union {
		sys_dnode_t qnode_dlist;
		struct rbnode qnode_rb;
	};

	/* wait queue on which the thread is pended (needed only for
	 * trees, not dumb lists)
	 */
	_wait_q_t *pended_on;

	/* user facing 'thread options'; values defined in include/kernel.h */
	uint8_t user_options;

	/* thread state */
	uint8_t thread_state;

	/*
	 * scheduler lock count and thread priority
	 *
	 * These two fields control the preemptibility of a thread.
	 *
	 * When the scheduler is locked, sched_locked is decremented, which
	 * means that the scheduler is locked for values from 0xff to 0x01. A
	 * thread is coop if its prio is negative, thus 0x80 to 0xff when
	 * looked at the value as unsigned.
	 *
	 * By putting them end-to-end, this means that a thread is
	 * non-preemptible if the bundled value is greater than or equal to
	 * 0x0080.
	 */
	union {
		struct {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			uint8_t sched_locked;
			int8_t prio;
#else /* LITTLE and PDP */
			int8_t prio;
			uint8_t sched_locked;
#endif
		};
		uint16_t preempt;
	};

#ifdef CONFIG_SCHED_DEADLINE
	int prio_deadline;
#endif

	uint32_t order_key;

#ifdef CONFIG_SMP
	/* True for the per-CPU idle threads */
	uint8_t is_idle;

	/* CPU index on which thread was last run */
	uint8_t cpu;

	/* Recursive count of irq_lock() calls */
	uint8_t global_lock_count;

#endif

#ifdef CONFIG_SCHED_CPU_MASK
	/* "May run on" bits for each CPU */
	uint8_t cpu_mask;
#endif

	/* data returned by APIs */
	void *swap_data;

#ifdef CONFIG_SYS_CLOCK_EXISTS
	/* this thread's entry in a timeout queue */
	struct _timeout timeout;
#endif

	_wait_q_t join_waiters;
#if __ASSERT_ON
	/* For detecting calls to k_thread_create() on threads that are
	 * already active
	 */
	atomic_t cookie;
#endif
};

typedef struct _thread_base _thread_base_t;

#if defined(CONFIG_THREAD_STACK_INFO)
/* Contains the stack information of a thread */
struct _thread_stack_info {
	/* Stack start - Represents the start address of the thread-writable
	 * stack area.
	 */
	uintptr_t start;

	/* Thread writable stack buffer size. Represents the size of the actual
	 * buffer, starting from the 'start' member, that should be writable by
	 * the thread. This comprises of the thread stack area, any area reserved
	 * for local thread data storage, as well as any area left-out due to
	 * random adjustments applied to the initial thread stack pointer during
	 * thread initialization.
	 */
	size_t size;

	/* Adjustment value to the size member, removing any storage
	 * used for TLS or random stack base offsets. (start + size - delta)
	 * is the initial stack pointer for a thread. May be 0.
	 */
	size_t delta;
};

typedef struct _thread_stack_info _thread_stack_info_t;
#endif /* CONFIG_THREAD_STACK_INFO */

#if defined(CONFIG_USERSPACE)
struct _mem_domain_info {
	/** memory domain queue node */
	sys_dnode_t mem_domain_q_node;
	/** memory domain of the thread */
	struct k_mem_domain *mem_domain;
};

#endif /* CONFIG_USERSPACE */

#ifdef CONFIG_THREAD_USERSPACE_LOCAL_DATA
struct _thread_userspace_local_data {
#if defined(CONFIG_ERRNO) && !defined(CONFIG_ERRNO_IN_TLS)
	int errno_var;
#endif
};
#endif

/* private, used by k_poll and k_work_poll */
struct k_work_poll;
typedef int (*_poller_cb_t)(struct k_poll_event *event, uint32_t state);
struct z_poller {
	bool is_polling;
	uint8_t mode;
};

#ifdef CONFIG_THREAD_RUNTIME_STATS
struct k_thread_runtime_stats {
	/* Thread execution cycles */
	uint64_t execution_cycles;
};

typedef struct k_thread_runtime_stats k_thread_runtime_stats_t;

struct _thread_runtime_stats {
	/* Timestamp when last switched in */
	uint32_t last_switched_in;

	k_thread_runtime_stats_t stats;
};
#endif

/**
 * @ingroup thread_apis
 * Thread Structure
 */
struct k_thread {

	struct _thread_base base;

	/** defined by the architecture, but all archs need these */
	struct _callee_saved callee_saved;

	/** static thread init data */
	void *init_data;

	/**
	 * abort function
	 *
	 * This function pointer, if non-NULL, will be run once after the
	 * thread has completely exited. It may run in the context of:
	 *   - the idle thread if the thread self-exited
	 *   - another thread calling k_thread_abort()
	 *   - a fatal exception handler on a special stack
	 *
	 * It will never run in the context of the thread itself.
	 *
	 * A pointer to the thread object that was aborted is provided. At the
	 * time this runs, this thread object has completely exited. It may
	 * be re-used with k_thread_create() or return it to a heap or slab
	 * pool.
	 *
	 * This function does not run with any kind of lock active and
	 * there is the possibility of races leading to undefined behavior
	 * if other threads are attempting to free or recycle this object
	 * concurrently.
	 */
	void (*fn_abort)(struct k_thread *aborted);

#if defined(CONFIG_POLL)
	struct z_poller poller;
#endif

#if defined(CONFIG_THREAD_MONITOR)
	/** thread entry and parameters description */
	struct __thread_entry entry;

	/** next item in list of all threads */
	struct k_thread *next_thread;
#endif

#if defined(CONFIG_THREAD_NAME)
	/** Thread name */
	char name[CONFIG_THREAD_MAX_NAME_LEN];
#endif

#ifdef CONFIG_THREAD_CUSTOM_DATA
	/** crude thread-local storage */
	void *custom_data;
#endif

#ifdef CONFIG_THREAD_USERSPACE_LOCAL_DATA
	struct _thread_userspace_local_data *userspace_local_data;
#endif

#if defined(CONFIG_ERRNO) && !defined(CONFIG_ERRNO_IN_TLS)
#ifndef CONFIG_USERSPACE
	/** per-thread errno variable */
	int errno_var;
#endif
#endif

#if defined(CONFIG_THREAD_STACK_INFO)
	/** Stack Info */
	struct _thread_stack_info stack_info;
#endif /* CONFIG_THREAD_STACK_INFO */

#if defined(CONFIG_USERSPACE)
	/** memory domain info of the thread */
	struct _mem_domain_info mem_domain_info;
	/** Base address of thread stack */
	k_thread_stack_t *stack_obj;
	/** current syscall frame pointer */
	void *syscall_frame;
#endif /* CONFIG_USERSPACE */


#if defined(CONFIG_USE_SWITCH)
	/* When using __switch() a few previously arch-specific items
	 * become part of the core OS
	 */

	/** z_swap() return value */
	int swap_retval;

	/** Context handle returned via arch_switch() */
	void *switch_handle;
#endif
	/** resource pool */
	struct k_mem_pool *resource_pool;

#if defined(CONFIG_THREAD_LOCAL_STORAGE)
	/* Pointer to arch-specific TLS area */
	uintptr_t tls;
#endif /* CONFIG_THREAD_LOCAL_STORAGE */

#ifdef CONFIG_THREAD_RUNTIME_STATS
	/** Runtime statistics */
	struct _thread_runtime_stats rt_stats;
#endif

	/** arch-specifics: must always be at the end */
	struct _thread_arch arch;
};

typedef struct k_thread _thread_t;
typedef struct k_thread *k_tid_t;

enum execution_context_types {
	K_ISR = 0,
	K_COOP_THREAD,
	K_PREEMPT_THREAD,
};

/**
 * @addtogroup thread_apis
 * @{
 */

typedef void (*k_thread_user_cb_t)(const struct k_thread *thread,
				   void *user_data);

/**
 * @brief Iterate over all the threads in the system.
 *
 * This routine iterates over all the threads in the system and
 * calls the user_cb function for each thread.
 *
 * @param user_cb Pointer to the user callback function.
 * @param user_data Pointer to user data.
 *
 * @note @option{CONFIG_THREAD_MONITOR} must be set for this function
 * to be effective.
 * @note This API uses @ref k_spin_lock to protect the _kernel.threads
 * list which means creation of new threads and terminations of existing
 * threads are blocked until this API returns.
 *
 * @return N/A
 */
extern void k_thread_foreach(k_thread_user_cb_t user_cb, void *user_data);

/**
 * @brief Iterate over all the threads in the system without locking.
 *
 * This routine works exactly the same like @ref k_thread_foreach
 * but unlocks interrupts when user_cb is executed.
 *
 * @param user_cb Pointer to the user callback function.
 * @param user_data Pointer to user data.
 *
 * @note @option{CONFIG_THREAD_MONITOR} must be set for this function
 * to be effective.
 * @note This API uses @ref k_spin_lock only when accessing the _kernel.threads
 * queue elements. It unlocks it during user callback function processing.
 * If a new task is created when this @c foreach function is in progress,
 * the added new task would not be included in the enumeration.
 * If a task is aborted during this enumeration, there would be a race here
 * and there is a possibility that this aborted task would be included in the
 * enumeration.
 * @note If the task is aborted and the memory occupied by its @c k_thread
 * structure is reused when this @c k_thread_foreach_unlocked is in progress
 * it might even lead to the system behave unstable.
 * This function may never return, as it would follow some @c next task
 * pointers treating given pointer as a pointer to the k_thread structure
 * while it is something different right now.
 * Do not reuse the memory that was occupied by k_thread structure of aborted
 * task if it was aborted after this function was called in any context.
 */
extern void k_thread_foreach_unlocked(
	k_thread_user_cb_t user_cb, void *user_data);

/** @} */

/**
 * @defgroup thread_apis Thread APIs
 * @ingroup kernel_apis
 * @{
 */

#endif /* !_ASMLANGUAGE */


/*
 * Thread user options. May be needed by assembly code. Common part uses low
 * bits, arch-specific use high bits.
 */

/**
 * @brief system thread that must not abort
 * */
#define K_ESSENTIAL (BIT(0))

#if defined(CONFIG_FPU_SHARING)
/**
 * @brief thread uses floating point registers
 */
#define K_FP_REGS (BIT(1))
#endif

/**
 * @brief user mode thread
 *
 * This thread has dropped from supervisor mode to user mode and consequently
 * has additional restrictions
 */
#define K_USER (BIT(2))

/**
 * @brief Inherit Permissions
 *
 * @details
 * Indicates that the thread being created should inherit all kernel object
 * permissions from the thread that created it. No effect if
 * @option{CONFIG_USERSPACE} is not enabled.
 */
#define K_INHERIT_PERMS (BIT(3))

#ifdef CONFIG_X86
/* x86 Bitmask definitions for threads user options */

#if defined(CONFIG_FPU_SHARING) && defined(CONFIG_SSE)
/* thread uses SSEx (and also FP) registers */
#define K_SSE_REGS (BIT(7))
#endif
#endif

/* end - thread options */

#if !defined(_ASMLANGUAGE)
/**
 * @brief Create a thread.
 *
 * This routine initializes a thread, then schedules it for execution.
 *
 * The new thread may be scheduled for immediate execution or a delayed start.
 * If the newly spawned thread does not have a delayed start the kernel
 * scheduler may preempt the current thread to allow the new thread to
 * execute.
 *
 * Thread options are architecture-specific, and can include K_ESSENTIAL,
 * K_FP_REGS, and K_SSE_REGS. Multiple options may be specified by separating
 * them using "|" (the logical OR operator).
 *
 * Stack objects passed to this function must be originally defined with
 * either of these macros in order to be portable:
 *
 * - K_THREAD_STACK_DEFINE() - For stacks that may support either user or
 *   supervisor threads.
 * - K_KERNEL_STACK_DEFINE() - For stacks that may support supervisor
 *   threads only. These stacks use less memory if CONFIG_USERSPACE is
 *   enabled.
 *
 * The stack_size parameter has constraints. It must either be:
 *
 * - The original size value passed to K_THREAD_STACK_DEFINE() or
 *   K_KERNEL_STACK_DEFINE()
 * - The return value of K_THREAD_STACK_SIZEOF(stack) if the stack was
 *   defined with K_THREAD_STACK_DEFINE()
 * - The return value of K_KERNEL_STACK_SIZEOF(stack) if the stack was
 *   defined with K_KERNEL_STACK_DEFINE().
 *
 * Using other values, or sizeof(stack) may produce undefined behavior.
 *
 * @param new_thread Pointer to uninitialized struct k_thread
 * @param stack Pointer to the stack space.
 * @param stack_size Stack size in bytes.
 * @param entry Thread entry function.
 * @param p1 1st entry point parameter.
 * @param p2 2nd entry point parameter.
 * @param p3 3rd entry point parameter.
 * @param prio Thread priority.
 * @param options Thread options.
 * @param delay Scheduling delay, or K_NO_WAIT (for no delay).
 *
 * @return ID of new thread.
 *
 */
__syscall k_tid_t k_thread_create(struct k_thread *new_thread,
				  k_thread_stack_t *stack,
				  size_t stack_size,
				  k_thread_entry_t entry,
				  void *p1, void *p2, void *p3,
				  int prio, uint32_t options, k_timeout_t delay);

/**
 * @brief Drop a thread's privileges permanently to user mode
 *
 * This allows a supervisor thread to be re-used as a user thread.
 * This function does not return, but control will transfer to the provided
 * entry point as if this was a new user thread.
 *
 * The implementation ensures that the stack buffer contents are erased.
 * Any thread-local storage will be reverted to a pristine state.
 *
 * Memory domain membership, resource pool assignment, kernel object
 * permissions, priority, and thread options are preserved.
 *
 * A common use of this function is to re-use the main thread as a user thread
 * once all supervisor mode-only tasks have been completed.
 *
 * @param entry Function to start executing from
 * @param p1 1st entry point parameter
 * @param p2 2nd entry point parameter
 * @param p3 3rd entry point parameter
 */
extern FUNC_NORETURN void k_thread_user_mode_enter(k_thread_entry_t entry,
						   void *p1, void *p2,
						   void *p3);

/**
 * @brief Grant a thread access to a set of kernel objects
 *
 * This is a convenience function. For the provided thread, grant access to
 * the remaining arguments, which must be pointers to kernel objects.
 *
 * The thread object must be initialized (i.e. running). The objects don't
 * need to be.
 * Note that NULL shouldn't be passed as an argument.
 *
 * @param thread Thread to grant access to objects
 * @param ... list of kernel object pointers
 */
#define k_thread_access_grant(thread, ...) \
	FOR_EACH_FIXED_ARG(k_object_access_grant, (;), thread, __VA_ARGS__)

/**
 * @brief Assign a resource memory pool to a thread
 *
 * By default, threads have no resource pool assigned unless their parent
 * thread has a resource pool, in which case it is inherited. Multiple
 * threads may be assigned to the same memory pool.
 *
 * Changing a thread's resource pool will not migrate allocations from the
 * previous pool.
 *
 * @param thread Target thread to assign a memory pool for resource requests.
 * @param pool Memory pool to use for resources,
 *             or NULL if the thread should no longer have a memory pool.
 */
static inline void k_thread_resource_pool_assign(struct k_thread *thread,
						 struct k_mem_pool *pool)
{
	thread->resource_pool = pool;
}

#if defined(CONFIG_INIT_STACKS) && defined(CONFIG_THREAD_STACK_INFO)
/**
 * @brief Obtain stack usage information for the specified thread
 *
 * User threads will need to have permission on the target thread object.
 *
 * Some hardware may prevent inspection of a stack buffer currently in use.
 * If this API is called from supervisor mode, on the currently running thread,
 * on a platform which selects @option{CONFIG_NO_UNUSED_STACK_INSPECTION}, an
 * error will be generated.
 *
 * @param thread Thread to inspect stack information
 * @param unused_ptr Output parameter, filled in with the unused stack space
 *	of the target thread in bytes.
 * @return 0 on success
 * @return -EBADF Bad thread object (user mode only)
 * @return -EPERM No permissions on thread object (user mode only)
 * #return -ENOTSUP Forbidden by hardware policy
 * @return -EINVAL Thread is uninitialized or exited (user mode only)
 * @return -EFAULT Bad memory address for unused_ptr (user mode only)
 */
__syscall int k_thread_stack_space_get(const struct k_thread *thread,
				       size_t *unused_ptr);
#endif

#if (CONFIG_HEAP_MEM_POOL_SIZE > 0)
/**
 * @brief Assign the system heap as a thread's resource pool
 *
 * Similar to k_thread_resource_pool_assign(), but the thread will use
 * the kernel heap to draw memory.
 *
 * Use with caution, as a malicious thread could perform DoS attacks on the
 * kernel heap.
 *
 * @param thread Target thread to assign the system heap for resource requests
 *
 */
void k_thread_system_pool_assign(struct k_thread *thread);
#endif /* (CONFIG_HEAP_MEM_POOL_SIZE > 0) */

/**
 * @brief Sleep until a thread exits
 *
 * The caller will be put to sleep until the target thread exits, either due
 * to being aborted, self-exiting, or taking a fatal error. This API returns
 * immediately if the thread isn't running.
 *
 * This API may only be called from ISRs with a K_NO_WAIT timeout.
 *
 * @param thread Thread to wait to exit
 * @param timeout upper bound time to wait for the thread to exit.
 * @retval 0 success, target thread has exited or wasn't running
 * @retval -EBUSY returned without waiting
 * @retval -EAGAIN waiting period timed out
 * @retval -EDEADLK target thread is joining on the caller, or target thread
 *                  is the caller
 */
__syscall int k_thread_join(struct k_thread *thread, k_timeout_t timeout);

/**
 * @brief Put the current thread to sleep.
 *
 * This routine puts the current thread to sleep for @a duration,
 * specified as a k_timeout_t object.
 *
 * @note if @a timeout is set to K_FOREVER then the thread is suspended.
 *
 * @param timeout Desired duration of sleep.
 *
 * @return Zero if the requested time has elapsed or the number of milliseconds
 * left to sleep, if thread was woken up by \ref k_wakeup call.
 */
__syscall int32_t k_sleep(k_timeout_t timeout);

/**
 * @brief Put the current thread to sleep.
 *
 * This routine puts the current thread to sleep for @a duration milliseconds.
 *
 * @param ms Number of milliseconds to sleep.
 *
 * @return Zero if the requested time has elapsed or the number of milliseconds
 * left to sleep, if thread was woken up by \ref k_wakeup call.
 */
static inline int32_t k_msleep(int32_t ms)
{
	return k_sleep(Z_TIMEOUT_MS(ms));
}

/**
 * @brief Put the current thread to sleep with microsecond resolution.
 *
 * This function is unlikely to work as expected without kernel tuning.
 * In particular, because the lower bound on the duration of a sleep is
 * the duration of a tick, @option{CONFIG_SYS_CLOCK_TICKS_PER_SEC} must be
 * adjusted to achieve the resolution desired. The implications of doing
 * this must be understood before attempting to use k_usleep(). Use with
 * caution.
 *
 * @param us Number of microseconds to sleep.
 *
 * @return Zero if the requested time has elapsed or the number of microseconds
 * left to sleep, if thread was woken up by \ref k_wakeup call.
 */
__syscall int32_t k_usleep(int32_t us);

/**
 * @brief Cause the current thread to busy wait.
 *
 * This routine causes the current thread to execute a "do nothing" loop for
 * @a usec_to_wait microseconds.
 *
 * @note The clock used for the microsecond-resolution delay here may
 * be skewed relative to the clock used for system timeouts like
 * k_sleep().  For example k_busy_wait(1000) may take slightly more or
 * less time than k_sleep(K_MSEC(1)), with the offset dependent on
 * clock tolerances.
 *
 * @return N/A
 */
__syscall void k_busy_wait(uint32_t usec_to_wait);

/**
 * @brief Yield the current thread.
 *
 * This routine causes the current thread to yield execution to another
 * thread of the same or higher priority. If there are no other ready threads
 * of the same or higher priority, the routine returns immediately.
 *
 * @return N/A
 */
__syscall void k_yield(void);

/**
 * @brief Wake up a sleeping thread.
 *
 * This routine prematurely wakes up @a thread from sleeping.
 *
 * If @a thread is not currently sleeping, the routine has no effect.
 *
 * @param thread ID of thread to wake.
 *
 * @return N/A
 */
__syscall void k_wakeup(k_tid_t thread);

/**
 * @brief Get thread ID of the current thread.
 *
 * @return ID of current thread.
 *
 */
__syscall k_tid_t k_current_get(void);

/**
 * @brief Abort a thread.
 *
 * This routine permanently stops execution of @a thread. The thread is taken
 * off all kernel queues it is part of (i.e. the ready queue, the timeout
 * queue, or a kernel object wait queue). However, any kernel resources the
 * thread might currently own (such as mutexes or memory blocks) are not
 * released. It is the responsibility of the caller of this routine to ensure
 * all necessary cleanup is performed.
 *
 * @param thread ID of thread to abort.
 *
 * @return N/A
 */
__syscall void k_thread_abort(k_tid_t thread);


/**
 * @brief Start an inactive thread
 *
 * If a thread was created with K_FOREVER in the delay parameter, it will
 * not be added to the scheduling queue until this function is called
 * on it.
 *
 * @param thread thread to start
 */
__syscall void k_thread_start(k_tid_t thread);

extern k_ticks_t z_timeout_expires(const struct _timeout *timeout);
extern k_ticks_t z_timeout_remaining(const struct _timeout *timeout);

#ifdef CONFIG_SYS_CLOCK_EXISTS

/**
 * @brief Get time when a thread wakes up, in system ticks
 *
 * This routine computes the system uptime when a waiting thread next
 * executes, in units of system ticks.  If the thread is not waiting,
 * it returns current system time.
 */
__syscall k_ticks_t k_thread_timeout_expires_ticks(struct k_thread *t);

static inline k_ticks_t z_impl_k_thread_timeout_expires_ticks(
						struct k_thread *t)
{
	return z_timeout_expires(&t->base.timeout);
}

/**
 * @brief Get time remaining before a thread wakes up, in system ticks
 *
 * This routine computes the time remaining before a waiting thread
 * next executes, in units of system ticks.  If the thread is not
 * waiting, it returns zero.
 */
__syscall k_ticks_t k_thread_timeout_remaining_ticks(struct k_thread *t);

static inline k_ticks_t z_impl_k_thread_timeout_remaining_ticks(
						struct k_thread *t)
{
	return z_timeout_remaining(&t->base.timeout);
}

#endif /* CONFIG_SYS_CLOCK_EXISTS */

/**
 * @cond INTERNAL_HIDDEN
 */

/* timeout has timed out and is not on _timeout_q anymore */
#define _EXPIRED (-2)

struct _static_thread_data {
	struct k_thread *init_thread;
	k_thread_stack_t *init_stack;
	unsigned int init_stack_size;
	k_thread_entry_t init_entry;
	void *init_p1;
	void *init_p2;
	void *init_p3;
	int init_prio;
	uint32_t init_options;
	int32_t init_delay;
	void (*init_abort)(void);
	const char *init_name;
};

#define Z_THREAD_INITIALIZER(thread, stack, stack_size,           \
			    entry, p1, p2, p3,                   \
			    prio, options, delay, abort, tname)  \
	{                                                        \
	.init_thread = (thread),				 \
	.init_stack = (stack),					 \
	.init_stack_size = (stack_size),                         \
	.init_entry = (k_thread_entry_t)entry,			 \
	.init_p1 = (void *)p1,                                   \
	.init_p2 = (void *)p2,                                   \
	.init_p3 = (void *)p3,                                   \
	.init_prio = (prio),                                     \
	.init_options = (options),                               \
	.init_delay = (delay),                                   \
	.init_abort = (abort),                                   \
	.init_name = STRINGIFY(tname),                           \
	}

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @brief Statically define and initialize a thread.
 *
 * The thread may be scheduled for immediate execution or a delayed start.
 *
 * Thread options are architecture-specific, and can include K_ESSENTIAL,
 * K_FP_REGS, and K_SSE_REGS. Multiple options may be specified by separating
 * them using "|" (the logical OR operator).
 *
 * The ID of the thread can be accessed using:
 *
 * @code extern const k_tid_t <name>; @endcode
 *
 * @param name Name of the thread.
 * @param stack_size Stack size in bytes.
 * @param entry Thread entry function.
 * @param p1 1st entry point parameter.
 * @param p2 2nd entry point parameter.
 * @param p3 3rd entry point parameter.
 * @param prio Thread priority.
 * @param options Thread options.
 * @param delay Scheduling delay (in milliseconds), zero for no delay.
 *
 *
 * @internal It has been observed that the x86 compiler by default aligns
 * these _static_thread_data structures to 32-byte boundaries, thereby
 * wasting space. To work around this, force a 4-byte alignment.
 *
 */
#define K_THREAD_DEFINE(name, stack_size,                                \
			entry, p1, p2, p3,                               \
			prio, options, delay)                            \
	K_THREAD_STACK_DEFINE(_k_thread_stack_##name, stack_size);	 \
	struct k_thread _k_thread_obj_##name;				 \
	Z_STRUCT_SECTION_ITERABLE(_static_thread_data, _k_thread_data_##name) =\
		Z_THREAD_INITIALIZER(&_k_thread_obj_##name,		 \
				    _k_thread_stack_##name, stack_size,  \
				entry, p1, p2, p3, prio, options, delay, \
				NULL, name);				 	 \
	const k_tid_t name = (k_tid_t)&_k_thread_obj_##name

/**
 * @brief Get a thread's priority.
 *
 * This routine gets the priority of @a thread.
 *
 * @param thread ID of thread whose priority is needed.
 *
 * @return Priority of @a thread.
 */
__syscall int k_thread_priority_get(k_tid_t thread);

/**
 * @brief Set a thread's priority.
 *
 * This routine immediately changes the priority of @a thread.
 *
 * Rescheduling can occur immediately depending on the priority @a thread is
 * set to:
 *
 * - If its priority is raised above the priority of the caller of this
 * function, and the caller is preemptible, @a thread will be scheduled in.
 *
 * - If the caller operates on itself, it lowers its priority below that of
 * other threads in the system, and the caller is preemptible, the thread of
 * highest priority will be scheduled in.
 *
 * Priority can be assigned in the range of -CONFIG_NUM_COOP_PRIORITIES to
 * CONFIG_NUM_PREEMPT_PRIORITIES-1, where -CONFIG_NUM_COOP_PRIORITIES is the
 * highest priority.
 *
 * @param thread ID of thread whose priority is to be set.
 * @param prio New priority.
 *
 * @warning Changing the priority of a thread currently involved in mutex
 * priority inheritance may result in undefined behavior.
 *
 * @return N/A
 */
__syscall void k_thread_priority_set(k_tid_t thread, int prio);


#ifdef CONFIG_SCHED_DEADLINE
/**
 * @brief Set deadline expiration time for scheduler
 *
 * This sets the "deadline" expiration as a time delta from the
 * current time, in the same units used by k_cycle_get_32().  The
 * scheduler (when deadline scheduling is enabled) will choose the
 * next expiring thread when selecting between threads at the same
 * static priority.  Threads at different priorities will be scheduled
 * according to their static priority.
 *
 * @note Deadlines that are negative (i.e. in the past) are still seen
 * as higher priority than others, even if the thread has "finished"
 * its work.  If you don't want it scheduled anymore, you have to
 * reset the deadline into the future, block/pend the thread, or
 * modify its priority with k_thread_priority_set().
 *
 * @note Despite the API naming, the scheduler makes no guarantees the
 * the thread WILL be scheduled within that deadline, nor does it take
 * extra metadata (like e.g. the "runtime" and "period" parameters in
 * Linux sched_setattr()) that allows the kernel to validate the
 * scheduling for achievability.  Such features could be implemented
 * above this call, which is simply input to the priority selection
 * logic.
 *
 * @note You should enable @option{CONFIG_SCHED_DEADLINE} in your project
 * configuration.
 *
 * @param thread A thread on which to set the deadline
 * @param deadline A time delta, in cycle units
 *
 */
__syscall void k_thread_deadline_set(k_tid_t thread, int deadline);
#endif

#ifdef CONFIG_SCHED_CPU_MASK
/**
 * @brief Sets all CPU enable masks to zero
 *
 * After this returns, the thread will no longer be schedulable on any
 * CPUs.  The thread must not be currently runnable.
 *
 * @note You should enable @option{CONFIG_SCHED_DEADLINE} in your project
 * configuration.
 *
 * @param thread Thread to operate upon
 * @return Zero on success, otherwise error code
 */
int k_thread_cpu_mask_clear(k_tid_t thread);

/**
 * @brief Sets all CPU enable masks to one
 *
 * After this returns, the thread will be schedulable on any CPU.  The
 * thread must not be currently runnable.
 *
 * @note You should enable @option{CONFIG_SCHED_DEADLINE} in your project
 * configuration.
 *
 * @param thread Thread to operate upon
 * @return Zero on success, otherwise error code
 */
int k_thread_cpu_mask_enable_all(k_tid_t thread);

/**
 * @brief Enable thread to run on specified CPU
 *
 * The thread must not be currently runnable.
 *
 * @note You should enable @option{CONFIG_SCHED_DEADLINE} in your project
 * configuration.
 *
 * @param thread Thread to operate upon
 * @param cpu CPU index
 * @return Zero on success, otherwise error code
 */
int k_thread_cpu_mask_enable(k_tid_t thread, int cpu);

/**
 * @brief Prevent thread to run on specified CPU
 *
 * The thread must not be currently runnable.
 *
 * @note You should enable @option{CONFIG_SCHED_DEADLINE} in your project
 * configuration.
 *
 * @param thread Thread to operate upon
 * @param cpu CPU index
 * @return Zero on success, otherwise error code
 */
int k_thread_cpu_mask_disable(k_tid_t thread, int cpu);
#endif

/**
 * @brief Suspend a thread.
 *
 * This routine prevents the kernel scheduler from making @a thread
 * the current thread. All other internal operations on @a thread are
 * still performed; for example, kernel objects it is waiting on are
 * still handed to it.  Note that any existing timeouts
 * (e.g. k_sleep(), or a timeout argument to k_sem_take() et. al.)
 * will be canceled.  On resume, the thread will begin running
 * immediately and return from the blocked call.
 *
 * If @a thread is already suspended, the routine has no effect.
 *
 * @param thread ID of thread to suspend.
 *
 * @return N/A
 */
__syscall void k_thread_suspend(k_tid_t thread);

/**
 * @brief Resume a suspended thread.
 *
 * This routine allows the kernel scheduler to make @a thread the current
 * thread, when it is next eligible for that role.
 *
 * If @a thread is not currently suspended, the routine has no effect.
 *
 * @param thread ID of thread to resume.
 *
 * @return N/A
 */
__syscall void k_thread_resume(k_tid_t thread);

/**
 * @brief Set time-slicing period and scope.
 *
 * This routine specifies how the scheduler will perform time slicing of
 * preemptible threads.
 *
 * To enable time slicing, @a slice must be non-zero. The scheduler
 * ensures that no thread runs for more than the specified time limit
 * before other threads of that priority are given a chance to execute.
 * Any thread whose priority is higher than @a prio is exempted, and may
 * execute as long as desired without being preempted due to time slicing.
 *
 * Time slicing only limits the maximum amount of time a thread may continuously
 * execute. Once the scheduler selects a thread for execution, there is no
 * minimum guaranteed time the thread will execute before threads of greater or
 * equal priority are scheduled.
 *
 * When the current thread is the only one of that priority eligible
 * for execution, this routine has no effect; the thread is immediately
 * rescheduled after the slice period expires.
 *
 * To disable timeslicing, set both @a slice and @a prio to zero.
 *
 * @param slice Maximum time slice length (in milliseconds).
 * @param prio Highest thread priority level eligible for time slicing.
 *
 * @return N/A
 */
extern void k_sched_time_slice_set(int32_t slice, int prio);

/** @} */

/**
 * @addtogroup isr_apis
 * @{
 */

/**
 * @brief Determine if code is running at interrupt level.
 *
 * This routine allows the caller to customize its actions, depending on
 * whether it is a thread or an ISR.
 *
 * @note Can be called by ISRs.
 *
 * @return false if invoked by a thread.
 * @return true if invoked by an ISR.
 */
extern bool k_is_in_isr(void);

/**
 * @brief Determine if code is running in a preemptible thread.
 *
 * This routine allows the caller to customize its actions, depending on
 * whether it can be preempted by another thread. The routine returns a 'true'
 * value if all of the following conditions are met:
 *
 * - The code is running in a thread, not at ISR.
 * - The thread's priority is in the preemptible range.
 * - The thread has not locked the scheduler.
 *
 * @note Can be called by ISRs.
 *
 * @return 0 if invoked by an ISR or by a cooperative thread.
 * @return Non-zero if invoked by a preemptible thread.
 */
__syscall int k_is_preempt_thread(void);

/**
 * @brief Test whether startup is in the before-main-task phase.
 *
 * This routine allows the caller to customize its actions, depending on
 * whether it being invoked before the kernel is fully active.
 *
 * @note Can be called by ISRs.
 *
 * @return true if invoked before post-kernel initialization
 * @return false if invoked during/after post-kernel initialization
 */
static inline bool k_is_pre_kernel(void)
{
	extern bool z_sys_post_kernel; /* in init.c */

	return !z_sys_post_kernel;
}

/**
 * @}
 */

/**
 * @addtogroup thread_apis
 * @{
 */

/**
 * @brief Lock the scheduler.
 *
 * This routine prevents the current thread from being preempted by another
 * thread by instructing the scheduler to treat it as a cooperative thread.
 * If the thread subsequently performs an operation that makes it unready,
 * it will be context switched out in the normal manner. When the thread
 * again becomes the current thread, its non-preemptible status is maintained.
 *
 * This routine can be called recursively.
 *
 * @note k_sched_lock() and k_sched_unlock() should normally be used
 * when the operation being performed can be safely interrupted by ISRs.
 * However, if the amount of processing involved is very small, better
 * performance may be obtained by using irq_lock() and irq_unlock().
 *
 * @return N/A
 */
extern void k_sched_lock(void);

/**
 * @brief Unlock the scheduler.
 *
 * This routine reverses the effect of a previous call to k_sched_lock().
 * A thread must call the routine once for each time it called k_sched_lock()
 * before the thread becomes preemptible.
 *
 * @return N/A
 */
extern void k_sched_unlock(void);

/**
 * @brief Set current thread's custom data.
 *
 * This routine sets the custom data for the current thread to @ value.
 *
 * Custom data is not used by the kernel itself, and is freely available
 * for a thread to use as it sees fit. It can be used as a framework
 * upon which to build thread-local storage.
 *
 * @param value New custom data value.
 *
 * @return N/A
 *
 */
__syscall void k_thread_custom_data_set(void *value);

/**
 * @brief Get current thread's custom data.
 *
 * This routine returns the custom data for the current thread.
 *
 * @return Current custom data value.
 */
__syscall void *k_thread_custom_data_get(void);

/**
 * @brief Set current thread name
 *
 * Set the name of the thread to be used when @option{CONFIG_THREAD_MONITOR}
 * is enabled for tracing and debugging.
 *
 * @param thread_id Thread to set name, or NULL to set the current thread
 * @param value Name string
 * @retval 0 on success
 * @retval -EFAULT Memory access error with supplied string
 * @retval -ENOSYS Thread name configuration option not enabled
 * @retval -EINVAL Thread name too long
 */
__syscall int k_thread_name_set(k_tid_t thread_id, const char *value);

/**
 * @brief Get thread name
 *
 * Get the name of a thread
 *
 * @param thread_id Thread ID
 * @retval Thread name, or NULL if configuration not enabled
 */
const char *k_thread_name_get(k_tid_t thread_id);

/**
 * @brief Copy the thread name into a supplied buffer
 *
 * @param thread_id Thread to obtain name information
 * @param buf Destination buffer
 * @param size Destination buffer size
 * @retval -ENOSPC Destination buffer too small
 * @retval -EFAULT Memory access error
 * @retval -ENOSYS Thread name feature not enabled
 * @retval 0 Success
 */
__syscall int k_thread_name_copy(k_tid_t thread_id, char *buf,
				 size_t size);

/**
 * @brief Get thread state string
 *
 * Get the human friendly thread state string
 *
 * @param thread_id Thread ID
 * @retval Thread state string, empty if no state flag is set
 */
const char *k_thread_state_str(k_tid_t thread_id);

/**
 * @}
 */

/**
 * @addtogroup clock_apis
 * @{
 */

/**
 * @brief Generate null timeout delay.
 *
 * This macro generates a timeout delay that instructs a kernel API
 * not to wait if the requested operation cannot be performed immediately.
 *
 * @return Timeout delay value.
 */
#define K_NO_WAIT Z_TIMEOUT_NO_WAIT

/**
 * @brief Generate timeout delay from nanoseconds.
 *
 * This macro generates a timeout delay that instructs a kernel API to
 * wait up to @a t nanoseconds to perform the requested operation.
 * Note that timer precision is limited to the tick rate, not the
 * requested value.
 *
 * @param t Duration in nanoseconds.
 *
 * @return Timeout delay value.
 */
#define K_NSEC(t)     Z_TIMEOUT_NS(t)

/**
 * @brief Generate timeout delay from microseconds.
 *
 * This macro generates a timeout delay that instructs a kernel API
 * to wait up to @a t microseconds to perform the requested operation.
 * Note that timer precision is limited to the tick rate, not the
 * requested value.
 *
 * @param t Duration in microseconds.
 *
 * @return Timeout delay value.
 */
#define K_USEC(t)     Z_TIMEOUT_US(t)

/**
 * @brief Generate timeout delay from cycles.
 *
 * This macro generates a timeout delay that instructs a kernel API
 * to wait up to @a t cycles to perform the requested operation.
 *
 * @param t Duration in cycles.
 *
 * @return Timeout delay value.
 */
#define K_CYC(t)     Z_TIMEOUT_CYC(t)

/**
 * @brief Generate timeout delay from system ticks.
 *
 * This macro generates a timeout delay that instructs a kernel API
 * to wait up to @a t ticks to perform the requested operation.
 *
 * @param t Duration in system ticks.
 *
 * @return Timeout delay value.
 */
#define K_TICKS(t)     Z_TIMEOUT_TICKS(t)

/**
 * @brief Generate timeout delay from milliseconds.
 *
 * This macro generates a timeout delay that instructs a kernel API
 * to wait up to @a ms milliseconds to perform the requested operation.
 *
 * @param ms Duration in milliseconds.
 *
 * @return Timeout delay value.
 */
#define K_MSEC(ms)     Z_TIMEOUT_MS(ms)

/**
 * @brief Generate timeout delay from seconds.
 *
 * This macro generates a timeout delay that instructs a kernel API
 * to wait up to @a s seconds to perform the requested operation.
 *
 * @param s Duration in seconds.
 *
 * @return Timeout delay value.
 */
#define K_SECONDS(s)   K_MSEC((s) * MSEC_PER_SEC)

/**
 * @brief Generate timeout delay from minutes.

 * This macro generates a timeout delay that instructs a kernel API
 * to wait up to @a m minutes to perform the requested operation.
 *
 * @param m Duration in minutes.
 *
 * @return Timeout delay value.
 */
#define K_MINUTES(m)   K_SECONDS((m) * 60)

/**
 * @brief Generate timeout delay from hours.
 *
 * This macro generates a timeout delay that instructs a kernel API
 * to wait up to @a h hours to perform the requested operation.
 *
 * @param h Duration in hours.
 *
 * @return Timeout delay value.
 */
#define K_HOURS(h)     K_MINUTES((h) * 60)

/**
 * @brief Generate infinite timeout delay.
 *
 * This macro generates a timeout delay that instructs a kernel API
 * to wait as long as necessary to perform the requested operation.
 *
 * @return Timeout delay value.
 */
#define K_FOREVER Z_FOREVER

#ifdef CONFIG_TIMEOUT_64BIT

/**
 * @brief Generates an absolute/uptime timeout value from system ticks
 *
 * This macro generates a timeout delay that represents an expiration
 * at the absolute uptime value specified, in system ticks.  That is, the
 * timeout will expire immediately after the system uptime reaches the
 * specified tick count.
 *
 * @param t Tick uptime value
 * @return Timeout delay value
 */
#define K_TIMEOUT_ABS_TICKS(t) Z_TIMEOUT_TICKS(Z_TICK_ABS(MAX(t, 0)))

/**
 * @brief Generates an absolute/uptime timeout value from milliseconds
 *
 * This macro generates a timeout delay that represents an expiration
 * at the absolute uptime value specified, in milliseconds.  That is,
 * the timeout will expire immediately after the system uptime reaches
 * the specified tick count.
 *
 * @param t Millisecond uptime value
 * @return Timeout delay value
 */
#define K_TIMEOUT_ABS_MS(t) K_TIMEOUT_ABS_TICKS(k_ms_to_ticks_ceil64(t))

/**
 * @brief Generates an absolute/uptime timeout value from microseconds
 *
 * This macro generates a timeout delay that represents an expiration
 * at the absolute uptime value specified, in microseconds.  That is,
 * the timeout will expire immediately after the system uptime reaches
 * the specified time.  Note that timer precision is limited by the
 * system tick rate and not the requested timeout value.
 *
 * @param t Microsecond uptime value
 * @return Timeout delay value
 */
#define K_TIMEOUT_ABS_US(t) K_TIMEOUT_ABS_TICKS(k_us_to_ticks_ceil64(t))

/**
 * @brief Generates an absolute/uptime timeout value from nanoseconds
 *
 * This macro generates a timeout delay that represents an expiration
 * at the absolute uptime value specified, in nanoseconds.  That is,
 * the timeout will expire immediately after the system uptime reaches
 * the specified time.  Note that timer precision is limited by the
 * system tick rate and not the requested timeout value.
 *
 * @param t Nanosecond uptime value
 * @return Timeout delay value
 */
#define K_TIMEOUT_ABS_NS(t) K_TIMEOUT_ABS_TICKS(k_ns_to_ticks_ceil64(t))

/**
 * @brief Generates an absolute/uptime timeout value from system cycles
 *
 * This macro generates a timeout delay that represents an expiration
 * at the absolute uptime value specified, in cycles.  That is, the
 * timeout will expire immediately after the system uptime reaches the
 * specified time.  Note that timer precision is limited by the system
 * tick rate and not the requested timeout value.
 *
 * @param t Cycle uptime value
 * @return Timeout delay value
 */
#define K_TIMEOUT_ABS_CYC(t) K_TIMEOUT_ABS_TICKS(k_cyc_to_ticks_ceil64(t))

#endif

/**
 * @}
 */

/**
 * @cond INTERNAL_HIDDEN
 */

struct k_timer {
	/*
	 * _timeout structure must be first here if we want to use
	 * dynamic timer allocation. timeout.node is used in the double-linked
	 * list of free timers
	 */
	struct _timeout timeout;

	/* wait queue for the (single) thread waiting on this timer */
	_wait_q_t wait_q;

	/* runs in ISR context */
	void (*expiry_fn)(struct k_timer *timer);

	/* runs in the context of the thread that calls k_timer_stop() */
	void (*stop_fn)(struct k_timer *timer);

	/* timer period */
	k_timeout_t period;

	/* timer status */
	uint32_t status;

	/* user-specific data, also used to support legacy features */
	void *user_data;

	_OBJECT_TRACING_NEXT_PTR(k_timer)
	_OBJECT_TRACING_LINKED_FLAG
};

#define Z_TIMER_INITIALIZER(obj, expiry, stop) \
	{ \
	.timeout = { \
		.node = {},\
		.fn = z_timer_expiration_handler, \
		.dticks = 0, \
	}, \
	.wait_q = Z_WAIT_Q_INIT(&obj.wait_q), \
	.expiry_fn = expiry, \
	.stop_fn = stop, \
	.status = 0, \
	.user_data = 0, \
	_OBJECT_TRACING_INIT \
	}

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup timer_apis Timer APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @typedef k_timer_expiry_t
 * @brief Timer expiry function type.
 *
 * A timer's expiry function is executed by the system clock interrupt handler
 * each time the timer expires. The expiry function is optional, and is only
 * invoked if the timer has been initialized with one.
 *
 * @param timer     Address of timer.
 *
 * @return N/A
 */
typedef void (*k_timer_expiry_t)(struct k_timer *timer);

/**
 * @typedef k_timer_stop_t
 * @brief Timer stop function type.
 *
 * A timer's stop function is executed if the timer is stopped prematurely.
 * The function runs in the context of call that stops the timer.  As
 * k_timer_stop() can be invoked from an ISR, the stop function must be
 * callable from interrupt context (isr-ok).
 *
 * The stop function is optional, and is only invoked if the timer has been
 * initialized with one.
 *
 * @param timer     Address of timer.
 *
 * @return N/A
 */
typedef void (*k_timer_stop_t)(struct k_timer *timer);

/**
 * @brief Statically define and initialize a timer.
 *
 * The timer can be accessed outside the module where it is defined using:
 *
 * @code extern struct k_timer <name>; @endcode
 *
 * @param name Name of the timer variable.
 * @param expiry_fn Function to invoke each time the timer expires.
 * @param stop_fn   Function to invoke if the timer is stopped while running.
 */
#define K_TIMER_DEFINE(name, expiry_fn, stop_fn) \
	Z_STRUCT_SECTION_ITERABLE(k_timer, name) = \
		Z_TIMER_INITIALIZER(name, expiry_fn, stop_fn)

/**
 * @brief Initialize a timer.
 *
 * This routine initializes a timer, prior to its first use.
 *
 * @param timer     Address of timer.
 * @param expiry_fn Function to invoke each time the timer expires.
 * @param stop_fn   Function to invoke if the timer is stopped while running.
 *
 * @return N/A
 */
extern void k_timer_init(struct k_timer *timer,
			 k_timer_expiry_t expiry_fn,
			 k_timer_stop_t stop_fn);

/**
 * @brief Start a timer.
 *
 * This routine starts a timer, and resets its status to zero. The timer
 * begins counting down using the specified duration and period values.
 *
 * Attempting to start a timer that is already running is permitted.
 * The timer's status is reset to zero and the timer begins counting down
 * using the new duration and period values.
 *
 * @param timer     Address of timer.
 * @param duration  Initial timer duration.
 * @param period    Timer period.
 *
 * @return N/A
 */
__syscall void k_timer_start(struct k_timer *timer,
			     k_timeout_t duration, k_timeout_t period);

/**
 * @brief Stop a timer.
 *
 * This routine stops a running timer prematurely. The timer's stop function,
 * if one exists, is invoked by the caller.
 *
 * Attempting to stop a timer that is not running is permitted, but has no
 * effect on the timer.
 *
 * @note Can be called by ISRs.  The stop handler has to be callable from ISRs
 * if @a k_timer_stop is to be called from ISRs.
 *
 * @param timer     Address of timer.
 *
 * @return N/A
 */
__syscall void k_timer_stop(struct k_timer *timer);

/**
 * @brief Read timer status.
 *
 * This routine reads the timer's status, which indicates the number of times
 * it has expired since its status was last read.
 *
 * Calling this routine resets the timer's status to zero.
 *
 * @param timer     Address of timer.
 *
 * @return Timer status.
 */
__syscall uint32_t k_timer_status_get(struct k_timer *timer);

/**
 * @brief Synchronize thread to timer expiration.
 *
 * This routine blocks the calling thread until the timer's status is non-zero
 * (indicating that it has expired at least once since it was last examined)
 * or the timer is stopped. If the timer status is already non-zero,
 * or the timer is already stopped, the caller continues without waiting.
 *
 * Calling this routine resets the timer's status to zero.
 *
 * This routine must not be used by interrupt handlers, since they are not
 * allowed to block.
 *
 * @param timer     Address of timer.
 *
 * @return Timer status.
 */
__syscall uint32_t k_timer_status_sync(struct k_timer *timer);

#ifdef CONFIG_SYS_CLOCK_EXISTS

/**
 * @brief Get next expiration time of a timer, in system ticks
 *
 * This routine returns the future system uptime reached at the next
 * time of expiration of the timer, in units of system ticks.  If the
 * timer is not running, current system time is returned.
 *
 * @param timer The timer object
 * @return Uptime of expiration, in ticks
 */
__syscall k_ticks_t k_timer_expires_ticks(struct k_timer *timer);

static inline k_ticks_t z_impl_k_timer_expires_ticks(struct k_timer *timer)
{
	return z_timeout_expires(&timer->timeout);
}

/**
 * @brief Get time remaining before a timer next expires, in system ticks
 *
 * This routine computes the time remaining before a running timer
 * next expires, in units of system ticks.  If the timer is not
 * running, it returns zero.
 */
__syscall k_ticks_t k_timer_remaining_ticks(struct k_timer *timer);

static inline k_ticks_t z_impl_k_timer_remaining_ticks(struct k_timer *timer)
{
	return z_timeout_remaining(&timer->timeout);
}

/**
 * @brief Get time remaining before a timer next expires.
 *
 * This routine computes the (approximate) time remaining before a running
 * timer next expires. If the timer is not running, it returns zero.
 *
 * @param timer     Address of timer.
 *
 * @return Remaining time (in milliseconds).
 */
static inline uint32_t k_timer_remaining_get(struct k_timer *timer)
{
	return k_ticks_to_ms_floor32(k_timer_remaining_ticks(timer));
}

#endif /* CONFIG_SYS_CLOCK_EXISTS */

/**
 * @brief Associate user-specific data with a timer.
 *
 * This routine records the @a user_data with the @a timer, to be retrieved
 * later.
 *
 * It can be used e.g. in a timer handler shared across multiple subsystems to
 * retrieve data specific to the subsystem this timer is associated with.
 *
 * @param timer     Address of timer.
 * @param user_data User data to associate with the timer.
 *
 * @return N/A
 */
__syscall void k_timer_user_data_set(struct k_timer *timer, void *user_data);

/**
 * @internal
 */
static inline void z_impl_k_timer_user_data_set(struct k_timer *timer,
					       void *user_data)
{
	timer->user_data = user_data;
}

/**
 * @brief Retrieve the user-specific data from a timer.
 *
 * @param timer     Address of timer.
 *
 * @return The user data.
 */
__syscall void *k_timer_user_data_get(const struct k_timer *timer);

static inline void *z_impl_k_timer_user_data_get(const struct k_timer *timer)
{
	return timer->user_data;
}

/** @} */

/**
 * @addtogroup clock_apis
 * @{
 */

/**
 * @brief Get system uptime, in system ticks.
 *
 * This routine returns the elapsed time since the system booted, in
 * ticks (c.f. @option{CONFIG_SYS_CLOCK_TICKS_PER_SEC}), which is the
 * fundamental unit of resolution of kernel timekeeping.
 *
 * @return Current uptime in ticks.
 */
__syscall int64_t k_uptime_ticks(void);

/**
 * @brief Get system uptime.
 *
 * This routine returns the elapsed time since the system booted,
 * in milliseconds.
 *
 * @note
 *    While this function returns time in milliseconds, it does
 *    not mean it has millisecond resolution. The actual resolution depends on
 *    @option{CONFIG_SYS_CLOCK_TICKS_PER_SEC} config option.
 *
 * @return Current uptime in milliseconds.
 */
static inline int64_t k_uptime_get(void)
{
	return k_ticks_to_ms_floor64(k_uptime_ticks());
}

/**
 * @brief Get system uptime (32-bit version).
 *
 * This routine returns the lower 32 bits of the system uptime in
 * milliseconds.
 *
 * Because correct conversion requires full precision of the system
 * clock there is no benefit to using this over k_uptime_get() unless
 * you know the application will never run long enough for the system
 * clock to approach 2^32 ticks.  Calls to this function may involve
 * interrupt blocking and 64-bit math.
 *
 * @note
 *    While this function returns time in milliseconds, it does
 *    not mean it has millisecond resolution. The actual resolution depends on
 *    @option{CONFIG_SYS_CLOCK_TICKS_PER_SEC} config option
 *
 * @return The low 32 bits of the current uptime, in milliseconds.
 */
static inline uint32_t k_uptime_get_32(void)
{
	return (uint32_t)k_uptime_get();
}

/**
 * @brief Get elapsed time.
 *
 * This routine computes the elapsed time between the current system uptime
 * and an earlier reference time, in milliseconds.
 *
 * @param reftime Pointer to a reference time, which is updated to the current
 *                uptime upon return.
 *
 * @return Elapsed time.
 */
static inline int64_t k_uptime_delta(int64_t *reftime)
{
	int64_t uptime, delta;

	uptime = k_uptime_get();
	delta = uptime - *reftime;
	*reftime = uptime;

	return delta;
}

/**
 * @brief Read the hardware clock.
 *
 * This routine returns the current time, as measured by the system's hardware
 * clock.
 *
 * @return Current hardware clock up-counter (in cycles).
 */
static inline uint32_t k_cycle_get_32(void)
{
	return arch_k_cycle_get_32();
}

/**
 * @}
 */

/**
 * @cond INTERNAL_HIDDEN
 */

struct k_queue {
	sys_sflist_t data_q;
	struct k_spinlock lock;
	_wait_q_t wait_q;

	_POLL_EVENT;
	_OBJECT_TRACING_NEXT_PTR(k_queue)
	_OBJECT_TRACING_LINKED_FLAG
};

#define Z_QUEUE_INITIALIZER(obj) \
	{ \
	.data_q = SYS_SFLIST_STATIC_INIT(&obj.data_q), \
	.lock = { }, \
	.wait_q = Z_WAIT_Q_INIT(&obj.wait_q),	\
	_POLL_EVENT_OBJ_INIT(obj)		\
	_OBJECT_TRACING_INIT \
	}

extern void *z_queue_node_peek(sys_sfnode_t *node, bool needs_free);

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup queue_apis Queue APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @brief Initialize a queue.
 *
 * This routine initializes a queue object, prior to its first use.
 *
 * @param queue Address of the queue.
 *
 * @return N/A
 */
__syscall void k_queue_init(struct k_queue *queue);

/**
 * @brief Cancel waiting on a queue.
 *
 * This routine causes first thread pending on @a queue, if any, to
 * return from k_queue_get() call with NULL value (as if timeout expired).
 * If the queue is being waited on by k_poll(), it will return with
 * -EINTR and K_POLL_STATE_CANCELLED state (and per above, subsequent
 * k_queue_get() will return NULL).
 *
 * @note Can be called by ISRs.
 *
 * @param queue Address of the queue.
 *
 * @return N/A
 */
__syscall void k_queue_cancel_wait(struct k_queue *queue);

/**
 * @brief Append an element to the end of a queue.
 *
 * This routine appends a data item to @a queue. A queue data item must be
 * aligned on a word boundary, and the first word of the item is reserved
 * for the kernel's use.
 *
 * @note Can be called by ISRs.
 *
 * @param queue Address of the queue.
 * @param data Address of the data item.
 *
 * @return N/A
 */
extern void k_queue_append(struct k_queue *queue, void *data);

/**
 * @brief Append an element to a queue.
 *
 * This routine appends a data item to @a queue. There is an implicit memory
 * allocation to create an additional temporary bookkeeping data structure from
 * the calling thread's resource pool, which is automatically freed when the
 * item is removed. The data itself is not copied.
 *
 * @note Can be called by ISRs.
 *
 * @param queue Address of the queue.
 * @param data Address of the data item.
 *
 * @retval 0 on success
 * @retval -ENOMEM if there isn't sufficient RAM in the caller's resource pool
 */
__syscall int32_t k_queue_alloc_append(struct k_queue *queue, void *data);

/**
 * @brief Prepend an element to a queue.
 *
 * This routine prepends a data item to @a queue. A queue data item must be
 * aligned on a word boundary, and the first word of the item is reserved
 * for the kernel's use.
 *
 * @note Can be called by ISRs.
 *
 * @param queue Address of the queue.
 * @param data Address of the data item.
 *
 * @return N/A
 */
extern void k_queue_prepend(struct k_queue *queue, void *data);

/**
 * @brief Prepend an element to a queue.
 *
 * This routine prepends a data item to @a queue. There is an implicit memory
 * allocation to create an additional temporary bookkeeping data structure from
 * the calling thread's resource pool, which is automatically freed when the
 * item is removed. The data itself is not copied.
 *
 * @note Can be called by ISRs.
 *
 * @param queue Address of the queue.
 * @param data Address of the data item.
 *
 * @retval 0 on success
 * @retval -ENOMEM if there isn't sufficient RAM in the caller's resource pool
 */
__syscall int32_t k_queue_alloc_prepend(struct k_queue *queue, void *data);

/**
 * @brief Inserts an element to a queue.
 *
 * This routine inserts a data item to @a queue after previous item. A queue
 * data item must be aligned on a word boundary, and the first word of
 * the item is reserved for the kernel's use.
 *
 * @note Can be called by ISRs.
 *
 * @param queue Address of the queue.
 * @param prev Address of the previous data item.
 * @param data Address of the data item.
 *
 * @return N/A
 */
extern void k_queue_insert(struct k_queue *queue, void *prev, void *data);

/**
 * @brief Atomically append a list of elements to a queue.
 *
 * This routine adds a list of data items to @a queue in one operation.
 * The data items must be in a singly-linked list, with the first word
 * in each data item pointing to the next data item; the list must be
 * NULL-terminated.
 *
 * @note Can be called by ISRs.
 *
 * @param queue Address of the queue.
 * @param head Pointer to first node in singly-linked list.
 * @param tail Pointer to last node in singly-linked list.
 *
 * @retval 0 on success
 * @retval -EINVAL on invalid supplied data
 *
 */
extern int k_queue_append_list(struct k_queue *queue, void *head, void *tail);

/**
 * @brief Atomically add a list of elements to a queue.
 *
 * This routine adds a list of data items to @a queue in one operation.
 * The data items must be in a singly-linked list implemented using a
 * sys_slist_t object. Upon completion, the original list is empty.
 *
 * @note Can be called by ISRs.
 *
 * @param queue Address of the queue.
 * @param list Pointer to sys_slist_t object.
 *
 * @retval 0 on success
 * @retval -EINVAL on invalid data
 */
extern int k_queue_merge_slist(struct k_queue *queue, sys_slist_t *list);

/**
 * @brief Get an element from a queue.
 *
 * This routine removes first data item from @a queue. The first word of the
 * data item is reserved for the kernel's use.
 *
 * @note Can be called by ISRs, but @a timeout must be set to K_NO_WAIT.
 *
 * @param queue Address of the queue.
 * @param timeout Non-negative waiting period to obtain a data item
 *                or one of the special values K_NO_WAIT and
 *                K_FOREVER.
 *
 * @return Address of the data item if successful; NULL if returned
 * without waiting, or waiting period timed out.
 */
__syscall void *k_queue_get(struct k_queue *queue, k_timeout_t timeout);

/**
 * @brief Remove an element from a queue.
 *
 * This routine removes data item from @a queue. The first word of the
 * data item is reserved for the kernel's use. Removing elements from k_queue
 * rely on sys_slist_find_and_remove which is not a constant time operation.
 *
 * @note Can be called by ISRs
 *
 * @param queue Address of the queue.
 * @param data Address of the data item.
 *
 * @return true if data item was removed
 */
static inline bool k_queue_remove(struct k_queue *queue, void *data)
{
	return sys_sflist_find_and_remove(&queue->data_q, (sys_sfnode_t *)data);
}

/**
 * @brief Append an element to a queue only if it's not present already.
 *
 * This routine appends data item to @a queue. The first word of the data
 * item is reserved for the kernel's use. Appending elements to k_queue
 * relies on sys_slist_is_node_in_list which is not a constant time operation.
 *
 * @note Can be called by ISRs
 *
 * @param queue Address of the queue.
 * @param data Address of the data item.
 *
 * @return true if data item was added, false if not
 */
static inline bool k_queue_unique_append(struct k_queue *queue, void *data)
{
	sys_sfnode_t *test;

	SYS_SFLIST_FOR_EACH_NODE(&queue->data_q, test) {
		if (test == (sys_sfnode_t *) data) {
			return false;
		}
	}

	k_queue_append(queue, data);
	return true;
}

/**
 * @brief Query a queue to see if it has data available.
 *
 * Note that the data might be already gone by the time this function returns
 * if other threads are also trying to read from the queue.
 *
 * @note Can be called by ISRs.
 *
 * @param queue Address of the queue.
 *
 * @return Non-zero if the queue is empty.
 * @return 0 if data is available.
 */
__syscall int k_queue_is_empty(struct k_queue *queue);

static inline int z_impl_k_queue_is_empty(struct k_queue *queue)
{
	return (int)sys_sflist_is_empty(&queue->data_q);
}

/**
 * @brief Peek element at the head of queue.
 *
 * Return element from the head of queue without removing it.
 *
 * @param queue Address of the queue.
 *
 * @return Head element, or NULL if queue is empty.
 */
__syscall void *k_queue_peek_head(struct k_queue *queue);

static inline void *z_impl_k_queue_peek_head(struct k_queue *queue)
{
	return z_queue_node_peek(sys_sflist_peek_head(&queue->data_q), false);
}

/**
 * @brief Peek element at the tail of queue.
 *
 * Return element from the tail of queue without removing it.
 *
 * @param queue Address of the queue.
 *
 * @return Tail element, or NULL if queue is empty.
 */
__syscall void *k_queue_peek_tail(struct k_queue *queue);

static inline void *z_impl_k_queue_peek_tail(struct k_queue *queue)
{
	return z_queue_node_peek(sys_sflist_peek_tail(&queue->data_q), false);
}

/**
 * @brief Statically define and initialize a queue.
 *
 * The queue can be accessed outside the module where it is defined using:
 *
 * @code extern struct k_queue <name>; @endcode
 *
 * @param name Name of the queue.
 */
#define K_QUEUE_DEFINE(name) \
	Z_STRUCT_SECTION_ITERABLE(k_queue, name) = \
		Z_QUEUE_INITIALIZER(name)

/** @} */

#ifdef CONFIG_USERSPACE
/**
 * @brief futex structure
 *
 * A k_futex is a lightweight mutual exclusion primitive designed
 * to minimize kernel involvement. Uncontended operation relies
 * only on atomic access to shared memory. k_futex are tracked as
 * kernel objects and can live in user memory so any access bypass
 * the kernel object permission management mechanism.
 */
struct k_futex {
	atomic_t val;
};

/**
 * @brief futex kernel data structure
 *
 * z_futex_data are the helper data structure for k_futex to complete
 * futex contended operation on kernel side, structure z_futex_data
 * of every futex object is invisible in user mode.
 */
struct z_futex_data {
	_wait_q_t wait_q;
	struct k_spinlock lock;
};

#define Z_FUTEX_DATA_INITIALIZER(obj) \
	{ \
	.wait_q = Z_WAIT_Q_INIT(&obj.wait_q) \
	}

/**
 * @defgroup futex_apis FUTEX APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @brief Pend the current thread on a futex
 *
 * Tests that the supplied futex contains the expected value, and if so,
 * goes to sleep until some other thread calls k_futex_wake() on it.
 *
 * @param futex Address of the futex.
 * @param expected Expected value of the futex, if it is different the caller
 *		   will not wait on it.
 * @param timeout Non-negative waiting period on the futex, or
 *		  one of the special values K_NO_WAIT or K_FOREVER.
 * @retval -EACCES Caller does not have read access to futex address.
 * @retval -EAGAIN If the futex value did not match the expected parameter.
 * @retval -EINVAL Futex parameter address not recognized by the kernel.
 * @retval -ETIMEDOUT Thread woke up due to timeout and not a futex wakeup.
 * @retval 0 if the caller went to sleep and was woken up. The caller
 *	     should check the futex's value on wakeup to determine if it needs
 *	     to block again.
 */
__syscall int k_futex_wait(struct k_futex *futex, int expected,
			   k_timeout_t timeout);

/**
 * @brief Wake one/all threads pending on a futex
 *
 * Wake up the highest priority thread pending on the supplied futex, or
 * wakeup all the threads pending on the supplied futex, and the behavior
 * depends on wake_all.
 *
 * @param futex Futex to wake up pending threads.
 * @param wake_all If true, wake up all pending threads; If false,
 *                 wakeup the highest priority thread.
 * @retval -EACCES Caller does not have access to the futex address.
 * @retval -EINVAL Futex parameter address not recognized by the kernel.
 * @retval Number of threads that were woken up.
 */
__syscall int k_futex_wake(struct k_futex *futex, bool wake_all);

/** @} */
#endif

struct k_fifo {
	struct k_queue _queue;
};

/**
 * @cond INTERNAL_HIDDEN
 */
#define Z_FIFO_INITIALIZER(obj) \
	{ \
	._queue = Z_QUEUE_INITIALIZER(obj._queue) \
	}

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup fifo_apis FIFO APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @brief Initialize a FIFO queue.
 *
 * This routine initializes a FIFO queue, prior to its first use.
 *
 * @param fifo Address of the FIFO queue.
 *
 * @return N/A
 */
#define k_fifo_init(fifo) \
	k_queue_init(&(fifo)->_queue)

/**
 * @brief Cancel waiting on a FIFO queue.
 *
 * This routine causes first thread pending on @a fifo, if any, to
 * return from k_fifo_get() call with NULL value (as if timeout
 * expired).
 *
 * @note Can be called by ISRs.
 *
 * @param fifo Address of the FIFO queue.
 *
 * @return N/A
 */
#define k_fifo_cancel_wait(fifo) \
	k_queue_cancel_wait(&(fifo)->_queue)

/**
 * @brief Add an element to a FIFO queue.
 *
 * This routine adds a data item to @a fifo. A FIFO data item must be
 * aligned on a word boundary, and the first word of the item is reserved
 * for the kernel's use.
 *
 * @note Can be called by ISRs.
 *
 * @param fifo Address of the FIFO.
 * @param data Address of the data item.
 *
 * @return N/A
 */
#define k_fifo_put(fifo, data) \
	k_queue_append(&(fifo)->_queue, data)

/**
 * @brief Add an element to a FIFO queue.
 *
 * This routine adds a data item to @a fifo. There is an implicit memory
 * allocation to create an additional temporary bookkeeping data structure from
 * the calling thread's resource pool, which is automatically freed when the
 * item is removed. The data itself is not copied.
 *
 * @note Can be called by ISRs.
 *
 * @param fifo Address of the FIFO.
 * @param data Address of the data item.
 *
 * @retval 0 on success
 * @retval -ENOMEM if there isn't sufficient RAM in the caller's resource pool
 */
#define k_fifo_alloc_put(fifo, data) \
	k_queue_alloc_append(&(fifo)->_queue, data)

/**
 * @brief Atomically add a list of elements to a FIFO.
 *
 * This routine adds a list of data items to @a fifo in one operation.
 * The data items must be in a singly-linked list, with the first word of
 * each data item pointing to the next data item; the list must be
 * NULL-terminated.
 *
 * @note Can be called by ISRs.
 *
 * @param fifo Address of the FIFO queue.
 * @param head Pointer to first node in singly-linked list.
 * @param tail Pointer to last node in singly-linked list.
 *
 * @return N/A
 */
#define k_fifo_put_list(fifo, head, tail) \
	k_queue_append_list(&(fifo)->_queue, head, tail)

/**
 * @brief Atomically add a list of elements to a FIFO queue.
 *
 * This routine adds a list of data items to @a fifo in one operation.
 * The data items must be in a singly-linked list implemented using a
 * sys_slist_t object. Upon completion, the sys_slist_t object is invalid
 * and must be re-initialized via sys_slist_init().
 *
 * @note Can be called by ISRs.
 *
 * @param fifo Address of the FIFO queue.
 * @param list Pointer to sys_slist_t object.
 *
 * @return N/A
 */
#define k_fifo_put_slist(fifo, list) \
	k_queue_merge_slist(&(fifo)->_queue, list)

/**
 * @brief Get an element from a FIFO queue.
 *
 * This routine removes a data item from @a fifo in a "first in, first out"
 * manner. The first word of the data item is reserved for the kernel's use.
 *
 * @note Can be called by ISRs, but @a timeout must be set to K_NO_WAIT.
 *
 * @param fifo Address of the FIFO queue.
 * @param timeout Waiting period to obtain a data item,
 *                or one of the special values K_NO_WAIT and K_FOREVER.
 *
 * @return Address of the data item if successful; NULL if returned
 * without waiting, or waiting period timed out.
 */
#define k_fifo_get(fifo, timeout) \
	k_queue_get(&(fifo)->_queue, timeout)

/**
 * @brief Query a FIFO queue to see if it has data available.
 *
 * Note that the data might be already gone by the time this function returns
 * if other threads is also trying to read from the FIFO.
 *
 * @note Can be called by ISRs.
 *
 * @param fifo Address of the FIFO queue.
 *
 * @return Non-zero if the FIFO queue is empty.
 * @return 0 if data is available.
 */
#define k_fifo_is_empty(fifo) \
	k_queue_is_empty(&(fifo)->_queue)

/**
 * @brief Peek element at the head of a FIFO queue.
 *
 * Return element from the head of FIFO queue without removing it. A usecase
 * for this is if elements of the FIFO object are themselves containers. Then
 * on each iteration of processing, a head container will be peeked,
 * and some data processed out of it, and only if the container is empty,
 * it will be completely remove from the FIFO queue.
 *
 * @param fifo Address of the FIFO queue.
 *
 * @return Head element, or NULL if the FIFO queue is empty.
 */
#define k_fifo_peek_head(fifo) \
	k_queue_peek_head(&(fifo)->_queue)

/**
 * @brief Peek element at the tail of FIFO queue.
 *
 * Return element from the tail of FIFO queue (without removing it). A usecase
 * for this is if elements of the FIFO queue are themselves containers. Then
 * it may be useful to add more data to the last container in a FIFO queue.
 *
 * @param fifo Address of the FIFO queue.
 *
 * @return Tail element, or NULL if a FIFO queue is empty.
 */
#define k_fifo_peek_tail(fifo) \
	k_queue_peek_tail(&(fifo)->_queue)

/**
 * @brief Statically define and initialize a FIFO queue.
 *
 * The FIFO queue can be accessed outside the module where it is defined using:
 *
 * @code extern struct k_fifo <name>; @endcode
 *
 * @param name Name of the FIFO queue.
 */
#define K_FIFO_DEFINE(name) \
	Z_STRUCT_SECTION_ITERABLE_ALTERNATE(k_queue, k_fifo, name) = \
		Z_FIFO_INITIALIZER(name)

/** @} */

struct k_lifo {
	struct k_queue _queue;
};

/**
 * @cond INTERNAL_HIDDEN
 */

#define Z_LIFO_INITIALIZER(obj) \
	{ \
	._queue = Z_QUEUE_INITIALIZER(obj._queue) \
	}

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup lifo_apis LIFO APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @brief Initialize a LIFO queue.
 *
 * This routine initializes a LIFO queue object, prior to its first use.
 *
 * @param lifo Address of the LIFO queue.
 *
 * @return N/A
 */
#define k_lifo_init(lifo) \
	k_queue_init(&(lifo)->_queue)

/**
 * @brief Add an element to a LIFO queue.
 *
 * This routine adds a data item to @a lifo. A LIFO queue data item must be
 * aligned on a word boundary, and the first word of the item is
 * reserved for the kernel's use.
 *
 * @note Can be called by ISRs.
 *
 * @param lifo Address of the LIFO queue.
 * @param data Address of the data item.
 *
 * @return N/A
 */
#define k_lifo_put(lifo, data) \
	k_queue_prepend(&(lifo)->_queue, data)

/**
 * @brief Add an element to a LIFO queue.
 *
 * This routine adds a data item to @a lifo. There is an implicit memory
 * allocation to create an additional temporary bookkeeping data structure from
 * the calling thread's resource pool, which is automatically freed when the
 * item is removed. The data itself is not copied.
 *
 * @note Can be called by ISRs.
 *
 * @param lifo Address of the LIFO.
 * @param data Address of the data item.
 *
 * @retval 0 on success
 * @retval -ENOMEM if there isn't sufficient RAM in the caller's resource pool
 */
#define k_lifo_alloc_put(lifo, data) \
	k_queue_alloc_prepend(&(lifo)->_queue, data)

/**
 * @brief Get an element from a LIFO queue.
 *
 * This routine removes a data item from @a LIFO in a "last in, first out"
 * manner. The first word of the data item is reserved for the kernel's use.
 *
 * @note Can be called by ISRs, but @a timeout must be set to K_NO_WAIT.
 *
 * @param lifo Address of the LIFO queue.
 * @param timeout Waiting period to obtain a data item,
 *                or one of the special values K_NO_WAIT and K_FOREVER.
 *
 * @return Address of the data item if successful; NULL if returned
 * without waiting, or waiting period timed out.
 */
#define k_lifo_get(lifo, timeout) \
	k_queue_get(&(lifo)->_queue, timeout)

/**
 * @brief Statically define and initialize a LIFO queue.
 *
 * The LIFO queue can be accessed outside the module where it is defined using:
 *
 * @code extern struct k_lifo <name>; @endcode
 *
 * @param name Name of the fifo.
 */
#define K_LIFO_DEFINE(name) \
	Z_STRUCT_SECTION_ITERABLE_ALTERNATE(k_queue, k_lifo, name) = \
		Z_LIFO_INITIALIZER(name)

/** @} */

/**
 * @cond INTERNAL_HIDDEN
 */
#define K_STACK_FLAG_ALLOC	((uint8_t)1)	/* Buffer was allocated */

typedef uintptr_t stack_data_t;

struct k_stack {
	_wait_q_t wait_q;
	struct k_spinlock lock;
	stack_data_t *base, *next, *top;

	_OBJECT_TRACING_NEXT_PTR(k_stack)
	_OBJECT_TRACING_LINKED_FLAG
	uint8_t flags;
};

#define Z_STACK_INITIALIZER(obj, stack_buffer, stack_num_entries) \
	{ \
	.wait_q = Z_WAIT_Q_INIT(&obj.wait_q),	\
	.base = stack_buffer, \
	.next = stack_buffer, \
	.top = stack_buffer + stack_num_entries, \
	_OBJECT_TRACING_INIT \
	}

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup stack_apis Stack APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @brief Initialize a stack.
 *
 * This routine initializes a stack object, prior to its first use.
 *
 * @param stack Address of the stack.
 * @param buffer Address of array used to hold stacked values.
 * @param num_entries Maximum number of values that can be stacked.
 *
 * @return N/A
 */
void k_stack_init(struct k_stack *stack,
		  stack_data_t *buffer, uint32_t num_entries);


/**
 * @brief Initialize a stack.
 *
 * This routine initializes a stack object, prior to its first use. Internal
 * buffers will be allocated from the calling thread's resource pool.
 * This memory will be released if k_stack_cleanup() is called, or
 * userspace is enabled and the stack object loses all references to it.
 *
 * @param stack Address of the stack.
 * @param num_entries Maximum number of values that can be stacked.
 *
 * @return -ENOMEM if memory couldn't be allocated
 */

__syscall int32_t k_stack_alloc_init(struct k_stack *stack,
				   uint32_t num_entries);

/**
 * @brief Release a stack's allocated buffer
 *
 * If a stack object was given a dynamically allocated buffer via
 * k_stack_alloc_init(), this will free it. This function does nothing
 * if the buffer wasn't dynamically allocated.
 *
 * @param stack Address of the stack.
 * @retval 0 on success
 * @retval -EAGAIN when object is still in use
 */
int k_stack_cleanup(struct k_stack *stack);

/**
 * @brief Push an element onto a stack.
 *
 * This routine adds a stack_data_t value @a data to @a stack.
 *
 * @note Can be called by ISRs.
 *
 * @param stack Address of the stack.
 * @param data Value to push onto the stack.
 *
 * @retval 0 on success
 * @retval -ENOMEM if stack is full
 */
__syscall int k_stack_push(struct k_stack *stack, stack_data_t data);

/**
 * @brief Pop an element from a stack.
 *
 * This routine removes a stack_data_t value from @a stack in a "last in,
 * first out" manner and stores the value in @a data.
 *
 * @note Can be called by ISRs, but @a timeout must be set to K_NO_WAIT.
 *
 * @param stack Address of the stack.
 * @param data Address of area to hold the value popped from the stack.
 * @param timeout Waiting period to obtain a value,
 *                or one of the special values K_NO_WAIT and
 *                K_FOREVER.
 *
 * @retval 0 Element popped from stack.
 * @retval -EBUSY Returned without waiting.
 * @retval -EAGAIN Waiting period timed out.
 */
__syscall int k_stack_pop(struct k_stack *stack, stack_data_t *data,
			  k_timeout_t timeout);

/**
 * @brief Statically define and initialize a stack
 *
 * The stack can be accessed outside the module where it is defined using:
 *
 * @code extern struct k_stack <name>; @endcode
 *
 * @param name Name of the stack.
 * @param stack_num_entries Maximum number of values that can be stacked.
 */
#define K_STACK_DEFINE(name, stack_num_entries)                \
	stack_data_t __noinit                                  \
		_k_stack_buf_##name[stack_num_entries];        \
	Z_STRUCT_SECTION_ITERABLE(k_stack, name) = \
		Z_STACK_INITIALIZER(name, _k_stack_buf_##name, \
				    stack_num_entries)

/** @} */

struct k_work;

/**
 * @addtogroup thread_apis
 * @{
 */

/**
 * @typedef k_work_handler_t
 * @brief Work item handler function type.
 *
 * A work item's handler function is executed by a workqueue's thread
 * when the work item is processed by the workqueue.
 *
 * @param work Address of the work item.
 *
 * @return N/A
 */
typedef void (*k_work_handler_t)(struct k_work *work);

/**
 * @cond INTERNAL_HIDDEN
 */

struct k_work_q {
	struct k_queue queue;
	struct k_thread thread;
};

enum {
	K_WORK_STATE_PENDING,	/* Work item pending state */
};

struct k_work {
	void *_reserved;		/* Used by k_queue implementation. */
	k_work_handler_t handler;
	atomic_t flags[1];
};

struct k_delayed_work {
	struct k_work work;
	struct _timeout timeout;
	struct k_work_q *work_q;
};

struct k_work_poll {
	struct k_work work;
	struct k_work_q *workq;
	struct z_poller poller;
	struct k_poll_event *events;
	int num_events;
	k_work_handler_t real_handler;
	struct _timeout timeout;
	int poll_result;
};

extern struct k_work_q k_sys_work_q;

/**
 * INTERNAL_HIDDEN @endcond
 */

#define Z_WORK_INITIALIZER(work_handler) \
	{ \
	._reserved = NULL, \
	.handler = work_handler, \
	.flags = { 0 } \
	}

/**
 * @brief Initialize a statically-defined work item.
 *
 * This macro can be used to initialize a statically-defined workqueue work
 * item, prior to its first use. For example,
 *
 * @code static K_WORK_DEFINE(<work>, <work_handler>); @endcode
 *
 * @param work Symbol name for work item object
 * @param work_handler Function to invoke each time work item is processed.
 */
#define K_WORK_DEFINE(work, work_handler) \
	struct k_work work = Z_WORK_INITIALIZER(work_handler)

/**
 * @brief Initialize a work item.
 *
 * This routine initializes a workqueue work item, prior to its first use.
 *
 * @param work Address of work item.
 * @param handler Function to invoke each time work item is processed.
 *
 * @return N/A
 */
static inline void k_work_init(struct k_work *work, k_work_handler_t handler)
{
	*work = (struct k_work)Z_WORK_INITIALIZER(handler);
}

/**
 * @brief Submit a work item.
 *
 * This routine submits work item @p work to be processed by workqueue @p
 * work_q. If the work item is already pending in @p work_q or any other
 * workqueue as a result of an earlier submission, this routine has no
 * effect on the work item. If the work item has already been processed, or
 * is currently being processed, its work is considered complete and the
 * work item can be resubmitted.
 *
 * @warning
 * A submitted work item must not be modified until it has been processed
 * by the workqueue.
 *
 * @note Can be called by ISRs.
 *
 * @param work_q Address of workqueue.
 * @param work Address of work item.
 *
 * @return N/A
 */
static inline void k_work_submit_to_queue(struct k_work_q *work_q,
					  struct k_work *work)
{
	if (!atomic_test_and_set_bit(work->flags, K_WORK_STATE_PENDING)) {
		k_queue_append(&work_q->queue, work);
	}
}

/**
 * @brief Submit a work item to a user mode workqueue
 *
 * Submits a work item to a workqueue that runs in user mode. A temporary
 * memory allocation is made from the caller's resource pool which is freed
 * once the worker thread consumes the k_work item. The workqueue
 * thread must have memory access to the k_work item being submitted. The caller
 * must have permission granted on the work_q parameter's queue object.
 *
 * Otherwise this works the same as k_work_submit_to_queue().
 *
 * @note Can be called by ISRs.
 *
 * @param work_q Address of workqueue.
 * @param work Address of work item.
 *
 * @retval -EBUSY if the work item was already in some workqueue
 * @retval -ENOMEM if no memory for thread resource pool allocation
 * @retval 0 Success
 */
static inline int k_work_submit_to_user_queue(struct k_work_q *work_q,
					      struct k_work *work)
{
	int ret = -EBUSY;

	if (!atomic_test_and_set_bit(work->flags, K_WORK_STATE_PENDING)) {
		ret = k_queue_alloc_append(&work_q->queue, work);

		/* Couldn't insert into the queue. Clear the pending bit
		 * so the work item can be submitted again
		 */
		if (ret != 0) {
			atomic_clear_bit(work->flags, K_WORK_STATE_PENDING);
		}
	}

	return ret;
}

/**
 * @brief Check if a work item is pending.
 *
 * This routine indicates if work item @a work is pending in a workqueue's
 * queue.
 *
 * @note Checking if the work is pending gives no guarantee that the
 *       work will still be pending when this information is used. It is up to
 *       the caller to make sure that this information is used in a safe manner.
 *
 * @note Can be called by ISRs.
 *
 * @param work Address of work item.
 *
 * @return true if work item is pending, or false if it is not pending.
 */
static inline bool k_work_pending(struct k_work *work)
{
	return atomic_test_bit(work->flags, K_WORK_STATE_PENDING);
}

/**
 * @brief  Check if a delayed work item is pending.
 *
 * This routine indicates if the work item @a work is pending in a workqueue's
 * queue or waiting for the delay timeout.
 *
 * @note Checking if the delayed work is pending gives no guarantee that the
 *       work will still be pending when this information is used. It is up to
 *       the caller to make sure that this information is used in a safe manner.
 *
 * @note Can be called by ISRs.
 *
 * @param work Address of delayed work item.
 *
 * @return true if work item is waiting for the delay to expire or pending on a
 *         work queue, or false if it is not pending.
 */
bool k_delayed_work_pending(struct k_delayed_work *work);

/**
 * @brief Start a workqueue.
 *
 * This routine starts workqueue @a work_q. The workqueue spawns its work
 * processing thread, which runs forever.
 *
 * @param work_q Address of workqueue.
 * @param stack Pointer to work queue thread's stack space, as defined by
 *		K_THREAD_STACK_DEFINE()
 * @param stack_size Size of the work queue thread's stack (in bytes), which
 *		should either be the same constant passed to
 *		K_THREAD_STACK_DEFINE() or the value of K_THREAD_STACK_SIZEOF().
 * @param prio Priority of the work queue's thread.
 *
 * @return N/A
 */
extern void k_work_q_start(struct k_work_q *work_q,
			   k_thread_stack_t *stack,
			   size_t stack_size, int prio);

/**
 * @brief Start a workqueue in user mode
 *
 * This works identically to k_work_q_start() except it is callable from user
 * mode, and the worker thread created will run in user mode.
 * The caller must have permissions granted on both the work_q parameter's
 * thread and queue objects, and the same restrictions on priority apply as
 * k_thread_create().
 *
 * @param work_q Address of workqueue.
 * @param stack Pointer to work queue thread's stack space, as defined by
 *		K_THREAD_STACK_DEFINE()
 * @param stack_size Size of the work queue thread's stack (in bytes), which
 *		should either be the same constant passed to
 *		K_THREAD_STACK_DEFINE() or the value of K_THREAD_STACK_SIZEOF().
 * @param prio Priority of the work queue's thread.
 *
 * @return N/A
 */
extern void k_work_q_user_start(struct k_work_q *work_q,
				k_thread_stack_t *stack,
				size_t stack_size, int prio);

/**
 * @brief Initialize a delayed work item.
 *
 * This routine initializes a workqueue delayed work item, prior to
 * its first use.
 *
 * @param work Address of delayed work item.
 * @param handler Function to invoke each time work item is processed.
 *
 * @return N/A
 */
extern void k_delayed_work_init(struct k_delayed_work *work,
				k_work_handler_t handler);

/**
 * @brief Submit a delayed work item.
 *
 * This routine schedules work item @a work to be processed by workqueue
 * @a work_q after a delay of @a delay milliseconds. The routine initiates
 * an asynchronous countdown for the work item and then returns to the caller.
 * Only when the countdown completes is the work item actually submitted to
 * the workqueue and becomes pending.
 *
 * Submitting a previously submitted delayed work item that is still counting
 * down or is pending cancels the existing submission and restarts the
 * countdown using the new delay.  Note that this behavior is inherently
 * subject to race conditions with the pre-existing timeouts and work queue,
 * so care must be taken to synchronize such resubmissions externally.
 *
 * Attempts to submit a work item to a queue after it has been submitted to a
 * different queue will fail with @c -EALREADY until k_delayed_work_cancel()
 * is successfully invoked on the work item to clear its internal state.
 *
 * @warning
 * A delayed work item must not be modified until it has been processed
 * by the workqueue.
 *
 * @note Can be called by ISRs.
 *
 * @param work_q Address of workqueue.
 * @param work Address of delayed work item.
 * @param delay Delay before submitting the work item
 *
 * @retval 0 Work item countdown started.
 * @retval -EINVAL
 *    * if a previously submitted work item had to be cancelled and the
 *      cancellation failed; or
 *    * Work item is being processed or has completed its work.
 * @retval -EADDRINUSE Work item was submitted to a different workqueue.
 */
extern int k_delayed_work_submit_to_queue(struct k_work_q *work_q,
					  struct k_delayed_work *work,
					  k_timeout_t delay);

/**
 * @brief Cancel a delayed work item.
 *
 * This routine cancels the submission of delayed work item @a work.  Whether
 * the work item can be successfully cancelled depends on its state.
 *
 * @note Can be called by ISRs.
 *
 * @note When @c -EALREADY is returned the caller cannot distinguish whether
 * the work item handler is still being invoked by the work queue thread or
 * has completed.
 *
 * @param work Address of delayed work item.
 *
 * @retval 0
 *   * Work item countdown cancelled before the item was submitted to its
 *     queue; or
 *   * Work item was removed from its queue before it was processed.
 * @retval -EINVAL
 *   * Work item has never been submitted; or
 *   * Work item has been successfully cancelled; or
 *   * Timeout handler is in the process of submitting the work item to its
 *     queue; or
 *   * Work queue thread has removed the work item from the queue but has not
 *     called its handler.
 * @retval -EALREADY
 *   * Work queue thread has removed the work item from the queue and cleared
 *     its pending flag; or
 *   * Work queue thread is invoking the item handler; or
 *   * Work item handler has completed.
 */
extern int k_delayed_work_cancel(struct k_delayed_work *work);

/**
 * @brief Submit a work item to the system workqueue.
 *
 * This routine submits work item @a work to be processed by the system
 * workqueue. If the work item is already pending in the system workqueue or
 * any other workqueue as a result of an earlier submission, this routine
 * has no effect on the work item. If the work item has already been
 * processed, or is currently being processed, its work is considered
 * complete and the work item can be resubmitted.
 *
 * @warning
 * Work items submitted to the system workqueue should avoid using handlers
 * that block or yield since this may prevent the system workqueue from
 * processing other work items in a timely manner.
 *
 * @note Can be called by ISRs.
 *
 * @param work Address of work item.
 *
 * @return N/A
 */
static inline void k_work_submit(struct k_work *work)
{
	k_work_submit_to_queue(&k_sys_work_q, work);
}

/**
 * @brief Submit a delayed work item to the system workqueue.
 *
 * This routine schedules work item @a work to be processed by the system
 * workqueue after a delay of @a delay milliseconds. The routine initiates
 * an asynchronous countdown for the work item and then returns to the caller.
 * Only when the countdown completes is the work item actually submitted to
 * the workqueue and becomes pending.
 *
 * Submitting a previously submitted delayed work item that is still
 * counting down cancels the existing submission and restarts the countdown
 * using the new delay. If the work item is currently pending on the
 * workqueue's queue because the countdown has completed it is too late to
 * resubmit the item, and resubmission fails without impacting the work item.
 * If the work item has already been processed, or is currently being processed,
 * its work is considered complete and the work item can be resubmitted.
 *
 * Attempts to submit a work item to a queue after it has been submitted to a
 * different queue will fail with @c -EALREADY until k_delayed_work_cancel()
 * is invoked on the work item to clear its internal state.
 *
 * @warning
 * Work items submitted to the system workqueue should avoid using handlers
 * that block or yield since this may prevent the system workqueue from
 * processing other work items in a timely manner.
 *
 * @note Can be called by ISRs.
 *
 * @param work Address of delayed work item.
 * @param delay Delay before submitting the work item
 *
 * @retval 0 Work item countdown started.
 * @retval -EINVAL Work item is being processed or has completed its work.
 * @retval -EADDRINUSE Work item was submitted to a different workqueue.
 */
static inline int k_delayed_work_submit(struct k_delayed_work *work,
					k_timeout_t delay)
{
	return k_delayed_work_submit_to_queue(&k_sys_work_q, work, delay);
}

/**
 * @brief Get time when a delayed work will be scheduled
 *
 * This routine computes the system uptime when a delayed work gets
 * executed. If the delayed work is not waiting to be scheduled, it
 * returns current system time.
 *
 * @param work     Delayed work item.
 *
 * @return Uptime of execution (in ticks).
 */
static inline k_ticks_t k_delayed_work_expires_ticks(
				       struct k_delayed_work *work)
{
	return z_timeout_expires(&work->timeout);
}

/**
 * @brief Get time remaining before a delayed work gets scheduled, in
 * system ticks
 *
 * This routine computes the time remaining before a delayed work gets
 * executed. If the delayed work is not waiting to be scheduled, it
 * returns zero.
 *
 * @param work     Delayed work item.
 *
 * @return Remaining time (in ticks).
 */
static inline k_ticks_t k_delayed_work_remaining_ticks(
				       struct k_delayed_work *work)
{
	return z_timeout_remaining(&work->timeout);
}

/**
 * @brief Get time remaining before a delayed work gets scheduled.
 *
 * This routine computes the (approximate) time remaining before a
 * delayed work gets executed. If the delayed work is not waiting to be
 * scheduled, it returns zero.
 *
 * @param work     Delayed work item.
 *
 * @return Remaining time (in milliseconds).
 */
static inline int32_t k_delayed_work_remaining_get(struct k_delayed_work *work)
{
	return k_ticks_to_ms_floor32(z_timeout_remaining(&work->timeout));
}

/**
 * @brief Initialize a triggered work item.
 *
 * This routine initializes a workqueue triggered work item, prior to
 * its first use.
 *
 * @param work Address of triggered work item.
 * @param handler Function to invoke each time work item is processed.
 *
 * @return N/A
 */
extern void k_work_poll_init(struct k_work_poll *work,
			     k_work_handler_t handler);

/**
 * @brief Submit a triggered work item.
 *
 * This routine schedules work item @a work to be processed by workqueue
 * @a work_q when one of the given @a events is signaled. The routine
 * initiates internal poller for the work item and then returns to the caller.
 * Only when one of the watched events happen the work item is actually
 * submitted to the workqueue and becomes pending.
 *
 * Submitting a previously submitted triggered work item that is still
 * waiting for the event cancels the existing submission and reschedules it
 * the using the new event list. Note that this behavior is inherently subject
 * to race conditions with the pre-existing triggered work item and work queue,
 * so care must be taken to synchronize such resubmissions externally.
 *
 * @note Can be called by ISRs.
 *
 * @warning
 * Provided array of events as well as a triggered work item must be placed
 * in persistent memory (valid until work handler execution or work
 * cancellation) and cannot be modified after submission.
 *
 * @param work_q Address of workqueue.
 * @param work Address of delayed work item.
 * @param events An array of events which trigger the work.
 * @param num_events The number of events in the array.
 * @param timeout Timeout after which the work will be scheduled
 *		  for execution even if not triggered.
 *
 *
 * @retval 0 Work item started watching for events.
 * @retval -EINVAL Work item is being processed or has completed its work.
 * @retval -EADDRINUSE Work item is pending on a different workqueue.
 */
extern int k_work_poll_submit_to_queue(struct k_work_q *work_q,
				       struct k_work_poll *work,
				       struct k_poll_event *events,
				       int num_events,
				       k_timeout_t timeout);

/**
 * @brief Submit a triggered work item to the system workqueue.
 *
 * This routine schedules work item @a work to be processed by system
 * workqueue when one of the given @a events is signaled. The routine
 * initiates internal poller for the work item and then returns to the caller.
 * Only when one of the watched events happen the work item is actually
 * submitted to the workqueue and becomes pending.
 *
 * Submitting a previously submitted triggered work item that is still
 * waiting for the event cancels the existing submission and reschedules it
 * the using the new event list. Note that this behavior is inherently subject
 * to race conditions with the pre-existing triggered work item and work queue,
 * so care must be taken to synchronize such resubmissions externally.
 *
 * @note Can be called by ISRs.
 *
 * @warning
 * Provided array of events as well as a triggered work item must not be
 * modified until the item has been processed by the workqueue.
 *
 * @param work Address of delayed work item.
 * @param events An array of events which trigger the work.
 * @param num_events The number of events in the array.
 * @param timeout Timeout after which the work will be scheduled
 *		  for execution even if not triggered.
 *
 * @retval 0 Work item started watching for events.
 * @retval -EINVAL Work item is being processed or has completed its work.
 * @retval -EADDRINUSE Work item is pending on a different workqueue.
 */
static inline int k_work_poll_submit(struct k_work_poll *work,
				     struct k_poll_event *events,
				     int num_events,
				     k_timeout_t timeout)
{
	return k_work_poll_submit_to_queue(&k_sys_work_q, work,
						events, num_events, timeout);
}

/**
 * @brief Cancel a triggered work item.
 *
 * This routine cancels the submission of triggered work item @a work.
 * A triggered work item can only be canceled if no event triggered work
 * submission.
 *
 * @note Can be called by ISRs.
 *
 * @param work Address of delayed work item.
 *
 * @retval 0 Work item canceled.
 * @retval -EINVAL Work item is being processed or has completed its work.
 */
extern int k_work_poll_cancel(struct k_work_poll *work);

/** @} */
/**
 * @defgroup mutex_apis Mutex APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * Mutex Structure
 * @ingroup mutex_apis
 */
struct k_mutex {
	/** Mutex wait queue */
	_wait_q_t wait_q;
	/** Mutex owner */
	struct k_thread *owner;

	/** Current lock count */
	uint32_t lock_count;

	/** Original thread priority */
	int owner_orig_prio;

	_OBJECT_TRACING_NEXT_PTR(k_mutex)
	_OBJECT_TRACING_LINKED_FLAG
};

/**
 * @cond INTERNAL_HIDDEN
 */
#define Z_MUTEX_INITIALIZER(obj) \
	{ \
	.wait_q = Z_WAIT_Q_INIT(&obj.wait_q), \
	.owner = NULL, \
	.lock_count = 0, \
	.owner_orig_prio = K_LOWEST_THREAD_PRIO, \
	_OBJECT_TRACING_INIT \
	}

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @brief Statically define and initialize a mutex.
 *
 * The mutex can be accessed outside the module where it is defined using:
 *
 * @code extern struct k_mutex <name>; @endcode
 *
 * @param name Name of the mutex.
 */
#define K_MUTEX_DEFINE(name) \
	Z_STRUCT_SECTION_ITERABLE(k_mutex, name) = \
		Z_MUTEX_INITIALIZER(name)

/**
 * @brief Initialize a mutex.
 *
 * This routine initializes a mutex object, prior to its first use.
 *
 * Upon completion, the mutex is available and does not have an owner.
 *
 * @param mutex Address of the mutex.
 *
 * @retval 0 Mutex object created
 *
 */
__syscall int k_mutex_init(struct k_mutex *mutex);


/**
 * @brief Lock a mutex.
 *
 * This routine locks @a mutex. If the mutex is locked by another thread,
 * the calling thread waits until the mutex becomes available or until
 * a timeout occurs.
 *
 * A thread is permitted to lock a mutex it has already locked. The operation
 * completes immediately and the lock count is increased by 1.
 *
 * Mutexes may not be locked in ISRs.
 *
 * @param mutex Address of the mutex.
 * @param timeout Waiting period to lock the mutex,
 *                or one of the special values K_NO_WAIT and
 *                K_FOREVER.
 *
 * @retval 0 Mutex locked.
 * @retval -EBUSY Returned without waiting.
 * @retval -EAGAIN Waiting period timed out.
 */
__syscall int k_mutex_lock(struct k_mutex *mutex, k_timeout_t timeout);

/**
 * @brief Unlock a mutex.
 *
 * This routine unlocks @a mutex. The mutex must already be locked by the
 * calling thread.
 *
 * The mutex cannot be claimed by another thread until it has been unlocked by
 * the calling thread as many times as it was previously locked by that
 * thread.
 *
 * Mutexes may not be unlocked in ISRs, as mutexes must only be manipulated
 * in thread context due to ownership and priority inheritance semantics.
 *
 * @param mutex Address of the mutex.
 *
 * @retval 0 Mutex unlocked.
 * @retval -EPERM The current thread does not own the mutex
 * @retval -EINVAL The mutex is not locked
 *
 */
__syscall int k_mutex_unlock(struct k_mutex *mutex);

/**
 * @}
 */

/**
 * @cond INTERNAL_HIDDEN
 */

struct k_sem {
	_wait_q_t wait_q;
	uint32_t count;
	uint32_t limit;
	_POLL_EVENT;

	_OBJECT_TRACING_NEXT_PTR(k_sem)
	_OBJECT_TRACING_LINKED_FLAG
};

#define Z_SEM_INITIALIZER(obj, initial_count, count_limit) \
	{ \
	.wait_q = Z_WAIT_Q_INIT(&obj.wait_q), \
	.count = initial_count, \
	.limit = count_limit, \
	_POLL_EVENT_OBJ_INIT(obj) \
	_OBJECT_TRACING_INIT \
	}

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup semaphore_apis Semaphore APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @brief Initialize a semaphore.
 *
 * This routine initializes a semaphore object, prior to its first use.
 *
 * @param sem Address of the semaphore.
 * @param initial_count Initial semaphore count.
 * @param limit Maximum permitted semaphore count.
 *
 * @retval 0 Semaphore created successfully
 * @retval -EINVAL Invalid values
 *
 */
__syscall int k_sem_init(struct k_sem *sem, unsigned int initial_count,
			  unsigned int limit);

/**
 * @brief Take a semaphore.
 *
 * This routine takes @a sem.
 *
 * @note Can be called by ISRs, but @a timeout must be set to K_NO_WAIT.
 *
 * @param sem Address of the semaphore.
 * @param timeout Waiting period to take the semaphore,
 *                or one of the special values K_NO_WAIT and K_FOREVER.
 *
 * @retval 0 Semaphore taken.
 * @retval -EBUSY Returned without waiting.
 * @retval -EAGAIN Waiting period timed out.
 */
__syscall int k_sem_take(struct k_sem *sem, k_timeout_t timeout);

/**
 * @brief Give a semaphore.
 *
 * This routine gives @a sem, unless the semaphore is already at its maximum
 * permitted count.
 *
 * @note Can be called by ISRs.
 *
 * @param sem Address of the semaphore.
 *
 * @return N/A
 */
__syscall void k_sem_give(struct k_sem *sem);

/**
 * @brief Reset a semaphore's count to zero.
 *
 * This routine sets the count of @a sem to zero.
 *
 * @param sem Address of the semaphore.
 *
 * @return N/A
 */
__syscall void k_sem_reset(struct k_sem *sem);

/**
 * @internal
 */
static inline void z_impl_k_sem_reset(struct k_sem *sem)
{
	sem->count = 0U;
}

/**
 * @brief Get a semaphore's count.
 *
 * This routine returns the current count of @a sem.
 *
 * @param sem Address of the semaphore.
 *
 * @return Current semaphore count.
 */
__syscall unsigned int k_sem_count_get(struct k_sem *sem);

/**
 * @internal
 */
static inline unsigned int z_impl_k_sem_count_get(struct k_sem *sem)
{
	return sem->count;
}

/**
 * @brief Statically define and initialize a semaphore.
 *
 * The semaphore can be accessed outside the module where it is defined using:
 *
 * @code extern struct k_sem <name>; @endcode
 *
 * @param name Name of the semaphore.
 * @param initial_count Initial semaphore count.
 * @param count_limit Maximum permitted semaphore count.
 */
#define K_SEM_DEFINE(name, initial_count, count_limit) \
	Z_STRUCT_SECTION_ITERABLE(k_sem, name) = \
		Z_SEM_INITIALIZER(name, initial_count, count_limit); \
	BUILD_ASSERT(((count_limit) != 0) && \
		     ((initial_count) <= (count_limit)));

/** @} */

/**
 * @defgroup msgq_apis Message Queue APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @brief Message Queue Structure
 */
struct k_msgq {
	/** Message queue wait queue */
	_wait_q_t wait_q;
	/** Lock */
	struct k_spinlock lock;
	/** Message size */
	size_t msg_size;
	/** Maximal number of messages */
	uint32_t max_msgs;
	/** Start of message buffer */
	char *buffer_start;
	/** End of message buffer */
	char *buffer_end;
	/** Read pointer */
	char *read_ptr;
	/** Write pointer */
	char *write_ptr;
	/** Number of used messages */
	uint32_t used_msgs;

	_OBJECT_TRACING_NEXT_PTR(k_msgq)
	_OBJECT_TRACING_LINKED_FLAG

	/** Message queue */
	uint8_t flags;
};
/**
 * @cond INTERNAL_HIDDEN
 */


#define Z_MSGQ_INITIALIZER(obj, q_buffer, q_msg_size, q_max_msgs) \
	{ \
	.wait_q = Z_WAIT_Q_INIT(&obj.wait_q), \
	.msg_size = q_msg_size, \
	.max_msgs = q_max_msgs, \
	.buffer_start = q_buffer, \
	.buffer_end = q_buffer + (q_max_msgs * q_msg_size), \
	.read_ptr = q_buffer, \
	.write_ptr = q_buffer, \
	.used_msgs = 0, \
	_OBJECT_TRACING_INIT \
	}

/**
 * INTERNAL_HIDDEN @endcond
 */


#define K_MSGQ_FLAG_ALLOC	BIT(0)

/**
 * @brief Message Queue Attributes
 */
struct k_msgq_attrs {
	/** Message Size */
	size_t msg_size;
	/** Maximal number of messages */
	uint32_t max_msgs;
	/** Used messages */
	uint32_t used_msgs;
};


/**
 * @brief Statically define and initialize a message queue.
 *
 * The message queue's ring buffer contains space for @a q_max_msgs messages,
 * each of which is @a q_msg_size bytes long. The buffer is aligned to a
 * @a q_align -byte boundary, which must be a power of 2. To ensure that each
 * message is similarly aligned to this boundary, @a q_msg_size must also be
 * a multiple of @a q_align.
 *
 * The message queue can be accessed outside the module where it is defined
 * using:
 *
 * @code extern struct k_msgq <name>; @endcode
 *
 * @param q_name Name of the message queue.
 * @param q_msg_size Message size (in bytes).
 * @param q_max_msgs Maximum number of messages that can be queued.
 * @param q_align Alignment of the message queue's ring buffer.
 *
 */
#define K_MSGQ_DEFINE(q_name, q_msg_size, q_max_msgs, q_align)		\
	static char __noinit __aligned(q_align)				\
		_k_fifo_buf_##q_name[(q_max_msgs) * (q_msg_size)];	\
	Z_STRUCT_SECTION_ITERABLE(k_msgq, q_name) =			\
	       Z_MSGQ_INITIALIZER(q_name, _k_fifo_buf_##q_name,	\
				  q_msg_size, q_max_msgs)

/**
 * @brief Initialize a message queue.
 *
 * This routine initializes a message queue object, prior to its first use.
 *
 * The message queue's ring buffer must contain space for @a max_msgs messages,
 * each of which is @a msg_size bytes long. The buffer must be aligned to an
 * N-byte boundary, where N is a power of 2 (i.e. 1, 2, 4, ...). To ensure
 * that each message is similarly aligned to this boundary, @a q_msg_size
 * must also be a multiple of N.
 *
 * @param q Address of the message queue.
 * @param buffer Pointer to ring buffer that holds queued messages.
 * @param msg_size Message size (in bytes).
 * @param max_msgs Maximum number of messages that can be queued.
 *
 * @return N/A
 */
void k_msgq_init(struct k_msgq *q, char *buffer, size_t msg_size,
		 uint32_t max_msgs);

/**
 * @brief Initialize a message queue.
 *
 * This routine initializes a message queue object, prior to its first use,
 * allocating its internal ring buffer from the calling thread's resource
 * pool.
 *
 * Memory allocated for the ring buffer can be released by calling
 * k_msgq_cleanup(), or if userspace is enabled and the msgq object loses
 * all of its references.
 *
 * @param msgq Address of the message queue.
 * @param msg_size Message size (in bytes).
 * @param max_msgs Maximum number of messages that can be queued.
 *
 * @return 0 on success, -ENOMEM if there was insufficient memory in the
 *	thread's resource pool, or -EINVAL if the size parameters cause
 *	an integer overflow.
 */
__syscall int k_msgq_alloc_init(struct k_msgq *msgq, size_t msg_size,
				uint32_t max_msgs);

/**
 * @brief Release allocated buffer for a queue
 *
 * Releases memory allocated for the ring buffer.
 *
 * @param msgq message queue to cleanup
 *
 * @retval 0 on success
 * @retval -EBUSY Queue not empty
 */
int k_msgq_cleanup(struct k_msgq *msgq);

/**
 * @brief Send a message to a message queue.
 *
 * This routine sends a message to message queue @a q.
 *
 * @note Can be called by ISRs.
 * @note The message content is copied from @a data into @a msgq and the @a data
 * pointer is not retained, so the message content will not be modified
 * by this function.
 *
 * @param msgq Address of the message queue.
 * @param data Pointer to the message.
 * @param timeout Non-negative waiting period to add the message,
 *                or one of the special values K_NO_WAIT and
 *                K_FOREVER.
 *
 * @retval 0 Message sent.
 * @retval -ENOMSG Returned without waiting or queue purged.
 * @retval -EAGAIN Waiting period timed out.
 */
__syscall int k_msgq_put(struct k_msgq *msgq, const void *data, k_timeout_t timeout);

/**
 * @brief Receive a message from a message queue.
 *
 * This routine receives a message from message queue @a q in a "first in,
 * first out" manner.
 *
 * @note Can be called by ISRs, but @a timeout must be set to K_NO_WAIT.
 *
 * @param msgq Address of the message queue.
 * @param data Address of area to hold the received message.
 * @param timeout Waiting period to receive the message,
 *                or one of the special values K_NO_WAIT and
 *                K_FOREVER.
 *
 * @retval 0 Message received.
 * @retval -ENOMSG Returned without waiting.
 * @retval -EAGAIN Waiting period timed out.
 */
__syscall int k_msgq_get(struct k_msgq *msgq, void *data, k_timeout_t timeout);

/**
 * @brief Peek/read a message from a message queue.
 *
 * This routine reads a message from message queue @a q in a "first in,
 * first out" manner and leaves the message in the queue.
 *
 * @note Can be called by ISRs.
 *
 * @param msgq Address of the message queue.
 * @param data Address of area to hold the message read from the queue.
 *
 * @retval 0 Message read.
 * @retval -ENOMSG Returned when the queue has no message.
 */
__syscall int k_msgq_peek(struct k_msgq *msgq, void *data);

/**
 * @brief Purge a message queue.
 *
 * This routine discards all unreceived messages in a message queue's ring
 * buffer. Any threads that are blocked waiting to send a message to the
 * message queue are unblocked and see an -ENOMSG error code.
 *
 * @param msgq Address of the message queue.
 *
 * @return N/A
 */
__syscall void k_msgq_purge(struct k_msgq *msgq);

/**
 * @brief Get the amount of free space in a message queue.
 *
 * This routine returns the number of unused entries in a message queue's
 * ring buffer.
 *
 * @param msgq Address of the message queue.
 *
 * @return Number of unused ring buffer entries.
 */
__syscall uint32_t k_msgq_num_free_get(struct k_msgq *msgq);

/**
 * @brief Get basic attributes of a message queue.
 *
 * This routine fetches basic attributes of message queue into attr argument.
 *
 * @param msgq Address of the message queue.
 * @param attrs pointer to message queue attribute structure.
 *
 * @return N/A
 */
__syscall void  k_msgq_get_attrs(struct k_msgq *msgq,
				 struct k_msgq_attrs *attrs);


static inline uint32_t z_impl_k_msgq_num_free_get(struct k_msgq *msgq)
{
	return msgq->max_msgs - msgq->used_msgs;
}

/**
 * @brief Get the number of messages in a message queue.
 *
 * This routine returns the number of messages in a message queue's ring buffer.
 *
 * @param msgq Address of the message queue.
 *
 * @return Number of messages.
 */
__syscall uint32_t k_msgq_num_used_get(struct k_msgq *msgq);

static inline uint32_t z_impl_k_msgq_num_used_get(struct k_msgq *msgq)
{
	return msgq->used_msgs;
}

/** @} */

/**
 * @defgroup mailbox_apis Mailbox APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @brief Mailbox Message Structure
 *
 */
struct k_mbox_msg {
	/** internal use only - needed for legacy API support */
	uint32_t _mailbox;
	/** size of message (in bytes) */
	size_t size;
	/** application-defined information value */
	uint32_t info;
	/** sender's message data buffer */
	void *tx_data;
	/** internal use only - needed for legacy API support */
	void *_rx_data;
	/** message data block descriptor */
	struct k_mem_block tx_block;
	/** source thread id */
	k_tid_t rx_source_thread;
	/** target thread id */
	k_tid_t tx_target_thread;
	/** internal use only - thread waiting on send (may be a dummy) */
	k_tid_t _syncing_thread;
#if (CONFIG_NUM_MBOX_ASYNC_MSGS > 0)
	/** internal use only - semaphore used during asynchronous send */
	struct k_sem *_async_sem;
#endif
};
/**
 * @brief Mailbox Structure
 *
 */
struct k_mbox {
	/** Transmit messages queue */
	_wait_q_t tx_msg_queue;
	/** Receive message queue */
	_wait_q_t rx_msg_queue;
	struct k_spinlock lock;

	_OBJECT_TRACING_NEXT_PTR(k_mbox)
	_OBJECT_TRACING_LINKED_FLAG
};
/**
 * @cond INTERNAL_HIDDEN
 */

#define Z_MBOX_INITIALIZER(obj) \
	{ \
	.tx_msg_queue = Z_WAIT_Q_INIT(&obj.tx_msg_queue), \
	.rx_msg_queue = Z_WAIT_Q_INIT(&obj.rx_msg_queue), \
	_OBJECT_TRACING_INIT \
	}

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @brief Statically define and initialize a mailbox.
 *
 * The mailbox is to be accessed outside the module where it is defined using:
 *
 * @code extern struct k_mbox <name>; @endcode
 *
 * @param name Name of the mailbox.
 */
#define K_MBOX_DEFINE(name) \
	Z_STRUCT_SECTION_ITERABLE(k_mbox, name) = \
		Z_MBOX_INITIALIZER(name) \

/**
 * @brief Initialize a mailbox.
 *
 * This routine initializes a mailbox object, prior to its first use.
 *
 * @param mbox Address of the mailbox.
 *
 * @return N/A
 */
extern void k_mbox_init(struct k_mbox *mbox);

/**
 * @brief Send a mailbox message in a synchronous manner.
 *
 * This routine sends a message to @a mbox and waits for a receiver to both
 * receive and process it. The message data may be in a buffer, in a memory
 * pool block, or non-existent (i.e. an empty message).
 *
 * @param mbox Address of the mailbox.
 * @param tx_msg Address of the transmit message descriptor.
 * @param timeout Waiting period for the message to be received,
 *                or one of the special values K_NO_WAIT
 *                and K_FOREVER. Once the message has been received,
 *                this routine waits as long as necessary for the message
 *                to be completely processed.
 *
 * @retval 0 Message sent.
 * @retval -ENOMSG Returned without waiting.
 * @retval -EAGAIN Waiting period timed out.
 */
extern int k_mbox_put(struct k_mbox *mbox, struct k_mbox_msg *tx_msg,
		      k_timeout_t timeout);

/**
 * @brief Send a mailbox message in an asynchronous manner.
 *
 * This routine sends a message to @a mbox without waiting for a receiver
 * to process it. The message data may be in a buffer, in a memory pool block,
 * or non-existent (i.e. an empty message). Optionally, the semaphore @a sem
 * will be given when the message has been both received and completely
 * processed by the receiver.
 *
 * @param mbox Address of the mailbox.
 * @param tx_msg Address of the transmit message descriptor.
 * @param sem Address of a semaphore, or NULL if none is needed.
 *
 * @return N/A
 */
extern void k_mbox_async_put(struct k_mbox *mbox, struct k_mbox_msg *tx_msg,
			     struct k_sem *sem);

/**
 * @brief Receive a mailbox message.
 *
 * This routine receives a message from @a mbox, then optionally retrieves
 * its data and disposes of the message.
 *
 * @param mbox Address of the mailbox.
 * @param rx_msg Address of the receive message descriptor.
 * @param buffer Address of the buffer to receive data, or NULL to defer data
 *               retrieval and message disposal until later.
 * @param timeout Waiting period for a message to be received,
 *                or one of the special values K_NO_WAIT and K_FOREVER.
 *
 * @retval 0 Message received.
 * @retval -ENOMSG Returned without waiting.
 * @retval -EAGAIN Waiting period timed out.
 */
extern int k_mbox_get(struct k_mbox *mbox, struct k_mbox_msg *rx_msg,
		      void *buffer, k_timeout_t timeout);

/**
 * @brief Retrieve mailbox message data into a buffer.
 *
 * This routine completes the processing of a received message by retrieving
 * its data into a buffer, then disposing of the message.
 *
 * Alternatively, this routine can be used to dispose of a received message
 * without retrieving its data.
 *
 * @param rx_msg Address of the receive message descriptor.
 * @param buffer Address of the buffer to receive data, or NULL to discard
 *               the data.
 *
 * @return N/A
 */
extern void k_mbox_data_get(struct k_mbox_msg *rx_msg, void *buffer);

/**
 * @brief Retrieve mailbox message data into a memory pool block.
 *
 * This routine completes the processing of a received message by retrieving
 * its data into a memory pool block, then disposing of the message.
 * The memory pool block that results from successful retrieval must be
 * returned to the pool once the data has been processed, even in cases
 * where zero bytes of data are retrieved.
 *
 * Alternatively, this routine can be used to dispose of a received message
 * without retrieving its data. In this case there is no need to return a
 * memory pool block to the pool.
 *
 * This routine allocates a new memory pool block for the data only if the
 * data is not already in one. If a new block cannot be allocated, the routine
 * returns a failure code and the received message is left unchanged. This
 * permits the caller to reattempt data retrieval at a later time or to dispose
 * of the received message without retrieving its data.
 *
 * @param rx_msg Address of a receive message descriptor.
 * @param pool Address of memory pool, or NULL to discard data.
 * @param block Address of the area to hold memory pool block info.
 * @param timeout Time to wait for a memory pool block,
 *                or one of the special values K_NO_WAIT
 *                and K_FOREVER.
 *
 * @retval 0 Data retrieved.
 * @retval -ENOMEM Returned without waiting.
 * @retval -EAGAIN Waiting period timed out.
 */
extern int k_mbox_data_block_get(struct k_mbox_msg *rx_msg,
				 struct k_mem_pool *pool,
				 struct k_mem_block *block,
				 k_timeout_t timeout);

/** @} */

/**
 * @defgroup pipe_apis Pipe APIs
 * @ingroup kernel_apis
 * @{
 */

/** Pipe Structure */
struct k_pipe {
	unsigned char *buffer;          /**< Pipe buffer: may be NULL */
	size_t         size;            /**< Buffer size */
	size_t         bytes_used;      /**< # bytes used in buffer */
	size_t         read_index;      /**< Where in buffer to read from */
	size_t         write_index;     /**< Where in buffer to write */
	struct k_spinlock lock;		/**< Synchronization lock */

	struct {
		_wait_q_t      readers; /**< Reader wait queue */
		_wait_q_t      writers; /**< Writer wait queue */
	} wait_q;			/** Wait queue */

	_OBJECT_TRACING_NEXT_PTR(k_pipe)
	_OBJECT_TRACING_LINKED_FLAG
	uint8_t	       flags;		/**< Flags */
};

/**
 * @cond INTERNAL_HIDDEN
 */
#define K_PIPE_FLAG_ALLOC	BIT(0)	/** Buffer was allocated */

#define Z_PIPE_INITIALIZER(obj, pipe_buffer, pipe_buffer_size)     \
	{                                                           \
	.buffer = pipe_buffer,                                      \
	.size = pipe_buffer_size,                                   \
	.bytes_used = 0,                                            \
	.read_index = 0,                                            \
	.write_index = 0,                                           \
	.lock = {},                                                 \
	.wait_q = {                                                 \
		.readers = Z_WAIT_Q_INIT(&obj.wait_q.readers),       \
		.writers = Z_WAIT_Q_INIT(&obj.wait_q.writers)        \
	},                                                          \
	_OBJECT_TRACING_INIT                                        \
	.flags = 0                                                  \
	}

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @brief Statically define and initialize a pipe.
 *
 * The pipe can be accessed outside the module where it is defined using:
 *
 * @code extern struct k_pipe <name>; @endcode
 *
 * @param name Name of the pipe.
 * @param pipe_buffer_size Size of the pipe's ring buffer (in bytes),
 *                         or zero if no ring buffer is used.
 * @param pipe_align Alignment of the pipe's ring buffer (power of 2).
 *
 */
#define K_PIPE_DEFINE(name, pipe_buffer_size, pipe_align)		\
	static unsigned char __noinit __aligned(pipe_align)	\
		_k_pipe_buf_##name[pipe_buffer_size];			\
	Z_STRUCT_SECTION_ITERABLE(k_pipe, name) = \
		Z_PIPE_INITIALIZER(name, _k_pipe_buf_##name, pipe_buffer_size)

/**
 * @brief Initialize a pipe.
 *
 * This routine initializes a pipe object, prior to its first use.
 *
 * @param pipe Address of the pipe.
 * @param buffer Address of the pipe's ring buffer, or NULL if no ring buffer
 *               is used.
 * @param size Size of the pipe's ring buffer (in bytes), or zero if no ring
 *             buffer is used.
 *
 * @return N/A
 */
void k_pipe_init(struct k_pipe *pipe, unsigned char *buffer, size_t size);

/**
 * @brief Release a pipe's allocated buffer
 *
 * If a pipe object was given a dynamically allocated buffer via
 * k_pipe_alloc_init(), this will free it. This function does nothing
 * if the buffer wasn't dynamically allocated.
 *
 * @param pipe Address of the pipe.
 * @retval 0 on success
 * @retval -EAGAIN nothing to cleanup
 */
int k_pipe_cleanup(struct k_pipe *pipe);

/**
 * @brief Initialize a pipe and allocate a buffer for it
 *
 * Storage for the buffer region will be allocated from the calling thread's
 * resource pool. This memory will be released if k_pipe_cleanup() is called,
 * or userspace is enabled and the pipe object loses all references to it.
 *
 * This function should only be called on uninitialized pipe objects.
 *
 * @param pipe Address of the pipe.
 * @param size Size of the pipe's ring buffer (in bytes), or zero if no ring
 *             buffer is used.
 * @retval 0 on success
 * @retval -ENOMEM if memory couldn't be allocated
 */
__syscall int k_pipe_alloc_init(struct k_pipe *pipe, size_t size);

/**
 * @brief Write data to a pipe.
 *
 * This routine writes up to @a bytes_to_write bytes of data to @a pipe.
 *
 * @param pipe Address of the pipe.
 * @param data Address of data to write.
 * @param bytes_to_write Size of data (in bytes).
 * @param bytes_written Address of area to hold the number of bytes written.
 * @param min_xfer Minimum number of bytes to write.
 * @param timeout Waiting period to wait for the data to be written,
 *                or one of the special values K_NO_WAIT and K_FOREVER.
 *
 * @retval 0 At least @a min_xfer bytes of data were written.
 * @retval -EIO Returned without waiting; zero data bytes were written.
 * @retval -EAGAIN Waiting period timed out; between zero and @a min_xfer
 *                 minus one data bytes were written.
 */
__syscall int k_pipe_put(struct k_pipe *pipe, void *data,
			 size_t bytes_to_write, size_t *bytes_written,
			 size_t min_xfer, k_timeout_t timeout);

/**
 * @brief Read data from a pipe.
 *
 * This routine reads up to @a bytes_to_read bytes of data from @a pipe.
 *
 * @param pipe Address of the pipe.
 * @param data Address to place the data read from pipe.
 * @param bytes_to_read Maximum number of data bytes to read.
 * @param bytes_read Address of area to hold the number of bytes read.
 * @param min_xfer Minimum number of data bytes to read.
 * @param timeout Waiting period to wait for the data to be read,
 *                or one of the special values K_NO_WAIT and K_FOREVER.
 *
 * @retval 0 At least @a min_xfer bytes of data were read.
 * @retval -EINVAL invalid parameters supplied
 * @retval -EIO Returned without waiting; zero data bytes were read.
 * @retval -EAGAIN Waiting period timed out; between zero and @a min_xfer
 *                 minus one data bytes were read.
 */
__syscall int k_pipe_get(struct k_pipe *pipe, void *data,
			 size_t bytes_to_read, size_t *bytes_read,
			 size_t min_xfer, k_timeout_t timeout);

/**
 * @brief Write memory block to a pipe.
 *
 * This routine writes the data contained in a memory block to @a pipe.
 * Once all of the data in the block has been written to the pipe, it will
 * free the memory block @a block and give the semaphore @a sem (if specified).
 *
 * @param pipe Address of the pipe.
 * @param block Memory block containing data to send
 * @param size Number of data bytes in memory block to send
 * @param sem Semaphore to signal upon completion (else NULL)
 *
 * @return N/A
 */
extern void k_pipe_block_put(struct k_pipe *pipe, struct k_mem_block *block,
			     size_t size, struct k_sem *sem);

/**
 * @brief Query the number of bytes that may be read from @a pipe.
 *
 * @param pipe Address of the pipe.
 *
 * @retval a number n such that 0 <= n <= @ref k_pipe.size; the
 *         result is zero for unbuffered pipes.
 */
__syscall size_t k_pipe_read_avail(struct k_pipe *pipe);

/**
 * @brief Query the number of bytes that may be written to @a pipe
 *
 * @param pipe Address of the pipe.
 *
 * @retval a number n such that 0 <= n <= @ref k_pipe.size; the
 *         result is zero for unbuffered pipes.
 */
__syscall size_t k_pipe_write_avail(struct k_pipe *pipe);

/** @} */

/**
 * @cond INTERNAL_HIDDEN
 */

struct k_mem_slab {
	_wait_q_t wait_q;
	uint32_t num_blocks;
	size_t block_size;
	char *buffer;
	char *free_list;
	uint32_t num_used;

	_OBJECT_TRACING_NEXT_PTR(k_mem_slab)
	_OBJECT_TRACING_LINKED_FLAG
};

#define Z_MEM_SLAB_INITIALIZER(obj, slab_buffer, slab_block_size, \
			       slab_num_blocks) \
	{ \
	.wait_q = Z_WAIT_Q_INIT(&obj.wait_q), \
	.num_blocks = slab_num_blocks, \
	.block_size = slab_block_size, \
	.buffer = slab_buffer, \
	.free_list = NULL, \
	.num_used = 0, \
	_OBJECT_TRACING_INIT \
	}


/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup mem_slab_apis Memory Slab APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @brief Statically define and initialize a memory slab.
 *
 * The memory slab's buffer contains @a slab_num_blocks memory blocks
 * that are @a slab_block_size bytes long. The buffer is aligned to a
 * @a slab_align -byte boundary. To ensure that each memory block is similarly
 * aligned to this boundary, @a slab_block_size must also be a multiple of
 * @a slab_align.
 *
 * The memory slab can be accessed outside the module where it is defined
 * using:
 *
 * @code extern struct k_mem_slab <name>; @endcode
 *
 * @param name Name of the memory slab.
 * @param slab_block_size Size of each memory block (in bytes).
 * @param slab_num_blocks Number memory blocks.
 * @param slab_align Alignment of the memory slab's buffer (power of 2).
 */
#define K_MEM_SLAB_DEFINE(name, slab_block_size, slab_num_blocks, slab_align) \
	char __noinit __aligned(WB_UP(slab_align)) \
	   _k_mem_slab_buf_##name[(slab_num_blocks) * WB_UP(slab_block_size)]; \
	Z_STRUCT_SECTION_ITERABLE(k_mem_slab, name) = \
		Z_MEM_SLAB_INITIALIZER(name, _k_mem_slab_buf_##name, \
					WB_UP(slab_block_size), slab_num_blocks)

/**
 * @brief Initialize a memory slab.
 *
 * Initializes a memory slab, prior to its first use.
 *
 * The memory slab's buffer contains @a slab_num_blocks memory blocks
 * that are @a slab_block_size bytes long. The buffer must be aligned to an
 * N-byte boundary matching a word boundary, where N is a power of 2
 * (i.e. 4 on 32-bit systems, 8, 16, ...).
 * To ensure that each memory block is similarly aligned to this boundary,
 * @a slab_block_size must also be a multiple of N.
 *
 * @param slab Address of the memory slab.
 * @param buffer Pointer to buffer used for the memory blocks.
 * @param block_size Size of each memory block (in bytes).
 * @param num_blocks Number of memory blocks.
 *
 * @retval 0 on success
 * @retval -EINVAL invalid data supplied
 *
 */
extern int k_mem_slab_init(struct k_mem_slab *slab, void *buffer,
			   size_t block_size, uint32_t num_blocks);

/**
 * @brief Allocate memory from a memory slab.
 *
 * This routine allocates a memory block from a memory slab.
 *
 * @note Can be called by ISRs, but @a timeout must be set to K_NO_WAIT.
 *
 * @param slab Address of the memory slab.
 * @param mem Pointer to block address area.
 * @param timeout Non-negative waiting period to wait for operation to complete.
 *        Use K_NO_WAIT to return without waiting,
 *        or K_FOREVER to wait as long as necessary.
 *
 * @retval 0 Memory allocated. The block address area pointed at by @a mem
 *         is set to the starting address of the memory block.
 * @retval -ENOMEM Returned without waiting.
 * @retval -EAGAIN Waiting period timed out.
 * @retval -EINVAL Invalid data supplied
 */
extern int k_mem_slab_alloc(struct k_mem_slab *slab, void **mem,
			    k_timeout_t timeout);

/**
 * @brief Free memory allocated from a memory slab.
 *
 * This routine releases a previously allocated memory block back to its
 * associated memory slab.
 *
 * @param slab Address of the memory slab.
 * @param mem Pointer to block address area (as set by k_mem_slab_alloc()).
 *
 * @return N/A
 */
extern void k_mem_slab_free(struct k_mem_slab *slab, void **mem);

/**
 * @brief Get the number of used blocks in a memory slab.
 *
 * This routine gets the number of memory blocks that are currently
 * allocated in @a slab.
 *
 * @param slab Address of the memory slab.
 *
 * @return Number of allocated memory blocks.
 */
static inline uint32_t k_mem_slab_num_used_get(struct k_mem_slab *slab)
{
	return slab->num_used;
}

/**
 * @brief Get the number of unused blocks in a memory slab.
 *
 * This routine gets the number of memory blocks that are currently
 * unallocated in @a slab.
 *
 * @param slab Address of the memory slab.
 *
 * @return Number of unallocated memory blocks.
 */
static inline uint32_t k_mem_slab_num_free_get(struct k_mem_slab *slab)
{
	return slab->num_blocks - slab->num_used;
}

/** @} */

/**
 * @addtogroup mem_pool_apis
 * @{
 */

/* kernel synchronized heap struct */

struct k_heap {
	struct sys_heap heap;
	_wait_q_t wait_q;
	struct k_spinlock lock;
};

/**
 * @brief Initialize a k_heap
 *
 * This constructs a synchronized k_heap object over a memory region
 * specified by the user.  Note that while any alignment and size can
 * be passed as valid parameters, internal alignment restrictions
 * inside the inner sys_heap mean that not all bytes may be usable as
 * allocated memory.
 *
 * @param h Heap struct to initialize
 * @param mem Pointer to memory.
 * @param bytes Size of memory region, in bytes
 */
void k_heap_init(struct k_heap *h, void *mem, size_t bytes);

/**
 * @brief Allocate memory from a k_heap
 *
 * Allocates and returns a memory buffer from the memory region owned
 * by the heap.  If no memory is available immediately, the call will
 * block for the specified timeout (constructed via the standard
 * timeout API, or K_NO_WAIT or K_FOREVER) waiting for memory to be
 * freed.  If the allocation cannot be performed by the expiration of
 * the timeout, NULL will be returned.
 *
 * @note Can be called by ISRs, but @a timeout must be set to K_NO_WAIT.
 *
 * @param h Heap from which to allocate
 * @param bytes Desired size of block to allocate
 * @param timeout How long to wait, or K_NO_WAIT
 * @return A pointer to valid heap memory, or NULL
 */
void *k_heap_alloc(struct k_heap *h, size_t bytes, k_timeout_t timeout);

/**
 * @brief Free memory allocated by k_heap_alloc()
 *
 * Returns the specified memory block, which must have been returned
 * from k_heap_alloc(), to the heap for use by other callers.  Passing
 * a NULL block is legal, and has no effect.
 *
 * @param h Heap to which to return the memory
 * @param mem A valid memory block, or NULL
 */
void k_heap_free(struct k_heap *h, void *mem);

/**
 * @brief Define a static k_heap
 *
 * This macro defines and initializes a static memory region and
 * k_heap of the requested size.  After kernel start, &name can be
 * used as if k_heap_init() had been called.
 *
 * @param name Symbol name for the struct k_heap object
 * @param bytes Size of memory region, in bytes
 */
#define K_HEAP_DEFINE(name, bytes)				\
	char __aligned(sizeof(void *)) kheap_##name[bytes];	\
	Z_STRUCT_SECTION_ITERABLE(k_heap, name) = {		\
		.heap = {					\
			.init_mem = kheap_##name,		\
			.init_bytes = (bytes),			\
		 },						\
	}

/**
 * @brief Statically define and initialize a memory pool.
 *
 * The memory pool's buffer contains @a n_max blocks that are @a max_size bytes
 * long. The memory pool allows blocks to be repeatedly partitioned into
 * quarters, down to blocks of @a min_size bytes long. The buffer is aligned
 * to a @a align -byte boundary.
 *
 * If the pool is to be accessed outside the module where it is defined, it
 * can be declared via
 *
 * @note When @option{CONFIG_MEM_POOL_HEAP_BACKEND} is enabled, the k_mem_pool
 * API is implemented on top of a k_heap, which is a more general
 * purpose allocator which does not make the same promises about
 * splitting or alignment detailed above.  Blocks will be aligned only
 * to the 8 byte chunk stride of the underlying heap and may point
 * anywhere within the heap; they are not split into four as
 * described.
 *
 * @code extern struct k_mem_pool <name>; @endcode
 *
 * @param name Name of the memory pool.
 * @param minsz Size of the smallest blocks in the pool (in bytes).
 * @param maxsz Size of the largest blocks in the pool (in bytes).
 * @param nmax Number of maximum sized blocks in the pool.
 * @param align Alignment of the pool's buffer (power of 2).
 */
#define K_MEM_POOL_DEFINE(name, minsz, maxsz, nmax, align) \
	Z_MEM_POOL_DEFINE(name, minsz, maxsz, nmax, align)

/**
 * @brief Allocate memory from a memory pool.
 *
 * This routine allocates a memory block from a memory pool.
 *
 * @note Can be called by ISRs, but @a timeout must be set to K_NO_WAIT.
 *
 * @param pool Address of the memory pool.
 * @param block Pointer to block descriptor for the allocated memory.
 * @param size Amount of memory to allocate (in bytes).
 * @param timeout Waiting period to wait for operation to complete.
 *        Use K_NO_WAIT to return without waiting,
 *        or K_FOREVER to wait as long as necessary.
 *
 * @retval 0 Memory allocated. The @a data field of the block descriptor
 *         is set to the starting address of the memory block.
 * @retval -ENOMEM Returned without waiting.
 * @retval -EAGAIN Waiting period timed out.
 */
extern int k_mem_pool_alloc(struct k_mem_pool *pool, struct k_mem_block *block,
			    size_t size, k_timeout_t timeout);

/**
 * @brief Allocate memory from a memory pool with malloc() semantics
 *
 * Such memory must be released using k_free().
 *
 * @param pool Address of the memory pool.
 * @param size Amount of memory to allocate (in bytes).
 * @return Address of the allocated memory if successful, otherwise NULL
 */
extern void *k_mem_pool_malloc(struct k_mem_pool *pool, size_t size);

/**
 * @brief Free memory allocated from a memory pool.
 *
 * This routine releases a previously allocated memory block back to its
 * memory pool.
 *
 * @param block Pointer to block descriptor for the allocated memory.
 *
 * @return N/A
 */
extern void k_mem_pool_free(struct k_mem_block *block);

/**
 * @brief Free memory allocated from a memory pool.
 *
 * This routine releases a previously allocated memory block back to its
 * memory pool
 *
 * @param id Memory block identifier.
 *
 * @return N/A
 */
extern void k_mem_pool_free_id(struct k_mem_block_id *id);

/**
 * @}
 */

/**
 * @defgroup heap_apis Heap Memory Pool APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @brief Allocate memory from heap.
 *
 * This routine provides traditional malloc() semantics. Memory is
 * allocated from the heap memory pool.
 *
 * @param size Amount of memory requested (in bytes).
 *
 * @return Address of the allocated memory if successful; otherwise NULL.
 */
extern void *k_malloc(size_t size);

/**
 * @brief Free memory allocated from heap.
 *
 * This routine provides traditional free() semantics. The memory being
 * returned must have been allocated from the heap memory pool or
 * k_mem_pool_malloc().
 *
 * If @a ptr is NULL, no operation is performed.
 *
 * @param ptr Pointer to previously allocated memory.
 *
 * @return N/A
 */
extern void k_free(void *ptr);

/**
 * @brief Allocate memory from heap, array style
 *
 * This routine provides traditional calloc() semantics. Memory is
 * allocated from the heap memory pool and zeroed.
 *
 * @param nmemb Number of elements in the requested array
 * @param size Size of each array element (in bytes).
 *
 * @return Address of the allocated memory if successful; otherwise NULL.
 */
extern void *k_calloc(size_t nmemb, size_t size);

/** @} */

/* polling API - PRIVATE */

#ifdef CONFIG_POLL
#define _INIT_OBJ_POLL_EVENT(obj) do { (obj)->poll_event = NULL; } while (false)
#else
#define _INIT_OBJ_POLL_EVENT(obj) do { } while (false)
#endif

/* private - types bit positions */
enum _poll_types_bits {
	/* can be used to ignore an event */
	_POLL_TYPE_IGNORE,

	/* to be signaled by k_poll_signal_raise() */
	_POLL_TYPE_SIGNAL,

	/* semaphore availability */
	_POLL_TYPE_SEM_AVAILABLE,

	/* queue/FIFO/LIFO data availability */
	_POLL_TYPE_DATA_AVAILABLE,

	_POLL_NUM_TYPES
};

#define Z_POLL_TYPE_BIT(type) (1U << ((type) - 1U))

/* private - states bit positions */
enum _poll_states_bits {
	/* default state when creating event */
	_POLL_STATE_NOT_READY,

	/* signaled by k_poll_signal_raise() */
	_POLL_STATE_SIGNALED,

	/* semaphore is available */
	_POLL_STATE_SEM_AVAILABLE,

	/* data is available to read on queue/FIFO/LIFO */
	_POLL_STATE_DATA_AVAILABLE,

	/* queue/FIFO/LIFO wait was cancelled */
	_POLL_STATE_CANCELLED,

	_POLL_NUM_STATES
};

#define Z_POLL_STATE_BIT(state) (1U << ((state) - 1U))

#define _POLL_EVENT_NUM_UNUSED_BITS \
	(32 - (0 \
	       + 8 /* tag */ \
	       + _POLL_NUM_TYPES \
	       + _POLL_NUM_STATES \
	       + 1 /* modes */ \
	      ))

/* end of polling API - PRIVATE */


/**
 * @defgroup poll_apis Async polling APIs
 * @ingroup kernel_apis
 * @{
 */

/* Public polling API */

/* public - values for k_poll_event.type bitfield */
#define K_POLL_TYPE_IGNORE 0
#define K_POLL_TYPE_SIGNAL Z_POLL_TYPE_BIT(_POLL_TYPE_SIGNAL)
#define K_POLL_TYPE_SEM_AVAILABLE Z_POLL_TYPE_BIT(_POLL_TYPE_SEM_AVAILABLE)
#define K_POLL_TYPE_DATA_AVAILABLE Z_POLL_TYPE_BIT(_POLL_TYPE_DATA_AVAILABLE)
#define K_POLL_TYPE_FIFO_DATA_AVAILABLE K_POLL_TYPE_DATA_AVAILABLE

/* public - polling modes */
enum k_poll_modes {
	/* polling thread does not take ownership of objects when available */
	K_POLL_MODE_NOTIFY_ONLY = 0,

	K_POLL_NUM_MODES
};

/* public - values for k_poll_event.state bitfield */
#define K_POLL_STATE_NOT_READY 0
#define K_POLL_STATE_SIGNALED Z_POLL_STATE_BIT(_POLL_STATE_SIGNALED)
#define K_POLL_STATE_SEM_AVAILABLE Z_POLL_STATE_BIT(_POLL_STATE_SEM_AVAILABLE)
#define K_POLL_STATE_DATA_AVAILABLE Z_POLL_STATE_BIT(_POLL_STATE_DATA_AVAILABLE)
#define K_POLL_STATE_FIFO_DATA_AVAILABLE K_POLL_STATE_DATA_AVAILABLE
#define K_POLL_STATE_CANCELLED Z_POLL_STATE_BIT(_POLL_STATE_CANCELLED)

/* public - poll signal object */
struct k_poll_signal {
	/** PRIVATE - DO NOT TOUCH */
	sys_dlist_t poll_events;

	/**
	 * 1 if the event has been signaled, 0 otherwise. Stays set to 1 until
	 * user resets it to 0.
	 */
	unsigned int signaled;

	/** custom result value passed to k_poll_signal_raise() if needed */
	int result;
};

#define K_POLL_SIGNAL_INITIALIZER(obj) \
	{ \
	.poll_events = SYS_DLIST_STATIC_INIT(&obj.poll_events), \
	.signaled = 0, \
	.result = 0, \
	}
/**
 * @brief Poll Event
 *
 */
struct k_poll_event {
	/** PRIVATE - DO NOT TOUCH */
	sys_dnode_t _node;

	/** PRIVATE - DO NOT TOUCH */
	struct z_poller *poller;

	/** optional user-specified tag, opaque, untouched by the API */
	uint32_t tag:8;

	/** bitfield of event types (bitwise-ORed K_POLL_TYPE_xxx values) */
	uint32_t type:_POLL_NUM_TYPES;

	/** bitfield of event states (bitwise-ORed K_POLL_STATE_xxx values) */
	uint32_t state:_POLL_NUM_STATES;

	/** mode of operation, from enum k_poll_modes */
	uint32_t mode:1;

	/** unused bits in 32-bit word */
	uint32_t unused:_POLL_EVENT_NUM_UNUSED_BITS;

	/** per-type data */
	union {
		void *obj;
		struct k_poll_signal *signal;
		struct k_sem *sem;
		struct k_fifo *fifo;
		struct k_queue *queue;
	};
};

#define K_POLL_EVENT_INITIALIZER(_event_type, _event_mode, _event_obj) \
	{ \
	.poller = NULL, \
	.type = _event_type, \
	.state = K_POLL_STATE_NOT_READY, \
	.mode = _event_mode, \
	.unused = 0, \
	.obj = _event_obj, \
	}

#define K_POLL_EVENT_STATIC_INITIALIZER(_event_type, _event_mode, _event_obj, \
					event_tag) \
	{ \
	.tag = event_tag, \
	.type = _event_type, \
	.state = K_POLL_STATE_NOT_READY, \
	.mode = _event_mode, \
	.unused = 0, \
	.obj = _event_obj, \
	}

/**
 * @brief Initialize one struct k_poll_event instance
 *
 * After this routine is called on a poll event, the event it ready to be
 * placed in an event array to be passed to k_poll().
 *
 * @param event The event to initialize.
 * @param type A bitfield of the types of event, from the K_POLL_TYPE_xxx
 *             values. Only values that apply to the same object being polled
 *             can be used together. Choosing K_POLL_TYPE_IGNORE disables the
 *             event.
 * @param mode Future. Use K_POLL_MODE_NOTIFY_ONLY.
 * @param obj Kernel object or poll signal.
 *
 * @return N/A
 */

extern void k_poll_event_init(struct k_poll_event *event, uint32_t type,
			      int mode, void *obj);

/**
 * @brief Wait for one or many of multiple poll events to occur
 *
 * This routine allows a thread to wait concurrently for one or many of
 * multiple poll events to have occurred. Such events can be a kernel object
 * being available, like a semaphore, or a poll signal event.
 *
 * When an event notifies that a kernel object is available, the kernel object
 * is not "given" to the thread calling k_poll(): it merely signals the fact
 * that the object was available when the k_poll() call was in effect. Also,
 * all threads trying to acquire an object the regular way, i.e. by pending on
 * the object, have precedence over the thread polling on the object. This
 * means that the polling thread will never get the poll event on an object
 * until the object becomes available and its pend queue is empty. For this
 * reason, the k_poll() call is more effective when the objects being polled
 * only have one thread, the polling thread, trying to acquire them.
 *
 * When k_poll() returns 0, the caller should loop on all the events that were
 * passed to k_poll() and check the state field for the values that were
 * expected and take the associated actions.
 *
 * Before being reused for another call to k_poll(), the user has to reset the
 * state field to K_POLL_STATE_NOT_READY.
 *
 * When called from user mode, a temporary memory allocation is required from
 * the caller's resource pool.
 *
 * @param events An array of events to be polled for.
 * @param num_events The number of events in the array.
 * @param timeout Waiting period for an event to be ready,
 *                or one of the special values K_NO_WAIT and K_FOREVER.
 *
 * @retval 0 One or more events are ready.
 * @retval -EAGAIN Waiting period timed out.
 * @retval -EINTR Polling has been interrupted, e.g. with
 *         k_queue_cancel_wait(). All output events are still set and valid,
 *         cancelled event(s) will be set to K_POLL_STATE_CANCELLED. In other
 *         words, -EINTR status means that at least one of output events is
 *         K_POLL_STATE_CANCELLED.
 * @retval -ENOMEM Thread resource pool insufficient memory (user mode only)
 * @retval -EINVAL Bad parameters (user mode only)
 */

__syscall int k_poll(struct k_poll_event *events, int num_events,
		     k_timeout_t timeout);

/**
 * @brief Initialize a poll signal object.
 *
 * Ready a poll signal object to be signaled via k_poll_signal_raise().
 *
 * @param signal A poll signal.
 *
 * @return N/A
 */

__syscall void k_poll_signal_init(struct k_poll_signal *signal);

/*
 * @brief Reset a poll signal object's state to unsignaled.
 *
 * @param signal A poll signal object
 */
__syscall void k_poll_signal_reset(struct k_poll_signal *signal);

static inline void z_impl_k_poll_signal_reset(struct k_poll_signal *signal)
{
	signal->signaled = 0U;
}

/**
 * @brief Fetch the signaled state and result value of a poll signal
 *
 * @param signal A poll signal object
 * @param signaled An integer buffer which will be written nonzero if the
 *		   object was signaled
 * @param result An integer destination buffer which will be written with the
 *		   result value if the object was signaled, or an undefined
 *		   value if it was not.
 */
__syscall void k_poll_signal_check(struct k_poll_signal *signal,
				   unsigned int *signaled, int *result);

/**
 * @brief Signal a poll signal object.
 *
 * This routine makes ready a poll signal, which is basically a poll event of
 * type K_POLL_TYPE_SIGNAL. If a thread was polling on that event, it will be
 * made ready to run. A @a result value can be specified.
 *
 * The poll signal contains a 'signaled' field that, when set by
 * k_poll_signal_raise(), stays set until the user sets it back to 0 with
 * k_poll_signal_reset(). It thus has to be reset by the user before being
 * passed again to k_poll() or k_poll() will consider it being signaled, and
 * will return immediately.
 *
 * @note The result is stored and the 'signaled' field is set even if
 * this function returns an error indicating that an expiring poll was
 * not notified.  The next k_poll() will detect the missed raise.
 *
 * @param signal A poll signal.
 * @param result The value to store in the result field of the signal.
 *
 * @retval 0 The signal was delivered successfully.
 * @retval -EAGAIN The polling thread's timeout is in the process of expiring.
 */

__syscall int k_poll_signal_raise(struct k_poll_signal *signal, int result);

/**
 * @internal
 */
extern void z_handle_obj_poll_events(sys_dlist_t *events, uint32_t state);

/** @} */

/**
 * @defgroup cpu_idle_apis CPU Idling APIs
 * @ingroup kernel_apis
 * @{
 */
/**
 * @brief Make the CPU idle.
 *
 * This function makes the CPU idle until an event wakes it up.
 *
 * In a regular system, the idle thread should be the only thread responsible
 * for making the CPU idle and triggering any type of power management.
 * However, in some more constrained systems, such as a single-threaded system,
 * the only thread would be responsible for this if needed.
 *
 * @note In some architectures, before returning, the function unmasks interrupts
 * unconditionally.
 *
 * @return N/A
 */
static inline void k_cpu_idle(void)
{
	arch_cpu_idle();
}

/**
 * @brief Make the CPU idle in an atomic fashion.
 *
 * Similar to k_cpu_idle(), but must be called with interrupts locked.
 *
 * Enabling interrupts and entering a low-power mode will be atomic,
 * i.e. there will be no period of time where interrupts are enabled before
 * the processor enters a low-power mode.
 *
 * After waking up from the low-power mode, the interrupt lockout state will
 * be restored as if by irq_unlock(key).
 *
 * @param key Interrupt locking key obtained from irq_lock().
 *
 * @return N/A
 */
static inline void k_cpu_atomic_idle(unsigned int key)
{
	arch_cpu_atomic_idle(key);
}

/**
 * @}
 */

/**
 * @internal
 */
extern void z_sys_power_save_idle_exit(int32_t ticks);

#ifdef ARCH_EXCEPT
/* This architecture has direct support for triggering a CPU exception */
#define z_except_reason(reason)	ARCH_EXCEPT(reason)
#else

#if !defined(CONFIG_ASSERT_NO_FILE_INFO)
#define __EXCEPT_LOC() __ASSERT_PRINT("@ %s:%d\n", __FILE__, __LINE__)
#else
#define __EXCEPT_LOC()
#endif

/* NOTE: This is the implementation for arches that do not implement
 * ARCH_EXCEPT() to generate a real CPU exception.
 *
 * We won't have a real exception frame to determine the PC value when
 * the oops occurred, so print file and line number before we jump into
 * the fatal error handler.
 */
#define z_except_reason(reason) do { \
		__EXCEPT_LOC();              \
		z_fatal_error(reason, NULL); \
	} while (false)

#endif /* _ARCH__EXCEPT */

/**
 * @brief Fatally terminate a thread
 *
 * This should be called when a thread has encountered an unrecoverable
 * runtime condition and needs to terminate. What this ultimately
 * means is determined by the _fatal_error_handler() implementation, which
 * will be called will reason code K_ERR_KERNEL_OOPS.
 *
 * If this is called from ISR context, the default system fatal error handler
 * will treat it as an unrecoverable system error, just like k_panic().
 */
#define k_oops()	z_except_reason(K_ERR_KERNEL_OOPS)

/**
 * @brief Fatally terminate the system
 *
 * This should be called when the Zephyr kernel has encountered an
 * unrecoverable runtime condition and needs to terminate. What this ultimately
 * means is determined by the _fatal_error_handler() implementation, which
 * will be called will reason code K_ERR_KERNEL_PANIC.
 */
#define k_panic()	z_except_reason(K_ERR_KERNEL_PANIC)

/*
 * private APIs that are utilized by one or more public APIs
 */

/**
 * @internal
 */
extern void z_init_thread_base(struct _thread_base *thread_base,
			      int priority, uint32_t initial_state,
			      unsigned int options);

#ifdef CONFIG_MULTITHREADING
/**
 * @internal
 */
extern void z_init_static_threads(void);
#else
/**
 * @internal
 */
#define z_init_static_threads() do { } while (false)
#endif

/**
 * @internal
 */
extern bool z_is_thread_essential(void);
/**
 * @internal
 */
extern void z_timer_expiration_handler(struct _timeout *t);

#ifdef CONFIG_PRINTK
/**
 * @brief Emit a character buffer to the console device
 *
 * @param c String of characters to print
 * @param n The length of the string
 *
 */
__syscall void k_str_out(char *c, size_t n);
#endif

/**
 * @brief Disable preservation of floating point context information.
 *
 * This routine informs the kernel that the specified thread
 * will no longer be using the floating point registers.
 *
 * @warning
 * Some architectures apply restrictions on how the disabling of floating
 * point preservation may be requested, see arch_float_disable.
 *
 * @warning
 * This routine should only be used to disable floating point support for
 * a thread that currently has such support enabled.
 *
 * @param thread ID of thread.
 *
 * @retval 0       On success.
 * @retval -ENOSYS If the floating point disabling is not implemented.
 *         -EINVAL If the floating point disabling could not be performed.
 */
__syscall int k_float_disable(struct k_thread *thread);

#ifdef CONFIG_THREAD_RUNTIME_STATS

/**
 * @brief Get the runtime statistics of a thread
 *
 * @param thread ID of thread.
 * @param stats Pointer to struct to copy statistics into.
 * @return -EINVAL if null pointers, otherwise 0
 */
int k_thread_runtime_stats_get(k_tid_t thread,
			       k_thread_runtime_stats_t *stats);

/**
 * @brief Get the runtime statistics of all threads
 *
 * @param stats Pointer to struct to copy statistics into.
 * @return -EINVAL if null pointers, otherwise 0
 */
int k_thread_runtime_stats_all_get(k_thread_runtime_stats_t *stats);

#endif

#ifdef __cplusplus
}
#endif

#include <tracing/tracing.h>
#include <syscalls/kernel.h>

#endif /* !_ASMLANGUAGE */

#endif /* ZEPHYR_INCLUDE_KERNEL_H_ */
