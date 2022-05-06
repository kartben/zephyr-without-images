/*
 * Copyright (c) 2020 Stephanos Ioannidis <root@stephanos.io>
 * Copyright (C) 2010-2020 ARM Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ztest.h>
#include <zephyr/zephyr.h>
#include <stdlib.h>
#include <arm_math.h>
#include "../../common/benchmark_common.h"

#define PATTERN_LENGTH	(256)

static const q15_t input1[256] = {
	0xE3D4, 0x52FC, 0x3145, 0x2BE1, 0xE819, 0xE0ED, 0x7FFF, 0xE3E1,
	0x5ABC, 0x05F6, 0xDDEF, 0xEDDD, 0x1E8B, 0xDF94, 0xF046, 0x0A36,
	0x0EE0, 0x009E, 0x26EB, 0xF319, 0x31C1, 0x10D4, 0xC9C4, 0x2262,
	0x4701, 0x34E1, 0xE40A, 0xDBA4, 0xEDB4, 0xE4A8, 0xE809, 0x0AF7,
	0x18D0, 0xE390, 0x069C, 0xF1F3, 0xFD87, 0x50E3, 0x11D9, 0xD170,
	0xF875, 0xEE6E, 0xFA82, 0x27E6, 0xC9ED, 0xF244, 0x1DAA, 0xD76C,
	0x3161, 0xF480, 0x2AD5, 0x3C94, 0xC6CD, 0x0E0F, 0xEED6, 0xF686,
	0x176B, 0xD1F1, 0x0376, 0x3383, 0x4A5E, 0x345F, 0xEF16, 0xF965,
	0x02F3, 0xFB76, 0xC971, 0xDE8C, 0x451B, 0xE544, 0x3DC0, 0xC6A4,
	0xE51E, 0xFE6F, 0x1611, 0x34E6, 0x62C7, 0xDB18, 0xE6D9, 0x704E,
	0xD2B6, 0xE9AF, 0xFBF6, 0xBB21, 0x238F, 0x41FB, 0xD4BF, 0xF8AC,
	0x56E5, 0xD443, 0x1110, 0x090F, 0xF2CB, 0x0EB2, 0xC3F9, 0xE172,
	0x023C, 0x1418, 0x2AB7, 0x2312, 0x0E1E, 0x12C8, 0xE18B, 0x295E,
	0x3406, 0x1CF5, 0x07C1, 0x1C2D, 0xE286, 0xBD73, 0xEC6A, 0x02D7,
	0xE723, 0x1CAF, 0x0AE6, 0x2981, 0x063E, 0x2C64, 0xE04F, 0xD244,
	0x1A70, 0xDE44, 0x01F4, 0x9045, 0x1FB1, 0x4211, 0x0C12, 0x06C6,
	0x9C63, 0x36BD, 0x245A, 0xA9E8, 0xC568, 0xC1AF, 0xC08E, 0x5486,
	0x351C, 0xA861, 0x0BA9, 0xD8BB, 0x156B, 0x1DF2, 0xDADC, 0xD697,
	0x41D4, 0x0577, 0xA57A, 0x0BC5, 0x207A, 0x65C6, 0xD39F, 0xCCE7,
	0xE5CB, 0xD27E, 0x1CA6, 0xBA07, 0xCE3E, 0xAD53, 0xF436, 0xFBCC,
	0x0A4C, 0x07F3, 0x076E, 0xA9F2, 0xFB3E, 0x0432, 0xF68E, 0x0F7E,
	0xBEFA, 0x46EB, 0xA4E9, 0x1A90, 0x1D3F, 0x16AD, 0x19B4, 0xD509,
	0x0471, 0x1D65, 0xDFAC, 0x25B5, 0x253B, 0xDA97, 0x0278, 0xFB9A,
	0xFDBF, 0x0E9B, 0xF860, 0x239C, 0xF297, 0x0E31, 0xF60B, 0x06C2,
	0xE21D, 0x281D, 0x368E, 0xBE38, 0x01CD, 0x8007, 0x327B, 0x1516,
	0x1B87, 0xEB37, 0xE7C9, 0x0B1F, 0xEB5C, 0x1351, 0xBE00, 0xE59B,
	0x11AD, 0xF790, 0xEA1C, 0x233D, 0xABAD, 0x1308, 0x1123, 0xCFC5,
	0xE2DE, 0xFB7E, 0x015C, 0x46B1, 0x39D4, 0xF461, 0xCF80, 0xFC2F,
	0xE0FD, 0xEB2F, 0xDFDF, 0xF6CE, 0x0E6B, 0xF37A, 0xDE3B, 0x0384,
	0xE41B, 0x0228, 0xEA1A, 0x0295, 0xE259, 0xF591, 0x1D80, 0xFE6D,
	0xE5D5, 0xF4BE, 0x59DE, 0x2A7C, 0xEDC1, 0xD15A, 0xD82E, 0xCF62,
	0xF37B, 0x208B, 0xBBBC, 0xE912, 0x2313, 0x343B, 0x04DB, 0xDAEA
	};

static const q15_t input2[256] = {
	0x1FA8, 0xB5C0, 0x0657, 0xF243, 0xF45A, 0xFC5F, 0xC797, 0xFB41,
	0xADA1, 0xD676, 0x19F3, 0xC719, 0xDCC1, 0xE58D, 0xA698, 0x07DE,
	0x1F5E, 0x38AA, 0x4DC9, 0xEADC, 0xF6F6, 0x0377, 0x0DA7, 0x04F9,
	0xC739, 0x468A, 0xBE92, 0xE168, 0xDAD3, 0x2AFB, 0xBF31, 0x2E55,
	0xC167, 0xE16F, 0x331D, 0x75C5, 0x9CEC, 0x0E00, 0x0FD6, 0x0FBD,
	0x66BF, 0x3D72, 0x210E, 0x4AF9, 0xE88E, 0x386F, 0x15B5, 0x3B1C,
	0xEEE1, 0xD8FA, 0xDEE1, 0x363B, 0xE247, 0x0675, 0xD48C, 0xF07E,
	0x2F80, 0xC403, 0xFA8E, 0x54CF, 0xF854, 0xECEF, 0x3430, 0xE2B4,
	0x0DD4, 0x46ED, 0xBAB9, 0x14E3, 0x0461, 0xFDEE, 0xEADD, 0x3CDC,
	0x0788, 0x1424, 0xD71C, 0xE338, 0xC0E2, 0x478F, 0xAD82, 0xE621,
	0x1A29, 0xEEA8, 0x0694, 0xB7F2, 0x01B0, 0xD64B, 0x45A6, 0x188F,
	0xFEEF, 0x0207, 0xD7DC, 0xF5FD, 0x9C9E, 0x1440, 0x451E, 0x288C,
	0x0D4C, 0xFBB8, 0xF5A3, 0xF9E7, 0x35DD, 0x0180, 0xF11F, 0x28CA,
	0xD05F, 0xE4F9, 0x62E6, 0xF7CF, 0x2E26, 0xDE18, 0x08D1, 0x0A62,
	0x31D2, 0x1FFE, 0x020D, 0x04A3, 0x04D1, 0xE242, 0xB659, 0xF8CC,
	0x1167, 0xE945, 0xD6CB, 0xFBF7, 0x9659, 0xE39B, 0xCB9B, 0x7352,
	0xEB7A, 0xEBB9, 0x3970, 0x42A5, 0xC17C, 0x25D1, 0x71BE, 0x0864,
	0xFB16, 0x7144, 0xE855, 0xB4C5, 0x1E53, 0xFC20, 0x619A, 0x284D,
	0xDFA1, 0xAA6C, 0xF0C7, 0xFF17, 0xEFB4, 0xF703, 0xD588, 0x89A9,
	0x163A, 0x08C7, 0x0797, 0xCDF4, 0x18AF, 0x0340, 0x1D79, 0xC5CF,
	0xE6FE, 0xB892, 0xE6E0, 0xC464, 0xF8A7, 0xC4BF, 0xCAB2, 0xFE34,
	0xB14D, 0xD6A8, 0x4BE8, 0xB393, 0xCA55, 0x1983, 0xB858, 0x2E94,
	0x25A7, 0x0E16, 0xF579, 0xF49B, 0x1238, 0x4404, 0x0DEE, 0x00EB,
	0xCEC0, 0xE9FF, 0x662F, 0x305C, 0x6647, 0x4A18, 0xF747, 0xFEC0,
	0x419B, 0xDF0B, 0x0A29, 0x2316, 0x1E1A, 0xDD96, 0x1FDF, 0xFAC7,
	0xBD7B, 0x0D0F, 0xB873, 0xB61A, 0x05C3, 0xE868, 0x0EF6, 0xCE54,
	0x27A1, 0x47AE, 0x4203, 0xC4D0, 0x5969, 0xE833, 0xE09F, 0x2D48,
	0xF580, 0x38E5, 0xF5F7, 0x2C88, 0x4139, 0xC6A3, 0xE8F8, 0xB988,
	0xBB7C, 0xFC8F, 0xD3CA, 0xDC37, 0x29BF, 0x5714, 0x0CBC, 0x068E,
	0x3858, 0x035D, 0xCD26, 0x7FFF, 0xF961, 0x2425, 0xE907, 0x297A,
	0xC6F3, 0xF9C6, 0xBC91, 0x206D, 0xBC27, 0xC6AB, 0x2203, 0xB8D5,
	0xEA8B, 0x0959, 0x2D02, 0xD265, 0x3343, 0x0521, 0x4A77, 0xE225
	};

void test_benchmark_vec_add_q15(void)
{
	uint32_t irq_key, timestamp, timespan;
	q15_t *output;

	/* Allocate output buffer */
	output = malloc(PATTERN_LENGTH * sizeof(q15_t));
	zassert_not_null(output, "output buffer allocation failed");

	/* Begin benchmark */
	benchmark_begin(&irq_key, &timestamp);

	/* Execute function */
	arm_add_q15(input1, input2, output, PATTERN_LENGTH);

	/* End benchmark */
	timespan = benchmark_end(irq_key, timestamp);

	/* Free output buffer */
	free(output);

	/* Print result */
	TC_PRINT(BENCHMARK_TYPE " = %u\n", timespan);
}

void test_benchmark_vec_sub_q15(void)
{
	uint32_t irq_key, timestamp, timespan;
	q15_t *output;

	/* Allocate output buffer */
	output = malloc(PATTERN_LENGTH * sizeof(q15_t));
	zassert_not_null(output, "output buffer allocation failed");

	/* Begin benchmark */
	benchmark_begin(&irq_key, &timestamp);

	/* Execute function */
	arm_sub_q15(input1, input2, output, PATTERN_LENGTH);

	/* End benchmark */
	timespan = benchmark_end(irq_key, timestamp);

	/* Free output buffer */
	free(output);

	/* Print result */
	TC_PRINT(BENCHMARK_TYPE " = %u\n", timespan);
}

void test_benchmark_vec_mult_q15(void)
{
	uint32_t irq_key, timestamp, timespan;
	q15_t *output;

	/* Allocate output buffer */
	output = malloc(PATTERN_LENGTH * sizeof(q15_t));
	zassert_not_null(output, "output buffer allocation failed");

	/* Begin benchmark */
	benchmark_begin(&irq_key, &timestamp);

	/* Execute function */
	arm_mult_q15(input1, input2, output, PATTERN_LENGTH);

	/* End benchmark */
	timespan = benchmark_end(irq_key, timestamp);

	/* Free output buffer */
	free(output);

	/* Print result */
	TC_PRINT(BENCHMARK_TYPE " = %u\n", timespan);
}

void test_benchmark_vec_abs_q15(void)
{
	uint32_t irq_key, timestamp, timespan;
	q15_t *output;

	/* Allocate output buffer */
	output = malloc(PATTERN_LENGTH * sizeof(q15_t));
	zassert_not_null(output, "output buffer allocation failed");

	/* Begin benchmark */
	benchmark_begin(&irq_key, &timestamp);

	/* Execute function */
	arm_abs_q15(input1, output, PATTERN_LENGTH);

	/* End benchmark */
	timespan = benchmark_end(irq_key, timestamp);

	/* Free output buffer */
	free(output);

	/* Print result */
	TC_PRINT(BENCHMARK_TYPE " = %u\n", timespan);
}

void test_benchmark_vec_negate_q15(void)
{
	uint32_t irq_key, timestamp, timespan;
	q15_t *output;

	/* Allocate output buffer */
	output = malloc(PATTERN_LENGTH * sizeof(q15_t));
	zassert_not_null(output, "output buffer allocation failed");

	/* Begin benchmark */
	benchmark_begin(&irq_key, &timestamp);

	/* Execute function */
	arm_negate_q15(input1, output, PATTERN_LENGTH);

	/* End benchmark */
	timespan = benchmark_end(irq_key, timestamp);

	/* Free output buffer */
	free(output);

	/* Print result */
	TC_PRINT(BENCHMARK_TYPE " = %u\n", timespan);
}

void test_benchmark_vec_offset_q15(void)
{
	uint32_t irq_key, timestamp, timespan;
	q15_t *output;

	/* Allocate output buffer */
	output = malloc(PATTERN_LENGTH * sizeof(q15_t));
	zassert_not_null(output, "output buffer allocation failed");

	/* Begin benchmark */
	benchmark_begin(&irq_key, &timestamp);

	/* Execute function */
	arm_offset_q15(input1, 1.0, output, PATTERN_LENGTH);

	/* End benchmark */
	timespan = benchmark_end(irq_key, timestamp);

	/* Free output buffer */
	free(output);

	/* Print result */
	TC_PRINT(BENCHMARK_TYPE " = %u\n", timespan);
}

void test_benchmark_vec_scale_q15(void)
{
	uint32_t irq_key, timestamp, timespan;
	q15_t *output;

	/* Allocate output buffer */
	output = malloc(PATTERN_LENGTH * sizeof(q15_t));
	zassert_not_null(output, "output buffer allocation failed");

	/* Begin benchmark */
	benchmark_begin(&irq_key, &timestamp);

	/* Execute function */
	arm_scale_q15(input1, 0x45, 1, output, PATTERN_LENGTH);

	/* End benchmark */
	timespan = benchmark_end(irq_key, timestamp);

	/* Free output buffer */
	free(output);

	/* Print result */
	TC_PRINT(BENCHMARK_TYPE " = %u\n", timespan);
}

void test_benchmark_vec_dot_prod_q15(void)
{
	uint32_t irq_key, timestamp, timespan;
	q63_t output;

	/* Begin benchmark */
	benchmark_begin(&irq_key, &timestamp);

	/* Execute function */
	arm_dot_prod_q15(input1, input2, PATTERN_LENGTH, &output);

	/* End benchmark */
	timespan = benchmark_end(irq_key, timestamp);

	/* Print result */
	TC_PRINT(BENCHMARK_TYPE " = %u\n", timespan);
}

ztest_register_test_suite(basicmath_q15_benchmark, NULL,
			  ztest_unit_test(test_benchmark_vec_add_q15),
			  ztest_unit_test(test_benchmark_vec_sub_q15),
			  ztest_unit_test(test_benchmark_vec_mult_q15),
			  ztest_unit_test(test_benchmark_vec_abs_q15),
			  ztest_unit_test(test_benchmark_vec_negate_q15),
			  ztest_unit_test(test_benchmark_vec_offset_q15),
			  ztest_unit_test(test_benchmark_vec_scale_q15),
			  ztest_unit_test(test_benchmark_vec_dot_prod_q15));
