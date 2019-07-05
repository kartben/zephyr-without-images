# Copyright (c) 2019 Intel Corp.
# SPDX-License-Identifier: Apache-2.0

#
# XXX: When using the Intel toolchain, cmake doesn't recognize .S files
# automatically, and I can't be bothered to figure out how to fix this.
#

set_property(SOURCE intel64/locore.S PROPERTY LANGUAGE ASM)

zephyr_library_sources(
  intel64/locore.S
  intel64/irq_manage.c
  intel64/thread.c
)
