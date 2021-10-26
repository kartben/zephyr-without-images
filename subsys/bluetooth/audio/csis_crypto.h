/*
 * Copyright (c) 2019 Bose Corporation
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include <zephyr/types.h>

#include <bluetooth/audio/csis.h>

#define BT_CSIS_CRYPTO_KEY_SIZE   16
#define BT_CSIS_CRYPTO_SALT_SIZE  16

/**
 * @brief Private Set Unique identifier hash function sih.
 *
 * The PSRI hash function sih is used to generate a hash value that is
 * used in PSRIs - Used by the Coordinated Set Identification service and
 * profile.
 *
 * @param sirk The 16-byte SIRK
 * @param r 3 byte random value
 * @param out The 3 byte output buffer
 * @return int 0 on success, any other value indicates a failure.
 */
int bt_csis_sih(const uint8_t sirk[BT_CSIS_SET_SIRK_SIZE], uint32_t r,
		uint32_t *out);

/**
 * @brief SIRK encryption function sef
 *
 * The SIRK encryption function sef is used by the server to encrypt the SIRK
 * with a key K. The value of K depends on the transport on which the pairing
 * between the client and the server was performed.
 *
 * If the pairing was performed on BR/EDR, K is equal to the Link Key shared by
 * the server and the client.
 *    K = Link Key.
 *
 * If the pairing was performed on LE, the 64 LSBs of K correspond to the 64
 * LSBs of the IRK that the server sent to the client during the Phase 3
 * (Transport Specific Key Distribution) of the pairing procedure (see Volume 3,
 * Part H, Section 2.1 in [2]), and the 64 MSBs of K correspond to the 64 MSBs
 * of the LTK shared by the server and client. That is,
 *    K = LTK_64-127 || IRK_0-63
 *
 * @param k         16-byte key.
 * @param sirk      The unencrypted SIRK.
 * @param out_sirk  The encrypted SIRK.
 * @return int 0 on success, any other value indicates a failure.
 */
int bt_csis_sef(const uint8_t k[BT_CSIS_CRYPTO_KEY_SIZE],
		const uint8_t sirk[BT_CSIS_SET_SIRK_SIZE],
		uint8_t out_sirk[BT_CSIS_SET_SIRK_SIZE]);

/**
 * @brief SIRK decryption function sdf
 *
 * The SIRK decryption function sdf is used by the client to decrypt the SIRK
 * with a key K. The value of K depends on the transport on which the pairing
 * between the client and the server was performed.
 *
 * If the pairing was performed on BR/EDR, K is equal to the Link Key shared by
 * the server and the client.
 *    K = Link Key.
 *
 * If the pairing was performed on LE, the 64 LSBs of K correspond to the 64
 * LSBs of the IRK that the server sent to the client during the Phase 3
 * (Transport Specific Key Distribution) of the pairing procedure (see Volume 3,
 * Part H, Section 2.1 in [2]), and the 64 MSBs of K correspond to the 64 MSBs
 * of the LTK shared by the server and client. That is,
 *    K = LTK_64-127 || IRK_0-63
 *
 * @param k         16-byte key.
 * @param sirk      The encrypted SIRK.
 * @param out_sirk  The decrypted SIRK.
 * @return int 0 on success, any other value indicates a failure.
 */
int bt_csis_sdf(const uint8_t k[BT_CSIS_CRYPTO_KEY_SIZE],
		const uint8_t enc_sirk[BT_CSIS_SET_SIRK_SIZE],
		uint8_t out_sirk[BT_CSIS_SET_SIRK_SIZE]);
