/*  Minimal DTSL client.
 *  (Meant to be used with config-threadnet.h)
 *
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */

#include <zephyr.h>
#include <stdio.h>

#include <errno.h>
#include <misc/printk.h>

#if !defined(CONFIG_MBEDTLS_CFG_FILE)
#include "mbedtls/config.h"
#else
#include CONFIG_MBEDTLS_CFG_FILE
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdlib.h>
#define mbedtls_time_t       time_t
#define MBEDTLS_EXIT_SUCCESS EXIT_SUCCESS
#define MBEDTLS_EXIT_FAILURE EXIT_FAILURE
#endif

#include <string.h>
#include <net/net_context.h>
#include <net/net_if.h>
#include "udp.h"
#include "udp_cfg.h"

#include "mbedtls/net.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
#include "mbedtls/memory_buffer_alloc.h"
static unsigned char heap[20480];
#endif

#define DEBUG_THRESHOLD 0
/*
 * Hardcoded values for server host and port
 */
#define HOSTNAME "localhost"	/* for cert verification if enabled */

#define GET_REQUEST "GET / HTTP/1.0\r\n\r\n"

const char *pers = "mini_client";

static struct in_addr client_addr = CLIENT_IP_ADDR;

#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
#define ECJPAKE_PW_SIZE 6
const unsigned char ecjpake_pw[ECJPAKE_PW_SIZE] = "passwd";
#endif

enum exit_codes {
	exit_ok = 0,
	ctr_drbg_seed_failed,
	ssl_config_defaults_failed,
	ssl_setup_failed,
	hostname_failed,
	socket_failed,
	connect_failed,
	x509_crt_parse_failed,
	ssl_handshake_failed,
	ssl_write_failed,
};

struct dtls_timing_context {
	uint32_t snapshot;
	uint32_t int_ms;
	uint32_t fin_ms;
};

static void my_debug(void *ctx, int level,
		     const char *file, int line, const char *str)
{
	const char *p, *basename;

	/* Extract basename from file */
	for (p = basename = file; *p != '\0'; p++) {
		if (*p == '/' || *p == '\\') {
			basename = p + 1;
		}
	}
	mbedtls_printf("%s:%04d: |%d| %s", basename, line, level, str);
}

void dtls_timing_set_delay(void *data, uint32_t int_ms, uint32_t fin_ms)
{
	struct dtls_timing_context *ctx = (struct dtls_timing_context *)data;

	ctx->int_ms = int_ms;
	ctx->fin_ms = fin_ms;

	if (fin_ms != 0) {
		ctx->snapshot = _do_read_cpu_timestamp32();
	}
}

int dtls_timing_get_delay(void *data)
{
	struct dtls_timing_context *ctx = (struct dtls_timing_context *)data;
	unsigned long elapsed_ms;

	if (ctx->fin_ms == 0) {
		return -1;
	}

	elapsed_ms = ((_do_read_cpu_timestamp32() - ctx->snapshot) * 1000) /
	    CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC;

	if (elapsed_ms >= ctx->fin_ms)
		return 2;

	if (elapsed_ms >= ctx->int_ms)
		return 1;
	return 0;
}

static int entropy_source(void *data, unsigned char *output, size_t len,
			  size_t *olen)
{
	uint32_t seed;
	char *ptr = data;

	seed = sys_rand32_get();

	if (!seed) {
		seed = 7;
	}

	for (int i = 0; i < len; i++) {
		seed ^= seed << 13;
		seed ^= seed >> 17;
		seed ^= seed << 5;
		*ptr++ = (char)seed;
	}
	*olen = len;
	return 0;
}

void dtls_client(void)
{
	int ret = exit_ok;
	struct udp_context ctx;
	struct dtls_timing_context timer;

	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr_drbg;
	mbedtls_ssl_context ssl;
	mbedtls_ssl_config conf;

	mbedtls_ctr_drbg_init(&ctr_drbg);

	mbedtls_platform_set_printf(printk);

	/*
	 * 0. Initialize and setup stuff
	 */
	mbedtls_ssl_init(&ssl);
	mbedtls_ssl_config_init(&conf);

	mbedtls_printf("\n  . Seeding the random number generator...");
	mbedtls_entropy_init(&entropy);
	mbedtls_entropy_add_source(&entropy, entropy_source, NULL,
				   MBEDTLS_ENTROPY_MAX_GATHER,
				   MBEDTLS_ENTROPY_SOURCE_STRONG);

	if (mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy,
				  (const unsigned char *)pers,
				  strlen(pers)) != 0) {
		ret = ctr_drbg_seed_failed;
		mbedtls_printf
		    (" failed\n  ! mbedtls_ctr_drbg_seed returned 0x%x\n", ret);
		goto exit;
	}
	mbedtls_printf(" ok\n");

	mbedtls_printf("  . Setting up the DTLS structure...");
	ret = mbedtls_ssl_config_defaults(&conf,
					MBEDTLS_SSL_IS_CLIENT,
					MBEDTLS_SSL_TRANSPORT_DATAGRAM,
					MBEDTLS_SSL_PRESET_DEFAULT);
	if (ret != 0) {
		ret = ssl_config_defaults_failed;
		mbedtls_printf(" failed! returned 0x%x\n\n", ret);
		goto exit;
	}

/* Modify this to change the default timeouts for the DTSL handshake */
/*        mbedtls_ssl_conf_handshake_timeout( &conf, min, max ); */

#if defined(MBEDTLS_DEBUG_C)
	mbedtls_debug_set_threshold(DEBUG_THRESHOLD);
#endif

	mbedtls_ssl_conf_rng(&conf, mbedtls_ctr_drbg_random, &ctr_drbg);
	mbedtls_ssl_conf_dbg(&conf, my_debug, NULL);

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
	mbedtls_memory_buffer_alloc_init(heap, sizeof(heap));
#endif

	if (mbedtls_ssl_setup(&ssl, &conf) != 0) {
		ret = ssl_setup_failed;
		mbedtls_printf
		    (" failed\n  ! mbedtls_ssl_setup returned 0x%x\n\n", ret);
		goto exit;
	}

	mbedtls_printf(" ok\n");

	/*
	 * 1. Start the connection
	 */

	mbedtls_printf("  . Connecting to udp %d.%d.%d.%d:%d...",
		       SERVER_IPADDR0, SERVER_IPADDR1, SERVER_IPADDR2,
		       SERVER_IPADDR3, SERVER_PORT);

	if (udp_init(&ctx) != 0) {
		ret = connect_failed;
		mbedtls_printf(" failed\n  ! udp_init returned 0x%x\n\n", ret);
		goto exit;
	}

	mbedtls_printf(" ok\n");

#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
	mbedtls_printf("  . Setting up ecjpake password ...");
	if (mbedtls_ssl_set_hs_ecjpake_password
	    (&ssl, ecjpake_pw, ECJPAKE_PW_SIZE) != 0) {
		mbedtls_printf(" failed! set ecjpake password returned %d\n\n",
			       ssl_setup_failed);
		goto exit;
	}
#endif
	mbedtls_printf(" ok\n");

	mbedtls_ssl_set_timer_cb(&ssl, &timer, dtls_timing_set_delay,
				 dtls_timing_get_delay);

	mbedtls_ssl_set_bio(&ssl, &ctx, udp_tx, udp_rx, NULL);

	mbedtls_printf("  . Performing the SSL/TLS handshake...");
	ret = mbedtls_ssl_handshake(&ssl);
	if (ret != 0) {
		ret = ssl_handshake_failed;
		mbedtls_printf
		    (" failed\n  ! mbedtls_ssl_handshake returned 0x%x\n", ret);
		goto exit;
	}
	mbedtls_printf(" ok\n");

	/*
	 * 2. Write the GET request and close the connection
	 */
	mbedtls_printf("  > Write to server:");
	if (mbedtls_ssl_write(&ssl, (const unsigned char *)GET_REQUEST,
			      sizeof(GET_REQUEST) - 1) <= 0) {
		ret = ssl_write_failed;
		mbedtls_printf
		    (" failed\n  ! mbedtls_ssl_write returned 0x%x\n\n", ret);
		goto exit;
	}
	mbedtls_printf(" ok\n");

	mbedtls_printf("  . Closing the connection...");
	mbedtls_ssl_close_notify(&ssl);
	mbedtls_printf(" done\n");
exit:

	mbedtls_ssl_free(&ssl);
	mbedtls_ssl_config_free(&conf);
	mbedtls_ctr_drbg_free(&ctr_drbg);
	mbedtls_entropy_free(&entropy);
}

#define STACK_SIZE		8192
uint8_t stack[STACK_SIZE];

static inline int init_app(void)
{
	if (!net_if_ipv4_addr_add(net_if_get_default(), &client_addr,
				  NET_ADDR_MANUAL, 0)) {
		return -EIO;
	}
	return 0;
}

void main(void)
{
	if (init_app() != 0) {
		printf("Cannot initialize network\n");
		return;
	}

	k_thread_spawn(stack, STACK_SIZE, (k_thread_entry_t) dtls_client,
			NULL, NULL, NULL, K_PRIO_COOP(7), 0, 0);

}
