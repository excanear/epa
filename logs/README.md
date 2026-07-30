# logs/

Dedicated `logs` command module (system/kernel/application log aggregation) is planned for v0.5.

Note: this is distinct from runtime logging — EPA itself already logs to `/var/log/epa/epa.log`
on the target starting in v0.1 (see `core/src/log.c`), controlled by the `log_level` key in
`/etc/epa.conf`.
