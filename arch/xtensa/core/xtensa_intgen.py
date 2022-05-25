#!/usr/bin/env python3
import re
import fileinput

# Pass an Xtensa core-isa.h file on stdin or the command line, emits a
# C file on output containing optimized interrupt dispatch routines.

# FIXME: looking at the assembly generated by the ESP-32 toolchain,
# this isn't as optimal as I'd hoped.  the individual cases are tested
# using a L32R + BNONE (i.e. a full mask test) instead of a BBSI, and
# the handlers are being invoked with CALL8 instead of CALL4,
# inexplicably wasting four words of stack.  Maybe this should be
# emitting assembly instead.  Wouldn't be much more complicated and
# would share all the same structure.

# My manual count of instructions says that a linear search becomes
# faster on average when there are three or fewer bits to test.  Would
# be four, if the compiler would generate BBSI instructions.
MAX_TESTS = 3

ints_by_lvl = {}

# print() wrapper that automatically handles indentation levels
cindent = 0
def cprint(s):
    global cindent
    if s.endswith(":"):
        print(s)
        return
    if s.find("}") >= 0:
        cindent -= 1
    s = cindent*"\t" + s
    print(s)
    if s.find("{") >= 0:
        cindent += 1

def emit_int_handler(ints):
    if len(ints) <= MAX_TESTS:
        for i in ints:
            # FIXME: a little work could allow us to extract the
            # handler pointer and argument as literals, saving a few
            # instructions and avoiding the need to link in
            # _sw_isr_table entirely.
            cprint("if (mask & BIT(%d)) {" % i)
            cprint("mask = BIT(%d);" % i)
            cprint("irq = %d;" % i)
            cprint("goto handle_irq;")
            cprint("}")
    else:
        half = int(len(ints)/2)

        m = 0
        for i in ints[0:half]:
            m |= 1 << i
        cprint("if (mask & " + ("0x%x" % (m)) + ") {")
        emit_int_handler(ints[0:half])
        cprint("} else {")
        emit_int_handler(ints[half:])
        cprint("}")

########################################################################

# Annoyingly need to join lines and remove #-marked annotations.  Some
# versions of the preprocessor (ahem, esp32 SDK) like to include
# newlines in the output where the original expressions are expanded
# from 100% single line macros.  Slurp it into a single string and
# parse via whitespace.
blob = ""
for l in fileinput.input():
    l = l if l.find("#") < 0 else l[0:l.find("#")]
    blob += l.rstrip() + " "

for match in re.finditer(r'__xtensa_int_level_magic__\s+(\d+)\s+(\d+)', blob):
    irq = int(match.group(1))
    lvl = int(match.group(2))

    if lvl not in ints_by_lvl:
        ints_by_lvl[lvl] = []

    ints_by_lvl[lvl].append(irq)

cprint("/*")
cprint(" * THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT.")
cprint(" *")
cprint(" * Functions here are designed to produce efficient code to")
cprint(" * search an Xtensa bitmask of interrupts, inspecting only those bits")
cprint(" * declared to be associated with a given interrupt level.  Each")
cprint(" * dispatcher will handle exactly one flagged interrupt, in numerical")
cprint(" * order (low bits first) and will return a mask of that bit that can")
cprint(" * then be cleared by the calling code.  Unrecognized bits for the")
cprint(" * level will invoke an error handler.")
cprint(" */")
cprint("")

# Re-include the core-isa header and be sure our definitions match, for sanity
cprint("#include <xtensa/config/core-isa.h>")
cprint("#include <zephyr/sys/util.h>")
cprint("#include <zephyr/sw_isr_table.h>")
cprint("")
for l in ints_by_lvl:
    for i in ints_by_lvl[l]:
        v = "XCHAL_INT" + str(i) + "_LEVEL"
        cprint("#if !defined(" + v + ") || " + str(v) + " != " + str(l))
        cprint("#error core-isa.h interrupt level does not match dispatcher!")
        cprint("#endif")
cprint("")

# Populate empty levels just for sanity.  The second-to-last interrupt
# level (usually "debug") typically doesn't have any associated
# vectors, but we don't have any way to know that a-prioi.
max = 0
for lvl in ints_by_lvl:
    if lvl > max:
        max = lvl

for lvl in range(0, max+1):
    if not lvl in ints_by_lvl:
        ints_by_lvl[lvl] = []

# Emit the handlers
for lvl in ints_by_lvl:
    cprint("static inline int _xtensa_handle_one_int" + str(lvl) + "(unsigned int mask)")
    cprint("{")

    if not ints_by_lvl[lvl]:
        cprint("return 0;")
        cprint("}")
        continue

    cprint("int irq;")
    print("")

    emit_int_handler(sorted(ints_by_lvl[lvl]))

    cprint("return 0;")
    cprint("handle_irq:")
    cprint("_sw_isr_table[irq].isr(_sw_isr_table[irq].arg);")
    cprint("return mask;")
    cprint("}")
    cprint("")
