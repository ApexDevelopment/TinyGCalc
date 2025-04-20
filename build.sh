#!/usr/bin/env bash

set -euo pipefail

# === Defaults ===
TARGET=${1:-mock}
ACTION=${2:-build}

# === Platform + board map ===
PLATFORM=""
PICO_BOARD_TYPE=""

case "$TARGET" in
  mock)
    PLATFORM="mock"
    ;;
  pico)
    PLATFORM="pico"
    PICO_BOARD_TYPE="pico"
    ;;
  picow)
    PLATFORM="pico"
    PICO_BOARD_TYPE="pico_w"
    ;;
  clean)
    echo "[INFO] Cleaning all build directories..."
    rm -rf build/
    exit 0
    ;;
  *)
    echo "[ERROR] Unknown target: $TARGET"
    echo "Usage:"
    echo "  ./build.sh [mock|pico|picow] [clean]"
    exit 1
    ;;
esac

# === Per-target clean ===
if [[ "$ACTION" == "clean" ]]; then
  echo "[INFO] Cleaning build/$TARGET..."
  rm -rf "build/$TARGET"
  exit 0
fi

# === Validate PICO_SDK_PATH if needed ===
if [[ "$PLATFORM" == "pico" ]]; then
  if [[ -z "${PICO_SDK_PATH:-}" ]]; then
    echo "[ERROR] PICO_SDK_PATH is not set"
    echo "  export PICO_SDK_PATH=/path/to/pico-sdk"
    exit 1
  fi
  if [[ ! -f "$PICO_SDK_PATH/pico_sdk_init.cmake" ]]; then
    echo "[ERROR] pico_sdk_init.cmake not found in $PICO_SDK_PATH"
    exit 1
  fi
fi

# === Check for arm-none-eabi-gcc ===
if [[ "$PLATFORM" != "mock" ]]; then
  if ! command -v arm-none-eabi-gcc > /dev/null; then
    echo "[ERROR] arm-none-eabi-gcc not found in PATH"
    exit 1
  fi
fi

# === Create and enter build directory ===
BUILD_DIR="build/$TARGET"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# === Run CMake ===
cmake ../.. \
  -DPICO_SDK_PATH="$PICO_SDK_PATH" \
  -DPLATFORM="$PLATFORM" \
  -DPICO_BOARD_TYPE="$PICO_BOARD_TYPE" \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -G "Unix Makefiles"

# === Build ===
make -j

echo "[SUCCESS] Build complete for target: $TARGET"
