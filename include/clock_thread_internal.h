#ifndef CLOCK_THREAD_INTERNAL_H
#define CLOCK_THREAD_INTERNAL_H

#include <mach/mach_types.h>
#include <time.h>

int clock_thread_getres(mach_port_t port, struct timespec *res);
int clock_thread_gettime(mach_port_t port, struct timespec *ts);
int clock_thread_settime(mach_port_t port, const struct timespec *ts);

#endif /* !CLOCK_THREAD_H */
