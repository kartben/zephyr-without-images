/*
 * Copyright (c) 2022 Espressif Systems (Shanghai) Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_ESP32_GPIO_SIGMAP_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_ESP32_GPIO_SIGMAP_H_

#define ESP_NOSIG			ESP_SIG_INVAL

#define ESP_SPICLK_IN			0
#define ESP_SPICLK_OUT			0
#define ESP_SPIQ_IN			1
#define ESP_SPIQ_OUT			1
#define ESP_SPID_IN			2
#define ESP_SPID_OUT			2
#define ESP_SPIHD_IN			3
#define ESP_SPIHD_OUT			3
#define ESP_SPIWP_IN			4
#define ESP_SPIWP_OUT			4
#define ESP_SPICS0_IN			5
#define ESP_SPICS0_OUT			5
#define ESP_SPICS1_IN			6
#define ESP_SPICS1_OUT			6
#define ESP_SPICS2_IN			7
#define ESP_SPICS2_OUT			7
#define ESP_HSPICLK_IN			8
#define ESP_HSPICLK_OUT			8
#define ESP_HSPIQ_IN			9
#define ESP_HSPIQ_OUT			9
#define ESP_HSPID_IN			10
#define ESP_HSPID_OUT			10
#define ESP_HSPICS0_IN			11
#define ESP_HSPICS0_OUT			11
#define ESP_HSPIHD_IN			12
#define ESP_HSPIHD_OUT			12
#define ESP_HSPIWP_IN			13
#define ESP_HSPIWP_OUT			13
#define ESP_U0RXD_IN			14
#define ESP_U0TXD_OUT			14
#define ESP_U0CTS_IN			15
#define ESP_U0RTS_OUT			15
#define ESP_U0DSR_IN			16
#define ESP_U0DTR_OUT			16
#define ESP_U1RXD_IN			17
#define ESP_U1TXD_OUT			17
#define ESP_U1CTS_IN			18
#define ESP_U1RTS_OUT			18
#define ESP_I2CM_SCL_O			19
#define ESP_I2CM_SDA_I			20
#define ESP_I2CM_SDA_O			20
#define ESP_EXT_I2C_SCL_O		21
#define ESP_EXT_I2C_SDA_O		22
#define ESP_EXT_I2C_SDA_I		22
#define ESP_I2S0O_BCK_IN		23
#define ESP_I2S0O_BCK_OUT		23
#define ESP_I2S1O_BCK_IN		24
#define ESP_I2S1O_BCK_OUT		24
#define ESP_I2S0O_WS_IN			25
#define ESP_I2S0O_WS_OUT		25
#define ESP_I2S1O_WS_IN			26
#define ESP_I2S1O_WS_OUT		26
#define ESP_I2S0I_BCK_IN		27
#define ESP_I2S0I_BCK_OUT		27
#define ESP_I2S0I_WS_IN			28
#define ESP_I2S0I_WS_OUT		28
#define ESP_I2CEXT0_SCL_IN		29
#define ESP_I2CEXT0_SCL_OUT		29
#define ESP_I2CEXT0_SDA_IN		30
#define ESP_I2CEXT0_SDA_OUT		30
#define ESP_PWM0_SYNC0_IN		31
#define ESP_SDIO_TOHOST_INT_OUT		31
#define ESP_PWM0_SYNC1_IN		32
#define ESP_PWM0_OUT0A			32
#define ESP_PWM0_SYNC2_IN		33
#define ESP_PWM0_OUT0B			33
#define ESP_PWM0_F0_IN			34
#define ESP_PWM0_OUT1A			34
#define ESP_PWM0_F1_IN			35
#define ESP_PWM0_OUT1B			35
#define ESP_PWM0_F2_IN			36
#define ESP_PWM0_OUT2A			36
#define ESP_GPIO_BT_ACTIVE		37
#define ESP_PWM0_OUT2B			37
#define ESP_GPIO_BT_PRIORITY		38
#define ESP_PCNT_SIG_CH0_IN0		39
#define ESP_PCNT_SIG_CH1_IN0		40
#define ESP_GPIO_WLAN_ACTIVE		40
#define ESP_PCNT_CTRL_CH0_IN0		41
#define ESP_BB_DIAG0			41
#define ESP_PCNT_CTRL_CH1_IN0		42
#define ESP_BB_DIAG1			42
#define ESP_PCNT_SIG_CH0_IN1		43
#define ESP_BB_DIAG2			43
#define ESP_PCNT_SIG_CH1_IN1		44
#define ESP_BB_DIAG3			44
#define ESP_PCNT_CTRL_CH0_IN1		45
#define ESP_BB_DIAG4			45
#define ESP_PCNT_CTRL_CH1_IN1		46
#define ESP_BB_DIAG5			46
#define ESP_PCNT_SIG_CH0_IN2		47
#define ESP_BB_DIAG6			47
#define ESP_PCNT_SIG_CH1_IN2		48
#define ESP_BB_DIAG7			48
#define ESP_PCNT_CTRL_CH0_IN2		49
#define ESP_BB_DIAG8			49
#define ESP_PCNT_CTRL_CH1_IN2		50
#define ESP_BB_DIAG9			50
#define ESP_PCNT_SIG_CH0_IN3		51
#define ESP_BB_DIAG10			51
#define ESP_PCNT_SIG_CH1_IN3		52
#define ESP_BB_DIAG11			52
#define ESP_PCNT_CTRL_CH0_IN3		53
#define ESP_BB_DIAG12			53
#define ESP_PCNT_CTRL_CH1_IN3		54
#define ESP_BB_DIAG13			54
#define ESP_PCNT_SIG_CH0_IN4		55
#define ESP_BB_DIAG14			55
#define ESP_PCNT_SIG_CH1_IN4		56
#define ESP_BB_DIAG15			56
#define ESP_PCNT_CTRL_CH0_IN4		57
#define ESP_BB_DIAG16			57
#define ESP_PCNT_CTRL_CH1_IN4		58
#define ESP_BB_DIAG17			58
#define ESP_BB_DIAG18			59
#define ESP_BB_DIAG19			60
#define ESP_HSPICS1_IN			61
#define ESP_HSPICS1_OUT			61
#define ESP_HSPICS2_IN			62
#define ESP_HSPICS2_OUT			62
#define ESP_VSPICLK_IN			63
#define ESP_VSPICLK_OUT			63
#define ESP_VSPIQ_IN			64
#define ESP_VSPIQ_OUT			64
#define ESP_VSPID_IN			65
#define ESP_VSPID_OUT			65
#define ESP_VSPIHD_IN			66
#define ESP_VSPIHD_OUT			66
#define ESP_VSPIWP_IN			67
#define ESP_VSPIWP_OUT			67
#define ESP_VSPICS0_IN			68
#define ESP_VSPICS0_OUT			68
#define ESP_VSPICS1_IN			69
#define ESP_VSPICS1_OUT			69
#define ESP_VSPICS2_IN			70
#define ESP_VSPICS2_OUT			70
#define ESP_PCNT_SIG_CH0_IN5		71
#define ESP_LEDC_HS_SIG_OUT0		71
#define ESP_PCNT_SIG_CH1_IN5		72
#define ESP_LEDC_HS_SIG_OUT1		72
#define ESP_PCNT_CTRL_CH0_IN5		73
#define ESP_LEDC_HS_SIG_OUT2		73
#define ESP_PCNT_CTRL_CH1_IN5		74
#define ESP_LEDC_HS_SIG_OUT3		74
#define ESP_PCNT_SIG_CH0_IN6		75
#define ESP_LEDC_HS_SIG_OUT4		75
#define ESP_PCNT_SIG_CH1_IN6		76
#define ESP_LEDC_HS_SIG_OUT5		76
#define ESP_PCNT_CTRL_CH0_IN6		77
#define ESP_LEDC_HS_SIG_OUT6		77
#define ESP_PCNT_CTRL_CH1_IN6		78
#define ESP_LEDC_HS_SIG_OUT7		78
#define ESP_PCNT_SIG_CH0_IN7		79
#define ESP_LEDC_LS_SIG_OUT0		79
#define ESP_PCNT_SIG_CH1_IN7		80
#define ESP_LEDC_LS_SIG_OUT1		80
#define ESP_PCNT_CTRL_CH0_IN7		81
#define ESP_LEDC_LS_SIG_OUT2		81
#define ESP_PCNT_CTRL_CH1_IN7		82
#define ESP_LEDC_LS_SIG_OUT3		82
#define ESP_RMT_SIG_IN0			83
#define ESP_LEDC_LS_SIG_OUT4		83
#define ESP_RMT_SIG_IN1			84
#define ESP_LEDC_LS_SIG_OUT5		84
#define ESP_RMT_SIG_IN2			85
#define ESP_LEDC_LS_SIG_OUT6		85
#define ESP_RMT_SIG_IN3			86
#define ESP_LEDC_LS_SIG_OUT7		86
#define ESP_RMT_SIG_IN4			87
#define ESP_RMT_SIG_OUT0		87
#define ESP_RMT_SIG_IN5			88
#define ESP_RMT_SIG_OUT1		88
#define ESP_RMT_SIG_IN6			89
#define ESP_RMT_SIG_OUT2		89
#define ESP_RMT_SIG_IN7			90
#define ESP_RMT_SIG_OUT3		90
#define ESP_RMT_SIG_OUT4		91
#define ESP_RMT_SIG_OUT5		92
#define ESP_EXT_ADC_START		93
#define ESP_RMT_SIG_OUT6		93
#define ESP_TWAI_RX			94
#define ESP_CAN_RX			ESP_TWAI_RX
#define ESP_RMT_SIG_OUT7		94
#define ESP_I2CEXT1_SCL_IN		95
#define ESP_I2CEXT1_SCL_OUT		95
#define ESP_I2CEXT1_SDA_IN		96
#define ESP_I2CEXT1_SDA_OUT		96
#define ESP_HOST_CARD_DETECT_N_1	97
#define ESP_HOST_CCMD_OD_PULLUP_EN_N	97
#define ESP_HOST_CARD_DETECT_N_2	98
#define ESP_HOST_RST_N_1		98
#define ESP_HOST_CARD_WRITE_PRT_1	99
#define ESP_HOST_RST_N_2		99
#define ESP_HOST_CARD_WRITE_PRT_2	100
#define ESP_GPIO_SD0_OUT		100
#define ESP_HOST_CARD_INT_N_1		101
#define ESP_GPIO_SD1_OUT		101
#define ESP_HOST_CARD_INT_N_2		102
#define ESP_GPIO_SD2_OUT		102
#define ESP_PWM1_SYNC0_IN		103
#define ESP_GPIO_SD3_OUT		103
#define ESP_PWM1_SYNC1_IN		104
#define ESP_GPIO_SD4_OUT		104
#define ESP_PWM1_SYNC2_IN		105
#define ESP_GPIO_SD5_OUT		105
#define ESP_PWM1_F0_IN			106
#define ESP_GPIO_SD6_OUT		106
#define ESP_PWM1_F1_IN			107
#define ESP_GPIO_SD7_OUT		107
#define ESP_PWM1_F2_IN			108
#define ESP_PWM1_OUT0A			108
#define ESP_PWM0_CAP0_IN		109
#define ESP_PWM1_OUT0B			109
#define ESP_PWM0_CAP1_IN		110
#define ESP_PWM1_OUT1A			110
#define ESP_PWM0_CAP2_IN		111
#define ESP_PWM1_OUT1B			111
#define ESP_PWM1_CAP0_IN		112
#define ESP_PWM1_OUT2A			112
#define ESP_PWM1_CAP1_IN		113
#define ESP_PWM1_OUT2B			113
#define ESP_PWM1_CAP2_IN		114
#define ESP_PWM2_OUT1H			114
#define ESP_PWM2_FLTA			115
#define ESP_PWM2_OUT1L			115
#define ESP_PWM2_FLTB			116
#define ESP_PWM2_OUT2H			116
#define ESP_PWM2_CAP1_IN		117
#define ESP_PWM2_OUT2L			117
#define ESP_PWM2_CAP2_IN		118
#define ESP_PWM2_OUT3H			118
#define ESP_PWM2_CAP3_IN		119
#define ESP_PWM2_OUT3L			119
#define ESP_PWM3_FLTA			120
#define ESP_PWM2_OUT4H			120
#define ESP_PWM3_FLTB			121
#define ESP_PWM2_OUT4L			121
#define ESP_PWM3_CAP1_IN		122
#define ESP_PWM3_CAP2_IN		123
#define ESP_TWAI_TX			123
#define ESP_CAN_TX			ESP_TWAI_TX
#define ESP_PWM3_CAP3_IN		124
#define ESP_TWAI_BUS_OFF_ON		124
#define ESP_CAN_BUS_OFF_ON		ESP_TWAI_BUS_OFF_ON
#define ESP_TWAI_CLKOUT			125
#define ESP_CAN_CLKOUT			ESP_TWAI_CLKOUT
#define ESP_SPID4_IN			128
#define ESP_SPID4_OUT			128
#define ESP_SPID5_IN			129
#define ESP_SPID5_OUT			129
#define ESP_SPID6_IN			130
#define ESP_SPID6_OUT			130
#define ESP_SPID7_IN			131
#define ESP_SPID7_OUT			131
#define ESP_HSPID4_IN			132
#define ESP_HSPID4_OUT			132
#define ESP_HSPID5_IN			133
#define ESP_HSPID5_OUT			133
#define ESP_HSPID6_IN			134
#define ESP_HSPID6_OUT			134
#define ESP_HSPID7_IN			135
#define ESP_HSPID7_OUT			135
#define ESP_VSPID4_IN			136
#define ESP_VSPID4_OUT			136
#define ESP_VSPID5_IN			137
#define ESP_VSPID5_OUT			137
#define ESP_VSPID6_IN			138
#define ESP_VSPID6_OUT			138
#define ESP_VSPID7_IN			139
#define ESP_VSPID7_OUT			139
#define ESP_I2S0I_DATA_IN0		140
#define ESP_I2S0O_DATA_OUT0		140
#define ESP_I2S0I_DATA_IN1		141
#define ESP_I2S0O_DATA_OUT1		141
#define ESP_I2S0I_DATA_IN2		142
#define ESP_I2S0O_DATA_OUT2		142
#define ESP_I2S0I_DATA_IN3		143
#define ESP_I2S0O_DATA_OUT3		143
#define ESP_I2S0I_DATA_IN4		144
#define ESP_I2S0O_DATA_OUT4		144
#define ESP_I2S0I_DATA_IN5		145
#define ESP_I2S0O_DATA_OUT5		145
#define ESP_I2S0I_DATA_IN6		146
#define ESP_I2S0O_DATA_OUT6		146
#define ESP_I2S0I_DATA_IN7		147
#define ESP_I2S0O_DATA_OUT7		147
#define ESP_I2S0I_DATA_IN8		148
#define ESP_I2S0O_DATA_OUT8		148
#define ESP_I2S0I_DATA_IN9		149
#define ESP_I2S0O_DATA_OUT9		149
#define ESP_I2S0I_DATA_IN10		150
#define ESP_I2S0O_DATA_OUT10		150
#define ESP_I2S0I_DATA_IN11		151
#define ESP_I2S0O_DATA_OUT11		151
#define ESP_I2S0I_DATA_IN12		152
#define ESP_I2S0O_DATA_OUT12		152
#define ESP_I2S0I_DATA_IN13		153
#define ESP_I2S0O_DATA_OUT13		153
#define ESP_I2S0I_DATA_IN14		154
#define ESP_I2S0O_DATA_OUT14		154
#define ESP_I2S0I_DATA_IN15		155
#define ESP_I2S0O_DATA_OUT15		155
#define ESP_I2S0O_DATA_OUT16		156
#define ESP_I2S0O_DATA_OUT17		157
#define ESP_I2S0O_DATA_OUT18		158
#define ESP_I2S0O_DATA_OUT19		159
#define ESP_I2S0O_DATA_OUT20		160
#define ESP_I2S0O_DATA_OUT21		161
#define ESP_I2S0O_DATA_OUT22		162
#define ESP_I2S0O_DATA_OUT23		163
#define ESP_I2S1I_BCK_IN		164
#define ESP_I2S1I_BCK_OUT		164
#define ESP_I2S1I_WS_IN			165
#define ESP_I2S1I_WS_OUT		165
#define ESP_I2S1I_DATA_IN0		166
#define ESP_I2S1O_DATA_OUT0		166
#define ESP_I2S1I_DATA_IN1		167
#define ESP_I2S1O_DATA_OUT1		167
#define ESP_I2S1I_DATA_IN2		168
#define ESP_I2S1O_DATA_OUT2		168
#define ESP_I2S1I_DATA_IN3		169
#define ESP_I2S1O_DATA_OUT3		169
#define ESP_I2S1I_DATA_IN4		170
#define ESP_I2S1O_DATA_OUT4		170
#define ESP_I2S1I_DATA_IN5		171
#define ESP_I2S1O_DATA_OUT5		171
#define ESP_I2S1I_DATA_IN6		172
#define ESP_I2S1O_DATA_OUT6		172
#define ESP_I2S1I_DATA_IN7		173
#define ESP_I2S1O_DATA_OUT7		173
#define ESP_I2S1I_DATA_IN8		174
#define ESP_I2S1O_DATA_OUT8		174
#define ESP_I2S1I_DATA_IN9		175
#define ESP_I2S1O_DATA_OUT9		175
#define ESP_I2S1I_DATA_IN10		176
#define ESP_I2S1O_DATA_OUT10		176
#define ESP_I2S1I_DATA_IN11		177
#define ESP_I2S1O_DATA_OUT11		177
#define ESP_I2S1I_DATA_IN12		178
#define ESP_I2S1O_DATA_OUT12		178
#define ESP_I2S1I_DATA_IN13		179
#define ESP_I2S1O_DATA_OUT13		179
#define ESP_I2S1I_DATA_IN14		180
#define ESP_I2S1O_DATA_OUT14		180
#define ESP_I2S1I_DATA_IN15		181
#define ESP_I2S1O_DATA_OUT15		181
#define ESP_I2S1O_DATA_OUT16		182
#define ESP_I2S1O_DATA_OUT17		183
#define ESP_I2S1O_DATA_OUT18		184
#define ESP_I2S1O_DATA_OUT19		185
#define ESP_I2S1O_DATA_OUT20		186
#define ESP_I2S1O_DATA_OUT21		187
#define ESP_I2S1O_DATA_OUT22		188
#define ESP_I2S1O_DATA_OUT23		189
#define ESP_I2S0I_H_SYNC		190
#define ESP_PWM3_OUT1H			190
#define ESP_I2S0I_V_SYNC		191
#define ESP_PWM3_OUT1L			191
#define ESP_I2S0I_H_ENABLE		192
#define ESP_PWM3_OUT2H			192
#define ESP_I2S1I_H_SYNC		193
#define ESP_PWM3_OUT2L			193
#define ESP_I2S1I_V_SYNC		194
#define ESP_PWM3_OUT3H			194
#define ESP_I2S1I_H_ENABLE		195
#define ESP_PWM3_OUT3L			195
#define ESP_PWM3_OUT4H			196
#define ESP_PWM3_OUT4L			197
#define ESP_U2RXD_IN			198
#define ESP_U2TXD_OUT			198
#define ESP_U2CTS_IN			199
#define ESP_U2RTS_OUT			199
#define ESP_EMAC_MDC_I			200
#define ESP_EMAC_MDC_O			200
#define ESP_EMAC_MDI_I			201
#define ESP_EMAC_MDO_O			201
#define ESP_EMAC_CRS_I			202
#define ESP_EMAC_CRS_O			202
#define ESP_EMAC_COL_I			203
#define ESP_EMAC_COL_O			203
#define ESP_PCMFSYNC_IN			204
#define ESP_BT_AUDIO0_IRQ		204
#define ESP_PCMCLK_IN			205
#define ESP_BT_AUDIO1_IRQ		205
#define ESP_PCMDIN			206
#define ESP_BT_AUDIO2_IRQ		206
#define ESP_BLE_AUDIO0_IRQ		207
#define ESP_BLE_AUDIO1_IRQ		208
#define ESP_BLE_AUDIO2_IRQ		209
#define ESP_PCMFSYNC_OUT		210
#define ESP_PCMCLK_OUT			211
#define ESP_PCMDOUT			212
#define ESP_BLE_AUDIO_SYNC0_P		213
#define ESP_BLE_AUDIO_SYNC1_P		214
#define ESP_BLE_AUDIO_SYNC2_P		215
#define ESP_ANT_SEL0			216
#define ESP_ANT_SEL1			217
#define ESP_ANT_SEL2			218
#define ESP_ANT_SEL3			219
#define ESP_ANT_SEL4			220
#define ESP_ANT_SEL5			221
#define ESP_ANT_SEL6			222
#define ESP_ANT_SEL7			223
#define ESP_SIG_IN_FUNC224		224
#define ESP_SIG_IN_FUNC225		225
#define ESP_SIG_IN_FUNC226		226
#define ESP_SIG_IN_FUNC227		227
#define ESP_SIG_IN_FUNC228		228
#define ESP_SIG_GPIO_OUT		256

#endif /* ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_ESP32_GPIO_SIGMAP_H_ */
