#include "clock.h"
#include <mach/mach_init.h>
#include <unistd.h>
#include <errno.h>

/*
 * Supporting this for more than the current task would be rough because it
 * would require allocating a new port and stuffing it into clockid_t. It is
 * not expected that clockid_t has resource ownership, so we can't reasonably
 * do force it to own something.
 */
int
clock_getcpuclockid(pid_t pid, clockid_t *clock_id)
{
    if (!pid || pid == getpid())
        *clock_id = CLOCK_PROCESS_CPUTIME_ID | mach_task_self();

    errno = EINVAL;
    return -1;
}
