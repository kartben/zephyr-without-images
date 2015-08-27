/*
 * Copyright (c) 2015 Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1) Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3) Neither the name of Intel Corporation nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * @file
 * @brief Event logger support.
 */

#include <misc/event_logger.h>
#include <misc/ring_buffer.h>

void sys_event_logger_init(struct event_logger *logger,
	uint32_t *logger_buffer, uint32_t buffer_size)
{
	sys_ring_buf_init(&logger->ring_buf, buffer_size, logger_buffer);
	nano_sem_init(&(logger->sync_sema));
}


static void event_logger_put(struct event_logger *logger, uint16_t event_id,
	uint32_t *event_data, uint8_t data_size,
	void(*sem_give_fn)(struct nano_sem *))
{
	int ret;
	unsigned int key;

	key = irq_lock();

	ret = sys_ring_buf_put(&logger->ring_buf, event_id,
			       logger->ring_buf.dropped_put_count, event_data,
			       data_size);
	if (ret == 0) {
		logger->ring_buf.dropped_put_count = 0;
		/* inform that there is event data available on the buffer */
		sem_give_fn(&(logger->sync_sema));
	}
	irq_unlock(key);
}


void sys_event_logger_put(struct event_logger *logger, uint16_t event_id,
	uint32_t *event_data, uint8_t data_size)
{
	event_logger_put(logger, event_id, event_data, data_size, nano_sem_give);
}


/**
 * @brief Send an event message to the logger with a non preemptible
 * behaviour.
 *
 * @details Add an event message to the ring buffer and signal the sync
 * semaphore using the internal function _sem_give_non_preemptible to inform
 * that there are event messages available, avoiding the preemptible
 * behaviour when the function is called from a task. This function
 * should be only used for special cases where the sys_event_logger_put
 * does not satisfy the needs.
 *
 * @param logger     Pointer to the event logger used.
 * @param event_id   The identification of the profiler event.
 * @param data       Pointer to the data of the message.
 * @param data_size  Size of the buffer in 32-bit words.
 *
 * @return No return value.
 */
void _sys_event_logger_put_non_preemptible(struct event_logger *logger,
	uint16_t event_id, uint32_t *event_data, uint8_t data_size)
{
	extern void _sem_give_non_preemptible(struct nano_sem *sem);

	event_logger_put(logger, event_id, event_data, data_size,
		_sem_give_non_preemptible);
}


static int event_logger_get(struct event_logger *logger,
			    uint16_t *event_id, uint8_t *dropped_event_count,
			    uint32_t *buffer, uint8_t *buffer_size)
{
	int ret;

	ret = sys_ring_buf_get(&logger->ring_buf, event_id, dropped_event_count,
			       buffer, buffer_size);
	if (likely(!ret)) {
		return *buffer_size;
	}
	switch (ret) {
	case -EMSGSIZE:
		/* if the user can not retrieve the message, we increase the
		 *  semaphore to indicate that the message remains in the buffer
		 */
		nano_fiber_sem_give(&(logger->sync_sema));
		return -EMSGSIZE;
	case -EAGAIN:
		return 0;
	default:
		return ret;
	}
}


int sys_event_logger_get(struct event_logger *logger, uint16_t *event_id,
			 uint8_t *dropped_event_count, uint32_t *buffer,
			 uint8_t *buffer_size)
{
	if (nano_fiber_sem_take(&(logger->sync_sema))) {
		return event_logger_get(logger, event_id, dropped_event_count,
					buffer, buffer_size);
	}
	return 0;
}


int sys_event_logger_get_wait(struct event_logger *logger,  uint16_t *event_id,
			      uint8_t *dropped_event_count, uint32_t *buffer,
			      uint8_t *buffer_size)
{
	nano_fiber_sem_take_wait(&(logger->sync_sema));

	return event_logger_get(logger, event_id, dropped_event_count, buffer,
				buffer_size);
}


#ifdef CONFIG_NANO_TIMEOUTS
int sys_event_logger_get_wait_timeout(struct event_logger *logger,
				      uint16_t *event_id,
				      uint8_t *dropped_event_count,
				      uint32_t *buffer, uint8_t *buffer_size,
				      uint32_t timeout)
{
	if (nano_fiber_sem_take_wait_timeout(&(logger->sync_sema), timeout)) {
		return event_logger_get(logger, event_id, dropped_event_count,
					buffer, buffer_size);
	}
	return 0;
}
#endif /* CONFIG_NANO_TIMEOUTS */
