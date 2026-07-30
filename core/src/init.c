/*
 * epa-init: PID 1 for the EPA appliance. No systemd, no busybox-init, no
 * getty/login - this process mounts the essential filesystems and forks the
 * interactive epa# shell, then reaps children until the shell exits.
 */
#include "epa/cli.h"
#include "epa/log.h"

#include <stdio.h>
#include <sys/mount.h>
#include <sys/reboot.h>
#include <sys/wait.h>
#include <unistd.h>

static void mount_essential_filesystems(void) {
    mount("proc", "/proc", "proc", 0, NULL);
    mount("sysfs", "/sys", "sysfs", 0, NULL);
    mount("devtmpfs", "/dev", "devtmpfs", 0, NULL);
}

int main(void) {
    mount_essential_filesystems();
    epa_log_init(EPA_LOG_INFO);
    epa_log(EPA_LOG_INFO, "epa-init starting (pid %d)", (int)getpid());

    pid_t shell_pid = fork();
    if (shell_pid == 0) {
        /* Child: become the interactive shell. */
        int rc = epa_shell_run();
        _exit(rc);
    }

    if (shell_pid < 0) {
        epa_log(EPA_LOG_ERROR, "failed to fork shell, halting");
        for (;;) pause();
    }

    /* Parent: PID 1 reaps every child; the shell exiting ends the appliance. */
    for (;;) {
        int status;
        pid_t died = wait(&status);

        if (died == shell_pid) {
            epa_log(EPA_LOG_INFO, "shell exited, powering off");
            sync();
            reboot(RB_POWER_OFF);
            for (;;) pause();
        }
        /* Any other reaped child (orphans) is ignored; keep waiting. */
        if (died < 0) {
            pause();
        }
    }
}
