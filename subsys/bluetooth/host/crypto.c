/*
 * Copyright (c) 2017 Nordic Semiconductor ASA
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <errno.h>

#include <zephyr.h>
#include <sys/byteorder.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/crypto.h>

#include <tinycrypt/constants.h>
#include <tinycrypt/hmac_prng.h>
#include <tinycrypt/aes.h>
#include <tinycrypt/utils.h>

#define BT_DBG_ENABLED IS_ENABLED(CONFIG_BT_DEBUG_HCI_CORE)
#define LOG_MODULE_NAME bt_crypto
#include "common/log.h"

#include "hci_core.h"

static struct tc_hmac_prng_struct prng;

static int prng_reseed(struct tc_hmac_prng_struct *h)
{
	uint8_t seed[32];
	int64_t extra;
	size_t i;
	int ret;

	for (i = 0; i < (sizeof(seed) / 8); i++) {
		struct bt_hci_rp_le_rand *rp;
		struct net_buf *rsp;

		ret = bt_hci_cmd_send_sync(BT_HCI_OP_LE_RAND, NULL, &rsp);
		if (ret) {
			return ret;
		}

		rp = (void *)rsp->data;
		memcpy(&seed[i * 8], rp->rand, 8);

		net_buf_unref(rsp);
	}

	extra = k_uptime_get();

	ret = tc_hmac_prng_reseed(h, seed, sizeof(seed), (uint8_t *)&extra,
				  sizeof(extra));
	if (ret == TC_CRYPTO_FAIL) {
		BT_ERR("Failed to re-seed PRNG");
		return -EIO;
	}

	return 0;
}

int prng_init(void)
{
	struct bt_hci_rp_le_rand *rp;
	struct net_buf *rsp;
	int ret;

	/* Check first that HCI_LE_Rand is supported */
	if (!BT_CMD_TEST(bt_dev.supported_commands, 27, 7)) {
		return -ENOTSUP;
	}

	ret = bt_hci_cmd_send_sync(BT_HCI_OP_LE_RAND, NULL, &rsp);
	if (ret) {
		return ret;
	}

	rp = (void *)rsp->data;

	ret = tc_hmac_prng_init(&prng, rp->rand, sizeof(rp->rand));

	net_buf_unref(rsp);

	if (ret == TC_CRYPTO_FAIL) {
		BT_ERR("Failed to initialize PRNG");
		return -EIO;
	}

	/* re-seed is needed after init */
	return prng_reseed(&prng);
}

#if defined(CONFIG_BT_HOST_CRYPTO_PRNG)
int bt_rand(void *buf, size_t len)
{
	int ret;

	ret = tc_hmac_prng_generate(buf, len, &prng);
	if (ret == TC_HMAC_PRNG_RESEED_REQ) {
		ret = prng_reseed(&prng);
		if (ret) {
			return ret;
		}

		ret = tc_hmac_prng_generate(buf, len, &prng);
	}

	if (ret == TC_CRYPTO_SUCCESS) {
		return 0;
	}

	return -EIO;
}
#else /* !CONFIG_BT_HOST_CRYPTO_PRNG */
int bt_rand(void *buf, size_t len)
{
	int ret, size;
	size_t i = 0;

	/* Check first that HCI_LE_Rand is supported */
	if (!BT_CMD_TEST(bt_dev.supported_commands, 27, 7)) {
		return -ENOTSUP;
	}

	while (len) {
		struct bt_hci_rp_le_rand *rp;
		struct net_buf *rsp;

		ret = bt_hci_cmd_send_sync(BT_HCI_OP_LE_RAND, NULL, &rsp);
		if (ret) {
			return ret;
		}

		rp = (void *)rsp->data;
		if (rp->status) {
			return -EIO;
		}

		size = MIN(len, sizeof(rp->rand));

		(void)memcpy((uint8_t *)buf + i, rp->rand, size);

		net_buf_unref(rsp);

		i += size;
		len -= size;
	}

	return 0;
}
#endif /* CONFIG_BT_HOST_CRYPTO_PRNG */

int bt_encrypt_le(const uint8_t key[16], const uint8_t plaintext[16],
		  uint8_t enc_data[16])
{
	struct tc_aes_key_sched_struct s;
	uint8_t tmp[16];

	BT_DBG("key %s", bt_hex(key, 16));
	BT_DBG("plaintext %s", bt_hex(plaintext, 16));

	sys_memcpy_swap(tmp, key, 16);

	if (tc_aes128_set_encrypt_key(&s, tmp) == TC_CRYPTO_FAIL) {
		return -EINVAL;
	}

	sys_memcpy_swap(tmp, plaintext, 16);

	if (tc_aes_encrypt(enc_data, tmp, &s) == TC_CRYPTO_FAIL) {
		return -EINVAL;
	}

	sys_mem_swap(enc_data, 16);

	BT_DBG("enc_data %s", bt_hex(enc_data, 16));

	return 0;
}

int bt_encrypt_be(const uint8_t key[16], const uint8_t plaintext[16],
		  uint8_t enc_data[16])
{
	struct tc_aes_key_sched_struct s;

	BT_DBG("key %s", bt_hex(key, 16));
	BT_DBG("plaintext %s", bt_hex(plaintext, 16));

	if (tc_aes128_set_encrypt_key(&s, key) == TC_CRYPTO_FAIL) {
		return -EINVAL;
	}

	if (tc_aes_encrypt(enc_data, plaintext, &s) == TC_CRYPTO_FAIL) {
		return -EINVAL;
	}

	BT_DBG("enc_data %s", bt_hex(enc_data, 16));

	return 0;
}
