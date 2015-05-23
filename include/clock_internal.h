#ifndef CLOCK_INTERNAL_H
#define CLOCK_INTERNAL_H

#include "clock.h"

#ifndef NSEC_PER_USEC
#   define NSEC_PER_USEC 1000
#endif

#define CLOCK_MASK (3UL << 32)
#define PORT_MASK (UINT64_MAX >> 32)

#endif /* !CLOCK_H */
