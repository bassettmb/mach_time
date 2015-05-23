#include "clock_internal.h"
#include "clock_serv_internal.h"
#include "clock_task_internal.h"
#include "clock_thread_internal.h"

#include <errno.h>

int
clock_settime(clockid_t clock_id, const struct timespec *ts)
{
    if (!ts) {
        errno = EFAULT;
        return -1;
    }

    switch (clock_id & CLOCK_MASK) {
        case CLOCK_REALTIME:
            return clock_serv_settime(clock_serv_realtime(), ts);
        case CLOCK_MONOTONIC:
            return clock_serv_settime(clock_serv_monotonic(), ts);
        case CLOCK_PROCESS_CPUTIME_ID:
            return clock_task_settime(clock_id & PORT_MASK, ts);
        case CLOCK_THREAD_CPUTIME_ID:
            return clock_thread_settime(clock_id & PORT_MASK, ts);
        default:
            errno = EINVAL;
            return -1;
    }
}
