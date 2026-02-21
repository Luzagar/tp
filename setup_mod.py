#!/usr/bin/env python3

"""
setup_mod.py — Scaffold a new mod fork based on the umbra mod base.

Usage:
    python3 setup_mod.py <mod_name>

This script:
1. Creates src/<mod_name>/ and include/<mod_name>/ directories
2. Generates mod_config.py with mod metadata and object lists
3. Generates stub source/header files with proper boilerplate
4. Applies core game hooks to decomp source files so the mod's
   execute(), draw(), and init() functions get called by the game loop
"""

import argparse
import os
import re
import sys
from pathlib import Path

SCRIPT_DIR = Path(__file__).parent.resolve()


def validate_mod_name(name: str) -> bool:
    """Mod name must be a valid C identifier (lowercase, underscores ok)."""
    return bool(re.match(r"^[a-z][a-z0-9_]*$", name))


def create_directories(mod_name: str) -> None:
    """Create the mod's source and include directories."""
    dirs = [
        SCRIPT_DIR / "src" / mod_name,
        SCRIPT_DIR / "include" / mod_name,
    ]
    for d in dirs:
        d.mkdir(parents=True, exist_ok=True)
        print(f"  Created {d.relative_to(SCRIPT_DIR)}/")


def generate_mod_config(mod_name: str) -> None:
    """Generate mod_config.py with mod metadata and object lists."""
    path = SCRIPT_DIR / "mod_config.py"
    if path.exists():
        print(f"  mod_config.py already exists, skipping")
        return

    content = f'''"""
mod_config.py — Mod configuration for '{mod_name}'.

This file is imported by configure.py to determine which custom objects
to compile and link into the DOL, and how to name the output ISO.
"""

# Display name used in ISO filename: <iso_prefix>-<version>.iso
iso_prefix = "{mod_name}"

# Mod source objects to compile (paths relative to src/).
# These are compiled with the same cflags as framework code and linked
# into the DOL after the vanilla game objects.
#
# Format: list of source file paths (relative to src/).
# .cpp and .c files are both supported.
mod_objects = [
    "{mod_name}/{mod_name}.cpp",
]

# Additional dependencies from the decomp that the mod needs but aren't
# already linked. For example, if the mod calls CARDDelete which isn't
# in the vanilla DOL link, add "dolphin/card/CARDDelete.c" here.
extra_objects = [
    "dolphin/card/CARDDelete.c",
]

# Umbra platform abstraction layer (always included).
umbra_objects = [
    "umbra/umbra_platform.cpp",
    "umbra/umbra_nintendont.cpp",
    "umbra/umbra_storage.cpp",
    "umbra/umbra_net.cpp",
]
'''
    path.write_text(content)
    print(f"  Generated mod_config.py")


def generate_header(mod_name: str) -> None:
    """Generate the main mod header file."""
    header_dir = SCRIPT_DIR / "include" / mod_name
    header_path = header_dir / f"{mod_name}.h"
    if header_path.exists():
        print(f"  include/{mod_name}/{mod_name}.h already exists, skipping")
        return

    guard = f"{mod_name.upper()}_H"
    content = f'''#ifndef {guard}
#define {guard}

#include "dolphin/types.h"

class {mod_name}Info {{
public:
    void startInit();
    void execute();
    void draw();

    bool isDisplay() const {{ return mDisplay; }}
    void setDisplay(bool d) {{ mDisplay = d; }}

private:
    bool mDisplay;
}};

extern {mod_name}Info g_{mod_name}Info;

#endif // {guard}
'''
    header_path.write_text(content)
    print(f"  Generated include/{mod_name}/{mod_name}.h")


def generate_source(mod_name: str) -> None:
    """Generate the main mod source file."""
    src_dir = SCRIPT_DIR / "src" / mod_name
    src_path = src_dir / f"{mod_name}.cpp"
    if src_path.exists():
        print(f"  src/{mod_name}/{mod_name}.cpp already exists, skipping")
        return

    content = f'''#include "d/dolzel.h" // IWYU pragma: keep

#ifndef __REVOLUTION_SDK__

#include "{mod_name}/{mod_name}.h"
#include "umbra/umbra_platform.h"
#include <dolphin/os.h>

{mod_name}Info g_{mod_name}Info;

void {mod_name}Info::startInit() {{
    UmbraPlatform platform = umbraDetectPlatform();
    OSReport("{mod_name}: init (platform=%d)\\n", platform);
}}

void {mod_name}Info::execute() {{
    // Called every frame before game actors execute.
    // Add mod logic here.
}}

void {mod_name}Info::draw() {{
    // Called every frame after game actors draw.
    // Add mod rendering here.
}}

#endif // !__REVOLUTION_SDK__
'''
    src_path.write_text(content)
    print(f"  Generated src/{mod_name}/{mod_name}.cpp")


# ---------------------------------------------------------------------------
# Game hook application
# ---------------------------------------------------------------------------

def apply_hook_f_pc_manager(mod_name: str) -> None:
    """
    Hook into f_pc/f_pc_manager.cpp:
    - Add #include for mod header
    - Call mod execute() before game actor execution
    - Call mod draw() after game actor drawing
    """
    path = SCRIPT_DIR / "src" / "f_pc" / "f_pc_manager.cpp"
    content = path.read_text()

    include_line = f'#include "{mod_name}/{mod_name}.h"'
    if include_line in content:
        print(f"  f_pc/f_pc_manager.cpp already hooked, skipping")
        return

    # Add include after the last existing #include
    last_include = content.rfind("#include")
    end_of_line = content.index("\n", last_include)
    content = content[:end_of_line + 1] + include_line + "\n" + content[end_of_line + 1:]

    # Hook execute: add g_<mod>Info.execute() before fpcEx_Handler
    old_execute = "            if (!fapGm_HIO_c::isCaptureScreen()) {\n                fpcEx_Handler((fpcLnIt_QueueFunc)fpcM_Execute);\n            }"
    new_execute = f"""            g_{mod_name}Info.execute();

            if (!fapGm_HIO_c::isCaptureScreen()) {{
                fpcEx_Handler((fpcLnIt_QueueFunc)fpcM_Execute);
            }}"""
    content = content.replace(old_execute, new_execute, 1)

    # Hook draw: add g_<mod>Info.draw() after fpcDw_Handler
    old_draw = "            if (!fapGm_HIO_c::isCaptureScreen() || fapGm_HIO_c::getCaptureScreenDivH() != 1) {\n                fpcDw_Handler((fpcDw_HandlerFuncFunc)fpcM_DrawIterater, (fpcDw_HandlerFunc)fpcM_Draw);\n            }\n\n            if (i_postExecuteFn != NULL) {"
    new_draw = f"""            if (!fapGm_HIO_c::isCaptureScreen() || fapGm_HIO_c::getCaptureScreenDivH() != 1) {{
                fpcDw_Handler((fpcDw_HandlerFuncFunc)fpcM_DrawIterater, (fpcDw_HandlerFunc)fpcM_Draw);
            }}

            g_{mod_name}Info.draw();

            if (i_postExecuteFn != NULL) {{"""
    content = content.replace(old_draw, new_draw, 1)

    path.write_text(content)
    print(f"  Hooked f_pc/f_pc_manager.cpp (execute + draw)")


def apply_hook_d_s_logo(mod_name: str) -> None:
    """
    Hook into d/d_s_logo.cpp:
    - Add #include for mod header
    - Call mod startInit() after all resources are loaded
    """
    path = SCRIPT_DIR / "src" / "d" / "d_s_logo.cpp"
    content = path.read_text()

    include_line = f'#include "{mod_name}/{mod_name}.h"'
    if include_line in content:
        print(f"  d/d_s_logo.cpp already hooked, skipping")
        return

    # Add include after the dolzel.h include
    old_inc = '#include "d/dolzel.h" // IWYU pragma: keep\n\n#include "d/d_s_logo.h"'
    new_inc = f'#include "d/dolzel.h" // IWYU pragma: keep\n\n#include "{mod_name}/{mod_name}.h"\n#include "d/d_s_logo.h"'
    content = content.replace(old_inc, new_inc, 1)

    # Add startInit() call right before setLogoScnFlag
    old_init = "            mDoRst::setLogoScnFlag(0);\n            mDoRst::setProgChgFlag(0);\n            mExecCommand = EXEC_SCENE_CHANGE;"
    new_init = f"            g_{mod_name}Info.startInit();\n            mDoRst::setLogoScnFlag(0);\n            mDoRst::setProgChgFlag(0);\n            mExecCommand = EXEC_SCENE_CHANGE;"
    content = content.replace(old_init, new_init, 1)

    path.write_text(content)
    print(f"  Hooked d/d_s_logo.cpp (startInit)")


def apply_hook_controller_pad(mod_name: str) -> None:
    """
    Hook into m_Do/m_Do_controller_pad.cpp:
    - Add #include for mod header
    - Add m_modPadInfo static member
    - Map port 1 inputs to mod pad info
    """
    path = SCRIPT_DIR / "src" / "m_Do" / "m_Do_controller_pad.cpp"
    content = path.read_text()

    include_line = f'#include "{mod_name}/{mod_name}.h"'
    if include_line in content:
        print(f"  m_Do/m_Do_controller_pad.cpp already hooked, skipping")
        return

    # Add include
    old_inc = '#include "m_Do/m_Do_controller_pad.h"'
    new_inc = f'#include "m_Do/m_Do_controller_pad.h"\n#include "{mod_name}/{mod_name}.h"'
    content = content.replace(old_inc, new_inc, 1)

    # Add m_modPadInfo declaration after m_debugCpadInfo
    old_decl = "interface_of_controller_pad mDoCPd_c::m_debugCpadInfo[4];"
    new_decl = f"interface_of_controller_pad mDoCPd_c::m_debugCpadInfo[4];\ninterface_of_controller_pad mDoCPd_c::m_modPadInfo;"
    content = content.replace(old_decl, new_decl, 1)

    # After the main pad read loop, add mod pad mapping.
    # Insert after the closing of the for loop in read().
    old_read_end = """        pad++;
        interface++;
#if DEBUG
        interface2++;
#endif
    }
}"""
    new_read_end = f"""        pad++;
        interface++;
#if DEBUG
        interface2++;
#endif
    }}

    if (m_gamePad[0] != NULL) {{
        convert(&m_modPadInfo, m_gamePad[0]);
        LRlockCheck(&m_modPadInfo);
    }}
}}"""
    content = content.replace(old_read_end, new_read_end, 1)

    path.write_text(content)

    # Also add the m_modPadInfo declaration to the header
    header_path = SCRIPT_DIR / "include" / "m_Do" / "m_Do_controller_pad.h"
    header = header_path.read_text()
    if "m_modPadInfo" not in header:
        old_debug = "    static interface_of_controller_pad m_debugCpadInfo[4];"
        new_debug = "    static interface_of_controller_pad m_debugCpadInfo[4];\n    static interface_of_controller_pad m_modPadInfo;"
        header = header.replace(old_debug, new_debug, 1)
        header_path.write_text(header)

    print(f"  Hooked m_Do/m_Do_controller_pad.cpp (mod pad)")


def apply_hook_development_mode() -> None:
    """
    Set developmentMode = 1 in m_Do/m_Do_main.cpp.
    This enables debug controller ports and development features.
    """
    path = SCRIPT_DIR / "src" / "m_Do" / "m_Do_main.cpp"
    content = path.read_text()

    old = "s8 mDoMain::developmentMode = -1;"
    new = "s8 mDoMain::developmentMode = 1;"
    if old not in content:
        print(f"  m_Do/m_Do_main.cpp already patched or differs, skipping")
        return

    content = content.replace(old, new, 1)
    path.write_text(content)
    print(f"  Patched m_Do/m_Do_main.cpp (developmentMode = 1)")


def apply_hook_debug_drawing() -> None:
    """
    Remove #if DEBUG guard around mDoExt_cube8pPacket in m_Do/m_Do_ext.cpp.
    This enables debug drawing primitives unconditionally.
    """
    path = SCRIPT_DIR / "src" / "m_Do" / "m_Do_ext.cpp"
    content = path.read_text()

    # Find the #if DEBUG before mDoExt_cube8pPacket
    marker = "mDoExt_cube8pPacket::mDoExt_cube8pPacket"
    if marker not in content:
        print(f"  m_Do/m_Do_ext.cpp: can't find cube8pPacket, skipping")
        return

    marker_pos = content.index(marker)

    # Search backwards for the #if DEBUG immediately preceding it
    before = content[:marker_pos]
    debug_start = before.rfind("#if DEBUG\n")
    if debug_start == -1:
        print(f"  m_Do/m_Do_ext.cpp: no #if DEBUG before cube8pPacket, skipping")
        return

    # Verify this #if DEBUG is immediately before the function (only whitespace between)
    between = content[debug_start + len("#if DEBUG\n"):marker_pos]
    if between.strip():
        print(f"  m_Do/m_Do_ext.cpp: unexpected code between #if DEBUG and cube8pPacket, skipping")
        return

    # Remove the #if DEBUG line
    content = content[:debug_start] + content[debug_start + len("#if DEBUG\n"):]

    # Now find the matching #endif. We need to find the #endif that closes this block.
    # After removing #if DEBUG, search forward from the cube8pPacket area for the
    # #endif that was at the end of the debug drawing block.
    # The block ends with GXDrawCylinder(8); } #endif
    end_marker = "GXDrawCylinder(8);\n}\n#endif"
    end_pos = content.find(end_marker)
    if end_pos == -1:
        print(f"  m_Do/m_Do_ext.cpp: can't find matching #endif, skipping")
        return

    # Remove just the #endif line
    endif_pos = content.index("#endif", end_pos)
    endif_end = content.index("\n", endif_pos) + 1
    content = content[:endif_pos] + content[endif_end:]

    path.write_text(content)
    print(f"  Patched m_Do/m_Do_ext.cpp (removed DEBUG guard on cube8pPacket)")


def main():
    parser = argparse.ArgumentParser(
        description="Scaffold a new mod fork based on the umbra mod base."
    )
    parser.add_argument(
        "mod_name",
        help="Name of the mod (lowercase, valid C identifier, e.g. 'gz', 'tpgz', 'mymod')"
    )
    parser.add_argument(
        "--no-hooks",
        action="store_true",
        help="Skip applying game hooks (only create files and mod_config.py)"
    )
    args = parser.parse_args()

    mod_name = args.mod_name

    if not validate_mod_name(mod_name):
        print(f"Error: '{mod_name}' is not a valid mod name.")
        print("  Must start with a lowercase letter, contain only [a-z0-9_].")
        sys.exit(1)

    print(f"\nSetting up mod '{mod_name}' in {SCRIPT_DIR}\n")

    # Step 1: Create directories
    print("Creating directories...")
    create_directories(mod_name)

    # Step 2: Generate mod_config.py
    print("\nGenerating mod configuration...")
    generate_mod_config(mod_name)

    # Step 3: Generate stub source files
    print("\nGenerating mod source files...")
    generate_header(mod_name)
    generate_source(mod_name)

    # Step 4: Apply game hooks
    if not args.no_hooks:
        print("\nApplying game hooks...")
        apply_hook_f_pc_manager(mod_name)
        apply_hook_d_s_logo(mod_name)
        apply_hook_controller_pad(mod_name)
        apply_hook_development_mode()
        apply_hook_debug_drawing()

    print(f"\nDone! Next steps:")
    print(f"  1. Review the generated files in src/{mod_name}/ and include/{mod_name}/")
    print(f"  2. Edit mod_config.py to add more source files as you develop")
    print(f"  3. Run: python3 configure.py && ninja")
    print(f"  4. Output ISO: {mod_name}-<version>.iso")
    print()


if __name__ == "__main__":
    main()
