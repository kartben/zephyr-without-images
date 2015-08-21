/* Port and memory mapped registers I/O operations */

/*
 * Copyright (c) 2015 Intel Corporation.
 *
 * Redistribution and use in source and binary froms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1) Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2) Redistributions in binary from must reproduce the above copyright notice,
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

#ifndef __SYS_IO_H__
#define __SYS_IO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

typedef uint32_t io_port_t;
typedef uint32_t mm_reg_t;

/* Port I/O functions */

/**
 * @fn static inline void sys_out8(uint8_t data, io_port_t port);
 * @brief Output a byte to an I/O port
 *
 * This function writes a byte to the given port.
 *
 * @param data the byte to write
 * @param port the port address where to write the byte
 */

/**
 * @fn static inline uint8_t sys_in8(io_port_t port);
 * @brief Input a byte from an I/O port
 *
 * This function reads a byte from the port.
 *
 * @param port the port address from where to read the byte
 *
 * @return the byte read
 */

/**
 * @fn static inline void sys_out16(uint16_t data, io_port_t port);
 * @brief Output a 16 bits to an I/O port
 *
 * This function writes a 16 bits to the given port.
 *
 * @param data the 16 bits to write
 * @param port the port address where to write the 16 bits
 */

/**
 * @fn static inline uint16_t sys_in16(io_port_t port);
 * @brief Input 16 bits from an I/O port
 *
 * This function reads 16 bits from the port.
 *
 * @param port the port address from where to read the 16 bits
 *
 * @return the 16 bits read
 */

/**
 * @fn static inline void sys_out32(uint32_t data, io_port_t port);
 * @brief Output 32 bits to an I/O port
 *
 * This function writes 32 bits to the given port.
 *
 * @param data the 32 bits to write
 * @param port the port address where to write the 32 bits
 */

/**
 * @fn static inline uint32_t sys_in32(io_port_t port);
 * @brief Input 32 bits from an I/O port
 *
 * This function reads 32 bits from the port.
 *
 * @param port the port address from where to read the 32 bits
 *
 * @return the 32 bits read
 */


/* Memory mapped registers I/O functions */

/**
 * @fn static inline void sys_write8(uint8_t data, mm_reg_t addr);
 * @brief Write a byte to a memory mapped register
 *
 * This function writes a byte to the given memory mapped register.
 *
 * @param data the byte to write
 * @param addr the memory mapped register address where to write the byte
 */

/**
 * @fn static inline uint8_t sys_read8(mm_reg_t addr);
 * @brief Read a byte from a memory mapped register
 *
 * This function reads a byte from the given memory mapped register.
 *
 * @param addr the memory mapped register address from where to read the byte
 *
 * @return the byte read
 */

/**
 * @fn static inline void sys_write16(uint16_t data, mm_reg_t addr);
 * @brief Write 16 bits to a memory mapped register
 *
 * This function writes 16 bits to the given memory mapped register.
 *
 * @param data the 16 bits to write
 * @param addr the memory mapped register address where to write the 16 bits
 */

/**
 * @fn static inline uint16_t sys_read16(mm_reg_t addr);
 * @brief Read 16 bits from a memory mapped register
 *
 * This function reads 16 bits from the given memory mapped register.
 *
 * @param addr the memory mapped register address from where to read
 *        the 16 bits
 *
 * @return the 16 bits read
 */

/**
 * @fn static inline void sys_write32(uint32_t data, mm_reg_t addr);
 * @brief Write 32 bits to a memory mapped register
 *
 * This function writes 32 bits to the given memory mapped register.
 *
 * @param data the 32 bits to write
 * @param addr the memory mapped register address where to write the 32 bits
 */

/**
 * @fn static inline uint32_t sys_read32(mm_reg_t addr);
 * @brief Read 32 bits from a memory mapped register
 *
 * This function reads 32 bits from the given memory mapped register.
 *
 * @param addr the memory mapped register address from where to read
 *        the 32 bits
 *
 * @return the 32 bits read
 */

#ifdef __cplusplus
}
#endif

#endif /* __SYS_IO_H__ */
