static const q7_t in_q7[256] = {
    0x2C, 0x50, 0x2F, 0x6C, 0x2D, 0x30, 0x58, 0x2F,
    0x78, 0x29, 0x47, 0x21, 0x0D, 0x4E, 0x1F, 0x45,
    0x16, 0x3B, 0x10, 0x1B, 0x0F, 0x68, 0x1E, 0x15,
    0x02, 0x52, 0x0F, 0x2A, 0x17, 0x0A, 0x54, 0x6D,
    0x7A, 0x11, 0x52, 0x12, 0x31, 0x4B, 0x3B, 0x32,
    0x33, 0x78, 0x34, 0x5E, 0x55, 0x06, 0x5E, 0x35,
    0x3E, 0x37, 0x0D, 0x52, 0x09, 0x04, 0x72, 0x78,
    0x0F, 0x5F, 0x62, 0x55, 0x3C, 0x7C, 0x45, 0x78,
    0x0C, 0x21, 0x25, 0x04, 0x5D, 0x6F, 0x38, 0x38,
    0x74, 0x20, 0x41, 0x16, 0x24, 0x64, 0x12, 0x7F,
    0x3A, 0x7D, 0x1C, 0x39, 0x10, 0x0E, 0x34, 0x4D,
    0x32, 0x79, 0x16, 0x60, 0x1A, 0x6E, 0x46, 0x63,
    0x08, 0x56, 0x1C, 0x40, 0x17, 0x41, 0x49, 0x78,
    0x46, 0x39, 0x52, 0x0E, 0x44, 0x2D, 0x49, 0x1B,
    0x3D, 0x1A, 0x76, 0x2B, 0x2D, 0x0E, 0x7F, 0x50,
    0x67, 0x0F, 0x67, 0x01, 0x56, 0x12, 0x4A, 0x03,
    0x40, 0x20, 0x1F, 0x69, 0x60, 0x36, 0x6A, 0x4E,
    0x3A, 0x41, 0x39, 0x2D, 0x57, 0x59, 0x6F, 0x67,
    0x6C, 0x63, 0x4D, 0x23, 0x19, 0x5B, 0x37, 0x57,
    0x03, 0x52, 0x02, 0x32, 0x75, 0x29, 0x5C, 0x62,
    0x7F, 0x49, 0x4F, 0x10, 0x2C, 0x51, 0x0C, 0x72,
    0x4D, 0x24, 0x19, 0x47, 0x50, 0x14, 0x0D, 0x75,
    0x7F, 0x19, 0x1F, 0x64, 0x1C, 0x17, 0x0F, 0x3F,
    0x7A, 0x43, 0x0A, 0x38, 0x04, 0x4D, 0x2E, 0x78,
    0x1F, 0x21, 0x7E, 0x34, 0x0A, 0x4F, 0x33, 0x5E,
    0x7C, 0x10, 0x65, 0x5A, 0x01, 0x65, 0x3C, 0x25,
    0x41, 0x0F, 0x26, 0x25, 0x7F, 0x0D, 0x7B, 0x6E,
    0x6E, 0x5E, 0x36, 0x76, 0x56, 0x71, 0x19, 0x48,
    0x00, 0x04, 0x65, 0x4D, 0x36, 0x2C, 0x01, 0x55,
    0x06, 0x2F, 0x16, 0x62, 0x51, 0x1C, 0x7A, 0x7F,
    0x29, 0x26, 0x79, 0x3A, 0x02, 0x25, 0x0F, 0x0A,
    0x7C, 0x34, 0x6B, 0x2D, 0x32, 0x4C, 0x5E, 0x41
    };

static const uint32_t ref_f32[256] = {
    0x3eaed064, 0x3f202e3d, 0x3ebc424e, 0x3f5716aa,
    0x3eb4e870, 0x3ebfce88, 0x3f3080cd, 0x3ebb2eff,
    0x3f701e4c, 0x3ea294e3, 0x3f0e650f, 0x3e83c5d2,
    0x3dce1120, 0x3f1b683e, 0x3e78a4c8, 0x3f095a73,
    0x3e325192, 0x3eea545c, 0x3e03c2f9, 0x3e5ad2c5,
    0x3df38d30, 0x3f4f9fe4, 0x3e71aaa2, 0x3e25684d,
    0x3c900890, 0x3f23d43b, 0x3df7e2dc, 0x3ea6ac84,
    0x3e36d3af, 0x3d98cae3, 0x3f279a4b, 0x3f596296,
    0x3f73297f, 0x3e0813b4, 0x3f240c43, 0x3e0ec11c,
    0x3ec25ef4, 0x3f157c4b, 0x3eea0dea, 0x3ec7a7cb,
    0x3ecd166a, 0x3f6f4edb, 0x3ecf6065, 0x3f3c4caf,
    0x3f2acddb, 0x3d397a36, 0x3f3bc7a3, 0x3ed4961e,
    0x3ef7b492, 0x3edd657a, 0x3dd358dc, 0x3f249104,
    0x3d9649eb, 0x3d078fb1, 0x3f64e9d8, 0x3f6f4f61,
    0x3defa143, 0x3f3ee51c, 0x3f44ebd2, 0x3f2965d4,
    0x3eeff575, 0x3f785e4e, 0x3f0a6410, 0x3f6fdb03,
    0x3dc4557a, 0x3e830ae6, 0x3e95d98f, 0x3cead9c1,
    0x3f3ae7d2, 0x3f5eb941, 0x3ee10721, 0x3ee0cfd4,
    0x3f6836a2, 0x3e7c4b41, 0x3f01838e, 0x3e31c0a6,
    0x3e91f6b6, 0x3f488a0e, 0x3e1371bf, 0x3f7ec4df,
    0x3ee6d862, 0x3f7a1287, 0x3e61ad0c, 0x3ee22f96,
    0x3dff38b7, 0x3dde4fd0, 0x3ed1fe61, 0x3f196e96,
    0x3ec89de5, 0x3f71be28, 0x3e2c0af5, 0x3f40a6de,
    0x3e4f6cdf, 0x3f5b9341, 0x3f0b0200, 0x3f46dfe1,
    0x3d863ec0, 0x3f2c7725, 0x3e627c0b, 0x3f00b08c,
    0x3e347368, 0x3f02ad76, 0x3f11137e, 0x3f6f67d1,
    0x3f0b4c49, 0x3ee5f909, 0x3f238437, 0x3de3102b,
    0x3f08ab0e, 0x3eb281c4, 0x3f11f4fb, 0x3e5a0a96,
    0x3ef3bcef, 0x3e50f340, 0x3f6b3dff, 0x3ead8aa3,
    0x3eb214e9, 0x3de45838, 0x3f7d6fba, 0x3f1fc752,
    0x3f4d54c5, 0x3df648cf, 0x3f4eb176, 0x3c2b30e8,
    0x3f2c1fa1, 0x3e0d8ad7, 0x3f14c998, 0x3cc5c4d1,
    0x3f00cbf1, 0x3e7e8a29, 0x3e7b2e8d, 0x3f51d014,
    0x3f40d031, 0x3ed73442, 0x3f53f14f, 0x3f1c7439,
    0x3ee6caf7, 0x3f027f48, 0x3ee31cd3, 0x3eb3b04c,
    0x3f2eb769, 0x3f31858b, 0x3f5e0c54, 0x3f4e5f27,
    0x3f58d48b, 0x3f46eb1e, 0x3f193758, 0x3e8d2ee0,
    0x3e443934, 0x3f354635, 0x3edabe1b, 0x3f2e10b4,
    0x3cd92caf, 0x3f234139, 0x3c8979e6, 0x3ec841cb,
    0x3f69d673, 0x3ea481bc, 0x3f381962, 0x3f448ea4,
    0x3f800000, 0x3f12f0cd, 0x3f1eae16, 0x3e03f3b8,
    0x3eb07145, 0x3f217565, 0x3dbcf025, 0x3f63de65,
    0x3f19ae3d, 0x3e8eaf69, 0x3e4b829f, 0x3f0dd1bd,
    0x3f209f7d, 0x3e2102e8, 0x3dc872f0, 0x3f6a42ce,
    0x3f7ed361, 0x3e466396, 0x3e789f78, 0x3f47e796,
    0x3e5fb6ab, 0x3e35a4c2, 0x3df54023, 0x3efdd91b,
    0x3f742ac7, 0x3f054f19, 0x3d9f68dc, 0x3ee09623,
    0x3d07ddbc, 0x3f1ac469, 0x3eb78be0, 0x3f7000b7,
    0x3e77eca2, 0x3e828bb1, 0x3f7b33c8, 0x3ece71ba,
    0x3d9a7b5d, 0x3f1e0b75, 0x3ecc2cbb, 0x3f3b08b7,
    0x3f782562, 0x3e010b19, 0x3f4995b7, 0x3f3398be,
    0x3be88070, 0x3f4a1fe0, 0x3eeeaf1f, 0x3e9526e6,
    0x3f02e7f4, 0x3df69bec, 0x3e98748d, 0x3e940097,
    0x3f7fcdca, 0x3dd2b446, 0x3f753a63, 0x3f5c8f69,
    0x3f5c155b, 0x3f3c9cdb, 0x3ed76d21, 0x3f6c0e9b,
    0x3f2b3634, 0x3f619d5d, 0x3e48a303, 0x3f0f11aa,
    0x3b6656f4, 0x3d0564cf, 0x3f4adb25, 0x3f19f91b,
    0x3ed93922, 0x3eaf2adb, 0x3b98b7b1, 0x3f296db0,
    0x3d3c593d, 0x3ebd175d, 0x3e33a5e9, 0x3f43beac,
    0x3f21d277, 0x3e6111b6, 0x3f73b51c, 0x3f7d745b,
    0x3ea34962, 0x3e9855be, 0x3f72df0c, 0x3ee93e7d,
    0x3c6802c5, 0x3e954815, 0x3dee3159, 0x3d982ecd,
    0x3f78f3d1, 0x3ecea39a, 0x3f550d05, 0x3eb3d709,
    0x3ec8f668, 0x3f187e4f, 0x3f3c5d17, 0x3f01cafe
    };

static const q31_t ref_q31[256] = {
    0x2BB418F9, 0x50171E56, 0x2F109370, 0x6B8B54E3,
    0x2D3A1C00, 0x2FF3A217, 0x58406676, 0x2ECBBFAC,
    0x780F2630, 0x28A538AA, 0x4732876A, 0x20F17476,
    0x0CE11200, 0x4DB41ED6, 0x1F14990A, 0x44AD39AC,
    0x164A3248, 0x3A9516FF, 0x10785F1B, 0x1B5A5897,
    0x0F38D304, 0x67CFF1D7, 0x1E355444, 0x14AD0991,
    0x02402241, 0x51EA1D74, 0x0F7E2DC4, 0x29AB2109,
    0x16DA75D0, 0x098CAE30, 0x53CD2598, 0x6CB14B31,
    0x7994BF5B, 0x11027679, 0x5206215E, 0x11D8237B,
    0x3097BCE2, 0x4ABE25A4, 0x3A837A76, 0x31E9F2D5,
    0x33459A9C, 0x77A76D66, 0x33D81955, 0x5E265758,
    0x5566ED6B, 0x05CBD1B0, 0x5DE3D14D, 0x3525878A,
    0x3DED2489, 0x37595E73, 0x0D358DBC, 0x524881F4,
    0x09649EB4, 0x043C7D88, 0x7274EBE7, 0x77A7B0BC,
    0x0EFA1432, 0x5F728E32, 0x6275E937, 0x54B2EA1C,
    0x3BFD5D2E, 0x7C2F26C5, 0x453207FC, 0x77ED817F,
    0x0C4557A1, 0x20C2B987, 0x257663DB, 0x03AB6705,
    0x5D73E8CD, 0x6F5CA053, 0x3841C83F, 0x3833F4E6,
    0x741B50C1, 0x1F89681E, 0x40C1C6D8, 0x163814BF,
    0x247DAD7E, 0x64450701, 0x126E37DE, 0x7F626F5B,
    0x39B61895, 0x7D0943BB, 0x1C35A187, 0x388BE57B,
    0x0FF38B77, 0x0DE4FD00, 0x347F9831, 0x4CB74AEE,
    0x32277925, 0x78DF141B, 0x15815E92, 0x60536EFF,
    0x19ED9BEF, 0x6DC9A054, 0x4581001A, 0x636FF0BA,
    0x0863EC04, 0x563B92BA, 0x1C4F8153, 0x40584638,
    0x168E6CF1, 0x4156BACE, 0x4889BECD, 0x77B3E844,
    0x45A624AB, 0x397E4256, 0x51C21B75, 0x0E3102B3,
    0x44558740, 0x2CA07108, 0x48FA7D91, 0x1B4152BB,
    0x3CEF3BD8, 0x1A1E67FB, 0x759EFFB7, 0x2B62A8CF,
    0x2C853A33, 0x0E45837A, 0x7EB7DD13, 0x4FE3A919,
    0x66AA624A, 0x0F648CEB, 0x6758BAE3, 0x015661D0,
    0x560FD069, 0x11B15AD7, 0x4A64CBDB, 0x03171344,
    0x4065F8A9, 0x1FD1451B, 0x1F65D197, 0x68E809DA,
    0x606818B7, 0x35CD109D, 0x69F8A799, 0x4E3A1CAF,
    0x39B2BDDE, 0x413FA3FC, 0x38C734A9, 0x2CEC131C,
    0x575BB469, 0x58C2C550, 0x6F0629C1, 0x672F938F,
    0x6C6A4562, 0x63758EF1, 0x4C9BABD1, 0x234BB81A,
    0x18872681, 0x5AA31A59, 0x36AF86B1, 0x570859FD,
    0x0364B2BC, 0x51A09CBD, 0x0225E796, 0x321072B0,
    0x74EB39AD, 0x29206F02, 0x5C0CB0DB, 0x624751F2,
    0x7FFFFFFF, 0x49786658, 0x4F570B15, 0x107E770C,
    0x2C1C5146, 0x50BAB290, 0x0BCF024C, 0x71EF329A,
    0x4CD71E95, 0x23ABDA31, 0x197053E3, 0x46E8DE9C,
    0x504FBE5D, 0x14205CF5, 0x0C872EFA, 0x75216716,
    0x7F69B0B0, 0x18CC72C2, 0x1F13EF10, 0x63F3CB2A,
    0x1BF6D55B, 0x16B49844, 0x0F54022E, 0x3F7646DF,
    0x7A1563A3, 0x42A78C82, 0x09F68DC5, 0x382588B2,
    0x043EEDDD, 0x4D623486, 0x2DE2F807, 0x78005BBC,
    0x1EFD943A, 0x20A2EC29, 0x7D99E3F1, 0x339C6E75,
    0x09A7B5D3, 0x4F05BA49, 0x330B2EB6, 0x5D845B53,
    0x7C12B0FE, 0x10216318, 0x64CADB74, 0x59CC5F21,
    0x00E88070, 0x650FF01F, 0x3BABC7B5, 0x2549B96A,
    0x4173FA18, 0x0F69BEBB, 0x261D232C, 0x250025CF,
    0x7FE6E4F3, 0x0D2B445E, 0x7A9D318B, 0x6E47B46A,
    0x6E0AAD99, 0x5E4E6D75, 0x35DB484D, 0x76074D71,
    0x559B1A2A, 0x70CEAE8E, 0x19146065, 0x4788D4FD,
    0x00732B7A, 0x042B2675, 0x656D9259, 0x4CFC8D8D,
    0x364E4868, 0x2BCAB6C2, 0x0098B7B1, 0x54B6D7CA,
    0x05E2C9E8, 0x2F45D756, 0x1674BD10, 0x61DF55F8,
    0x50E93B9E, 0x1C2236CA, 0x79DA8E0B, 0x7EBA2D79,
    0x28D25897, 0x26156F78, 0x796F85DE, 0x3A4F9F40,
    0x01D0058B, 0x25520531, 0x0EE3158C, 0x0982ECD3,
    0x7C79E854, 0x33A8E67A, 0x6A8682A5, 0x2CF5C24F,
    0x323D99FA, 0x4C3F274D, 0x5E2E8B91, 0x40E57F32
    };

static const q15_t ref_q15[256] = {
    0x2BB4, 0x5017, 0x2F11, 0x6B8B, 0x2D3A, 0x2FF4, 0x5840, 0x2ECC,
    0x780F, 0x28A5, 0x4733, 0x20F1, 0x0CE1, 0x4DB4, 0x1F15, 0x44AD,
    0x164A, 0x3A95, 0x1078, 0x1B5A, 0x0F39, 0x67D0, 0x1E35, 0x14AD,
    0x0240, 0x51EA, 0x0F7E, 0x29AB, 0x16DA, 0x098D, 0x53CD, 0x6CB1,
    0x7995, 0x1102, 0x5206, 0x11D8, 0x3098, 0x4ABE, 0x3A83, 0x31EA,
    0x3346, 0x77A7, 0x33D8, 0x5E26, 0x5567, 0x05CC, 0x5DE4, 0x3526,
    0x3DED, 0x3759, 0x0D36, 0x5249, 0x0965, 0x043C, 0x7275, 0x77A8,
    0x0EFA, 0x5F73, 0x6276, 0x54B3, 0x3BFD, 0x7C2F, 0x4532, 0x77EE,
    0x0C45, 0x20C3, 0x2576, 0x03AB, 0x5D74, 0x6F5D, 0x3842, 0x3834,
    0x741B, 0x1F89, 0x40C2, 0x1638, 0x247E, 0x6445, 0x126E, 0x7F62,
    0x39B6, 0x7D09, 0x1C36, 0x388C, 0x0FF4, 0x0DE5, 0x3480, 0x4CB7,
    0x3227, 0x78DF, 0x1581, 0x6053, 0x19EE, 0x6DCA, 0x4581, 0x6370,
    0x0864, 0x563C, 0x1C50, 0x4058, 0x168E, 0x4157, 0x488A, 0x77B4,
    0x45A6, 0x397E, 0x51C2, 0x0E31, 0x4456, 0x2CA0, 0x48FA, 0x1B41,
    0x3CEF, 0x1A1E, 0x759F, 0x2B63, 0x2C85, 0x0E46, 0x7EB8, 0x4FE4,
    0x66AA, 0x0F65, 0x6759, 0x0156, 0x5610, 0x11B1, 0x4A65, 0x0317,
    0x4066, 0x1FD1, 0x1F66, 0x68E8, 0x6068, 0x35CD, 0x69F9, 0x4E3A,
    0x39B3, 0x4140, 0x38C7, 0x2CEC, 0x575C, 0x58C3, 0x6F06, 0x6730,
    0x6C6A, 0x6376, 0x4C9C, 0x234C, 0x1887, 0x5AA3, 0x36B0, 0x5708,
    0x0365, 0x51A1, 0x0226, 0x3210, 0x74EB, 0x2920, 0x5C0D, 0x6247,
    0x7FFF, 0x4978, 0x4F57, 0x107E, 0x2C1C, 0x50BB, 0x0BCF, 0x71EF,
    0x4CD7, 0x23AC, 0x1970, 0x46E9, 0x5050, 0x1420, 0x0C87, 0x7521,
    0x7F6A, 0x18CC, 0x1F14, 0x63F4, 0x1BF7, 0x16B5, 0x0F54, 0x3F76,
    0x7A15, 0x42A8, 0x09F7, 0x3826, 0x043F, 0x4D62, 0x2DE3, 0x7800,
    0x1EFE, 0x20A3, 0x7D9A, 0x339C, 0x09A8, 0x4F06, 0x330B, 0x5D84,
    0x7C13, 0x1021, 0x64CB, 0x59CC, 0x00E9, 0x6510, 0x3BAC, 0x254A,
    0x4174, 0x0F6A, 0x261D, 0x2500, 0x7FE7, 0x0D2B, 0x7A9D, 0x6E48,
    0x6E0B, 0x5E4E, 0x35DB, 0x7607, 0x559B, 0x70CF, 0x1914, 0x4789,
    0x0073, 0x042B, 0x656E, 0x4CFD, 0x364E, 0x2BCB, 0x0099, 0x54B7,
    0x05E3, 0x2F46, 0x1675, 0x61DF, 0x50E9, 0x1C22, 0x79DB, 0x7EBA,
    0x28D2, 0x2615, 0x7970, 0x3A50, 0x01D0, 0x2552, 0x0EE3, 0x0983,
    0x7C7A, 0x33A9, 0x6A87, 0x2CF6, 0x323E, 0x4C3F, 0x5E2F, 0x40E5
    };

