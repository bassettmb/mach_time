#include "clock_thread_internal.h"
#include <mach/thread_act.h>
#include <errno.h>

int
clock_thread_getres(mach_port_t thread, struct timespec *ts)
{
    ts->tv_sec = 0;
    ts->tv_nsec = NSEC_PER_USEC;
    return 0;
}

int
clock_thread_gettime(mach_port_t thread, struct timespec *ts)
{
    struct thread_basic_info info;
    mach_msg_type_number_t size = sizeof info;

    kern_return_t error =
        thread_info(thread, THREAD_BASIC_INFO, (thread_info_t)&info, &size);

    if (error != KERN_SUCCESS) {
        errno = EINVAL;
        return -1;
    }

    ts->tv_sec = info.user_time.seconds;
    ts->tv_nsec = info.user_time.microseconds * NSEC_PER_USEC;

    return 0;
}

int
clock_thread_settime(mach_port_t thread, const struct timespec *ts)
{
    errno = EINVAL;
    return -1;
}
