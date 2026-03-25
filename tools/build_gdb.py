#!/usr/bin/env python3

"""
Downloads and builds powerpc-eabi-gdb from source with Python scripting support.
Installs into an existing binutils directory.

Usage:
    python3 tools/build_gdb.py build/binutils --version 17.1
"""

import argparse
import io
import os
import shutil
import subprocess
import sys
import tarfile
import urllib.request
from pathlib import Path


GDB_MIRROR = "https://sourceware.org/pub/gdb/releases"


def download_source(version: str, work_dir: Path) -> Path:
    src_dir = work_dir / "gdb-src"
    if src_dir.exists():
        return src_dir

    url = f"{GDB_MIRROR}/gdb-{version}.tar.xz"
    print(f"Downloading {url}")
    req = urllib.request.Request(url, headers={"User-Agent": "Mozilla/5.0"})
    with urllib.request.urlopen(req) as resp:
        data = io.BytesIO(resp.read())

    src_dir.mkdir(parents=True)
    import lzma

    with lzma.open(data) as xz:
        with tarfile.open(fileobj=xz) as tar:
            tar.extractall(src_dir, filter="data")

    # tar extracts into gdb-<version>/ subfolder
    subdirs = list(src_dir.iterdir())
    if len(subdirs) == 1 and subdirs[0].is_dir():
        inner = subdirs[0]
        tmp = work_dir / "_gdb_inner"
        inner.rename(tmp)
        src_dir.rmdir()
        tmp.rename(src_dir)

    return src_dir


def build_gdb(src_dir: Path, work_dir: Path, prefix: Path) -> None:
    build_dir = work_dir / "gdb-build"
    build_dir.mkdir(parents=True, exist_ok=True)

    jobs = str(os.cpu_count() or 4)
    configure_path = str(src_dir / "configure")
    prefix_path = str(prefix)

    def run(cmd_args, **kwargs):
        subprocess.check_call(cmd_args, cwd=build_dir, **kwargs)

    # Configure
    configure_cmd = [
        configure_path,
        "--target=powerpc-eabi",
        f"--prefix={prefix_path}",
        "--with-python=python3",
        "--disable-sim",
        "--disable-nls",
        "--disable-werror",
    ]
    print("Configuring GDB...")
    run(configure_cmd, stdout=subprocess.DEVNULL)

    # Build
    print("Building GDB (this may take a few minutes)...")
    run(["make", f"-j{jobs}"], stdout=subprocess.DEVNULL)

    # Install
    run(["make", "install"], stdout=subprocess.DEVNULL)


def main() -> None:
    parser = argparse.ArgumentParser(description="Build powerpc-eabi-gdb from source")
    parser.add_argument(
        "binutils_dir", type=Path, help="Binutils directory to install into"
    )
    parser.add_argument(
        "--version", default="17.1", help="GDB version (default: 17.1)"
    )
    args = parser.parse_args()

    binutils_dir = args.binutils_dir.resolve()
    if not binutils_dir.exists():
        sys.exit(f"Binutils directory not found: {binutils_dir}")

    EXE = ".exe" if sys.platform == "win32" else ""
    gdb_binary = binutils_dir / f"powerpc-eabi-gdb{EXE}"
    if gdb_binary.exists():
        print(f"GDB already exists at {gdb_binary}, skipping build")
        return

    if sys.platform == "win32":
        print(
            "WARNING: Building GDB from source is not supported on Windows.\n"
            "GDB debugging requires powerpc-eabi-gdb (v14.1+, for DAP support).\n"
            f"Place powerpc-eabi-gdb.exe in: {binutils_dir}"
        )
        return

    work_dir = binutils_dir.parent / "gdb-build"
    work_dir.mkdir(parents=True, exist_ok=True)

    # Install to temp prefix, then merge into binutils dir.
    # GDB's `make install` puts binaries in {prefix}/bin/ and data in {prefix}/share/gdb/.
    # The binutils dir has tools flat (no bin/ subdir), so we copy selectively.
    install_dir = work_dir / "install"
    install_dir.mkdir(parents=True, exist_ok=True)

    src_dir = download_source(args.version, work_dir)
    build_gdb(src_dir, work_dir, install_dir)

    # Copy GDB binary
    installed_gdb = install_dir / "bin" / "powerpc-eabi-gdb"
    if not installed_gdb.exists():
        sys.exit(f"GDB build succeeded but binary not found at {installed_gdb}")
    shutil.copy2(installed_gdb, gdb_binary)
    os.chmod(gdb_binary, 0o755)

    # Copy GDB data directory (Python/Guile modules needed at runtime).
    # GDB resolves its data dir relative to the binary: {binary}/../../share/gdb.
    # Binary is at build/binutils/powerpc-eabi-gdb, so data goes to build/share/gdb.
    gdb_data = install_dir / "share" / "gdb"
    if gdb_data.exists():
        dest_data = binutils_dir.parent / "share" / "gdb"
        if dest_data.exists():
            shutil.rmtree(dest_data)
        shutil.copytree(gdb_data, dest_data)

    print(f"Installed {gdb_binary}")

    # Clean up source and build artifacts
    shutil.rmtree(work_dir)


if __name__ == "__main__":
    main()
