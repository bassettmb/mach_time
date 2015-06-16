#ifndef MT_POSIX_H
#define MT_POSIX_H

#include "mt_clock.h"

typedef mt_clockid_t clockid_t;

#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC (1UL << 32)
#define CLOCK_PROCESS_CPUTIME_ID (2UL << 32)
#define CLOCK_THREAD_CPUTIME_ID (3UL << 32)

int clock_getres(clockid_t clock_id, struct timespec *res);
int clock_gettime(clockid_t clock_id, struct timespec *ts);
int clock_settime(clockid_t clock_id, const struct timespec *ts);
int clock_getcpuclockid(pid_t pid, clockid_t *clock_id);
int pthread_getcpuclockid(pthread_t thread, clockid_t *clock_id);


#endif /* !MT_POSIX_H */
