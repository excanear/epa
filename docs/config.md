# /etc/epa.conf

Simple `key = value` lines, one per line, no sections. Blank lines and lines starting with `#`
are ignored. Unknown keys are logged as a warning and otherwise ignored - a malformed or partial
config file must never prevent boot (`epa-init` is PID 1).

## Keys (v0.1)

| Key | Default | Meaning |
|---|---|---|
| `language` | `en` | UI language (only `en` implemented in v0.1) |
| `hostname` | `epa-node` | Hostname applied at boot |
| `output_dir` | `/var/reports` | Where `report json` writes generated reports |
| `report_format` | `json` | Default report format (only `json` implemented in v0.1) |
| `log_level` | `info` | One of `debug`, `info`, `warn`, `error` - controls `/var/log/epa/epa.log` verbosity |

## Example

```
language = en
hostname = epa-node
output_dir = /var/reports
report_format = json
log_level = info
```

The default shipped on the target image lives at
`br2-external/board/epa/qemu/rootfs-overlay/etc/epa.conf` in this repo.
