#!/usr/bin/env python3
#
# Copyright (c) 2024 STMicroelectronics
# SPDX-License-Identifier: Apache-2.0

"""
Script to prepare the LLEXT exports table of a Zephyr ELF

This script performs compile-time processing of the LLEXT exports
table for usage at runtime by the LLEXT subsystem code. The table
is a special section filled with 'llext_const_symbol' structures
generated by the EXPORT_SYMBOL macro.

Currently, the preparatory work consists mostly of sorting the
exports table to allow usage of binary search algorithms at runtime.
If CONFIG_LLEXT_EXPORT_BUILTINS_BY_SLID option is enabled, SLIDs
of all exported functions are also injected in the export table by
this script. (In this case, the preparation process is destructive)
"""

import llext_slidlib

from elftools.elf.elffile import ELFFile
from elftools.elf.sections import Section

import argparse
import logging
import pathlib
import struct
import sys

#!!!!! WARNING !!!!!
#
#These constants MUST be kept in sync with the linker scripts
#and the EXPORT_SYMBOL macro located in 'subsys/llext/llext.h'.
#Otherwise, the LLEXT subsystem will be broken!
#
#!!!!! WARNING !!!!!

LLEXT_EXPORT_TABLE_SECTION_NAME = "llext_const_symbol_area"
LLEXT_EXPORT_NAMES_SECTION_NAME = "llext_exports_strtab"

def _llext_const_symbol_struct(ptr_size: int, endianness: str):
    """
    ptr_size -- Platform pointer size in bytes
    endianness -- Platform endianness ('little'/'big')
    """
    endspec = "<" if endianness == 'little' else ">"
    if ptr_size == 4:
        ptrspec = "I"
    elif ptr_size == 8:
        ptrspec = "Q"

    # struct llext_const_symbol
    # contains just two pointers.
    lcs_spec = endspec + 2 * ptrspec
    return struct.Struct(lcs_spec)

#ELF Shdr flag applied to the export table section, to indicate
#the section has already been prepared by this script. This is
#mostly a security measure to prevent the script from running
#twice on the same ELF file, which can result in catastrophic
#failures if SLID-based linking is enabled (in this case, the
#preparation process is destructive).
#
#This flag is part of the SHF_MASKOS mask, of which all bits
#are "reserved for operating system-specific semantics".
#See: https://refspecs.linuxbase.org/elf/gabi4+/ch4.sheader.html
SHF_LLEXT_PREPARATION_DONE = 0x08000000

class SectionDescriptor():
    """ELF Section descriptor

    This is a wrapper class around pyelftools' "Section" object.
    """
    def __init__(self, elffile, section_name):
        self.name = section_name
        self.section = elffile.get_section_by_name(section_name)
        if not isinstance(self.section, Section):
            raise KeyError(f"section {section_name} not found")

        self.shdr_index = elffile.get_section_index(section_name)
        self.shdr_offset = elffile['e_shoff'] + \
            self.shdr_index * elffile['e_shentsize']
        self.size = self.section['sh_size']
        self.flags = self.section['sh_flags']
        self.offset = self.section['sh_offset']

class LLEXTExptabManipulator():
    """Class used to wrap the LLEXT export table manipulation."""
    def __init__(self, elf_fd, exptab_file_offset, lcs_struct, exports_count):
        self.fd = elf_fd
        self.exports_count = exports_count
        self.base_offset = exptab_file_offset
        self.lcs_struct = lcs_struct

    def _seek_to_sym(self, index):
        self.fd.seek(self.base_offset + index * self.lcs_struct.size)

    def __getitem__(self, index):
        if not isinstance(index, int):
            raise TypeError(f"invalid type {type(index)} for index")

        if index >= self.exports_count:
            raise IndexError(f"index {index} is out of bounds (max {self.exports_count})")

        self._seek_to_sym(index)
        return self.lcs_struct.unpack(self.fd.read(self.lcs_struct.size))

    def __setitem__(self, index, item):
        if not isinstance(index, int):
            raise TypeError(f"invalid type {type(index)} for index")

        if index >= self.exports_count:
            raise IndexError(f"index {index} is out of bounds (max {self.exports_count})")

        (addr_or_slid, sym_addr) = item

        self._seek_to_sym(index)
        self.fd.write(self.lcs_struct.pack(addr_or_slid, sym_addr))

class ZephyrElfExptabPreparator():
    """Prepares the LLEXT export table of a Zephyr ELF.

    Attributes:
        elf_path: path to the Zephyr ELF to prepare
        log: a logging.Logger object
        slid_listing_path: path to the file where SLID listing should be saved
    """
    def __init__(self, elf_path: str, log: logging.Logger, slid_listing_path: str | None):
        self.elf_path = elf_path
        self.elf_fd = open(self.elf_path, 'rb+')
        self.elf = ELFFile(self.elf_fd)
        self.log = log

        # Lazy-open the SLID listing file to ensure it is only created when necessary
        self.slid_listing_path = slid_listing_path
        self.slid_listing_fd = None

    def _prepare_exptab_for_slid_linking(self):
        """
        IMPLEMENTATION NOTES:
          In the linker script, we declare the export names table
          as starting at address 0. Thanks to this, all "pointers"
          to that section are equal to the offset inside the section.
          Also note that symbol names are always NUL-terminated.

          The export table is sorted by SLID in ASCENDING order.
        """
        def read_symbol_name(name_ptr):
            raw_name = b''
            self.elf_fd.seek(self.expstrtab_section.offset + name_ptr)

            c = self.elf_fd.read(1)
            while c != b'\0':
                raw_name += c
                c = self.elf_fd.read(1)

            return raw_name.decode("utf-8")

        #1) Load the export table
        exports_list = []
        for (name_ptr, export_address) in self.exptab_manipulator:
            export_name = read_symbol_name(name_ptr)
            exports_list.append((export_name, export_address))

        #2) Generate the SLID for all exports
        collided = False
        sorted_exptab = dict()
        for export_name, export_addr in exports_list:
            slid = llext_slidlib.generate_slid(export_name, self.ptrsize)

            collision = sorted_exptab.get(slid)
            if collision:
                #Don't abort immediately on collision: if there are others, we want to log them all.
                self.log.error(f"SLID collision: {export_name} and {collision[0]} have the same SLID 0x{slid:X}")
                collided = True
            else:
                sorted_exptab[slid] = (export_name, export_addr)

        if collided:
            return 1

        #3) Sort the export table (order specified above)
        sorted_exptab = dict(sorted(sorted_exptab.items()))

        #4) Write the updated export table to ELF, and dump
        #to SLID listing if requested by caller
        if self.slid_listing_path:
            self.slid_listing_fd = open(self.slid_listing_path, "w")

        def slidlist_write(msg):
            if self.slid_listing_fd:
                self.slid_listing_fd.write(msg + "\n")

        slidlist_write(f"/* SLID listing generated by {__file__} */")
        slidlist_write("//")
        slidlist_write("// This file contains the 'SLID -> name' mapping for all")
        slidlist_write("// symbols exported to LLEXT by this Zephyr executable.")
        slidlist_write("")

        self.log.info("SLID -> export name mapping:")

        i = 0
        for (slid, name_and_symaddr) in sorted_exptab.items():
            slid_as_str = llext_slidlib.format_slid(slid, self.ptrsize)
            msg = f"{slid_as_str} -> {name_and_symaddr[0]}"
            self.log.info(msg)
            slidlist_write(msg)

            self.exptab_manipulator[i] = (slid, name_and_symaddr[1])
            i += 1

        if self.slid_listing_fd:
            self.slid_listing_fd.close()

        return 0

    def _prepare_exptab_for_str_linking(self):
        #TODO: sort the export table by symbol
        #      name to allow binary search too
        #
        # Plan of action:
        #   1) Locate in which section the names are located
        #   2) Load the export table and resolve names
        #   3) Sort the exports by name
        #       WARN: THIS MUST USE THE SAME SORTING RULES
        #       AS LLEXT CODE OR DICHOTOMIC SEARCH WILL BREAK
        #       Using a custom sorting function might be required.
        #   4) Write back the updated export table
        #
        # N.B.: reusing part of the code in _prepare_elf_for_slid_linking
        # might be possible and desireable.
        #
        # As of writing, this function will never be called as this script
        # is only called if CONFIG_LLEXT_EXPORT_BUILTINS_BY_SLID is enabled,
        # which makes _prepare_exptab_for_slid_linking be called instead.
        #
        self.log.warn(f"_prepare_exptab_for_str_linking: do nothing")
        return 0

    def _set_prep_done_shdr_flag(self):
        #Offset and size of the 'sh_flags' member of
        #the Elf_Shdr structure. The offset does not
        #change between ELF32 and ELF64. Size in both
        #is equal to pointer size (4 bytes for ELF32,
        #8 bytes for ELF64).
        SHF_OFFSET = 8
        SHF_SIZE = self.ptrsize

        off = self.exptab_section.shdr_offset + SHF_OFFSET

        #Read existing sh_flags, set the PREPARATION_DONE flag
        #and write back the new value.
        self.elf_fd.seek(off)
        sh_flags = int.from_bytes(self.elf_fd.read(SHF_SIZE), self.endianness)

        sh_flags |= SHF_LLEXT_PREPARATION_DONE

        self.elf_fd.seek(off)
        self.elf_fd.write(int.to_bytes(sh_flags, self.ptrsize, self.endianness))

    def _prepare_inner(self):
        # Locate the export table section
        try:
            self.exptab_section = SectionDescriptor(
                self.elf, LLEXT_EXPORT_TABLE_SECTION_NAME)
        except KeyError as e:
            self.log.error(e.args[0])
            return 1

        # Abort if the ELF has already been processed
        if (self.exptab_section.flags & SHF_LLEXT_PREPARATION_DONE) != 0:
            self.log.warning("exptab section flagged with LLEXT_PREPARATION_DONE "
                "- not preparing again")
            return 0

        # Get the struct.Struct for export table entry
        self.ptrsize = self.elf.elfclass // 8
        self.endianness = 'little' if self.elf.little_endian else 'big'
        self.lcs_struct = _llext_const_symbol_struct(self.ptrsize, self.endianness)

        # Verify that the export table size is coherent
        if (self.exptab_section.size % self.lcs_struct.size) != 0:
            self.log.error(f"export table size (0x{self.exptab_section.size:X}) "
                f"not aligned to 'llext_const_symbol' size (0x{self.lcs_struct.size:X})")
            return 1

        # Create the export table manipulator
        num_exports = self.exptab_section.size // self.lcs_struct.size
        self.exptab_manipulator = LLEXTExptabManipulator(
            self.elf_fd, self.exptab_section.offset, self.lcs_struct, num_exports)

        # Attempt to locate the export names section
        try:
            self.expstrtab_section = SectionDescriptor(
                self.elf, LLEXT_EXPORT_NAMES_SECTION_NAME)
        except KeyError:
            self.expstrtab_section = None

        self.log.debug(f"exports table section at file offset 0x{self.exptab_section.offset:X}")
        if self.expstrtab_section:
            self.log.debug(f"exports strtab section at file offset 0x{self.expstrtab_section.offset:X}")
        else:
            self.log.debug("no exports strtab section in ELF")
        self.log.info(f"{num_exports} symbols are exported to LLEXTs by this ELF")

        # Perform the export table preparation
        if self.expstrtab_section:
            res = self._prepare_exptab_for_slid_linking()
        else:
            res = self._prepare_exptab_for_str_linking()

        if res == 0: # Add the "prepared" flag to export table section
            self._set_prep_done_shdr_flag()

    def prepare_elf(self):
        res = self._prepare_inner()
        self.elf_fd.close()
        return res

# pylint: disable=duplicate-code
def _parse_args(argv):
    """Parse the command line arguments."""
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
        allow_abbrev=False)

    parser.add_argument("-f", "--elf-file", default=pathlib.Path("build", "zephyr", "zephyr.elf"),
                        help="ELF file to process")
    parser.add_argument("-sl", "--slid-listing",
                        help=("write the SLID listing to a file (only useful"
                              "when CONFIG_LLEXT_EXPORT_BUILTINS_BY_SLID is enabled) "))
    parser.add_argument("-v", "--verbose", action="count",
                        help=("enable verbose output, can be used multiple times "
                              "to increase verbosity level"))
    parser.add_argument("--always-succeed", action="store_true",
                        help="always exit with a return code of 0, used for testing")

    return parser.parse_args(argv)

def _init_log(verbose):
    """Initialize a logger object."""
    log = logging.getLogger(__file__)

    console = logging.StreamHandler()
    console.setFormatter(logging.Formatter("%(levelname)s: %(message)s"))
    log.addHandler(console)

    if verbose and verbose > 1:
        log.setLevel(logging.DEBUG)
    elif verbose and verbose > 0:
        log.setLevel(logging.INFO)
    else:
        log.setLevel(logging.WARNING)

    return log

def main(argv=None):
    args = _parse_args(argv)

    log = _init_log(args.verbose)

    log.info(f"prepare_llext_exptab: {args.elf_file}")

    preparator = ZephyrElfExptabPreparator(args.elf_file, log, args.slid_listing)

    res = preparator.prepare_elf()

    if args.always_succeed:
        return 0

    return res

if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
