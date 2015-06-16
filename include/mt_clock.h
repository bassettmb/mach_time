#ifndef MT_CLOCK_H
#define MT_CLOCK_H

#include <sys/types.h>
#include <pthread.h>
#include <stdint.h>

typedef uint64_t mt_clockid_t;

#define MT_CLOCK_REALTIME 0
#define MT_CLOCK_MONOTONIC (1UL << 32)
#define MT_CLOCK_PROCESS_CPUTIME_ID (2UL << 32)
#define MT_CLOCK_THREAD_CPUTIME_ID (3UL << 32)

const char *mt_version(void);
int mt_clock_getres(mt_clockid_t clock_id, struct timespec *res);
int mt_clock_gettime(mt_clockid_t clock_id, struct timespec *ts);
int mt_clock_settime(mt_clockid_t clock_id, const struct timespec *ts);
int mt_clock_getcpuclockid(pid_t pid, mt_clockid_t *clock_id);
int mt_pthread_getcpuclockid(pthread_t thread, mt_clockid_t *clock_id);

#endif /* !MT_CLOCK_H */
