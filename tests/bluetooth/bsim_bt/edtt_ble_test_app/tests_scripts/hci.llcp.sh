#!/usr/bin/env bash
# Copyright 2019 Oticon A/S
# SPDX-License-Identifier: Apache-2.0

# HCI regression tests based on the EDTTool
CWD="$(cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P)"

export SIMULATION_ID="edtt_hci_llcp"
export TEST_FILE=${CWD}"/hci.llcp.test_list"
export TEST_MODULE="hci_verification"
export PRJ_CONF_1="prj_dut_llcp_conf"
export PRJ_CONF_2="prj_tst_llcp_conf"

${CWD}/_controller_tests_inner.sh
