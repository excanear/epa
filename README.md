<div align="center">

# Excanear Portable Appliance (EPA)

**A portable, CLI-only embedded Linux appliance for hardware, firmware, and system
auditing, inventory, and incident response.**

[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Status](https://img.shields.io/badge/status-v0.1_in_progress-yellow.svg)](docs/roadmap.md)
[![Platform](https://img.shields.io/badge/platform-x86__64_%7C_QEMU-lightgrey.svg)](docs/build.md)
[![Language](https://img.shields.io/badge/language-C-informational.svg)](core/)

</div>

---

EPA boots straight into its own shell — no login prompt, no desktop, no systemd, no other
userspace. It exists to answer one question fast, on a machine you're authorized to inspect:
*what is this system, exactly?*

```
epa# hardware cpu
epa# firmware info
epa# report json
Report written to /var/reports/epa-report-2026-07-28T19-42-00.json
```

## Why

Incident responders and auditors often need a trustworthy, minimal, disposable environment to
boot on a target machine and collect a full hardware/firmware/system inventory without dragging
in a whole desktop OS. EPA is that environment: a purpose-built appliance, not a general-purpose
Linux distro with tools bolted on.

## Design

- **CLI-only.** No GUI, ever. Everything happens at the `epa#` prompt.
- **EPA *is* the OS.** EPA's own C code runs as PID 1 on a minimal Buildroot-based root
  filesystem. There's no init system, no login manager, no shell other than EPA's own — the
  appliance boots directly into it.
- **One implementation, two outputs.** Every module (`hardware cpu`, `firmware info`, ...) is
  written once and renders either as human-readable shell output or as part of a structured JSON
  report — never duplicated. See [docs/architecture.md](docs/architecture.md).
- **Native over vendored.** Facts are read directly from `/proc` and `/sys` wherever practical.
  The only vendored external tool is `smartmontools`, for disk SMART data.
- **QEMU first, real hardware next.** Developed and tested against QEMU x86_64; ARM64/RISC-V and
  physical hardware bring-up are on the roadmap.

## Status

EPA is under active early development. **v0.1** is the current milestone:

| Area | Status |
|---|---|
| Boot to `epa#` shell (Buildroot + custom PID 1 init) | 🚧 in progress |
| `hardware cpu / memory / pci / usb / disk` | planned |
| `firmware info` (BIOS/UEFI, SMBIOS, ACPI, Secure Boot, TPM) | planned |
| `system info` | planned |
| `report json` | planned |
| `/etc/epa.conf` | planned |
| Network, storage, filesystem, logs, security, plugins | out of scope until v0.5 / v1.0 |

See [docs/roadmap.md](docs/roadmap.md) for the full v0.1 → v0.5 → v1.0 plan and
[docs/architecture.md](docs/architecture.md) for why some folders are stubs right now.

## Quick start

Requires a Linux build environment (native Linux, or WSL2 on Windows). Buildroot cannot build in
a path containing spaces — see [docs/build.md](docs/build.md) for the full prerequisite list and
troubleshooting.

```sh
make setup   # one-time: init the Buildroot submodule, check host tools
make run     # build (if needed) and boot in QEMU, drops into epa#
```

## Repository layout

```
boot/         QEMU boot scripts, kernel cmdline
kernel/       Linux kernel config fragment
core/         epa-init (PID 1), module framework, JSON writer, config parser
cli/          the epa# shell: line editing, dispatch, builtins
modules/      hardware / firmware / system / report module implementations
br2-external/ Buildroot external tree (package, defconfig, board files)
config/       /etc/epa.conf template + schema
tests/        unit tests + QEMU boot smoke test
docs/         architecture, build guide, module authoring, roadmap
scripts/      setup / build / run wrappers
```

`network/`, `storage/`, `filesystem/`, `security/`, `browsers/`, `drivers/`, `plugins/` exist as
stubs for later milestones — each has a `README.md` stating its target version.

## Legal / authorized use only

EPA is built for auditing and incident response on systems you own or are explicitly authorized
to inspect. It does not attempt to bypass encryption, authentication, or other protection
mechanisms, and it never will by design. Use it responsibly and only where you have permission.

## Contributing

The project is young and the architecture is still settling — see
[docs/architecture.md](docs/architecture.md) for the module contract before adding a new one, and
[docs/module-authoring.md](docs/module-authoring.md) once it lands (v0.1 milestone M7).

## License

[MIT](LICENSE).
