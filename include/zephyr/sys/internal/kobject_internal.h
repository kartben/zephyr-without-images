/*
 * Copyright (c) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_INCLUDE_SYS_INTERNAL_KOBJECT_INTERNAL_H
#define ZEPHYR_INCLUDE_SYS_INTERNAL_KOBJECT_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup usermode_internal_apis User Mode Internal APIs
 * @ingroup internal_api
 * @{
 */

#if defined(CONFIG_USERSPACE) || defined(__DOXYGEN__)
#if defined(CONFIG_GEN_PRIV_STACKS) || defined(__DOXYGEN__)
/* Metadata struct for K_OBJ_THREAD_STACK_ELEMENT */
struct z_stack_data {
	/* Size of the entire stack object, including reserved areas */
	size_t size;

	/* Stack buffer for privilege mode elevations */
	uint8_t *priv;
};
#endif /* CONFIG_GEN_PRIV_STACKS */

/* Object extra data. Only some objects use this, determined by object type */
union k_object_data {
	/* Backing mutex for K_OBJ_SYS_MUTEX */
	struct k_mutex *mutex;

	/* Numerical thread ID for K_OBJ_THREAD */
	unsigned int thread_id;

#if defined(CONFIG_GEN_PRIV_STACKS) || defined(__DOXYGEN__)
	/* Metadata for K_OBJ_THREAD_STACK_ELEMENT */
	const struct z_stack_data *stack_data;
#else
	/* Stack buffer size for K_OBJ_THREAD_STACK_ELEMENT */
	size_t stack_size;
#endif /* CONFIG_GEN_PRIV_STACKS */

	/* Futex wait queue and spinlock for K_OBJ_FUTEX */
	struct z_futex_data *futex_data;

	/* All other objects */
	int unused;
};

/**
 * @brief Table generated by gperf, these objects are retrieved via
 * k_object_find().
 *
 * @note This is an internal API. Do not use unless you are extending
 *       functionality in the Zephyr tree.
 */
struct k_object {
	void *name;
	uint8_t perms[CONFIG_MAX_THREAD_BYTES];
	uint8_t type;
	uint8_t flags;
	union k_object_data data;
} __packed __aligned(4);

struct k_object_assignment {
	struct k_thread *thread;
	void * const *objects;
};


/**
 * Lookup a kernel object and init its metadata if it exists
 *
 * Calling this on an object will make it usable from userspace.
 * Intended to be called as the last statement in kernel object init
 * functions.
 *
 * @param obj Address of the kernel object
 *
 * @note This is an internal API. Do not use unless you are extending
 *       functionality in the Zephyr tree.
 */
void k_object_init(const void *obj);


#else
/* LCOV_EXCL_START */
static inline void k_object_init(const void *obj)
{
	ARG_UNUSED(obj);
}
/* LCOV_EXCL_STOP */
#endif /* !CONFIG_USERSPACE */

#ifdef CONFIG_DYNAMIC_OBJECTS
/**
 * Allocate memory and install as a generic kernel object
 *
 * This is a low-level function to allocate some memory, and register that
 * allocated memory in the kernel object lookup tables with type K_OBJ_ANY.
 * Initialization state and thread permissions will be cleared. The
 * returned k_object's data value will be uninitialized.
 *
 * Most users will want to use k_object_alloc() instead.
 *
 * Memory allocated will be drawn from the calling thread's reasource pool
 * and may be freed later by passing the actual object pointer (found
 * in the returned k_object's 'name' member) to k_object_free().
 *
 * @param align Required memory alignment for the allocated object
 * @param size Size of the allocated object
 * @return NULL on insufficient memory
 * @return A pointer to the associated k_object that is installed in the
 *	kernel object tables
 *
 * @note This is an internal API. Do not use unless you are extending
 *       functionality in the Zephyr tree.
 */
struct k_object *k_object_create_dynamic_aligned(size_t align, size_t size);

/**
 * Allocate memory and install as a generic kernel object
 *
 * This is a low-level function to allocate some memory, and register that
 * allocated memory in the kernel object lookup tables with type K_OBJ_ANY.
 * Initialization state and thread permissions will be cleared. The
 * returned k_object's data value will be uninitialized.
 *
 * Most users will want to use k_object_alloc() instead.
 *
 * Memory allocated will be drawn from the calling thread's reasource pool
 * and may be freed later by passing the actual object pointer (found
 * in the returned k_object's 'name' member) to k_object_free().
 *
 * @param size Size of the allocated object
 * @return NULL on insufficient memory
 * @return A pointer to the associated k_object that is installed in the
 *	kernel object tables
 *
 * @note This is an internal API. Do not use unless you are extending
 *       functionality in the Zephyr tree.
 */
static inline struct k_object *k_object_create_dynamic(size_t size)
{
	return k_object_create_dynamic_aligned(0, size);
}

#else

/* LCOV_EXCL_START */
static inline struct k_object *k_object_create_dynamic_aligned(size_t align,
							       size_t size)
{
	ARG_UNUSED(align);
	ARG_UNUSED(size);

	return NULL;
}

static inline struct k_object *k_object_create_dynamic(size_t size)
{
	ARG_UNUSED(size);

	return NULL;
}

/* LCOV_EXCL_STOP */
#endif /* CONFIG_DYNAMIC_OBJECTS */

/** @} */

#ifdef __cplusplus
}
#endif

#endif
