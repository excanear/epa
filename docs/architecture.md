# EPA Architecture

## Layers

```
QEMU / hardware
      |
Linux kernel (kernel/epa_qemu_defconfig fragment on top of an in-tree defconfig)
      |
epa-init (core/src/init.c) - PID 1, no systemd, no other init
      |
epa# shell (cli/) <-> module registry (core/ + modules/) <-> report generator (modules/report/)
```

There is no login prompt, no getty, no other userspace program. `epa-init` mounts `/proc`,
`/sys`, `/dev`, reads `/etc/epa.conf`, forks the interactive shell, and reaps children until the
shell exits, at which point it powers the machine off.

## Repository layout

Active code/config for v0.1: `boot/`, `kernel/`, `core/`, `cli/`, `modules/`, `config/`,
`tests/`, `docs/`, `scripts/`, `br2-external/`.

Stub-only (each holds just a `README.md` stating its target version): `network/`, `storage/`,
`filesystem/`, `security/`, `browsers/`, `drivers/`, `plugins/`.

**Deliberate deviation from the original spec**: the spec's top-level `hardware/`, `firmware/`,
`system/` folders are documentation-only mirrors pointing at `modules/hardware/`,
`modules/firmware/`, `modules/system/`. Actual module code lives under `modules/` per the layer
diagram above (the "Modules" stage) - this avoids two plausible locations for the same code.

## The module reuse contract

Every module (`hardware cpu`, `firmware info`, etc.) is implemented once and used by both the
interactive shell and `report json`. It does this by never writing text or JSON directly - it
populates a generic `epa_fact_set_t` (ordered key/value/nested entries), and two renderers
consume that:

- `epa_render_text()` - human-readable output for the shell
- `epa_render_json()` - used by `report json`

```c
typedef struct epa_module {
    const char *area;   // "hardware" | "firmware" | "system"
    const char *name;   // "cpu" | "memory" | "pci" | "usb" | "disk" | "info"
    const char *help;
    int (*run)(const epa_module_ctx_t *ctx, epa_fact_set_t *out);
} epa_module_t;
```

Modules register into a static table (`core/src/module_registry.c`); there is no dynamic loading
in v0.1 (see `plugins/README.md` for when that changes).

## Data sources

Facts are read natively from `/proc` and `/sys` wherever practical. The sole vendored external
tool in v0.1 is `smartmontools` (`smartctl -j`), used for disk SMART data - reimplementing
ATA/NVMe SMART parsing was judged not worth it. Everything else (CPU/cpuid, PCI, USB, DMI/SMBIOS,
ACPI, TPM, procfs-derived system facts) is parsed directly in `core`/`modules`.

## Build system

Buildroot (`third_party/buildroot`, git submodule) via a `BR2_EXTERNAL` tree (`br2-external/`).
EPA's C sources build as a Buildroot package (`br2-external/package/epa/`) using CMake, producing
a single static `epa-init` binary that becomes `/sbin/init` on the target. See
[build.md](build.md) for the developer workflow.
