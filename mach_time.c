#include "mach_time.h"

#include <mach/mach_host.h>
#include <mach/clock.h>
#include <mach/clock_priv.h> /* the priv is for privileged */

#include <assert.h>
#include <errno.h>

static clock_serv_t get_mach_calend_clock(void);
static clock_serv_t get_mach_system_clock(void);

static int clock_serv_getres(clock_serv_t clk, struct timespec *res);
static int clock_serv_gettime(clock_serv_t serv, struct timespec *ts);
static int clock_serv_settime(clock_serv_t serv, const struct timespec *ts);


clock_serv_t
get_mach_system_clock(void)
{
    static clock_serv_t system_clock = MACH_PORT_NULL;
    kern_return_t kres;

    if (system_clock == MACH_PORT_NULL) {
        kres = host_get_clock_service(
                mach_host_self(), SYSTEM_CLOCK, &system_clock);
        if (kres != KERN_SUCCESS)
            errno = EINVAL;
    }

    return system_clock;
}

clock_serv_t
get_mach_calend_clock(void)
{
    static clock_serv_t calend_clock = MACH_PORT_NULL;

    if (calend_clock == MACH_PORT_NULL) {
        kern_return_t kres;
        kres = host_get_clock_service(
                mach_host_self(), CALENDAR_CLOCK, &calend_clock);
        if (kres != KERN_SUCCESS)
            errno = EINVAL;
    }

    return calend_clock;
}

int
clock_serv_gettime(clock_serv_t serv, struct timespec *ts)
{
    kern_return_t kres;
    mach_timespec_t mts;

    kres = clock_get_time(serv, &mts);
    if (kres != KERN_SUCCESS) {
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
    kern_return_t kres;
    mach_timespec_t mts;

    mts.tv_sec = ts->tv_sec;
    mts.tv_nsec = ts->tv_nsec;

    /* This should always fail, but we'll give it a shot. */
    kres = clock_set_time(serv, mts);
    if (kres != KERN_SUCCESS) {
        errno = EPERM;
        return -1;
    }

    return 0;
}

int
clock_serv_getres(clock_serv_t clk, struct timespec *res)
{
    kern_return_t kres;
    clock_res_t nsec;
    mach_msg_type_number_t count;

    kres = clock_get_attributes(clk, CLOCK_GET_TIME_RES, &nsec, &count);
    if (kres != KERN_SUCCESS) {
        errno = EINVAL;
        return -1;
    }

    res->tv_sec = nsec / NSEC_PER_SEC;
    res->tv_nsec = nsec % NSEC_PER_SEC;
    return 0;
}

/* In the functions below, we switch on the clk_id every time instead of
 * shoving it into a function because, while the current functionality goes
 * through the clock server mach api, the thread-specific clocks can't if they
 * are ever implemented.
 */

int
clock_getres(clockid_t clk_id, struct timespec *res)
{
    kern_return_t kres;
    clock_serv_t clk;
    int nsecs;
    mach_msg_type_number_t count;

    if (!res) {
        errno = EFAULT;
        return -1;
    }

    switch (clk_id) {
        case CLOCK_MONOTONIC:
            clk = get_mach_calend_clock();
            break;
        case CLOCK_REALTIME:
            clk = get_mach_system_clock();
            break;
        default:
            /* unimplemented */
            errno = EINVAL;
            return -1;
    }

    if (clk == MACH_PORT_NULL) {
        errno = EINVAL;
        return -1;
    }

    return clock_serv_getres(clk, res);
}

int
clock_gettime(clockid_t clk_id, struct timespec *ts)
{
    clock_serv_t clk;

    if (!ts) {
        errno = EFAULT;
        return -1;
    }

    switch (clk_id) {
        case CLOCK_MONOTONIC:
            clk = get_mach_calend_clock();
            break;
        case CLOCK_REALTIME:
            clk = get_mach_system_clock();
            break;
        default:
            /* unimplemented */
            errno = EINVAL;
            return -1;
    }

    if (clk == MACH_PORT_NULL) {
        errno = EINVAL;
        return -1;
    }

    return clock_serv_gettime(clk, ts);
}

int
clock_settime(clockid_t clk_id, const struct timespec *ts)
{
    clock_serv_t clk;

    if (!ts) {
        errno = EFAULT;
        return -1;
    }

    switch (clk_id) {
        case CLOCK_MONOTONIC:
            clk = get_mach_calend_clock();
            break;
        case CLOCK_REALTIME:
            clk = get_mach_system_clock();
            break;
        default:
            /* unimplemented */
            errno = EINVAL;
            return -1;
    }

    if (clk == MACH_PORT_NULL) {
        errno = EINVAL;
        return -1;
    }

    return clock_serv_settime(clk, ts);
}
