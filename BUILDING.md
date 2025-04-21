# Building TinyGCalc

This document describes how to set up your environment, configure your toolchain, and build TinyGCalc for various platforms.

---

## Prerequisites

- **CMake** 3.13 or later
- **Git** (with submodule support)
- **SDL2** (for mock platform)
- **A C compiler**:
  - Windows: MinGW-w64
  - Linux/macOS: GCC/Clang
- **`picotool`** (optional but recommended, see below)

---

## Cloning the Repository

Make sure to clone with submodules:

```bash
git clone --recursive https://github.com/ApexDevelopment/TinyGCalc.git
cd TinyGCalc
```

If you forgot `--recursive`, you can run:
```bash
git submodule update --init --recursive
```

---

## Platform Targets

TinyGCalc supports multiple platforms. Use the build script to select a target:

```bash
./build [platform]       # Linux/macOS/WSL
build.bat [platform]     # Windows
```

Supported platforms:

- `mock` (default): Desktop SDL2 build
- `pico`: Raspberry Pi Pico (RP2040)
- `picow`: Raspberry Pi Pico W (RP2040 + Wi-Fi)
- `stm32`: Experimental; build system is present but the platform is not yet functional

---

## Cleaning Builds

- `build clean` – removes all platform build directories
- `build [platform] clean` – cleans only that platform’s build directory

---

## Installing `picotool`

If you're building for a Pico target, installing `picotool` is strongly recommended.

### Windows (MinGW)

1. Clone and build it:

   ```bash
   git clone --recursive https://github.com/raspberrypi/picotool.git
   cd picotool
   mkdir build && cd build
   cmake -G "MinGW Makefiles" ..  # or use Ninja if preferred
   mingw32-make                   # or make / ninja
   ```

2. Copy the binary to a folder in your `PATH` (e.g., `C:\Tools\picotool.exe`)

### Linux / macOS / WSL

1. Clone and build it:

   ```bash
   git clone --recursive https://github.com/raspberrypi/picotool.git
   cd picotool
   mkdir build && cd build
   cmake ..
   make
   sudo make install  # Optional, installs to /usr/local/bin
   ```

This allows TinyGCalc to skip rebuilding the SDK’s bundled `picotool` every time you run a clean build.

---

## Common Pitfalls

### `mbedtls` CMake version errors

Some versions of `pico-sdk` (as a submodule) include a bundled copy of `mbedtls` with a deprecated `cmake_minimum_required()` directive in its `CMakeLists.txt`. This can cause CMake configuration to fail with unclear errors during `pico_sdk_init()`.

To fix this:

- Make sure your CMake is **at least 3.13**
- Open `pico-sdk/lib/mbedtls/CMakeLists.txt`
- Locate the `cmake_minimum_required(...)` line near the top
- Manually update it to `cmake_minimum_required(VERSION 3.13)` or higher

Once patched, re-run your build.

Alternatively, installing `picotool` globally (see above) avoids this issue entirely by disabling the SDK's internal `picotool` build.

---

## Questions?

If you hit something unexpected, open an issue!
