#!/usr/bin/python3

"""
Extracts symbol data from relocatable ELF files.
"""

import argparse
from dataclasses import dataclass
from enum import IntEnum
from io import BufferedReader
import json
import os
import re
import struct
import sys
from typing import ByteString, ClassVar, List, Union

__author__ = "kipcode66"
__copyright__ = "Copyright 2022, kipcode66"
__credits__ = ["kipcode66"]
__license__ = "GPL3"
__version__ = "0.1.0"


class SHID(IntEnum):
    UND = 0
    ABS = 65521


class EIClass(IntEnum):
    C32 = 1
    C64 = 2


class EIData(IntEnum):
    LITTLE = 1
    BIG = 2


@dataclass
class ELFIdent():
    magic: bytes
    clss: EIClass
    data: EIData
    version: int
    os_abi: int
    abi_version: int
    FORMAT: ClassVar[struct.Struct] = struct.Struct("=4sBBBBB7x")


class ELFType(IntEnum):
    NONE = 0
    REL = 1
    EXEC = 2
    DYN = 3
    CORE = 4
    LOOS = 0xFE00
    HIOS = 0xFEFF
    LOPROC = 0xFF00
    HIPROC = 0xFFFF


@dataclass
class ELFHeader():
    e_ident: ELFIdent
    e_type: ELFType
    e_machine: int
    e_version: int
    e_entry: int
    e_phoff: int
    e_shoff: int
    e_flags: int
    e_ehsize: int
    e_phentsize: int
    e_phnum: int
    e_shentsize: int
    e_shnum: int
    e_shstrndx: int
    FORMAT_L32: ClassVar[struct.Struct] = struct.Struct("<HHIIIIIHHHHHH")
    FORMAT_L64: ClassVar[struct.Struct] = struct.Struct("<HHIQQQIHHHHHH")
    FORMAT_B32: ClassVar[struct.Struct] = struct.Struct(">HHIIIIIHHHHHH")
    FORMAT_B64: ClassVar[struct.Struct] = struct.Struct(">HHIQQQIHHHHHH")


@dataclass
class ELFProgramHeader():
    p_type: int
    p_offset: int
    p_vaddr: int
    p_paddr: int
    p_filesz: int
    p_memsz: int
    p_flags: int
    p_align: int
    FORMAT_L32: ClassVar[struct.Struct] = struct.Struct("<IIIIIIII")
    FORMAT_L64: ClassVar[struct.Struct] = struct.Struct("<IIQQQQQQ")
    FORMAT_B32: ClassVar[struct.Struct] = struct.Struct(">IIIIIIII")
    FORMAT_B64: ClassVar[struct.Struct] = struct.Struct(">IIQQQQQQ")


class SectionHeaderType(IntEnum):
    NULL = 0
    PROGBITS = 1
    SYMTAB = 2
    STRTAB = 3
    RELA = 4
    HASH = 5
    DYNAMIC = 6
    NOTE = 7
    NOBITS = 8
    REL = 9
    SHLIB = 10
    DYNSYM = 11
    INIT_ARRAY = 14
    FINI_ARRAY = 15
    PREINI_ARRAY = 16
    GROUP = 17
    SYMTAB_SHNDX = 18
    NUM = 13


@dataclass
class ELFSectionHeader():
    sh_name: int
    sh_type: SectionHeaderType
    sh_flags: int
    sh_addr: int
    sh_offset: int
    sh_size: int
    sh_link: int
    sh_info: int
    sh_addralign: int
    sh_entsize: int
    FORMAT_L32: ClassVar[struct.Struct] = struct.Struct("<IIIIIIIIII")
    FORMAT_L64: ClassVar[struct.Struct] = struct.Struct("<IIQQQQIIQQ")
    FORMAT_B32: ClassVar[struct.Struct] = struct.Struct(">IIIIIIIIII")
    FORMAT_B64: ClassVar[struct.Struct] = struct.Struct(">IIQQQQIIQQ")


class SymbolBinding(IntEnum):
    LOCAL = 0
    GLOBAL = 1
    WEAK = 2


class SymbolType(IntEnum):
    NOTYPE = 0
    OBJECT = 1
    FUNC = 2
    SECTION = 3
    FILE = 4


@dataclass
class ELFSymbol():
    st_name: int
    st_value: int
    st_size: int
    st_info: int
    st_other: int
    st_shndx: int
    FORMAT_L32: ClassVar[struct.Struct] = struct.Struct("<IIIBBH")
    FORMAT_L64: ClassVar[struct.Struct] = struct.Struct("<IQQBBH")
    FORMAT_B32: ClassVar[struct.Struct] = struct.Struct(">IIIBBH")
    FORMAT_B64: ClassVar[struct.Struct] = struct.Struct(">IQQBBH")

    def get_bind(self) -> Union[SymbolBinding, int]:
        b = (self.st_info & 0xf0) >> 4
        return SymbolBinding(b) if b < len(SymbolBinding) else b

    def get_type(self) -> Union[SymbolType, int]:
        t = (self.st_info & 0xf)
        return SymbolType(t) if t < len(SymbolType) else t


class DataFormat(IntEnum):
    L32 = 0
    L64 = 1
    B32 = 2
    B64 = 3


class ELFFile():
    __slots__ = ("header", "p_headers", "sections",
                 "shstr", "strtab", "symbols")

    def __init__(self, reader: BufferedReader):
        e_ident = ELFIdent(
            *ELFIdent.FORMAT.unpack(reader.read(ELFIdent.FORMAT.size)))
        if not e_ident.magic == b"\x7FELF":
            raise TypeError("Unsupported file format (not ELF)")
        e_ident.clss = EIClass(e_ident.clss)
        e_ident.data = EIData(e_ident.data)

        data_format = DataFormat(
            (e_ident.clss - 1) | ((e_ident.data - 1) << 1))
        h_formats = {DataFormat.L32: ELFHeader.FORMAT_L32, DataFormat.L64: ELFHeader.FORMAT_L64,
                     DataFormat.B32: ELFHeader.FORMAT_B32, DataFormat.B64: ELFHeader.FORMAT_B64}
        p_formats = {DataFormat.L32: ELFProgramHeader.FORMAT_L32, DataFormat.L64: ELFProgramHeader.FORMAT_L64,
                     DataFormat.B32: ELFProgramHeader.FORMAT_B32, DataFormat.B64: ELFProgramHeader.FORMAT_B64}
        self.header = ELFHeader(e_ident, *h_formats[data_format].unpack(
            reader.read(h_formats[data_format].size)))
        self.header.e_type = ELFType(self.header.e_type)
        # Load program header table
        self.p_headers: List[ELFProgramHeader] = []
        for i in range(self.header.e_phnum):
            reader.seek(self.header.e_phoff + i * self.header.e_phentsize)
            if e_ident.clss == EIClass.C32:
                p_header = ELFProgramHeader(
                    *p_formats[data_format].unpack(reader.read(p_formats[data_format].size)))
            else:
                tmp = p_formats[data_format].unpack(
                    reader.read(p_formats[data_format].size))
                p_header = ELFProgramHeader(
                    tmp[0], *tmp[2:7], tmp[1], *tmp[7:])
            self.p_headers.append(p_header)
        # Load the section header table
        sh_formats = {DataFormat.L32: ELFSectionHeader.FORMAT_L32, DataFormat.L64: ELFSectionHeader.FORMAT_L64,
                      DataFormat.B32: ELFSectionHeader.FORMAT_B32, DataFormat.B64: ELFSectionHeader.FORMAT_B64}
        self.sections: List[ELFSectionHeader] = []
        for i in range(self.header.e_shnum):
            reader.seek(self.header.e_shoff + i * self.header.e_shentsize)
            sh_header = ELFSectionHeader(
                *sh_formats[data_format].unpack(reader.read(sh_formats[data_format].size)))
            if sh_header.sh_type < SectionHeaderType.NUM:
                sh_header.sh_type = SectionHeaderType(sh_header.sh_type)
            self.sections.append(sh_header)
        # load main name table
        reader.seek(self.sections[self.header.e_shstrndx].sh_offset)
        section_str_table = reader.read(
            self.sections[self.header.e_shstrndx].sh_size)
        self.shstr = section_str_table
        # Set section names
        for section in self.sections:
            section.sh_name = self._get_shstr(section.sh_name)

        strtab = self.get_section_by_name(b".strtab")
        reader.seek(strtab.sh_offset)
        strtab = reader.read(strtab.sh_size)
        self.strtab = strtab

        # Get the symbol table
        symtab_idx = self.get_section_idx(b".symtab")
        symtab: ELFSectionHeader = self.sections[symtab_idx]
        st_formats = {DataFormat.L32: ELFSymbol.FORMAT_L32, DataFormat.L64: ELFSymbol.FORMAT_L64,
                      DataFormat.B32: ELFSymbol.FORMAT_B32, DataFormat.B64: ELFSymbol.FORMAT_B64}
        self.symbols: List[ELFSymbol] = []
        for i in range(symtab.sh_size // symtab.sh_entsize):
            reader.seek(symtab.sh_offset + i * symtab.sh_entsize)
            sym = ELFSymbol(
                *st_formats[data_format].unpack(reader.read(symtab.sh_entsize)))
            sym.st_name = self._get_str(sym.st_name)
            self.symbols.append(sym)

    def _get_str(self, idx: int):
        c = 0
        while self.strtab[idx + c] != 0 and c + idx < len(self.strtab):
            c += 1
        return self.strtab[idx: idx+c]

    def _get_shstr(self, idx: int):
        c = 0
        while self.shstr[idx + c] != 0 and c + idx < len(self.shstr):
            c += 1
        return self.shstr[idx: idx+c]

    def get_section_by_name(self, name: ByteString):
        ret = None
        for section in self.sections:
            if section.sh_name == name:
                ret = section
                break
        return ret

    def get_section_idx(self, name: ByteString):
        ret = None
        for i, section in enumerate(self.sections):
            if section.sh_name == name:
                ret = i
                break
        return ret


def main():
    EXCLUDED_ENTRIES = ["^_prolog$", "^_epilog$", "^_unresolved$",
                        "^_ZN3mod4mainEv$", "^_ZN3mod4exitEv$",
                        r"^_rest(?:g|f)pr_[a-zA-Z0-9_]*_x$",
                        r"^_(?:c|d)tors_(?:start|end)$",
                        r"^__(?:s?bss|stack)_(?:start|end)$",
                        r"^_e(?:data|nd)$"]

    # Parsing functions
    def parseInputLstFile(string):
        return string

    def parseOutputLstFile(string):
        return string

    def parseInputConfigFile(string):
        return string

    def parseInputElfFile(string):
        return string

    parser = argparse.ArgumentParser(
        sys.argv[0], description="Tool to extract the symbols from ELF file(s).")
    parser.add_argument("-o", "--output-lst", type=parseOutputLstFile,
                        required=True, help="Path to the output file")
    parser.add_argument("-m", "--input-modules", type=parseInputConfigFile,
                        required=False, help="Path to list of module IDs")
    parser.add_argument("-i", "--input-lst",
                        type=parseInputLstFile, help="Path to the input file")
    parser.add_argument("-s", "--start-id", type=int, default=0x1000)
    parser.add_argument("elf", type=parseInputElfFile,
                        nargs="+", help="List of additional modules to add")
    args = parser.parse_args()

    provided_lst = {}

    # Load the provided lst file (if needed)
    if not args.input_lst is None:
        with open(args.input_lst, "r") as f:
            for line in f:
                m = re.match(r"^\s*(?://.*)?$", line)
                if m:
                    # Comment line, skip
                    continue
                m = re.match(
                    r"^(?:([a-zA-Z0-9]{1,8}),([a-zA-Z0-9]{1,8}),)?([a-zA-Z0-9]{1,8}):([^/\s]+?)(?:\s*//.*)?$", line)
                if m:
                    provided_lst.setdefault(m[4], (0 if m[1] is None else int(
                        m[1], 16), 0 if m[2] is None else int(m[2], 16), int(m[3], 16)))

    module_ids = {}
    # Load module ids
    if not args.input_modules is None:
        with open(args.input_modules, "r") as f:
            module_ids = json.load(f)

    curr_id = args.start_id

    def skip_symbol_predicate(symbol: ELFSymbol):
        if any(not re.search(excluded, str(symbol.st_name, encoding="utf-8")) is None for excluded in EXCLUDED_ENTRIES):
            return True
        if symbol.st_shndx == SHID.UND or symbol.st_shndx >= len(elf.sections):
            return True
        if symbol.st_size == 0 and symbol.get_type() is SymbolType.NOTYPE and symbol.st_name:
            return False
        if symbol.st_size == 0:
            return True
        return False

    for elf_file in args.elf:
        with open(elf_file, "rb") as f:
            elf = ELFFile(f)
            file_name = os.path.splitext(os.path.basename(elf_file))
            while file_name[1]:
                file_name = os.path.splitext(file_name[0])
            file_name = file_name[0]
            if not file_name in module_ids:
                module_ids.setdefault(file_name, curr_id)
                curr_id += 1
            for symbol in elf.symbols:
                if skip_symbol_predicate(symbol):
                    continue
                provided_lst.setdefault(str(symbol.st_name, encoding="utf-8"),
                                        (module_ids[file_name], symbol.st_shndx, symbol.st_value))

    # Output lst file
    with open(args.output_lst, "w") as f:
        f.writelines([f"0x{t[0]:x},{t[1]:d},{t[2]:x}:{name}\n" if t[0] !=
                     0 else f"{t[2]:x}:{name}\n" for name, t in provided_lst.items()])


if __name__ == "__main__":
    main()
