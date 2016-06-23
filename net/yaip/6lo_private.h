/** @file
 @brief 6lowpan private header

 This is not to be included by the application.
 */

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>

/* 6lopan dispatches */
#define NET6LO_DISPATH_IPV6		0x41 /* 01000001 */
#define NET6LO_DISPATH_BROADCAST	0x50 /* 01010000 */
#define NET6LO_DISPATH_IPHC		0x60 /* 01100000 */
#define NET6LO_DISPATH_MESH		0x80 /* 10xxxxxx */
#define NET6LO_DISPATH_FRAG1	0xC0 /* 11000xxx */
#define NET6LO_DISPATH_FRAGN	0xE0 /* 11100xxx */

/**
  * TF (Traffic class and Flow label)
  * 00:  ECN + DSCP + 4-bit Pad + Flow Label (4 bytes)
  * 01:  ECN + 2-bit Pad + Flow Label (3 bytes), DSCP is elided.
  * 10:  ECN + DSCP (1 byte), Flow Label is elided.
  * 11:  Traffic Class and Flow Label are elided.
  */
#define NET6LO_IPHC_TF_00		0x00
#define NET6LO_IPHC_TF_01		0x08
#define NET6LO_IPHC_TF_10		0x10
#define NET6LO_IPHC_TF_11		0x18

/* NH (next header) */
#define NET6LO_IPHC_NH_0		0x00
#define NET6LO_IPHC_NH_1		0x04

/* HLIM (Hop Limit) */
#define NET6LO_IPHC_HLIM		0x00 /* 00 */
#define NET6LO_IPHC_HLIM1		0x01 /* 01 */
#define NET6LO_IPHC_HLIM64		0x02 /* 10 */
#define NET6LO_IPHC_HLIM255		0x03 /* 11 */

/* CID (Context Identifier Extension) */
#define NET6LO_IPHC_CID_0		0x00
#define NET6LO_IPHC_CID_1		0x80

/* SAC (Source Address Compression) */
#define NET6LO_IPHC_SAC_0		0x00
#define NET6LO_IPHC_SAC_1		0x40

/* SAM (Source Address Mode) */
#define NET6LO_IPHC_SAM_00		0x00
#define NET6LO_IPHC_SAM_01		0x10
#define NET6LO_IPHC_SAM_10		0x20
#define NET6LO_IPHC_SAM_11		0x30

/* M (Multicast compression) */
#define NET6LO_IPHC_M_0		0x00
#define NET6LO_IPHC_M_1		0x08

/* DAC (Destination Address Compression) */
#define NET6LO_IPHC_DAC_0		0x00
#define NET6LO_IPHC_DAC_1		0x04

/* DAM (Destination Address Mode) */
#define NET6LO_IPHC_DAM_00		0x00
#define NET6LO_IPHC_DAM_01		0x01
#define NET6LO_IPHC_DAM_10		0x02
#define NET6LO_IPHC_DAM_11		0x03

/* Next Header UDP */
#define NET6LO_NHC_UDP_BARE		0xF0

#define NET6LO_NHC_UDP_CHKSUM_0	0x00
#define NET6LO_NHC_UDP_CHKSUM_1	0x08

#define NET6LO_NHC_UDP_PORT_00	0x00
#define NET6LO_NHC_UDP_PORT_01	0x01
#define NET6LO_NHC_UDP_PORT_10	0x02
#define NET6LO_NHC_UDP_PORT_11	0x03

#define NET6LO_NHC_UDP_8_BIT_PORT	0xF0
#define NET6LO_NHC_UDP_4_BIT_PORT	0xF0B

#define IPHC ((frag)->data)
#define CIPHC ((buf->frags)->data)
