/*
 * Copyright (c) 2016 ARM Limited.
 *
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <device.h>
#include <random.h>
#include <drivers/rand32.h>
#include <init.h>

#include "fsl_rnga.h"

static uint8_t random_ksdk_get_uint8(void)
{
	uint32_t random;
	uint8_t output = 0;
	int i;

	RNGA_SetMode(RNG, kRNGA_ModeNormal);
	/* The Reference manual states that back to back reads from
	 * the RNGA deliver one or two bits of entropy per 32-bit
	 * word, therefore to deliver 8 bits of entropy we need
	 * between 4 and 8 samples.  Conservatively, we take 8.
	 */
	for (i = 0; i < 8; i++) {
		status_t status;

		status = RNGA_GetRandomData(RNG, &random, sizeof(random));
		__ASSERT_NO_MSG(!status);
		output ^= random;
	}

	RNGA_SetMode(RNG, kRNGA_ModeSleep);

	return output;
}

static int random_ksdk_get_entropy(struct device *dev, uint8_t *buffer,
				   uint16_t length)
{
	int i;

	ARG_UNUSED(dev);

	for (i = 0; i < length; i++) {
		buffer[i] = random_ksdk_get_uint8();
	}

	return 0;
}

static const struct random_driver_api random_ksdk_api_funcs = {
	.get_entropy = random_ksdk_get_entropy
};

static int random_ksdk_init(struct device *);

DEVICE_AND_API_INIT(random_ksdk, CONFIG_RANDOM_NAME,
		    random_ksdk_init, NULL, NULL,
		    PRE_KERNEL_2, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		    &random_ksdk_api_funcs);

static int random_ksdk_init(struct device *dev)
{
	uint32_t seed = sys_cycle_get_32();

	ARG_UNUSED(dev);

	RNGA_Init(RNG);

	/* The range of seed values acquired by this method is likely
	 * to be relatively small.  The RNGA hardware uses two free
	 * running oscillators to add entropy to the seed value, we
	 * take care below to ensure the read rate is lower than the
	 * rate at which the hardware can add entropy.
	 */
	RNGA_Seed(RNG, seed);
	RNGA_SetMode(RNG, kRNGA_ModeSleep);
	return 0;
}

uint32_t sys_rand32_get(void)
{
	uint32_t output;
	int r;

	r = random_ksdk_get_entropy(DEVICE_GET(random_ksdk),
				    (uint8_t *) &output, sizeof(output));
	__ASSERT_NO_MSG(!r);

	return output;
}
