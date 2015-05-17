#ifndef MACH_TIME_H
#define MACH_TIME_H

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum clockid_type {
    CLOCK_REALTIME = 0,
    CLOCK_MONOTONIC = 1,
    CLOCK_PROCESS_CPUTIME_ID = 2,
    CLOCK_THREAD_CPUTIME_ID = 3
} clockid_t;

int clock_getres(clockid_t clk_id, struct timespec *res);
int clock_gettime(clockid_t clk_id, struct timespec *ts);
int clock_settime(clockid_t clk_id, const struct timespec *ts);

#ifdef __cplusplus
}
#endif 

#endif /* !MACH_TIME_H */
