/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel_structs.h>
#include <cmsis_os.h>

/**
 * @brief Create and Initialize mail queue.
 */
osMailQId osMailCreate(const osMailQDef_t *queue_def, osThreadId thread_id)
{
	if (queue_def == NULL) {
		return NULL;
	}

	if (_is_in_isr()) {
		return NULL;
	}

	k_mbox_init(queue_def->mbox);
	return (osMailQId)(queue_def);
}

/**
 * @brief Allocate a memory block from a mail.
 */
void *osMailAlloc(osMailQId queue_id, uint32_t millisec)
{
	osMailQDef_t *queue_def = (osMailQDef_t *)queue_id;
	char *ptr;
	int retval;

	if (queue_def == NULL) {
		return NULL;
	}

	if (millisec == 0) {
		retval = k_mem_slab_alloc(
				(struct k_mem_slab *)(queue_def->pool),
				(void **)&ptr, K_NO_WAIT);
	} else if (millisec == osWaitForever) {
		retval = k_mem_slab_alloc(
				(struct k_mem_slab *)(queue_def->pool),
				(void **)&ptr, K_FOREVER);
	} else {
		retval = k_mem_slab_alloc(
				(struct k_mem_slab *)(queue_def->pool),
				(void **)&ptr, millisec);
	}

	if (retval == 0) {
		return ptr;
	} else {
		return NULL;
	}
}

/**
 * @brief Allocate a memory block from a mail and set memory block to zero.
 */
void *osMailCAlloc(osMailQId queue_id, uint32_t millisec)
{
	osMailQDef_t *queue_def = (osMailQDef_t *)queue_id;
	char *ptr;
	int retval;

	if (queue_def == NULL) {
		return NULL;
	}

	if (millisec == 0) {
		retval = k_mem_slab_alloc(
				(struct k_mem_slab *)(queue_def->pool),
				(void **)&ptr, K_NO_WAIT);
	} else if (millisec == osWaitForever) {
		retval = k_mem_slab_alloc(
				(struct k_mem_slab *)(queue_def->pool),
				(void **)&ptr, K_FOREVER);
	} else {
		retval = k_mem_slab_alloc(
				(struct k_mem_slab *)(queue_def->pool),
				(void **)&ptr, millisec);
	}

	if (retval == 0) {
		memset(ptr, 0, queue_def->item_sz);
		return ptr;
	} else {
		return NULL;
	}
}

/**
 * @brief Put a mail to a queue.
 */
osStatus osMailPut(osMailQId queue_id, void *mail)
{
	osMailQDef_t *queue_def = (osMailQDef_t *)queue_id;
	struct k_mbox_msg mmsg;

	if (queue_def == NULL) {
		return osErrorParameter;
	}

	memset(&mmsg, 0, sizeof(mmsg));
	mmsg.tx_data = mail;
	mmsg.rx_source_thread = K_ANY;
	mmsg.tx_target_thread = K_ANY;

	if (k_mbox_put(queue_def->mbox, &mmsg, 100) == 0) {
		return osOK;
	} else {
		return osErrorValue;
	}
}

/**
 * @brief Get a mail from a queue.
 */
osEvent osMailGet(osMailQId queue_id, uint32_t millisec)
{
	osMailQDef_t *queue_def = (osMailQDef_t *)queue_id;
	struct k_mbox_msg mmsg;
	osEvent evt;
	int retval;

	if (queue_def == NULL) {
		evt.status = osErrorParameter;
		return evt;
	}

	memset(&mmsg, 0, sizeof(mmsg));
	mmsg.rx_source_thread = K_ANY;
	mmsg.tx_target_thread = K_ANY;

	if (millisec == 0) {
		retval = k_mbox_get(queue_def->mbox, &mmsg, NULL, K_NO_WAIT);
	} else if (millisec == osWaitForever) {
		retval = k_mbox_get(queue_def->mbox, &mmsg, NULL, K_FOREVER);
	} else {
		retval = k_mbox_get(queue_def->mbox, &mmsg, NULL, millisec);
	}

	if (retval == 0) {
		evt.status = osEventMail;
	} else if (retval == -EAGAIN) {
		evt.status = osEventTimeout;
	} else if (retval == -ENOMSG) {
		evt.status = osOK;
	} else {
		evt.status = osErrorValue;
	}

	evt.value.p = mmsg.tx_data;
	evt.def.mail_id = queue_id;

	return evt;
}

/**
 * @brief Free a memory block from a mail.
 */
osStatus osMailFree(osMailQId queue_id, void *mail)
{
	osMailQDef_t *queue_def = (osMailQDef_t *)queue_id;

	k_mem_slab_free((struct k_mem_slab *)(queue_def->pool), (void *) &mail);

	return osOK;
}
