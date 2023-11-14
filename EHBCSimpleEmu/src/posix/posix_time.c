#define _POSIX_C_SOURCE 200809L

#include "posix/posix_time.h"

#include <time.h>
#include <errno.h>

int get_timestamp(long* nsec, time_t* sec) {
    struct timespec tspec;

    int err = clock_gettime(CLOCK_REALTIME, &tspec);

    *sec = tspec.tv_sec;
    *nsec = tspec.tv_nsec;

    return err ? errno : 0;
}
