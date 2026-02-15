#!/usr/bin/env python3
"""
Builds a sprite atlas BTI from individual icon PNGs.

The atlas is a horizontal strip of 24x24 icons in IA8 format (288x24).
Each icon slot corresponds to a main menu entry index.

Usage:
    python tools/build_icon_atlas.py

Source PNGs:  source_assets/gz/icons/
Output BTI:   mod_assets/gz/icon_atlas.bti
"""

import sys
from io import BytesIO
from pathlib import Path

from gclib.bti import BTI
from PIL import Image

SCRIPT_DIR = Path(__file__).parent
REPO_ROOT = SCRIPT_DIR.parent
SOURCE_DIR = REPO_ROOT / "source_assets" / "gz" / "icons"
OUTPUT_PATH = REPO_ROOT / "mod_assets" / "gz" / "icon_atlas.bti"
TEMPLATE_PATH = REPO_ROOT / "mod_assets" / "gz" / "icon_default.bti"

ICON_SIZE = 24

# Atlas slot order - matches gzMainMenu_c menu entry order.
# Each entry is the source PNG filename (without extension).
ATLAS_SLOTS = [
    "icon_default",     # MENU_ACTORS
    "icon_cheats",      # MENU_CHEATS
    "icon_flags",       # MENU_FLAGS
    "icon_framework",   # MENU_FRAMEWORK
    "icon_default",     # MENU_HEAPS
    "icon_inventory",   # MENU_INVENTORY
    "icon_memory",      # MENU_MEMORY
    "icon_practice",    # MENU_PRACTICE
    "icon_scene",       # MENU_SCENE
    "icon_settings",    # MENU_SETTINGS
    "icon_tools",       # MENU_TOOLS
    "icon_warping",     # MENU_WARPING
]


def main():
    icon_cache = {}
    for slot_name in set(ATLAS_SLOTS):
        png_path = SOURCE_DIR / f"{slot_name}.png"
        if not png_path.exists():
            print(f"Error: Missing source PNG: {png_path}")
            sys.exit(1)
        img = Image.open(png_path).convert("RGBA")
        if img.size != (ICON_SIZE, ICON_SIZE):
            print(f"Error: {png_path} is {img.size}, expected ({ICON_SIZE}, {ICON_SIZE})")
            sys.exit(1)
        icon_cache[slot_name] = img

    atlas_width = len(ATLAS_SLOTS) * ICON_SIZE
    atlas = Image.new("RGBA", (atlas_width, ICON_SIZE), (0, 0, 0, 0))
    for i, slot_name in enumerate(ATLAS_SLOTS):
        atlas.paste(icon_cache[slot_name], (i * ICON_SIZE, 0))

    atlas_path = "/tmp/gz_icon_atlas.png"
    atlas.save(atlas_path)

    with open(TEMPLATE_PATH, "rb") as f:
        bti = BTI(BytesIO(f.read()))
    bti.read()

    bti.replace_image_from_path(atlas_path)
    bti.save_changes()

    OUTPUT_PATH.parent.mkdir(parents=True, exist_ok=True)
    bti.data.seek(0)
    with open(OUTPUT_PATH, "wb") as f:
        f.write(bti.data.read())

    bti.data.seek(0, 2)
    size = bti.data.tell()
    print(f"Built icon atlas: {OUTPUT_PATH}")
    print(f"  {len(ATLAS_SLOTS)} icons, {atlas_width}x{ICON_SIZE} IA8, {size} bytes")


if __name__ == "__main__":
    main()
