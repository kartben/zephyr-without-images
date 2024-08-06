/*
 * Copyright 2023-2024 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_NXP_S32Z2_CLOCK_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_NXP_S32Z2_CLOCK_H_

#define NXP_S32_FIRC_CLK                           1U
#define NXP_S32_FXOSC_CLK                          2U
#define NXP_S32_SIRC_CLK                           3U
#define NXP_S32_COREPLL_CLK                        4U
#define NXP_S32_PERIPHPLL_CLK                      5U
#define NXP_S32_DDRPLL_CLK                         6U
#define NXP_S32_LFAST0_PLL_CLK                     7U
#define NXP_S32_LFAST1_PLL_CLK                     8U
#define NXP_S32_COREPLL_PHI0_CLK                   9U
#define NXP_S32_COREPLL_DFS0_CLK                   10U
#define NXP_S32_COREPLL_DFS1_CLK                   11U
#define NXP_S32_COREPLL_DFS2_CLK                   12U
#define NXP_S32_COREPLL_DFS3_CLK                   13U
#define NXP_S32_COREPLL_DFS4_CLK                   14U
#define NXP_S32_COREPLL_DFS5_CLK                   15U
#define NXP_S32_PERIPHPLL_PHI0_CLK                 16U
#define NXP_S32_PERIPHPLL_PHI1_CLK                 17U
#define NXP_S32_PERIPHPLL_PHI2_CLK                 18U
#define NXP_S32_PERIPHPLL_PHI3_CLK                 19U
#define NXP_S32_PERIPHPLL_PHI4_CLK                 20U
#define NXP_S32_PERIPHPLL_PHI5_CLK                 21U
#define NXP_S32_PERIPHPLL_PHI6_CLK                 22U
#define NXP_S32_PERIPHPLL_DFS0_CLK                 23U
#define NXP_S32_PERIPHPLL_DFS1_CLK                 24U
#define NXP_S32_PERIPHPLL_DFS2_CLK                 25U
#define NXP_S32_PERIPHPLL_DFS3_CLK                 26U
#define NXP_S32_PERIPHPLL_DFS4_CLK                 27U
#define NXP_S32_PERIPHPLL_DFS5_CLK                 28U
#define NXP_S32_DDRPLL_PHI0_CLK                    29U
#define NXP_S32_LFAST0_PLL_PH0_CLK                 30U
#define NXP_S32_LFAST1_PLL_PH0_CLK                 31U
#define NXP_S32_ETH_RGMII_REF_CLK                  32U
#define NXP_S32_TMR_1588_CLK                       33U
#define NXP_S32_ETH0_EXT_RX_CLK                    34U
#define NXP_S32_ETH0_EXT_TX_CLK                    35U
#define NXP_S32_ETH1_EXT_RX_CLK                    36U
#define NXP_S32_ETH1_EXT_TX_CLK                    37U
#define NXP_S32_LFAST0_EXT_REF_CLK                 38U
#define NXP_S32_LFAST1_EXT_REF_CLK                 39U
#define NXP_S32_DDR_CLK                            40U
#define NXP_S32_P0_SYS_CLK                         41U
#define NXP_S32_P1_SYS_CLK                         42U
#define NXP_S32_P1_SYS_DIV2_CLK                    43U
#define NXP_S32_P1_SYS_DIV4_CLK                    44U
#define NXP_S32_P2_SYS_CLK                         45U
#define NXP_S32_CORE_M33_CLK                       46U
#define NXP_S32_P2_SYS_DIV2_CLK                    47U
#define NXP_S32_P2_SYS_DIV4_CLK                    48U
#define NXP_S32_P3_SYS_CLK                         49U
#define NXP_S32_CE_SYS_DIV2_CLK                    50U
#define NXP_S32_CE_SYS_DIV4_CLK                    51U
#define NXP_S32_P3_SYS_DIV2_NOC_CLK                52U
#define NXP_S32_P3_SYS_DIV4_CLK                    53U
#define NXP_S32_P4_SYS_CLK                         54U
#define NXP_S32_P4_SYS_DIV2_CLK                    55U
#define NXP_S32_HSE_SYS_DIV2_CLK                   56U
#define NXP_S32_P5_SYS_CLK                         57U
#define NXP_S32_P5_SYS_DIV2_CLK                    58U
#define NXP_S32_P5_SYS_DIV4_CLK                    59U
#define NXP_S32_P2_MATH_CLK                        60U
#define NXP_S32_P2_MATH_DIV3_CLK                   61U
#define NXP_S32_GLB_LBIST_CLK                      62U
#define NXP_S32_RTU0_CORE_CLK                      63U
#define NXP_S32_RTU0_CORE_DIV2_CLK                 64U
#define NXP_S32_RTU1_CORE_CLK                      65U
#define NXP_S32_RTU1_CORE_DIV2_CLK                 66U
#define NXP_S32_P0_PSI5_S_UTIL_CLK                 67U
#define NXP_S32_P4_PSI5_S_UTIL_CLK                 68U
#define NXP_S32_ADC0_CLK                           70U
#define NXP_S32_ADC1_CLK                           71U
#define NXP_S32_CE_EDMA_CLK                        72U
#define NXP_S32_CE_PIT0_CLK                        73U
#define NXP_S32_CE_PIT1_CLK                        74U
#define NXP_S32_CE_PIT2_CLK                        75U
#define NXP_S32_CE_PIT3_CLK                        76U
#define NXP_S32_CE_PIT4_CLK                        77U
#define NXP_S32_CE_PIT5_CLK                        78U
#define NXP_S32_CLKOUT0_CLK                        79U
#define NXP_S32_CLKOUT1_CLK                        80U
#define NXP_S32_CLKOUT2_CLK                        81U
#define NXP_S32_CLKOUT3_CLK                        82U
#define NXP_S32_CLKOUT4_CLK                        83U
#define NXP_S32_CTU_CLK                            84U
#define NXP_S32_DMACRC0_CLK                        85U
#define NXP_S32_DMACRC1_CLK                        86U
#define NXP_S32_DMACRC4_CLK                        87U
#define NXP_S32_DMACRC5_CLK                        88U
#define NXP_S32_DMAMUX0_CLK                        89U
#define NXP_S32_DMAMUX1_CLK                        90U
#define NXP_S32_DMAMUX4_CLK                        91U
#define NXP_S32_DMAMUX5_CLK                        92U
#define NXP_S32_EDMA0_CLK                          93U
#define NXP_S32_EDMA1_CLK                          94U
#define NXP_S32_EDMA3_CLK                          95U
#define NXP_S32_EDMA4_CLK                          96U
#define NXP_S32_EDMA5_CLK                          97U
#define NXP_S32_ETH0_TX_MII_CLK                    98U
#define NXP_S32_ENET0_CLK                          99U
#define NXP_S32_P3_CAN_PE_CLK                      100U
#define NXP_S32_FLEXCAN0_CLK                       101U
#define NXP_S32_FLEXCAN1_CLK                       102U
#define NXP_S32_FLEXCAN2_CLK                       103U
#define NXP_S32_FLEXCAN3_CLK                       104U
#define NXP_S32_FLEXCAN4_CLK                       105U
#define NXP_S32_FLEXCAN5_CLK                       106U
#define NXP_S32_FLEXCAN6_CLK                       107U
#define NXP_S32_FLEXCAN7_CLK                       108U
#define NXP_S32_FLEXCAN8_CLK                       109U
#define NXP_S32_FLEXCAN9_CLK                       110U
#define NXP_S32_FLEXCAN10_CLK                      111U
#define NXP_S32_FLEXCAN11_CLK                      112U
#define NXP_S32_FLEXCAN12_CLK                      113U
#define NXP_S32_FLEXCAN13_CLK                      114U
#define NXP_S32_FLEXCAN14_CLK                      115U
#define NXP_S32_FLEXCAN15_CLK                      116U
#define NXP_S32_FLEXCAN16_CLK                      117U
#define NXP_S32_FLEXCAN17_CLK                      118U
#define NXP_S32_FLEXCAN18_CLK                      119U
#define NXP_S32_FLEXCAN19_CLK                      120U
#define NXP_S32_FLEXCAN20_CLK                      121U
#define NXP_S32_FLEXCAN21_CLK                      122U
#define NXP_S32_FLEXCAN22_CLK                      123U
#define NXP_S32_FLEXCAN23_CLK                      124U
#define NXP_S32_P0_FR_PE_CLK                       125U
#define NXP_S32_FRAY0_CLK                          126U
#define NXP_S32_FRAY1_CLK                          127U
#define NXP_S32_GTM_CLK                            128U
#define NXP_S32_IIIC0_CLK                          129U
#define NXP_S32_IIIC1_CLK                          130U
#define NXP_S32_IIIC2_CLK                          131U
#define NXP_S32_P0_LIN_BAUD_CLK                    132U
#define NXP_S32_LIN0_CLK                           133U
#define NXP_S32_LIN1_CLK                           134U
#define NXP_S32_LIN2_CLK                           135U
#define NXP_S32_P1_LIN_BAUD_CLK                    136U
#define NXP_S32_LIN3_CLK                           137U
#define NXP_S32_LIN4_CLK                           138U
#define NXP_S32_LIN5_CLK                           139U
#define NXP_S32_P4_LIN_BAUD_CLK                    140U
#define NXP_S32_LIN6_CLK                           141U
#define NXP_S32_LIN7_CLK                           142U
#define NXP_S32_LIN8_CLK                           143U
#define NXP_S32_P5_LIN_BAUD_CLK                    144U
#define NXP_S32_LIN9_CLK                           145U
#define NXP_S32_LIN10_CLK                          146U
#define NXP_S32_LIN11_CLK                          147U
#define NXP_S32_MSCDSPI_CLK                        148U
#define NXP_S32_MSCLIN_CLK                         149U
#define NXP_S32_NANO_CLK                           150U
#define NXP_S32_P0_CLKOUT_SRC_CLK                  151U
#define NXP_S32_P0_CTU_PER_CLK                     152U
#define NXP_S32_P0_DSPI_MSC_CLK                    153U
#define NXP_S32_P0_EMIOS_LCU_CLK                   154U
#define NXP_S32_P0_GTM_CLK                         155U
#define NXP_S32_P0_GTM_NOC_CLK                     156U
#define NXP_S32_P0_GTM_TS_CLK                      157U
#define NXP_S32_P0_LIN_CLK                         158U
#define NXP_S32_P0_NANO_CLK                        159U
#define NXP_S32_P0_PSI5_125K_CLK                   160U
#define NXP_S32_P0_PSI5_189K_CLK                   161U
#define NXP_S32_P0_PSI5_S_BAUD_CLK                 162U
#define NXP_S32_P0_PSI5_S_CORE_CLK                 163U
#define NXP_S32_P0_PSI5_S_TRIG0_CLK                164U
#define NXP_S32_P0_PSI5_S_TRIG1_CLK                165U
#define NXP_S32_P0_PSI5_S_TRIG2_CLK                166U
#define NXP_S32_P0_PSI5_S_TRIG3_CLK                167U
#define NXP_S32_P0_PSI5_S_UART_CLK                 168U
#define NXP_S32_P0_PSI5_S_WDOG0_CLK                169U
#define NXP_S32_P0_PSI5_S_WDOG1_CLK                170U
#define NXP_S32_P0_PSI5_S_WDOG2_CLK                171U
#define NXP_S32_P0_PSI5_S_WDOG3_CLK                172U
#define NXP_S32_P0_REG_INTF_2X_CLK                 173U
#define NXP_S32_P0_REG_INTF_CLK                    174U
#define NXP_S32_P1_CLKOUT_SRC_CLK                  175U
#define NXP_S32_P1_DSPI60_CLK                      176U
#define NXP_S32_ETH_TS_CLK                         177U
#define NXP_S32_ETH_TS_DIV4_CLK                    178U
#define NXP_S32_ETH0_REF_RMII_CLK                  179U
#define NXP_S32_ETH0_RX_MII_CLK                    180U
#define NXP_S32_ETH0_RX_RGMII_CLK                  181U
#define NXP_S32_ETH0_TX_RGMII_CLK                  182U
#define NXP_S32_ETH0_PS_TX_CLK                     183U
#define NXP_S32_ETH1_REF_RMII_CLK                  184U
#define NXP_S32_ETH1_RX_MII_CLK                    185U
#define NXP_S32_ETH1_RX_RGMII_CLK                  186U
#define NXP_S32_ETH1_TX_MII_CLK                    187U
#define NXP_S32_ETH1_TX_RGMII_CLK                  188U
#define NXP_S32_ETH1_PS_TX_CLK                     189U
#define NXP_S32_P1_LFAST0_REF_CLK                  190U
#define NXP_S32_P1_LFAST1_REF_CLK                  191U
#define NXP_S32_P1_NETC_AXI_CLK                    192U
#define NXP_S32_P1_LIN_CLK                         193U
#define NXP_S32_P1_REG_INTF_CLK                    194U
#define NXP_S32_P2_DBG_ATB_CLK                     195U
#define NXP_S32_P2_REG_INTF_CLK                    196U
#define NXP_S32_P3_AES_CLK                         197U
#define NXP_S32_P3_CLKOUT_SRC_CLK                  198U
#define NXP_S32_P3_DBG_TS_CLK                      199U
#define NXP_S32_P3_REG_INTF_CLK                    200U
#define NXP_S32_P3_SYS_MON1_CLK                    201U
#define NXP_S32_P3_SYS_MON2_CLK                    202U
#define NXP_S32_P3_SYS_MON3_CLK                    203U
#define NXP_S32_P4_CLKOUT_SRC_CLK                  204U
#define NXP_S32_P4_DSPI60_CLK                      205U
#define NXP_S32_P4_EMIOS_LCU_CLK                   206U
#define NXP_S32_P4_LIN_CLK                         207U
#define NXP_S32_P4_PSI5_125K_CLK                   208U
#define NXP_S32_P4_PSI5_189K_CLK                   209U
#define NXP_S32_P4_PSI5_S_BAUD_CLK                 210U
#define NXP_S32_P4_PSI5_S_CORE_CLK                 211U
#define NXP_S32_P4_PSI5_S_TRIG0_CLK                212U
#define NXP_S32_P4_PSI5_S_TRIG1_CLK                213U
#define NXP_S32_P4_PSI5_S_TRIG2_CLK                214U
#define NXP_S32_P4_PSI5_S_TRIG3_CLK                215U
#define NXP_S32_P4_PSI5_S_UART_CLK                 216U
#define NXP_S32_P4_PSI5_S_WDOG0_CLK                217U
#define NXP_S32_P4_PSI5_S_WDOG1_CLK                218U
#define NXP_S32_P4_PSI5_S_WDOG2_CLK                219U
#define NXP_S32_P4_PSI5_S_WDOG3_CLK                220U
#define NXP_S32_P4_QSPI0_2X_CLK                    221U
#define NXP_S32_P4_QSPI0_1X_CLK                    222U
#define NXP_S32_P4_QSPI1_2X_CLK                    223U
#define NXP_S32_P4_QSPI1_1X_CLK                    224U
#define NXP_S32_P4_REG_INTF_2X_CLK                 225U
#define NXP_S32_P4_REG_INTF_CLK                    226U
#define NXP_S32_P4_SDHC_IP_CLK                     227U
#define NXP_S32_P4_SDHC_IP_DIV2_CLK                228U
#define NXP_S32_P5_DIPORT_CLK                      229U
#define NXP_S32_P5_AE_CLK                          230U
#define NXP_S32_P5_CANXL_PE_CLK                    231U
#define NXP_S32_P5_CANXL_CHI_CLK                   232U
#define NXP_S32_P5_CLKOUT_SRC_CLK                  233U
#define NXP_S32_P5_LIN_CLK                         234U
#define NXP_S32_P5_REG_INTF_CLK                    235U
#define NXP_S32_P6_REG_INTF_CLK                    236U
#define NXP_S32_PIT0_CLK                           237U
#define NXP_S32_PIT1_CLK                           238U
#define NXP_S32_PIT4_CLK                           239U
#define NXP_S32_PIT5_CLK                           240U
#define NXP_S32_P0_PSI5_1US_CLK                    241U
#define NXP_S32_PSI5_0_CLK                         242U
#define NXP_S32_P4_PSI5_1US_CLK                    243U
#define NXP_S32_PSI5_1_CLK                         244U
#define NXP_S32_PSI5S_0_CLK                        245U
#define NXP_S32_PSI5S_1_CLK                        246U
#define NXP_S32_QSPI0_CLK                          247U
#define NXP_S32_QSPI1_CLK                          248U
#define NXP_S32_RTU0_CORE_MON1_CLK                 249U
#define NXP_S32_RTU0_CORE_MON2_CLK                 250U
#define NXP_S32_RTU0_CORE_DIV2_MON1_CLK            251U
#define NXP_S32_RTU0_CORE_DIV2_MON2_CLK            252U
#define NXP_S32_RTU0_CORE_DIV2_MON3_CLK            253U
#define NXP_S32_RTU0_REG_INTF_CLK                  254U
#define NXP_S32_RTU1_CORE_MON1_CLK                 255U
#define NXP_S32_RTU1_CORE_MON2_CLK                 256U
#define NXP_S32_RTU1_CORE_DIV2_MON1_CLK            257U
#define NXP_S32_RTU1_CORE_DIV2_MON2_CLK            258U
#define NXP_S32_RTU1_CORE_DIV2_MON3_CLK            259U
#define NXP_S32_RTU1_REG_INTF_CLK                  260U
#define NXP_S32_P4_SDHC_CLK                        261U
#define NXP_S32_RXLUT_CLK                          262U
#define NXP_S32_SDHC0_CLK                          263U
#define NXP_S32_SINC_CLK                           264U
#define NXP_S32_SIPI0_CLK                          265U
#define NXP_S32_SIPI1_CLK                          266U
#define NXP_S32_SIUL2_0_CLK                        267U
#define NXP_S32_SIUL2_1_CLK                        268U
#define NXP_S32_SIUL2_4_CLK                        269U
#define NXP_S32_SIUL2_5_CLK                        270U
#define NXP_S32_P0_DSPI_CLK                        271U
#define NXP_S32_SPI0_CLK                           272U
#define NXP_S32_SPI1_CLK                           273U
#define NXP_S32_P1_DSPI_CLK                        274U
#define NXP_S32_SPI2_CLK                           275U
#define NXP_S32_SPI3_CLK                           276U
#define NXP_S32_SPI4_CLK                           277U
#define NXP_S32_P4_DSPI_CLK                        278U
#define NXP_S32_SPI5_CLK                           279U
#define NXP_S32_SPI6_CLK                           280U
#define NXP_S32_SPI7_CLK                           281U
#define NXP_S32_P5_DSPI_CLK                        282U
#define NXP_S32_SPI8_CLK                           283U
#define NXP_S32_SPI9_CLK                           284U
#define NXP_S32_SRX0_CLK                           285U
#define NXP_S32_SRX1_CLK                           286U

#endif /* ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_NXP_S32Z2_CLOCK_H_ */
