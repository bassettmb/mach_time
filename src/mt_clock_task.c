#include "mt_clock_internal.h"
#include "mt_clock_task_internal.h"
#include <mach/task.h>
#include <mach/task_info.h>
#include <errno.h>

int
mt_clock_task_getres(mach_port_t task, struct timespec *ts)
{
    ts->tv_sec = 0;
    ts->tv_nsec = MT_NSEC_PER_USEC;
    return 0;
}

int
mt_clock_task_gettime(mach_port_t task, struct timespec *ts)
{
    struct task_basic_info task_data;
    struct task_thread_times_info thread_data;

    mach_msg_type_number_t size = sizeof thread_data;
    kern_return_t error = 
        task_info(task, TASK_THREAD_TIMES_INFO,
                (task_info_t)&thread_data, &size);

    if (error != KERN_SUCCESS) {
        errno = EINVAL;
        return -1;
    }

    size = sizeof task_data;
    error = task_info(task, TASK_BASIC_INFO, (task_info_t)&task_data, &size);
    if (error != KERN_SUCCESS) {
        errno = EINVAL;
        return -1;
    }

    struct timespec tmp;
    tmp.tv_nsec = MT_NSEC_PER_USEC *
        (task_data.user_time.microseconds +
         thread_data.user_time.microseconds);
    tmp.tv_sec = tmp.tv_nsec / MT_NSEC_PER_SEC + 
        task_data.user_time.seconds + thread_data.user_time.seconds;
    tmp.tv_nsec %= MT_NSEC_PER_SEC;

    ts->tv_sec = tmp.tv_sec;
    ts->tv_nsec = tmp.tv_nsec;
    return 0;
}

int
mt_clock_task_settime(mach_port_t task, const struct timespec *ts)
{
    errno = EINVAL;
    return -1;
}
