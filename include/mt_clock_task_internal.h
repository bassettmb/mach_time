#ifndef MT_CLOCK_TASK_INTERNAL_H
#define MT_CLOCK_TASK_INTERNAL_H

#include <mach/mach_types.h>
#include <time.h>

int mt_clock_task_getres(mach_port_t port, struct timespec *res);
int mt_clock_task_gettime(mach_port_t port, struct timespec *ts);
int mt_clock_task_settime(mach_port_t port, const struct timespec *ts);

#endif /* !MT_CLOCK_TASK_INTERNAL_H */
