#ifndef CLOCK_TASK_INTERNAL_H
#define CLOCK_TASK_INTERNAL_H

#include <mach/mach_types.h>
#include <time.h>

int clock_task_getres(mach_port_t port, struct timespec *res);
int clock_task_gettime(mach_port_t port, struct timespec *ts);
int clock_task_settime(mach_port_t port, const struct timespec *ts);

#endif /* !CLOCK_TASK_H */
