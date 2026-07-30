# Building EPA

## Prerequisites

EPA is built with [Buildroot](https://buildroot.org/), which requires a Linux host. On Windows,
use WSL2 (Ubuntu recommended).

Host packages needed (Ubuntu/Debian): `build-essential cmake git bc rsync cpio unzip wget
libncurses-dev`.

The project directory path **must not contain spaces** - this is a hard Buildroot requirement
(its kconfig/make tooling breaks on space-containing paths).

## Build

```
make setup   # one-time: init the Buildroot submodule, check host tools
make build   # configure (first run only) + build kernel, toolchain, rootfs
make run     # boot the result in QEMU, drops into epa#
```

`make run` builds first if no image exists yet, so `make build` is optional - `make run` alone is
enough for day-to-day use.

Build output goes to `build/` (gitignored). Images end up at `build/images/bzImage` and
`build/images/rootfs.ext2`.

## Rebuilding after C source changes

Editing files under `core/`, `cli/`, or `modules/` and re-running `make build` triggers an
incremental rebuild of just the `epa` package (via Buildroot's package dependency tracking) - no
full kernel/toolchain rebuild needed.

## Troubleshooting

- **"No rule to make target ..._defconfig"**: the project path contains a space, or `BR2_EXTERNAL`
  wasn't passed through. Verify `pwd` has no spaces.
- **QEMU exits immediately**: check `build/images/bzImage` and `build/images/rootfs.ext2` exist;
  re-run `make build`.
