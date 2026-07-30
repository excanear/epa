#include "epa/cli.h"

#include <stdio.h>
#include <string.h>

static char *trim(char *s) {
    while (*s == ' ' || *s == '\t') s++;
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r' ||
                        s[len - 1] == ' ' || s[len - 1] == '\t')) {
        s[--len] = '\0';
    }
    return s;
}

int epa_shell_run(void) {
    char line[256];

    for (;;) {
        fputs("epa# ", stdout);
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin)) {
            /* EOF on stdin (e.g. serial console closed) */
            putchar('\n');
            return 0;
        }

        char *cmd = trim(line);
        if (cmd[0] == '\0') {
            continue;
        }

        if (strcmp(cmd, "exit") == 0) {
            return 0;
        } else if (strcmp(cmd, "help") == 0) {
            puts("EPA v0.1 - available commands:");
            puts("  help    show this message");
            puts("  exit    leave the shell");
        } else {
            printf("epa: unknown command: %s\n", cmd);
        }
    }
}
