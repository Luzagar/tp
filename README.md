# decompgz

 The Twilight Princess practice rom, based on the decompilation project.  

## Dependencies

Windows
-------

On Windows, it's **highly recommended** to use native tooling. WSL or msys2 are **not** required.  

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- Install Lago's gclib tools:

  ```
  pip install "gclib[speedups] @ git+https://github.com/LagoLunatic/gclib.git"
  ```
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
  - Quick install via pip: `pip install ninja`

macOS
-----

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):

  ```sh
  brew install ninja
  ```

- Install [wine-crossover](https://github.com/Gcenx/homebrew-wine):

  ```sh
  brew install --cask --no-quarantine gcenx/wine/wine-crossover
  ```

- Install Lago's gclib tools:

  ```
  pip install "gclib[speedups] @ git+https://github.com/LagoLunatic/gclib.git"
  ```

After OS upgrades, if macOS complains about `Wine Crossover.app` being unverified, you can unquarantine it using:

```sh
sudo xattr -rd com.apple.quarantine '/Applications/Wine Crossover.app'
```

Linux
-----

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).
- Install Lago's gclib tools:

  ```
  pip install "gclib[speedups] @ git+https://github.com/LagoLunatic/gclib.git"
  ```
- For non-x86(_64) platforms: Install wine from your package manager.
  - For x86(_64), [wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

## Building

- Clone the repository:

  ```sh
  git clone https://github.com/zeldaret/tp.git
  ```

- Copy your game's disc image (ISO) to `orig/GZ2E01/GZ2E01.iso` (or appropriate version, e.g., `orig/GZ2P01/GZ2P01.iso`).
  - Supported formats: ISO (GCM), RVZ, WIA, WBFS, CISO, NFS, GCZ, TGC.
  - This is used for both asset extraction and rebuilding the final ISO.

- Configure and build:

  ```sh
  python configure.py -v GZ2E01
  ninja
  ```

  - Replace `GZ2E01` with your desired version (e.g., `GZ2P01` for PAL)
  - Currently supported versions: `GZ2E01`, `GZ2P01`, `GZ2J01`
  - Wii support coming soon
  - After the project compiles, build the final iso with:

  ```sh
  python tools/rebuild-decomp-tp.py ./orig/GZ2E01/GZ2E01.iso ./tpgz-GZ2E01.iso ./ --version GZ2E01
  ```

  - Replace `GZ2E01` with your desired version

## Adding Custom Code

To add new features to the practice ROM:

- Create new .cpp or .h files in appropriate directories (e.g., `src/gz/` for game-specific custom code)
- Add them to `configure.py` in the `config.libs` list, marked as `Custom`
- Look at existing custom files in `src/gz/` for examples of how to structure and integrate new code
- Re-run `python configure.py -v VERSION` and `ninja` to include your changes

## GDB Remote Debugging

Umbra includes a GDB remote stub for source-level debugging of game code. It supports both real hardware via [umbra-nintendont](https://github.com/zsrtp/umbra-nintendont) and emulation via [umbra-dolphin](https://github.com/zsrtp/umbra-dolphin).

### Setup

To include debug info (DWARF 2 conversion + REL symbol loader) as part of the default build, configure with `--penumbra`:

```sh
python configure.py --penumbra
ninja
```

This converts MetroWerks DWARF 1 debug info to DWARF 2 and generates the GDB symbol loader script during the normal build. Debug info is regenerated automatically when source files change.

### Connecting

Install the bundled debug adapter extension (one-time setup):

```sh
code --install-extension .vscode/penumbra-debug.vsix
```

Then use the launch configurations in `.vscode/launch.json`:

- **Penumbra: Attach to Nintendont** -- connect to a Wii running the GDB stub
- **Penumbra: Attach to Dolphin** -- connect to Dolphin's GDB stub

Symbols and debug info are loaded automatically on connect.

## Adding Custom Assets

- Place your custom asset into the `mod_assets` directory. The directory structure will be copied 1:1 to the final disc image.
- Re-run the build process above to include your changes
