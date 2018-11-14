#!/usr/bin/env python3
#
# Copyright (c) 2017 Intel Corporation
# SPDX-License-Identifier: Apache-2.0
#

import argparse
import struct
import sys
import os
from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection

ISR_FLAG_DIRECT = (1 << 0)

# The below few hardware independent magic numbers represent various
# levels of interrupts in a multi-level interrupt system.
# 0x000000FF - represents the 1st level (i.e. the interrupts
#              that directly go to the processor).
# 0x0000FF00 - represents the 2nd level (i.e. the interrupts funnel
#              into 1 line which then goes into the 1st level)
# 0x00FF0000 - represents the 3rd level (i.e. the interrupts funnel
#              into 1 line which then goes into the 2nd level)
FIRST_LVL_INTERRUPTS = 0x000000FF
SECND_LVL_INTERRUPTS = 0x0000FF00
THIRD_LVL_INTERRUPTS = 0x00FF0000

def debug(text):
    if args.debug:
        sys.stdout.write(os.path.basename(sys.argv[0]) + ": " + text + "\n")

def error(text):
    sys.stderr.write(os.path.basename(sys.argv[0]) + ": " + text + "\n")
    raise Exception()

def endian_prefix():
    if args.big_endian:
        return ">"
    else:
        return "<"

def read_intlist(intlist_path):
    """read a binary file containing the contents of the kernel's .intList
    section. This is an instance of a header created by
    include/linker/intlist.ld:

     struct {
       u32_t num_vectors;       <- typically CONFIG_NUM_IRQS
       struct _isr_list isrs[]; <- Usually of smaller size than num_vectors
    }

    Followed by instances of struct _isr_list created by IRQ_CONNECT()
    calls:

    struct _isr_list {
        /** IRQ line number */
        s32_t irq;
        /** Flags for this IRQ, see ISR_FLAG_* definitions */
        s32_t flags;
        /** ISR to call */
        void *func;
        /** Parameter for non-direct IRQs */
        void *param;
    };
    """

    intlist = {}

    prefix = endian_prefix()

    intlist_header_fmt = prefix + "II"
    intlist_entry_fmt = prefix + "iiII"

    with open(intlist_path, "rb") as fp:
        intdata = fp.read()

    header_sz = struct.calcsize(intlist_header_fmt)
    header = struct.unpack_from(intlist_header_fmt, intdata, 0)
    intdata = intdata[header_sz:]

    debug(str(header))

    intlist["num_vectors"]    = header[0]
    intlist["offset"]         = header[1]

    intlist["interrupts"] = [i for i in
            struct.iter_unpack(intlist_entry_fmt, intdata)]

    debug("Configured interrupt routing")
    debug("handler    irq flags param")
    debug("--------------------------")

    for irq in intlist["interrupts"]:
        debug("{0:<10} {1:<3} {2:<3}   {3}".format(
            hex(irq[2]), irq[0], irq[1], hex(irq[3])))

    return intlist


def parse_args():
    global args

    parser = argparse.ArgumentParser(description = __doc__,
            formatter_class = argparse.RawDescriptionHelpFormatter)

    parser.add_argument("-e", "--big-endian", action="store_true",
            help="Target encodes data in big-endian format (little endian is "
                 "the default)")
    parser.add_argument("-d", "--debug", action="store_true",
            help="Print additional debugging information")
    parser.add_argument("-o", "--output-source", required=True,
            help="Output source file")
    parser.add_argument("-k", "--kernel", required=True,
            help="Zephyr kernel image")
    parser.add_argument("-s", "--sw-isr-table", action="store_true",
            help="Generate SW ISR table")
    parser.add_argument("-V", "--vector-table", action="store_true",
            help="Generate vector table")
    parser.add_argument("-i", "--intlist", required=True,
            help="Zephyr intlist binary for intList extraction")

    args = parser.parse_args()

source_header = """
/* AUTO-GENERATED by gen_isr_tables.py, do not edit! */

#include <toolchain.h>
#include <linker/sections.h>
#include <sw_isr_table.h>
#include <arch/cpu.h>

#if defined(CONFIG_GEN_SW_ISR_TABLE) && defined(CONFIG_GEN_IRQ_VECTOR_TABLE)
#define ISR_WRAPPER ((u32_t)&_isr_wrapper)
#else
#define ISR_WRAPPER NULL
#endif

"""

def write_source_file(fp, vt, swt, intlist):
    fp.write(source_header)

    nv = intlist["num_vectors"]

    if vt:
        fp.write("u32_t __irq_vector_table _irq_vector_table[%d] = {\n" % nv)
        for i in range(nv):
            fp.write("\t{},\n".format(vt[i]))
        fp.write("};\n")

    if not swt:
        return

    fp.write("struct _isr_table_entry __sw_isr_table _sw_isr_table[%d] = {\n"
            % nv)
    for i in range(nv):
        param, func = swt[i]
        if type(func) is int:
            func_as_string = "{0:#x}".format(func)
        else:
            func_as_string = func

        fp.write("\t{{(void *){0:#x}, (void *){1}}},\n".format(param, func_as_string))
    fp.write("};\n")

def get_symbols(obj):
    for section in obj.iter_sections():
        if isinstance(section, SymbolTableSection):
            return {sym.name: sym.entry.st_value
                    for sym in section.iter_symbols()}

    error("Could not find symbol table")

def getindex(irq, irq_aggregator_pos):
    for indx, val in enumerate(irq_aggregator_pos):
        if irq == irq_aggregator_pos[indx]:
            return indx
    error("The index %d has no match. Recheck interrupt configuration" % indx)

def main():
    parse_args()

    with open(args.kernel, "rb") as fp:
        kernel = ELFFile(fp)
        syms = get_symbols(kernel)

    if "CONFIG_MULTI_LEVEL_INTERRUPTS" in syms:
        if "CONFIG_2ND_LEVEL_INTERRUPTS" in syms:
            if "CONFIG_NUM_2ND_LEVEL_AGGREGATORS" in syms:
                num_aggregators = syms["CONFIG_NUM_2ND_LEVEL_AGGREGATORS"]
                list_2nd_lvl_offsets = []
                for i in range(num_aggregators):
                    offset_str = 'CONFIG_2ND_LVL_INTR_' + str(i).zfill(2) + '_OFFSET'
                    if offset_str in syms:
                        list_2nd_lvl_offsets.append(syms[offset_str])

            debug(str(list_2nd_lvl_offsets))

            if "CONFIG_3RD_LEVEL_INTERRUPTS" in syms:
                if "CONFIG_NUM_3RD_LEVEL_AGGREGATORS" in syms:
                    num_aggregators = syms["CONFIG_NUM_3RD_LEVEL_AGGREGATORS"]
                    list_3rd_lvl_offsets = []
                    for i in range(num_aggregators):
                        offset_str = 'CONFIG_3RD_LVL_INTR_' + str(i).zfill(2) + '_OFFSET'
                        if offset_str in syms:
                            list_3rd_lvl_offsets.append(syms[offset_str])

                debug(str(list_3rd_lvl_offsets))

    intlist = read_intlist(args.intlist)
    nvec = intlist["num_vectors"]
    offset = intlist["offset"]
    prefix = endian_prefix()

    spurious_handler = "&_irq_spurious"
    sw_irq_handler   = "ISR_WRAPPER"

    debug('offset is ' + str(offset))
    debug('num_vectors is ' + str(nvec))

    # Set default entries in both tables
    if args.sw_isr_table:
        # All vectors just jump to the common sw_irq_handler. If some entries
        # are used for direct interrupts, they will be replaced later.
        if args.vector_table:
            vt = [sw_irq_handler for i in range(nvec)]
        else:
            vt = None
        # Default to spurious interrupt handler. Configured interrupts
        # will replace these entries.
        swt = [(0, spurious_handler) for i in range(nvec)]
    else:
        if args.vector_table:
            vt = [spurious_handler for i in range(nvec)]
        else:
            error("one or both of -s or -V needs to be specified on command line")
        swt = None

    for irq, flags, func, param in intlist["interrupts"]:
        if (flags & ISR_FLAG_DIRECT):
            if (param != 0):
                error("Direct irq %d declared, but has non-NULL parameter"
                        % irq)
            vt[irq - offset] = func
        else:
            # Regular interrupt
            if not swt:
                error("Regular Interrupt %d declared with parameter 0x%x "
                        "but no SW ISR_TABLE in use"
                        % (irq, param))

            if not "CONFIG_MULTI_LEVEL_INTERRUPTS" in syms:
                swt[irq - offset] = (param, func)
            else:
                # Figure out third level interrupt position
                debug('IRQ = ' + hex(irq))
                irq3 = (irq & THIRD_LVL_INTERRUPTS) >> 16
                if irq3:
                    irq_parent = (irq & SECND_LVL_INTERRUPTS) >> 8
                    list_index = getindex(irq_parent, list_3rd_lvl_offsets)
                    irq3_baseoffset = syms["CONFIG_3RD_LVL_ISR_TBL_OFFSET"]
                    irq3_pos = irq3_baseoffset + 32*list_index + irq3 - 1
                    debug('IRQ_Indx = ' + str(irq3))
                    debug('IRQ_Pos  = ' + str(irq3_pos))
                    swt[irq3_pos - offset] = (param, func)

                # Figure out second level interrupt position
                if not irq3:
                    irq2 = (irq & SECND_LVL_INTERRUPTS) >> 8
                    if irq2:
                        irq_parent = (irq & FIRST_LVL_INTERRUPTS)
                        list_index = getindex(irq_parent, list_2nd_lvl_offsets)
                        irq2_baseoffset = syms["CONFIG_2ND_LVL_ISR_TBL_OFFSET"]
                        irq2_pos = irq2_baseoffset + 32*list_index + irq2 - 1
                        debug('IRQ_Indx = ' + str(irq2))
                        debug('IRQ_Pos  = ' + str(irq2_pos))
                        swt[irq2_pos - offset] = (param, func)

                # Figure out first level interrupt position
                if not irq3 and not irq2:
                    irq1 = (irq & FIRST_LVL_INTERRUPTS)
                    debug('IRQ_Indx = ' + str(irq1))
                    debug('IRQ_Pos  = ' + str(irq1))
                    swt[irq1 - offset] = (param, func)

    with open(args.output_source, "w") as fp:
        write_source_file(fp, vt, swt, intlist)

if __name__ == "__main__":
    main()

