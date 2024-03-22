# SPDX-License-Identifier: Apache-2.0

# This file contains boards in Zephyr which has been replaced with a new board
# name.
# This allows the system to automatically change the board while at the same
# time prints a warning to the user, that the board name is deprecated.
#
# To add a board rename, add a line in following format:
# set(<old_board_name>_DEPRECATED <new_board_name>)

set(96b_carbon_DEPRECATED
    96b_carbon/stm32f401xe
)
set(96b_carbon_nrf51_DEPRECATED
    96b_carbon/nrf51822
)
set(96b_meerkat96_DEPRECATED
    96b_meerkat96/mcimx7d/m4
)
set(actinius_icarus_bee_ns_DEPRECATED
    actinius_icarus_bee/nrf9160/ns
)
set(actinius_icarus_ns_DEPRECATED
    actinius_icarus/nrf9160/ns
)
set(actinius_icarus_som_dk_ns_DEPRECATED
    actinius_icarus_som_dk/nrf9160/ns
)
set(actinius_icarus_som_ns_DEPRECATED
    actinius_icarus_som/nrf9160/ns
)
set(adafruit_feather_nrf52840_DEPRECATED
    adafruit_feather
)
set(adafruit_itsybitsy_nrf52840_DEPRECATED
    adafruit_itsybitsy
)
set(adp_xc7k_ae350_DEPRECATED
    adp_xc7k
)
set(am62x_m4_phyboard_lyra_DEPRECATED
    phyboard_lyra_am62x/am6234/m4
)
set(am62x_m4_sk_DEPRECATED
    sk_am62/am6234/m4
)
set(arduino_giga_r1_m4_DEPRECATED
    arduino_giga_r1/stm32h747xx/m4
)
set(arduino_giga_r1_m7_DEPRECATED
    arduino_giga_r1/stm32h747xx/m7
)
set(arduino_nano_33_ble_sense_DEPRECATED
    arduino_nano_33_ble/nrf52840/sense
)
set(arduino_opta_m4_DEPRECATED
    arduino_opta/stm32h747xx/m4
)
set(arduino_portenta_h7_m4_DEPRECATED
    arduino_portenta_h7/stm32h747xx/m4
)
set(arduino_portenta_h7_m7_DEPRECATED
    arduino_portenta_h7/stm32h747xx/m7
)
set(arty_a7_arm_designstart_m1_DEPRECATED
    arty_a7/designstart_fpga_cortex_m1
)
set(arty_a7_arm_designstart_m3_DEPRECATED
    arty_a7/designstart_fpga_cortex_m3
)
set(atsamc21n_xpro_DEPRECATED
    samc21n_xpro
)
set(atsamd20_xpro_DEPRECATED
    samd20_xpro
)
set(atsamd21_xpro_DEPRECATED
    samd21_xpro
)
set(atsame54_xpro_DEPRECATED
    same54_xpro
)
set(atsaml21_xpro_DEPRECATED
    saml21_xpro
)
set(atsamr21_xpro_DEPRECATED
    samr21_xpro
)
set(atsamr34_xpro_DEPRECATED
    samr34_xpro
)
set(b_u585i_iot02a_ns_DEPRECATED
    b_u585i_iot02a/stm32u585xx/ns
)
set(bcm958402m2_a72_DEPRECATED
    bcm958402m2/bcm58402/a72
)
set(bcm958402m2_m7_DEPRECATED
    bcm958402m2/bcm58402/m7
)
set(bl5340_dvk_cpuapp_DEPRECATED
    bl5340_dvk/nrf5340/cpuapp
)
set(bl5340_dvk_cpuapp_ns_DEPRECATED
    bl5340_dvk/nrf5340/cpuapp/ns
)
set(bl5340_dvk_cpunet_DEPRECATED
    bl5340_dvk/nrf5340/cpunet
)
set(blueclover_plt_demo_v2_nrf52832_DEPRECATED
    blueclover_plt_demo_v2
)
set(circuitdojo_feather_nrf9160_DEPRECATED
    circuitdojo_feather
)
set(circuitdojo_feather_nrf9160_ns_DEPRECATED
    circuitdojo_feather/nrf9160/ns
)
set(colibri_imx7d_m4_DEPRECATED
    colibri_imx7d/mcimx7d/m4
)
set(cy8ckit_062_ble_m0_DEPRECATED
    cy8ckit_062_ble/cy8c6347/m0
)
set(cy8ckit_062_ble_m4_DEPRECATED
    cy8ckit_062_ble/cy8c6347/m4
)
set(cy8ckit_062_wifi_bt_m0_DEPRECATED
    cy8ckit_062_wifi_bt/cy8c6247/m0
)
set(cy8ckit_062_wifi_bt_m4_DEPRECATED
    cy8ckit_062_wifi_bt/cy8c6247/m4
)
set(cy8ckit_062s4_m4_DEPRECATED
    cy8ckit_062s4
)
set(ebyte_e73_tbb_nrf52832_DEPRECATED
    ebyte_e73_tbb
)
set(efm32pg_stk3402a_DEPRECATED
    efm32pg_stk3402a/efm32pg12b500f1024gl125
)
set(efm32pg_stk3402a_jg_DEPRECATED
    efm32pg_stk3402a/efm32jg12b500f1024gl125
)
set(efr32_radio_brd4104a_DEPRECATED
    efr32_radio/efr32bg13p632f512gm48
)
set(efr32_radio_brd4161a_DEPRECATED
    efr32_radio/efr32mg12p432f1024gl125
)
set(efr32_radio_brd4170a_DEPRECATED
    efr32_radio/efr32mg12p433f1024gm68
)
set(efr32_radio_brd4180a_DEPRECATED
    efr32_radio/efr32mg21a020f1024im32
)
set(efr32_radio_brd4187c_DEPRECATED
    efr32_radio/efr32mg24b220f1536im48
)
set(efr32_radio_brd4250b_DEPRECATED
    efr32_radio/efr32fg1p133f256gm48
)
set(efr32_radio_brd4255a_DEPRECATED
    efr32_radio/efr32fg13p233f512gm48
)
set(em_starterkit_DEPRECATED
    em_starterkit/emsk_em9d
)
set(em_starterkit_em11d_DEPRECATED
    em_starterkit@2.3/emsk_em11d
)
set(em_starterkit_em7d_DEPRECATED
    em_starterkit@2.3/emsk_em7d
)
set(em_starterkit_em7d_v22_DEPRECATED
    em_starterkit@2.2/emsk_em7d
)
set(emsdp_DEPRECATED
    emsdp/emsdp_em11d
)
set(emsdp_em4_DEPRECATED
    emsdp/emsdp_em4
)
set(emsdp_em5d_DEPRECATED
    emsdp/emsdp_em5d
)
set(emsdp_em6_DEPRECATED
    emsdp/emsdp_em6
)
set(emsdp_em7d_DEPRECATED
    emsdp/emsdp_em7d
)
set(emsdp_em7d_esp_DEPRECATED
    emsdp/emsdp_em7d_esp
)
set(emsdp_em9d_DEPRECATED
    emsdp/emsdp_em9d
)
set(esp32_DEPRECATED
    esp32_devkitc_wrover/esp32/procpu
)
set(esp32_devkitc_wroom_DEPRECATED
    esp32_devkitc_wroom/esp32/procpu
)
set(esp32_devkitc_wroom_appcpu_DEPRECATED
    esp32_devkitc_wroom/esp32/appcpu
)
set(esp32_devkitc_wrover_DEPRECATED
    esp32_devkitc_wrover/esp32/procpu
)
set(esp32_devkitc_wrover_appcpu_DEPRECATED
    esp32_devkitc_wrover/esp32/appcpu
)
set(esp32_ethernet_kit_DEPRECATED
    esp32_ethernet_kit/esp32/procpu
)
set(esp32c3_luatos_core_usb_DEPRECATED
    esp32c3_luatos_core/esp32c3/usb
)
set(esp32s3_devkitm_DEPRECATED
    esp32s3_devkitm/esp32s3/procpu
)
set(esp32s3_devkitm_appcpu_DEPRECATED
    esp32s3_devkitm/esp32s3/appcpu
)
set(esp32s3_luatos_core_DEPRECATED
    esp32s3_luatos_core/esp32s3/procpu
)
set(esp32s3_luatos_core_usb_DEPRECATED
    esp32s3_luatos_core/esp32s3/procpu/usb
)
set(esp_wrover_kit_DEPRECATED
    esp_wrover_kit/esp32/procpu
)
set(fvp_base_revc_2xaemv8a_smp_ns_DEPRECATED
    fvp_base_revc_2xaemv8a/fvp_base_revc_2xaemv8a/smp/ns
)
set(fvp_baser_aemv8r_DEPRECATED
    fvp_baser_aemv8r/fvp_aemv8r_aarch64
)
set(fvp_baser_aemv8r_aarch32_DEPRECATED
    fvp_baser_aemv8r/fvp_aemv8r_aarch32
)
set(fvp_baser_aemv8r_aarch32_smp_DEPRECATED
    fvp_baser_aemv8r/fvp_aemv8r_aarch32/smp
)
set(fvp_baser_aemv8r_smp_DEPRECATED
    fvp_baser_aemv8r/fvp_aemv8r_aarch64/smp
)
set(heltec_wifi_lora32_v2_DEPRECATED
    heltec_wifi_lora32_v2/esp32/procpu
)
set(heltec_wireless_stick_lite_v3_DEPRECATED
    heltec_wireless_stick_lite_v3/esp32s3/procpu
)
set(hexiwear_k64_DEPRECATED
    hexiwear/mk64f12
)
set(hexiwear_kw40z_DEPRECATED
    hexiwear/mkw40z4
)
set(hifive1_revb_DEPRECATED
    hifive1@B
)
set(hsdk_2cores_DEPRECATED
    hsdk/arc_hsdk/2cores
)
set(intel_adsp_ace15_mtpm_DEPRECATED
    intel_adsp/ace15_mtpm
)
set(intel_adsp_ace20_lnl_DEPRECATED
    intel_adsp/ace20_lnl
)
set(intel_adsp_cavs25_DEPRECATED
    intel_adsp/cavs25
)
set(intel_adsp_cavs25_tgph_DEPRECATED
    intel_adsp/cavs25/tgph
)
set(intel_ehl_crb_sbl_DEPRECATED
    intel_ehl_crb/elkhart_lake/sbl
)
set(kincony_kc868_a32_DEPRECATED
    kincony_kc868_a32/esp32/procpu
)
set(longan_nano_lite_DEPRECATED
    longan_nano/gd32vf103/lite
)
set(lpcxpresso54114_m0_DEPRECATED
    lpcxpresso54114/lpc54114/m0
)
set(lpcxpresso54114_m4_DEPRECATED
    lpcxpresso54114/lpc54114/m4
)
set(lpcxpresso55s69_cpu0_DEPRECATED
    lpcxpresso55s69/lpc55s69/cpu0
)
set(lpcxpresso55s69_cpu1_DEPRECATED
    lpcxpresso55s69/lpc55s69/cpu1
)
set(lpcxpresso55s69_ns_DEPRECATED
    lpcxpresso55s69/lpc55s69/cpu0/ns
)
set(m5stack_atoms3_DEPRECATED
    m5stack_atoms3/esp32s3/procpu
)
set(m5stack_atoms3_lite_DEPRECATED
    m5stack_atoms3_lite/esp32s3/procpu
)
set(m5stack_core2_DEPRECATED
    m5stack_core2/esp32/procpu
)
set(m5stack_stamps3_DEPRECATED
    m5stack_stamps3/esp32s3/procpu
)
set(m5stickc_plus_DEPRECATED
    m5stickc_plus/esp32/procpu
)
set(mimx8mm_evk_DEPRECATED
    imx8mm_evk/mimx8mm6/m4
)
set(mimx8mm_evk_a53_DEPRECATED
    imx8mm_evk/mimx8mm6/a53
)
set(mimx8mm_evk_a53_smp_DEPRECATED
    imx8mm_evk/mimx8mm6/a53/smp
)
set(mimx8mm_phyboard_polis_DEPRECATED
    mimx8mm_phyboard_polis/mimx8mm6/m4
)
set(mimx8mn_evk_a53_DEPRECATED
    imx8mn_evk/mimx8mn6/a53
)
set(mimx8mn_evk_a53_smp_DEPRECATED
    imx8mn_evk/mimx8mn6/a53/smp
)
set(mimx8mp_evk_a53_DEPRECATED
    imx8mp_evk/mimx8ml8/a53
)
set(mimx8mp_evk_a53_smp_DEPRECATED
    imx8mp_evk/mimx8ml8/a53/smp
)
set(mimx8mp_evk_ddr_DEPRECATED
    imx8mp_evk/mimx8ml8/m7/ddr
)
set(mimx8mp_evk_itcm_DEPRECATED
    imx8mp_evk/mimx8ml8/m7
)
set(mimx8mp_phyboard_pollux_DEPRECATED
    mimx8mp_phyboard_pollux/mimx8ml8/m7
)
set(mimx8mq_evk_cm4_DEPRECATED
    imx8mq_evk/mimx8mq6/m4
)
set(mimx93_evk_a55_DEPRECATED
    imx93_evk/mimx9352/a55
)
set(mimxrt1050_evk_qspi_DEPRECATED
    mimxrt1050_evk@qspi
)
set(mimxrt1060_evk_hyperflash_DEPRECATED
    mimxrt1060_evk@hyperflash
)
set(mimxrt1160_evk_cm4_DEPRECATED
    mimxrt1160_evk/mimxrt1166/cm4
)
set(mimxrt1160_evk_cm7_DEPRECATED
    mimxrt1160_evk/mimxrt1166/cm7
)
set(mimxrt1170_evk_cm4_DEPRECATED
    mimxrt1170_evk@A/mimxrt1176/cm4
)
set(mimxrt1170_evk_cm7_DEPRECATED
    mimxrt1170_evk@A/mimxrt1176/cm7
)
set(mimxrt1170_evkb_cm4_DEPRECATED
    mimxrt1170_evk@B/mimxrt1176/cm4
)
set(mimxrt1170_evkb_cm7_DEPRECATED
    mimxrt1170_evk@B/mimxrt1176/cm7
)
set(mimxrt595_evk_cm33_DEPRECATED
    mimxrt595_evk/mimxrt595s/cm33
)
set(mimxrt685_evk_cm33_DEPRECATED
    mimxrt685_evk
)
set(mps2_an385_DEPRECATED
    mps2/an385
)
set(mps2_an521_DEPRECATED
    mps2/an521/cpu0
)
set(mps2_an521_ns_DEPRECATED
    mps2/an521/cpu0/ns
)
set(mps2_an521_remote_DEPRECATED
    mps2/an521/cpu1
)
set(mps3_an547_DEPRECATED
    mps3
)
set(mps3_an547_ns_DEPRECATED
    mps3/an547/ns
)
set(nrf21540dk_nrf52840_DEPRECATED
    nrf21540dk
)
set(nrf51dk_nrf51422_DEPRECATED
    nrf51dk
)
set(nrf51dongle_nrf51422_DEPRECATED
    nrf51dongle
)
set(nrf52833dk_nrf52820_DEPRECATED
    nrf52833dk/nrf52820
)
set(nrf52833dk_nrf52833_DEPRECATED
    nrf52833dk/nrf52833
)
set(nrf52840dk_nrf52811_DEPRECATED
    nrf52840dk/nrf52811
)
set(nrf52840dk_nrf52840_DEPRECATED
    nrf52840dk/nrf52840
)
set(nrf52840dongle_nrf52840_DEPRECATED
    nrf52840dongle
)
set(nrf52dk_nrf52805_DEPRECATED
    nrf52dk/nrf52805
)
set(nrf52dk_nrf52810_DEPRECATED
    nrf52dk/nrf52810
)
set(nrf52dk_nrf52832_DEPRECATED
    nrf52dk/nrf52832
)
set(nrf5340_audio_dk_nrf5340_cpuapp_DEPRECATED
    nrf5340_audio_dk/nrf5340/cpuapp
)
set(nrf5340_audio_dk_nrf5340_cpuapp_ns_DEPRECATED
    nrf5340_audio_dk/nrf5340/cpuapp/ns
)
set(nrf5340_audio_dk_nrf5340_cpunet_DEPRECATED
    nrf5340_audio_dk/nrf5340/cpunet
)
set(nrf5340bsim_nrf5340_cpuapp_DEPRECATED
    nrf5340bsim/nrf5340/cpuapp
)
set(nrf5340bsim_nrf5340_cpunet_DEPRECATED
    nrf5340bsim/nrf5340/cpunet
)
set(nrf5340dk_nrf5340_cpuapp_DEPRECATED
    nrf5340dk/nrf5340/cpuapp
)
set(nrf5340dk_nrf5340_cpuapp_ns_DEPRECATED
    nrf5340dk/nrf5340/cpuapp/ns
)
set(nrf5340dk_nrf5340_cpunet_DEPRECATED
    nrf5340dk/nrf5340/cpunet
)
set(nrf54l15pdk_nrf54l15_cpuapp_DEPRECATED
    nrf54l15pdk/nrf54l15/cpuapp
)
set(nrf9131ek_nrf9131_DEPRECATED
    nrf9131ek
)
set(nrf9131ek_nrf9131_ns_DEPRECATED
    nrf9131ek/nrf9131/ns
)
set(nrf9151dk_nrf9151_DEPRECATED
    nrf9151dk
)
set(nrf9151dk_nrf9151_ns_DEPRECATED
    nrf9151dk/nrf9151/ns
)
set(nrf9160_innblue21_DEPRECATED
    innblue21
)
set(nrf9160_innblue21_ns_DEPRECATED
    innblue21/nrf9160/ns
)
set(nrf9160_innblue22_DEPRECATED
    innblue22
)
set(nrf9160_innblue22_ns_DEPRECATED
    innblue22/nrf9160/ns
)
set(nrf9160dk_nrf52840_DEPRECATED
    nrf9160dk/nrf52840
)
set(nrf9160dk_nrf9160_DEPRECATED
    nrf9160dk/nrf9160
)
set(nrf9160dk_nrf9160_ns_DEPRECATED
    nrf9160dk/nrf9160/ns
)
set(nrf9161dk_nrf9161_DEPRECATED
    nrf9161dk
)
set(nrf9161dk_nrf9161_ns_DEPRECATED
    nrf9161dk/nrf9161/ns
)
set(nsim_em_DEPRECATED
    nsim/nsim_em
)
set(nsim_em11d_DEPRECATED
    nsim/nsim_em11d
)
set(nsim_em7d_v22_DEPRECATED
    nsim/nsim_em7d_v22
)
set(nsim_hs_DEPRECATED
    nsim/nsim_hs
)
set(nsim_hs3x_hostlink_DEPRECATED
    nsim/nsim_hs/hostlink
)
set(nsim_hs5x_DEPRECATED
    nsim/nsim_hs5x
)
set(nsim_hs5x_smp_DEPRECATED
    nsim/nsim_hs5x/smp
)
set(nsim_hs5x_smp_12cores_DEPRECATED
    nsim/nsim_hs5x/smp/12cores
)
set(nsim_hs6x_DEPRECATED
    nsim/nsim_hs6x
)
set(nsim_hs6x_smp_DEPRECATED
    nsim/nsim_hs6x/smp
)
set(nsim_hs6x_smp_12cores_DEPRECATED
    nsim/nsim_hs6x/smp/12cores
)
set(nsim_hs_flash_xip_DEPRECATED
    nsim/nsim_hs/flash_xip
)
set(nsim_hs_mpuv6_DEPRECATED
    nsim/nsim_hs/mpuv6
)
set(nsim_hs_smp_DEPRECATED
    nsim/nsim_hs/smp
)
set(nsim_hs_sram_DEPRECATED
    nsim/nsim_hs/sram
)
set(nsim_sem_DEPRECATED
    nsim/nsim_sem
)
set(nsim_sem_mpu_stack_guard_DEPRECATED
    nsim/nsim_sem/mpu_stack_guard
)
set(nsim_vpx5_DEPRECATED
    nsim/nsim_vpx5
)
set(nucleo_h745zi_q_m4_DEPRECATED
    nucleo_h745zi_q/stm32h745xx/m4
)
set(nucleo_h745zi_q_m7_DEPRECATED
    nucleo_h745zi_q/stm32h745xx/m7
)
set(nucleo_l452re_p_DEPRECATED
    nucleo_l452re/stm32l452xx/p
)
set(nucleo_l552ze_q_ns_DEPRECATED
    nucleo_l552ze_q/stm32l552xx/ns
)
set(nuvoton_pfm_m487_DEPRECATED
    numaker_pfm_m487
)
set(nxp_adsp_imx8_DEPRECATED
    imx8qm_mek/mimx8qm6/adsp
)
set(nxp_adsp_imx8m_DEPRECATED
    imx8mp_evk/mimx8ml8/adsp
)
set(nxp_adsp_imx8ulp_DEPRECATED
    imx8ulp_evk/imx8ulp/adsp
)
set(nxp_adsp_imx8x_DEPRECATED
    imx8qxp_mek/mimx8qx6/adsp
)
set(nxp_adsp_rt595_DEPRECATED
    mimxrt595_evk/mimxrt595s/f1
)
set(nxp_ls1046ardb_DEPRECATED
    ls1046ardb
)
set(nxp_ls1046ardb_smp_2cores_DEPRECATED
    ls1046ardb/ls1046a/smp
)
set(nxp_ls1046ardb_smp_4cores_DEPRECATED
    ls1046ardb/ls1046a/smp/4cores
)
set(odroid_go_DEPRECATED
    odroid_go/esp32/procpu
)
set(olimex_esp32_evb_DEPRECATED
    olimex_esp32_evb/esp32/procpu
)
set(pan1783_evb_cpuapp_DEPRECATED
    pan1783_evb/nrf5340/cpuapp
)
set(pan1783_evb_cpunet_DEPRECATED
    pan1783_evb/nrf5340/cpunet
)
set(pan1783a_evb_cpuapp_DEPRECATED
    pan1783a_evb/nrf5340/cpuapp
)
set(pan1783a_evb_cpunet_DEPRECATED
    pan1783a_evb/nrf5340/cpunet
)
set(pan1783a_pa_evb_cpuapp_DEPRECATED
    pan1783a_pa_evb/nrf5340/cpuapp
)
set(pan1783a_pa_evb_cpunet_DEPRECATED
    pan1783a_pa_evb/nrf5340/cpunet
)
set(phycore_am62x_a53_DEPRECATED
    phycore_am62x/am6234/a53
)
set(pico_pi_m4_DEPRECATED
    pico_pi/mcimx7d/m4
)
set(qemu_arc_em_DEPRECATED
    qemu_arc/qemu_arc_em
)
set(qemu_arc_hs_DEPRECATED
    qemu_arc/qemu_arc_hs
)
set(qemu_arc_hs5x_DEPRECATED
    qemu_arc/qemu_arc_hs5x
)
set(qemu_arc_hs6x_DEPRECATED
    qemu_arc/qemu_arc_hs6x
)
set(qemu_arc_hs_xip_DEPRECATED
    qemu_arc/qemu_arc_hs/xip
)
set(qemu_cortex_a53_smp_DEPRECATED
    qemu_cortex_a53/qemu_cortex_a53/smp
)
set(qemu_cortex_a53_xip_DEPRECATED
    qemu_cortex_a53/qemu_cortex_a53/xip
)
set(qemu_malta_be_DEPRECATED
    qemu_malta/qemu_malta/be
)
set(qemu_riscv32_smp_DEPRECATED
    qemu_riscv32/qemu_virt_riscv32/smp
)
set(qemu_riscv64_smp_DEPRECATED
    qemu_riscv64/qemu_virt_riscv64/smp
)
set(qemu_x86_64_nokpti_DEPRECATED
    qemu_x86_64/atom/nokpti
)
set(qemu_x86_nokpti_DEPRECATED
    qemu_x86/atom/nokpti
)
set(qemu_x86_nommu_DEPRECATED
    qemu_x86/atom/nommu
)
set(qemu_x86_nopae_DEPRECATED
    qemu_x86/atom/nopae
)
set(qemu_x86_virt_DEPRECATED
    qemu_x86/atom/virt
)
set(qemu_x86_xip_DEPRECATED
    qemu_x86/atom/xip
)
set(qemu_xtensa_mmu_DEPRECATED
    qemu_xtensa/dc233c/mmu
)
set(rak4631_nrf52840_DEPRECATED
    rak4631
)
set(rak5010_nrf52840_DEPRECATED
    rak5010
)
set(raytac_mdbt50q_db_33_nrf52833_DEPRECATED
    raytac_mdbt50q_db_33
)
set(raytac_mdbt50q_db_40_nrf52840_DEPRECATED
    raytac_mdbt50q_db_40
)
set(raytac_mdbt53_db_40_nrf5340_cpuapp_DEPRECATED
    raytac_mdbt53_db_40/nrf5340/cpuapp
)
set(raytac_mdbt53_db_40_nrf5340_cpuapp_ns_DEPRECATED
    raytac_mdbt53_db_40/nrf5340/cpuapp/ns
)
set(raytac_mdbt53_db_40_nrf5340_cpunet_DEPRECATED
    raytac_mdbt53_db_40/nrf5340/cpunet
)
set(raytac_mdbt53v_db_40_nrf5340_cpuapp_DEPRECATED
    raytac_mdbt53v_db_40/nrf5340/cpuapp
)
set(raytac_mdbt53v_db_40_nrf5340_cpuapp_ns_DEPRECATED
    raytac_mdbt53v_db_40/nrf5340/cpuapp/ns
)
set(raytac_mdbt53v_db_40_nrf5340_cpunet_DEPRECATED
    raytac_mdbt53v_db_40/nrf5340/cpunet
)
set(rcar_h3_salvatorx_cr7_DEPRECATED
    rcar_salvator_x/r8a77951/r7
)
set(rcar_h3ulcb_ca57_DEPRECATED
    rcar_h3ulcb/r8a77951/a57
)
set(rcar_h3ulcb_cr7_DEPRECATED
    rcar_h3ulcb/r8a77951/r7
)
set(rcar_salvator_xs_m3_DEPRECATED
    rcar_salvator_xs
)
set(rcar_spider_cr52_DEPRECATED
    rcar_spider_s4
)
set(reel_board_v2_DEPRECATED
    reel_board@2
)
set(roc_rk3568_pc_smp_DEPRECATED
    roc_rk3568_pc/rk3568/smp
)
set(rpi_pico_w_DEPRECATED
    rpi_pico/rp2040/w
)
set(rv32m1_vega_ri5cy_DEPRECATED
    rv32m1_vega/openisa_rv32m1/ri5cy
)
set(rv32m1_vega_zero_riscy_DEPRECATED
    rv32m1_vega/openisa_rv32m1/zero_riscy
)
set(s32z270dc2_rtu0_r52_DEPRECATED
    s32z2xxdc2/s32z270/rtu0
)
set(s32z270dc2_rtu1_r52_DEPRECATED
    s32z2xxdc2/s32z270/rtu1
)
set(sam_e70_xplained_DEPRECATED
    sam_e70_xplained/same70q21
)
set(sam_e70b_xplained_DEPRECATED
    sam_e70_xplained/same70q21b
)
set(sam_v71_xult_DEPRECATED
    sam_v71_xult/samv71q21
)
set(sam_v71b_xult_DEPRECATED
    sam_v71_xult/samv71q21b
)
set(sparkfun_thing_plus_nrf9160_DEPRECATED
    sparkfun_thing_plus
)
set(sparkfun_thing_plus_nrf9160_ns_DEPRECATED
    sparkfun_thing_plus/nrf9160/ns
)
set(stm32_min_dev_black_DEPRECATED
    stm32_min_dev@black
)
set(stm32_min_dev_blue_DEPRECATED
    stm32_min_dev@blue
)
set(stm32h747i_disco_m4_DEPRECATED
    stm32h747i_disco/stm32h747xx/m4
)
set(stm32h747i_disco_m7_DEPRECATED
    stm32h747i_disco/stm32h747xx/m7
)
set(stm32l562e_dk_ns_DEPRECATED
    stm32l562e_dk/stm32l562xx/ns
)
set(tdk_robokit1_DEPRECATED
    robokit1
)
set(thingy52_nrf52832_DEPRECATED
    thingy52
)
set(thingy53_nrf5340_cpuapp_DEPRECATED
    thingy53/nrf5340/cpuapp
)
set(thingy53_nrf5340_cpuapp_ns_DEPRECATED
    thingy53/nrf5340/cpuapp/ns
)
set(thingy53_nrf5340_cpunet_DEPRECATED
    thingy53/nrf5340/cpunet
)
set(ubx_bmd300eval_nrf52832_DEPRECATED
    ubx_bmd300eval
)
set(ubx_bmd330eval_nrf52810_DEPRECATED
    ubx_bmd330eval
)
set(ubx_bmd340eval_nrf52840_DEPRECATED
    ubx_bmd340eval
)
set(ubx_bmd345eval_nrf52840_DEPRECATED
    ubx_bmd345eval
)
set(ubx_bmd360eval_nrf52811_DEPRECATED
    ubx_bmd360eval
)
set(ubx_bmd380eval_nrf52840_DEPRECATED
    ubx_bmd380eval
)
set(ubx_evkannab1_nrf52832_DEPRECATED
    ubx_evkannab1
)
set(ubx_evkninab1_nrf52832_DEPRECATED
    ubx_evkninab1
)
set(ubx_evkninab3_nrf52840_DEPRECATED
    ubx_evkninab3
)
set(ubx_evkninab4_nrf52833_DEPRECATED
    ubx_evkninab4
)
set(udoo_neo_full_m4_DEPRECATED
    udoo_neo_full/mcimx6x/m4
)
set(v2m_musca_b1_ns_DEPRECATED
    v2m_musca_b1/musca_b1/ns
)
set(v2m_musca_s1_ns_DEPRECATED
    v2m_musca_s1/musca_s1/ns
)
set(verdin_imx8mp_m7_ddr_DEPRECATED
    verdin_imx8mp/mimx8ml8/m7/ddr
)
set(verdin_imx8mp_m7_itcm_DEPRECATED
    verdin_imx8mp/mimx8ml8/m7
)
set(vmu_rt1170_DEPRECATED
    vmu_rt1170/mimxrt1176/cm7
)
set(warp7_m4_DEPRECATED
    warp7/mcimx7d/m4
)
set(we_ophelia1ev_nrf52805_DEPRECATED
    we_ophelia1ev
)
set(we_proteus2ev_nrf52832_DEPRECATED
    we_proteus2ev
)
set(we_proteus3ev_nrf52840_DEPRECATED
    we_proteus3ev
)
set(xenvm_gicv3_DEPRECATED
    xenvm/xenvm/gicv3
)
set(xiao_ble_sense_DEPRECATED
    xiao_ble/nrf52840/sense
)
set(xiao_esp32s3_DEPRECATED
    xiao_esp32s3/esp32s3/procpu
)
set(yd_esp32_DEPRECATED
    yd_esp32/esp32/procpu
)
