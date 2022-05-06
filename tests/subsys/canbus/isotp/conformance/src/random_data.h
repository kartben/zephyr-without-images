/*
 * Copyright (c) 2019 Alexander Wachter
 *
 * SPDX-License-Identifier: Apache-2.0
 */

static const uint8_t random_data[] = {
	0xdc, 0x70, 0xfa, 0x96, 0xbb, 0x71, 0x49, 0x06, 0x18, 0x75, 0x84, 0xaf,
	0xe3, 0xd4, 0x60, 0x11, 0xf8, 0xf8, 0xfa, 0xc7, 0x67, 0xae, 0xa4, 0x36,
	0x08, 0xe5, 0x76, 0xa6, 0x50, 0x98, 0x2e, 0xc1, 0x4f, 0x91, 0x90, 0x92,
	0xbf, 0xfa, 0x5a, 0xce, 0x6d, 0xeb, 0x2e, 0x5c, 0x77, 0x6b, 0x90, 0xfc,
	0x50, 0xd7, 0x69, 0x04, 0x4b, 0x1d, 0xb3, 0x54, 0x55, 0xba, 0x0f, 0x75,
	0xf5, 0x3b, 0x0c, 0x76, 0xc8, 0x31, 0x7d, 0x9a, 0xb5, 0xcd, 0x4f, 0x70,
	0x47, 0xa0, 0xe3, 0xe5, 0x68, 0x59, 0xfb, 0x1e, 0x20, 0x4a, 0x9c, 0x90,
	0xb6, 0xe7, 0x45, 0x83, 0x8d, 0x71, 0xd7, 0x27, 0xac, 0xef, 0xa3, 0xb9,
	0x39, 0xda, 0x30, 0xac, 0xc3, 0x3a, 0x1c, 0x7c, 0x29, 0x2f, 0xc6, 0xa0,
	0xbc, 0xe1, 0x1d, 0xab, 0x0f, 0x16, 0x30, 0xa4, 0x3c, 0x5d, 0x10, 0x45,
	0x38, 0xc0, 0x82, 0x21, 0xad, 0x4c, 0xb3, 0x27, 0xa8, 0xe8, 0x86, 0xa3,
	0x2a, 0xa1, 0xfb, 0x06, 0xab, 0xa8, 0x95, 0xab, 0xcf, 0x3b, 0x9f, 0x4e,
	0xfa, 0x09, 0xf3, 0x9b, 0x2d, 0x53, 0x1f, 0x8f, 0x00, 0x36, 0x7d, 0x91,
	0xd7, 0xf5, 0xc5, 0x81, 0x62, 0x8c, 0x7e, 0xed, 0x01, 0x2a, 0x8d, 0x8c,
	0x0b, 0xb8, 0x32, 0x48, 0xad, 0x75, 0xd2, 0xb9, 0xf0, 0x8e, 0xac, 0x1e,
	0xfd, 0x3a, 0xac, 0x80, 0xb5, 0x68, 0xf0, 0x84, 0xdc, 0xdf, 0xa9, 0x5a,
	0x76, 0x39, 0xee, 0x7e, 0xd5, 0x46, 0xbc, 0xa5, 0x2d, 0x6c, 0x6f, 0x21,
	0x3a, 0x23, 0xe1, 0x82, 0x68, 0x4d, 0x67, 0xf9, 0xc4, 0x9b, 0xed, 0x77,
	0x9c, 0x5a, 0xc2, 0x09, 0x95, 0xd7, 0x0a, 0x21, 0x94, 0xa7, 0xab, 0x7b,
	0xa9, 0xce, 0xce, 0xc6, 0x7e, 0x55, 0xba, 0x22, 0xe5, 0x6c, 0xd5, 0x28,
	0x8e, 0x9f, 0x23, 0x5f, 0x68, 0xd3, 0xb9, 0x46, 0x3c, 0x43, 0xcb, 0xe8,
	0x9f, 0x7d, 0xb2, 0x08, 0xc8, 0xd6, 0xf8, 0xfa, 0x4e, 0x97, 0xb2, 0x6e,
	0x84, 0x0f, 0x1e, 0xfa, 0x17, 0xcb, 0x63, 0xb9, 0xdd, 0xbe, 0xf1, 0x34,
	0x72, 0xbb, 0xe5, 0x13, 0xd5, 0x7e, 0x02, 0xd1, 0x06, 0x15, 0x50, 0xd5,
	0x7c, 0x91, 0xd5, 0x29, 0x72, 0x58, 0x52, 0x98, 0xb3, 0xa4, 0x4b, 0x54,
	0x12, 0xbc, 0xa2, 0xd1, 0xb5, 0x50, 0x33, 0xe2, 0x81, 0xc2, 0x1a, 0x7a,
	0xf2, 0xf8, 0xe6, 0x61, 0xa3, 0x96, 0xdb, 0xea, 0x39, 0x84, 0xbb, 0x76,
	0x0e, 0xe7, 0x42, 0x6f, 0xee, 0x24, 0x16, 0x33, 0xb1, 0x30, 0x75, 0x9c,
	0x97, 0xf0, 0x34, 0x21, 0xea, 0x60, 0xcd, 0x2e, 0x22, 0x51, 0xa4, 0x0a,
	0x27, 0xd3, 0x6a, 0x36, 0xe2, 0x55, 0xb3, 0xec, 0x6d, 0x99, 0x1a, 0x26,
	0xe6, 0xe0, 0xc3, 0x34, 0x98, 0x8a, 0x95, 0x06, 0x03, 0xa7, 0xc1, 0x4d,
	0x28, 0x25, 0x4d, 0xbd, 0xd3, 0x72, 0xc2, 0x5d, 0x0b, 0xf4, 0x98, 0x52,
	0x27, 0xe0, 0x56, 0xaf, 0xa8, 0x63, 0xa0, 0x7a, 0x63, 0xbb, 0xb3, 0x18,
	0x64, 0xe4, 0xcb, 0x7a, 0x3b, 0xf3, 0x66, 0x44, 0x54, 0xc7, 0xd0, 0x48,
	0xb6, 0x00, 0xed, 0x1c, 0xa2, 0xec, 0x4b, 0x72, 0x0a, 0xb0, 0x7e, 0x27,
	0x25, 0x77, 0x75, 0xa0, 0x94, 0xaf, 0xb2, 0x97, 0xfc, 0x1d, 0xb2, 0xfb,
	0x4b, 0x3a, 0x09, 0x7f, 0x90, 0x05, 0xa0, 0x1d, 0x5f, 0x89, 0x95, 0xb8,
	0x1c, 0x50, 0xa2, 0xfa, 0xd9, 0xf5, 0x20, 0x44, 0x99, 0x28, 0x17, 0xa2,
	0x5c, 0x5e, 0x02, 0x4d, 0xa1, 0xd1, 0xb4, 0xac, 0x77, 0x45, 0xb8, 0x74,
	0xd7, 0xe6, 0xcf, 0x32, 0xee, 0x70, 0x04, 0x05, 0x94, 0x6a, 0x48, 0x8f,
	0xcc, 0x1f, 0xf1, 0xc8, 0x92, 0xee, 0xdd, 0xd1, 0x5b, 0x1b, 0xe6, 0x4c,
	0x1d, 0x10, 0xf8, 0xc7, 0x1e, 0xc9, 0x8d, 0xbb, 0xf2, 0x30, 0x90, 0x05,
	0x5c, 0x07, 0x3c, 0x3e, 0x19, 0xf2, 0xcd, 0x3b, 0xe2, 0x4a, 0xfc, 0xc1,
	0xc3, 0x60, 0x64, 0x5c, 0xd0, 0xdf, 0xf7, 0xe3, 0x0d, 0x22, 0xc3, 0x73,
	0x08, 0x29, 0x6c, 0x31, 0xa5, 0x2f, 0x99, 0x7a, 0x5c, 0x62, 0x24, 0xb9,
	0xe2, 0xb2, 0x0f, 0xc2, 0x32, 0x5d, 0x9e, 0x30, 0x9c, 0xe8, 0x31, 0xd4,
	0x4c, 0x63, 0xfd, 0x08, 0x1c, 0x79, 0xbe, 0xea, 0x04, 0xae, 0x31, 0x82,
	0x10, 0xd2, 0xf9, 0x05, 0x37, 0x0c, 0x6b, 0xce, 0x1d, 0x5b, 0xdd, 0x0b,
	0xdd, 0x4d, 0x1f, 0x47, 0x08, 0xea, 0xf3, 0xf9, 0xd0, 0x5a, 0xf8, 0xf7,
	0x12, 0xdf, 0x6e, 0xe8, 0x80, 0xc5, 0x12, 0x27, 0x2d, 0x31, 0xa5, 0xa5,
	0x32, 0xb0, 0x1c, 0x83, 0x0f, 0x49, 0xec, 0x95, 0x7a, 0x99, 0x41, 0x97,
	0x75, 0x37, 0x64, 0x0c, 0x47, 0x80, 0x7a, 0xe7, 0x13, 0xca, 0xf6, 0x04,
	0x18, 0x5d, 0xc3, 0xb3, 0x00, 0x6a, 0x20, 0x96, 0xfb, 0x54, 0x70, 0xa6,
	0x77, 0x65, 0xdd, 0x61, 0x5e, 0x0e, 0xd8, 0x53, 0x61, 0x57, 0x8b, 0x0e,
	0xa3, 0xc0, 0x30, 0x92, 0xa9, 0xff, 0x13, 0xda, 0xac, 0x5f, 0x38, 0x2c,
	0x85, 0xba, 0x79, 0x75, 0x01, 0x65, 0x52, 0xe0, 0x8a, 0x3c, 0x1b, 0xe5,
	0x61, 0x79, 0x22, 0xb9, 0x37, 0x44, 0x29, 0x0d, 0x8a, 0xc3, 0x6c, 0x2f,
	0x2c, 0x78, 0xcb, 0xab, 0x45, 0x84, 0xb5, 0x88, 0x3a, 0x87, 0x8e, 0x1e,
	0x83, 0x02, 0x15, 0x2e, 0x8d, 0x4c, 0x95, 0xbd, 0x38, 0x83, 0xda, 0xa1,
	0x9f, 0x6b, 0x41, 0xb4, 0x4a, 0x19, 0x3c, 0x6c, 0xca, 0xd2, 0xc2, 0x89,
	0x80, 0x02, 0xd9, 0x41, 0xf6, 0xdc, 0x63, 0x1d, 0x9b, 0x25, 0x25, 0x8b,
	0x45, 0xc2, 0x8f, 0x92, 0x1f, 0xf0, 0xe5, 0x0b, 0x42, 0xfc, 0x70, 0x0e,
	0xf1, 0x73, 0x44, 0xaa, 0x02, 0xb6, 0x46, 0x71, 0x1d, 0x8a, 0x2c, 0x84,
	0xca, 0x48, 0x61, 0x30, 0x44, 0xff, 0x4c, 0xa2, 0x85, 0x98, 0xda, 0x64,
	0x67, 0x3d, 0xef, 0xbe, 0xe4, 0xa8, 0x14, 0x8a, 0xda, 0x63, 0xf3, 0x66,
	0x39, 0x07, 0x97, 0xdd, 0x5f, 0xea, 0x00, 0x52, 0x56, 0x1a, 0xc9, 0xbc,
	0x87, 0xf3, 0x93, 0xda, 0x30, 0xaf, 0x82, 0x87, 0xb0, 0x8e, 0xa5, 0x60,
	0x39, 0xf7, 0xd0, 0x15, 0x29, 0xc9, 0x82, 0xe8, 0xe0, 0x95, 0x25, 0x51,
	0x70, 0xa3, 0x67, 0xae, 0x37, 0x62, 0x5d, 0xac, 0x73, 0x7f, 0x77, 0x8d,
	0xc7, 0xa1, 0x82, 0xf3, 0x69, 0xd9, 0x95, 0x93, 0x83, 0x95, 0x37, 0x17,
	0x86, 0x13, 0x5b, 0xb2, 0x82, 0x4a, 0x5b, 0xe3, 0x9b, 0xed, 0x16, 0x9b,
	0x8e, 0x25, 0xc8, 0x64, 0xb0, 0x82, 0x16, 0x16, 0xa0, 0x79, 0x7b, 0x0a,
	0xbb, 0xd6, 0xa2, 0x27, 0x6e, 0x07, 0x5b, 0x48, 0x48, 0x49, 0xff, 0x67,
	0x47, 0x4c, 0xe9, 0xea, 0xe0, 0xf8, 0x15, 0x1f, 0x63, 0xaf, 0x41, 0xa6,
	0xed, 0xd4, 0x3e, 0x68, 0x2a, 0xdf, 0x1b, 0x8f, 0x68, 0x16, 0xe2, 0xb7,
	0x3a, 0x7e, 0x57, 0x18, 0x81, 0x6b, 0xb6, 0xb3, 0x35, 0x30, 0x55, 0xf3,
	0xf9, 0xc9, 0xe6, 0x58, 0x78, 0xa6, 0xf3, 0x02, 0x3e, 0x3c, 0x35, 0x10,
	0x41, 0x2c, 0x6e, 0x2c, 0x5b, 0xb2, 0x1c, 0x66, 0xbd, 0x1f, 0x4b, 0xd9,
	0x87, 0xcd, 0x54, 0x1b, 0x1e, 0x9a, 0x92, 0xdc, 0x82, 0xae, 0x1c, 0xbc,
	0x2f, 0xea, 0x9d, 0x35, 0xdc, 0x3f, 0x9b, 0x18, 0xa2, 0x94, 0x59, 0xd0,
	0xea, 0x80, 0xa6, 0xb0, 0xf7, 0x63, 0x6f, 0x4d, 0x63, 0x03, 0x14, 0x94,
	0x00, 0x48, 0x7f, 0xbc, 0xe0, 0xb3, 0x52, 0xbc, 0x09, 0xa9, 0x33, 0x51,
	0x05, 0xf0, 0x2b, 0x6c, 0xad, 0x78, 0xd0, 0xe5, 0x89, 0xc0, 0x94, 0x49,
	0x62, 0xb9, 0x04, 0x71, 0x13, 0xb1, 0x2b, 0x24, 0xcb, 0x6b, 0x2b, 0x71,
	0xde, 0x58, 0x8a, 0x01, 0x4c, 0x95, 0x63, 0xa1, 0x29, 0xcb, 0x66, 0x83,
	0x58, 0x5c, 0x9e, 0x04
};
