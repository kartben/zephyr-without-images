/*
 * Copyright (c) 2020 Nuvoton Technology Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT nuvoton_npcx_i2c_ctrl

/**
 * @file
 * @brief Nuvoton NPCX smb/i2c module (controller) driver
 *
 * This file contains the driver of SMB module (controller) which provides full
 * support for a two-wire SMBus/I2C synchronous serial interface. The following
 * is the state diagrams for each Zephyr i2c api functions.
 *
 * case 1: i2c_write()/i2c_burst_write()
 *
 *                              All msg data sent?    Is there next msg?
 *                              +<----------------+<----------------------+
 *                              |       No        |                       | Yes
 *    +------+   +------------+ |  +------- ----+ |    +------- -------+  |
 * +->| IDLE |-->| WAIT_START |--->| WRITE_FIFO |-+--->| WRITE_SUSPEND |--+
 * |  +------+   +------------+    +------------+  Yes +---------------+  |
 * |      Issue START    START completed                                  | No
 * |                                            +-----------+             |
 * +--------------------------------------------| WAIT_STOP |<------------+
 *             STOP is completed                +-----------+  Issue STOP
 *
 *
 * case 2: i2c_read()
 *
 *                             All msg data received?  Is there next msg?
 *                              +<-----------------+<---------------------+
 *                              |       No         |                      | Yes
 *    +------+   +------------+ |  +------- ---+   |    +------- ------+  |
 * +->| IDLE |-->| WAIT_START |--->| READ_FIFO |---+--->| READ_SUSPEND |--+
 * |  +------+   +------------+    +------------+   Yes +--------------+  |
 * |     Issue START     START completed                                  | No
 * |                                          +-----------+               |
 * +------------------------------------------| WAIT_STOP |<--------------+
 *             STOP is completed              +-----------+  Issue STOP
 *
 *
 * case 3: i2c_write_read()/i2c_burst_read()
 *
 *                              All msg data sent?  Is there next write msg?
 *                              +<----------------+<----------------------+
 *                              |       No        |                       | Yes
 *    +------+   +------------+ |  +------- ----+ |    +------- -------+  |
 * +->| IDLE |-->| WAIT_START |--->| WRITE_FIFO |-+--->| WRITE_SUSPEND |--+
 * |  +------+   +------------+    +------------+  Yes +---------------+  |
 * |     Issue START     START completed                                  | No
 * |      +---------------------------------------------------------------+
 * |      |
 * |      |                 All msg data received?  Is there next read msg?
 * |      |                   +<-----------------+<-----------------------+
 * |      |                   |       No         |                        | Yes
 * |      |  +--------------+ |  +------- ---+   |    +------- ------+    |
 * |      +--| WAIT_RESTART |--->| READ_FIFO |---+--->| READ_SUSPEND |----+
 * |         +--------------+    +-----------+    Yes +--------------+    |
 * |  Issue RESTART      RESTART completed                                | No
 * |                                           +-----------+              |
 * +-------------------------------------------| WAIT_STOP |<-------------+
 *              STOP is completed              +-----------+  Issue STOP
 *
 */

#include <assert.h>
#include <drivers/clock_control.h>
#include <drivers/i2c.h>
#include <soc.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(i2c_npcx, LOG_LEVEL_ERR);

/* I2C controller mode */
#define NPCX_I2C_BANK_NORMAL 0
#define NPCX_I2C_BANK_FIFO   1

/* Timeout for device should be available after reset (SMBus spec. unit:ms) */
#define I2C_MAX_TIMEOUT 35

/* Timeout for SCL held to low by slave device . (SMBus spec. unit:ms). */
#define I2C_MIN_TIMEOUT 25

/* Default maximum time we allow for an I2C transfer (unit:ms) */
#define I2C_TRANS_TIMEOUT K_MSEC(100)

/*
 * NPCX I2C module that supports FIFO mode has 32 bytes Tx FIFO and
 * 32 bytes Rx FIFO.
 */
#define NPCX_I2C_FIFO_MAX_SIZE 32

/* Valid bit fields in SMBST register */
#define NPCX_VALID_SMBST_MASK ~(BIT(NPCX_SMBST_XMIT) | BIT(NPCX_SMBST_MASTER))

/* Supported I2C bus frequency */
enum npcx_i2c_freq {
	NPCX_I2C_BUS_SPEED_100KHZ,
	NPCX_I2C_BUS_SPEED_400KHZ,
	NPCX_I2C_BUS_SPEED_1MHZ,
};

/*
 * Internal SMBus Interface driver states values, which reflect events
 * which occurred on the bus
 */
enum npcx_i2c_oper_state {
	NPCX_I2C_IDLE,
	NPCX_I2C_WAIT_START,
	NPCX_I2C_WAIT_RESTART,
	NPCX_I2C_WRITE_FIFO,
	NPCX_I2C_WRITE_SUSPEND,
	NPCX_I2C_READ_FIFO,
	NPCX_I2C_READ_SUSPEND,
	NPCX_I2C_WAIT_STOP,
	NPCX_I2C_ERROR_RECOVERY,
};

/* I2C timing configuration for each i2c speed */
struct npcx_i2c_timing_cfg {
	uint8_t HLDT; /* i2c hold-time (Unit: clocks) */
	uint8_t k1; /* k1 = SCL low-time (Unit: clocks) */
	uint8_t k2; /* k2 = SCL high-time (Unit: clocks) */
};

/* Device config */
struct i2c_ctrl_config {
	uintptr_t base; /* i2c controller base address */
	struct npcx_clk_cfg clk_cfg; /* clock configuration */
	uint8_t irq; /* i2c controller irq */
};

/* Driver data */
struct i2c_ctrl_data {
	struct k_sem lock_sem; /* mutex of i2c controller */
	struct k_sem sync_sem; /* semaphore used for synchronization */
	uint32_t bus_freq; /* operation freq of i2c */
	enum npcx_i2c_oper_state oper_state; /* controller operation state */
	int trans_err;  /* error code during transaction */
	struct i2c_msg *msg; /* cache msg for transaction state machine */
	int is_write; /* direction of current msg */
	uint8_t *ptr_msg; /* current msg pointer for FIFO read/write */
	uint16_t addr; /* slave address of transcation */
	uint8_t port; /* current port used the controller */
};

/* Driver convenience defines */
#define DRV_CONFIG(dev) ((const struct i2c_ctrl_config *)(dev)->config)

#define DRV_DATA(dev) ((struct i2c_ctrl_data *)(dev)->data)

#define HAL_I2C_INSTANCE(dev) (struct smb_reg *)(DRV_CONFIG(dev)->base)

#define HAL_I2C_FIFO_INSTANCE(dev) \
	(struct smb_fifo_reg *)(DRV_CONFIG(dev)->base)

/* Recommended I2C timing values are based on 15 MHz */
static const struct npcx_i2c_timing_cfg npcx_speed_confs[] = {
	[NPCX_I2C_BUS_SPEED_100KHZ] = {.HLDT = 0, .k1 = 75, .k2 = 0},
	[NPCX_I2C_BUS_SPEED_400KHZ] = {.HLDT = 7, .k1 = 24, .k2 = 18,},
	[NPCX_I2C_BUS_SPEED_1MHZ] = {.HLDT  = 7, .k1 = 14, .k2 = 10,},
};

/* I2C controller inline functions access shared registers */
static inline void i2c_ctrl_start(const struct device *dev)
{
	struct smb_fifo_reg *const inst_fifo = HAL_I2C_FIFO_INSTANCE(dev);

	inst_fifo->SMBCTL1 |= BIT(NPCX_SMBCTL1_START);
}

static inline void i2c_ctrl_stop(const struct device *dev)
{
	struct smb_fifo_reg *const inst_fifo = HAL_I2C_FIFO_INSTANCE(dev);

	inst_fifo->SMBCTL1 |= BIT(NPCX_SMBCTL1_STOP);
}

static inline int i2c_ctrl_bus_busy(const struct device *dev)
{
	struct smb_fifo_reg *const inst_fifo = HAL_I2C_FIFO_INSTANCE(dev);

	return IS_BIT_SET(inst_fifo->SMBCST, NPCX_SMBCST_BB);
}

static inline void i2c_ctrl_bank_sel(const struct device *dev, int bank)
{
	struct smb_reg *const inst = HAL_I2C_INSTANCE(dev);

	if (bank) {
		inst->SMBCTL3 |= BIT(NPCX_SMBCTL3_BNK_SEL);
	} else {
		inst->SMBCTL3 &= ~BIT(NPCX_SMBCTL3_BNK_SEL);
	}
}

static inline void i2c_ctrl_irq_enable(const struct device *dev, int enable)
{
	const struct i2c_ctrl_config *const config = DRV_CONFIG(dev);

	if (enable) {
		irq_enable(config->irq);
	} else {
		irq_disable(config->irq);
	}
}

/* I2C controller inline functions access registers in 'Normal' bank */
static inline void i2c_ctrl_norm_stall_scl(const struct device *dev)
{
	struct smb_reg *const inst = HAL_I2C_INSTANCE(dev);

	/* Enable writing to SCL_LVL/SDA_LVL bit in SMBnCTL3 */
	inst->SMBCTL4 |= BIT(NPCX_SMBCTL4_LVL_WE);
	/* Force SCL bus to low and keep SDA floating */
	inst->SMBCTL3 = (inst->SMBCTL3 & ~BIT(NPCX_SMBCTL3_SCL_LVL))
						| BIT(NPCX_SMBCTL3_SDA_LVL);
	/* Disable writing to them */
	inst->SMBCTL4 &= ~BIT(NPCX_SMBCTL4_LVL_WE);
}

static inline void i2c_ctrl_norm_free_scl(const struct device *dev)
{
	struct smb_reg *const inst = HAL_I2C_INSTANCE(dev);

	/* Enable writing to SCL_LVL/SDA_LVL bit in SMBnCTL3 */
	inst->SMBCTL4 |= BIT(NPCX_SMBCTL4_LVL_WE);
	/*
	 * Release SCL bus. Then it might be still driven by module itself or
	 * slave device.
	 */
	inst->SMBCTL3 |= BIT(NPCX_SMBCTL3_SCL_LVL) | BIT(NPCX_SMBCTL3_SDA_LVL);
	/* Disable writing to them */
	inst->SMBCTL4 &= ~BIT(NPCX_SMBCTL4_LVL_WE);
}

/* I2C controller inline functions access registers in 'FIFO' bank */
static inline void i2c_ctrl_fifo_write(const struct device *dev, uint8_t data)
{
	struct smb_fifo_reg *const inst_fifo = HAL_I2C_FIFO_INSTANCE(dev);

	inst_fifo->SMBSDA = data;
}

static inline uint8_t i2c_ctrl_fifo_read(const struct device *dev)
{
	struct smb_fifo_reg *const inst_fifo = HAL_I2C_FIFO_INSTANCE(dev);

	return inst_fifo->SMBSDA;
}

static inline int i2c_ctrl_fifo_tx_avail(const struct device *dev)
{
	struct smb_fifo_reg *const inst_fifo = HAL_I2C_FIFO_INSTANCE(dev);

	return NPCX_I2C_FIFO_MAX_SIZE - (inst_fifo->SMBTXF_STS & 0x3f);
}

static inline int i2c_ctrl_fifo_rx_occupied(const struct device *dev)
{
	struct smb_fifo_reg *const inst_fifo = HAL_I2C_FIFO_INSTANCE(dev);

	return inst_fifo->SMBRXF_STS & 0x3f;
}

static inline void i2c_ctrl_fifo_rx_setup_threshold_nack(
		const struct device *dev, int threshold, int last)
{
	struct smb_fifo_reg *const inst_fifo = HAL_I2C_FIFO_INSTANCE(dev);
	uint8_t value = MIN(threshold, NPCX_I2C_FIFO_MAX_SIZE);

	SET_FIELD(inst_fifo->SMBRXF_CTL, NPCX_SMBRXF_CTL_RX_THR, value);

	/*
	 * Is it last received transaction? If so, set LAST bit. Then the
	 * hardware will generate NACK automatically when receiving last byte.
	 */
	if (last && (value == threshold)) {
		inst_fifo->SMBRXF_CTL |= BIT(NPCX_SMBRXF_CTL_LAST);
	}
}

static inline void i2c_ctrl_fifo_clear_status(const struct device *dev)
{
	struct smb_fifo_reg *const inst_fifo = HAL_I2C_FIFO_INSTANCE(dev);

	inst_fifo->SMBFIF_CTS |= BIT(NPCX_SMBFIF_CTS_CLR_FIFO);
}

/*
 * I2C local functions which touch the registers in 'Normal' bank. These
 * utilities will change bank back to FIFO mode when leaving themselves in case
 * the other utilities acces the registers in 'FIFO' bank.
 */
static void i2c_ctrl_hold_bus(const struct device *dev, int stall)
{
	i2c_ctrl_bank_sel(dev, NPCX_I2C_BANK_NORMAL);

	if (stall) {
		i2c_ctrl_norm_stall_scl(dev);
	} else {
		i2c_ctrl_norm_free_scl(dev);
	}

	i2c_ctrl_bank_sel(dev, NPCX_I2C_BANK_FIFO);
}

static void i2c_ctrl_init_module(const struct device *dev)
{
	struct smb_reg *const inst = HAL_I2C_INSTANCE(dev);

	i2c_ctrl_bank_sel(dev, NPCX_I2C_BANK_NORMAL);

	/* Enable FIFO mode first */
	inst->SMBFIF_CTL |= BIT(NPCX_SMBFIF_CTL_FIFO_EN);

	/* Enable module - before configuring CTL1 */
	inst->SMBCTL2  |= BIT(NPCX_SMBCTL2_ENABLE);

	/* Enable SMB interrupt and 'New Address Match' interrupt source */
	inst->SMBCTL1 |= BIT(NPCX_SMBCTL1_NMINTE) | BIT(NPCX_SMBCTL1_INTEN);

	i2c_ctrl_bank_sel(dev, NPCX_I2C_BANK_FIFO);
}

static void i2c_ctrl_config_bus_freq(const struct device *dev,
						enum npcx_i2c_freq bus_freq)
{
	struct smb_reg *const inst = HAL_I2C_INSTANCE(dev);
	const struct npcx_i2c_timing_cfg bus_cfg = npcx_speed_confs[bus_freq];

	/* Switch to bank 0 to configure bus speed */
	i2c_ctrl_bank_sel(dev, NPCX_I2C_BANK_NORMAL);

	/* Configure bus speed */
	if (bus_freq == NPCX_I2C_BUS_SPEED_100KHZ) {
		/* Enable 'Normal' Mode */
		inst->SMBCTL3 &= ~(BIT(NPCX_SMBCTL3_400K));
		/* Set freq of SCL */
		SET_FIELD(inst->SMBCTL2, NPCX_SMBCTL2_SCLFRQ0_6_FIELD,
				bus_cfg.k1/2 & 0x7f);
		SET_FIELD(inst->SMBCTL3, NPCX_SMBCTL3_SCLFRQ7_8_FIELD,
				bus_cfg.k2/2 >> 7);
	} else {
		/* Enable 'Fast' Mode for 400K or higher freq. */
		inst->SMBCTL3 |= BIT(NPCX_SMBCTL3_400K);
		/* Set high/low time of SCL and hold-time */
		inst->SMBSCLLT = bus_cfg.k1/2;
		inst->SMBSCLHT = bus_cfg.k2/2;
		SET_FIELD(inst->SMBCTL4, NPCX_SMBCTL4_HLDT_FIELD,
				bus_cfg.HLDT);
	}

	/* Switch to bank 1 to access I2C FIFO registers */
	i2c_ctrl_bank_sel(dev, NPCX_I2C_BANK_FIFO);
}

/* I2C controller local functions */
static int i2c_ctrl_wait_stop_completed(const struct device *dev, int timeout)
{
	struct smb_fifo_reg *const inst_fifo = HAL_I2C_FIFO_INSTANCE(dev);

	if (timeout <= 0) {
		return -EINVAL;
	}

	do {
		/*
		 * Wait till i2c bus is idle. This bit is cleared to 0
		 * automatically after the STOP condition is generated.
		 */
		if (!IS_BIT_SET(inst_fifo->SMBCTL1, NPCX_SMBCTL1_STOP))
			break;
		k_msleep(1);
	} while (--timeout);

	if (timeout > 0) {
		return 0;
	} else {
		return -ETIMEDOUT;
	}
}

static int i2c_ctrl_wait_idle_completed(const struct device *dev, int timeout)
{
	struct smb_fifo_reg *const inst_fifo = HAL_I2C_FIFO_INSTANCE(dev);

	if (timeout <= 0) {
		return -EINVAL;
	}

	do {
		/* Wait for both SCL & SDA lines are high */
		if (IS_BIT_SET(inst_fifo->SMBCTL3, NPCX_SMBCTL3_SCL_LVL)
		  && IS_BIT_SET(inst_fifo->SMBCTL3, NPCX_SMBCTL3_SDA_LVL)) {
			break;
		}
		k_msleep(1);
	} while (--timeout);

	if (timeout > 0) {
		return 0;
	} else {
		return -ETIMEDOUT;
	}
}

static int i2c_ctrl_recovery(const struct device *dev)
{
	struct smb_fifo_reg *const inst_fifo = HAL_I2C_FIFO_INSTANCE(dev);
	struct i2c_ctrl_data *const data = DRV_DATA(dev);
	int ret;

	if (data->oper_state != NPCX_I2C_ERROR_RECOVERY) {
		data->oper_state = NPCX_I2C_ERROR_RECOVERY;
	}

	/* Step 1: Make sure the bus is not stalled before exit. */
	i2c_ctrl_hold_bus(dev, 0);

	/*
	 * Step 2: Abort data, wait for STOP condition completed.
	 * - Clearing NEGACK and BER bits first
	 * - Wait for STOP condition completed
	 * - Then clear BB (BUS BUSY) bit
	 */
	inst_fifo->SMBST = BIT(NPCX_SMBST_BER) | BIT(NPCX_SMBST_NEGACK);
	ret = i2c_ctrl_wait_stop_completed(dev, I2C_MAX_TIMEOUT);
	inst_fifo->SMBCST |= BIT(NPCX_SMBCST_BB);
	if (ret != 0) {
		LOG_ERR("Abort i2c port%02x fail! Bus might be stalled.",
								data->port);
	}

	/*
	 * Step 3: Reset i2c module to clear all internal state machine of it
	 * - Disable the SMB module first
	 * - Wait both SCL/SDA line are high
	 * - Enable i2c module again
	 */
	inst_fifo->SMBCTL2 &= ~BIT(NPCX_SMBCTL2_ENABLE);
	ret = i2c_ctrl_wait_idle_completed(dev, I2C_MAX_TIMEOUT);
	if (ret != 0) {
		LOG_ERR("Reset i2c port%02x fail! Bus might be stalled.",
								data->port);
		return -EIO;
	}

	/* Reset module and internal state machine */
	i2c_ctrl_init_module(dev);

	/* Recovery is completed */
	data->oper_state = NPCX_I2C_IDLE;
	return 0;
}

static void i2c_ctrl_notify(const struct device *dev, int error)
{
	struct i2c_ctrl_data *const data = DRV_DATA(dev);

	data->trans_err = error;
	k_sem_give(&data->sync_sem);
}

static int i2c_ctrl_wait_completion(const struct device *dev)
{
	struct i2c_ctrl_data *const data = DRV_DATA(dev);

	if (k_sem_take(&data->sync_sem, I2C_TRANS_TIMEOUT) == 0) {
		return data->trans_err;
	} else {
		return -ETIMEDOUT;
	}
}

size_t i2c_ctrl_calculate_msg_remains(const struct device *dev)
{
	struct i2c_ctrl_data *const data = DRV_DATA(dev);
	uint8_t *buf_end = data->msg->buf + data->msg->len;

	return (buf_end > data->ptr_msg) ? (buf_end - data->ptr_msg) : 0;
}

static void i2c_ctrl_handle_write_int_event(const struct device *dev)
{
	struct i2c_ctrl_data *const data = DRV_DATA(dev);

	/* START condition is issued */
	if (data->oper_state == NPCX_I2C_WAIT_START) {
		/* Write slave address with W bit */
		i2c_ctrl_fifo_write(dev, ((data->addr << 1)  & ~BIT(0)));
		/* Start to proceed write process */
		data->oper_state = NPCX_I2C_WRITE_FIFO;
		return;
	}

	/* Write message data bytes to FIFO */
	if (data->oper_state == NPCX_I2C_WRITE_FIFO) {
		/* Calculate how many remaining bytes need to transmit */
		size_t tx_remain = i2c_ctrl_calculate_msg_remains(dev);
		size_t tx_avail = MIN(tx_remain, i2c_ctrl_fifo_tx_avail(dev));

		LOG_DBG("tx remains %d, avail %d", tx_remain, tx_avail);
		for (int i = 0U; i < tx_avail; i++)
			i2c_ctrl_fifo_write(dev, *(data->ptr_msg++));

		/* Is there any remaining bytes? */
		if (data->ptr_msg == data->msg->buf + data->msg->len) {
			data->oper_state = NPCX_I2C_WRITE_SUSPEND;
		}
		return;
	}

	/* Issue STOP after sending message? */
	if (data->oper_state == NPCX_I2C_WRITE_SUSPEND) {
		if (data->msg->flags & I2C_MSG_STOP) {
			/* Generate a STOP condition immediately */
			i2c_ctrl_stop(dev);
			/* Clear rx FIFO threshold and status bits */
			i2c_ctrl_fifo_clear_status(dev);
			/* Wait for STOP completed */
			data->oper_state = NPCX_I2C_WAIT_STOP;
		} else {
			/* Disable interrupt and handle next message */
			i2c_ctrl_irq_enable(dev, 0);
		}
	}

	return i2c_ctrl_notify(dev, 0);
}

static void i2c_ctrl_handle_read_int_event(const struct device *dev)
{
	struct i2c_ctrl_data *const data = DRV_DATA(dev);

	/* START or RESTART condition is issued */
	if (data->oper_state == NPCX_I2C_WAIT_START ||
			data->oper_state == NPCX_I2C_WAIT_RESTART) {
		/* Setup threshold of rx FIFO before sending address byte */
		i2c_ctrl_fifo_rx_setup_threshold_nack(dev, data->msg->len,
					(data->msg->flags & I2C_MSG_STOP) != 0);
		/* Write slave address with R bit */
		i2c_ctrl_fifo_write(dev, ((data->addr << 1) | BIT(0)));
		/* Start to proceed read process */
		data->oper_state = NPCX_I2C_READ_FIFO;
		return;
	}

	/* Read message data bytes from FIFO */
	if (data->oper_state == NPCX_I2C_READ_FIFO) {
		/* Calculate how many remaining bytes need to receive */
		size_t rx_remain = i2c_ctrl_calculate_msg_remains(dev);
		size_t rx_occupied = i2c_ctrl_fifo_rx_occupied(dev);

		LOG_DBG("rx remains %d, occupied %d", rx_remain, rx_occupied);
		/*
		 * Hold SCL line before reading data bytes from FIFO. Or the
		 * hardware will release bus immediately before the driver
		 * handles incoming data.
		 */
		i2c_ctrl_hold_bus(dev, 1);
		/* Read data bytes from FIFO */
		for (int i = 0; i < rx_occupied; i++) {
			*(data->ptr_msg++) = i2c_ctrl_fifo_read(dev);
		}
		rx_remain = i2c_ctrl_calculate_msg_remains(dev);

		/* Setup threshold of RX FIFO next time */
		if (rx_remain > 0) {
			i2c_ctrl_fifo_rx_setup_threshold_nack(dev, rx_remain,
					(data->msg->flags & I2C_MSG_STOP) != 0);
			/* Release bus */
			i2c_ctrl_hold_bus(dev, 0);
			return;
		}
	}

	/* Issue STOP after receiving message? */
	if ((data->msg->flags & I2C_MSG_STOP) != 0) {
		/* Release bus */
		i2c_ctrl_hold_bus(dev, 0);

		/* Generate a STOP condition immediately */
		i2c_ctrl_stop(dev);

		/* Clear rx FIFO threshold and status bits */
		i2c_ctrl_fifo_clear_status(dev);

		/* Wait for STOP completed */
		data->oper_state = NPCX_I2C_WAIT_STOP;
	} else {
		/* Disable i2c interrupt first */
		i2c_ctrl_irq_enable(dev, 0);
		data->oper_state = NPCX_I2C_READ_SUSPEND;
	}

	return i2c_ctrl_notify(dev, 0);
}

static int i2c_ctrl_proc_write_msg(const struct device *dev,
							struct i2c_msg *msg)
{
	struct i2c_ctrl_data *const data = DRV_DATA(dev);

	data->is_write = 1;
	data->ptr_msg = msg->buf;
	data->msg = msg;

	if (data->oper_state == NPCX_I2C_IDLE) {
		data->oper_state = NPCX_I2C_WAIT_START;
		/* Issue a START, wait for transaction completed */
		i2c_ctrl_start(dev);

		return i2c_ctrl_wait_completion(dev);
	} else if (data->oper_state == NPCX_I2C_WRITE_SUSPEND) {
		data->oper_state = NPCX_I2C_WRITE_FIFO;
		i2c_ctrl_irq_enable(dev, 1);

		return i2c_ctrl_wait_completion(dev);
	}

	LOG_ERR("Unexpected state %d during writing i2c port%02x!",
					data->oper_state, data->port);
	data->trans_err = -EIO;
	return data->trans_err;
}

static int i2c_ctrl_proc_read_msg(const struct device *dev, struct i2c_msg *msg)
{
	struct i2c_ctrl_data *const data = DRV_DATA(dev);

	data->is_write = 0;
	data->ptr_msg = msg->buf;
	data->msg = msg;

	if (data->oper_state == NPCX_I2C_IDLE) {
		data->oper_state = NPCX_I2C_WAIT_START;
		/* Issue a START, wait for transaction completed */
		i2c_ctrl_start(dev);

		return i2c_ctrl_wait_completion(dev);
	} else if (data->oper_state == NPCX_I2C_WRITE_SUSPEND) {
		data->oper_state = NPCX_I2C_WAIT_RESTART;
		/* Issue a RESTART, wait for transaction completed */
		i2c_ctrl_start(dev);
		i2c_ctrl_irq_enable(dev, 1);

		return i2c_ctrl_wait_completion(dev);
	} else if (data->oper_state == NPCX_I2C_READ_SUSPEND) {
		data->oper_state = NPCX_I2C_READ_FIFO;

		/* Setup threshold of RX FIFO first */
		i2c_ctrl_fifo_rx_setup_threshold_nack(dev, msg->len,
				(msg->flags & I2C_MSG_STOP) != 0);

		/* Release bus */
		i2c_ctrl_hold_bus(dev, 0);

		/* Enable i2c interrupt first */
		i2c_ctrl_irq_enable(dev, 1);
		return i2c_ctrl_wait_completion(dev);
	}

	LOG_ERR("Unexpected state  %d during reading i2c port%02x!",
					data->oper_state, data->port);
	data->trans_err = -EIO;
	return data->trans_err;
}

/* I2C controller isr function */
static void i2c_ctrl_isr(const struct device *dev)
{
	struct smb_fifo_reg *const inst_fifo = HAL_I2C_FIFO_INSTANCE(dev);
	struct i2c_ctrl_data *const data = DRV_DATA(dev);
	uint8_t status, tmp;

	status = inst_fifo->SMBST & NPCX_VALID_SMBST_MASK;
	LOG_DBG("status: %02x, %d", status, data->oper_state);

	/* A 'Bus Error' has been identified */
	if (IS_BIT_SET(status, NPCX_SMBST_BER)) {
		/* Generate a STOP condition immediately */
		i2c_ctrl_stop(dev);

		/* Clear BER Bit */
		inst_fifo->SMBST = BIT(NPCX_SMBST_BER);

		/* Make sure slave doesn't hold bus by reading FIFO again */
		tmp = i2c_ctrl_fifo_read(dev);

		LOG_ERR("Bus error occurred on i2c port%02x!", data->port);
		data->oper_state = NPCX_I2C_ERROR_RECOVERY;

		/* I/O error occurred */
		i2c_ctrl_notify(dev, -EIO);
		return;
	}

	/* A negative acknowledge has occurred */
	if (IS_BIT_SET(status, NPCX_SMBST_NEGACK)) {
		/* Generate a STOP condition immediately */
		i2c_ctrl_stop(dev);

		/* Clear NEGACK Bit */
		inst_fifo->SMBST = BIT(NPCX_SMBST_NEGACK);

		/* End transaction */
		data->oper_state = NPCX_I2C_WAIT_STOP;

		/* No such device or address */
		return i2c_ctrl_notify(dev, -ENXIO);
	}

	/* START, tx FIFO empty or rx FIFO full has occurred */
	if (IS_BIT_SET(status, NPCX_SMBST_SDAST)) {
		if (data->is_write) {
			return i2c_ctrl_handle_write_int_event(dev);
		} else {
			return i2c_ctrl_handle_read_int_event(dev);
		}
	}

	/* Clear unexpected status bits */
	inst_fifo->SMBST = status;
	LOG_ERR("Unexpected  SMBST 0x%02x occurred on i2c port%02x!", status,
								data->port);
}

/* NPCX specific I2C controller functions */
void npcx_i2c_ctrl_mutex_lock(const struct device *i2c_dev)
{
	struct i2c_ctrl_data *const data = DRV_DATA(i2c_dev);

	k_sem_take(&data->lock_sem, K_FOREVER);
}

void npcx_i2c_ctrl_mutex_unlock(const struct device *i2c_dev)
{
	struct i2c_ctrl_data *const data = DRV_DATA(i2c_dev);

	k_sem_give(&data->lock_sem);
}

int npcx_i2c_ctrl_configure(const struct device *i2c_dev, uint32_t dev_config)
{
	struct i2c_ctrl_data *const data = DRV_DATA(i2c_dev);

	switch (I2C_SPEED_GET(dev_config)) {
	case I2C_SPEED_STANDARD:
		data->bus_freq = NPCX_I2C_BUS_SPEED_100KHZ;
		break;
	case I2C_SPEED_FAST:
		data->bus_freq = NPCX_I2C_BUS_SPEED_400KHZ;
		break;
	case I2C_SPEED_FAST_PLUS:
		data->bus_freq = NPCX_I2C_BUS_SPEED_1MHZ;
		break;
	default:
		return -ERANGE;
	}

	i2c_ctrl_config_bus_freq(i2c_dev, data->bus_freq);
	return 0;
}

int npcx_i2c_ctrl_transfer(const struct device *i2c_dev, struct i2c_msg *msgs,
			      uint8_t num_msgs, uint16_t addr, int port)
{
	struct i2c_ctrl_data *const data = DRV_DATA(i2c_dev);
	int ret = 0;
	uint8_t i;

	/* Does bus need recovery? */
	if (data->oper_state != NPCX_I2C_WRITE_SUSPEND &&
			data->oper_state != NPCX_I2C_READ_SUSPEND) {
		if (i2c_ctrl_bus_busy(i2c_dev) ||
		    data->oper_state == NPCX_I2C_ERROR_RECOVERY) {
			ret = i2c_ctrl_recovery(i2c_dev);
			if (ret) {
				return ret;
			}
		}
	}

	/* Start i2c transaction */
	data->port = port;
	data->trans_err = 0;
	data->addr = addr;

	/*
	 * Reset i2c event-completed semaphore before starting transactions.
	 * Some interrupt events such as BUS_ERROR might change its counter
	 * when bus is idle.
	 */
	k_sem_reset(&data->sync_sem);

	for (i = 0U; i < num_msgs; i++) {
		struct i2c_msg *msg = msgs + i;

		/* Handle write transaction */
		if ((msg->flags & I2C_MSG_RW_MASK) == I2C_MSG_WRITE) {
			ret = i2c_ctrl_proc_write_msg(i2c_dev, msg);
		} else {/* Handle read transaction */
			ret = i2c_ctrl_proc_read_msg(i2c_dev, msg);
		}
		if (ret < 0) {
			break;
		}
	}

	/* Check STOP completed? */
	if (data->oper_state == NPCX_I2C_WAIT_STOP) {
		data->trans_err = i2c_ctrl_wait_stop_completed(i2c_dev,
							I2C_MIN_TIMEOUT);
		if (data->trans_err == 0) {
			data->oper_state = NPCX_I2C_IDLE;
		} else {
			LOG_ERR("STOP fail! bus is held on i2c port%02x!",
								data->port);
			data->oper_state = NPCX_I2C_ERROR_RECOVERY;
		}
	}

	if (data->oper_state == NPCX_I2C_ERROR_RECOVERY) {
		ret = i2c_ctrl_recovery(i2c_dev);
	}

	return ret;
}

/* I2C controller driver registration */
static int i2c_ctrl_init(const struct device *dev)
{
	const struct i2c_ctrl_config *const config = DRV_CONFIG(dev);
	struct i2c_ctrl_data *const data = DRV_DATA(dev);
	const struct device *const clk_dev =
					device_get_binding(NPCX_CLK_CTRL_NAME);
	uint32_t i2c_rate;

	/* Turn on device clock first and get source clock freq. */
	if (clock_control_on(clk_dev,
		(clock_control_subsys_t *) &config->clk_cfg) != 0) {
		LOG_ERR("Turn on %s clock fail.", dev->name);
		return -EIO;
	}

	/*
	 * If apb2/3's clock is not 15MHz, we need to add the other timing
	 * configuration of the device to meet SMBus timing spec. Please refer
	 * Table 21/22/23 and section 7.5.9 SMBus Timing for more detail.
	 */
	if (clock_control_get_rate(clk_dev, (clock_control_subsys_t *)
			&config->clk_cfg, &i2c_rate) != 0) {
		LOG_ERR("Get %s clock rate error.", dev->name);
		return -EIO;
	}
	__ASSERT(i2c_rate == 15000000, "Unsupported apb2/3 freq for I2C!");

	/* Initialize i2c module */
	i2c_ctrl_init_module(dev);

	/* initialize mutux and semaphore for i2c/smb controller */
	k_sem_init(&data->lock_sem, 1, 1);
	k_sem_init(&data->sync_sem, 0, UINT_MAX);

	/* Initialize driver status machine */
	data->oper_state = NPCX_I2C_IDLE;

	return 0;
}

/* I2C controller init macro functions */
#define NPCX_I2C_CTRL_INIT_FUNC(inst) _CONCAT(i2c_ctrl_init_, inst)
#define NPCX_I2C_CTRL_INIT_FUNC_DECL(inst) \
	static int i2c_ctrl_init_##inst(const struct device *dev)
#define NPCX_I2C_CTRL_INIT_FUNC_IMPL(inst)                                     \
	static int i2c_ctrl_init_##inst(const struct device *dev)              \
	{	                                                               \
		int ret;                                                       \
									       \
		ret = i2c_ctrl_init(dev);                                      \
		IRQ_CONNECT(DT_INST_IRQN(inst),		                       \
			DT_INST_IRQ(inst, priority),                           \
			i2c_ctrl_isr,                                          \
			DEVICE_DT_INST_GET(inst),                              \
			0);                                                    \
		irq_enable(DT_INST_IRQN(inst));                                \
									       \
		return ret;                                                    \
	}


#define NPCX_I2C_CTRL_INIT(inst)                                               \
	NPCX_I2C_CTRL_INIT_FUNC_DECL(inst);                                    \
									       \
	static const struct i2c_ctrl_config i2c_ctrl_cfg_##inst = {            \
		.base = DT_INST_REG_ADDR(inst),                                \
		.irq = DT_INST_IRQN(inst),                                     \
		.clk_cfg = NPCX_DT_CLK_CFG_ITEM(inst),                         \
	};                                                                     \
									       \
	static struct i2c_ctrl_data i2c_ctrl_data_##inst;                      \
									       \
	DEVICE_DT_INST_DEFINE(inst,                                            \
			    NPCX_I2C_CTRL_INIT_FUNC(inst),                     \
			    device_pm_control_nop,                             \
			    &i2c_ctrl_data_##inst, &i2c_ctrl_cfg_##inst,       \
			    PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,  \
			    NULL);                                             \
									       \
	NPCX_I2C_CTRL_INIT_FUNC_IMPL(inst)

DT_INST_FOREACH_STATUS_OKAY(NPCX_I2C_CTRL_INIT)
