# TinyGCalc

**TinyGCalc** is a minimal, portable graphing calculator firmware designed for small embedded systems like the Raspberry Pi Pico. It emphasizes:

- Simplicity – just plot functions; no bloat
- Portability – easily retarget to new hardware
- Modularity – replaceable HAL for display/input/time

It builds cleanly for:

- Raspberry Pi Pico (via Pico SDK)
- Desktop mock display (SDL2)
- STM32 (planned)

---

## Project Goals

- Lightweight: Works on chips with 128–256 KB RAM and 1–2 MB flash
- Pure C/C++: Simple to understand and debug
- Hardware-abstracted: Port by just swapping the HAL
- Buildable on Windows, Linux, macOS

---

## Build Instructions

### Quick Start

Clone the repo and its submodules:

```bash
git clone --recursive https://github.com/ApexDevelopment/TinyGCalc.git
cd TinyGCalc
```

#### On Windows (with MinGW)
```cmd
build.bat
```

#### On Linux / macOS / WSL
```bash
./build.sh
```

> By default, both scripts build the `mock` (desktop SDL2) platform using your native compiler (e.g. MinGW or GCC). You can build for a specific platform with `build [platform]`. For example, `build picow` will build a UF2 for the Pi Pico W.

---

### Pico SDK Setup

TinyGCalc expects the Pico SDK to be installed globally. You can set the SDK location when running CMake:

```bash
cmake -DPICO_SDK_PATH=/path/to/pico-sdk ..
```

If you haven’t installed it yet:

```bash
git clone https://github.com/raspberrypi/pico-sdk.git ~/pico-sdk
```

Then use:
```bash
cmake -DPICO_SDK_PATH=$HOME/pico-sdk ..
```

Or set it globally in your shell:
```bash
export PICO_SDK_PATH=$HOME/pico-sdk
```

> Pitfall: if you are building for a Pico board and you don't have `picotool` installed, it will be built from source.
This can cause CMake to choke on `mbedtls`. In that case you should either install picotool, or patch that `CMakeLists.txt`
file to ask for a newer version of CMake.

---

## Controls

TinyGCalc supports keyboard input when running on the `mock` platform with SDL2.

- Simply start typing to enter an expression. Press enter to evaluate it.
- F1 enters the equation editor. Use arrow keys to navigate and enter to plot all equations.
- While in graph view, use arrow keys to pan, mouse wheel to zoom, and enter to return to the editor.
- While in the editor, press escape to return to the REPL (expression evaluator).

More features are planned for the future.

---

## License

This project is licensed under the ISC license.

It includes third-party code licensed under:

- zlib (TinyExpr, SDL2)
- BSD 3-Clause (Pico SDK)
- GNU GPL 3.0 (font6x8)
