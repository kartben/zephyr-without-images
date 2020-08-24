#!/usr/bin/env python3

# Copyright (c) 2019 Nordic Semiconductor ASA
# Copyright (c) 2019 Linaro Limited
# SPDX-License-Identifier: BSD-3-Clause

# This script is similar to gen_defines.py, but is for the legacy
# macro syntax used in e.g. Zephyr 2.2.
#
# It should be considered frozen code. New macro-related functionality
# should be done by modifying the macro namespaces managed by
# gen_defines.py.

import argparse
import os
import pathlib
import pickle

# Set this to True to generated deprecated macro warnings. Since this
# entire file is deprecated and must be explicitly enabled with
# CONFIG_LEGACY_DEVICETREE_MACROS, this was turned off by default
# shortly before the v2.3 release (this was the least impactful way to
# do it, which resulted in the smallest and least-risky patch).
DEPRECATION_MESSAGES = False

def main():
    global header_file
    global flash_area_num

    args = parse_args()

    with open(args.edt_pickle, 'rb') as f:
        edt = pickle.load(f)

    header_file = open(args.header_out, "w", encoding="utf-8")
    flash_area_num = 0

    write_top_comment(edt)

    for node in sorted(edt.nodes, key=lambda node: node.dep_ordinal):
        write_node_comment(node)

        # Flash partition nodes are handled as a special case. It
        # would be nicer if we had bindings that would let us
        # avoid that, but this will do for now.
        if node.name.startswith("partition@"):
            write_flash_partition(node, flash_area_num)
            flash_area_num += 1

        if node.enabled and node.matching_compat:
            write_regs(node)
            write_irqs(node)
            write_props(node)
            write_clocks(node)
            write_spi_dev(node)
            write_bus(node)
            write_existence_flags(node)

    out_comment("Compatibles appearing on enabled nodes")
    for compat in sorted(edt.compat2enabled):
        #define DT_COMPAT_<COMPAT> 1
        out(f"COMPAT_{str2ident(compat)}", 1)

    # Definitions derived from /chosen nodes
    write_addr_size(edt, "zephyr,ccm", "CCM")
    write_addr_size(edt, "zephyr,dtcm", "DTCM")
    write_addr_size(edt, "zephyr,ipc_shm", "IPC_SHM")
    write_flash(edt)

    header_file.close()


def parse_args():
    # Returns parsed command-line arguments

    parser = argparse.ArgumentParser()
    parser.add_argument("--edt-pickle", required=True,
                        help="pickle file containing EDT object")
    parser.add_argument("--header-out", required=True,
                        help="path to write header to")

    return parser.parse_args()


def write_top_comment(edt):
    # Writes an overview comment with misc. info at the top of the header and
    # configuration file

    s = f"""\
Generated by gen_legacy_defines.py

DTS input file:
  {edt.dts_path}

Directories with bindings:
  {", ".join(map(relativize, edt.bindings_dirs))}

Nodes in dependency order (ordinal and path):
"""

    for scc in edt.scc_order:
        if len(scc) > 1:
            err("cycle in devicetree involving "
                + ", ".join(node.path for node in scc))
        s += f"  {scc[0].dep_ordinal:<3} {scc[0].path}\n"

    s += """
Definitions derived from these nodes in dependency order are next,
followed by tree-wide information (active compatibles, chosen nodes,
etc.).
"""

    out_comment(s, blank_before=False)


def write_node_comment(node):
    # Writes a comment describing 'node' to the header and configuration file

    s = f"""\
Devicetree node:
  {node.path}
"""
    if node.matching_compat:
        if node.binding_path:
            s += f"""
Binding (compatible = {node.matching_compat}):
  {relativize(node.binding_path)}
"""
        else:
            s += f"""
Binding (compatible = {node.matching_compat}):
  No yaml (bindings inferred from properties)
"""
    else:
        s += "\nNo matching binding.\n"

    s += f"\nDependency Ordinal: {node.dep_ordinal}\n"

    if node.depends_on:
        s += "\nRequires:\n"
        for dep in node.depends_on:
            s += f"  {dep.dep_ordinal:<3} {dep.path}\n"

    if node.required_by:
        s += "\nSupports:\n"
        for req in node.required_by:
            s += f"  {req.dep_ordinal:<3} {req.path}\n"

    if node.description:
        # Indent description by two spaces
        s += "\nDescription:\n" + \
            "\n".join("  " + line for line in
                      node.description.splitlines()) + \
            "\n"

    if not node.enabled:
        s += "\nNode is disabled.\n"

    out_comment(s)


def relativize(path):
    # If 'path' is within $ZEPHYR_BASE, returns it relative to $ZEPHYR_BASE,
    # with a "$ZEPHYR_BASE/..." hint at the start of the string. Otherwise,
    # returns 'path' unchanged.

    zbase = os.getenv("ZEPHYR_BASE")
    if zbase is None:
        return path

    try:
        return str("$ZEPHYR_BASE" / pathlib.Path(path).relative_to(zbase))
    except ValueError:
        # Not within ZEPHYR_BASE
        return path


def write_regs(node):
    # Writes address/size output for the registers in the node's 'reg' property

    def write_reg(reg, base_ident, val):
        # Drop '_0' from the identifier if there's a single register, for
        # backwards compatibility
        if len(reg.node.regs) > 1:
            ident = f"{base_ident}_{reg.node.regs.index(reg)}"
        else:
            ident = base_ident

        out_node(node, ident, val,
                 # Name alias from 'reg-names = ...'
                 f"{str2ident(reg.name)}_{base_ident}" if reg.name else None)

    for reg in node.regs:
        write_reg(reg, "BASE_ADDRESS", hex(reg.addr))
        if reg.size:
            write_reg(reg, "SIZE", reg.size)


def write_props(node):
    # Writes any properties defined in the "properties" section of the binding
    # for the node

    for prop in node.props.values():
        if not should_write(prop):
            continue

        if prop.description is not None:
            out_comment(prop.description, blank_before=False)

        ident = str2ident(prop.name)

        if prop.type == "boolean":
            out_node(node, ident, 1 if prop.val else 0)
        elif prop.type == "string":
            out_node_s(node, ident, prop.val)
        elif prop.type == "int":
            out_node(node, ident, prop.val)
        elif prop.type == "array":
            for i, val in enumerate(prop.val):
                out_node(node, f"{ident}_{i}", val)
            out_node_init(node, ident, prop.val)
        elif prop.type == "string-array":
            for i, val in enumerate(prop.val):
                out_node_s(node, f"{ident}_{i}", val)
        elif prop.type == "uint8-array":
            out_node_init(node, ident,
                          [f"0x{b:02x}" for b in prop.val])
        else:  # prop.type == "phandle-array"
            write_phandle_val_list(prop)

        # Generate DT_..._ENUM if there's an 'enum:' key in the binding
        if prop.enum_index is not None:
            out_node(node, ident + "_ENUM", prop.enum_index)


def should_write(prop):
    # write_props() helper. Returns True if output should be generated for
    # 'prop'.

    # Skip #size-cell and other property starting with #. Also skip mapping
    # properties like 'gpio-map'.
    if prop.name[0] == "#" or prop.name.endswith("-map"):
        return False

    # See write_clocks()
    if prop.name == "clocks":
        return False

    # For these, Property.val becomes an edtlib.Node, a list of edtlib.Nodes,
    # or None. Nothing is generated for them at the moment.
    if prop.type in {"phandle", "phandles", "path", "compound"}:
        return False

    # Skip properties that we handle elsewhere
    if prop.name in {
        "reg", "compatible", "status", "interrupts",
        "interrupt-controller", "gpio-controller"
    }:
        return False

    return True


def write_bus(node):
    # Generate bus-related #defines

    if not node.bus_node:
        return

    if node.bus_node.label is None:
        err(f"missing 'label' property on bus node {node.bus_node!r}")

    # #define DT_<DEV-IDENT>_BUS_NAME <BUS-LABEL>
    out_node_s(node, "BUS_NAME", str2ident(node.bus_node.label), "Macro is deprecated")

    for compat in node.compats:
        # #define DT_<COMPAT>_BUS_<BUS-TYPE> 1
        out(f"{str2ident(compat)}_BUS_{str2ident(node.on_bus)}", 1)


def write_existence_flags(node):
    # Generate #defines of the form
    #
    #   #define DT_INST_<instance no.>_<compatible string> 1
    #
    # for enabled nodes. These are flags for which devices exist.

    for compat in node.compats:
        instance_no = node.edt.compat2enabled[compat].index(node)
        out(f"INST_{instance_no}_{str2ident(compat)}", 1)


def node_ident(node):
    # Returns an identifier for 'node'. Used e.g. when building macro names.

    # TODO: Handle PWM on STM
    # TODO: Better document the rules of how we generate things

    ident = ""

    if node.bus_node:
        if node.bus_node.unit_addr is not None:
            ident += "{}_{:X}_".format(
                str2ident(node.bus_node.matching_compat), node.bus_node.unit_addr)
        else:
            ident += str2ident(node.bus_node.matching_compat)

    ident += f"{str2ident(node.matching_compat)}_"

    if node.unit_addr is not None:
        ident += f"{node.unit_addr:X}"
    elif node.parent.unit_addr is not None:
        ident += f"{node.parent.unit_addr:X}_{str2ident(node.name)}"
    else:
        # This is a bit of a hack
        ident += str2ident(node.name)

    return ident


def node_aliases(node):
    # Returns a list of aliases for 'node', used e.g. when building macro names

    return node_path_aliases(node) + node_instance_aliases(node)


def node_path_aliases(node):
    # Returns a list of aliases for 'node', based on the aliases registered for
    # it in the /aliases node. Used e.g. when building macro names.

    if node.matching_compat is None:
        return []

    compat_s = str2ident(node.matching_compat)

    aliases = []
    for alias in node.aliases:
        aliases.append(f"ALIAS_{str2ident(alias)}")
        # TODO: See if we can remove or deprecate this form
        aliases.append(f"{compat_s}_{str2ident(alias)}")

    return aliases


def node_instance_aliases(node):
    # Returns a list of aliases for 'node', based on the compatible string and
    # the instance number (each node with a particular compatible gets its own
    # instance number, starting from zero).
    #
    # This is a list since a node can have multiple 'compatible' strings, each
    # with their own instance number.

    res = []
    for compat in node.compats:
        instance_no = node.edt.compat2enabled[compat].index(node)
        res.append(f"INST_{instance_no}_{str2ident(compat)}")
    return res


def write_addr_size(edt, prop_name, prefix):
    # Writes <prefix>_BASE_ADDRESS and <prefix>_SIZE for the node pointed at by
    # the /chosen property named 'prop_name', if it exists

    node = edt.chosen_node(prop_name)
    if not node:
        return

    if not node.regs:
        err("missing 'reg' property in node pointed at by "
            f"/chosen/{prop_name} ({node!r})")

    out_comment(f"/chosen/{prop_name} ({node.path})")
    out(f"{prefix}_BASE_ADDRESS", hex(node.regs[0].addr))
    out(f"{prefix}_SIZE", node.regs[0].size//1024)


def write_flash(edt):
    # Writes chosen and tree-wide flash-related output

    write_flash_node(edt)
    write_code_partition(edt)

    if flash_area_num != 0:
        out_comment("Number of flash partitions")
        out("FLASH_AREA_NUM", flash_area_num)


def write_flash_node(edt):
    # Writes output for the top-level flash node pointed at by
    # zephyr,flash in /chosen

    node = edt.chosen_node("zephyr,flash")

    out_comment(f"/chosen/zephyr,flash ({node.path if node else 'missing'})")

    if not node:
        # No flash node. Write dummy values.
        out("FLASH_BASE_ADDRESS", 0)
        out("FLASH_SIZE", 0)
        return

    if len(node.regs) != 1:
        err("expected zephyr,flash to have a single register, has "
            f"{len(node.regs)}")

    if node.on_bus == "spi" and len(node.bus_node.regs) == 2:
        reg = node.bus_node.regs[1]  # QSPI flash
    else:
        reg = node.regs[0]

    out("FLASH_BASE_ADDRESS", hex(reg.addr))
    if reg.size:
        out("FLASH_SIZE", reg.size//1024)

    if "erase-block-size" in node.props:
        out("FLASH_ERASE_BLOCK_SIZE", node.props["erase-block-size"].val)

    if "write-block-size" in node.props:
        out("FLASH_WRITE_BLOCK_SIZE", node.props["write-block-size"].val)


def write_code_partition(edt):
    # Writes output for the node pointed at by zephyr,code-partition in /chosen

    node = edt.chosen_node("zephyr,code-partition")

    out_comment("/chosen/zephyr,code-partition "
                f"({node.path if node else 'missing'})")

    if not node:
        # No code partition. Write dummy values.
        out("CODE_PARTITION_OFFSET", 0)
        out("CODE_PARTITION_SIZE", 0)
        return

    if not node.regs:
        err(f"missing 'regs' property on {node!r}")

    out("CODE_PARTITION_OFFSET", node.regs[0].addr)
    out("CODE_PARTITION_SIZE", node.regs[0].size)


def write_flash_partition(partition_node, index):
    if partition_node.label is None:
        err(f"missing 'label' property on {partition_node!r}")

    # Generate label-based identifiers
    write_flash_partition_prefix(
        "FLASH_AREA_" + str2ident(partition_node.label), partition_node, index)

    # Generate index-based identifiers
    write_flash_partition_prefix(f"FLASH_AREA_{index}", partition_node, index)


def write_flash_partition_prefix(prefix, partition_node, index):
    # write_flash_partition() helper. Generates identifiers starting with
    # 'prefix'.

    out(f"{prefix}_ID", index)

    out(f"{prefix}_READ_ONLY", 1 if partition_node.read_only else 0)

    for i, reg in enumerate(partition_node.regs):
        # Also add aliases that point to the first sector (TODO: get rid of the
        # aliases?)
        out(f"{prefix}_OFFSET_{i}", reg.addr,
            aliases=[f"{prefix}_OFFSET"] if i == 0 else [])
        out(f"{prefix}_SIZE_{i}", reg.size,
            aliases=[f"{prefix}_SIZE"] if i == 0 else [])

    controller = partition_node.flash_controller
    if controller.label is not None:
        out_s(f"{prefix}_DEV", controller.label)


def write_irqs(node):
    # Writes IRQ num and data for the interrupts in the node's 'interrupt'
    # property

    def irq_name_alias(irq, cell_name):
        if not irq.name:
            return None

        alias = f"IRQ_{str2ident(irq.name)}"
        if cell_name != "irq":
            alias += f"_{str2ident(cell_name)}"
        return alias

    def map_arm_gic_irq_type(irq, irq_num):
        # Maps ARM GIC IRQ (type)+(index) combo to linear IRQ number
        if "type" not in irq.data:
            err(f"Expected binding for {irq.controller!r} to have 'type' in "
                "interrupt-cells")
        irq_type = irq.data["type"]

        if irq_type == 0:  # GIC_SPI
            return irq_num + 32
        if irq_type == 1:  # GIC_PPI
            return irq_num + 16
        err(f"Invalid interrupt type specified for {irq!r}")

    def encode_zephyr_multi_level_irq(irq, irq_num):
        # See doc/reference/kernel/other/interrupts.rst for details
        # on how this encoding works

        irq_ctrl = irq.controller
        # Look for interrupt controller parent until we have none
        while irq_ctrl.interrupts:
            irq_num = (irq_num + 1) << 8
            if "irq" not in irq_ctrl.interrupts[0].data:
                err(f"Expected binding for {irq_ctrl!r} to have 'irq' in "
                    "interrupt-cells")
            irq_num |= irq_ctrl.interrupts[0].data["irq"]
            irq_ctrl = irq_ctrl.interrupts[0].controller
        return irq_num

    for irq_i, irq in enumerate(node.interrupts):
        for cell_name, cell_value in irq.data.items():
            ident = f"IRQ_{irq_i}"
            if cell_name == "irq":
                if "arm,gic" in irq.controller.compats:
                    cell_value = map_arm_gic_irq_type(irq, cell_value)
                cell_value = encode_zephyr_multi_level_irq(irq, cell_value)
            else:
                ident += f"_{str2ident(cell_name)}"

            out_node(node, ident, cell_value,
                     name_alias=irq_name_alias(irq, cell_name))


def write_spi_dev(node):
    # Writes SPI device GPIO chip select data if there is any

    cs_gpio = node.spi_cs_gpio
    if cs_gpio is not None:
        write_phandle_val_list_entry(node, cs_gpio, None, "CS_GPIOS")


def write_phandle_val_list(prop):
    # Writes output for a phandle/value list, e.g.
    #
    #    pwms = <&pwm-ctrl-1 10 20
    #            &pwm-ctrl-2 30 40>;
    #
    # prop:
    #   phandle/value Property instance.
    #
    #   If only one entry appears in 'prop' (the example above has two), the
    #   generated identifier won't get a '_0' suffix, and the '_COUNT' and
    #   group initializer are skipped too.
    #
    # The base identifier is derived from the property name. For example, 'pwms = ...'
    # generates output like this:
    #
    #   #define <node prefix>_PWMS_CONTROLLER_0 "PWM_0"  (name taken from 'label = ...')
    #   #define <node prefix>_PWMS_CHANNEL_0 123         (name taken from *-cells in binding)
    #   #define <node prefix>_PWMS_0 {"PWM_0", 123}
    #   #define <node prefix>_PWMS_CONTROLLER_1 "PWM_1"
    #   #define <node prefix>_PWMS_CHANNEL_1 456
    #   #define <node prefix>_PWMS_1 {"PWM_1", 456}
    #   #define <node prefix>_PWMS_COUNT 2
    #   #define <node prefix>_PWMS {<node prefix>_PWMS_0, <node prefix>_PWMS_1}
    #   ...

    # pwms -> PWMS
    # foo-gpios -> FOO_GPIOS
    ident = str2ident(prop.name)

    initializer_vals = []
    for i, entry in enumerate(prop.val):
        initializer_vals.append(write_phandle_val_list_entry(
            prop.node, entry, i if len(prop.val) > 1 else None, ident))

    if len(prop.val) > 1:
        out_node(prop.node, ident + "_COUNT", len(initializer_vals))
        out_node_init(prop.node, ident, initializer_vals)


def write_phandle_val_list_entry(node, entry, i, ident):
    # write_phandle_val_list() helper. We could get rid of it if it wasn't for
    # write_spi_dev(). Adds 'i' as an index to identifiers unless it's None.
    #
    # 'entry' is an edtlib.ControllerAndData instance.
    #
    # Returns the identifier for the macro that provides the
    # initializer for the entire entry.

    initializer_vals = []
    if entry.controller.label is not None:
        ctrl_ident = ident + "_CONTROLLER"  # e.g. PWMS_CONTROLLER
        if entry.name:
            name_alias = f"{str2ident(entry.name)}_{ctrl_ident}"
        else:
            name_alias = None
        # Ugly backwards compatibility hack. Only add the index if there's
        # more than one entry.
        if i is not None:
            ctrl_ident += f"_{i}"
        initializer_vals.append(quote_str(entry.controller.label))
        out_node_s(node, ctrl_ident, entry.controller.label, name_alias)

    for cell, val in entry.data.items():
        cell_ident = f"{ident}_{str2ident(cell)}"  # e.g. PWMS_CHANNEL
        if entry.name:
            # From e.g. 'pwm-names = ...'
            name_alias = f"{str2ident(entry.name)}_{cell_ident}"
        else:
            name_alias = None
        # Backwards compatibility (see above)
        if i is not None:
            cell_ident += f"_{i}"
        out_node(node, cell_ident, val, name_alias)

    initializer_vals += entry.data.values()

    initializer_ident = ident
    if entry.name:
        name_alias = f"{initializer_ident}_{str2ident(entry.name)}"
    else:
        name_alias = None
    if i is not None:
        initializer_ident += f"_{i}"
    return out_node_init(node, initializer_ident, initializer_vals, name_alias)


def write_clocks(node):
    # Writes clock information.
    #
    # Most of this ought to be handled in write_props(), but the identifiers
    # that get generated for 'clocks' are inconsistent with the with other
    # 'phandle-array' properties.
    #
    # See https://github.com/zephyrproject-rtos/zephyr/pull/19327#issuecomment-534081845.

    if "clocks" not in node.props:
        return

    for clock_i, clock in enumerate(node.props["clocks"].val):
        controller = clock.controller

        if controller.label is not None:
            out_node_s(node, "CLOCK_CONTROLLER", controller.label)

        for name, val in clock.data.items():
            if clock_i == 0:
                clk_name_alias = "CLOCK_" + str2ident(name)
            else:
                clk_name_alias = None

            out_node(node, f"CLOCK_{str2ident(name)}_{clock_i}", val,
                     name_alias=clk_name_alias)

        if "fixed-clock" not in controller.compats:
            continue

        if "clock-frequency" not in controller.props:
            err(f"{controller!r} is a 'fixed-clock' but lacks a "
                "'clock-frequency' property")

        out_node(node, "CLOCKS_CLOCK_FREQUENCY",
                 controller.props["clock-frequency"].val)


def str2ident(s):
    # Converts 's' to a form suitable for (part of) an identifier

    return s.replace("-", "_") \
            .replace(",", "_") \
            .replace("@", "_") \
            .replace("/", "_") \
            .replace(".", "_") \
            .replace("+", "PLUS") \
            .upper()


def out_node(node, ident, val, name_alias=None, deprecation_msg=None):
    # Writes a
    #
    #   <node prefix>_<ident> = <val>
    #
    # assignment, along with a set of
    #
    #   <node alias>_<ident>
    #
    # aliases, for each path/instance alias for the node. If 'name_alias' (a
    # string) is passed, then these additional aliases are generated:
    #
    #   <node prefix>_<name alias>
    #   <node alias>_<name alias> (for each node alias)
    #
    # 'name_alias' is used for reg-names and the like.
    #
    # If a 'deprecation_msg' string is passed, the generated identifiers will
    # generate a warning if used, via __WARN(<deprecation_msg>)).
    #
    # Returns the identifier used for the macro that provides the value
    # for 'ident' within 'node', e.g. DT_MFG_MODEL_CTL_GPIOS_PIN.

    node_prefix = node_ident(node)

    aliases = [f"{alias}_{ident}" for alias in node_aliases(node)]
    if name_alias is not None:
        aliases.append(f"{node_prefix}_{name_alias}")
        aliases += [f"{alias}_{name_alias}" for alias in node_aliases(node)]

    return out(f"{node_prefix}_{ident}", val, aliases, deprecation_msg)


def out_node_s(node, ident, s, name_alias=None, deprecation_msg=None):
    # Like out_node(), but emits 's' as a string literal
    #
    # Returns the generated macro name for 'ident'.

    return out_node(node, ident, quote_str(s), name_alias, deprecation_msg)


def out_node_init(node, ident, elms, name_alias=None, deprecation_msg=None):
    # Like out_node(), but generates an {e1, e2, ...} initializer with the
    # elements in the iterable 'elms'.
    #
    # Returns the generated macro name for 'ident'.

    return out_node(node, ident, "{" + ", ".join(map(str, elms)) + "}",
                    name_alias, deprecation_msg)


def out_s(ident, val):
    # Like out(), but puts quotes around 'val' and escapes any double
    # quotes and backslashes within it
    #
    # Returns the generated macro name for 'ident'.

    return out(ident, quote_str(val))


def out(ident, val, aliases=(), deprecation_msg=None):
    # Writes '#define <ident> <val>' to the header and '<ident>=<val>' to the
    # the configuration file.
    #
    # Also writes any aliases listed in 'aliases' (an iterable). For the
    # header, these look like '#define <alias> <ident>'. For the configuration
    # file, the value is just repeated as '<alias>=<val>' for each alias.
    #
    # See out_node() for the meaning of 'deprecation_msg'.
    #
    # Returns the generated macro name for 'ident'.

    out_define(ident, val, deprecation_msg, header_file)
    primary_ident = f"DT_{ident}"

    d_msg = deprecation_msg

    for alias in aliases:
        if alias != ident:
            if alias.startswith("INST_"):
                deprecation_msg = "Macro is deprecated"

            out_define(alias, "DT_" + ident, deprecation_msg, header_file)

            deprecation_msg = d_msg

    return primary_ident


def out_define(ident, val, deprecation_msg, out_file):
    # out() helper for writing a #define. See out_node() for the meaning of
    # 'deprecation_msg'.

    s = f"#define DT_{ident:40}"

    if DEPRECATION_MESSAGES and deprecation_msg:
        s += fr' __WARN("{deprecation_msg}")'
    s += f" {val}"
    print(s, file=out_file)


def out_comment(s, blank_before=True):
    # Writes 's' as a comment to the header and configuration file. 's' is
    # allowed to have multiple lines. blank_before=True adds a blank line
    # before the comment.

    if blank_before:
        print(file=header_file)

    if "\n" in s:
        # Format multi-line comments like
        #
        #   /*
        #    * first line
        #    * second line
        #    *
        #    * empty line before this line
        #    */
        res = ["/*"]
        for line in s.splitlines():
            # Avoid an extra space after '*' for empty lines. They turn red in
            # Vim if space error checking is on, which is annoying.
            res.append(" *" if not line.strip() else " * " + line)
        res.append(" */")
        print("\n".join(res), file=header_file)
    else:
        # Format single-line comments like
        #
        #   /* foo bar */
        print("/* " + s + " */", file=header_file)


def escape(s):
    # Backslash-escapes any double quotes and backslashes in 's'

    # \ must be escaped before " to avoid double escaping
    return s.replace("\\", "\\\\").replace('"', '\\"')


def quote_str(s):
    # Puts quotes around 's' and escapes any double quotes and
    # backslashes within it

    return f'"{escape(s)}"'


def err(s):
    raise Exception(s)


if __name__ == "__main__":
    main()
