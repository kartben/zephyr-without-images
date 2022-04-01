/*
 * Copyright (c) 2022 Nordic Semiconductor
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mesh_test.h"
#include "mesh/blob.h"
#include "argparse.h"

#define LOG_MODULE_NAME test_blob

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL_INF);

#define BLOB_GROUP_ADDR 0xc000
#define BLOB_CLI_ADDR 0x0001
#define MODEL_LIST(...) ((struct bt_mesh_model[]){ __VA_ARGS__ })

static uint8_t dev_key[16] = { 0xdd };
static uint8_t app_key[16] = { 0xaa };
static uint8_t net_key[16] = { 0xcc };
static struct bt_mesh_prov prov;

static struct {
	struct bt_mesh_blob_cli_inputs inputs;
	struct bt_mesh_blob_target targets[2];
	uint8_t target_count;
	struct bt_mesh_blob_xfer xfer;
} blob_cli_xfer;

static struct {
	uint16_t addrs[6];
	uint8_t rem_cnt;
} lost_targets;

static uint16_t own_addr_get(void)
{
	return BLOB_CLI_ADDR + get_device_nbr();
}

static bool lost_target_find_and_remove(uint16_t addr)
{
	for (int i = 0; i < ARRAY_SIZE(lost_targets.addrs); i++) {
		if (addr == lost_targets.addrs[i]) {
			lost_targets.addrs[i] = 0;
			lost_targets.rem_cnt--;
			return true;
		}
	}

	return false;
}

static void lost_target_add(uint16_t addr)
{
	if (lost_targets.rem_cnt >= ARRAY_SIZE(lost_targets.addrs)) {
		FAIL("No more room in lost target list");
		return;
	}

	lost_targets.addrs[lost_targets.rem_cnt] = addr;
	lost_targets.rem_cnt++;
}

static struct k_sem blob_caps_sem;

static void blob_cli_caps(struct bt_mesh_blob_cli *b, const struct bt_mesh_blob_cli_caps *caps)
{
	k_sem_give(&blob_caps_sem);
	if (caps) {
		ASSERT_EQUAL(caps->mtu_size, BT_MESH_RX_SDU_MAX - BT_MESH_MIC_SHORT);
		ASSERT_EQUAL(caps->modes, BT_MESH_BLOB_XFER_MODE_ALL);
		ASSERT_EQUAL(caps->max_size, CONFIG_BT_MESH_BLOB_SIZE_MAX);
		ASSERT_EQUAL(caps->max_block_size_log, BLOB_BLOCK_SIZE_LOG_MIN);
		ASSERT_EQUAL(caps->min_block_size_log, BLOB_BLOCK_SIZE_LOG_MAX);
		ASSERT_EQUAL(caps->max_chunk_size, BLOB_CHUNK_SIZE_MAX(BT_MESH_RX_SDU_MAX));
		ASSERT_EQUAL(caps->max_chunks, CONFIG_BT_MESH_BLOB_CHUNK_COUNT_MAX);
	}
}

static struct k_sem lost_target_sem;

static void blob_cli_lost_target(struct bt_mesh_blob_cli *b, struct bt_mesh_blob_target *blobt,
				 enum bt_mesh_blob_status reason)
{
	ASSERT_FALSE(reason == BT_MESH_BLOB_SUCCESS);
	ASSERT_TRUE(lost_target_find_and_remove(blobt->addr));

	if (!lost_targets.rem_cnt) {
		k_sem_give(&lost_target_sem);
	}
}

static void blob_cli_suspended(struct bt_mesh_blob_cli *b)
{
}

static void blob_cli_end(struct bt_mesh_blob_cli *b, const struct bt_mesh_blob_xfer *xfer,
			 bool success)
{
}

static void blob_srv_suspended(struct bt_mesh_blob_srv *b)
{
}

static void blob_srv_end(struct bt_mesh_blob_srv *b, uint64_t id, bool success)
{
}

static int blob_srv_recover(struct bt_mesh_blob_srv *b, struct bt_mesh_blob_xfer *xfer,
			    const struct bt_mesh_blob_io **io)
{
	return 0;
}

static int blob_srv_start(struct bt_mesh_blob_srv *srv, struct bt_mesh_msg_ctx *ctx,
			  struct bt_mesh_blob_xfer *xfer)
{
	return 0;
}

static void blob_srv_resume(struct bt_mesh_blob_srv *srv)
{
}

static const struct bt_mesh_blob_srv_cb blob_srv_cb = {
	.suspended = blob_srv_suspended,
	.end = blob_srv_end,
	.recover = blob_srv_recover,
	.start = blob_srv_start,
	.resume = blob_srv_resume,
};
static const struct bt_mesh_blob_cli_cb blob_cli_handlers = {
	.caps = blob_cli_caps,
	.lost_target = blob_cli_lost_target,
	.suspended = blob_cli_suspended,
	.end = blob_cli_end,
};
static struct bt_mesh_blob_srv blob_srv = { .cb = &blob_srv_cb };
static struct bt_mesh_blob_cli blob_cli = { .cb = &blob_cli_handlers };
static struct bt_mesh_cfg_cli cfg_cli;

static const struct bt_mesh_comp srv_comp = {
	.elem =
		(struct bt_mesh_elem[]){
			BT_MESH_ELEM(1,
				     MODEL_LIST(BT_MESH_MODEL_CFG_SRV,
						BT_MESH_MODEL_CFG_CLI(&cfg_cli),
						BT_MESH_MODEL_BLOB_SRV(&blob_srv)),
				     BT_MESH_MODEL_NONE),
		},
	.elem_count = 1,
};

static const struct bt_mesh_comp cli_comp = {
	.elem =
		(struct bt_mesh_elem[]){
			BT_MESH_ELEM(1,
				     MODEL_LIST(BT_MESH_MODEL_CFG_SRV,
						BT_MESH_MODEL_CFG_CLI(&cfg_cli),
						BT_MESH_MODEL_BLOB_CLI(&blob_cli)),
				     BT_MESH_MODEL_NONE),
		},
	.elem_count = 1,
};

static struct k_sem info_get_sem;

static int mock_handle_info_get(struct bt_mesh_model *model, struct bt_mesh_msg_ctx *ctx,
				struct net_buf_simple *buf)
{
	k_sem_give(&info_get_sem);
	return 0;
}

static const struct bt_mesh_model_op model_op1[] = {
	{ BT_MESH_BLOB_OP_INFO_GET, 0, mock_handle_info_get },
	BT_MESH_MODEL_OP_END };

static const struct bt_mesh_comp none_rsp_srv_comp = {
	.elem =
		(struct bt_mesh_elem[]){
			BT_MESH_ELEM(1,
				     MODEL_LIST(BT_MESH_MODEL_CFG_SRV,
						BT_MESH_MODEL_CFG_CLI(&cfg_cli),
						BT_MESH_MODEL_CB(BT_MESH_MODEL_ID_BLOB_SRV,
								 model_op1, NULL, NULL, NULL)),
				     BT_MESH_MODEL_NONE),
		},
	.elem_count = 1,
};

static void provision(uint16_t addr)
{
	int err;

	err = bt_mesh_provision(net_key, 0, 0, 0, addr, dev_key);
	if (err) {
		FAIL("Provisioning failed (err %d)", err);
		return;
	}
}

static void common_configure(uint16_t addr)
{
	uint8_t status;
	int err;

	err = bt_mesh_cfg_cli_app_key_add(0, addr, 0, 0, app_key, &status);
	if (err || status) {
		FAIL("AppKey add failed (err %d, status %u)", err, status);
		return;
	}
}

static void blob_srv_prov_and_conf(uint16_t addr)
{
	uint8_t status;
	int err;

	provision(addr);
	common_configure(addr);

	err = bt_mesh_cfg_cli_mod_app_bind(0, addr, addr, 0, BT_MESH_MODEL_ID_BLOB_SRV, &status);
	if (err || status) {
		FAIL("Model %#4x bind failed (err %d, status %u)", BT_MESH_MODEL_ID_BLOB_CLI, err,
		     status);
		return;
	}

	err = bt_mesh_cfg_cli_mod_sub_add(0, addr, addr, BLOB_GROUP_ADDR, BT_MESH_MODEL_ID_BLOB_SRV,
					  &status);
	if (err || status) {
		FAIL("Model %#4x sub add failed (err %d, status %u)", BT_MESH_MODEL_ID_BLOB_CLI,
		     err, status);
		return;
	}
}

static void blob_cli_prov_and_conf(uint16_t addr)
{
	uint8_t status;
	int err;

	provision(addr);
	common_configure(addr);

	err = bt_mesh_cfg_cli_mod_app_bind(0, addr, addr, 0, BT_MESH_MODEL_ID_BLOB_CLI, &status);
	if (err || status) {
		FAIL("Model %#4x bind failed (err %d, status %u)", BT_MESH_MODEL_ID_BLOB_CLI, err,
		     status);
		return;
	}
}

static void blob_cli_inputs_prepare(uint16_t group)
{
	blob_cli_xfer.inputs.ttl = BT_MESH_TTL_DEFAULT;
	blob_cli_xfer.inputs.group = group;
	blob_cli_xfer.inputs.app_idx = 0;
	sys_slist_init(&blob_cli_xfer.inputs.targets);

	for (int i = 0; i < blob_cli_xfer.target_count; ++i) {
		/* Reset target context. */
		uint16_t addr = blob_cli_xfer.targets[i].addr;

		memset(&blob_cli_xfer.targets[i].addr, 0, sizeof(struct bt_mesh_blob_target));
		blob_cli_xfer.targets[i].addr = addr;

		sys_slist_append(&blob_cli_xfer.inputs.targets, &blob_cli_xfer.targets[i].n);
	}
}

static struct bt_mesh_blob_target *target_srv_add(uint16_t addr, bool expect_lost)
{
	if (expect_lost) {
		lost_target_add(addr);
	}

	ASSERT_TRUE(blob_cli_xfer.target_count < ARRAY_SIZE(blob_cli_xfer.targets));
	struct bt_mesh_blob_target *t = &blob_cli_xfer.targets[blob_cli_xfer.target_count];

	t->addr = addr;
	blob_cli_xfer.target_count++;
	return t;
}

static void cli_caps_common_procedure(bool lost_targets)
{
	int err;

	bt_mesh_test_cfg_set(NULL, 60);
	bt_mesh_device_setup(&prov, &cli_comp);
	blob_cli_prov_and_conf(BLOB_CLI_ADDR);

	blob_cli_inputs_prepare(BLOB_GROUP_ADDR);
	k_sem_init(&blob_caps_sem, 0, 1);
	k_sem_init(&lost_target_sem, 0, 1);

	err = bt_mesh_blob_cli_caps_get(&blob_cli, &blob_cli_xfer.inputs);
	if (err) {
		FAIL("Boundary check start failed (err: %d)", err);
	}

	if (lost_targets) {
		if (k_sem_take(&lost_target_sem, K_SECONDS(60))) {
			FAIL("Lost targets CB did not trigger for all expected lost targets");
		}
	}

	if (k_sem_take(&blob_caps_sem, K_SECONDS(60))) {
		FAIL("Caps CB did not trigger at the end of caps procedure");
	}
}

static void test_cli_caps_all_rsp(void)
{
	struct bt_mesh_blob_target *srv1 = target_srv_add(BLOB_CLI_ADDR + 1, false);
	struct bt_mesh_blob_target *srv2 = target_srv_add(BLOB_CLI_ADDR + 2, false);

	cli_caps_common_procedure(false);

	ASSERT_TRUE(srv1->acked);
	ASSERT_FALSE(srv1->timedout);
	ASSERT_TRUE(srv2->acked);
	ASSERT_FALSE(srv2->timedout);

	PASS();

}

static void test_cli_caps_partial_rsp(void)
{
	struct bt_mesh_blob_target *srv1 = target_srv_add(BLOB_CLI_ADDR + 1, false);
	struct bt_mesh_blob_target *srv2 = target_srv_add(BLOB_CLI_ADDR + 2, true);

	cli_caps_common_procedure(true);

	ASSERT_TRUE(srv1->acked);
	ASSERT_FALSE(srv1->timedout);
	ASSERT_FALSE(srv2->acked);
	ASSERT_TRUE(srv2->timedout);

	PASS();
}

static void test_cli_caps_no_rsp(void)
{
	struct bt_mesh_blob_target *srv1 = target_srv_add(BLOB_CLI_ADDR + 1, true);
	struct bt_mesh_blob_target *srv2 = target_srv_add(BLOB_CLI_ADDR + 2, true);

	cli_caps_common_procedure(true);

	ASSERT_FALSE(srv1->acked);
	ASSERT_TRUE(srv1->timedout);
	ASSERT_FALSE(srv2->acked);
	ASSERT_TRUE(srv2->timedout);

	PASS();
}

static void test_srv_caps_standard(void)
{
	bt_mesh_test_cfg_set(NULL, 60);
	bt_mesh_device_setup(&prov, &srv_comp);
	blob_srv_prov_and_conf(own_addr_get());

	PASS();
}

static void test_srv_caps_no_rsp(void)
{
	bt_mesh_test_cfg_set(NULL, 60);
	bt_mesh_device_setup(&prov, &none_rsp_srv_comp);
	blob_srv_prov_and_conf(own_addr_get());

	k_sem_init(&info_get_sem, 0, 1);

	/* Checks that the client performs correct amount of retransmit attempts */
	for (size_t j = 0; j < CONFIG_BT_MESH_BLOB_CLI_BLOCK_RETRIES; j++) {
		int err = k_sem_take(&info_get_sem, K_SECONDS(15));

		if (err) {
			FAIL("Failed to receive expected number of info get messages from cli"
			"(expected: %d, got %d)", CONFIG_BT_MESH_BLOB_CLI_BLOCK_RETRIES, j);
		}
	}

	PASS();
}

#define TEST_CASE(role, name, description)                     \
	{                                                      \
		.test_id = "blob_" #role "_" #name,          \
		.test_descr = description,                     \
		.test_tick_f = bt_mesh_test_timeout,           \
		.test_main_f = test_##role##_##name,           \
	}

static const struct bst_test_instance test_blob[] = {
	TEST_CASE(cli, caps_all_rsp, "Caps procedure: All responsive targets"),
	TEST_CASE(cli, caps_partial_rsp, "Caps procedure: Mixed response from targets"),
	TEST_CASE(cli, caps_no_rsp, "Caps procedure: No response from targets"),
	TEST_CASE(srv, caps_standard, "Standard responsive blob server"),
	TEST_CASE(srv, caps_no_rsp, "Non-responsive blob server"),

	BSTEST_END_MARKER
};

struct bst_test_list *test_blob_install(struct bst_test_list *tests)
{
	tests = bst_add_tests(tests, test_blob);
	return tests;
}
