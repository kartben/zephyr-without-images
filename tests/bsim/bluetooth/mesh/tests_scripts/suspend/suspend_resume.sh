#!/usr/bin/env bash
# Copyright 2023 Nordic Semiconductor
# SPDX-License-Identifier: Apache-2.0

source $(dirname "${BASH_SOURCE[0]}")/../../_mesh_test.sh

# Test that periodic publication is stopped when suspending Mesh, and that it
# is started again when Mesh is resumed. The test will fail under two
# conditions; if no publication is received while Mesh is enabled,
# or if a publication is received while Mesh is suspended.
#
# Test procedure:
# 0. Provisioning and setup.
# 1. Start publication.
# 2. Suspend Mesh, checking that publication stops.
# 3. Resume Mesh a specified time after suspension. Check that publication resumes.

RunTest mesh_suspend_resume \
	suspend_tx_suspend_resume suspend_rx_suspend_resume

conf=prj_mesh1d1_conf
RunTest mesh_suspend_resume_1d1 \
	suspend_tx_suspend_resume suspend_rx_suspend_resume

overlay=overlay_low_lat_conf
RunTest mesh_suspend_resume_low_lat \
	suspend_tx_suspend_resume suspend_rx_suspend_resume

conf=prj_mesh1d1_conf
overlay=overlay_psa_conf
RunTest mesh_suspend_resume_psa \
	suspend_tx_suspend_resume suspend_rx_suspend_resume
