#include "mt_clock_internal.h"
#include "mt_clock_serv_internal.h"
#include "mt_clock_task_internal.h"
#include "mt_clock_thread_internal.h"

#include <errno.h>

int
mt_clock_getres(mt_clockid_t clock_id, struct timespec *res)
{
    if (!res) {
        errno = EFAULT;
        return -1;
    }

    switch (clock_id & MT_CLOCK_MASK) {
        case MT_CLOCK_REALTIME:
            return mt_clock_serv_getres(mt_clock_serv_realtime(), res);
        case MT_CLOCK_MONOTONIC:
            return mt_clock_serv_getres(mt_clock_serv_monotonic(), res);
        case MT_CLOCK_PROCESS_CPUTIME_ID:
            return mt_clock_task_getres(clock_id & MT_PORT_MASK, res);
        case MT_CLOCK_THREAD_CPUTIME_ID:
            return mt_clock_thread_getres(clock_id & MT_PORT_MASK, res);
        default:
            errno = EINVAL;
            return -1;
    }
}
