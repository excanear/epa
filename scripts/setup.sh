#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO_ROOT"

echo "==> Initializing git submodules (Buildroot)..."
git submodule update --init --recursive

echo "==> Checking required host tools..."
missing=0
for tool in make gcc cmake git bc rsync cpio unzip wget; do
    if ! command -v "$tool" >/dev/null 2>&1; then
        echo "MISSING: $tool"
        missing=1
    fi
done

if [ "$missing" -ne 0 ]; then
    echo
    echo "Install the missing tools above (Buildroot's host requirements) and re-run scripts/setup.sh."
    exit 1
fi

echo "==> Setup complete. Next: scripts/build.sh (or 'make build')."
