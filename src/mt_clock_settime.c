#include "mt_clock_internal.h"
#include "mt_clock_serv_internal.h"
#include "mt_clock_task_internal.h"
#include "mt_clock_thread_internal.h"

#include <errno.h>

MT_EXPORT int
mt_clock_settime(mt_clockid_t clock_id, const struct timespec *ts)
{
    if (!ts) {
        errno = EFAULT;
        return -1;
    }

    if (ts->tv_nsec >= MT_NSEC_PER_SEC) {
        errno = EINVAL;
        return -1;
    }

    switch (clock_id & MT_CLOCK_MASK) {
        case MT_CLOCK_REALTIME:
            return mt_clock_serv_settime(mt_clock_serv_realtime(), ts);
        case MT_CLOCK_MONOTONIC:
            return mt_clock_serv_settime(mt_clock_serv_monotonic(), ts);
        case MT_CLOCK_PROCESS_CPUTIME_ID:
            return mt_clock_task_settime(clock_id & MT_PORT_MASK, ts);
        case MT_CLOCK_THREAD_CPUTIME_ID:
            return mt_clock_thread_settime(clock_id & MT_PORT_MASK, ts);
        default:
            errno = EINVAL;
            return -1;
    }
}
