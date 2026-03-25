#!/usr/bin/env python3
"""Generate load_rel_symbols.py (Python GDB extension) from config.json and PLF ELF headers."""

import json
import os
import struct
import sys


# REL section index -> ELF section name
REL_SECTIONS = {
    1: ".text",
    4: ".rodata",
    5: ".data",
    6: ".bss",
}


def get_elf_sections(plf_path):
    """Parse ELF section headers and return set of section names."""
    sections = set()
    try:
        with open(plf_path, "rb") as f:
            magic = f.read(4)
            if magic != b"\x7fELF":
                return sections
            f.seek(0)
            ehdr = f.read(52)  # ELF32 header
            e_shoff = struct.unpack(">I", ehdr[32:36])[0]
            e_shentsize = struct.unpack(">H", ehdr[46:48])[0]
            e_shnum = struct.unpack(">H", ehdr[48:50])[0]
            e_shstrndx = struct.unpack(">H", ehdr[50:52])[0]

            # Read section header string table
            f.seek(e_shoff + e_shstrndx * e_shentsize)
            shstrtab_hdr = f.read(e_shentsize)
            strtab_off = struct.unpack(">I", shstrtab_hdr[16:20])[0]
            strtab_size = struct.unpack(">I", shstrtab_hdr[20:24])[0]
            f.seek(strtab_off)
            strtab = f.read(strtab_size)

            # Read each section header
            for i in range(e_shnum):
                f.seek(e_shoff + i * e_shentsize)
                shdr = f.read(e_shentsize)
                sh_name_idx = struct.unpack(">I", shdr[0:4])[0]
                # Extract null-terminated string
                end = strtab.index(b"\x00", sh_name_idx)
                name = strtab[sh_name_idx:end].decode("ascii", errors="replace")
                if name:
                    sections.add(name)
    except Exception:
        pass
    return sections


def get_elf_text_base(elf_path):
    """Get the .text section virtual address from an ELF file."""
    try:
        with open(elf_path, "rb") as f:
            magic = f.read(4)
            if magic != b"\x7fELF":
                return None
            f.seek(0)
            ehdr = f.read(52)
            e_shoff = struct.unpack(">I", ehdr[32:36])[0]
            e_shentsize = struct.unpack(">H", ehdr[46:48])[0]
            e_shnum = struct.unpack(">H", ehdr[48:50])[0]
            e_shstrndx = struct.unpack(">H", ehdr[50:52])[0]

            f.seek(e_shoff + e_shstrndx * e_shentsize)
            shstrtab_hdr = f.read(e_shentsize)
            strtab_off = struct.unpack(">I", shstrtab_hdr[16:20])[0]
            strtab_size = struct.unpack(">I", shstrtab_hdr[20:24])[0]
            f.seek(strtab_off)
            strtab = f.read(strtab_size)

            for i in range(e_shnum):
                f.seek(e_shoff + i * e_shentsize)
                shdr = f.read(e_shentsize)
                sh_name_idx = struct.unpack(">I", shdr[0:4])[0]
                end = strtab.index(b"\x00", sh_name_idx)
                name = strtab[sh_name_idx:end].decode("ascii", errors="replace")
                if name == ".text":
                    sh_addr = struct.unpack(">I", shdr[12:16])[0]
                    return sh_addr
    except Exception:
        pass
    return None


def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    repo_root = os.path.dirname(script_dir)

    if len(sys.argv) < 2:
        print("Usage: %s <build_dir>" % sys.argv[0])
        sys.exit(1)
    build_dir = os.path.abspath(sys.argv[1])

    config_path = os.path.join(build_dir, "config.json")
    if not os.path.exists(config_path):
        print("Error: config.json not found at %s" % config_path)
        sys.exit(1)

    with open(config_path) as f:
        cfg = json.load(f)

    # Build module_id -> (plf_path, set of section names, debug_o)
    modules = {}
    for m in cfg.get("modules", []):
        mid = m.get("module_id")
        name = m.get("name")
        if mid is not None and name:
            plf = os.path.join(build_dir, name, "%s.plf" % name).replace("\\", "/")
            if os.path.exists(plf):
                elf_sections = get_elf_sections(plf)
                debug_o = os.path.join(build_dir, name, "debug_info.o").replace("\\", "/")
                if not os.path.exists(debug_o):
                    debug_o = None
                modules[mid] = (plf, elf_sections, debug_o)

    modules_with_debug = {
        mid: debug_o
        for mid, (plf, elf_sections, debug_o) in modules.items()
        if debug_o
    }

    # Build module_names for dbg-<name> convenience commands
    module_names = {}  # mid -> name
    for m in cfg.get("modules", []):
        mid = m.get("module_id")
        name = m.get("name")
        if mid in modules_with_debug and name:
            module_names[mid] = name

    elf_path = os.path.join(build_dir, "framework.elf").replace("\\", "/")
    debug_o_path = os.path.join(build_dir, "debug_info.o").replace("\\", "/")
    has_debug = os.path.exists(debug_o_path)

    out_path = os.path.join(build_dir, "load_rel_symbols.py")

    with open(out_path, "w") as f:
        f.write('# Auto-generated by gen_gdb_rel_loader.py - do not edit\n')
        f.write('# Source this file in GDB, then run: load-all-symbols\n')
        f.write('\n')
        f.write('import gdb\n')
        f.write('\n')

        # --- Helper ---
        f.write('def _read_u32(addr):\n')
        f.write('    return int(gdb.parse_and_eval("*(unsigned int*)%d" % addr))\n')
        f.write('\n')

        # --- Module data tables ---
        # REL_MODULES: mid -> (plf_path, [(sec_idx, sec_name), ...])
        f.write('REL_MODULES = {\n')
        for mid in sorted(modules.keys()):
            plf, elf_sections, debug_o = modules[mid]
            extra_secs = []
            for sec_idx, sec_name in sorted(REL_SECTIONS.items()):
                if sec_idx == 1:
                    continue
                if sec_name in elf_sections:
                    extra_secs.append((sec_idx, sec_name))
            f.write('    %d: (%r, %r),\n' % (mid, plf, extra_secs))
        f.write('}\n')
        f.write('\n')

        # DEBUG_MODULES: mid -> debug_o_path
        f.write('DEBUG_MODULES = {\n')
        for mid in sorted(modules_with_debug.keys()):
            f.write('    %d: %r,\n' % (mid, modules_with_debug[mid]))
        f.write('}\n')
        f.write('\n')

        # MODULE_NAMES: mid -> name (for dbg-<name> commands)
        f.write('MODULE_NAMES = {\n')
        for mid, name in sorted(module_names.items(), key=lambda x: x[1]):
            f.write('    %d: %r,\n' % (mid, name))
        f.write('}\n')
        f.write('\n')

        # --- load-dol-symbols ---
        f.write('class LoadDolSymbols(gdb.Command):\n')
        f.write('    """Load DOL (framework.elf) symbols."""\n')
        f.write('    def __init__(self):\n')
        f.write('        super().__init__("load-dol-symbols", gdb.COMMAND_USER)\n')
        f.write('    def invoke(self, arg, from_tty):\n')
        f.write('        gdb.execute("symbol-file %s")\n' % elf_path)
        if has_debug:
            f.write('        gdb.execute("add-symbol-file %s 0")\n' % debug_o_path)
            f.write('        print("Loaded DOL symbols + debug info")\n')
        else:
            f.write('        print("Loaded DOL symbols")\n')
        f.write('LoadDolSymbols()\n')
        f.write('\n')

        # --- load-rel-symbols ---
        f.write('def _load_rel(mid, ns, si):\n')
        f.write('    if mid not in REL_MODULES:\n')
        f.write('        return False\n')
        f.write('    plf, extra_secs = REL_MODULES[mid]\n')
        f.write('    t = _read_u32(si + 8) & ~1\n')
        f.write('    ts = _read_u32(si + 12)\n')
        f.write('    if t == 0 or ts == 0:\n')
        f.write('        return False\n')
        f.write('    cmd = "add-symbol-file %s 0x%x" % (plf, t)\n')
        f.write('    for sec_idx, sec_name in extra_secs:\n')
        f.write('        if ns > sec_idx:\n')
        f.write('            addr = _read_u32(si + sec_idx * 8) & ~1\n')
        f.write('            cmd += " -s %s 0x%x" % (sec_name, addr)\n')
        f.write('    gdb.execute(cmd)\n')
        f.write('    return True\n')
        f.write('\n')

        f.write('def _walk_modules():\n')
        f.write('    """Walk the OS module linked list. Yields (mid, ns, si) tuples."""\n')
        f.write('    mod = _read_u32(0x800030C8)\n')
        f.write('    while mod != 0:\n')
        f.write('        mid = _read_u32(mod)\n')
        f.write('        nxt = _read_u32(mod + 4)\n')
        f.write('        ns = _read_u32(mod + 0x0C)\n')
        f.write('        si = _read_u32(mod + 0x10)\n')
        f.write('        yield (mid, ns, si)\n')
        f.write('        mod = nxt\n')
        f.write('\n')

        f.write('class LoadRelSymbols(gdb.Command):\n')
        f.write('    """Walk the OS module list and load PLF symbols for each REL."""\n')
        f.write('    def __init__(self):\n')
        f.write('        super().__init__("load-rel-symbols", gdb.COMMAND_USER)\n')
        f.write('    def invoke(self, arg, from_tty):\n')
        f.write('        gdb.execute("set confirm off")\n')
        f.write('        loaded = 0\n')
        f.write('        for mid, ns, si in _walk_modules():\n')
        f.write('            if _load_rel(mid, ns, si):\n')
        f.write('                loaded += 1\n')
        f.write('        gdb.execute("set confirm on")\n')
        f.write('        print("Loaded %d REL modules" % loaded)\n')
        f.write('LoadRelSymbols()\n')
        f.write('\n')

        # --- load-debug-for ---
        f.write('class LoadDebugFor(gdb.Command):\n')
        f.write('    """Load debug info for a REL module by ID. Usage: load-debug-for <module_id>"""\n')
        f.write('    def __init__(self):\n')
        f.write('        super().__init__("load-debug-for", gdb.COMMAND_USER)\n')
        f.write('    def invoke(self, arg, from_tty):\n')
        f.write('        target_id = int(gdb.parse_and_eval(arg))\n')
        f.write('        if target_id not in DEBUG_MODULES:\n')
        f.write('            print("Module %d has no debug info" % target_id)\n')
        f.write('            return\n')
        f.write('        gdb.execute("set confirm off")\n')
        f.write('        loaded = False\n')
        f.write('        for mid, ns, si in _walk_modules():\n')
        f.write('            if mid != target_id:\n')
        f.write('                continue\n')
        f.write('            t = _read_u32(si + 8) & ~1\n')
        f.write('            ts = _read_u32(si + 12)\n')
        f.write('            if t != 0 and ts != 0:\n')
        f.write('                gdb.execute("add-symbol-file %s 0" % DEBUG_MODULES[mid])\n')
        f.write('                loaded = True\n')
        f.write('            break\n')
        f.write('        gdb.execute("set confirm on")\n')
        f.write('        if not loaded:\n')
        f.write('            print("Module %d not found in module list" % target_id)\n')
        f.write('LoadDebugFor()\n')
        f.write('\n')

        # --- dbg-<name> convenience commands ---
        f.write('class _DbgModule(gdb.Command):\n')
        f.write('    def __init__(self, name, mid):\n')
        f.write('        super().__init__("dbg-%s" % name, gdb.COMMAND_USER)\n')
        f.write('        self._mid = mid\n')
        f.write('    def invoke(self, arg, from_tty):\n')
        f.write('        gdb.execute("load-debug-for %d" % self._mid)\n')
        f.write('\n')
        f.write('for _mid, _name in MODULE_NAMES.items():\n')
        f.write('    _DbgModule(_name, _mid)\n')
        f.write('\n')

        # --- load-all-symbols ---
        f.write('class LoadAllSymbols(gdb.Command):\n')
        f.write('    """Load DOL + all REL symbols."""\n')
        f.write('    def __init__(self):\n')
        f.write('        super().__init__("load-all-symbols", gdb.COMMAND_USER)\n')
        f.write('    def invoke(self, arg, from_tty):\n')
        f.write('        gdb.execute("load-dol-symbols")\n')
        f.write('        gdb.execute("load-rel-symbols")\n')
        f.write('LoadAllSymbols()\n')
        f.write('\n')

        # --- Auto-load on first stop (for DAP mode) ---
        f.write('def _auto_load_on_stop(event):\n')
        f.write('    gdb.events.stop.disconnect(_auto_load_on_stop)\n')
        f.write('    try:\n')
        f.write('        gdb.execute("load-all-symbols")\n')
        f.write('    except Exception as e:\n')
        f.write('        print("Auto-load symbols failed: %s" % e)\n')
        f.write('gdb.events.stop.connect(_auto_load_on_stop)\n')

    # Generate .gdbinit in repo root (gitignored)
    gdbinit_path = os.path.join(repo_root, ".gdbinit")
    with open(gdbinit_path, "w") as f:
        f.write("set confirm off\n")
        f.write("source %s\n" % out_path)

    # Generate GDB wrapper script for VS Code DAP.
    # The gdb-dap extension may not set CWD to the workspace folder, so
    # GDB wouldn't find .gdbinit.  The wrapper ensures GDB starts in the
    # repo root.
    binutils_dir = os.path.join(repo_root, "build", "binutils")
    gdb_binary = os.path.join(binutils_dir, "powerpc-eabi-gdb")
    wrapper_path = os.path.join(binutils_dir, "gdb-wrapper.sh")
    with open(wrapper_path, "w") as f:
        f.write("#!/bin/bash\n")
        f.write('cd "%s"\n' % repo_root)
        f.write('exec "%s" "$@"\n' % gdb_binary)
    os.chmod(wrapper_path, 0o755)

    print("Generated %s (%d module mappings)" % (out_path, len(modules)))


if __name__ == "__main__":
    main()
