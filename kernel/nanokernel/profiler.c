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
 * @brief Profiler support.
 */


#include <misc/profiler.h>
#include <misc/util.h>
#include <init.h>
#include <nano_private.h>
#include <profiler_arch.h>

uint32_t _sys_profiler_buffer[CONFIG_PROFILER_BUFFER_SIZE];

#ifdef CONFIG_PROFILER_CONTEXT_SWITCH
void *_collector_fiber=NULL;
#endif

#ifdef CONFIG_PROFILER_SLEEP
uint32_t _sys_profiler_sleep_start_time;
#endif


/**
 * @brief Initialize the profiler system.
 *
 * @details Initialize the ring buffer and the sync semaphore.
 *
 * @return No return value.
 */
static int _sys_profiler_init(struct device *arg)
{
	ARG_UNUSED(arg);

	sys_event_logger_init(&sys_profiler_logger, _sys_profiler_buffer,
		CONFIG_PROFILER_BUFFER_SIZE);

	return 0;
}
DECLARE_DEVICE_INIT_CONFIG(profiler_0, "", _sys_profiler_init, NULL);
nano_early_init(profiler_0, NULL);


void sys_profiler_put_timed(uint16_t event_id)
{
	uint32_t data[1];

	data[0] = nano_tick_get_32();

	sys_event_logger_put(&sys_profiler_logger, event_id, data,
		ARRAY_SIZE(data));
}

#ifdef CONFIG_PROFILER_CONTEXT_SWITCH
void _sys_profiler_context_switch(void)
{
	extern tNANO _nanokernel;
	uint32_t data[2];
	extern void _sys_event_logger_put_non_preemptible(
		struct event_logger *logger, uint16_t event_id, uint32_t *event_data,
		uint8_t data_size);

	/* if the profiler has not been initialized, we do nothing */
	if (sys_profiler_logger.ring_buf.buf == NULL) {
		return;
	}

	if (_collector_fiber != _nanokernel.current) {
		data[0] = nano_tick_get_32();
		data[1] = (uint32_t)_nanokernel.current;

		/*
		 * The mechanism we use to log the profile events uses a sync semaphore
		 * to inform that there are available events to be collected. The
		 * context switch event can be triggered from a task. When we
		 * signal a semaphore from a task and a fiber is waiting for
		 * that semaphore, a context switch is generated immediately. Due to
		 * the fact that we register the context switch event while the context
		 * switch is being processed, a new context switch can be generated
		 * before the kernel finishes processing the current context switch. We
		 * need to prevent this because the kernel is not able to handle it.
		 * The _sem_give_non_preemptible function does not trigger a context
		 * switch when we signal the semaphore from any type of thread. Using
		 * _sys_event_logger_put_non_preemptible function, that internally uses
		 * _sem_give_non_preemptible function for signaling the sync semaphore,
		 * allow us registering the context switch event without triggering any
		 * new context switch during the process.
		 */
		_sys_event_logger_put_non_preemptible(&sys_profiler_logger,
			PROFILER_CONTEXT_SWITCH_EVENT_ID, data, ARRAY_SIZE(data));
	}
}

void sys_profiler_register_as_collector(void)
{
	_collector_fiber = _nanokernel.current;
}
#endif /* CONFIG_PROFILER_CONTEXT_SWITCH */


#ifdef CONFIG_PROFILER_INTERRUPT
void _sys_profiler_interrupt()
{
	uint32_t data[2];

	data[0] = nano_tick_get_32();
	data[1] = _sys_current_irq_key_get();

	sys_profiler_put(PROFILER_INTERRUPT_EVENT_ID, data, ARRAY_SIZE(data));
}
#endif /* CONFIG_PROFILER_INTERRUPT */


#ifdef CONFIG_PROFILER_SLEEP
void _sys_profiler_enter_sleep(void)
{
	_sys_profiler_sleep_start_time = nano_cycle_get_32();
}

void _sys_profiler_exit_sleep(void)
{
	uint32_t data[3];

	data[0] = nano_tick_get_32();
	data[1] = (nano_cycle_get_32() - _sys_profiler_sleep_start_time) / sys_clock_hw_cycles_per_tick;
	/* register the cause of exiting sleep mode */
	data[2] = _sys_current_irq_key_get();

	sys_profiler_put(PROFILER_SLEEP_EVENT_ID, data, ARRAY_SIZE(data));
}
#endif /* CONFIG_PROFILER_SLEEP */
