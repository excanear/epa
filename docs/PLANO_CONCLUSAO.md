# Plano de Conclusão — EPA (v0.1)

> Gerado em 2026-10-09. Baseado no estado real do código + `docs/roadmap.md`.

## Estado atual
- Implementado: `core/` (`init.c`, `log.c`) + `cli/shell.c` (~44 linhas: só `help`/`exit`).
- Infra Buildroot presente: `br2-external/`, `scripts/build.sh`, `run-qemu.sh`, `setup.sh`.
- **Nenhum** módulo de auditoria implementado. O stub referencia `modules/`, que ainda não existe.
- Alvo v0.1 (roadmap): bootar no shell `epa#` e responder `hardware/firmware/system/report`.

## Plano (ordem sugerida)
1. **Fundação do shell** — command registry (tabela nome→handler) em `cli/`, dispatch, parsing de args e `help` dinâmico (hoje é hardcoded).
2. **`modules/` + API de módulo** — criar `modules/` e um contrato `epa_module_t` (nome, help, `run(argc,argv)`), registrados no boot.
3. **`hardware`** — `cpu` (`/proc/cpuinfo`, CPUID), `memory` (`/proc/meminfo`, SMBIOS tipo 17), `pci` (`/sys/bus/pci`), `usb` (`/sys/bus/usb`), `disk` (`/sys/block`, SMART via ioctl).
4. **`firmware`** — SMBIOS/DMI (`/sys/firmware/dmi`), ACPI (`/sys/firmware/acpi`), Secure Boot (`efivars`), TPM (`/sys/class/tpm`).
5. **`system`** — kernel, uptime, hostname, usuários, rede básica.
6. **`report json`** — serializador JSON próprio (sem libs), agregando todos os módulos, gravando em `/var/reports/`.
7. **`/etc/epa.conf`** — parser de config simples.
8. **Boot/Buildroot** — finalizar `epa_qemu_x86_64_defconfig` (EPA como PID 1), validar no QEMU.
9. **Testes** — `tests/smoke/boot_smoke.sh` + testes por módulo.
10. **CI** — build Buildroot + smoke no QEMU.

## Ferramentas / limitações
- Precisa de Linux (ou WSL2) + Buildroot + toolchain cross x86_64. **Não compila no Windows puro.**
- Esforço: **alto** (é o mais "do zero" dos repos em andamento).
