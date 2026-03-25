#!/usr/bin/env python3
"""Convert DWARF 1 debug info from MW .o files into a combined DWARF 2 object.

mwcceppc emits DWARF 1.1 (.line/.debug sections) which GDB 8.2+ cannot
read.  This script parses both line tables and variable/type info from each .o,
cross-references with the linker MAP, and generates a single .o file containing:
  - .debug_line  (line number tables)
  - .debug_info  (CU + subprogram/variable DIEs)
  - .debug_abbrev

All in one CU so GDB can resolve both line info and variable info for the same
address range without conflicts.

Processes both the DOL (framework.elf) and all REL modules.

Usage:
    python3 tools/gen_dwarf2_debug.py <build_dir>
    # e.g. python3 tools/gen_dwarf2_debug.py build/GZ2E01
"""

import bisect
import os
import re
import struct
import subprocess
import sys


# ---------------------------------------------------------------------------
# DWARF 1 constants (TIS DWARF 1 spec — used by MetroWerks)
# ---------------------------------------------------------------------------

DW1_TAG_COMPILE_UNIT = 0x0011
DW1_TAG_GLOBAL_SUBR = 0x0006
DW1_TAG_SUBROUTINE = 0x0014
DW1_TAG_FORMAL_PARAM = 0x0005
DW1_TAG_LOCAL_VAR = 0x000C

DW1_AT_SIBLING = 0x0010
DW1_AT_LOCATION = 0x0020
DW1_AT_NAME = 0x0030
DW1_AT_FUND_TYPE = 0x0050
DW1_AT_LOW_PC = 0x0110
DW1_AT_HIGH_PC = 0x0120
DW1_AT_MW_MANGLED = 0x2000

AT_NAME_WITH_STRING = 0x0038  # AT_name | FORM_STRING

# Location ops
DW1_OP_REG = 0x01
DW1_OP_BASEREG = 0x02
DW1_OP_ADDR = 0x03
DW1_OP_CONST = 0x04

# Form sizes
FORM_SIZES = {0x1: 4, 0x2: 4, 0x5: 2, 0x6: 4, 0x7: 8}

# Fundamental types: ft_code -> (name, byte_size, DW_ATE_encoding)
FT_INFO = {
    0x01: ("char", 1, 0x06),
    0x02: ("signed char", 1, 0x06),
    0x03: ("unsigned char", 1, 0x08),
    0x04: ("short", 2, 0x05),
    0x05: ("signed short", 2, 0x05),
    0x06: ("unsigned short", 2, 0x07),
    0x07: ("int", 4, 0x05),
    0x08: ("signed int", 4, 0x05),
    0x09: ("unsigned int", 4, 0x07),
    0x0A: ("long", 4, 0x05),
    0x0B: ("signed long", 4, 0x05),
    0x0C: ("unsigned long", 4, 0x07),
    0x0D: ("void *", 4, 0x01),
    0x0E: ("float", 4, 0x04),
    0x0F: ("double", 8, 0x04),
    0x14: ("void", 0, 0x00),
    0x15: ("bool", 1, 0x02),
}

FT_CANONICAL = {
    0x02: 0x01, 0x05: 0x04, 0x08: 0x07, 0x0B: 0x0A,
}


# ---------------------------------------------------------------------------
# ELF parsing
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
    """Parse ELF returning (section_list, section_dict)."""
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
            end_idx = strtab.index(b"\x00", name_idx)
            name = strtab[name_idx:end_idx].decode("ascii", errors="replace")
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
# MAP file parsing
# ---------------------------------------------------------------------------

def parse_map_file(map_path):
    """Parse MAP file .text section layout.

    Returns (obj_offsets, obj_func_map) where:
      obj_offsets: {obj_basename: [(starting_address, size), ...]} (alignment-1)
      obj_func_map: {obj_basename: [(func_name, linked_offset, size), ...]} (alignment-4)
    """
    obj_offsets = {}
    obj_func_map = {}
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
                    elif alignment >= 4 and size > 0:
                        # Per-function entry: section_name is the symbol name
                        func_name = section_name
                        obj_func_map.setdefault(obj_name, []).append(
                            (func_name, start_addr, size)
                        )
    return obj_offsets, obj_func_map


def build_o_index(search_dirs):
    """Build {basename: path} index of .o files."""
    o_by_basename = {}
    for search_dir in search_dirs:
        if not os.path.isdir(search_dir):
            continue
        for dirpath, _, filenames in os.walk(search_dir):
            for fn in filenames:
                if fn.endswith(".o") and fn not in (
                    "debug_info.o", "debug_varinfo.o"
                ):
                    full = os.path.join(dirpath, fn)
                    if fn not in o_by_basename or (os.sep + "src" + os.sep) in full:
                        o_by_basename[fn] = full
    return o_by_basename


def read_o_text_symbols(o_path):
    """Read function symbols from .o ELF symbol table.

    Returns {symbol_name: offset_in_text} for defined function symbols
    in the .text section.
    """
    sec_list, sec_dict = read_elf_sections_detailed(o_path)
    if ".symtab" not in sec_dict:
        return {}

    text_shndx = None
    for i, (name, sh_type, sh_off, sh_size, sh_link, sh_addr) in enumerate(sec_list):
        if name == ".text":
            text_shndx = i
            break
    if text_shndx is None:
        return {}

    with open(o_path, "rb") as f:
        soff, ssz, _ = sec_dict[".symtab"]
        f.seek(soff)
        symtab_data = f.read(ssz)

        # Find strtab for symtab
        symtab_link = None
        for name, sh_type, sh_off, sh_size, sh_link, sh_addr in sec_list:
            if name == ".symtab":
                symtab_link = sh_link
                break
        if symtab_link is None:
            return {}

        st_off, st_sz, _ = sec_dict[sec_list[symtab_link][0]]
        f.seek(st_off)
        strtab_data = f.read(st_sz)

    result = {}
    n_syms = ssz // 16
    for i in range(n_syms):
        base = i * 16
        st_name_off = struct.unpack(">I", symtab_data[base:base+4])[0]
        st_value = struct.unpack(">I", symtab_data[base+4:base+8])[0]
        st_info = symtab_data[base + 12]
        st_shndx = struct.unpack(">H", symtab_data[base+14:base+16])[0]

        # STT_FUNC = 2, STT_OBJECT can also be in .text for some compilers
        sym_type = st_info & 0xF
        if st_shndx == text_shndx and sym_type == 2:  # STT_FUNC
            end = strtab_data.index(b"\x00", st_name_off)
            sym_name = strtab_data[st_name_off:end].decode("ascii", errors="replace")
            if sym_name:
                result[sym_name] = st_value
    return result


def build_remap_table(o_path, map_funcs):
    """Build a remapping table for function-level address correction.

    The MW linker can reorder functions within an .o file (e.g., moving
    __sinit_* to the end).  The .line section pc_addresses reflect the
    original .o layout, so we need per-function deltas to compute the
    correct linked addresses.

    Returns (remap_offsets, remap_deltas) — parallel sorted lists — or
    (None, None) if the remap can't be built.
    """
    if not map_funcs:
        return None, None

    o_syms = read_o_text_symbols(o_path)
    if not o_syms:
        return None, None

    map_by_name = {name: off for name, off, sz in map_funcs}

    pairs = []  # (o_offset, linked_offset)
    for sym_name, o_off in o_syms.items():
        if sym_name in map_by_name:
            pairs.append((o_off, map_by_name[sym_name]))

    if not pairs:
        return None, None

    pairs.sort()
    remap_offsets = [p[0] for p in pairs]
    remap_deltas = [p[1] - p[0] for p in pairs]
    return remap_offsets, remap_deltas


def remap_pc(pc_addr, remap_offsets, remap_deltas, fallback_offset):
    """Remap a .o-relative pc_addr to a linked .text offset.

    Uses binary search on remap_offsets to find the function containing
    pc_addr, then applies that function's delta.
    """
    if remap_offsets is None:
        return fallback_offset + pc_addr

    idx = bisect.bisect_right(remap_offsets, pc_addr) - 1
    if idx < 0:
        return fallback_offset + pc_addr

    return pc_addr + remap_deltas[idx]


# ---------------------------------------------------------------------------
# DWARF 1 .line section parsing
# ---------------------------------------------------------------------------

def parse_dwarf1_source_name(f, debug_off, debug_size):
    """Extract AT_name (source filename) from first compile_unit DIE."""
    f.seek(debug_off)
    if debug_size < 6:
        return None

    die_len = struct.unpack(">I", f.read(4))[0]
    tag = struct.unpack(">H", f.read(2))[0]
    if tag != DW1_TAG_COMPILE_UNIT:
        return None

    die_end = debug_off + 4 + die_len
    while f.tell() < die_end:
        if f.tell() + 2 > die_end:
            break
        attr_word = struct.unpack(">H", f.read(2))[0]
        if attr_word == 0:
            break
        form = attr_word & 0xF

        if attr_word == AT_NAME_WITH_STRING:
            chars = []
            while True:
                c = f.read(1)
                if c == b"\x00" or c == b"":
                    break
                chars.append(c)
            return b"".join(chars).decode("ascii", errors="replace")

        if form == 0x8:
            while True:
                c = f.read(1)
                if c == b"\x00" or c == b"":
                    break
        elif form == 0x3:
            blen = struct.unpack(">H", f.read(2))[0]
            f.seek(blen, 1)
        elif form == 0x4:
            blen = struct.unpack(">I", f.read(4))[0]
            f.seek(blen, 1)
        elif form in FORM_SIZES:
            f.seek(FORM_SIZES[form], 1)
        else:
            break
    return None


def parse_dwarf1_line(f, line_off, line_size):
    """Parse DWARF 1 .line section.

    Returns list of entry-lists per sub-section:
        [[(line_number, pc_address), ...], ...]
    """
    all_subsections = []
    if line_size < 8:
        return all_subsections

    offset = 0
    while offset + 8 <= line_size:
        f.seek(line_off + offset)
        total_length = struct.unpack(">I", f.read(4))[0]
        _base_address = struct.unpack(">I", f.read(4))[0]
        if total_length < 8:
            break

        entries = []
        pos = 8
        while pos + 10 <= total_length:
            line_no = struct.unpack(">I", f.read(4))[0]
            src_idx = struct.unpack(">H", f.read(2))[0]
            pc_addr = struct.unpack(">I", f.read(4))[0]
            pos += 10
            if line_no == 0:
                break
            if src_idx == 0xFFFF:
                entries.append((line_no, pc_addr))
        all_subsections.append(entries)
        offset += total_length
    return all_subsections


def parse_object_lines(o_path):
    """Parse DWARF 1 line info from a .o file.

    Returns (source_name, [[(line, pc), ...], ...])
    """
    sections = read_elf_sections(o_path)
    if ".line" not in sections or ".debug" not in sections:
        return None, []

    line_off, line_size, _ = sections[".line"]
    debug_off, debug_size, _ = sections[".debug"]

    with open(o_path, "rb") as f:
        source_name = parse_dwarf1_source_name(f, debug_off, debug_size)
        line_subsections = parse_dwarf1_line(f, line_off, line_size)
    return source_name, line_subsections


# ---------------------------------------------------------------------------
# DWARF 1 .debug section parsing (variable/type info)
# ---------------------------------------------------------------------------

def parse_dwarf1_dies(o_path):
    """Parse DWARF 1 .debug section with relocations.

    Returns list of DIEs: [(offset, tag, attrs_dict, sibling_offset), ...]
    """
    sec_list, sec_dict = read_elf_sections_detailed(o_path)
    if ".debug" not in sec_dict or ".rela.debug" not in sec_dict:
        return []

    with open(o_path, "rb") as f:
        doff, dsz, _ = sec_dict[".debug"]
        f.seek(doff)
        debug_data = f.read(dsz)

        roff, rsz, _ = sec_dict[".rela.debug"]
        f.seek(roff)
        rela_data = f.read(rsz)

        if ".symtab" not in sec_dict:
            return []
        soff, ssz, _ = sec_dict[".symtab"]
        f.seek(soff)
        symtab_data = f.read(ssz)

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

    n_syms = ssz // 16
    symbols = []
    for i in range(n_syms):
        st_name_off = struct.unpack(">I", symtab_data[i*16:i*16+4])[0]
        st_value = struct.unpack(">I", symtab_data[i*16+4:i*16+8])[0]
        st_shndx = struct.unpack(">H", symtab_data[i*16+14:i*16+16])[0]
        end_idx = sym_strtab.index(b"\x00", st_name_off)
        sym_name = sym_strtab[st_name_off:end_idx].decode("ascii", errors="replace")
        symbols.append((sym_name, st_value, st_shndx))

    debug_shndx = None
    text_shndx = None
    for i, (name, sh_type, sh_off, sh_size, sh_link, sh_addr) in enumerate(sec_list):
        if name == ".debug":
            debug_shndx = i
        elif name == ".text" and text_shndx is None:
            text_shndx = i

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
        elif sym_shndx == debug_shndx:
            rela_map[r_off] = ("debug", resolved_value)
        else:
            section_name = sec_list[sym_shndx][0] if sym_shndx < len(sec_list) else "?"
            rela_map[r_off] = (section_name, resolved_value)

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

            if form == 0x8:
                start = pos
                while pos < die_end and debug_data[pos] != 0:
                    pos += 1
                value = debug_data[start:pos].decode("ascii", errors="replace")
                pos += 1
            elif form == 0x3:
                blen = struct.unpack(">H", debug_data[pos:pos+2])[0]
                pos += 2
                value = bytes(debug_data[pos:pos+blen])
                pos += blen
            elif form == 0x4:
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
                if value_pos in rela_map:
                    section, resolved = rela_map[value_pos]
                    value = (section, resolved)
                pos += sz
            else:
                break
            attrs[attr_base] = value

        sibling_offset = None
        sib = attrs.get(DW1_AT_SIBLING)
        if isinstance(sib, tuple) and sib[0] == "debug":
            sibling_offset = sib[1]

        dies.append((die_start, tag, attrs, sibling_offset))
        pos = die_end
    return dies


def extract_varinfo(dies):
    """Extract functions, parameters, and local variables from parsed DIEs.

    Returns (source_name, functions_list).
    """
    source_name = None
    functions = []
    current_func = None
    current_func_end = None

    for die_start, tag, attrs, sibling_offset in dies:
        if tag == DW1_TAG_COMPILE_UNIT:
            source_name = attrs.get(DW1_AT_NAME)
            continue

        if tag in (DW1_TAG_GLOBAL_SUBR, DW1_TAG_SUBROUTINE):
            name = attrs.get(DW1_AT_NAME, "")
            low_pc = attrs.get(DW1_AT_LOW_PC)
            high_pc = attrs.get(DW1_AT_HIGH_PC)
            lp = low_pc[1] if isinstance(low_pc, tuple) and low_pc[0] == "text" else None
            hp = high_pc[1] if isinstance(high_pc, tuple) and high_pc[0] == "text" else None
            if lp is not None and hp is not None:
                current_func = {"name": name, "low_pc": lp, "high_pc": hp, "children": []}
                current_func_end = sibling_offset
                functions.append(current_func)
            else:
                current_func = None
                current_func_end = None
            continue

        if current_func is None:
            continue
        if current_func_end is not None and die_start >= current_func_end:
            current_func = None
            current_func_end = None
            continue

        if tag == DW1_TAG_FORMAL_PARAM:
            name = attrs.get(DW1_AT_NAME)
            if name:
                current_func["children"].append(
                    ("param", name, attrs.get(DW1_AT_FUND_TYPE), attrs.get(DW1_AT_LOCATION)))
        elif tag == DW1_TAG_LOCAL_VAR:
            name = attrs.get(DW1_AT_NAME)
            if name:
                current_func["children"].append(
                    ("local", name, attrs.get(DW1_AT_FUND_TYPE), attrs.get(DW1_AT_LOCATION)))

    return source_name, functions


# ---------------------------------------------------------------------------
# DWARF 1 -> DWARF 2 location conversion
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


def uleb128_bytes(value):
    """Encode an unsigned value as ULEB128."""
    result = []
    while True:
        byte = value & 0x7F
        value >>= 7
        if value:
            byte |= 0x80
        result.append(byte)
        if not value:
            break
    return bytes(result)


def convert_location(loc_block):
    """Convert DWARF 1 location expression to DWARF 2 bytes."""
    if not loc_block or len(loc_block) < 1:
        return None
    op = loc_block[0]

    if op == DW1_OP_REG and len(loc_block) >= 5:
        regnum = struct.unpack(">I", loc_block[1:5])[0]
        if regnum < 32:
            return bytes([0x50 + regnum])
        result = [0x90]
        result.extend(uleb128_bytes(regnum))
        return bytes(result)

    elif op == DW1_OP_BASEREG and len(loc_block) >= 5:
        regnum = struct.unpack(">I", loc_block[1:5])[0]
        offset = 0
        if len(loc_block) >= 10 and loc_block[5] == DW1_OP_CONST:
            offset = struct.unpack(">I", loc_block[6:10])[0]
        if regnum < 32:
            return bytes([0x70 + regnum]) + sleb128_bytes(offset)

    elif op == DW1_OP_ADDR and len(loc_block) >= 5:
        addr = struct.unpack(">I", loc_block[1:5])[0]
        return bytes([0x03]) + struct.pack(">I", addr)

    return None


# ---------------------------------------------------------------------------
# LEB128 helpers for assembly output
# ---------------------------------------------------------------------------

def format_sleb128(value):
    """Return .byte directive string for SLEB128-encoded value."""
    data = sleb128_bytes(value)
    return ", ".join("0x%02x" % b for b in data)


def format_uleb128(value):
    """Return .byte directive string for ULEB128-encoded value."""
    data = uleb128_bytes(value)
    return ", ".join("0x%02x" % b for b in data)


# ---------------------------------------------------------------------------
# Combined DWARF 2 assembly generation
# ---------------------------------------------------------------------------

def generate_combined_asm(line_entries, all_functions, file_table, text_base,
                          out_s):
    """Generate combined DWARF 2 assembly with line tables + variable info.

    line_entries: sorted [(global_pc, file_idx, line_no), ...]
    all_functions: sorted [(global_lp, global_hp, name, children), ...]
    file_table: {source_path: file_idx (1-based)}
    text_base: .text section virtual address (for absolute addresses)
    """
    lines = []
    lines.append("# Auto-generated combined DWARF 2 debug info — do not edit")
    lines.append("")

    # --- .debug_abbrev ---
    lines.append('    .section .debug_abbrev,"",@progbits')
    lines.append(".Labbrev_start:")

    # Abbrev 1: DW_TAG_compile_unit [has children]
    lines.append("    .byte 1")
    lines.append("    .byte 0x11")        # DW_TAG_compile_unit
    lines.append("    .byte 1")           # DW_CHILDREN_yes
    lines.append("    .byte 0x10, 0x06")  # DW_AT_stmt_list, DW_FORM_data4
    lines.append("    .byte 0x11, 0x01")  # DW_AT_low_pc, DW_FORM_addr
    lines.append("    .byte 0x12, 0x01")  # DW_AT_high_pc, DW_FORM_addr
    lines.append("    .byte 0x03, 0x08")  # DW_AT_name, DW_FORM_string
    lines.append("    .byte 0, 0")

    # Abbrev 2: DW_TAG_subprogram [has children] (with frame_base)
    lines.append("    .byte 2")
    lines.append("    .byte 0x2e")
    lines.append("    .byte 1")           # DW_CHILDREN_yes
    lines.append("    .byte 0x03, 0x08")  # DW_AT_name
    lines.append("    .byte 0x11, 0x01")  # DW_AT_low_pc
    lines.append("    .byte 0x12, 0x01")  # DW_AT_high_pc
    lines.append("    .byte 0x40, 0x0a")  # DW_AT_frame_base, DW_FORM_block1
    lines.append("    .byte 0, 0")

    # Abbrev 3: DW_TAG_subprogram [no children]
    lines.append("    .byte 3")
    lines.append("    .byte 0x2e")
    lines.append("    .byte 0")
    lines.append("    .byte 0x03, 0x08")
    lines.append("    .byte 0x11, 0x01")
    lines.append("    .byte 0x12, 0x01")
    lines.append("    .byte 0, 0")

    # Abbrev 4: DW_TAG_formal_parameter [no children] (with location)
    lines.append("    .byte 4")
    lines.append("    .byte 0x05")
    lines.append("    .byte 0")
    lines.append("    .byte 0x03, 0x08")  # DW_AT_name
    lines.append("    .byte 0x49, 0x13")  # DW_AT_type, DW_FORM_ref4
    lines.append("    .byte 0x02, 0x0a")  # DW_AT_location, DW_FORM_block1
    lines.append("    .byte 0, 0")

    # Abbrev 5: DW_TAG_variable [no children] (with location)
    lines.append("    .byte 5")
    lines.append("    .byte 0x34")
    lines.append("    .byte 0")
    lines.append("    .byte 0x03, 0x08")
    lines.append("    .byte 0x49, 0x13")
    lines.append("    .byte 0x02, 0x0a")
    lines.append("    .byte 0, 0")

    # Abbrev 6: DW_TAG_base_type [no children]
    lines.append("    .byte 6")
    lines.append("    .byte 0x24")
    lines.append("    .byte 0")
    lines.append("    .byte 0x03, 0x08")  # DW_AT_name
    lines.append("    .byte 0x0b, 0x0b")  # DW_AT_byte_size, DW_FORM_data1
    lines.append("    .byte 0x3e, 0x0b")  # DW_AT_encoding, DW_FORM_data1
    lines.append("    .byte 0, 0")

    # Abbrev 7: DW_TAG_pointer_type [no children]
    lines.append("    .byte 7")
    lines.append("    .byte 0x0f")
    lines.append("    .byte 0")
    lines.append("    .byte 0x0b, 0x0b")  # DW_AT_byte_size
    lines.append("    .byte 0x49, 0x13")  # DW_AT_type, DW_FORM_ref4
    lines.append("    .byte 0, 0")

    # Abbrev 8: DW_TAG_formal_parameter [no children] (no location)
    lines.append("    .byte 8")
    lines.append("    .byte 0x05")
    lines.append("    .byte 0")
    lines.append("    .byte 0x03, 0x08")
    lines.append("    .byte 0x49, 0x13")
    lines.append("    .byte 0, 0")

    # Abbrev 9: DW_TAG_variable [no children] (no location)
    lines.append("    .byte 9")
    lines.append("    .byte 0x34")
    lines.append("    .byte 0")
    lines.append("    .byte 0x03, 0x08")
    lines.append("    .byte 0x49, 0x13")
    lines.append("    .byte 0, 0")

    lines.append("    .byte 0")  # end abbrev table
    lines.append("")

    # --- Compute address range ---
    all_addrs = set()
    for pc, _, _ in line_entries:
        all_addrs.add(text_base + pc)
    for lp, hp, _, _ in all_functions:
        all_addrs.add(text_base + lp)
        all_addrs.add(text_base + hp)

    if all_addrs:
        min_addr = min(all_addrs)
        max_addr = max(all_addrs)
    else:
        min_addr = text_base
        max_addr = text_base

    # --- Collect used fundamental types ---
    used_ft = set()
    for _, _, _, children in all_functions:
        for kind, name, ft, loc in children:
            if ft is not None:
                used_ft.add(FT_CANONICAL.get(ft, ft))
    used_ft.add(0x0D)  # void* fallback

    # --- .debug_info ---
    lines.append('    .section .debug_info,"",@progbits')
    lines.append(".Lcu_header:")
    lines.append("    .4byte .Lcu_end - .Lcu_start")
    lines.append(".Lcu_start:")
    lines.append("    .2byte 2")
    lines.append("    .4byte .Labbrev_start")
    lines.append("    .byte 4")
    lines.append("")

    # CU DIE (abbrev 1)
    lines.append("    .byte 1")
    lines.append("    .4byte 0  /* DW_AT_stmt_list = offset 0 in .debug_line */")
    lines.append("    .4byte 0x%08x  /* DW_AT_low_pc */" % min_addr)
    lines.append("    .4byte 0x%08x  /* DW_AT_high_pc */" % max_addr)
    lines.append('    .asciz "debug"')
    lines.append("")

    # Base type DIEs
    ft_labels = {}
    for ft_code in sorted(used_ft):
        info = FT_INFO.get(ft_code)
        if info is None:
            continue
        ft_name, ft_size, ft_encoding = info
        label = ".Ltype_%02x" % ft_code
        ft_labels[ft_code] = label
        lines.append("%s:" % label)
        lines.append("    .byte 6")
        lines.append('    .asciz "%s"' % ft_name)
        lines.append("    .byte %d" % ft_size)
        lines.append("    .byte %d" % ft_encoding)
        lines.append("")

    default_type_label = ft_labels.get(0x0D, ".Ltype_0d")

    # Subprogram + variable DIEs
    func_count = 0
    var_count = 0
    for global_lp, global_hp, func_name, children in all_functions:
        abs_lp = text_base + global_lp
        abs_hp = text_base + global_hp
        has_children = len(children) > 0

        if has_children:
            lines.append("    .byte 2")
            lines.append('    .asciz "%s"' % func_name)
            lines.append("    .4byte 0x%08x" % abs_lp)
            lines.append("    .4byte 0x%08x" % abs_hp)
            lines.append("    .byte 1")      # frame_base block length
            lines.append("    .byte 0x51")   # DW_OP_reg1 (r1)

            for kind, var_name, ft, dw2_loc in children:
                type_label = default_type_label
                if ft is not None:
                    canon = FT_CANONICAL.get(ft, ft)
                    if canon in ft_labels:
                        type_label = ft_labels[canon]

                if dw2_loc is not None:
                    abbrev_code = 4 if kind == "param" else 5
                    lines.append("    .byte %d" % abbrev_code)
                    lines.append('    .asciz "%s"' % var_name)
                    lines.append("    .4byte %s - .Lcu_header" % type_label)
                    loc_bytes = ", ".join("0x%02x" % b for b in dw2_loc)
                    lines.append("    .byte %d" % len(dw2_loc))
                    lines.append("    .byte %s" % loc_bytes)
                else:
                    abbrev_code = 8 if kind == "param" else 9
                    lines.append("    .byte %d" % abbrev_code)
                    lines.append('    .asciz "%s"' % var_name)
                    lines.append("    .4byte %s - .Lcu_header" % type_label)
                var_count += 1

            lines.append("    .byte 0  /* end children */")
        else:
            lines.append("    .byte 3")
            lines.append('    .asciz "%s"' % func_name)
            lines.append("    .4byte 0x%08x" % abs_lp)
            lines.append("    .4byte 0x%08x" % abs_hp)

        func_count += 1

    lines.append("    .byte 0  /* end CU children */")
    lines.append(".Lcu_end:")
    lines.append("")

    # --- .debug_line (manually generated) ---
    sorted_files = sorted(file_table.items(), key=lambda x: x[1])

    lines.append('    .section .debug_line,"",@progbits')
    lines.append(".Ldl_unit_start:")
    lines.append("    .4byte .Ldl_unit_end - .Ldl_after_length")
    lines.append(".Ldl_after_length:")
    lines.append("    .2byte 2  /* DWARF version */")
    lines.append("    .4byte .Ldl_program - .Ldl_after_header_length")
    lines.append(".Ldl_after_header_length:")
    lines.append("    .byte 4   /* minimum_instruction_length */")
    lines.append("    .byte 1   /* default_is_stmt */")
    lines.append("    .byte 0   /* line_base (signed) */")
    lines.append("    .byte 1   /* line_range */")
    lines.append("    .byte 10  /* opcode_base */")
    # standard_opcode_lengths for opcodes 1-9
    lines.append("    .byte 0, 1, 1, 1, 1, 0, 0, 0, 1")
    # include_directories — empty
    lines.append("    .byte 0")
    # file_names
    for src_path, idx in sorted_files:
        lines.append('    .asciz "%s"' % src_path)
        lines.append("    .byte 0, 0, 0  /* dir=0, time=0, size=0 */")
    lines.append("    .byte 0  /* end file names */")

    # Line number program
    lines.append(".Ldl_program:")

    if line_entries:
        # Dedup and sort by address
        deduped = []
        prev_pc = -1
        for global_pc, file_idx, line_no in line_entries:
            abs_pc = text_base + global_pc
            if abs_pc <= prev_pc:
                continue
            deduped.append((abs_pc, file_idx, line_no))
            prev_pc = abs_pc

        cur_file = 1
        cur_line = 1
        cur_addr = 0

        for i, (abs_pc, file_idx, line_no) in enumerate(deduped):
            # Set file if changed
            if file_idx != cur_file:
                lines.append("    .byte 4  /* DW_LNS_set_file */")
                lines.append("    .byte %s" % format_uleb128(file_idx))
                cur_file = file_idx

            # Set address — use DW_LNE_set_address for first entry or when
            # gap is large; otherwise use DW_LNS_advance_pc
            if i == 0 or (abs_pc - cur_addr) > 0xFFFF:
                # DW_LNE_set_address
                lines.append("    .byte 0")
                lines.append("    .byte %s  /* length: 1+4 */" % format_uleb128(5))
                lines.append("    .byte 2  /* DW_LNE_set_address */")
                lines.append("    .4byte 0x%08x" % abs_pc)
            else:
                delta = abs_pc - cur_addr
                if delta > 0:
                    lines.append("    .byte 2  /* DW_LNS_advance_pc */")
                    lines.append("    .byte %s  /* advance %d instrs */" % (
                        format_uleb128(delta // 4), delta // 4))
            cur_addr = abs_pc

            # Advance line
            line_delta = line_no - cur_line
            if line_delta != 0:
                lines.append("    .byte 3  /* DW_LNS_advance_line */")
                lines.append("    .byte %s" % format_sleb128(line_delta))
            cur_line = line_no

            # Copy (emit row)
            lines.append("    .byte 1  /* DW_LNS_copy */")

        # End sequence
        lines.append("    .byte 0")
        lines.append("    .byte 1")
        lines.append("    .byte 1  /* DW_LNE_end_sequence */")

    lines.append(".Ldl_unit_end:")
    lines.append("")

    with open(out_s, "w") as f:
        f.write("\n".join(lines) + "\n")

    return func_count, var_count, len(line_entries)


# ---------------------------------------------------------------------------
# Processing pipeline
# ---------------------------------------------------------------------------

def process_object_varinfo(o_path, map_entries, remap_offsets=None,
                           remap_deltas=None):
    """Process a single .o for variable info.

    Returns list of (global_lp, global_hp, name, children).
    """
    dies = parse_dwarf1_dies(o_path)
    if not dies:
        return []

    _, functions = extract_varinfo(dies)
    if not functions or not map_entries:
        return []

    map_base = map_entries[0][0]
    result = []
    for func in functions:
        global_lp = remap_pc(func["low_pc"], remap_offsets, remap_deltas,
                             map_base)
        # Compute high_pc from function size to avoid remap boundary issues
        # (high_pc may fall exactly on the next function's start offset,
        # which would pick the wrong delta in remap_pc)
        func_size = func["high_pc"] - func["low_pc"]
        global_hp = global_lp + func_size
        converted = []
        for kind, name, ft, loc in func["children"]:
            dw2_loc = convert_location(loc) if isinstance(loc, bytes) else None
            converted.append((kind, name, ft, dw2_loc))
        result.append((global_lp, global_hp, func["name"], converted))
    return result


def generate_combined_obj(map_path, o_index, out_s, out_o, build_dir,
                          text_base, label="", as_cmd="powerpc-eabi-as"):
    """Generate a combined debug_info.o from MAP file and .o index.

    Returns (n_funcs, n_vars, n_lines, n_skipped) or None.
    """
    obj_offsets, obj_func_map = parse_map_file(map_path)
    if not obj_offsets:
        return None

    file_table = {}   # source_path -> file_index (1-based)
    all_line_entries = []  # [(global_pc, file_idx, line_no)]
    all_functions = []     # [(global_lp, global_hp, name, children)]
    skipped = 0
    processed = 0

    for obj_basename, map_entries in obj_offsets.items():
        if obj_basename not in o_index:
            skipped += 1
            continue

        o_path = o_index[obj_basename]

        # Build per-function remap table for this .o
        map_funcs = obj_func_map.get(obj_basename, [])
        remap_offsets, remap_deltas = build_remap_table(o_path, map_funcs)
        fallback_offset = map_entries[0][0]

        # --- Line info ---
        source_name, line_subsections = parse_object_lines(o_path)
        if source_name and line_subsections:
            o_rel_norm = os.path.relpath(o_path, build_dir)
            parts = o_rel_norm.split(os.sep)
            src_dir = os.path.join(*parts[:-1]) if len(parts) >= 2 else "."
            source_path = os.path.join(src_dir, source_name).replace("\\", "/")

            # The build system may strip prefixes (e.g. libs/dolphin/src/os/X.c
            # compiles to build/src/dolphin/os/X.o, giving src/dolphin/os/X.c).
            # Check if the path exists; if not, try libs/<lib>/src/<rest>.
            project_root = os.path.dirname(os.path.dirname(build_dir))
            if not os.path.exists(os.path.join(project_root, source_path)):
                sp_parts = source_path.split("/")
                if len(sp_parts) >= 3 and sp_parts[0] == "src":
                    libs_path = "libs/%s/src/%s" % (
                        sp_parts[1], "/".join(sp_parts[2:]))
                    if os.path.exists(os.path.join(project_root, libs_path)):
                        source_path = libs_path

            if source_path not in file_table:
                file_table[source_path] = len(file_table) + 1
            file_idx = file_table[source_path]

            # Process ALL subsections — remap handles function reordering
            for sub_entries in line_subsections:
                for line_no, pc_addr in sub_entries:
                    global_pc = remap_pc(pc_addr, remap_offsets,
                                         remap_deltas, fallback_offset)
                    all_line_entries.append((global_pc, file_idx, line_no))

        # --- Variable info ---
        funcs = process_object_varinfo(o_path, map_entries, remap_offsets,
                                       remap_deltas)
        if funcs:
            all_functions.extend(funcs)

        processed += 1

    if not all_line_entries and not all_functions:
        return None

    # Sort and deduplicate
    all_line_entries.sort(key=lambda e: e[0])
    all_functions.sort(key=lambda f: f[0])

    # Deduplicate functions with the same low_pc (e.g., template/inline
    # instantiations compiled into multiple .o files but linked once).
    # Keep the version with more children (more complete debug info).
    if all_functions:
        deduped = [all_functions[0]]
        for f in all_functions[1:]:
            if f[0] == deduped[-1][0]:  # same low_pc
                # Keep the one with more children
                if len(f[3]) > len(deduped[-1][3]):
                    deduped[-1] = f
            else:
                deduped.append(f)
        all_functions = deduped

    result = generate_combined_asm(
        all_line_entries, all_functions, file_table, text_base, out_s)
    if not result:
        return None

    func_count, var_count, line_count = result

    # Assemble
    as_cmd = [as_cmd, "-o", out_o, out_s]
    res = subprocess.run(as_cmd, capture_output=True, text=True)
    if res.returncode != 0:
        print("  Assembly failed for %s: %s" % (label or out_o, res.stderr.strip()))
        return None

    return (func_count, var_count, line_count, skipped)


def main():
    import argparse
    p = argparse.ArgumentParser()
    p.add_argument("build_dir")
    p.add_argument("--as", dest="assembler", default="powerpc-eabi-as",
                   help="path to powerpc-eabi-as")
    args = p.parse_args()

    build_dir = os.path.abspath(args.build_dir)
    assembler = args.assembler

    # --- DOL ---
    dol_map = os.path.join(build_dir, "framework.elf.MAP")
    elf_path = os.path.join(build_dir, "framework.elf")
    dol_s = os.path.join(build_dir, "debug_info.s")
    dol_o = os.path.join(build_dir, "debug_info.o")

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

    result = generate_combined_obj(dol_map, o_index, dol_s, dol_o, build_dir,
                                    text_base, "DOL", assembler)
    if result:
        func_count, var_count, line_count, skip = result
        print("DOL: %d functions, %d params/vars, %d line entries (%d skipped)" %
              (func_count, var_count, line_count, skip))
    else:
        print("DOL: no debug info found")

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

        rel_s = os.path.join(module_dir, "debug_info.s")
        rel_o = os.path.join(module_dir, "debug_info.o")

        rel_o_index = build_o_index([
            os.path.join(build_dir, "src"),
            os.path.join(module_dir, "obj"),
        ])

        result = generate_combined_obj(plf_map, rel_o_index, rel_s, rel_o,
                                        build_dir, rel_text_base, entry,
                                        assembler)
        if result:
            rel_count += 1
        else:
            rel_skipped += 1
            for p in (rel_s, rel_o):
                if os.path.exists(p):
                    os.remove(p)

    print("RELs: %d with debug info, %d without" % (rel_count, rel_skipped))


if __name__ == "__main__":
    main()
