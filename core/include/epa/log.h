#ifndef EPA_LOG_H
#define EPA_LOG_H

typedef enum {
    EPA_LOG_DEBUG = 0,
    EPA_LOG_INFO,
    EPA_LOG_WARN,
    EPA_LOG_ERROR
} epa_log_level_t;

/* Opens /var/log/epa/epa.log (best-effort) in addition to stdout. */
void epa_log_init(epa_log_level_t min_level);
void epa_log(epa_log_level_t level, const char *fmt, ...);

#endif
