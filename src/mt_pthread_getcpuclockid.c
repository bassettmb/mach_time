#include "mt_clock.h"
#include "mt_clock_internal.h"
#include <mach/mach_types.h>
#include <errno.h>

MT_EXPORT int
mt_pthread_getcpuclockid(pthread_t threadid, mt_clockid_t *clock_id) 
{
    if (!clock_id)
        return EFAULT;

    /* If this thread is the current thread, we don't need to deallocate the
     * port -- it gets sent to us without an added reference */

    /* Note: We don't need to deallocate this port. We only borrow it from the
     *       global pthread structures.
     */
    mach_port_t port = pthread_mach_thread_np(threadid);
    if (port == MACH_PORT_NULL)
        return ESRCH;

    *clock_id = MT_CLOCK_THREAD_CPUTIME_ID | port;
    return 0;
}
