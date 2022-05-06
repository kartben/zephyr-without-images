/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_INCLUDE_POSIX_SEMAPHORE_H_
#define ZEPHYR_INCLUDE_POSIX_SEMAPHORE_H_

#include <zephyr/posix/time.h>
#include "posix_types.h"

#ifdef __cplusplus
extern "C" {
#endif

int sem_destroy(sem_t *semaphore);
int sem_getvalue(sem_t *ZRESTRICT semaphore, int *ZRESTRICT value);
int sem_init(sem_t *semaphore, int pshared, unsigned int value);
int sem_post(sem_t *semaphore);
int sem_timedwait(sem_t *ZRESTRICT semaphore, struct timespec *ZRESTRICT abstime);
int sem_trywait(sem_t *semaphore);
int sem_wait(sem_t *semaphore);

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_POSIX_SEMAPHORE_H_ */
