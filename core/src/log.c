#include "epa/log.h"

#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

static epa_log_level_t g_min_level = EPA_LOG_INFO;
static FILE *g_log_file = NULL;

static const char *level_name(epa_log_level_t level) {
    switch (level) {
        case EPA_LOG_DEBUG: return "DEBUG";
        case EPA_LOG_INFO:  return "INFO";
        case EPA_LOG_WARN:  return "WARN";
        case EPA_LOG_ERROR: return "ERROR";
        default:            return "?";
    }
}

void epa_log_init(epa_log_level_t min_level) {
    g_min_level = min_level;

    /* Best-effort: PID 1 must never fail to start because logging isn't set up yet. */
    mkdir("/var/log", 0755);
    mkdir("/var/log/epa", 0755);
    g_log_file = fopen("/var/log/epa/epa.log", "a");
}

void epa_log(epa_log_level_t level, const char *fmt, ...) {
    if (level < g_min_level) {
        return;
    }

    va_list args;

    va_start(args, fmt);
    fprintf(stdout, "[%s] ", level_name(level));
    vfprintf(stdout, fmt, args);
    fputc('\n', stdout);
    va_end(args);

    if (g_log_file) {
        va_start(args, fmt);
        fprintf(g_log_file, "[%s] ", level_name(level));
        vfprintf(g_log_file, fmt, args);
        fputc('\n', g_log_file);
        fflush(g_log_file);
        va_end(args);
    }
}
