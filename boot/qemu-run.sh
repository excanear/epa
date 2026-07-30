#!/usr/bin/env bash
# Boots the EPA image in QEMU. Serial console only (-nographic) - EPA is CLI-only.
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
IMAGES_DIR="$REPO_ROOT/build/images"

KERNEL="$IMAGES_DIR/bzImage"
ROOTFS="$IMAGES_DIR/rootfs.ext2"

if [ ! -f "$KERNEL" ] || [ ! -f "$ROOTFS" ]; then
    echo "Build images not found under $IMAGES_DIR - run scripts/build.sh first." >&2
    exit 1
fi

exec qemu-system-x86_64 \
    -kernel "$KERNEL" \
    -drive file="$ROOTFS",format=raw,if=virtio \
    -append "root=/dev/vda console=ttyS0 rw" \
    -netdev user,id=net0 -device virtio-net-pci,netdev=net0 \
    -m 512M \
    -nographic \
    -no-reboot \
    "$@"
