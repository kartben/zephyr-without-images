#!/usr/bin/env python3
#
# Copyright (c) 2017 Intel Corporation
#
# SPDX-License-Identifier: Apache-2.0

import sys
import re
import argparse
import os
import json

table_template = """/* auto-generated by gen_syscalls.py, don't edit */

/* Weak handler functions that get replaced by the real ones unless a system
 * call is not implemented due to kernel configuration.
 */
%s

const _k_syscall_handler_t _k_syscall_table[K_SYSCALL_LIMIT] = {
\t%s
};
"""

list_template = """
/* auto-generated by gen_syscalls.py, don't edit */
#ifndef _ZEPHYR_SYSCALL_LIST_H_
#define _ZEPHYR_SYSCALL_LIST_H_

%s

#ifndef _ASMLANGUAGE

#include <zephyr/types.h>

#ifdef __cplusplus
extern "C" {
#endif

%s

#ifdef __cplusplus
}
#endif

#endif /* _ASMLANGUAGE */

#endif /* _ZEPHYR_SYSCALL_LIST_H_ */
"""

syscall_template = """
/* auto-generated by gen_syscalls.py, don't edit */

#ifndef _ASMLANGUAGE

#include <syscall_list.h>
#include <syscall_macros.h>

#ifdef __cplusplus
extern "C" {
#endif

%s

#ifdef __cplusplus
}
#endif

#endif
"""

handler_template = """
extern u32_t %s(u32_t arg1, u32_t arg2, u32_t arg3,
                u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);
"""

weak_template = """
__weak ALIAS_OF(handler_no_syscall)
u32_t %s(u32_t arg1, u32_t arg2, u32_t arg3,
         u32_t arg4, u32_t arg5, u32_t arg6, void *ssf);
"""


typename_regex = re.compile(r'(.*?)([A-Za-z0-9_]+)$')


class SyscallParseException(Exception):
    pass


def typename_split(item):
    if "[" in item:
        raise SyscallParseException(
            "Please pass arrays to syscalls as pointers, unable to process '%s'" %
            item)

    if "(" in item:
        raise SyscallParseException(
            "Please use typedefs for function pointers")

    mo = typename_regex.match(item)
    if not mo:
        raise SyscallParseException("Malformed system call invocation")

    m = mo.groups()
    return (m[0].strip(), m[1])


def analyze_fn(match_group):
    func, args = match_group

    try:
        if args == "void":
            args = []
        else:
            args = [typename_split(a.strip()) for a in args.split(",")]

        func_type, func_name = typename_split(func)
    except SyscallParseException:
        sys.stderr.write("In declaration of %s\n" % func)
        raise

    sys_id = "K_SYSCALL_" + func_name.upper()

    if func_type == "void":
        suffix = "_VOID"
        is_void = True
    else:
        is_void = False
        if func_type in ["s64_t", "u64_t"]:
            suffix = "_RET64"
        else:
            suffix = ""

    is_void = (func_type == "void")

    # Get the proper system call macro invocation, which depends on the
    # number of arguments, the return type, and whether the implementation
    # is an inline function
    macro = "K_SYSCALL_DECLARE%d%s" % (len(args), suffix)

    # Flatten the argument lists and generate a comma separated list
    # of t0, p0, t1, p1, ... tN, pN as expected by the macros
    flat_args = [i for sublist in args for i in sublist]
    if not is_void:
        flat_args = [func_type] + flat_args
    flat_args = [sys_id, func_name] + flat_args
    argslist = ", ".join(flat_args)

    invocation = "%s(%s);" % (macro, argslist)

    handler = "_handler_" + func_name

    # Entry in _k_syscall_table
    table_entry = "[%s] = %s" % (sys_id, handler)

    return (handler, invocation, sys_id, table_entry)

def parse_args():
    global args
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)

    parser.add_argument("-i", "--json-file", required=True,
                        help="Read syscall information from json file")
    parser.add_argument("-d", "--syscall-dispatch", required=True,
                        help="output C system call dispatch table file")
    parser.add_argument("-l", "--syscall-list", required=True,
                        help="output C system call list header")
    parser.add_argument("-o", "--base-output", required=True,
                        help="Base output directory for syscall macro headers")
    args = parser.parse_args()


def main():
    parse_args()

    with open(args.json_file, 'r') as fd:
        syscalls = json.load(fd)

    invocations = {}
    ids = []
    table_entries = []
    handlers = []

    for match_group, fn in syscalls:
        handler, inv, sys_id, entry = analyze_fn(match_group)

        if fn not in invocations:
            invocations[fn] = []

        invocations[fn].append(inv)
        ids.append(sys_id)
        table_entries.append(entry)
        handlers.append(handler)

    with open(args.syscall_dispatch, "w") as fp:
        table_entries.append("[K_SYSCALL_BAD] = handler_bad_syscall")

        weak_defines = "".join([weak_template % name for name in handlers])

        fp.write(table_template % (weak_defines, ",\n\t".join(table_entries)))

    # Listing header emitted to stdout
    ids.sort()
    ids.extend(["K_SYSCALL_BAD", "K_SYSCALL_LIMIT"])

    ids_as_defines = ""
    for i, item in enumerate(ids):
        ids_as_defines += "#define {} {}\n".format(item, i)

    handler_defines = "".join([handler_template % name for name in handlers])
    with open(args.syscall_list, "w") as fp:
        fp.write(list_template % (ids_as_defines, handler_defines))

    os.makedirs(args.base_output, exist_ok=True)
    for fn, invo_list in invocations.items():
        out_fn = os.path.join(args.base_output, fn)

        header = syscall_template % "\n\n".join(invo_list)

        with open(out_fn, "w") as fp:
            fp.write(header)


if __name__ == "__main__":
    main()
