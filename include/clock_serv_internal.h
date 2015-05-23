#ifndef CLOCK_SERV_INTERNAL_H
#define CLOCK_SERV_INTERNAL_H

#include <mach/clock.h>
#include <time.h>

clock_serv_t clock_serv_monotonic(void);
clock_serv_t clock_serv_realtime(void);
int clock_serv_getres(clock_serv_t serv, struct timespec *res);
int clock_serv_gettime(clock_serv_t serv, struct timespec *ts);
int clock_serv_settime(clock_serv_t serv, const struct timespec *ts);

#endif /* !CLOCK_SERV_H */
