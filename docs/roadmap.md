# EPA Roadmap

## v0.1 (current)
Boot, CLI shell, hardware modules (cpu/memory/pci/usb/disk), firmware module, system module,
JSON report, `/etc/epa.conf`.

## v0.5
Network module, storage module, filesystem module, logs module, plugin system (dlopen-based).

## v1.0
Stable platform, complete reports (all areas), consolidated plugin system, QEMU x86_64 support
finalized, ARM64/RISC-V preparation.

Anything not listed under v0.1 above is out of scope for the current milestone set - see the
per-folder `README.md` in each not-yet-implemented top-level directory (`network/`, `storage/`,
`filesystem/`, `security/`, `browsers/`, `drivers/`, `plugins/`) for its target version.
