#include "clock_internal.h"
#include "clock_serv_internal.h"
#include "clock_task_internal.h"
#include "clock_thread_internal.h"

#include <errno.h>

int
clock_getres(clockid_t clock_id, struct timespec *res)
{
    if (!res) {
        errno = EFAULT;
        return -1;
    }

    switch (clock_id & CLOCK_MASK) {
        case CLOCK_REALTIME:
            return clock_serv_getres(clock_serv_realtime(), res);
        case CLOCK_MONOTONIC:
            return clock_serv_getres(clock_serv_monotonic(), res);
        case CLOCK_PROCESS_CPUTIME_ID:
            return clock_task_getres(clock_id & PORT_MASK, res);
        case CLOCK_THREAD_CPUTIME_ID:
            return clock_thread_getres(clock_id & PORT_MASK, res);
        default:
            errno = EINVAL;
            return -1;
    }
}
