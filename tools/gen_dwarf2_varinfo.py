#!/usr/bin/env python3
"""Convert DWARF 1 variable/type info from .o files into DWARF 2.

mwcceppc emits DWARF 1.1 (.debug sections) which newer version of GDB cannot read.
This script parses the DWARF 1 debug info from each .o, extracts function
boundaries, parameters, local variables, and basic type information, then
generates DWARF 2 .debug_abbrev/.debug_info sections as gas assembly.

Works alongside gen_dwarf2_debug.py (which handles line tables) to provide
full source-level debugging with `info locals`, `info args`, `print var`.

Usage:
    python3 tools/gen_dwarf2_varinfo.py <build_dir>
    # e.g. python3 tools/gen_dwarf2_varinfo.py build/GZ2E01
"""

import os
import re
import struct
import subprocess
import sys


# ---------------------------------------------------------------------------
# DWARF 1 constants (TIS DWARF 1 spec — used by MetroWerks)
# ---------------------------------------------------------------------------

# Tags
DW1_TAG_PADDING = 0x0000
DW1_TAG_ARRAY_TYPE = 0x0001
DW1_TAG_CLASS_TYPE = 0x0002
DW1_TAG_ENTRY_POINT = 0x0003
DW1_TAG_ENUM_TYPE = 0x0004
DW1_TAG_FORMAL_PARAM = 0x0005
DW1_TAG_GLOBAL_SUBR = 0x0006
DW1_TAG_GLOBAL_VAR = 0x0007
DW1_TAG_LOCAL_VAR = 0x000C
DW1_TAG_MEMBER = 0x000D
DW1_TAG_POINTER_TYPE = 0x000F
DW1_TAG_COMPILE_UNIT = 0x0011
DW1_TAG_STRUCT_TYPE = 0x0013
DW1_TAG_SUBROUTINE = 0x0014
DW1_TAG_SUBROUTINE_TYPE = 0x0015
DW1_TAG_TYPEDEF = 0x0016
DW1_TAG_UNION_TYPE = 0x0017

# Attributes (base values — form is OR'd into low nibble)
DW1_AT_SIBLING = 0x0010
DW1_AT_LOCATION = 0x0020
DW1_AT_NAME = 0x0030
DW1_AT_FUND_TYPE = 0x0050
DW1_AT_MOD_FUND_TYPE = 0x0060
DW1_AT_MOD_U_D_TYPE = 0x0070
DW1_AT_BYTE_SIZE = 0x00A0
DW1_AT_STMT_LIST = 0x0100
DW1_AT_LOW_PC = 0x0110
DW1_AT_HIGH_PC = 0x0120
DW1_AT_LANGUAGE = 0x0130
DW1_AT_MEMBER = 0x0140
DW1_AT_PRODUCER = 0x0250
DW1_AT_MW_MANGLED = 0x2000

# Location ops
DW1_OP_REG = 0x01
DW1_OP_BASEREG = 0x02
DW1_OP_ADDR = 0x03
DW1_OP_CONST = 0x04
DW1_OP_ADD = 0x07

# Form sizes
FORM_SIZES = {0x1: 4, 0x2: 4, 0x5: 2, 0x6: 4, 0x7: 8}

# Fundamental types: ft_code -> (name, byte_size, DW_ATE_encoding)
FT_INFO = {
    0x01: ("char", 1, 0x06),             # DW_ATE_signed_char
    0x02: ("signed char", 1, 0x06),
    0x03: ("unsigned char", 1, 0x08),     # DW_ATE_unsigned_char
    0x04: ("short", 2, 0x05),             # DW_ATE_signed
    0x05: ("signed short", 2, 0x05),
    0x06: ("unsigned short", 2, 0x07),    # DW_ATE_unsigned
    0x07: ("int", 4, 0x05),
    0x08: ("signed int", 4, 0x05),
    0x09: ("unsigned int", 4, 0x07),
    0x0A: ("long", 4, 0x05),
    0x0B: ("signed long", 4, 0x05),
    0x0C: ("unsigned long", 4, 0x07),
    0x0D: ("void *", 4, 0x01),            # DW_ATE_address
    0x0E: ("float", 4, 0x04),             # DW_ATE_float
    0x0F: ("double", 8, 0x04),
    0x14: ("void", 0, 0x00),
    0x15: ("bool", 1, 0x02),              # DW_ATE_boolean
}

# Canonical fund_type for dedup (e.g., int == signed int)
FT_CANONICAL = {
    0x02: 0x01,  # signed char -> char
    0x05: 0x04,  # signed short -> short
    0x08: 0x07,  # signed int -> int
    0x0B: 0x0A,  # signed long -> long
}


# ---------------------------------------------------------------------------
# ELF parsing (reused from gen_dwarf2_debug.py)
# ---------------------------------------------------------------------------

def read_elf_sections(path):
    """Parse ELF section headers, return {name: (offset, size, addr)}."""
    sections = {}
    with open(path, "rb") as f:
        magic = f.read(4)
        if magic != b"\x7fELF":
            return sections
        f.seek(0)
        ehdr = f.read(52)
        e_shoff = struct.unpack(">I", ehdr[32:36])[0]
        e_shentsize = struct.unpack(">H", ehdr[46:48])[0]
        e_shnum = struct.unpack(">H", ehdr[48:50])[0]
        e_shstrndx = struct.unpack(">H", ehdr[50:52])[0]

        f.seek(e_shoff + e_shstrndx * e_shentsize)
        shdr = f.read(e_shentsize)
        strtab_off = struct.unpack(">I", shdr[16:20])[0]
        strtab_sz = struct.unpack(">I", shdr[20:24])[0]
        f.seek(strtab_off)
        strtab = f.read(strtab_sz)

        for i in range(e_shnum):
            f.seek(e_shoff + i * e_shentsize)
            shdr = f.read(e_shentsize)
            name_idx = struct.unpack(">I", shdr[0:4])[0]
            end = strtab.index(b"\x00", name_idx)
            name = strtab[name_idx:end].decode("ascii", errors="replace")
            sh_addr = struct.unpack(">I", shdr[12:16])[0]
            sh_off = struct.unpack(">I", shdr[16:20])[0]
            sh_size = struct.unpack(">I", shdr[20:24])[0]
            if name and name not in sections:
                sections[name] = (sh_off, sh_size, sh_addr)
    return sections


def read_elf_sections_detailed(path):
    """Parse ELF returning (section_list, section_dict).

    section_list: [(name, sh_type, sh_off, sh_size, sh_link, sh_addr), ...]
    section_dict: {name: (sh_off, sh_size, sh_addr)}
    """
    sec_list = []
    sec_dict = {}
    with open(path, "rb") as f:
        magic = f.read(4)
        if magic != b"\x7fELF":
            return sec_list, sec_dict
        f.seek(0)
        ehdr = f.read(52)
        e_shoff = struct.unpack(">I", ehdr[32:36])[0]
        e_shentsize = struct.unpack(">H", ehdr[46:48])[0]
        e_shnum = struct.unpack(">H", ehdr[48:50])[0]
        e_shstrndx = struct.unpack(">H", ehdr[50:52])[0]

        f.seek(e_shoff + e_shstrndx * e_shentsize)
        shdr = f.read(e_shentsize)
        strtab_off = struct.unpack(">I", shdr[16:20])[0]
        strtab_sz = struct.unpack(">I", shdr[20:24])[0]
        f.seek(strtab_off)
        strtab = f.read(strtab_sz)

        for i in range(e_shnum):
            f.seek(e_shoff + i * e_shentsize)
            shdr = f.read(e_shentsize)
            name_idx = struct.unpack(">I", shdr[0:4])[0]
            end = strtab.index(b"\x00", name_idx)
            name = strtab[name_idx:end].decode("ascii", errors="replace")
            sh_type = struct.unpack(">I", shdr[4:8])[0]
            sh_addr = struct.unpack(">I", shdr[12:16])[0]
            sh_off = struct.unpack(">I", shdr[16:20])[0]
            sh_size = struct.unpack(">I", shdr[20:24])[0]
            sh_link = struct.unpack(">I", shdr[24:28])[0]
            sec_list.append((name, sh_type, sh_off, sh_size, sh_link, sh_addr))
            if name and name not in sec_dict:
                sec_dict[name] = (sh_off, sh_size, sh_addr)
    return sec_list, sec_dict


def get_text_base(elf_path):
    """Get the .text section virtual address from an ELF."""
    sections = read_elf_sections(elf_path)
    if ".text" in sections:
        return sections[".text"][2]
    return None


# ---------------------------------------------------------------------------
# MAP file parsing (reused from gen_dwarf2_debug.py)
# ---------------------------------------------------------------------------

def parse_map_file(map_path):
    """Parse MAP file .text section layout.

    Returns {obj_basename: [(starting_address, size), ...]}
    """
    obj_offsets = {}
    in_text_layout = False
    past_header = False

    with open(map_path) as f:
        for line in f:
            line = line.rstrip()
            if ".text section layout" in line:
                in_text_layout = True
                past_header = False
                continue
            if in_text_layout:
                if line.strip().startswith("---"):
                    past_header = True
                    continue
                if not past_header:
                    continue
                if not line.strip():
                    continue
                if line.strip() and not line.startswith("  "):
                    in_text_layout = False
                    continue

                m = re.match(
                    r"\s+([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+[0-9a-fA-F]+\s+[0-9a-fA-F]+\s+"
                    r"(\d+)\s+(\S+)\s+(\S+)",
                    line,
                )
                if m:
                    start_addr = int(m.group(1), 16)
                    size = int(m.group(2), 16)
                    alignment = int(m.group(3))
                    section_name = m.group(4)
                    obj_name = m.group(5)
                    if alignment == 1 and section_name == ".text" and size > 0:
                        obj_offsets.setdefault(obj_name, []).append(
                            (start_addr, size)
                        )
    return obj_offsets


def build_o_index(search_dirs):
    """Build {basename: path} index of .o files."""
    o_by_basename = {}
    for search_dir in search_dirs:
        if not os.path.isdir(search_dir):
            continue
        for dirpath, _, filenames in os.walk(search_dir):
            for fn in filenames:
                if fn.endswith(".o") and fn not in ("debug_info.o", "debug_varinfo.o"):
                    full = os.path.join(dirpath, fn)
                    if fn not in o_by_basename or "/src/" in full:
                        o_by_basename[fn] = full
    return o_by_basename


# ---------------------------------------------------------------------------
# DWARF 1 parsing — variable/type info
# ---------------------------------------------------------------------------

def parse_dwarf1_dies(o_path):
    """Parse DWARF 1 .debug section from a .o file.

    Returns list of DIEs: [(offset, tag, attrs_dict, sibling_offset), ...]
    where attrs_dict maps AT_xxx constant -> value.

    Resolves .rela.debug relocations for addresses and sibling references.
    """
    sec_list, sec_dict = read_elf_sections_detailed(o_path)
    if ".debug" not in sec_dict or ".rela.debug" not in sec_dict:
        return []

    with open(o_path, "rb") as f:
        # Read .debug
        doff, dsz, _ = sec_dict[".debug"]
        f.seek(doff)
        debug_data = f.read(dsz)

        # Read .rela.debug
        roff, rsz, _ = sec_dict[".rela.debug"]
        f.seek(roff)
        rela_data = f.read(rsz)

        # Read .symtab
        if ".symtab" not in sec_dict:
            return []
        soff, ssz, _ = sec_dict[".symtab"]
        f.seek(soff)
        symtab_data = f.read(ssz)

        # Find .symtab's string table link
        symtab_link = None
        for name, sh_type, sh_off, sh_size, sh_link, sh_addr in sec_list:
            if name == ".symtab":
                symtab_link = sh_link
                break
        if symtab_link is None:
            return []

        strtab_name = sec_list[symtab_link][0]
        st_off, st_sz, _ = sec_dict[strtab_name]
        f.seek(st_off)
        sym_strtab = f.read(st_sz)

    # Build symbol table: [(name, value, shndx), ...]
    n_syms = ssz // 16
    symbols = []
    for i in range(n_syms):
        st_name_off = struct.unpack(">I", symtab_data[i*16:i*16+4])[0]
        st_value = struct.unpack(">I", symtab_data[i*16+4:i*16+8])[0]
        st_shndx = struct.unpack(">H", symtab_data[i*16+14:i*16+16])[0]
        end_idx = sym_strtab.index(b"\x00", st_name_off)
        sym_name = sym_strtab[st_name_off:end_idx].decode("ascii", errors="replace")
        symbols.append((sym_name, st_value, st_shndx))

    # Find .debug and .text section indices
    debug_shndx = None
    text_shndx = None
    for i, (name, sh_type, sh_off, sh_size, sh_link, sh_addr) in enumerate(sec_list):
        if name == ".debug":
            debug_shndx = i
        elif name == ".text" and text_shndx is None:
            text_shndx = i

    # Build relocation map: {offset_in_debug: (section_name, addend)}
    rela_map = {}
    for i in range(rsz // 12):
        r_off = struct.unpack(">I", rela_data[i*12:i*12+4])[0]
        r_info = struct.unpack(">I", rela_data[i*12+4:i*12+8])[0]
        r_addend = struct.unpack(">i", rela_data[i*12+8:i*12+12])[0]
        r_sym_idx = r_info >> 8

        if r_sym_idx >= len(symbols):
            continue

        sym_name, sym_val, sym_shndx = symbols[r_sym_idx]
        resolved_value = sym_val + r_addend

        if sym_shndx == text_shndx:
            rela_map[r_off] = ("text", resolved_value)
        elif sym_shndx == debug_shndx or (sym_name.startswith(".dwarf.")):
            rela_map[r_off] = ("debug", resolved_value)
        else:
            # Other sections (rodata, data, etc.) — treat as address
            section_name = sec_list[sym_shndx][0] if sym_shndx < len(sec_list) else "?"
            rela_map[r_off] = (section_name, resolved_value)

    # Parse DIEs
    dies = []
    pos = 0
    while pos < len(debug_data):
        if pos + 4 > len(debug_data):
            break
        die_len = struct.unpack(">I", debug_data[pos:pos+4])[0]
        if die_len < 6:
            pos += 4
            continue

        die_start = pos
        die_end = pos + die_len
        pos += 4

        tag = struct.unpack(">H", debug_data[pos:pos+2])[0]
        pos += 2

        attrs = {}
        while pos < die_end:
            if pos + 2 > die_end:
                break
            attr_word = struct.unpack(">H", debug_data[pos:pos+2])[0]
            if attr_word == 0:
                break
            pos += 2

            form = attr_word & 0xF
            attr_base = attr_word & 0xFFF0
            value_pos = pos

            if form == 0x8:  # FORM_STRING
                start = pos
                while pos < die_end and debug_data[pos] != 0:
                    pos += 1
                value = debug_data[start:pos].decode("ascii", errors="replace")
                pos += 1
            elif form == 0x3:  # FORM_BLOCK2
                blen = struct.unpack(">H", debug_data[pos:pos+2])[0]
                pos += 2
                value = bytes(debug_data[pos:pos+blen])
                pos += blen
            elif form == 0x4:  # FORM_BLOCK4
                blen = struct.unpack(">I", debug_data[pos:pos+4])[0]
                pos += 4
                value = bytes(debug_data[pos:pos+blen])
                pos += blen
            elif form in FORM_SIZES:
                sz = FORM_SIZES[form]
                if sz == 2:
                    value = struct.unpack(">H", debug_data[pos:pos+2])[0]
                elif sz == 4:
                    value = struct.unpack(">I", debug_data[pos:pos+4])[0]
                elif sz == 8:
                    value = struct.unpack(">Q", debug_data[pos:pos+8])[0]
                else:
                    value = 0

                # Resolve relocation
                if value_pos in rela_map:
                    section, resolved = rela_map[value_pos]
                    value = (section, resolved)

                pos += sz
            else:
                break

            attrs[attr_base] = value

        # Resolve sibling offset
        sibling_offset = None
        sib = attrs.get(DW1_AT_SIBLING)
        if isinstance(sib, tuple) and sib[0] == "debug":
            sibling_offset = sib[1]

        dies.append((die_start, tag, attrs, sibling_offset))
        pos = die_end

    return dies


def extract_varinfo(dies):
    """Extract functions, parameters, and local variables from parsed DIEs.

    Returns (source_name, functions) where functions is:
    [(name, mangled, low_pc, high_pc, [(var_kind, name, fund_type, location), ...]), ...]

    low_pc/high_pc are .text-relative offsets.
    var_kind is "param" or "local".
    fund_type is the fundamental type code (or None).
    location is the raw DWARF 1 location block bytes (or None).
    """
    source_name = None
    functions = []
    current_func = None
    current_func_end = None  # sibling offset to determine children

    for die_start, tag, attrs, sibling_offset in dies:
        if tag == DW1_TAG_COMPILE_UNIT:
            source_name = attrs.get(DW1_AT_NAME)
            continue

        if tag == DW1_TAG_GLOBAL_SUBR or tag == DW1_TAG_SUBROUTINE:
            # Start a new function
            name = attrs.get(DW1_AT_NAME, "")
            mangled = attrs.get(DW1_AT_MW_MANGLED, name)
            low_pc = attrs.get(DW1_AT_LOW_PC)
            high_pc = attrs.get(DW1_AT_HIGH_PC)

            # Resolve text-relative addresses
            lp = None
            hp = None
            if isinstance(low_pc, tuple) and low_pc[0] == "text":
                lp = low_pc[1]
            if isinstance(high_pc, tuple) and high_pc[0] == "text":
                hp = high_pc[1]

            if lp is not None and hp is not None:
                current_func = {
                    "name": name,
                    "mangled": mangled,
                    "low_pc": lp,
                    "high_pc": hp,
                    "children": [],
                }
                current_func_end = sibling_offset
                functions.append(current_func)
            else:
                current_func = None
                current_func_end = None
            continue

        # Check if this DIE is a child of the current function
        if current_func is None:
            continue
        if current_func_end is not None and die_start >= current_func_end:
            current_func = None
            current_func_end = None
            continue

        if tag == DW1_TAG_FORMAL_PARAM:
            name = attrs.get(DW1_AT_NAME)
            if name is None:
                continue
            ft = attrs.get(DW1_AT_FUND_TYPE)
            loc = attrs.get(DW1_AT_LOCATION)
            current_func["children"].append(("param", name, ft, loc))

        elif tag == DW1_TAG_LOCAL_VAR:
            name = attrs.get(DW1_AT_NAME)
            if name is None:
                continue
            ft = attrs.get(DW1_AT_FUND_TYPE)
            loc = attrs.get(DW1_AT_LOCATION)
            current_func["children"].append(("local", name, ft, loc))

    return source_name, functions


# ---------------------------------------------------------------------------
# DWARF 1 → DWARF 2 location conversion
# ---------------------------------------------------------------------------

def sleb128_bytes(value):
    """Encode a signed value as SLEB128."""
    result = []
    more = True
    while more:
        byte = value & 0x7F
        value >>= 7
        if (value == 0 and (byte & 0x40) == 0) or \
           (value == -1 and (byte & 0x40) != 0):
            more = False
        else:
            byte |= 0x80
        result.append(byte)
    return bytes(result)


def convert_location(loc_block):
    """Convert DWARF 1 location expression to DWARF 2.

    Returns list of bytes for the DWARF 2 location expression,
    or None if conversion fails.
    """
    if not loc_block or len(loc_block) < 1:
        return None

    op = loc_block[0]

    if op == DW1_OP_REG and len(loc_block) >= 5:
        # OP_REG + u32 regnum → DW_OP_regN
        regnum = struct.unpack(">I", loc_block[1:5])[0]
        if regnum < 32:
            return bytes([0x50 + regnum])  # DW_OP_reg0..DW_OP_reg31
        else:
            # DW_OP_regx + ULEB128
            result = [0x90]
            val = regnum
            while True:
                b = val & 0x7F
                val >>= 7
                if val:
                    b |= 0x80
                result.append(b)
                if not val:
                    break
            return bytes(result)

    elif op == DW1_OP_BASEREG and len(loc_block) >= 5:
        # OP_BASEREG + u32 regnum [+ OP_CONST + u32 offset + OP_ADD]
        regnum = struct.unpack(">I", loc_block[1:5])[0]
        offset = 0

        # Check for OP_CONST + OP_ADD
        if len(loc_block) >= 10 and loc_block[5] == DW1_OP_CONST:
            offset = struct.unpack(">I", loc_block[6:10])[0]
            # OP_ADD may follow but we don't need to check

        if regnum < 32:
            # DW_OP_bregN + SLEB128 offset
            return bytes([0x70 + regnum]) + sleb128_bytes(offset)

    elif op == DW1_OP_ADDR and len(loc_block) >= 5:
        # OP_ADDR + u32 address → DW_OP_addr + u32
        addr = struct.unpack(">I", loc_block[1:5])[0]
        return bytes([0x03]) + struct.pack(">I", addr)

    return None


# ---------------------------------------------------------------------------
# DWARF 2 assembly generation
# ---------------------------------------------------------------------------

def generate_abbrev_table():
    """Generate the .debug_abbrev section as gas assembly lines."""
    lines = []
    lines.append('    .section .debug_abbrev,"",@progbits')
    lines.append(".Labbrev_start:")

    # Abbrev 1: DW_TAG_compile_unit [has children]
    # NOTE: No low_pc/high_pc — prevents this CU from intercepting
    # address-to-line lookups that should go to the line-info CU.
    lines.append("    .byte 1")          # abbrev code
    lines.append("    .byte 0x11")       # DW_TAG_compile_unit
    lines.append("    .byte 1")          # DW_CHILDREN_yes
    lines.append("    .byte 0x03, 0x08") # DW_AT_name, DW_FORM_string
    lines.append("    .byte 0, 0")       # end attrs

    # Abbrev 2: DW_TAG_subprogram [has children] (with frame_base)
    lines.append("    .byte 2")
    lines.append("    .byte 0x2e")       # DW_TAG_subprogram
    lines.append("    .byte 1")          # DW_CHILDREN_yes
    lines.append("    .byte 0x03, 0x08") # DW_AT_name, DW_FORM_string
    lines.append("    .byte 0x11, 0x01") # DW_AT_low_pc, DW_FORM_addr
    lines.append("    .byte 0x12, 0x01") # DW_AT_high_pc, DW_FORM_addr
    lines.append("    .byte 0x40, 0x0a") # DW_AT_frame_base, DW_FORM_block1
    lines.append("    .byte 0, 0")

    # Abbrev 3: DW_TAG_subprogram [no children]
    lines.append("    .byte 3")
    lines.append("    .byte 0x2e")
    lines.append("    .byte 0")          # DW_CHILDREN_no
    lines.append("    .byte 0x03, 0x08") # DW_AT_name, DW_FORM_string
    lines.append("    .byte 0x11, 0x01") # DW_AT_low_pc, DW_FORM_addr
    lines.append("    .byte 0x12, 0x01") # DW_AT_high_pc, DW_FORM_addr
    lines.append("    .byte 0, 0")

    # Abbrev 4: DW_TAG_formal_parameter [no children]
    lines.append("    .byte 4")
    lines.append("    .byte 0x05")       # DW_TAG_formal_parameter
    lines.append("    .byte 0")
    lines.append("    .byte 0x03, 0x08") # DW_AT_name, DW_FORM_string
    lines.append("    .byte 0x49, 0x13") # DW_AT_type, DW_FORM_ref4
    lines.append("    .byte 0x02, 0x0a") # DW_AT_location, DW_FORM_block1
    lines.append("    .byte 0, 0")

    # Abbrev 5: DW_TAG_variable [no children]
    lines.append("    .byte 5")
    lines.append("    .byte 0x34")       # DW_TAG_variable
    lines.append("    .byte 0")
    lines.append("    .byte 0x03, 0x08") # DW_AT_name, DW_FORM_string
    lines.append("    .byte 0x49, 0x13") # DW_AT_type, DW_FORM_ref4
    lines.append("    .byte 0x02, 0x0a") # DW_AT_location, DW_FORM_block1
    lines.append("    .byte 0, 0")

    # Abbrev 6: DW_TAG_base_type [no children]
    lines.append("    .byte 6")
    lines.append("    .byte 0x24")       # DW_TAG_base_type
    lines.append("    .byte 0")
    lines.append("    .byte 0x03, 0x08") # DW_AT_name, DW_FORM_string
    lines.append("    .byte 0x0b, 0x0b") # DW_AT_byte_size, DW_FORM_data1
    lines.append("    .byte 0x3e, 0x0b") # DW_AT_encoding, DW_FORM_data1
    lines.append("    .byte 0, 0")

    # Abbrev 7: DW_TAG_pointer_type [no children]
    lines.append("    .byte 7")
    lines.append("    .byte 0x0f")       # DW_TAG_pointer_type
    lines.append("    .byte 0")
    lines.append("    .byte 0x0b, 0x0b") # DW_AT_byte_size, DW_FORM_data1
    lines.append("    .byte 0x49, 0x13") # DW_AT_type, DW_FORM_ref4
    lines.append("    .byte 0, 0")

    # Abbrev 8: DW_TAG_formal_parameter [no children] (no location)
    lines.append("    .byte 8")
    lines.append("    .byte 0x05")       # DW_TAG_formal_parameter
    lines.append("    .byte 0")
    lines.append("    .byte 0x03, 0x08") # DW_AT_name, DW_FORM_string
    lines.append("    .byte 0x49, 0x13") # DW_AT_type, DW_FORM_ref4
    lines.append("    .byte 0, 0")

    # Abbrev 9: DW_TAG_variable [no children] (no location)
    lines.append("    .byte 9")
    lines.append("    .byte 0x34")       # DW_TAG_variable
    lines.append("    .byte 0")
    lines.append("    .byte 0x03, 0x08") # DW_AT_name, DW_FORM_string
    lines.append("    .byte 0x49, 0x13") # DW_AT_type, DW_FORM_ref4
    lines.append("    .byte 0, 0")

    lines.append("    .byte 0")          # end of abbreviation table
    return lines


def generate_varinfo_asm(all_functions, text_base, out_s):
    """Generate DWARF 2 assembly for functions, params, and local variables.

    all_functions: list of (global_low_pc, global_high_pc, name, children)
        where children: [(var_kind, name, fund_type, dw2_location), ...]
    text_base: .text section virtual address
    """
    if not all_functions:
        return False

    # Collect used fundamental types
    used_ft = set()
    for _, _, _, children in all_functions:
        for kind, name, ft, loc in children:
            if ft is not None:
                canon = FT_CANONICAL.get(ft, ft)
                used_ft.add(canon)
    # Always include void* as fallback
    used_ft.add(0x0D)  # void*

    # Sort functions by address
    all_functions.sort(key=lambda f: f[0])

    lines = []
    lines.append("# Auto-generated DWARF 2 variable info — do not edit")
    lines.append("")

    # Abbreviation table
    lines.extend(generate_abbrev_table())
    lines.append("")

    # Debug info section
    lines.append('    .section .debug_info,"",@progbits')
    lines.append(".Lcu_header:")
    lines.append("    .4byte .Lcu_end - .Lcu_start  /* CU length */")
    lines.append(".Lcu_start:")
    lines.append("    .2byte 2           /* DWARF version */")
    lines.append("    .4byte .Labbrev_start  /* abbrev offset */")
    lines.append("    .byte 4            /* address size */")
    lines.append("")

    # Compile unit DIE (abbrev 1) — no address range to avoid
    # intercepting line lookups from the separate line-info .o file
    lines.append("    /* DW_TAG_compile_unit */")
    lines.append("    .byte 1")
    lines.append('    .asciz "varinfo"')
    lines.append("")

    # Emit base type DIEs
    ft_labels = {}  # ft_code -> label name
    for ft_code in sorted(used_ft):
        info = FT_INFO.get(ft_code)
        if info is None:
            continue
        ft_name, ft_size, ft_encoding = info
        label = ".Ltype_%02x" % ft_code
        ft_labels[ft_code] = label

        lines.append("    /* DW_TAG_base_type: %s */" % ft_name)
        lines.append("%s:" % label)
        lines.append("    .byte 6")
        lines.append('    .asciz "%s"' % ft_name)
        lines.append("    .byte %d  /* byte_size */" % ft_size)
        lines.append("    .byte %d  /* encoding */" % ft_encoding)
        lines.append("")

    # Default type label (void* for unknown types)
    default_type_label = ft_labels.get(0x0D, ".Ltype_0d")

    # Emit function DIEs
    func_count = 0
    var_count = 0

    for global_lp, global_hp, func_name, children in all_functions:
        has_children = len(children) > 0
        abs_lp = text_base + global_lp
        abs_hp = text_base + global_hp

        if has_children:
            lines.append("    /* DW_TAG_subprogram: %s */" % func_name)
            lines.append("    .byte 2  /* abbrev 2: subprogram with children */")
            lines.append('    .asciz "%s"' % func_name)
            lines.append("    .4byte 0x%08x  /* low_pc */" % abs_lp)
            lines.append("    .4byte 0x%08x  /* high_pc */" % abs_hp)
            # frame_base = DW_OP_reg1 (r1 = stack pointer)
            lines.append("    .byte 1  /* frame_base block length */")
            lines.append("    .byte 0x51  /* DW_OP_reg1 */")

            for kind, var_name, ft, dw2_loc in children:
                # Determine type label
                type_label = default_type_label
                if ft is not None:
                    canon = FT_CANONICAL.get(ft, ft)
                    if canon in ft_labels:
                        type_label = ft_labels[canon]

                if dw2_loc is not None:
                    # Abbrev 4 (param) or 5 (variable) — with location
                    abbrev_code = 4 if kind == "param" else 5
                    lines.append("    .byte %d  /* %s: %s */" % (
                        abbrev_code, kind, var_name))
                    lines.append('    .asciz "%s"' % var_name)
                    lines.append("    .4byte %s - .Lcu_header  /* type ref */" %
                                 type_label)
                    # Location block
                    loc_bytes = ", ".join("0x%02x" % b for b in dw2_loc)
                    lines.append("    .byte %d  /* location block length */" %
                                 len(dw2_loc))
                    lines.append("    .byte %s" % loc_bytes)
                else:
                    # Abbrev 8 (param) or 9 (variable) — no location
                    abbrev_code = 8 if kind == "param" else 9
                    lines.append("    .byte %d  /* %s: %s (no loc) */" % (
                        abbrev_code, kind, var_name))
                    lines.append('    .asciz "%s"' % var_name)
                    lines.append("    .4byte %s - .Lcu_header  /* type ref */" %
                                 type_label)

                var_count += 1

            # End children
            lines.append("    .byte 0  /* end children */")
        else:
            # No children — use abbrev 3
            lines.append("    /* DW_TAG_subprogram: %s */" % func_name)
            lines.append("    .byte 3  /* abbrev 3: subprogram no children */")
            lines.append('    .asciz "%s"' % func_name)
            lines.append("    .4byte 0x%08x  /* low_pc */" % abs_lp)
            lines.append("    .4byte 0x%08x  /* high_pc */" % abs_hp)

        lines.append("")
        func_count += 1

    # End CU children
    lines.append("    .byte 0  /* end CU children */")
    lines.append(".Lcu_end:")

    with open(out_s, "w") as f:
        f.write("\n".join(lines) + "\n")

    return func_count, var_count


def assemble(out_s, out_o, label=""):
    """Assemble a .s file to .o using powerpc-eabi-as."""
    as_cmd = ["powerpc-eabi-as", "-o", out_o, out_s]
    result = subprocess.run(as_cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print("  Assembly failed for %s: %s" % (label or out_o,
              result.stderr.strip()))
        return False
    return True


# ---------------------------------------------------------------------------
# Main processing pipeline
# ---------------------------------------------------------------------------

def process_object(o_path, map_entries_for_obj):
    """Process a single .o file, return list of (global_lp, global_hp, name, children).

    map_entries_for_obj: [(map_start_addr, map_size), ...] from MAP file.
    """
    dies = parse_dwarf1_dies(o_path)
    if not dies:
        return []

    source_name, functions = extract_varinfo(dies)
    if not functions:
        return []

    result = []

    # Match functions to MAP entries by .text offset
    # MW objects have a single .text section, so all functions use map_entries[0]
    if not map_entries_for_obj:
        return []

    map_base = map_entries_for_obj[0][0]  # first .text entry's starting address

    for func in functions:
        global_lp = map_base + func["low_pc"]
        global_hp = map_base + func["high_pc"]

        # Convert DWARF 1 locations to DWARF 2
        converted_children = []
        for kind, name, ft, loc in func["children"]:
            dw2_loc = None
            if isinstance(loc, bytes):
                dw2_loc = convert_location(loc)
            converted_children.append((kind, name, ft, dw2_loc))

        result.append((global_lp, global_hp, func["name"], converted_children))

    return result


def generate_varinfo_obj(map_path, o_index, out_s, out_o, build_dir,
                          text_base, label=""):
    """Generate a debug_varinfo.o from a MAP file and .o file index.

    Returns (n_funcs, n_vars, n_skipped) or None.
    """
    obj_offsets = parse_map_file(map_path)
    if not obj_offsets:
        return None

    all_functions = []
    skipped = 0
    processed = 0

    for obj_basename, map_entries in obj_offsets.items():
        if obj_basename not in o_index:
            skipped += 1
            continue

        o_path = o_index[obj_basename]
        funcs = process_object(o_path, map_entries)
        if funcs:
            all_functions.extend(funcs)
            processed += 1
        else:
            skipped += 1

    if not all_functions:
        return None

    result = generate_varinfo_asm(all_functions, text_base, out_s)
    if not result:
        return None

    func_count, var_count = result

    if not assemble(out_s, out_o, label):
        return None

    return (func_count, var_count, skipped)


def main():
    if len(sys.argv) < 2:
        print("Usage: %s <build_dir>" % sys.argv[0])
        print("  e.g. %s build/GZ2E01" % sys.argv[0])
        sys.exit(1)

    build_dir = os.path.abspath(sys.argv[1])

    # --- DOL ---
    dol_map = os.path.join(build_dir, "framework.elf.MAP")
    elf_path = os.path.join(build_dir, "framework.elf")
    dol_s = os.path.join(build_dir, "debug_varinfo.s")
    dol_o = os.path.join(build_dir, "debug_varinfo.o")

    if not os.path.exists(dol_map):
        print("Error: MAP file not found: %s" % dol_map)
        sys.exit(1)

    if not os.path.exists(elf_path):
        print("Error: ELF not found: %s" % elf_path)
        sys.exit(1)

    text_base = get_text_base(elf_path)
    if text_base is None:
        print("Error: could not read .text base from %s" % elf_path)
        sys.exit(1)

    print("DOL .text base: 0x%08X" % text_base)

    o_index = build_o_index([build_dir])

    result = generate_varinfo_obj(dol_map, o_index, dol_s, dol_o, build_dir,
                                   text_base, "DOL")
    if result:
        func_count, var_count, skipped = result
        print("DOL: %d functions, %d params/vars (%d objects skipped)" %
              (func_count, var_count, skipped))
    else:
        print("DOL: no variable info found")

    # --- RELs ---
    rel_count = 0
    rel_skipped = 0

    for entry in sorted(os.listdir(build_dir)):
        module_dir = os.path.join(build_dir, entry)
        if not os.path.isdir(module_dir):
            continue

        plf_map = os.path.join(module_dir, "%s.plf.MAP" % entry)
        plf_path = os.path.join(module_dir, "%s.plf" % entry)
        if not os.path.exists(plf_map):
            continue

        rel_text_base = get_text_base(plf_path) if os.path.exists(plf_path) else 0
        if rel_text_base is None:
            rel_text_base = 0

        rel_s = os.path.join(module_dir, "debug_varinfo.s")
        rel_o = os.path.join(module_dir, "debug_varinfo.o")

        rel_o_index = build_o_index([
            os.path.join(build_dir, "src"),
            os.path.join(module_dir, "obj"),
        ])

        result = generate_varinfo_obj(plf_map, rel_o_index, rel_s, rel_o,
                                       build_dir, rel_text_base, entry)
        if result:
            rel_count += 1
        else:
            rel_skipped += 1
            for p in (rel_s, rel_o):
                if os.path.exists(p):
                    os.remove(p)

    print("RELs: %d with varinfo, %d without" % (rel_count, rel_skipped))


if __name__ == "__main__":
    main()
