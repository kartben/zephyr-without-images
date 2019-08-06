#!/usr/bin/env python3
#
# Copyright (c) 2017 Intel Corporation
#
# SPDX-License-Identifier: Apache-2.0

"""
Generation script for syscall_macros.h

Except for a single transitive include, this header is empty.  The
generated code that used to live here is now emitted by
gen_syscalls.py directly.

This script has no inputs, and emits the generated header to stdout.
"""

import sys

sys.stdout.write(
    "/* Auto-generated by gen_syscall_header.py, do not edit! */\n\n")
sys.stdout.write("#ifndef GEN_SYSCALL_H\n#define GEN_SYSCALL_H\n\n")
sys.stdout.write("#include <syscall.h>\n")

sys.stdout.write("#endif /* GEN_SYSCALL_H */\n")
