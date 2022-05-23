/* sensor_lsm6ds0.h - header file for LSM6DS0 accelerometer, gyroscope and
 * temperature sensor driver
 */

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_SENSOR_LSM6DS0_LSM6DS0_H_
#define ZEPHYR_DRIVERS_SENSOR_LSM6DS0_LSM6DS0_H_

#include <zephyr/types.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/util.h>

#define LSM6DS0_REG_ACT_THS                     0x04
#define LSM6DS0_MASK_ACT_THS_SLEEP_ON_INACT_EN	BIT(7)
#define LSM6DS0_SHIFT_ACT_THS_SLEEP_ON_INACT_EN	7
#define LSM6DS0_MASK_ACT_THS_ACT_THS		(BIT(6) | BIT(5) | BIT(4) | \
						 BIT(3) | BIT(2) | BIT(1) | \
						 BIT(0))
#define LSM6DS0_SHIFT_ACT_THS_ACT_THS		0

#define LSM6DS0_REG_ACT_DUR                     0x05

#define LSM6DS0_REG_INT_GEN_CFG_XL              0x06
#define LSM6DS0_MASK_INT_GEN_CFG_XL_AOI_XL	BIT(7)
#define LSM6DS0_SHIFT_INT_GEN_CFG_XL_AOI_XL	7
#define LSM6DSO_MASK_INT_GEN_CFG_XL_6D		BIT(6)
#define LSM6DS0_SHIFT_INT_GEN_CFG_XL_6D		6
#define LSM6DS0_MASK_INT_GEN_CFG_XL_ZHIE_XL	BIT(5)
#define LSM6DS0_SHIFT_INT_GEN_CFG_XL_ZHIE_XL	5
#define LSM6DS0_MASK_INT_GEN_CFG_XL_ZLIE_XL	BIT(4)
#define LSM6DS0_SHIFT_INT_GEN_CFG_XL_ZLIE_XL	4
#define LSM6DS0_MASK_INT_GEN_CFG_XL_YHIE_XL	BIT(3)
#define LSM6DS0_SHIFT_INT_GEN_CFG_XL_YHIE_XL	3
#define LSM6DS0_MASK_INT_GEN_CFG_XL_YLIE_XL	BIT(2)
#define LSM6DS0_SHIFT_INT_GEN_CFG_XL_YLIE_XL	2
#define LSM6DS0_MASK_INT_GEN_CFG_XL_XHIE_XL	BIT(1)
#define LSM6DS0_SHIFT_INT_GEN_CFG_XL_XHIE_XL	1
#define LSM6DS0_MASK_INT_GEN_CFG_XL_XLIE_XL	BIT(0)
#define LSM6DS0_SHIFT_INT_GEN_CFG_XL_XLIE_XL	0

#define LSM6DS0_REG_INT_GEN_THS_X_XL            0x07
#define LSM6DS0_REG_INT_GEN_THS_Y_XL            0x08
#define LSM6DS0_REG_INT_GEN_THS_Z_XL            0x09
#define LSM6DS0_REG_INT_GEN_DUR_XL              0x0A
#define LSM6DS0_REG_REFERENCE_G                 0x0B

#define LSM6DS0_REG_INT_CTRL                    0x0C
#define LSM6DS0_MASK_INT_CTRL_INT_IG_G		BIT(7)
#define LSM6DS0_SHIFT_INT_CTRL_INT_IG_G		7
#define LSM6DS0_MASK_INT_CTRL_INT_IG_XL		BIT(6)
#define LSM6DS0_SHIFT_INT_CTRL_INT_IG_XL	6
#define LSM6DS0_MASK_INT_CTRL_INT_FSS5		BIT(5)
#define LSM6DS0_SHIFT_INT_CTRL_INT_FSS5		5
#define LSM6DS0_MASK_INT_CTRL_INT_OVR		BIT(4)
#define LSM6DS0_SHIFT_INT_CTRL_INT_OVR		4
#define LSM6DS0_MASK_INT_CTRL_INT_FTH		BIT(3)
#define LSM6DS0_SHIFT_INT_CTRL_INT_FTH		3
#define LSM6DS0_MASK_INT_CTRL_INT_BOOT		BIT(2)
#define LSM6DS0_SHIFT_INT_CTRL_INT_BOOT		2
#define LSM6DS0_MASK_INT_CTRL_INT_DRDY_G	BIT(1)
#define LSM6DS0_SHIFT_INT_CTRL_INT_DRDY_G	1
#define LSM6DS0_MASK_INT_CTRL_INT_DRDY_XL	BIT(0)
#define LSM6DS0_SHIFT_INT_CTRL_INT_DRDY_XL	0

#define LSM6DS0_REG_WHO_AM_I                    0x0F
#define LSM6DS0_VAL_WHO_AM_I			0x68

#define LSM6DS0_REG_CTRL_REG1_G                 0x10
#define LSM6DS0_MASK_CTRL_REG1_G_ODR_G		(BIT(7) | BIT(6) | BIT(5))
#define LSM6DS0_SHIFT_CTRL_REG1_G_ODR_G		5
#define LSM6DS0_MASK_CTRL_REG1_G_FS_G		(BIT(4) | BIT(3))
#define LSM6DS0_SHIFT_CTRL_REG1_G_FS_G		3
#define LSM6DS0_MASK_CTRL_REG1_G_BW_G		(BIT(1) | BIT(0))
#define LSM6DS0_SHIFT_CTRL_REG1_G_BW_G		0

#define LSM6DS0_REG_CTRL_REG2_G                 0x11
#define LSM6DS0_MASK_CTRL_REG2_G_INT_SEL	(BIT(3) | BIT(2))
#define LSM6DS0_SHIFT_CTRL_REG2_G_INT_SEL	2
#define LSM6DS0_MASK_CTRL_REG2_G_OUT_SEL	(BIT(1) | BIT(0))
#define LSM6DS0_SHIFT_CTRL_REG2_G_OUT_SEL	0

#define LSM6DS0_REG_CTRL_REG3_G                 0x12
#define LSM6DS0_MASK_CTRL_REG3_G_LP_MODE	BIT(7)
#define LSM6DS0_SHIFT_CTRL_REG3_G_LP_MODE	7
#define LSM6DS0_MASK_CTRL_REG3_G_HP_EN		BIT(6)
#define LSM6DS0_SHIFT_CTRL_REG3_G_HP_EN		6
#define LSM6DS0_MASK_CTRL_REG3_G_HPCF_G		(BIT(3) | BIT(2) | BIT(1) | \
						 BIT(0))
#define LSM6DS0_SHIFT_CTRL_REG3_G_HPCF_G	0

#define LSM6DS0_REG_ORIENT_CFG_G                0x13
#define LSM6DS0_MASK_ORIENT_CFG_G_SIGNX_G	BIT(5)
#define LSM6DS0_SHIFT_ORIENT_CFG_G_SIGNX_G	5
#define LSM6DS0_MASK_ORIENT_CFG_G_SIGNY_G	BIT(4)
#define LSM6DS0_SHIFT_ORIENT_CFG_G_SIGNY_G	4
#define LSM6DS0_MASK_ORIENT_CFG_G_SIGNZ_G	BIT(3)
#define LSM6DS0_SHIFT_ORIENT_CFG_G_SIGNZ_G	3
#define LSM6DS0_MASK_ORIENT_CFG_ORIENT		(BIT(2) | BIT(1) | BIT(0))
#define LSM6DS0_SHIFT_ORIENT_CFG_ORIENT		0

#define LSM6DS0_REG_INT_GEN_SRC_G               0x14
#define LSM6DS0_MASK_INT_GEN_SRC_G_IA_G		BIT(6)
#define LSM6DS0_SHIFT_INT_GEN_SRC_G_IA_G	6
#define LSM6DS0_MASK_INT_GEN_SRC_G_ZH_G		BIT(5)
#define LSM6DS0_SHIFT_INT_GEN_SRC_G_ZH_G	5
#define LSM6DS0_MASK_INT_GEN_SRC_G_ZL_G		BIT(4)
#define LSM6DS0_SHIFT_INT_GEN_SRC_G_ZL_G	4
#define LSM6DS0_MASK_INT_GEN_SRC_G_YH_G		BIT(3)
#define LSM6DS0_SHIFT_INT_GEN_SRC_G_YH_G	3
#define LSM6DS0_MASK_INT_GEN_SRC_G_YL_G		BIT(2)
#define LSM6DS0_SHIFT_INT_GEN_SRC_G_YL_G	2
#define LSM6DS0_MASK_INT_GEN_SRC_G_XH_G		BIT(1)
#define LSM6DS0_SHIFT_INT_GEN_SRC_G_XH_G	1
#define LSM6DS0_MASK_INT_GEN_SRC_G_XL_G		BIT(0)
#define LSM6DS0_SHIFT_INT_GEN_SRC_G_XL_G	0

#define LSM6DS0_REG_OUT_TEMP_L                  0x15
#define LSM6DS0_REG_OUT_TEMP_H                  0x16

#define LSM6DS0_REG_STATUS_REG_G                0x17
#define LSM6DS0_MASK_STATUS_REG_G_IG_XL		BIT(6)
#define LSM6DS0_SHIFT_STATUS_REG_G_IG_XL	6
#define LSM6DS0_MASK_STATUS_REG_G_IG_G		BIT(5)
#define LSM6DS0_SHIFT_STATUS_REG_G_IG_G		5
#define LSM6DS0_MASK_STATUS_REG_G_INACT		BIT(4)
#define LSM6DS0_SHIFT_STATUS_REG_G_INACT	4
#define LSM6DS0_MASK_STATUS_REG_G_BOOT_STATUS	BIT(3)
#define LSM6DS0_SHIFT_STATUS_REG_G_BOOT_STATUS	3
#define LSM6DS0_MASK_STATUS_REG_G_TDA		BIT(2)
#define LSM6DS0_SHIFT_STATUS_REG_G_TDA		2
#define LSM6DS0_MASK_STATUS_REG_G_GDA		BIT(1)
#define LSM6DS0_SHIFT_STATUS_REG_G_GDA		1
#define LSM6DS0_MASK_STATUS_REG_G_XLDA		BIT(0)
#define LSM6DS0_SHIFT_STATUS_REG_G_XLDA		0

#define LSM6DS0_REG_OUT_X_L_G                   0x18
#define LSM6DS0_REG_OUT_X_H_G                   0x19
#define LSM6DS0_REG_OUT_Y_L_G                   0x1A
#define LSM6DS0_REG_OUT_Y_H_G                   0x1B
#define LSM6DS0_REG_OUT_Z_L_G                   0x1C
#define LSM6DS0_REG_OUT_Z_H_G                   0x1D

#define LSM6DS0_REG_CTRL_REG4                   0x1E
#define LSM6DS0_MASK_CTRL_REG4_ZEN_G		BIT(5)
#define LSM6DS0_SHIFT_CTRL_REG4_ZEN_G		5
#define LSM6DS0_MASK_CTRL_REG4_YEN_G		BIT(4)
#define LSM6DS0_SHIFT_CTRL_REG4_YEN_G		4
#define LSM6DS0_MASK_CTRL_REG4_XEN_G		BIT(3)
#define LSM6DS0_SHIFT_CTRL_REG4_XEN_G		3
#define LSM6DS0_MASK_CTRL_REG4_LIR_XL1		BIT(1)
#define LSM6DS0_SHIFT_CTRL_REG4_LIR_XL1		1
#define LSM6DS0_MASK_CTRL_REG4_4D_XL1		BIT(0)
#define LSM6DS0_SHIFT_CTRL_REG4_4D_XL1		0

#define LSM6DS0_REG_CTRL_REG5_XL                0x1F
#define LSM6DS0_MASK_CTRL_REG5_XL_DEC		(BIT(7) | BIT(6))
#define LSM6DS0_SHIFT_CTRL_REG5_XL_DEC		6
#define LSM6DS0_MASK_CTRL_REG5_XL_ZEN_XL	BIT(5)
#define LSM6DS0_SHIFT_CTRL_REG5_XL_ZEN_XL	5
#define LSM6DS0_MASK_CTRL_REG5_XL_YEN_XL	BIT(4)
#define LSM6DS0_SHIFT_CTRL_REG5_XL_YEN_XL	4
#define LSM6DS0_MASK_CTRL_REG5_XL_XEN_XL	BIT(3)
#define LSM6DS0_SHIFT_CTRL_REG5_XL_XEN_XL	3

#define LSM6DS0_REG_CTRL_REG6_XL                0x20
#define LSM6DS0_MASK_CTRL_REG6_XL_ODR_XL	(BIT(7) | BIT(6) | BIT(5))
#define LSM6DS0_SHIFT_CTRL_REG6_XL_ODR_XL	5
#define LSM6DS0_MASK_CTRL_REG6_XL_FS_XL		(BIT(4) | BIT(3))
#define LSM6DS0_SHIFT_CTRL_REG6_XL_FS_XL	3
#define LSM6DS0_MASK_CTRL_REG6_XL_BW_SCAL_ODR	BIT(2)
#define LSM6DS0_SHIFT_CTRL_REG6_XL_BW_SCAL_ODR	2
#define LSM6DS0_MASK_CTRL_REG6_XL_BW_XL		(BIT(1) | BIT(0))
#define LSM6DS0_SHIFT_CTRL_REG6_XL_BW_XL	0

#define LSM6DS0_REG_CTRL_REG7_XL                0x21
#define LSM6DS0_MASK_CTRL_REG7_XL_HR		BIT(7)
#define LSM6DS0_SHIFT_CTRL_REG7_XL_HR		7
#define LSM6DS0_MASK_CTRL_REG7_XL_DCF		(BIT(6) | BIT(5))
#define LSM6DS0_SHIFT_CTRL_REG7_XL_DCF		5
#define LSM6DS0_MASK_CTRL_REG7_XL_FDS		BIT(2)
#define LSM6DS0_SHIFT_CTRL_REG7_XL_FDS		2
#define LSM6DS0_MASK_CTRL_REG7_XL_HPIS1		BIT(0)
#define LSM6DS0_SHIFT_CTRL_REG7_XL_HPIS		0

#define LSM6DS0_REG_CTRL_REG8                   0x22
#define LSM6DS0_MASK_CTRL_REG8_BOOT		BIT(7)
#define LSM6DS0_SHIFT_CTRL_REG8_BOOT		7
#define LSM6DS0_MASK_CTRL_REG8_BDU		BIT(6)
#define LSM6DS0_SHIFT_CTRL_REG8_BDU		6
#define LSM6DS0_MASK_CTRL_REG8_H_LACTIVE	BIT(5)
#define LSM6DS0_SHIFT_CTRL_REG8_H_LACTIVE	5
#define LSM6DS0_MASK_CTRL_REG8_PP_OD		BIT(4)
#define LSM6DS0_SHIFT_CTRL_REG8_PP_OD		4
#define LSM6DS0_MASK_CTRL_REG8_SIM		BIT(3)
#define LSM6DS0_SHIFT_CTRL_REG8_SIM		3
#define LSM6DS0_MASK_CTRL_REG8_IF_ADD_INC	BIT(2)
#define LSM6DS0_SHIFT_CTRL_REG8_IF_ADD_INC	2
#define LSM6DS0_MASK_CTRL_REG8_BLE		BIT(1)
#define LSM6DS0_SHIFT_CTRL_REG8_BLE		1
#define LSM6DS0_MASK_CTRL_REG8_SW_RESET		BIT(0)
#define LSM6DS0_SHIFT_CTRL_REG8_SW_RESET	0

#define LSM6DS0_REG_CTRL_REG9                   0x23
#define LSM6DS0_MASK_CTRL_REG9_SLEEP_G		BIT(6)
#define LSM6DS0_SHIFT_CTRL_REG9_SLEEP_G		6
#define LSM6DS0_MASK_CTRL_REG9_FIFO_TEMP_EN	BIT(4)
#define LSM6DS0_SHIFT_CTRL_REG9_FIFO_TEMP_EN	4
#define LSM6DS0_MASK_CTRL_REG9_DRDY_MASK_BIT	BIT(3)
#define LSM6DS0_SHIFT_CTRL_REG9_DRDY_MASK_BIT	3
#define LSM6DS0_MASK_CTRL_REG9_DRDY_I2C_DIS	BIT(2)
#define LSM6DS0_SHIFT_CTRL_REG9_DRDY_I2C_DIS	2
#define LSM6DS0_MASK_CTRL_REG9_FIFO_EN		BIT(1)
#define LSM6DS0_SHIFT_CTRL_REG9_FIFO_EN		1
#define LSM6DS0_MASK_CTRL_REG9_STOP_ON_FTH	BIT(0)
#define LSM6DS0_SHIFT_CTRL_REG9_STOP_ON_FTH	0

#define LSM6DS0_REG_CTRL_REG10                  0x24
#define LSM6DS0_MASK_CTRL_REG10_ST_G		BIT(2)
#define LSM6DS0_SHIFT_CTRL_REG10_ST_G		2
#define LSM6DS0_MASK_CTRL_REG10_ST_XL		BIT(0)
#define LSM6DS0_SHIFT_CTRL_REG10_ST_XL		0

#define LSM6DS0_REG_INT_GEN_SRC_XL              0x26
#define LSM6DS0_MASK_INT_GEN_SRC_XL_IA_XL	BIT(6)
#define LSM6DS0_SHIFT_INT_GEN_SRC_XL_IA_XL	6
#define LSM6DS0_MASK_INT_GEN_SRC_XL_ZH_XL	BIT(5)
#define LSM6DS0_SHIFT_INT_GEN_SRC_XL_ZH_XL	5
#define LSM6DS0_MASK_INT_GEN_SRC_XL_ZL_XL	BIT(4)
#define LSM6DS0_SHIFT_INT_GEN_SRC_XL_ZL_XL	4
#define LSM6DS0_MASK_INT_GEN_SRC_XL_YH_XL	BIT(3)
#define LSM6DS0_SHIFT_INT_GEN_SRC_XL_YH_XL	3
#define LSM6DS0_MASK_INT_GEN_SRC_XL_YL_XL	BIT(2)
#define LSM6DS0_SHIFT_INT_GEN_SRC_XL_YL_XL	2
#define LSM6DS0_MASK_INT_GEN_SRC_XL_XH_XL	BIT(1)
#define LSM6DS0_SHIFT_INT_GEN_SRC_XL_XH_XL	1
#define LSM6DS0_MASK_INT_GEN_SRC_XL_XL_XL	BIT(0)
#define LSM6DS0_SHIFT_INT_GEN_SRC_XL_XL_XL	0

#define LSM6DS0_REG_STATUS_REG_XL		0x27
#define LSM6DS0_MASK_STATUS_REG_XL_IG_XL	BIT(6)
#define LSM6DS0_SHIFT_STATUS_REG_XL_IG_XL	6
#define LSM6DS0_MASK_STATUS_REG_XL_IG_G		BIT(5)
#define LSM6DS0_SHIFT_STATUS_REG_XL_IG_G	5
#define LSM6DS0_MASK_STATUS_REG_XL_INACT	BIT(4)
#define LSM6DS0_SHIFT_STATUS_REG_XL_INACT	4
#define LSM6DS0_MASK_STATUS_REG_XL_BOOT_STATUS	BIT(3)
#define LSM6DS0_SHIFT_STATUS_REG_XL_BOOT_STATUS	3
#define LSM6DS0_MASK_STATUS_REG_XL_TDA		BIT(2)
#define LSM6DS0_SHIFT_STATUS_REG_XL_TDA		2
#define LSM6DS0_MASK_STATUS_REG_XL_GDA		BIT(1)
#define LSM6DS0_SHIFT_STATUS_REG_XL_GDA		1
#define LSM6DS0_MASK_STATUS_REG_XL_XLDA		BIT(0)
#define LSM6DS0_SHIFT_STATUS_REG_XL_XLDA	0

#define LSM6DS0_REG_OUT_X_L_XL                  0x28
#define LSM6DS0_REG_OUT_X_H_XL                  0x29
#define LSM6DS0_REG_OUT_Y_L_XL                  0x2A
#define LSM6DS0_REG_OUT_Y_H_XL                  0x2B
#define LSM6DS0_REG_OUT_Z_L_XL                  0x2C
#define LSM6DS0_REG_OUT_Z_H_XL                  0x2D

#define LSM6DS0_REG_FIFO_CTRL                   0x2E
#define LSM6DS0_MASK_FIFO_CTRL_FMODE		(BIT(7) | BIT(6) | BIT(5))
#define LSM6DS0_SHIFT_FIFO_CTRL_FMODE		5
#define LSM6DS0_MASK_FIFO_CTRL_FTH		(BIT(4) | BIT(3) | BIT(2) | \
						 BIT(1) | BIT(0))
#define LSM6DS0_SHIFT_FIFO_CTRL_FTH		0

#define LSM6DS0_REG_FIFO_SRC                    0x2F
#define LSM6DS0_MASK_FIFO_SRC_FTH		BIT(7)
#define LSM6DS0_SHIFT_FIFO_SRC_FTH		7
#define LSM6DS0_MASK_FIFO_SRC_OVRN		BIT(6)
#define LSM6DS0_SHIFT_FIFO_SRC_OVRN		6
#define LSM6DS0_MASK_FIFO_SRC_FSS		(BIT(5) | BIT(4) | BIT(3) | \
						 BIT(2) | BIT(1) | BIT(0))
#define LSM6DS0_SHIFT_FIFO_SRC_FSS		0

#define LSM6DS0_REG_INT_GEN_CFG_G               0x30
#define LSM6DS0_MASK_INT_GEN_CFG_G_AOI_G	BIT(7)
#define LSM6DS0_SHIFT_INT_GEN_CFG_G_AOI_G	7
#define LSM6DS0_MASK_INT_GEN_CFG_G_LIR_G	BIT(6)
#define LSM6DS0_SHIFT_INT_GEN_CFG_G_LIR_G	6
#define LSM6DS0_MASK_INT_GEN_CFG_G_ZHIE_G	BIT(5)
#define LSM6DS0_SHIFT_INT_GEN_CFG_G_ZHIE_G	5
#define LSM6DS0_MASK_INT_GEN_CFG_G_ZLIE_G	BIT(4)
#define LSM6DS0_SHIFT_INT_GEN_CFG_G_ZLIE_G	4
#define LSM6DS0_MASK_INT_GEN_CFG_G_YHIE_G	BIT(3)
#define LSM6DS0_SHIFT_INT_GEN_CFG_G_YHIE_G	3
#define LSM6DS0_MASK_INT_GEN_CFG_G_YLIE_G	BIT(2)
#define LSM6DS0_SHIFT_INT_GEN_CFG_G_YLIE_G	2
#define LSM6DS0_MASK_INT_GEN_CFG_G_XHIE_G	BIT(1)
#define LSM6DS0_SHIFT_INT_GEN_CFG_G_XHIE_G	1
#define LSM6DS0_MASK_INT_GEN_CFG_G_XLIE_G	BIT(0)
#define LSM6DS0_SHIFT_INT_GEN_CFG_G_XLIE_G	0

#define LSM6DS0_REG_INT_GEN_THS_XH_G            0x31
#define LSM6DS0_MASK_INT_GEN_THS_XH_G_DCRM_G	BIT(7)
#define LSM6DS0_SHIFT_INT_GEN_THS_XH_G_DCRM_G	7

#define LSM6DS0_REG_INT_GEN_THS_XL_G            0x32
#define LSM6DS0_REG_INT_GEN_THS_YH_G            0x33
#define LSM6DS0_REG_INT_GEN_THS_YL_G            0x34
#define LSM6DS0_REG_INT_GEN_THS_ZH_G            0x35
#define LSM6DS0_REG_INT_GEN_THS_ZL_G            0x36

#define LSM6DS0_REG_INT_GEN_DUR_G               0x37
#define LSM6DS0_MASK_INT_GEN_DUR_G_WAIT_G	BIT(7)
#define LSM6DS0_SHIFT_INT_GEN_DUR_G_WAIT_G	7

#define SENSOR_G_DOUBLE		(SENSOR_G / 1000000.0)
#define SENSOR_PI_DOUBLE	(SENSOR_PI / 1000000.0)
#define SENSOR_DEG2RAD_DOUBLE	(SENSOR_PI_DOUBLE / 180)

#if defined(CONFIG_LSM6DS0_ACCEL_ENABLE_X_AXIS)
	#define LSM6DS0_ACCEL_ENABLE_X_AXIS		1
#else
	#define LSM6DS0_ACCEL_ENABLE_X_AXIS		0
#endif

#if defined(CONFIG_LSM6DS0_ACCEL_ENABLE_Y_AXIS)
	#define LSM6DS0_ACCEL_ENABLE_Y_AXIS		1
#else
	#define LSM6DS0_ACCEL_ENABLE_Y_AXIS		0
#endif

#if defined(CONFIG_LSM6DS0_ACCEL_ENABLE_Z_AXIS)
	#define LSM6DS0_ACCEL_ENABLE_Z_AXIS		1
#else
	#define LSM6DS0_ACCEL_ENABLE_Z_AXIS		0
#endif

#if defined(CONFIG_LSM6DS0_GYRO_ENABLE_X_AXIS)
	#define LSM6DS0_GYRO_ENABLE_X_AXIS		1
#else
	#define LSM6DS0_GYRO_ENABLE_X_AXIS		0
#endif

#if defined(CONFIG_LSM6DS0_GYRO_ENABLE_Y_AXIS)
	#define LSM6DS0_GYRO_ENABLE_Y_AXIS		1
#else
	#define LSM6DS0_GYRO_ENABLE_Y_AXIS		0
#endif

#if defined(CONFIG_LSM6DS0_GYRO_ENABLE_Z_AXIS)
	#define LSM6DS0_GYRO_ENABLE_Z_AXIS		1
#else
	#define LSM6DS0_GYRO_ENABLE_Z_AXIS		0
#endif

#if CONFIG_LSM6DS0_ACCEL_FULLSCALE == 2
	#define LSM6DS0_ACCEL_FULLSCALE_2G
#elif CONFIG_LSM6DS0_ACCEL_FULLSCALE == 4
	#define LSM6DS0_ACCEL_FULLSCALE_4G
#elif CONFIG_LSM6DS0_ACCEL_FULLSCALE == 8
	#define LSM6DS0_ACCEL_FULLSCALE_8G
#elif CONFIG_LSM6DS0_ACCEL_FULLSCALE == 16
	#define LSM6DS0_ACCEL_FULLSCALE_16G
#endif

#if defined(LSM6DS0_ACCEL_FULLSCALE_2G)
	#define LSM6DS0_DEFAULT_ACCEL_FULLSCALE		0
	#define LSM6DS0_DEFAULT_ACCEL_FULLSCALE_FACTOR	(2.0 * SENSOR_G_DOUBLE)
#elif defined(LSM6DS0_ACCEL_FULLSCALE_4G)
	#define LSM6DS0_DEFAULT_ACCEL_FULLSCALE		2
	#define LSM6DS0_DEFAULT_ACCEL_FULLSCALE_FACTOR	(4.0 * SENSOR_G_DOUBLE)
#elif defined(LSM6DS0_ACCEL_FULLSCALE_8G)
	#define LSM6DS0_DEFAULT_ACCEL_FULLSCALE		3
	#define LSM6DS0_DEFAULT_ACCEL_FULLSCALE_FACTOR	(8.0 * SENSOR_G_DOUBLE)
#elif defined(LSM6DS0_ACCEL_FULLSCALE_16G)
	#define LSM6DS0_DEFAULT_ACCEL_FULLSCALE		1
	#define LSM6DS0_DEFAULT_ACCEL_FULLSCALE_FACTOR	(16.0 * SENSOR_G_DOUBLE)
#endif

#if CONFIG_LSM6DS0_ACCEL_SAMPLING_RATE == 0
	#define LSM6DS0_ACCEL_SAMPLING_RATE_0
#elif CONFIG_LSM6DS0_ACCEL_SAMPLING_RATE == 10
	#define LSM6DS0_ACCEL_SAMPLING_RATE_10
#elif CONFIG_LSM6DS0_ACCEL_SAMPLING_RATE == 50
	#define LSM6DS0_ACCEL_SAMPLING_RATE_50
#elif CONFIG_LSM6DS0_ACCEL_SAMPLING_RATE == 119
	#define LSM6DS0_ACCEL_SAMPLING_RATE_119
#elif CONFIG_LSM6DS0_ACCEL_SAMPLING_RATE == 238
	#define LSM6DS0_ACCEL_SAMPLING_RATE_238
#elif CONFIG_LSM6DS0_ACCEL_SAMPLING_RATE == 476
	#define LSM6DS0_ACCEL_SAMPLING_RATE_476
#elif CONFIG_LSM6DS0_ACCEL_SAMPLING_RATE == 952
	#define LSM6DS0_ACCEL_SAMPLING_RATE_952
#endif

#if defined(LSM6DS0_ACCEL_SAMPLING_RATE_0)
	#define LSM6DS0_DEFAULT_ACCEL_SAMPLING_RATE	0
#elif defined(LSM6DS0_ACCEL_SAMPLING_RATE_10)
	#define LSM6DS0_DEFAULT_ACCEL_SAMPLING_RATE	1
#elif defined(LSM6DS0_ACCEL_SAMPLING_RATE_50)
	#define LSM6DS0_DEFAULT_ACCEL_SAMPLING_RATE	2
#elif defined(LSM6DS0_ACCEL_SAMPLING_RATE_119)
	#define LSM6DS0_DEFAULT_ACCEL_SAMPLING_RATE	3
#elif defined(LSM6DS0_ACCEL_SAMPLING_RATE_238)
	#define LSM6DS0_DEFAULT_ACCEL_SAMPLING_RATE	4
#elif defined(LSM6DS0_ACCEL_SAMPLING_RATE_476)
	#define LSM6DS0_DEFAULT_ACCEL_SAMPLING_RATE	5
#elif defined(LSM6DS0_ACCEL_SAMPLING_RATE_952)
	#define LSM6DS0_DEFAULT_ACCEL_SAMPLING_RATE	6
#endif

#if CONFIG_LSM6DS0_GYRO_FULLSCALE == 245
	#define LSM6DS0_GYRO_FULLSCALE_245
#elif CONFIG_LSM6DS0_GYRO_FULLSCALE == 500
	#define LSM6DS0_GYRO_FULLSCALE_500
#elif CONFIG_LSM6DS0_GYRO_FULLSCALE == 2000
	#define LSM6DS0_GYRO_FULLSCALE_2000
#endif

#if defined(LSM6DS0_GYRO_FULLSCALE_245)
	#define LSM6DS0_DEFAULT_GYRO_FULLSCALE		0
	#define LSM6DS0_DEFAULT_GYRO_FULLSCALE_FACTOR	8.75
#elif defined(LSM6DS0_GYRO_FULLSCALE_500)
	#define LSM6DS0_DEFAULT_GYRO_FULLSCALE		1
	#define LSM6DS0_DEFAULT_GYRO_FULLSCALE_FACTOR	17.50
#elif defined(LSM6DS0_GYRO_FULLSCALE_2000)
	#define LSM6DS0_DEFAULT_GYRO_FULLSCALE		3
	#define LSM6DS0_DEFAULT_GYRO_FULLSCALE_FACTOR	70.0
#endif

#if CONFIG_LSM6DS0_GYRO_SAMPLING_RATE == 0
	#define LSM6DS0_GYRO_SAMPLING_RATE_0
#elif CONFIG_LSM6DS0_GYRO_SAMPLING_RATE == 15
	#define LSM6DS0_GYRO_SAMPLING_RATE_14_9
#elif CONFIG_LSM6DS0_GYRO_SAMPLING_RATE == 60
	#define LSM6DS0_GYRO_SAMPLING_RATE_59_5
#elif CONFIG_LSM6DS0_GYRO_SAMPLING_RATE == 119
	#define LSM6DS0_GYRO_SAMPLING_RATE_119
#elif CONFIG_LSM6DS0_GYRO_SAMPLING_RATE == 238
	#define LSM6DS0_GYRO_SAMPLING_RATE_238
#elif CONFIG_LSM6DS0_GYRO_SAMPLING_RATE == 476
	#define LSM6DS0_GYRO_SAMPLING_RATE_476
#elif CONFIG_LSM6DS0_GYRO_SAMPLING_RATE == 952
	#define LSM6DS0_GYRO_SAMPLING_RATE_952
#endif

#if defined(LSM6DS0_GYRO_SAMPLING_RATE_0)
	#define LSM6DS0_DEFAULT_GYRO_SAMPLING_RATE	0
#elif defined(LSM6DS0_GYRO_SAMPLING_RATE_14_9)
	#define LSM6DS0_DEFAULT_GYRO_SAMPLING_RATE	1
#elif defined(LSM6DS0_GYRO_SAMPLING_RATE_59_5)
	#define LSM6DS0_DEFAULT_GYRO_SAMPLING_RATE	2
#elif defined(LSM6DS0_GYRO_SAMPLING_RATE_119)
	#define LSM6DS0_DEFAULT_GYRO_SAMPLING_RATE	3
#elif defined(LSM6DS0_GYRO_SAMPLING_RATE_238)
	#define LSM6DS0_DEFAULT_GYRO_SAMPLING_RATE	4
#elif defined(LSM6DS0_GYRO_SAMPLING_RATE_476)
	#define LSM6DS0_DEFAULT_GYRO_SAMPLING_RATE	5
#elif defined(LSM6DS0_GYRO_SAMPLING_RATE_952)
	#define LSM6DS0_DEFAULT_GYRO_SAMPLING_RATE	6
#endif

struct lsm6ds0_config {
	char *i2c_master_dev_name;
	uint16_t i2c_slave_addr;
};

struct lsm6ds0_data {
	const struct device *i2c_master;

#if defined(CONFIG_LSM6DS0_ACCEL_ENABLE_X_AXIS)
	int accel_sample_x;
#endif
#if defined(CONFIG_LSM6DS0_ACCEL_ENABLE_Y_AXIS)
	int accel_sample_y;
#endif
#if defined(CONFIG_LSM6DS0_ACCEL_ENABLE_Z_AXIS)
	int accel_sample_z;
#endif

#if defined(CONFIG_LSM6DS0_GYRO_ENABLE_X_AXIS)
	int gyro_sample_x;
#endif
#if defined(CONFIG_LSM6DS0_GYRO_ENABLE_Y_AXIS)
	int gyro_sample_y;
#endif
#if defined(CONFIG_LSM6DS0_GYRO_ENABLE_Z_AXIS)
	int gyro_sample_z;
#endif

#if defined(CONFIG_LSM6DS0_ENABLE_TEMP)
	int temp_sample;
#endif
};

#endif /* ZEPHYR_DRIVERS_SENSOR_LSM6DS0_LSM6DS0_H_ */
