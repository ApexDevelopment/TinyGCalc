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

#### On Windows (MinGW)
```cmd
build.bat
```

#### On Linux / macOS / WSL
```bash
./build.sh
```

By default, this builds the desktop `mock` platform using SDL2.

To build for a different platform, use:
```bash
build [platform]
```

For example, to build a UF2 for the Raspberry Pi Pico W:
```bash
build picow
```

> Pitfall: if you target a Pico board but you don't have `picotool` installed, it will be built from source. This may cause CMake to choke. In that case you should either install picotool, or patch that `CMakeLists.txt` file to ask for a newer version of CMake.

> For more information on dependencies and environment configuration, see [`BUILDING.md`](./BUILDING.md)

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
