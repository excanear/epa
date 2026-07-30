#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

if [ ! -f "$REPO_ROOT/build/images/bzImage" ]; then
    "$REPO_ROOT/scripts/build.sh"
fi

exec "$REPO_ROOT/boot/qemu-run.sh" "$@"
