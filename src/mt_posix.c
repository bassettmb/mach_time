#include "mt_clock.h"
#include "mt_clock_internal.h"
#include "mt_posix.h"


/* We mark these symbols as weak in case Apple ever properly supports the
 * posix highres clock API. We cannot alias these symbols because of Mach-O
 * constraints.
 */

MT_EXPORT MT_WEAK int
clock_getres(clockid_t clock_id, struct timespec *res)
{
    return mt_clock_getres(clock_id, res);
}

MT_EXPORT MT_WEAK int
clock_gettime(clockid_t clock_id, struct timespec *ts)
{
    return mt_clock_gettime(clock_id, ts);
}

MT_EXPORT MT_WEAK int
clock_settime(clockid_t clock_id, const struct timespec *ts)
{
    return mt_clock_settime(clock_id, ts);
}

MT_EXPORT MT_WEAK int
clock_getcpuclockid(pid_t pid, clockid_t *clock_id)
{
    return mt_clock_getcpuclockid(pid, clock_id);
}

MT_EXPORT MT_WEAK int
pthread_getcpuclockid(pthread_t thread, clockid_t *clock_id)
{
    return mt_pthread_getcpuclockid(thread, clock_id);
}
