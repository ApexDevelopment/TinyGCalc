#!/bin/bash
set -e

UF2_FILE="build/tinygcalc.uf2"

# === Check for .uf2 file ===
if [ ! -f "$UF2_FILE" ]; then
    echo "[ERROR] $UF2_FILE not found. Did you build the project?"
    exit 1
fi

# === Find RPI-RP2 mount point ===
MOUNT_POINT=""

for mount in /media/*/RPI-RP2 /run/media/*/RPI-RP2 /Volumes/RPI-RP2; do
    if [ -d "$mount" ]; then
        MOUNT_POINT="$mount"
        break
    fi
done

if [ -z "$MOUNT_POINT" ]; then
    echo "[ERROR] Could not find RPI-RP2 mount point."
    echo "Make sure your Pico is in BOOTSEL mode and mounted as a USB drive."
    exit 1
fi

# === Copy the firmware ===
cp "$UF2_FILE" "$MOUNT_POINT"
sync

echo "[SUCCESS] tinygcalc.uf2 flashed to $MOUNT_POINT"
