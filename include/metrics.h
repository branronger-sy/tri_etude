#ifndef METRICS_H
#define METRICS_H
#include <time.h>
extern unsigned long long g_comparisons;
void reset_comparisons(void);
double get_time_sec(void);
#endif
