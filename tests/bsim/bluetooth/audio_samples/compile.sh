#!/usr/bin/env bash
# Copyright 2023 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

# Compile all the applications needed by the bsim tests in these subfolders

#set -x #uncomment this line for debugging
set -ue

: "${ZEPHYR_BASE:?ZEPHYR_BASE must be set to point to the zephyr root directory}"

source ${ZEPHYR_BASE}/tests/bsim/compile.source

if [ "${BOARD_TS}" == "nrf5340bsim_nrf5340_cpuapp" ]; then
  app=samples/bluetooth/bap_unicast_server sysbuild=1 compile
  app=samples/bluetooth/bap_broadcast_source sysbuild=1 compile
  app=tests/bsim/bluetooth/audio_samples/bap_unicast_client sysbuild=1 compile
  app=tests/bsim/bluetooth/audio_samples/bap_broadcast_sink sysbuild=1 \
    conf_file=${ZEPHYR_BASE}/samples/bluetooth/bap_broadcast_sink/prj.conf \
    exe_name=bs_${BOARD_TS}_${app}_prj_conf sysbuild=1 compile
else
  app=samples/bluetooth/bap_unicast_server conf_overlay=overlay-bt_ll_sw_split.conf \
    exe_name=bs_${BOARD_TS}_${app}_prj_conf sysbuild=1 compile
  app=samples/bluetooth/bap_broadcast_source conf_overlay=overlay-bt_ll_sw_split.conf \
    exe_name=bs_${BOARD_TS}_${app}_prj_conf sysbuild=1 compile
  app=tests/bsim/bluetooth/audio_samples/bap_unicast_client \
    conf_overlay=${ZEPHYR_BASE}/samples/bluetooth/bap_unicast_client/overlay-bt_ll_sw_split.conf \
    exe_name=bs_${BOARD_TS}_${app}_prj_conf sysbuild=1 compile
  app=tests/bsim/bluetooth/audio_samples/bap_broadcast_sink \
    conf_file=${ZEPHYR_BASE}/samples/bluetooth/bap_broadcast_sink/prj.conf \
    conf_overlay=${ZEPHYR_BASE}/samples/bluetooth/bap_broadcast_sink/overlay-bt_ll_sw_split.conf \
    exe_name=bs_${BOARD_TS}_${app}_prj_conf sysbuild=1 compile
fi

wait_for_background_jobs
