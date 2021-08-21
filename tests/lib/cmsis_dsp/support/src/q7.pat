static const q7_t in_q7[256] = {
    0x03, 0x64, 0x09, 0x53, 0x31, 0x5F, 0x1F, 0x70,
    0x14, 0x41, 0x42, 0x7D, 0x3F, 0x04, 0x39, 0x30,
    0x43, 0x71, 0x20, 0x49, 0x39, 0x2B, 0x2B, 0x1C,
    0x6A, 0x03, 0x43, 0x7A, 0x4A, 0x66, 0x7A, 0x0A,
    0x75, 0x67, 0x74, 0x25, 0x2F, 0x5D, 0x3E, 0x19,
    0x62, 0x7E, 0x32, 0x5E, 0x7F, 0x3C, 0x44, 0x48,
    0x52, 0x5C, 0x2E, 0x7F, 0x70, 0x56, 0x45, 0x64,
    0x54, 0x4D, 0x12, 0x2D, 0x6B, 0x54, 0x1A, 0x6C,
    0x28, 0x07, 0x0D, 0x3A, 0x6F, 0x70, 0x03, 0x39,
    0x55, 0x23, 0x54, 0x23, 0x26, 0x03, 0x48, 0x4E,
    0x1D, 0x7C, 0x7C, 0x65, 0x69, 0x7E, 0x43, 0x3B,
    0x4E, 0x29, 0x41, 0x5B, 0x34, 0x45, 0x12, 0x26,
    0x39, 0x74, 0x6E, 0x16, 0x39, 0x08, 0x43, 0x28,
    0x16, 0x15, 0x6A, 0x40, 0x32, 0x1E, 0x40, 0x65,
    0x53, 0x28, 0x3D, 0x5F, 0x1B, 0x05, 0x53, 0x7C,
    0x67, 0x7D, 0x1B, 0x38, 0x2E, 0x00, 0x7E, 0x1F,
    0x3F, 0x3B, 0x3A, 0x10, 0x50, 0x50, 0x36, 0x7C,
    0x61, 0x7F, 0x31, 0x68, 0x7B, 0x2E, 0x28, 0x4E,
    0x61, 0x5C, 0x22, 0x00, 0x74, 0x3D, 0x0B, 0x5B,
    0x3B, 0x63, 0x53, 0x6F, 0x17, 0x0D, 0x60, 0x46,
    0x49, 0x7D, 0x36, 0x11, 0x34, 0x67, 0x22, 0x6D,
    0x7C, 0x32, 0x25, 0x53, 0x23, 0x7D, 0x4F, 0x11,
    0x01, 0x0E, 0x55, 0x28, 0x65, 0x10, 0x7E, 0x7B,
    0x2F, 0x2B, 0x71, 0x72, 0x75, 0x5D, 0x6D, 0x66,
    0x48, 0x27, 0x00, 0x12, 0x2C, 0x30, 0x02, 0x15,
    0x4B, 0x1D, 0x20, 0x32, 0x2F, 0x5E, 0x11, 0x51,
    0x4C, 0x60, 0x51, 0x21, 0x70, 0x39, 0x21, 0x12,
    0x72, 0x59, 0x71, 0x30, 0x37, 0x65, 0x2E, 0x14,
    0x10, 0x25, 0x0D, 0x71, 0x7F, 0x49, 0x37, 0x76,
    0x20, 0x6C, 0x1A, 0x63, 0x1E, 0x01, 0x74, 0x27,
    0x43, 0x6B, 0x52, 0x53, 0x3F, 0x02, 0x13, 0x13,
    0x79, 0x2B, 0x38, 0x4F, 0x2E, 0x06, 0x4E, 0x45
    };

static const uint32_t ref_f32[256] = {
    0x3cdaae8c, 0x3f474e41, 0x3d8f21ec, 0x3f25318a,
    0x3ec50f7e, 0x3f3d0d19, 0x3e7ba409, 0x3f5fa32d,
    0x3e23e890, 0x3f012b75, 0x3f032914, 0x3f7a9f5c,
    0x3efb0ebc, 0x3ce11291, 0x3ee5bb7f, 0x3ebf38d3,
    0x3f056a6e, 0x3f61d6ab, 0x3e7ceff0, 0x3f11cf88,
    0x3ee3091e, 0x3eab939a, 0x3ead5245, 0x3e6142b9,
    0x3f53e874, 0x3cc56327, 0x3f0620ee, 0x3f7406e6,
    0x3f134927, 0x3f4b9e6a, 0x3f740848, 0x3d990424,
    0x3f69da88, 0x3f4d3369, 0x3f677219, 0x3e951d6c,
    0x3ebcf24b, 0x3f3ad20d, 0x3ef95e32, 0x3e49959a,
    0x3f446541, 0x3f7cbfb2, 0x3ec8b8ee, 0x3f3c009a,
    0x3f7d3653, 0x3ef17b53, 0x3f073c8d, 0x3f0f0a6f,
    0x3f23c72d, 0x3f3748f7, 0x3eb62e0c, 0x3f7e6c27,
    0x3f5fcbc6, 0x3f2c6615, 0x3f095cf9, 0x3f47f639,
    0x3f288205, 0x3f199cc0, 0x3e127817, 0x3eb3eff8,
    0x3f55d902, 0x3f286448, 0x3e4f84cf, 0x3f58e534,
    0x3e9fbad8, 0x3d5181b6, 0x3dd5b675, 0x3ee8fb1f,
    0x3f5eef65, 0x3f5f6f8d, 0x3ccdacdf, 0x3ee2a28e,
    0x3f299a57, 0x3e8db5d8, 0x3f2774ea, 0x3e8a774b,
    0x3e96688a, 0x3ccdcc40, 0x3f0f9678, 0x3f1c5a25,
    0x3e698fc9, 0x3f7780b4, 0x3f78888d, 0x3f49b36f,
    0x3f521562, 0x3f7b0c9e, 0x3f052794, 0x3eebc571,
    0x3f1c421b, 0x3ea414fb, 0x3f02b782, 0x3f36674e,
    0x3ecfb71a, 0x3f0a2058, 0x3e0d7c0b, 0x3e98b990,
    0x3ee4372f, 0x3f687ded, 0x3f5ca5a6, 0x3e327686,
    0x3ee47d8e, 0x3d85b4af, 0x3f052964, 0x3ea0b631,
    0x3e337f1b, 0x3e266bc5, 0x3f54e428, 0x3efea8e6,
    0x3ec87ef5, 0x3e73134e, 0x3f00f7fe, 0x3f493d5f,
    0x3f26fa35, 0x3ea11938, 0x3ef3a7e0, 0x3f3ecbc5,
    0x3e552735, 0x3d2505d9, 0x3f253bd5, 0x3f7807f1,
    0x3f4e7ce6, 0x3f798c6f, 0x3e56174e, 0x3ede4108,
    0x3eb90dfc, 0x3affa413, 0x3f7b998d, 0x3e74ad6c,
    0x3efb2b5b, 0x3eea783c, 0x3ee795b1, 0x3e002afa,
    0x3f1fcfd7, 0x3f20e973, 0x3ed6434f, 0x3f7860d0,
    0x3f42c5ab, 0x3f7e3599, 0x3ec33f48, 0x3f4f051e,
    0x3f764c5f, 0x3eb714ed, 0x3ea0a588, 0x3f1ce5dd,
    0x3f426d77, 0x3f38827a, 0x3e867abc, 0x3ac3ca12,
    0x3f67bd88, 0x3ef3b27e, 0x3db6c68d, 0x3f356dbe,
    0x3eec30df, 0x3f45941d, 0x3f26900b, 0x3f5d723e,
    0x3e360ccc, 0x3dd7c7b9, 0x3f3f3974, 0x3f0c1a39,
    0x3f128a8c, 0x3f7ac105, 0x3ed72933, 0x3e04ed79,
    0x3ecf1a0e, 0x3f4d6c8a, 0x3e8945f8, 0x3f5a7cdb,
    0x3f781df4, 0x3ec64d82, 0x3e934118, 0x3f26c02e,
    0x3e8bb48f, 0x3f7a9fce, 0x3f1e2c17, 0x3e08b9fb,
    0x3c350d33, 0x3dda3cbf, 0x3f299733, 0x3ea0f9ae,
    0x3f49e6e1, 0x3dff5af4, 0x3f7c502f, 0x3f75b0a5,
    0x3ebb6ebd, 0x3eadcc9e, 0x3f61ca63, 0x3f6407ca,
    0x3f6a8432, 0x3f39835c, 0x3f599f87, 0x3f4cec04,
    0x3f0f6c5a, 0x3e9bbd45, 0x3b0fe09d, 0x3e101866,
    0x3eaf8689, 0x3ec0b364, 0x3c9ce29b, 0x3e292903,
    0x3f157de0, 0x3e6b8118, 0x3e812da2, 0x3ec99988,
    0x3ebcae9d, 0x3f3cc440, 0x3e0a2e6e, 0x3f2112b5,
    0x3f183869, 0x3f3f9623, 0x3f22bd63, 0x3e853fb0,
    0x3f608f6f, 0x3ee394b2, 0x3e85d7a8, 0x3e1049a3,
    0x3f64f1b8, 0x3f32055e, 0x3f6186fd, 0x3ebead61,
    0x3edb59ee, 0x3f49e340, 0x3eb9a749, 0x3e21622b,
    0x3dfa4c99, 0x3e93c9fa, 0x3dd389af, 0x3f622926,
    0x3f800000, 0x3f1178a2, 0x3edd4357, 0x3f6c34ff,
    0x3e81dffe, 0x3f584f58, 0x3e4edfb3, 0x3f46c39b,
    0x3e6c9e3b, 0x3bcbafc0, 0x3f675856, 0x3e9a3362,
    0x3f055282, 0x3f5566f9, 0x3f24fceb, 0x3f257d5c,
    0x3efa0b8b, 0x3c8fb9ee, 0x3e156c40, 0x3e160e9b,
    0x3f7200ae, 0x3ead566d, 0x3edf4aa7, 0x3f1d34c5,
    0x3eb62204, 0x3d4d7776, 0x3f1b9252, 0x3f09ea32
    };

static const q31_t ref_q31[256] = {
    0x036ABA30, 0x63A72056, 0x08F21EC3, 0x5298C4D1,
    0x3143DF8E, 0x5E868C6A, 0x1F74812D, 0x6FD19645,
    0x147D11F8, 0x4095BA41, 0x41948A36, 0x7D4FAE07,
    0x3EC3AF17, 0x03844A44, 0x396EDFCE, 0x2FCE34A8,
    0x42B53700, 0x70EB556F, 0x1F9DFDF4, 0x48E7C43E,
    0x38C2479A, 0x2AE4E692, 0x2B549121, 0x1C28572F,
    0x69F43A1F, 0x03158C9D, 0x4310771A, 0x7A0372E7,
    0x49A49346, 0x65CF3502, 0x7A04242D, 0x0990423C,
    0x74ED43EE, 0x6699B4BF, 0x73B90C71, 0x25475B1F,
    0x2F3C92CA, 0x5D690649, 0x3E578C97, 0x1932B34C,
    0x6232A0BA, 0x7E5FD8F7, 0x322E3B8B, 0x5E004D1E,
    0x7E9B295C, 0x3C5ED4C8, 0x439E465C, 0x4785375B,
    0x51E39649, 0x5BA47B41, 0x2D8B82EF, 0x7F361349,
    0x6FE5E2E4, 0x56330A93, 0x44AE7C82, 0x63FB1C85,
    0x54410273, 0x4CCE5FDD, 0x124F02E6, 0x2CFBFDEA,
    0x6AEC813F, 0x5432242C, 0x19F099EE, 0x6C729A2C,
    0x27EEB60E, 0x068C0DB3, 0x0D5B674A, 0x3A3EC7D0,
    0x6F77B25A, 0x6FB7C67C, 0x0336B37D, 0x38A8A37A,
    0x54CD2B8E, 0x236D761F, 0x53BA74DC, 0x229DD2A4,
    0x259A2289, 0x033730FE, 0x47CB3BE6, 0x4E2D12AA,
    0x1D31F92C, 0x7BC05A24, 0x7C4446B7, 0x64D9B797,
    0x690AB101, 0x7D864F39, 0x4293CA05, 0x3AF15C29,
    0x4E210D4E, 0x29053EBF, 0x415BC0CA, 0x5B33A6D6,
    0x33EDC696, 0x45102BC6, 0x11AF8152, 0x262E63F9,
    0x390DCBD2, 0x743EF644, 0x6E52D30F, 0x164ED0CA,
    0x391F6377, 0x085B4AF1, 0x4294B218, 0x282D8C32,
    0x166FE35E, 0x14CD789E, 0x6A7213CC, 0x3FAA397F,
    0x321FBD36, 0x1E6269B8, 0x407BFEF9, 0x649EAF83,
    0x537D1A68, 0x28464E0B, 0x3CE9F801, 0x5F65E2A1,
    0x1AA4E691, 0x05282EC7, 0x529DEA90, 0x7C03F8BC,
    0x673E72DD, 0x7CC6375F, 0x1AC2E9C0, 0x3790420B,
    0x2E437F1A, 0x003FE905, 0x7DCCC64D, 0x1E95AD8D,
    0x3ECAD6D1, 0x3A9E0EE3, 0x39E56C2D, 0x10055F45,
    0x4FE7EBAA, 0x5074B948, 0x3590D3CF, 0x7C3067F4,
    0x6162D570, 0x7F1ACC71, 0x30CFD1E1, 0x67828EEF,
    0x7B262FA6, 0x2DC53B2D, 0x28296209, 0x4E72EE76,
    0x6136BB67, 0x5C413D07, 0x219EAF09, 0x0030F284,
    0x73DEC3E5, 0x3CEC9F99, 0x0B6C68CF, 0x5AB6DEFD,
    0x3B0C37DA, 0x62CA0E41, 0x53480582, 0x6EB91EE4,
    0x16C19988, 0x0D7C7B96, 0x5F9CBA3C, 0x460D1C43,
    0x4945461F, 0x7D6082B5, 0x35CA4CBC, 0x109DAF2C,
    0x33C6839A, 0x66B644CA, 0x22517DE8, 0x6D3E6D50,
    0x7C0EFA03, 0x31936074, 0x24D045FD, 0x536016E6,
    0x22ED23C0, 0x7D4FE73B, 0x4F160BB7, 0x11173F5B,
    0x016A1A65, 0x0DA3CBF1, 0x54CB9950, 0x283E6B96,
    0x64F37085, 0x0FF5AF3A, 0x7E2817AA, 0x7AD8526A,
    0x2EDBAF50, 0x2B732762, 0x70E53141, 0x7203E4F2,
    0x754218EC, 0x5CC1ADE0, 0x6CCFC351, 0x66760217,
    0x47B62CC2, 0x26EF515A, 0x0047F04F, 0x12030CCF,
    0x2BE1A243, 0x302CD907, 0x02738A6D, 0x15252058,
    0x4ABEEFC8, 0x1D70230E, 0x204B6878, 0x32666212,
    0x2F2BA744, 0x5E622004, 0x1145CDC2, 0x50895AAC,
    0x4C1C3451, 0x5FCB1169, 0x515EB15F, 0x214FEC0E,
    0x7047B7A9, 0x38E52C85, 0x2175EA15, 0x12093460,
    0x7278DC3A, 0x5902AF19, 0x70C37E74, 0x2FAB583A,
    0x36D67B9E, 0x64F19FE6, 0x2E69D223, 0x142C4560,
    0x0FA4C98C, 0x24F27E8F, 0x0D389AF6, 0x711492D0,
    0x7FFFFFFF, 0x48BC50FC, 0x3750D5DC, 0x761A7FBB,
    0x2077FF97, 0x6C27ABD5, 0x19DBF65F, 0x6361CD72,
    0x1D93C756, 0x00CBAFC0, 0x73AC2AF2, 0x268CD890,
    0x42A9413E, 0x6AB37C88, 0x527E75BB, 0x52BEAE19,
    0x3E82E2B7, 0x023EE7B9, 0x12AD87F6, 0x12C1D360,
    0x790056F2, 0x2B559B3D, 0x37D2A9C7, 0x4E9A6259,
    0x2D888103, 0x066BBBB2, 0x4DC9291E, 0x44F518FD
    };

static const q15_t ref_q15[256] = {
    0x036B, 0x63A7, 0x08F2, 0x5299, 0x3144, 0x5E87, 0x1F75, 0x6FD2,
    0x147D, 0x4096, 0x4195, 0x7D50, 0x3EC4, 0x0384, 0x396F, 0x2FCE,
    0x42B5, 0x70EB, 0x1F9E, 0x48E8, 0x38C2, 0x2AE5, 0x2B55, 0x1C28,
    0x69F4, 0x0316, 0x4310, 0x7A03, 0x49A5, 0x65CF, 0x7A04, 0x0990,
    0x74ED, 0x669A, 0x73B9, 0x2547, 0x2F3D, 0x5D69, 0x3E58, 0x1933,
    0x6233, 0x7E60, 0x322E, 0x5E00, 0x7E9B, 0x3C5F, 0x439E, 0x4785,
    0x51E4, 0x5BA4, 0x2D8C, 0x7F36, 0x6FE6, 0x5633, 0x44AE, 0x63FB,
    0x5441, 0x4CCE, 0x124F, 0x2CFC, 0x6AED, 0x5432, 0x19F1, 0x6C73,
    0x27EF, 0x068C, 0x0D5B, 0x3A3F, 0x6F78, 0x6FB8, 0x0337, 0x38A9,
    0x54CD, 0x236D, 0x53BA, 0x229E, 0x259A, 0x0337, 0x47CB, 0x4E2D,
    0x1D32, 0x7BC0, 0x7C44, 0x64DA, 0x690B, 0x7D86, 0x4294, 0x3AF1,
    0x4E21, 0x2905, 0x415C, 0x5B34, 0x33EE, 0x4510, 0x11B0, 0x262E,
    0x390E, 0x743F, 0x6E53, 0x164F, 0x391F, 0x085B, 0x4295, 0x282E,
    0x1670, 0x14CD, 0x6A72, 0x3FAA, 0x3220, 0x1E62, 0x407C, 0x649F,
    0x537D, 0x2846, 0x3CEA, 0x5F66, 0x1AA5, 0x0528, 0x529E, 0x7C04,
    0x673E, 0x7CC6, 0x1AC3, 0x3790, 0x2E43, 0x0040, 0x7DCD, 0x1E96,
    0x3ECB, 0x3A9E, 0x39E5, 0x1005, 0x4FE8, 0x5075, 0x3591, 0x7C30,
    0x6163, 0x7F1B, 0x30D0, 0x6783, 0x7B26, 0x2DC5, 0x2829, 0x4E73,
    0x6137, 0x5C41, 0x219F, 0x0031, 0x73DF, 0x3CED, 0x0B6C, 0x5AB7,
    0x3B0C, 0x62CA, 0x5348, 0x6EB9, 0x16C2, 0x0D7C, 0x5F9D, 0x460D,
    0x4945, 0x7D61, 0x35CA, 0x109E, 0x33C7, 0x66B6, 0x2251, 0x6D3E,
    0x7C0F, 0x3193, 0x24D0, 0x5360, 0x22ED, 0x7D50, 0x4F16, 0x1117,
    0x016A, 0x0DA4, 0x54CC, 0x283E, 0x64F3, 0x0FF6, 0x7E28, 0x7AD8,
    0x2EDC, 0x2B73, 0x70E5, 0x7204, 0x7542, 0x5CC2, 0x6CD0, 0x6676,
    0x47B6, 0x26EF, 0x0048, 0x1203, 0x2BE2, 0x302D, 0x0274, 0x1525,
    0x4ABF, 0x1D70, 0x204B, 0x3266, 0x2F2C, 0x5E62, 0x1146, 0x5089,
    0x4C1C, 0x5FCB, 0x515F, 0x2150, 0x7048, 0x38E5, 0x2176, 0x1209,
    0x7279, 0x5903, 0x70C3, 0x2FAB, 0x36D6, 0x64F2, 0x2E6A, 0x142C,
    0x0FA5, 0x24F2, 0x0D39, 0x7115, 0x7FFF, 0x48BC, 0x3751, 0x761A,
    0x2078, 0x6C28, 0x19DC, 0x6362, 0x1D94, 0x00CC, 0x73AC, 0x268D,
    0x42A9, 0x6AB3, 0x527E, 0x52BF, 0x3E83, 0x023F, 0x12AE, 0x12C2,
    0x7900, 0x2B56, 0x37D3, 0x4E9A, 0x2D89, 0x066C, 0x4DC9, 0x44F5
    };

