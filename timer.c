#include "timer.h"
#include <time.h>

// void (*sort)(int *, int) argument 3la chkel function , so it can hold any
// sorting algo

double measure_time(void (*sort)(int *, int), int *array, int n) {
  struct timespec start;
  struct timespec end;

  clock_gettime(CLOCK_MONOTONIC, &start);
  sort(array, n);
  clock_gettime(CLOCK_MONOTONIC, &end);

  double time_spent =
      (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
  return time_spent;
}
