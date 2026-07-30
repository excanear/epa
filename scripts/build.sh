#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILDROOT_DIR="$REPO_ROOT/third_party/buildroot"
BUILD_OUT="$REPO_ROOT/build"
BR2_EXTERNAL_EPA_PATH="$REPO_ROOT/br2-external"

# Buildroot refuses to run if PATH contains spaces. On WSL, PATH usually
# includes interop entries from Windows (e.g. "C:\Program Files\...") which
# break this. Strip any PATH entry containing a space.
CLEAN_PATH="$(printf '%s' "$PATH" | tr ':' '\n' | grep -v ' ' | paste -sd: -)"
export PATH="$CLEAN_PATH"

cd "$BUILDROOT_DIR"

if [ ! -f "$BUILD_OUT/.config" ]; then
    echo "==> Configuring Buildroot (epa_qemu_x86_64_defconfig)..."
    make O="$BUILD_OUT" BR2_EXTERNAL="$BR2_EXTERNAL_EPA_PATH" epa_qemu_x86_64_defconfig
fi

echo "==> Building (this can take a while the first time)..."
make O="$BUILD_OUT" BR2_EXTERNAL="$BR2_EXTERNAL_EPA_PATH"

echo "==> Build complete. Images in $BUILD_OUT/images/"
