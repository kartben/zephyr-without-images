/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ztest.h>
#include <kernel.h>
#include <cmsis_os2.h>

#include <irq_offload.h>
#include <kernel_structs.h>

#define TIMEOUT_TICKS	(100)
#define FLAG1		(0x00000020)
#define FLAG2		(0x00000004)
#define FLAG		(FLAG1 | FLAG2)
#define ISR_FLAG	0x50
#define STACKSZ		512

osEventFlagsId_t evt_id;

static void thread1(void *arg)
{
	int flags = osEventFlagsSet((osEventFlagsId_t)arg, FLAG1);

	zassert_equal(flags & FLAG1, FLAG1, "");
}

static void thread2(void *arg)
{
	int flags = osEventFlagsSet((osEventFlagsId_t)arg, FLAG2);

	/* Please note that as soon as the last flag that a thread is waiting
	 * on is set, the control shifts to that thread and that thread may
	 * choose to clear the flags as part of its osEventFlagsWait operation.
	 * In this test case, the main thread is waiting for FLAG1 and FLAG2.
	 * FLAG1 gets set first and then FLAG2 gets set. As soon as FLAG2 gets
	 * set, control shifts to the waiting thread where osEventFlagsWait
	 * clears FLAG1 and FLAG2 internally. When this thread eventually gets
	 * scheduled we should hence check if FLAG2 is cleared.
	 */
	zassert_equal(flags & FLAG2, 0, "");
}

static K_THREAD_STACK_DEFINE(test_stack1, STACKSZ);
static osThreadAttr_t thread1_attr = {
	.name       = "Thread1",
	.stack_mem  = &test_stack1,
	.stack_size = STACKSZ,
	.priority   = osPriorityHigh,
};

static K_THREAD_STACK_DEFINE(test_stack2, STACKSZ);
static osThreadAttr_t thread2_attr = {
	.name       = "Thread2",
	.stack_mem  = &test_stack2,
	.stack_size = STACKSZ,
	.priority   = osPriorityHigh,
};

static osEventFlagsAttr_t event_flags_attrs = {
	.name = "MyEvent",
	.attr_bits = 0,
	.cb_mem = NULL,
	.cb_size = 0,
};

void test_event_flags_no_wait_timeout(void)
{
	osThreadId_t id1;
	u32_t flags;
	const char *name;

	evt_id = osEventFlagsNew(&event_flags_attrs);
	zassert_true(evt_id != NULL, "Failed creating event flags");

	name = osEventFlagsGetName(evt_id);
	zassert_true(strcmp(event_flags_attrs.name, name) == 0,
			"Error getting event_flags object name");

	id1 = osThreadNew(thread1, evt_id, &thread1_attr);
	zassert_true(id1 != NULL, "Failed creating thread1");

	/* Let id1 run to trigger FLAG1 */
	osDelay(2);

	/* wait for FLAG1. It should return immediately as it is
	 * already triggered.
	 */
	flags = osEventFlagsWait(evt_id, FLAG1,
				osFlagsWaitAny | osFlagsNoClear, 0);
	zassert_equal(flags & FLAG1, FLAG1, "");

	/* Since the flags are not cleared automatically in the previous step,
	 * we should be able to get the same flags upon query below.
	 */
	flags = osEventFlagsGet(evt_id);
	zassert_equal(flags & FLAG1, FLAG1, "");

	/* Clear the Flag explicitly */
	flags = osEventFlagsClear(evt_id, FLAG1);
	zassert_not_equal(flags, osFlagsErrorParameter, "Event clear failed");

	/* wait for FLAG1. It should timeout here as the event
	 * though triggered, gets cleared in the previous step.
	 */
	flags = osEventFlagsWait(evt_id, FLAG1, osFlagsWaitAny, TIMEOUT_TICKS);
	zassert_equal(flags, osFlagsErrorTimeout, "EventFlagsWait failed");
}

void test_event_flags_signalled(void)
{
	osThreadId_t id1, id2;
	u32_t flags;

	id1 = osThreadNew(thread1, evt_id, &thread1_attr);
	zassert_true(id1 != NULL, "Failed creating thread1");

	id2 = osThreadNew(thread2, evt_id, &thread2_attr);
	zassert_true(id2 != NULL, "Failed creating thread2");

	/* wait for multiple flags. The flags will be cleared automatically
	 * upon being set since "osFlagsNoClear" is not opted for.
	 */
	flags = osEventFlagsWait(evt_id, FLAG, osFlagsWaitAll, TIMEOUT_TICKS);
	zassert_equal(flags & FLAG, FLAG,
		      "osEventFlagsWait failed unexpectedly");

	/* set any single flag */
	flags = osEventFlagsSet(evt_id, FLAG1);
	zassert_equal(flags & FLAG1, FLAG1, "set any flag failed");

	flags = osEventFlagsWait(evt_id, FLAG1, osFlagsWaitAny, TIMEOUT_TICKS);
	zassert_equal(flags & FLAG1, FLAG1,
		      "osEventFlagsWait failed unexpectedly");

	/* validate by passing invalid parameters */
	zassert_equal(osEventFlagsSet(NULL, 0), osFlagsErrorParameter,
			"Invalid event Flags ID is unexpectedly working!");
	zassert_equal(osEventFlagsSet(evt_id, 0x80010000),
				osFlagsErrorParameter,
				"Event with MSB set is set unexpectedly");

	zassert_equal(osEventFlagsClear(NULL, 0), osFlagsErrorParameter,
			"Invalid event Flags ID is unexpectedly working!");
	zassert_equal(osEventFlagsClear(evt_id, 0x80010000),
				osFlagsErrorParameter,
				"Event with MSB set is cleared unexpectedly");

	/* cannot wait for Flag mask with MSB set */
	zassert_equal(osEventFlagsWait(evt_id, 0x80010000, osFlagsWaitAny, 0),
					osFlagsErrorParameter,
					"EventFlagsWait passed unexpectedly");
}

/* IRQ offload function handler to set event flag */
static void offload_function(void *param)
{
	int flags;

	/* Make sure we're in IRQ context */
	zassert_true(k_is_in_isr(), "Not in IRQ context!");

	flags = osEventFlagsSet((osEventFlagsId_t)param, ISR_FLAG);
	zassert_equal(flags & ISR_FLAG, ISR_FLAG,
				"EventFlagsSet failed in ISR");
}

void test_event_from_isr(void *event_id)
{
	/**TESTPOINT: Offload to IRQ context*/
	irq_offload(offload_function, (void *)event_id);
}

static K_THREAD_STACK_DEFINE(test_stack3, STACKSZ);
static osThreadAttr_t thread3_attr = {
	.name       = "Thread3",
	.stack_mem  = &test_stack3,
	.stack_size = STACKSZ,
	.priority   = osPriorityHigh,
};

void test_event_flags_isr(void)
{
	osThreadId_t id;
	int flags;

	id = osThreadNew(test_event_from_isr, evt_id, &thread3_attr);
	zassert_true(id != NULL, "Failed creating thread");

	flags = osEventFlagsWait(evt_id, ISR_FLAG,
					osFlagsWaitAll, TIMEOUT_TICKS);
	zassert_equal((flags & ISR_FLAG),
		       ISR_FLAG, "unexpected event flags value");

	zassert_true(osEventFlagsDelete(evt_id) == osOK,
			"EventFlagsDelete failed");
}
