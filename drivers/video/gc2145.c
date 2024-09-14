/*
 * Copyright (c) 2024 Felipe Neves
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT galaxycore_gc2145
#include <zephyr/kernel.h>
#include <zephyr/device.h>

#include <zephyr/drivers/video.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(video_gc2145, CONFIG_VIDEO_LOG_LEVEL);

#define GC2145_REG_AMODE1               0x17
#define GC2145_AMODE1_WINDOW_MASK       0xFC
#define GC2145_REG_AMODE1_DEF           0x14
#define GC2145_REG_OUTPUT_FMT           0x84
#define GC2145_REG_OUTPUT_FMT_RGB565    0x06
#define GC2145_REG_SYNC_MODE            0x86
#define GC2145_REG_SYNC_MODE_DEF        0x23
#define GC2145_REG_SYNC_MODE_COL_SWITCH 0x10
#define GC2145_REG_SYNC_MODE_ROW_SWITCH 0x20
#define GC2145_REG_RESET                0xFE
#define GC2145_REG_SW_RESET             0x80
#define GC2145_PID_VAL                  0x21
#define GC2145_REV_VAL                  0x55
#define GC2145_SET_P0_REGS              0x00
#define GC2145_REG_CROP_ENABLE          0x90
#define GC2145_CROP_SET_ENABLE          0x01
#define GC2145_REG_BLANK_WINDOW_BASE    0x09
#define GC2145_REG_WINDOW_BASE          0x91
#define GC2145_REG_SUBSAMPLE            0x99
#define GC2145_REG_SUBSAMPLE_MODE       0x9A
#define GC2145_SUBSAMPLE_MODE_SMOOTH    0x0E

#define UXGA_HSIZE 1600
#define UXGA_VSIZE 1200

struct gc2145_reg {
	uint8_t addr;
	uint8_t value;
};

static const struct gc2145_reg default_regs[] = {
	{0xfe, 0xf0},
	{0xfe, 0xf0},
	{0xfe, 0xf0},
	{0xfc, 0x06},
	{0xf6, 0x00},
	{0xf7, 0x1d},
	{0xf8, 0x85},
	{0xfa, 0x00},
	{0xf9, 0xfe},
	{0xf2, 0x00},

	/* ISP settings */
	{0xfe, 0x00},
	{0x03, 0x04},
	{0x04, 0xe2},

	{0x09, 0x00},
	{0x0a, 0x00},

	{0x0b, 0x00},
	{0x0c, 0x00},

	{0x0d, 0x04}, /* Window height */
	{0x0e, 0xc0},

	{0x0f, 0x06}, /* Window width */
	{0x10, 0x52},

	{0x99, 0x11}, /* Subsample */
	{0x9a, 0x0E}, /* Subsample mode */

	{0x12, 0x2e},
	{GC2145_REG_OUTPUT_FMT, 0x14}, /* Analog Mode 1 (vflip/mirror[1:0]) */
	{0x18, 0x22},                  /* Analog Mode 2 */
	{0x19, 0x0e},
	{0x1a, 0x01},
	{0x1b, 0x4b},
	{0x1c, 0x07},
	{0x1d, 0x10},
	{0x1e, 0x88},
	{0x1f, 0x78},
	{0x20, 0x03},
	{0x21, 0x40},
	{0x22, 0xa0},
	{0x24, 0x16},
	{0x25, 0x01},
	{0x26, 0x10},
	{0x2d, 0x60},
	{0x30, 0x01},
	{0x31, 0x90},
	{0x33, 0x06},
	{0x34, 0x01},
	{0x80, 0x7f},
	{0x81, 0x26},
	{0x82, 0xfa},
	{0x83, 0x00},
	{GC2145_REG_OUTPUT_FMT, 0x06},
	{GC2145_REG_SYNC_MODE, 0x23},
	{0x88, 0x03},
	{0x89, 0x03},
	{0x85, 0x08},
	{0x8a, 0x00},
	{0x8b, 0x00},
	{0xb0, 0x55},
	{0xc3, 0x00},
	{0xc4, 0x80},
	{0xc5, 0x90},
	{0xc6, 0x3b},
	{0xc7, 0x46},
	{0xec, 0x06},
	{0xed, 0x04},
	{0xee, 0x60},
	{0xef, 0x90},
	{0xb6, 0x01},

	{0x90, 0x01},
	{0x91, 0x00},
	{0x92, 0x00},
	{0x93, 0x00},
	{0x94, 0x00},
	{0x95, 0x02},
	{0x96, 0x58},
	{0x97, 0x03},
	{0x98, 0x20},
	{0x99, 0x22},
	{0x9a, 0x0E},

	{0x9b, 0x00},
	{0x9c, 0x00},
	{0x9d, 0x00},
	{0x9e, 0x00},
	{0x9f, 0x00},
	{0xa0, 0x00},
	{0xa1, 0x00},
	{0xa2, 0x00},

	/* BLK Settings */
	{0xfe, 0x00},
	{0x40, 0x42},
	{0x41, 0x00},
	{0x43, 0x5b},
	{0x5e, 0x00},
	{0x5f, 0x00},
	{0x60, 0x00},
	{0x61, 0x00},
	{0x62, 0x00},
	{0x63, 0x00},
	{0x64, 0x00},
	{0x65, 0x00},
	{0x66, 0x20},
	{0x67, 0x20},
	{0x68, 0x20},
	{0x69, 0x20},
	{0x76, 0x00},
	{0x6a, 0x08},
	{0x6b, 0x08},
	{0x6c, 0x08},
	{0x6d, 0x08},
	{0x6e, 0x08},
	{0x6f, 0x08},
	{0x70, 0x08},
	{0x71, 0x08},
	{0x76, 0x00},
	{0x72, 0xf0},
	{0x7e, 0x3c},
	{0x7f, 0x00},
	{0xfe, 0x02},
	{0x48, 0x15},
	{0x49, 0x00},
	{0x4b, 0x0b},
	{0xfe, 0x00},

	/* AEC Settings */
	{0xfe, 0x01},
	{0x01, 0x04},
	{0x02, 0xc0},
	{0x03, 0x04},
	{0x04, 0x90},
	{0x05, 0x30},
	{0x06, 0x90},
	{0x07, 0x30},
	{0x08, 0x80},
	{0x09, 0x00},
	{0x0a, 0x82},
	{0x0b, 0x11},
	{0x0c, 0x10},
	{0x11, 0x10},
	{0x13, 0x68},
	{GC2145_REG_OUTPUT_FMT, 0x00},
	{0x1c, 0x11},
	{0x1e, 0x61},
	{0x1f, 0x35},
	{0x20, 0x40},
	{0x22, 0x40},
	{0x23, 0x20},
	{0xfe, 0x02},
	{0x0f, 0x04},
	{0xfe, 0x01},
	{0x12, 0x30},
	{0x15, 0xb0},
	{0x10, 0x31},
	{0x3e, 0x28},
	{0x3f, 0xb0},
	{0x40, 0x90},
	{0x41, 0x0f},
	{0xfe, 0x02},
	{0x90, 0x6c},
	{0x91, 0x03},
	{0x92, 0xcb},
	{0x94, 0x33},
	{0x95, 0x84},
	{0x97, 0x65},
	{0xa2, 0x11},
	{0xfe, 0x00},
	{0xfe, 0x02},
	{0x80, 0xc1},
	{0x81, 0x08},
	{0x82, 0x05},
	{0x83, 0x08},
	{GC2145_REG_OUTPUT_FMT, 0x0a},
	{GC2145_REG_SYNC_MODE, 0xf0},
	{0x87, 0x50},
	{0x88, 0x15},
	{0x89, 0xb0},
	{0x8a, 0x30},
	{0x8b, 0x10},
	{0xfe, 0x01},
	{0x21, 0x04},
	{0xfe, 0x02},
	{0xa3, 0x50},
	{0xa4, 0x20},
	{0xa5, 0x40},
	{0xa6, 0x80},
	{0xab, 0x40},
	{0xae, 0x0c},
	{0xb3, 0x46},
	{0xb4, 0x64},
	{0xb6, 0x38},
	{0xb7, 0x01},
	{0xb9, 0x2b},
	{0x3c, 0x04},
	{0x3d, 0x15},
	{0x4b, 0x06},
	{0x4c, 0x20},
	{0xfe, 0x00},

	/* Gamma Control */
	{0xfe, 0x02},
	{0x10, 0x09},
	{0x11, 0x0d},
	{0x12, 0x13},
	{0x13, 0x19},
	{0x14, 0x27},
	{0x15, 0x37},
	{0x16, 0x45},
	{GC2145_REG_OUTPUT_FMT, 0x53},
	{0x18, 0x69},
	{0x19, 0x7d},
	{0x1a, 0x8f},
	{0x1b, 0x9d},
	{0x1c, 0xa9},
	{0x1d, 0xbd},
	{0x1e, 0xcd},
	{0x1f, 0xd9},
	{0x20, 0xe3},
	{0x21, 0xea},
	{0x22, 0xef},
	{0x23, 0xf5},
	{0x24, 0xf9},
	{0x25, 0xff},
	{0xfe, 0x00},
	{0xc6, 0x20},
	{0xc7, 0x2b},
	{0xfe, 0x02},
	{0x26, 0x0f},
	{0x27, 0x14},
	{0x28, 0x19},
	{0x29, 0x1e},
	{0x2a, 0x27},
	{0x2b, 0x33},
	{0x2c, 0x3b},
	{0x2d, 0x45},
	{0x2e, 0x59},
	{0x2f, 0x69},
	{0x30, 0x7c},
	{0x31, 0x89},
	{0x32, 0x98},
	{0x33, 0xae},
	{0x34, 0xc0},
	{0x35, 0xcf},
	{0x36, 0xda},
	{0x37, 0xe2},
	{0x38, 0xe9},
	{0x39, 0xf3},
	{0x3a, 0xf9},
	{0x3b, 0xff},
	{0xfe, 0x02},
	{0xd1, 0x32},
	{0xd2, 0x32},
	{0xd3, 0x40},
	{0xd6, 0xf0},
	{0xd7, 0x10},
	{0xd8, 0xda},
	{0xdd, 0x14},
	{0xde, 0x86},
	{0xed, 0x80},
	{0xee, 0x00},
	{0xef, 0x3f},
	{0xd8, 0xd8},
	{0xfe, 0x01},
	{0x9f, 0x40},
	{0xfe, 0x01},
	{0xc2, 0x14},
	{0xc3, 0x0d},
	{0xc4, 0x0c},
	{0xc8, 0x15},
	{0xc9, 0x0d},
	{0xca, 0x0a},
	{0xbc, 0x24},
	{0xbd, 0x10},
	{0xbe, 0x0b},
	{0xb6, 0x25},
	{0xb7, 0x16},
	{0xb8, 0x15},
	{0xc5, 0x00},
	{0xc6, 0x00},
	{0xc7, 0x00},
	{0xcb, 0x00},
	{0xcc, 0x00},
	{0xcd, 0x00},
	{0xbf, 0x07},
	{0xc0, 0x00},
	{0xc1, 0x00},
	{0xb9, 0x00},
	{0xba, 0x00},
	{0xbb, 0x00},
	{0xaa, 0x01},
	{0xab, 0x01},
	{0xac, 0x00},
	{0xad, 0x05},
	{0xae, 0x06},
	{0xaf, 0x0e},
	{0xb0, 0x0b},
	{0xb1, 0x07},
	{0xb2, 0x06},
	{0xb3, 0x17},
	{0xb4, 0x0e},
	{0xb5, 0x0e},
	{0xd0, 0x09},
	{0xd1, 0x00},
	{0xd2, 0x00},
	{0xd6, 0x08},
	{0xd7, 0x00},
	{0xd8, 0x00},
	{0xd9, 0x00},
	{0xda, 0x00},
	{0xdb, 0x00},
	{0xd3, 0x0a},
	{0xd4, 0x00},
	{0xd5, 0x00},
	{0xa4, 0x00},
	{0xa5, 0x00},
	{0xa6, 0x77},
	{0xa7, 0x77},
	{0xa8, 0x77},
	{0xa9, 0x77},
	{0xa1, 0x80},
	{0xa2, 0x80},

	{0xfe, 0x01},
	{0xdf, 0x0d},
	{0xdc, 0x25},
	{0xdd, 0x30},
	{0xe0, 0x77},
	{0xe1, 0x80},
	{0xe2, 0x77},
	{0xe3, 0x90},
	{0xe6, 0x90},
	{0xe7, 0xa0},
	{0xe8, 0x90},
	{0xe9, 0xa0},
	{0xfe, 0x00},
	{0xfe, 0x01},
	{0x4f, 0x00},
	{0x4f, 0x00},
	{0x4b, 0x01},
	{0x4f, 0x00},

	{0x4c, 0x01},
	{0x4d, 0x71},
	{0x4e, 0x01},
	{0x4c, 0x01},
	{0x4d, 0x91},
	{0x4e, 0x01},
	{0x4c, 0x01},
	{0x4d, 0x70},
	{0x4e, 0x01},
	{0x4c, 0x01},
	{0x4d, 0x90},
	{0x4e, 0x02},
	{0x4c, 0x01},
	{0x4d, 0xb0},
	{0x4e, 0x02},
	{0x4c, 0x01},
	{0x4d, 0x8f},
	{0x4e, 0x02},
	{0x4c, 0x01},
	{0x4d, 0x6f},
	{0x4e, 0x02},
	{0x4c, 0x01},
	{0x4d, 0xaf},
	{0x4e, 0x02},
	{0x4c, 0x01},
	{0x4d, 0xd0},
	{0x4e, 0x02},
	{0x4c, 0x01},
	{0x4d, 0xf0},
	{0x4e, 0x02},
	{0x4c, 0x01},
	{0x4d, 0xcf},
	{0x4e, 0x02},
	{0x4c, 0x01},
	{0x4d, 0xef},
	{0x4e, 0x02},
	{0x4c, 0x01},
	{0x4d, 0x6e},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0x8e},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0xae},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0xce},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0x4d},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0x6d},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0x8d},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0xad},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0xcd},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0x4c},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0x6c},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0x8c},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0xac},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0xcc},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0xcb},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0x4b},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0x6b},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0x8b},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0xab},
	{0x4e, 0x03},
	{0x4c, 0x01},
	{0x4d, 0x8a},
	{0x4e, 0x04},
	{0x4c, 0x01},
	{0x4d, 0xaa},
	{0x4e, 0x04},
	{0x4c, 0x01},
	{0x4d, 0xca},
	{0x4e, 0x04},
	{0x4c, 0x01},
	{0x4d, 0xca},
	{0x4e, 0x04},
	{0x4c, 0x01},
	{0x4d, 0xc9},
	{0x4e, 0x04},
	{0x4c, 0x01},
	{0x4d, 0x8a},
	{0x4e, 0x04},
	{0x4c, 0x01},
	{0x4d, 0x89},
	{0x4e, 0x04},
	{0x4c, 0x01},
	{0x4d, 0xa9},
	{0x4e, 0x04},
	{0x4c, 0x02},
	{0x4d, 0x0b},
	{0x4e, 0x05},
	{0x4c, 0x02},
	{0x4d, 0x0a},
	{0x4e, 0x05},
	{0x4c, 0x01},
	{0x4d, 0xeb},
	{0x4e, 0x05},
	{0x4c, 0x01},
	{0x4d, 0xea},
	{0x4e, 0x05},
	{0x4c, 0x02},
	{0x4d, 0x09},
	{0x4e, 0x05},
	{0x4c, 0x02},
	{0x4d, 0x29},
	{0x4e, 0x05},
	{0x4c, 0x02},
	{0x4d, 0x2a},
	{0x4e, 0x05},
	{0x4c, 0x02},
	{0x4d, 0x4a},
	{0x4e, 0x05},
	{0x4c, 0x02},
	{0x4d, 0x8a},
	{0x4e, 0x06},
	{0x4c, 0x02},
	{0x4d, 0x49},
	{0x4e, 0x06},
	{0x4c, 0x02},
	{0x4d, 0x69},
	{0x4e, 0x06},
	{0x4c, 0x02},
	{0x4d, 0x89},
	{0x4e, 0x06},
	{0x4c, 0x02},
	{0x4d, 0xa9},
	{0x4e, 0x06},
	{0x4c, 0x02},
	{0x4d, 0x48},
	{0x4e, 0x06},
	{0x4c, 0x02},
	{0x4d, 0x68},
	{0x4e, 0x06},
	{0x4c, 0x02},
	{0x4d, 0x69},
	{0x4e, 0x06},
	{0x4c, 0x02},
	{0x4d, 0xca},
	{0x4e, 0x07},
	{0x4c, 0x02},
	{0x4d, 0xc9},
	{0x4e, 0x07},
	{0x4c, 0x02},
	{0x4d, 0xe9},
	{0x4e, 0x07},
	{0x4c, 0x03},
	{0x4d, 0x09},
	{0x4e, 0x07},
	{0x4c, 0x02},
	{0x4d, 0xc8},
	{0x4e, 0x07},
	{0x4c, 0x02},
	{0x4d, 0xe8},
	{0x4e, 0x07},
	{0x4c, 0x02},
	{0x4d, 0xa7},
	{0x4e, 0x07},
	{0x4c, 0x02},
	{0x4d, 0xc7},
	{0x4e, 0x07},
	{0x4c, 0x02},
	{0x4d, 0xe7},
	{0x4e, 0x07},
	{0x4c, 0x03},
	{0x4d, 0x07},
	{0x4e, 0x07},

	{0x4f, 0x01},
	{0x50, 0x80},
	{0x51, 0xa8},
	{0x52, 0x47},
	{0x53, 0x38},
	{0x54, 0xc7},
	{0x56, 0x0e},
	{0x58, 0x08},
	{0x5b, 0x00},
	{0x5c, 0x74},
	{0x5d, 0x8b},
	{0x61, 0xdb},
	{0x62, 0xb8},
	{0x63, 0x86},
	{0x64, 0xc0},
	{0x65, 0x04},
	{0x67, 0xa8},
	{0x68, 0xb0},
	{0x69, 0x00},
	{0x6a, 0xa8},
	{0x6b, 0xb0},
	{0x6c, 0xaf},
	{0x6d, 0x8b},
	{0x6e, 0x50},
	{0x6f, 0x18},
	{0x73, 0xf0},
	{0x70, 0x0d},
	{0x71, 0x60},
	{0x72, 0x80},
	{0x74, 0x01},
	{0x75, 0x01},
	{0x7f, 0x0c},
	{0x76, 0x70},
	{0x77, 0x58},
	{0x78, 0xa0},
	{0x79, 0x5e},
	{0x7a, 0x54},
	{0x7b, 0x58},
	{0xfe, 0x00},
	{0xfe, 0x02},
	{0xc0, 0x01},
	{0xc1, 0x44},
	{0xc2, 0xfd},
	{0xc3, 0x04},
	{0xc4, 0xF0},
	{0xc5, 0x48},
	{0xc6, 0xfd},
	{0xc7, 0x46},
	{0xc8, 0xfd},
	{0xc9, 0x02},
	{0xca, 0xe0},
	{0xcb, 0x45},
	{0xcc, 0xec},
	{0xcd, 0x48},
	{0xce, 0xf0},
	{0xcf, 0xf0},
	{0xe3, 0x0c},
	{0xe4, 0x4b},
	{0xe5, 0xe0},
	{0xfe, 0x01},
	{0x9f, 0x40},
	{0xfe, 0x00},

	/* Output Control  */
	{0xfe, 0x00},
	{0xf2, 0x0f},
	{0xfe, 0x02},
	{0x40, 0xbf},
	{0x46, 0xcf},
	{0xfe, 0x00},

	{0xfe, 0x00},
	{0x05, 0x01},
	{0x06, 0x1C},
	{0x07, 0x00},
	{0x08, 0x32},
	{0x11, 0x00},
	{0x12, 0x1D},
	{0x13, 0x00},
	{0x14, 0x00},

	{0xfe, 0x01},
	{0x3c, 0x00},
	{0x3d, 0x04},
	{0xfe, 0x00},
	{0x00, 0x00},
};

struct gc2145_config {
	struct i2c_dt_spec i2c;
#if DT_INST_NODE_HAS_PROP(0, reset_gpios)
	struct gpio_dt_spec reset_gpio;
#endif
};

struct gc2145_data {
	struct video_format fmt;
};

#define GC2145_VIDEO_FORMAT_CAP(width, height, format) \
	{                                              \
	.pixelformat = format,                         \
	.width_min = width,                            \
	.width_max = width,                            \
	.height_min = height,                          \
	.height_max = height,                          \
	.width_step = 0,                               \
	.height_step = 0,                              \
	}

static const struct video_format_cap fmts[] = {
	GC2145_VIDEO_FORMAT_CAP(1600, 1200, VIDEO_PIX_FMT_RGB565), /* UXGA  */
	{0},
};

static int gc2145_write_reg(const struct i2c_dt_spec *spec, uint8_t reg_addr, uint8_t value)
{
	int ret;
	uint8_t tries = 3;

	/*
	 * It rarely happens that the camera does not respond with ACK signal.
	 * In that case it usually responds on 2nd try but there is a 3rd one
	 * just to be sure that the connection error is not caused by driver
	 * itself.
	 */
	do {
		ret = i2c_reg_write_byte_dt(spec, reg_addr, value);
		if (!ret) {
			return 0;
		}
		/* If writing failed wait 5ms before next attempt */
		k_msleep(5);

	} while (tries--);

	LOG_ERR("failed to write 0x%x to 0x%x,", value, reg_addr);
	return ret;
}

static int gc2145_read_reg(const struct i2c_dt_spec *spec, uint8_t reg_addr, uint8_t *value)
{
	int ret;
	uint8_t tries = 3;

	/*
	 * It rarely happens that the camera does not respond with ACK signal.
	 * In that case it usually responds on 2nd try but there is a 3rd one
	 * just to be sure that the connection error is not caused by driver
	 * itself.
	 */
	do {
		ret = i2c_reg_read_byte_dt(spec, reg_addr, value);
		if (!ret) {
			return 0;
		}
		/* If writing failed wait 5ms before next attempt */
		k_msleep(5);

	} while (tries--);

	LOG_ERR("failed to read 0x%x register", reg_addr);
	return ret;
}

static int gc2145_write_all(const struct device *dev, const struct gc2145_reg *regs,
			    uint16_t reg_num)
{
	const struct gc2145_config *cfg = dev->config;

	for (uint16_t i = 0; i < reg_num; i++) {
		int ret;

		ret = gc2145_write_reg(&cfg->i2c, regs[i].addr, regs[i].value);
		if (ret < 0) {
			return ret;
		}
	}

	return 0;
}

static int gc2145_soft_reset(const struct device *dev)
{
	int ret;
	const struct gc2145_config *cfg = dev->config;

	/* Initiate system reset */
	ret = gc2145_write_reg(&cfg->i2c, GC2145_REG_RESET, GC2145_REG_SW_RESET);

	k_msleep(300);

	return ret;
}

static int gc2145_set_ctrl_vflip(const struct device *dev, bool enable)
{
	int ret;
	const struct gc2145_config *cfg = dev->config;
	uint8_t old_value;

	ret = gc2145_read_reg(&cfg->i2c, GC2145_REG_AMODE1, &old_value);
	if (ret < 0) {
		return ret;
	}

	/* Set the vertical flip state */
	return gc2145_write_reg(&cfg->i2c, GC2145_REG_AMODE1,
				(old_value & GC2145_AMODE1_WINDOW_MASK) | (enable << 1));
}

static int gc2145_set_ctrl_hmirror(const struct device *dev, bool enable)
{
	int ret;
	const struct gc2145_config *cfg = dev->config;
	uint8_t old_value;

	ret = gc2145_read_reg(&cfg->i2c, GC2145_REG_AMODE1, &old_value);
	if (ret < 0) {
		return ret;
	}

	/* Set the horizontal mirror state */
	return gc2145_write_reg(&cfg->i2c, GC2145_REG_AMODE1,
				(old_value & GC2145_AMODE1_WINDOW_MASK) | enable);
}

static int gc2145_set_window(const struct device *dev, uint16_t reg, uint16_t x, uint16_t y,
			     uint16_t w, uint16_t h)
{
	int ret;
	const struct gc2145_config *cfg = dev->config;

	ret = gc2145_write_reg(&cfg->i2c, GC2145_REG_RESET, GC2145_SET_P0_REGS);
	if (ret < 0) {
		return ret;
	}

	/* Y/row offset */
	ret = gc2145_write_reg(&cfg->i2c, reg++, y >> 8);
	if (ret < 0) {
		return ret;
	}

	ret = gc2145_write_reg(&cfg->i2c, reg++, y & 0xff);
	if (ret < 0) {
		return ret;
	}

	/* X/col offset */
	ret = gc2145_write_reg(&cfg->i2c, reg++, x >> 8);
	if (ret < 0) {
		return ret;
	}

	ret = gc2145_write_reg(&cfg->i2c, reg++, x & 0xff);
	if (ret < 0) {
		return ret;
	}

	/* Window height */
	ret = gc2145_write_reg(&cfg->i2c, reg++, h >> 8);
	if (ret < 0) {
		return ret;
	}

	ret = gc2145_write_reg(&cfg->i2c, reg++, h & 0xff);
	if (ret < 0) {
		return ret;
	}

	/* Window width */
	ret = gc2145_write_reg(&cfg->i2c, reg++, w >> 8);
	if (ret < 0) {
		return ret;
	}

	ret = gc2145_write_reg(&cfg->i2c, reg++, w & 0xff);
	if (ret < 0) {
		return ret;
	}

	return ret;
}

static int gc2145_set_output_format(const struct device *dev, int output_format)
{
	int ret;
	const struct gc2145_config *cfg = dev->config;

	ret = gc2145_write_reg(&cfg->i2c, GC2145_REG_RESET, GC2145_SET_P0_REGS);
	if (ret < 0) {
		return ret;
	}

	if (output_format != VIDEO_PIX_FMT_RGB565) {
		LOG_ERR("Image format not supported");
		return -ENOTSUP;
	}

	/* Disable JPEG compression and set output to RGB565 */
	ret = gc2145_write_reg(&cfg->i2c, GC2145_REG_OUTPUT_FMT, GC2145_REG_OUTPUT_FMT_RGB565);
	if (ret < 0) {
		return ret;
	}

	k_sleep(K_MSEC(30));

	return 0;
}

static int gc2145_set_resolution(const struct device *dev, uint16_t img_width, uint16_t img_height)
{
	int ret;
	const struct gc2145_config *cfg = dev->config;

	uint16_t win_w = UXGA_HSIZE + 16;
	uint16_t win_h = UXGA_VSIZE + 8;
	uint16_t c_ratio = 1;
	uint16_t r_ratio = 1;
	uint16_t x = (((win_w / c_ratio) - UXGA_HSIZE) / 2);
	uint16_t y = (((win_h / r_ratio) - UXGA_VSIZE) / 2);
	uint16_t win_x = ((UXGA_HSIZE - win_w) / 2);
	uint16_t win_y = ((UXGA_VSIZE - win_h) / 2);

	/* Set readout window first. */
	ret = gc2145_set_window(dev, GC2145_REG_BLANK_WINDOW_BASE, win_x, win_y, win_w, win_h);
	if (ret < 0) {
		return ret;
	}

	/* Set cropping window next. */
	ret = gc2145_set_window(dev, GC2145_REG_WINDOW_BASE, x, y, 1, 1);
	if (ret < 0) {
		return ret;
	}

	/* Enable crop */
	ret = gc2145_write_reg(&cfg->i2c, GC2145_REG_CROP_ENABLE, GC2145_CROP_SET_ENABLE);
	if (ret < 0) {
		return ret;
	}

	/* Set Sub-sampling ratio and mode */
	ret = gc2145_write_reg(&cfg->i2c, GC2145_REG_SUBSAMPLE, ((r_ratio << 4) | c_ratio));
	if (ret < 0) {
		return ret;
	}

	ret = gc2145_write_reg(&cfg->i2c, GC2145_REG_SUBSAMPLE_MODE, GC2145_SUBSAMPLE_MODE_SMOOTH);
	if (ret < 0) {
		return ret;
	}
	/*
	 * Galaxy Core datasheet does not document the reason behind of this
	 * and other short delay requirements, but the reason exposed by them
	 * is to give enough time for the sensor DSP to handle the I2C transaction
	 * give some time time to apply the changes before the next instruction.
	 */
	k_sleep(K_MSEC(30));

	return 0;
}

static uint8_t gc2145_check_connection(const struct device *dev)
{
	int ret;
	const struct gc2145_config *cfg = dev->config;
	uint8_t reg_pid_val;
	uint8_t reg_ver_val;

	ret = gc2145_read_reg(&cfg->i2c, 0xf0, &reg_pid_val);
	if (ret < 0) {
		return ret;
	}

	ret = gc2145_read_reg(&cfg->i2c, 0xf1, &reg_ver_val);
	if (ret < 0) {
		return ret;
	}

	if ((reg_ver_val != GC2145_REV_VAL) || (reg_pid_val != GC2145_PID_VAL)) {
		LOG_ERR("failed to detect GC2145 pid: 0x%x rev: 0x%x", reg_pid_val, reg_ver_val);
		return -EIO;
	}

	return 0;
}

static int gc2145_set_fmt(const struct device *dev, enum video_endpoint_id ep,
			  struct video_format *fmt)
{
	struct gc2145_data *drv_data = dev->data;
	uint16_t width, height;
	int ret;

	/* We only support RGB565 formats */
	if (fmt->pixelformat != VIDEO_PIX_FMT_RGB565) {
		LOG_ERR("gc2145 camera supports only RGB565");
		return -ENOTSUP;
	}

	width = fmt->width;
	height = fmt->height;

	if (memcmp(&drv_data->fmt, fmt, sizeof(drv_data->fmt)) == 0) {
		/* nothing to do */
		return 0;
	}

	drv_data->fmt = *fmt;

	/* Set output format */
	ret = gc2145_set_output_format(dev, fmt->pixelformat);
	if (ret < 0) {
		LOG_ERR("Failed to set the output format");
		return ret;
	}

	/* Check if camera is capable of handling given format */
	for (int i = 0; i < ARRAY_SIZE(fmts); i++) {
		if (fmts[i].width_min == width && fmts[i].height_min == height &&
		    fmts[i].pixelformat == fmt->pixelformat) {
			/* Set window size */
			ret = gc2145_set_resolution(dev, fmt->width, fmt->height);
			if (ret < 0) {
				LOG_ERR("Failed to set the resolution");
			}
			return ret;
		}
	}

	/* Camera is not capable of handling given format */
	LOG_ERR("Image format not supported\n");
	return -ENOTSUP;
}

static int gc2145_get_fmt(const struct device *dev, enum video_endpoint_id ep,
			  struct video_format *fmt)
{
	struct gc2145_data *drv_data = dev->data;

	*fmt = drv_data->fmt;

	return 0;
}

static int gc2145_stream_start(const struct device *dev)
{
	const struct gc2145_config *cfg = dev->config;

	return gc2145_write_reg(&cfg->i2c, 0xf2, 0x0f);
}

static int gc2145_stream_stop(const struct device *dev)
{
	const struct gc2145_config *cfg = dev->config;

	return gc2145_write_reg(&cfg->i2c, 0xf2, 0x00);
}

static int gc2145_get_caps(const struct device *dev, enum video_endpoint_id ep,
			   struct video_caps *caps)
{
	caps->format_caps = fmts;
	return 0;
}

static int gc2145_set_ctrl(const struct device *dev, unsigned int cid, void *value)
{
	switch (cid) {
	case VIDEO_CID_HFLIP:
		return gc2145_set_ctrl_hmirror(dev, (int)value);
	case VIDEO_CID_VFLIP:
		return gc2145_set_ctrl_vflip(dev, (int)value);
	default:
		return -ENOTSUP;
	}
}

static const struct video_driver_api gc2145_driver_api = {
	.set_format = gc2145_set_fmt,
	.get_format = gc2145_get_fmt,
	.get_caps = gc2145_get_caps,
	.stream_start = gc2145_stream_start,
	.stream_stop = gc2145_stream_stop,
	.set_ctrl = gc2145_set_ctrl,
};

static int gc2145_init(const struct device *dev)
{
	struct video_format fmt;
	int ret;

#if DT_INST_NODE_HAS_PROP(0, reset_gpios)
	const struct gc2145_config *cfg = dev->config;

	ret = gpio_pin_configure_dt(&cfg->reset_gpio, GPIO_OUTPUT_ACTIVE);
	if (ret) {
		return ret;
	}

	k_sleep(K_MSEC(1));
	gpio_pin_set_dt(&cfg->reset_gpio, 0);
	k_sleep(K_MSEC(1));
#endif

	ret = gc2145_check_connection(dev);
	if (ret) {
		return ret;
	}

	gc2145_soft_reset(dev);
	gc2145_write_all(dev, default_regs, ARRAY_SIZE(default_regs));

	/* set default/init format SVGA RGB565 */
	fmt.pixelformat = VIDEO_PIX_FMT_RGB565;
	fmt.width = UXGA_HSIZE;
	fmt.height = UXGA_VSIZE;
	fmt.pitch = UXGA_HSIZE * 2;
	ret = gc2145_set_fmt(dev, VIDEO_EP_OUT, &fmt);
	if (ret) {
		LOG_ERR("Unable to configure default format");
		return -EIO;
	}
	return ret;
}

/* Unique Instance */
static const struct gc2145_config gc2145_cfg_0 = {
	.i2c = I2C_DT_SPEC_INST_GET(0),
#if DT_INST_NODE_HAS_PROP(0, reset_gpios)
	.reset_gpio = GPIO_DT_SPEC_INST_GET(0, reset_gpios),
#endif
};
static struct gc2145_data gc2145_data_0;

static int gc2145_init_0(const struct device *dev)
{
	const struct gc2145_config *cfg = dev->config;

	if (!i2c_is_ready_dt(&cfg->i2c)) {
		LOG_ERR("Bus device is not ready");
		return -ENODEV;
	}

#if DT_INST_NODE_HAS_PROP(0, reset_gpios)
	if (!gpio_is_ready_dt(&cfg->reset_gpio)) {
		LOG_ERR("%s: device %s is not ready", dev->name, cfg->reset_gpio.port->name);
		return -ENODEV;
	}
#endif

	return gc2145_init(dev);
}

DEVICE_DT_INST_DEFINE(0, &gc2145_init_0, NULL, &gc2145_data_0, &gc2145_cfg_0, POST_KERNEL,
		      CONFIG_VIDEO_INIT_PRIORITY, &gc2145_driver_api);
