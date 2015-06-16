#ifndef MT_CLOCK_THREAD_INTERNAL_H
#define MT_CLOCK_THREAD_INTERNAL_H

#include <mach/mach_types.h>
#include <time.h>

int mt_clock_thread_getres(mach_port_t port, struct timespec *res);
int mt_clock_thread_gettime(mach_port_t port, struct timespec *ts);
int mt_clock_thread_settime(mach_port_t port, const struct timespec *ts);

#endif /* !CLOCK_THREAD_H */
