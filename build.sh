#!/bin/bash
set -e

# === Clean target ===
if [[ "$1" == "clean" ]]; then
    echo "[INFO] Cleaning build directory..."
    rm -rf build
    exit 0
fi

# === Default to mock platform if none specified ===
: "${PLATFORM:=mock}"
echo "[INFO] PLATFORM=$PLATFORM"

# === Check for Pico SDK only if targeting Pico ===
if [[ "$PLATFORM" == "pico" ]]; then
    if [ -z "$PICO_SDK_PATH" ]; then
        echo "[ERROR] PICO_SDK_PATH is not set."
        echo "Please set the Pico SDK path like this:"
        echo "  export PICO_SDK_PATH=\$HOME/pico-sdk"
        echo "Or pass it to CMake:"
        echo "  cmake -DPICO_SDK_PATH=\$HOME/pico-sdk .."
        exit 1
    fi

    if [ ! -f "$PICO_SDK_PATH/pico_sdk_init.cmake" ]; then
        echo "[ERROR] pico_sdk_init.cmake not found in $PICO_SDK_PATH"
        echo "Please make sure you cloned the SDK:"
        echo "  git clone https://github.com/raspberrypi/pico-sdk.git \$PICO_SDK_PATH"
        exit 1
    fi
fi

# === Check for arm-none-eabi-gcc only for embedded targets ===
if [[ "$PLATFORM" != "mock" ]]; then
    if ! command -v arm-none-eabi-gcc &> /dev/null; then
        echo "[ERROR] arm-none-eabi-gcc not found in PATH."
        echo "Install the ARM GCC toolchain (e.g., sudo apt install gcc-arm-none-eabi)"
        exit 1
    fi
fi

# === Create build directory ===
mkdir -p build
cd build

# === Use native toolchain if mock ===
TOOLCHAIN_OPTION=""
if [[ "$PLATFORM" == "mock" ]]; then
    TOOLCHAIN_OPTION="-DCMAKE_TOOLCHAIN_FILE=../toolchain/native.cmake"
fi

# === Configure with CMake ===
cmake .. $TOOLCHAIN_OPTION -DPICO_SDK_PATH="$PICO_SDK_PATH" -DPLATFORM="$PLATFORM"

# === Build with Make ===
make -j"$(nproc)"

echo "[SUCCESS] Build complete."
cd ..
