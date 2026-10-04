#define _POSIX_C_SOURCE 199309L
#include "metrics.h"
#include <time.h>

unsigned long long g_comparisons = 0;

void reset_comparisons(void)
{
    g_comparisons = 0;
}

double get_time_sec(void) //AI (clock_gettime pour precision nanoseconde)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}
