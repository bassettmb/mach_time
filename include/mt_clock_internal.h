#ifndef MT_CLOCK_INTERNAL_H
#define MT_CLOCK_INTERNAL_H

#include "mt_clock.h"

#define MT_EXPORT __attribute__((visibility("default")))

#define MT_NSEC_PER_USEC 1000
#define MT_NSEC_PER_SEC 1000000000

#define MT_CLOCK_MASK (3UL << 32)
#define MT_PORT_MASK (UINT64_MAX >> 32)

#endif /* !MT_CLOCK_INTERNAL_H */
