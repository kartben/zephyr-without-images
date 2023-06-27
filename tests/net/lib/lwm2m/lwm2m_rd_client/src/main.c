/*
 * Copyright (c) 2022 grandcentrix GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "stubs.h"

#include <zephyr/fff.h>
#include <zephyr/logging/log.h>
#include <zephyr/ztest.h>
#if defined(CONFIG_NATIVE_POSIX_SLOWDOWN_TO_REAL_TIME)
#include "timer_model.h"
#endif
#include <lwm2m_rd_client.h>

LOG_MODULE_REGISTER(lwm2m_rd_client_test);

DEFINE_FFF_GLOBALS;

/* Maximum number of iterations within the state machine of RD Client
 * service that is waited for until a possible event occurs
 */
static const uint8_t RD_CLIENT_MAX_LOOKUP_ITERATIONS = 100;

FAKE_VOID_FUNC(show_lwm2m_event, enum lwm2m_rd_client_event);
FAKE_VOID_FUNC(show_lwm2m_observe, enum lwm2m_observe_event);

bool check_lwm2m_rd_client_event(uint8_t expected_val, uint8_t arg_index)
{
	int max_service_iterations = RD_CLIENT_MAX_LOOKUP_ITERATIONS;
	bool match = false;

	while (max_service_iterations > 0) {
		if (show_lwm2m_event_fake.call_count > arg_index) {
			match = show_lwm2m_event_fake.arg0_history[arg_index] == expected_val;
			break;
		}

		wait_for_service(1);
		max_service_iterations--;
	}

	if (!match) {
		LOG_INF("Expecting %d at %d, events:", expected_val, arg_index);
		for (int i = 0; i < show_lwm2m_event_fake.call_count; i++) {
			LOG_INF("[%d] = %d", i, show_lwm2m_event_fake.arg0_history[i]);
		}
	}

	return match;
}

bool check_lwm2m_observe_event(uint8_t expected_val, uint8_t arg_index)
{
	int max_service_iterations = RD_CLIENT_MAX_LOOKUP_ITERATIONS;

	while (max_service_iterations > 0) {
		if (show_lwm2m_observe_fake.call_count > arg_index) {
			return show_lwm2m_observe_fake.arg0_history[arg_index] == expected_val;
		}

		wait_for_service(1);
		max_service_iterations--;
	}

	return false;
}

static void lwm2m_event_cb(struct lwm2m_ctx *client, enum lwm2m_rd_client_event client_event)
{
	ARG_UNUSED(client);

	switch (client_event) {
	case LWM2M_RD_CLIENT_EVENT_NONE:
		LOG_INF("*** LWM2M_RD_CLIENT_EVENT_NONE");
		break;
	case LWM2M_RD_CLIENT_EVENT_BOOTSTRAP_REG_FAILURE:
		LOG_INF("*** LWM2M_RD_CLIENT_EVENT_BOOTSTRAP_REG_FAILURE");
		break;
	case LWM2M_RD_CLIENT_EVENT_BOOTSTRAP_REG_COMPLETE:
		LOG_INF("*** LWM2M_RD_CLIENT_EVENT_BOOTSTRAP_REG_COMPLETE");
		break;
	case LWM2M_RD_CLIENT_EVENT_BOOTSTRAP_TRANSFER_COMPLETE:
		LOG_INF("*** LWM2M_RD_CLIENT_EVENT_BOOTSTRAP_TRANSFER_COMPLETE");
		break;
	case LWM2M_RD_CLIENT_EVENT_REGISTRATION_FAILURE:
		LOG_INF("*** LWM2M_RD_CLIENT_EVENT_REGISTRATION_FAILURE");
		break;
	case LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE:
		LOG_INF("*** LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE");
		break;
	case LWM2M_RD_CLIENT_EVENT_REG_TIMEOUT:
		LOG_INF("*** LWM2M_RD_CLIENT_EVENT_REG_TIMEOUT");
		break;
	case LWM2M_RD_CLIENT_EVENT_REG_UPDATE_COMPLETE:
		LOG_INF("*** LWM2M_RD_CLIENT_EVENT_REG_UPDATE_COMPLETE");
		break;
	case LWM2M_RD_CLIENT_EVENT_DEREGISTER_FAILURE:
		LOG_INF("*** LWM2M_RD_CLIENT_EVENT_DEREGISTER_FAILURE");
		break;
	case LWM2M_RD_CLIENT_EVENT_DISCONNECT:
		LOG_INF("*** LWM2M_RD_CLIENT_EVENT_DISCONNECT");
		break;
	case LWM2M_RD_CLIENT_EVENT_QUEUE_MODE_RX_OFF:
		LOG_INF("*** LWM2M_RD_CLIENT_EVENT_QUEUE_MODE_RX_OFF");
		break;
	case LWM2M_RD_CLIENT_EVENT_ENGINE_SUSPENDED:
		LOG_INF("*** LWM2M_RD_CLIENT_EVENT_ENGINE_SUSPENDED");
		break;
	case LWM2M_RD_CLIENT_EVENT_NETWORK_ERROR:
		LOG_INF("*** LWM2M_RD_CLIENT_EVENT_NETWORK_ERROR");
		break;
	case LWM2M_RD_CLIENT_EVENT_REG_UPDATE:
		LOG_INF("*** LWM2M_RD_CLIENT_EVENT_REG_UPDATE");
		break;
	}

	show_lwm2m_event(client_event);
}

static void lwm2m_observe_cb(enum lwm2m_observe_event event, struct lwm2m_obj_path *path,
			     void *user_data)
{
	switch (event) {
	case LWM2M_OBSERVE_EVENT_OBSERVER_ADDED:
		LOG_INF("**** LWM2M_OBSERVE_EVENT_OBSERVER_ADDED");
		break;
	case LWM2M_OBSERVE_EVENT_NOTIFY_TIMEOUT:
		LOG_INF("**** LWM2M_OBSERVE_EVENT_NOTIFY_TIMEOUT");
		break;
	case LWM2M_OBSERVE_EVENT_OBSERVER_REMOVED:
		LOG_INF("**** LWM2M_OBSERVE_EVENT_OBSERVER_REMOVED");
		break;
	case LWM2M_OBSERVE_EVENT_NOTIFY_ACK:
		LOG_INF("**** LWM2M_OBSERVE_EVENT_NOTIFY_ACK");
		break;
	default:
		break;
	}

	show_lwm2m_observe(event);
}

#define FFF_FAKES_LIST(FAKE)

static void my_suite_before(void *data)
{
#if defined(CONFIG_NATIVE_POSIX_SLOWDOWN_TO_REAL_TIME)
	/* It is enough that some slow-down is happening on sleeps, it does not have to be
	 * real time
	 */
	hwtimer_set_rt_ratio(100.0);
#endif
	/* Register resets */
	DO_FOREACH_FAKE(RESET_FAKE);

	/* reset common FFF internal structures */
	FFF_RESET_HISTORY();

	RESET_FAKE(show_lwm2m_event);
	RESET_FAKE(show_lwm2m_observe);
}

static void my_suite_after(void *data)
{
	test_lwm2m_engine_stop_service();
}

void message_reply_cb_default(struct lwm2m_message *msg)
{
	struct coap_packet response;
	struct coap_reply reply;
	struct sockaddr from;

	memset(&response, 0, sizeof(struct coap_packet));
	memset(&reply, 0, sizeof(struct coap_reply));
	memset(&from, 0, sizeof(struct sockaddr));

	msg->reply_cb(&response, &reply, &from);
}

void message_reply_timeout_cb_default(struct lwm2m_message *msg)
{
	msg->message_timeout_cb(msg);
}

ZTEST_SUITE(lwm2m_rd_client, NULL, NULL, my_suite_before, my_suite_after, NULL);

ZTEST(lwm2m_rd_client, test_start_registration_ok)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert(lwm2m_rd_client_ctx() == &ctx, "");
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 0),
		     NULL);
	zassert_true(lwm2m_rd_client_is_registred(&ctx), NULL);

	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_deleted;
	zassert_true(lwm2m_rd_client_stop(&ctx, lwm2m_event_cb, true) == 0, NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_DISCONNECT, 1), NULL);
	zassert_true(!lwm2m_rd_client_is_registred(&ctx), NULL);
}

ZTEST(lwm2m_rd_client, test_register_update_too_small_lifetime_to_default)
{
	struct lwm2m_ctx ctx;

	get_u32_val = CONFIG_LWM2M_ENGINE_DEFAULT_LIFETIME / 2;
	lwm2m_get_u32_fake.custom_fake = lwm2m_get_u32_val;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_engine_add_service_fake.custom_fake = lwm2m_engine_add_service_fake_default;
	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert(lwm2m_rd_client_ctx() == &ctx, "");
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 0),
		     NULL);
	zassert_equal(lwm2m_set_u32_fake.arg1_val, CONFIG_LWM2M_ENGINE_DEFAULT_LIFETIME);
}

ZTEST(lwm2m_rd_client, test_timeout_resume_registration)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert(lwm2m_rd_client_ctx() == &ctx, "");
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 0),
		     NULL);

	zassert(lwm2m_rd_client_timeout(&ctx) == 0, "");
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 1),
		     NULL);

}

ZTEST(lwm2m_rd_client, test_start_registration_timeout)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_timeout_cb_default);

	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_DISCONNECT, 0), NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REG_TIMEOUT, 1), NULL);
}

ZTEST(lwm2m_rd_client, test_start_registration_fail)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_FAILURE, 0),
		     NULL);
}

ZTEST(lwm2m_rd_client, test_start_registration_update)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 0),
		     NULL);

	lwm2m_rd_client_update();
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REG_UPDATE_COMPLETE, 2),
		     NULL);
}

ZTEST(lwm2m_rd_client, test_rx_off)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 0),
		     NULL);

	engine_update_tx_time();
	k_sleep(K_SECONDS(15));
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_QUEUE_MODE_RX_OFF, 1),
		     NULL);
}

ZTEST(lwm2m_rd_client, test_start_registration_update_fail)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 0),
		     NULL);

	RESET_FAKE(coap_header_get_code);

	lwm2m_rd_client_update();
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_FAILURE, 2),
		     NULL);
}

ZTEST(lwm2m_rd_client, test_registration_update_timeout)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 0),
		     NULL);

	test_prepare_pending_message_cb(&message_reply_timeout_cb_default);
	ctx.sock_fd = 100;
	lwm2m_rd_client_update();
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REG_UPDATE, 1));
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REG_TIMEOUT, 2),
		     NULL);
	zassert_equal(lwm2m_engine_stop_fake.call_count, 2);
	zassert_equal(lwm2m_engine_stop_fake.arg0_val, &ctx);

	test_prepare_pending_message_cb(&message_reply_cb_default);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 3),
		     NULL);
}

ZTEST(lwm2m_rd_client, test_deregistration_timeout)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 0),
		     NULL);

	test_prepare_pending_message_cb(&message_reply_timeout_cb_default);
	zassert_true(lwm2m_rd_client_stop(&ctx, lwm2m_event_cb, true) == 0, NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_DEREGISTER_FAILURE, 1));
}

ZTEST(lwm2m_rd_client, test_error_on_registration_update)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	coap_packet_append_option_fake.custom_fake = NULL;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 0),
		     NULL);

	coap_packet_append_option_fake.custom_fake = coap_packet_append_option_fake_err;
	lwm2m_rd_client_update();
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 3),
		     NULL);
}

ZTEST(lwm2m_rd_client, test_network_error_on_registration)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	coap_packet_append_option_fake.custom_fake = coap_packet_append_option_fake_err;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	wait_for_service(100);

	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_NETWORK_ERROR, 0), NULL);
}

ZTEST(lwm2m_rd_client, test_suspend_resume_registration)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	get_u32_val = CONFIG_LWM2M_ENGINE_DEFAULT_LIFETIME;
	lwm2m_get_u32_fake.custom_fake = lwm2m_get_u32_val;
	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 0),
		     NULL);
	zassert_true(!lwm2m_rd_client_is_suspended(&ctx), NULL);

	zassert_true(lwm2m_rd_client_pause() == 0, NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_ENGINE_SUSPENDED, 1), NULL);
	zassert_true(lwm2m_rd_client_is_suspended(&ctx), NULL);

	zassert_true(lwm2m_rd_client_resume() == 0, NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REG_UPDATE_COMPLETE, 3),
		     NULL);
	zassert_true(!lwm2m_rd_client_is_suspended(&ctx), NULL);

	zassert_true(lwm2m_rd_client_pause() == 0, NULL);
	k_sleep(K_SECONDS(CONFIG_LWM2M_ENGINE_DEFAULT_LIFETIME));
	zassert_true(lwm2m_rd_client_resume() == 0, NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 7),
		     NULL);
}

ZTEST(lwm2m_rd_client, test_suspend_stop_resume)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_engine_add_service_fake.custom_fake = lwm2m_engine_add_service_fake_default;
	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	get_u32_val = CONFIG_LWM2M_ENGINE_DEFAULT_LIFETIME;
	lwm2m_get_u32_fake.custom_fake = lwm2m_get_u32_val;
	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 0),
		     NULL);
	zassert_true(lwm2m_rd_client_pause() == 0, NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_ENGINE_SUSPENDED, 2), NULL);

	zassert_equal(lwm2m_rd_client_stop(&ctx, lwm2m_event_cb, false), 0);
	zassert_true(lwm2m_rd_client_resume() == 0, NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_DISCONNECT, 3), NULL);
}

ZTEST(lwm2m_rd_client, test_socket_error)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 0),
		     NULL);

	ctx.fault_cb(EIO);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REG_UPDATE, 1), NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REG_UPDATE_COMPLETE, 2),
		     NULL);
}

ZTEST(lwm2m_rd_client, test_socket_error_on_stop)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_engine_add_service_fake.custom_fake = lwm2m_engine_add_service_fake_default;
	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 0),
		     NULL);

	test_prepare_pending_message_cb(NULL);
	zassert_equal(lwm2m_rd_client_stop(&ctx, lwm2m_event_cb, true), 0);
	k_msleep(1000);
	ctx.fault_cb(EIO);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_DEREGISTER_FAILURE, 2),
		     NULL);
}

ZTEST(lwm2m_rd_client, test_no_context)
{
	struct lwm2m_ctx ctx;

	lwm2m_rd_client_init();
	zassert_equal(lwm2m_rd_client_stop(&ctx, NULL, false), -EPERM);
	zassert_equal(lwm2m_rd_client_pause(), -EPERM);
	zassert_equal(lwm2m_rd_client_resume(), -EPERM);
	zassert_equal(lwm2m_rd_client_connection_resume(&ctx), -EPERM);
	zassert_equal(lwm2m_rd_client_timeout(&ctx), -EPERM);
}

ZTEST(lwm2m_rd_client, test_engine_trigger_bootstrap)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_engine_add_service_fake.custom_fake = lwm2m_engine_add_service_fake_default;
	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 0, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 0),
		     NULL);
	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_true;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_changed;
	zassert_equal(engine_trigger_bootstrap(), 0);
	zassert_equal(engine_trigger_bootstrap(), -EPERM);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_BOOTSTRAP_REG_COMPLETE, 2),
		     NULL);
	engine_bootstrap_finish();
	zassert_equal(
		check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_BOOTSTRAP_TRANSFER_COMPLETE, 3),
		true);
}

ZTEST(lwm2m_rd_client, test_bootstrap_timeout)
{

	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_timeout_cb_default);

	lwm2m_engine_add_service_fake.custom_fake = lwm2m_engine_add_service_fake_default;
	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_true;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 1, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_BOOTSTRAP_REG_FAILURE, 0),
		     NULL);
}

ZTEST(lwm2m_rd_client, test_bootstrap_fail)
{
	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_engine_add_service_fake.custom_fake = lwm2m_engine_add_service_fake_default;
	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_true;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_bad_request;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 1, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_BOOTSTRAP_REG_FAILURE, 0),
		     NULL);

}

ZTEST(lwm2m_rd_client, test_bootstrap_no_srv_fallback_to_register)
{

	struct lwm2m_ctx ctx;

	(void)memset(&ctx, 0x0, sizeof(ctx));

	test_prepare_pending_message_cb(&message_reply_cb_default);

	lwm2m_engine_add_service_fake.custom_fake = lwm2m_engine_add_service_fake_default;
	lwm2m_rd_client_init();
	test_lwm2m_engine_start_service();
	wait_for_service(1);

	lwm2m_get_bool_fake.custom_fake = lwm2m_get_bool_fake_default;
	lwm2m_sprint_ip_addr_fake.custom_fake = lwm2m_sprint_ip_addr_fake_default;
	lwm2m_init_message_fake.custom_fake = lwm2m_init_message_fake_default;
	coap_header_get_code_fake.custom_fake = coap_header_get_code_fake_created;
	coap_find_options_fake.custom_fake = coap_find_options_do_registration_reply_cb_ok;
	zassert_true(lwm2m_rd_client_start(&ctx, "Test", 1, lwm2m_event_cb, lwm2m_observe_cb) == 0,
		     NULL);
	zassert_true(check_lwm2m_rd_client_event(LWM2M_RD_CLIENT_EVENT_REGISTRATION_COMPLETE, 0),
		     NULL);
}
