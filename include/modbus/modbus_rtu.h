/*
 * Copyright (c) 2020 PHYTEC Messtechnik GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * Client API in this file is based on mbm_core.c from uC/Modbus Stack.
 *
 *                                uC/Modbus
 *                         The Embedded Modbus Stack
 *
 *      Copyright 2003-2020 Silicon Laboratories Inc. www.silabs.com
 *
 *                   SPDX-License-Identifier: APACHE-2.0
 *
 * This software is subject to an open source license and is distributed by
 *  Silicon Laboratories Inc. pursuant to the terms of the Apache License,
 *      Version 2.0 available at www.apache.org/licenses/LICENSE-2.0.
 */

/**
 * @brief MODBUS RTU transport protocol over Serial Line
 * @defgroup modbus MODBUS
 * @ingroup io_interfaces
 * @{
 */

#ifndef ZEPHYR_INCLUDE_MODBUS_RTU_H_
#define ZEPHYR_INCLUDE_MODBUS_RTU_H_

#include <drivers/uart.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Coil read (FC01)
 *
 * Sends a Modbus message to read the status of coils from a server.
 *
 * @param iface      Modbus RTU interface index
 * @param node_addr  Modbus RTU address of the server
 * @param start_addr Coil starting address
 * @param coil_tbl   Pointer to an array of bytes containing the value
 *                   of the coils read.
 *                   The format is:
 *
 *                                       MSB                               LSB
 *                                       B7   B6   B5   B4   B3   B2   B1   B0
 *                                       -------------------------------------
 *                       coil_tbl[0]     #8   #7                            #1
 *                       coil_tbl[1]     #16  #15                           #9
 *                            :
 *                            :
 *
 *                   Note that the array that will be receiving the coil
 *                   values must be greater than or equal to:
 *                   (num_coils - 1) / 8 + 1
 * @param num_coils  Quantity of coils to read
 *
 * @retval           0 If the function was successful
 */
int mb_rtu_read_coils(const int iface,
		      const uint8_t node_addr,
		      const uint16_t start_addr,
		      uint8_t *const coil_tbl,
		      const uint16_t num_coils);

/**
 * @brief Read discrete inputs (FC02)
 *
 * Sends a Modbus message to read the status of discrete inputs from
 * a server.
 *
 * @param iface      Modbus RTU interface index
 * @param node_addr  Modbus RTU address of the server
 * @param start_addr Discrete input starting address
 * @param di_tbl     Pointer to an array that will receive the state
 *                   of the discrete inputs.
 *                   The format of the array is as follows:
 *
 *                                     MSB                               LSB
 *                                     B7   B6   B5   B4   B3   B2   B1   B0
 *                                     -------------------------------------
 *                       di_tbl[0]     #8   #7                            #1
 *                       di_tbl[1]     #16  #15                           #9
 *                            :
 *                            :
 *
 *                   Note that the array that will be receiving the discrete
 *                   input values must be greater than or equal to:
 *                        (num_di - 1) / 8 + 1
 * @param num_di     Quantity of discrete inputs to read
 *
 * @retval           0 If the function was successful
 */
int mb_rtu_read_dinputs(const int iface,
			const uint8_t node_addr,
			const uint16_t start_addr,
			uint8_t *const di_tbl,
			const uint16_t num_di);

/**
 * @brief Read holding registers (FC03)
 *
 * Sends a Modbus message to read the value of holding registers
 * from a server.
 *
 * @param iface      Modbus RTU interface index
 * @param node_addr  Modbus RTU address of the server
 * @param start_addr Register starting address
 * @param reg_buf    Is a pointer to an array that will receive
 *                   the current values of the holding registers from
 *                   the server.  The array pointed to by 'reg_buf' needs
 *                   to be able to hold at least 'num_regs' entries.
 * @param num_regs   Quantity of registers to read
 *
 * @retval           0 If the function was successful
 */
int mb_rtu_read_holding_regs(const int iface,
			     const uint8_t node_addr,
			     const uint16_t start_addr,
			     uint16_t *const reg_buf,
			     const uint16_t num_regs);

/**
 * @brief Read input registers (FC04)
 *
 * Sends a Modbus message to read the value of input registers from
 * a server.
 *
 * @param iface      Modbus RTU interface index
 * @param node_addr  Modbus RTU address of the server
 * @param start_addr Register starting address
 * @param reg_buf    Is a pointer to an array that will receive
 *                   the current value of the holding registers
 *                   from the server.  The array pointed to by 'reg_buf'
 *                   needs to be able to hold at least 'num_regs' entries.
 * @param num_regs   Quantity of registers to read
 *
 * @retval           0 If the function was successful
 */
int mb_rtu_read_input_regs(const int iface,
			   const uint8_t node_addr,
			   const uint16_t start_addr,
			   uint16_t *const reg_buf,
			   const uint16_t num_regs);

/**
 * @brief Write single coil (FC05)
 *
 * Sends a Modbus message to write the value of single coil to a server.
 *
 * @param iface      Modbus RTU interface index
 * @param node_addr  Modbus RTU address of the server
 * @param coil_addr  Coils starting address
 * @param coil_state Is the desired state of the coil
 *
 * @retval           0 If the function was successful
 */
int mb_rtu_write_coil(const int iface,
		      const uint8_t node_addr,
		      const uint16_t coil_addr,
		      const bool coil_state);

/**
 * @brief Write single holding register (FC06)
 *
 * Sends a Modbus message to write the value of single holding register
 * to a server unit.
 *
 * @param iface      Modbus RTU interface index
 * @param node_addr  Modbus RTU address of the server
 * @param start_addr Coils starting address
 * @param reg_val    Desired value of the holding register
 *
 * @retval           0 If the function was successful
 */
int mb_rtu_write_holding_reg(const int iface,
			     const uint8_t node_addr,
			     const uint16_t start_addr,
			     const uint16_t reg_val);

/**
 * @brief Read diagnostic (FC08)
 *
 * Sends a Modbus message to perform a diagnostic function of a server unit.
 *
 * @param iface      Modbus RTU interface index
 * @param node_addr  Modbus RTU address of the server
 * @param sfunc      Diagnostic sub-function code
 * @param data       Sub-function data
 * @param data_out   Pointer to the data value
 *
 * @retval           0 If the function was successful
 */
int mb_rtu_request_diagnostic(const int iface,
			      const uint8_t node_addr,
			      const uint16_t sfunc,
			      const uint16_t data,
			      uint16_t *const data_out);

/**
 * @brief Write coils (FC15)
 *
 * Sends a Modbus message to write to coils on a server unit.
 *
 * @param iface      Modbus RTU interface index
 * @param node_addr  Modbus RTU address of the server
 * @param start_addr Coils starting address
 * @param coil_tbl   Pointer to an array of bytes containing the value
 *                   of the coils to write.
 *                   The format is:
 *
 *                                       MSB                               LSB
 *                                       B7   B6   B5   B4   B3   B2   B1   B0
 *                                       -------------------------------------
 *                       coil_tbl[0]     #8   #7                            #1
 *                       coil_tbl[1]     #16  #15                           #9
 *                            :
 *                            :
 *
 *                   Note that the array that will be receiving the coil
 *                   values must be greater than or equal to:
 *                   (num_coils - 1) / 8 + 1
 * @param num_coils  Quantity of coils to write
 *
 * @retval           0 If the function was successful
 */
int mb_rtu_write_coils(const int iface,
		       const uint8_t node_addr,
		       const uint16_t start_addr,
		       uint8_t *const coil_tbl,
		       const uint16_t num_coils);

/**
 * @brief Write holding registers (FC16)
 *
 * Sends a Modbus message to write to integer holding registers
 * to a server unit.
 *
 * @param iface      Modbus RTU interface index
 * @param node_addr  Modbus RTU address of the server
 * @param start_addr Register starting address
 * @param reg_buf    Is a pointer to an array containing
 *                   the value of the holding registers to write.
 *                   Note that the array containing the register values must
 *                   be greater than or equal to 'num_regs'
 * @param num_regs   Quantity of registers to write
 *
 * @retval           0 If the function was successful
 */
int mb_rtu_write_holding_regs(const int iface,
			      const uint8_t node_addr,
			      const uint16_t start_addr,
			      uint16_t *const reg_buf,
			      const uint16_t num_regs);

/**
 * @brief Read floating-point holding registers (FC03)
 *
 * Sends a Modbus message to read the value of floating-point
 * holding registers from a server unit.
 *
 * @param iface      Modbus RTU interface index
 * @param node_addr  Modbus RTU address of the server
 * @param start_addr Register starting address
 * @param reg_buf    Is a pointer to an array that will receive
 *                   the current values of the holding registers from
 *                   the server.  The array pointed to by 'reg_buf' needs
 *                   to be able to hold at least 'num_regs' entries.
 * @param num_regs   Quantity of registers to read
 *
 * @retval           0 If the function was successful
 */
int mb_rtu_read_holding_regs_fp(const int iface,
				const uint8_t node_addr,
				const uint16_t start_addr,
				float *const reg_buf,
				const uint16_t num_regs);

/**
 * @brief Write floating-point holding registers (FC16)
 *
 * Sends a Modbus message to write to floating-point holding registers
 * to a server unit.
 *
 * @param iface      Modbus RTU interface index
 * @param node_addr  Modbus RTU address of the server
 * @param start_addr Register starting address
 * @param reg_buf    Is a pointer to an array containing
 *                   the value of the holding registers to write.
 *                   Note that the array containing the register values must
 *                   be greater than or equal to 'num_regs'
 * @param num_regs   Quantity of registers to write
 *
 * @retval           0 If the function was successful
 */
int mb_rtu_write_holding_regs_fp(const int iface,
				 const uint8_t node_addr,
				 const uint16_t start_addr,
				 float *const reg_buf,
				 const uint16_t num_regs);

/** Modbus Server User Callback structure */
struct mbs_rtu_user_callbacks {
	/** Coil read callback */
	int (*coil_rd)(uint16_t addr, bool *state);

	/** Coil write callback */
	int (*coil_wr)(uint16_t addr, bool state);

	/** Discrete Input read callback */
	int (*discrete_input_rd)(uint16_t addr, bool *state);

	/** Input Register read callback */
	int (*input_reg_rd)(uint16_t addr, uint16_t *reg);

	/** Floating Point Input Register read callback */
	int (*input_reg_rd_fp)(uint16_t addr, float *reg);

	/** Holding Register read callback */
	int (*holding_reg_rd)(uint16_t addr, uint16_t *reg);

	/** Holding Register write callback */
	int (*holding_reg_wr)(uint16_t addr, uint16_t reg);

	/** Floating Point Holding Register read callback */
	int (*holding_reg_rd_fp)(uint16_t addr, float *reg);

	/** Floating Point Holding Register write callback */
	int (*holding_reg_wr_fp)(uint16_t addr, float reg);
};

/**
 * @brief Get Modbus RTU interface index according to interface name
 *
 * If there is more than one interface, it can be used to clearly
 * identify interfaces in the application.
 *
 * @param iface_name Modbus RTU interface name
 *
 * @retval           Modbus RTU interface index or negative error value.
 */
int mb_rtu_iface_get_by_name(const char *iface_name);

/**
 * @brief Configure Modbus Interface as server
 *
 * @param iface      Modbus RTU interface index
 * @param node_addr  Modbus RTU address of the server
 * @param baud       Baudrate of the serial line
 * @param parity     UART's parity setting:
 *                       UART_CFG_PARITY_NONE,
 *                       UART_CFG_PARITY_EVEN,
 *                       UART_CFG_PARITY_ODD
 * @param cb         Pointer to the User Callback structure
 * @param ascii_mode Enable ASCII Transfer Mode
 *
 * @retval           0 If the function was successful
 */
int mb_rtu_cfg_server(const uint8_t iface, const uint8_t node_addr,
		      const uint32_t baud, enum uart_config_parity parity,
		      struct mbs_rtu_user_callbacks *const cb,
		      bool ascii_mode);

/**
 * @brief Configure Modbus Interface as client
 *
 * @param iface      Modbus RTU interface index
 * @param baud       Baudrate of the serial line
 * @param parity     UART's parity setting:
 *                       UART_CFG_PARITY_NONE,
 *                       UART_CFG_PARITY_EVEN,
 *                       UART_CFG_PARITY_ODD
 * @param rx_timeout Amount of time client will wait for a response
 *                   from the server.
 * @param ascii_mode Enable ASCII Transfer Mode
 *
 * @retval           0 If the function was successful
 */
int mb_rtu_cfg_client(const uint8_t iface,
		      const uint32_t baud, enum uart_config_parity parity,
		      uint32_t rx_timeout,
		      bool ascii_mode);
/**
 * @brief Disable Modbus Interface
 *
 * This function is called to disable Modbus interface.
 *
 * @param iface      Modbus RTU interface index
 *
 * @retval           0 If the function was successful
 */
int mb_rtu_disable_iface(const uint8_t iface);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* ZEPHYR_INCLUDE_MODBUS_RTU_H_ */
