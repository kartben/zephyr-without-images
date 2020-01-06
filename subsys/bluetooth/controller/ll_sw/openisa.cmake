# SPDX-License-Identifier: Apache-2.0

if(CONFIG_BT_LL_SW_SPLIT)
  zephyr_library_sources(
    ll_sw/openisa/lll/lll.c
    )
  if(CONFIG_BT_BROADCASTER)
    zephyr_library_sources(
      ll_sw/openisa/lll/lll_adv.c
      )
  endif()
  if(CONFIG_BT_OBSERVER)
    zephyr_library_sources(
      ll_sw/openisa/lll/lll_scan.c
      )
  endif()
  if(CONFIG_BT_CONN)
    zephyr_library_sources(
      ll_sw/openisa/lll/lll_clock.c
      ll_sw/openisa/lll/lll_conn.c
    )
    if(CONFIG_BT_PERIPHERAL)
      zephyr_library_sources(
        ll_sw/openisa/lll/lll_slave.c
      )
    endif()
    if(CONFIG_BT_CENTRAL)
      zephyr_library_sources(
        ll_sw/openisa/lll/lll_master.c
      )
    endif()
  endif()
    zephyr_library_include_directories(
      ll_sw/openisa/lll
    )
  zephyr_library_sources_ifdef(
    CONFIG_BT_CTLR_DTM
    ll_sw/openisa/lll/lll_test.c
  )
  zephyr_library_sources_ifdef(
    CONFIG_BT_CTLR_PROFILE_ISR
    ll_sw/openisa/lll/lll_test.c
  )
endif()

zephyr_library_sources_ifdef(
  CONFIG_SOC_OPENISA_RV32M1_RISCV32
  ll_sw/openisa/hal/RV32M1/cntr.c
  ll_sw/openisa/hal/RV32M1/ecb.c
  ll_sw/openisa/hal/RV32M1/radio/radio.c
  ll_sw/openisa/hal/RV32M1/mayfly.c
  ll_sw/openisa/hal/RV32M1/ticker.c
  )

if(CONFIG_SOC_OPENISA_RV32M1_RISCV32)
  zephyr_library_include_directories(
    ll_sw/openisa
    hci/openisa
    )
endif()
