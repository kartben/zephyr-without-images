/* gap.c - Bluetooth GAP Tester */

/*
 * Copyright (c) 2015 Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1) Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3) Neither the name of Intel Corporation nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>

#include <toolchain.h>
#include <bluetooth/bluetooth.h>

#include "bttester.h"

static uint8_t start_advertising(uint8_t *data, uint16_t len)
{
	struct cmd_start_advertising *cmd = (void *) data;

	if (bt_start_advertising(cmd->adv_type, NULL, NULL) < 0) {
		return STATUS_FAILED;
	}

	return STATUS_SUCCESS;
}

void tester_handle_gap(uint8_t opcode, uint8_t *data, uint16_t len)
{
	uint8_t status;

	switch (opcode) {
	case OP_GAP_START_ADV:
		status = start_advertising(data, len);
		break;
	default:
		status = STATUS_UNKNOWN_CMD;
		break;
	}

	tester_rsp(SERVICE_ID_GAP, opcode, status);
}

uint8_t tester_init_gap(void)
{
	if (bt_init() < 0) {
		return STATUS_FAILED;
	}

	return STATUS_SUCCESS;
}
