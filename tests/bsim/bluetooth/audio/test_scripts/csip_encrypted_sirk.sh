#!/usr/bin/env bash
#
# Copyright (c) 2023-2024 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: Apache-2.0

# CSIP test where the SIRK is encrypted

source ${ZEPHYR_BASE}/tests/bsim/sh_common.source

VERBOSITY_LEVEL=2
EXECUTE_TIMEOUT=30

cd ${BSIM_OUT_PATH}/bin

SIMULATION_ID="csip_sirk_encrypted"

printf "\n\n======== Running test with SIRK encrypted ========\n\n"
Execute ./bs_${BOARD}_tests_bsim_bluetooth_audio_prj_conf \
  -v=${VERBOSITY_LEVEL} -s=${SIMULATION_ID} -d=0 -testid=csip_set_coordinator \
  -RealEncryption=1 -rs=1 -D=4

Execute ./bs_${BOARD}_tests_bsim_bluetooth_audio_prj_conf \
  -v=${VERBOSITY_LEVEL} -s=${SIMULATION_ID} -d=1 -testid=csip_set_member_enc \
  -RealEncryption=1 -rs=2 -D=4 -argstest rank 1

Execute ./bs_${BOARD}_tests_bsim_bluetooth_audio_prj_conf \
  -v=${VERBOSITY_LEVEL} -s=${SIMULATION_ID} -d=2 -testid=csip_set_member_enc \
  -RealEncryption=1 -rs=3 -D=4 -argstest rank 2

Execute ./bs_${BOARD}_tests_bsim_bluetooth_audio_prj_conf \
  -v=${VERBOSITY_LEVEL} -s=${SIMULATION_ID} -d=3 -testid=csip_set_member_enc \
  -RealEncryption=1 -rs=4 -D=4 -argstest rank 3

# Simulation time should be larger than the WAIT_TIME in common.h
Execute ./bs_2G4_phy_v1 -v=${VERBOSITY_LEVEL} -s=${SIMULATION_ID} \
  -D=4 -sim_length=60e6 $@

wait_for_background_jobs
