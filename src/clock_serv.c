#include "clock_serv_internal.h"

#include <mach/clock.h>
#include <mach/clock_priv.h> /* the priv is for privileged */
#include <mach/mach_host.h>
#include <pthread.h>

#include <errno.h>

clock_serv_t
clock_serv_monotonic(void)
{
    static clock_serv_t clock = MACH_PORT_NULL;
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    if (clock != MACH_PORT_NULL)
        return clock;

    int error = pthread_mutex_lock(&mutex);
    if (error) {
        errno = error;
        return MACH_PORT_NULL;
    }

    if (clock == MACH_PORT_NULL) {
        kern_return_t kerror =
            host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &clock);
        if (kerror != KERN_SUCCESS)
            errno = EINVAL;
    }

    pthread_mutex_unlock(&mutex);
    return clock;
}

clock_serv_t
clock_serv_realtime(void)
{
    static clock_serv_t clock = MACH_PORT_NULL;
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    if (clock != MACH_PORT_NULL)
        return clock;

    int error = pthread_mutex_lock(&mutex);
    if (error) {
        errno = error;
        return MACH_PORT_NULL;
    }

    if (clock == MACH_PORT_NULL) {
        kern_return_t kerror =
            host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &clock);
        if (kerror != KERN_SUCCESS)
            errno = EINVAL;
    }

    pthread_mutex_unlock(&mutex);
    return clock;
}

int
clock_serv_getres(clock_serv_t serv, struct timespec *res)
{
    clock_res_t nsec;
    mach_msg_type_number_t count;

    if (serv == MACH_PORT_NULL) {
        errno = EINVAL;
        return -1;
    }

    kern_return_t error =
        clock_get_attributes(serv, CLOCK_GET_TIME_RES, &nsec, &count);

    if (error != KERN_SUCCESS) {
        errno = EINVAL;
        return -1;
    }

    res->tv_sec = nsec / NSEC_PER_SEC;
    res->tv_nsec = nsec % NSEC_PER_SEC;
    return 0;
}

int
clock_serv_gettime(clock_serv_t serv, struct timespec *ts)
{
    mach_timespec_t mts;
    kern_return_t error = clock_get_time(serv, &mts);

    if (serv == MACH_PORT_NULL) {
        errno = EINVAL;
        return -1;
    }

    if (error != KERN_SUCCESS) {
        errno = EINVAL;
        return -1;
    }

    ts->tv_sec = mts.tv_sec;
    ts->tv_nsec = mts.tv_nsec;
    return 0;
}

int
clock_serv_settime(clock_serv_t serv, const struct timespec *ts)
{
    mach_timespec_t mts = { ts->tv_sec, ts->tv_nsec };

    if (serv == MACH_PORT_NULL) {
        errno = EINVAL;
        return -1;
    }

    /* This should always fail, but we'll give it a shot. */
    kern_return_t error = clock_set_time(serv, mts);
    if (error != KERN_SUCCESS) {
        errno = EPERM;
        return -1;
    }

    return 0;
}
