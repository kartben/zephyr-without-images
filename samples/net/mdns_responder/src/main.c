/* main.c - mDNS responder */

/*
 * Copyright (c) 2017 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <logging/log.h>
LOG_MODULE_REGISTER(net_mdns_responder_sample, LOG_LEVEL_DBG);

#include <zephyr.h>
#include <net/net_core.h>

/* Note that this application does not do anything itself.
 * It is just a placeholder for waiting mDNS queries.
 */
void main(void)
{
	NET_INFO("Waiting mDNS queries...");
}
