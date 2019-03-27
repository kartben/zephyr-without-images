/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <logging/log.h>
LOG_MODULE_REGISTER(net_test, LOG_LEVEL_WRN);

#include <ztest.h>
#include <net/socket.h>
#include <net/mqtt.h>

#include <string.h>
#include <errno.h>

#include "../../mqtt_pubsub/src/config.h"

#define BUFFER_SIZE 32

static u8_t rx_buffer[BUFFER_SIZE];
static u8_t tx_buffer[BUFFER_SIZE];
static struct mqtt_client client_ctx;
static struct sockaddr broker;
static struct pollfd fds[1];
static int nfds;
static bool connected;
static int payload_left;
static const u8_t *payload;

static const u8_t payload_short[] = "Short payload";

/* Generated by http://www.lipsum.com/
 * 2 paragraphs, 171 words, 1210 bytes of Lorem Ipsum
 */
static const u8_t payload_long[] =
	"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse "
	"eleifend odio sit amet scelerisque tincidunt. In orci ligula, egestas "
	"ut neque sit amet, fringilla malesuada dolor. Fusce rhoncus nunc in "
	"lacus tincidunt lobortis. Donec aliquam lectus gravida fermentum "
	"egestas. Curabitur eu ex pretium, dapibus massa in, pretium tellus. "
	"Suspendisse ac efficitur magna, ut convallis nisl. Duis sed sapien "
	"odio. Aliquam efficitur sed tellus sit amet eleifend. Sed facilisis "
	"ligula aliquam erat ornare hendrerit. Aenean tincidunt nunc a nulla "
	"vestibulum mollis. Vivamus fringilla euismod nisi sit amet malesuada. "
	"Vivamus consequat ultricies metus sed feugiat. Aenean malesuada "
	"cursus sem."
	"\n"
	"Vestibulum tempor diam et aliquam tristique. Nullam condimentum felis "
	"et convallis finibus. Aliquam erat volutpat. Nam et blandit tortor. "
	"Nullam pharetra arcu aliquam, suscipit mi eu, faucibus lacus. "
	"Pellentesque eleifend nulla sit amet purus maximus, et elementum "
	"lectus fringilla. Praesent consectetur diam eget tellus molestie "
	"tempor. Class aptent taciti sociosqu ad litora torquent per conubia "
	"nostra, per inceptos himenaeos. Nam tincidunt urna augue, nec cursus "
	"arcu eleifend nec. Donec semper tellus in leo nullam."
	"\n";

static void broker_init(void)
{
#if defined(CONFIG_NET_IPV6)
	struct sockaddr_in6 *broker6 = net_sin6(&broker);

	broker6->sin6_family = AF_INET6;
	broker6->sin6_port = htons(SERVER_PORT);
	inet_pton(AF_INET6, SERVER_ADDR, &broker6->sin6_addr);
#else
	struct sockaddr_in *broker4 = net_sin(&broker);

	broker4->sin_family = AF_INET;
	broker4->sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_ADDR, &broker4->sin_addr);
#endif
}

static void prepare_fds(struct mqtt_client *client)
{
	if (client->transport.type == MQTT_TRANSPORT_NON_SECURE) {
		fds[0].fd = client->transport.tcp.sock;
	}

	fds[0].events = ZSOCK_POLLIN;
	nfds = 1;
}

static void clear_fds(void)
{
	nfds = 0;
}

static void wait(int timeout)
{
	if (nfds > 0) {
		if (poll(fds, nfds, timeout) < 0) {
			TC_PRINT("poll error: %d\n", errno);
		}
	}
}

void publish_handler(struct mqtt_client *const client,
		    const struct mqtt_evt *evt)
{
	int rc;
	u8_t buf[16];
	u32_t offset = 0U;

	if (evt->result != 0) {
		TC_PRINT("MQTT PUBLISH error: %d\n", evt->result);
		goto error;
	}

	if (payload_left != evt->param.publish.message.payload.len) {
		TC_PRINT("Invalid payload length: %d\n",
			 evt->param.publish.message.payload.len);
		goto error;
	}

	while (payload_left > 0) {
		wait(APP_SLEEP_MSECS);
		rc = mqtt_read_publish_payload(client, buf, sizeof(buf));
		if (rc <= 0) {
			TC_PRINT("Failed to receive payload, err: %d\n", -rc);
			if (rc == -EAGAIN) {
				continue;
			}
			goto error;
		}

		if (memcmp(payload + offset, buf, rc) != 0) {
			TC_PRINT("Invalid payload content\n");
			goto error;
		}

		payload_left -= rc;
		offset += rc;
	}

	return;

error:
	payload_left = -1;
}

void mqtt_evt_handler(struct mqtt_client *const client,
		      const struct mqtt_evt *evt)
{
	int err;

	switch (evt->type) {
	case MQTT_EVT_CONNACK:
		if (evt->result != 0) {
			TC_PRINT("MQTT connect failed %d\n", evt->result);
			break;
		}

		connected = true;
		TC_PRINT("[%s:%d] MQTT_EVT_CONNACK: Connected!\n",
			 __func__, __LINE__);

		break;

	case MQTT_EVT_DISCONNECT:
		TC_PRINT("[%s:%d] MQTT_EVT_DISCONNECT: disconnected %d\n",
			 __func__, __LINE__, evt->result);

		connected = false;
		payload_left = -1;
		clear_fds();

		break;

	case MQTT_EVT_PUBLISH:
		publish_handler(client, evt);

		break;

	case MQTT_EVT_PUBACK:
		if (evt->result != 0) {
			TC_PRINT("MQTT PUBACK error %d\n", evt->result);
			payload_left = -1;
			break;
		}

		TC_PRINT("[%s:%d] MQTT_EVT_PUBACK packet id: %u\n",
			 __func__, __LINE__, evt->param.puback.message_id);

		break;

	case MQTT_EVT_PUBREC:
		if (evt->result != 0) {
			TC_PRINT("MQTT PUBREC error %d\n", evt->result);
			break;
		}

		TC_PRINT("[%s:%d] MQTT_EVT_PUBREC packet id: %u\n",
			 __func__, __LINE__, evt->param.pubrec.message_id);

		const struct mqtt_pubrel_param rel_param = {
			.message_id = evt->param.pubrec.message_id
		};

		err = mqtt_publish_qos2_release(client, &rel_param);
		if (err != 0) {
			TC_PRINT("Failed to send MQTT PUBREL: %d\n",
				 err);
		}

		break;

	case MQTT_EVT_PUBCOMP:
		if (evt->result != 0) {
			TC_PRINT("MQTT PUBCOMP error %d\n", evt->result);
			break;
		}

		TC_PRINT("[%s:%d] MQTT_EVT_PUBCOMP packet id: %u\n",
			 __func__, __LINE__, evt->param.pubcomp.message_id);

		break;

	case MQTT_EVT_SUBACK:
		if (evt->result != 0) {
			TC_PRINT("MQTT SUBACK error %d\n", evt->result);
			break;
		}


		TC_PRINT("[%s:%d] items: %d packet id: %u\n", __func__,
			 __LINE__, evt->param.suback.return_codes.len,
			 evt->param.suback.message_id);


		break;

	case MQTT_EVT_UNSUBACK:
		if (evt->result != 0) {
			TC_PRINT("MQTT UNSUBACK error %d\n", evt->result);
			break;
		}

		TC_PRINT("[%s:%d] packet id: %u\n", __func__, __LINE__,
			 evt->param.unsuback.message_id);

		break;

	default:
		TC_PRINT("[%s:%d] Invalid MQTT packet\n", __func__, __LINE__);
		break;
	}
}

static char *get_mqtt_topic(void)
{
	return "sensors";
}

static void client_init(struct mqtt_client *client)
{
	mqtt_client_init(client);

	broker_init();

	/* MQTT client configuration */
	client->broker = &broker;
	client->evt_cb = mqtt_evt_handler;
	client->client_id.utf8 = (u8_t *)MQTT_CLIENTID;
	client->client_id.size = strlen(MQTT_CLIENTID);
	client->password = NULL;
	client->user_name = NULL;
	client->protocol_version = MQTT_VERSION_3_1_1;
	client->transport.type = MQTT_TRANSPORT_NON_SECURE;

	client->rx_buf = rx_buffer;
	client->rx_buf_size = sizeof(rx_buffer);
	client->tx_buf = tx_buffer;
	client->tx_buf_size = sizeof(tx_buffer);
}

/* In this routine we block until the connected variable is 1 */
static int try_to_connect(struct mqtt_client *client)
{
	int rc, i = 0;

	while (i++ < APP_CONNECT_TRIES && !connected) {

		client_init(&client_ctx);

		rc = mqtt_connect(client);
		if (rc != 0) {
			k_sleep(APP_SLEEP_MSECS);
			continue;
		}

		prepare_fds(client);

		wait(APP_SLEEP_MSECS);
		mqtt_input(client);

		if (!connected) {
			mqtt_abort(client);
		}
	}

	if (connected) {
		return 0;
	}

	return -EINVAL;
}

static int test_connect(void)
{
	int rc;

	rc = try_to_connect(&client_ctx);
	if (rc != 0) {
		return TC_FAIL;
	}

	return TC_PASS;
}

static int test_subscribe(void)
{
	int rc;
	struct mqtt_topic topic;
	struct mqtt_subscription_list sub;

	topic.topic.utf8 = get_mqtt_topic();
	topic.topic.size = strlen(topic.topic.utf8);
	topic.qos = MQTT_QOS_1_AT_LEAST_ONCE;
	sub.list = &topic;
	sub.list_count = 1U;
	sub.message_id = sys_rand32_get();

	rc = mqtt_subscribe(&client_ctx, &sub);
	if (rc != 0) {
		return TC_FAIL;
	}

	wait(APP_SLEEP_MSECS);
	rc = mqtt_input(&client_ctx);
	if (rc != 0) {
		return TC_FAIL;
	}

	return TC_PASS;
}

static int test_publish(enum mqtt_qos qos)
{
	int rc;
	struct mqtt_publish_param param;

	payload_left = strlen(payload);

	param.message.topic.qos = qos;
	param.message.topic.topic.utf8 = (u8_t *)get_mqtt_topic();
	param.message.topic.topic.size =
			strlen(param.message.topic.topic.utf8);
	param.message.payload.data = (u8_t *)payload;
	param.message.payload.len = payload_left;
	param.message_id = sys_rand32_get();
	param.dup_flag = 0U;
	param.retain_flag = 0U;

	rc = mqtt_publish(&client_ctx, &param);
	if (rc != 0) {
		return TC_FAIL;
	}

	while (payload_left > 0) {
		wait(APP_SLEEP_MSECS);
		rc = mqtt_input(&client_ctx);
		if (rc != 0) {
			return TC_FAIL;
		}
	}

	if (payload_left != 0) {
		return TC_FAIL;
	}

	return TC_PASS;
}

static int test_unsubscribe(void)
{
	int rc;
	struct mqtt_topic topic;
	struct mqtt_subscription_list unsub;

	topic.topic.utf8 = get_mqtt_topic();
	topic.topic.size = strlen(topic.topic.utf8);
	unsub.list = &topic;
	unsub.list_count = 1U;
	unsub.message_id = sys_rand32_get();

	rc = mqtt_unsubscribe(&client_ctx, &unsub);
	if (rc != 0) {
		return TC_FAIL;
	}

	wait(APP_SLEEP_MSECS);
	rc = mqtt_input(&client_ctx);
	if (rc != 0) {
		return TC_FAIL;
	}

	return TC_PASS;
}

static int test_disconnect(void)
{
	int rc;

	rc = mqtt_disconnect(&client_ctx);
	if (rc != 0) {
		return TC_FAIL;
	}

	wait(APP_SLEEP_MSECS);
	rc = mqtt_input(&client_ctx);
	if (rc != 0) {
		return TC_FAIL;
	}

	if (connected) {
		return TC_FAIL;
	}

	return TC_PASS;
}

void test_mqtt_connect(void)
{
	zassert_true(test_connect() == TC_PASS, NULL);
}

void test_mqtt_subscribe(void)
{
	zassert_true(test_subscribe() == TC_PASS, NULL);
}

void test_mqtt_publish_short(void)
{
	payload = payload_short;
	zassert_true(test_publish(MQTT_QOS_0_AT_MOST_ONCE) == TC_PASS, NULL);
}

void test_mqtt_publish_long(void)
{
	payload = payload_long;
	zassert_true(test_publish(MQTT_QOS_1_AT_LEAST_ONCE) == TC_PASS, NULL);
}

void test_mqtt_unsubscribe(void)
{
	zassert_true(test_unsubscribe() == TC_PASS, NULL);
}

void test_mqtt_disconnect(void)
{
	zassert_true(test_disconnect() == TC_PASS, NULL);
}
