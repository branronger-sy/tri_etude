#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "input.h"

typedef struct {
    const char *algorithm_name;
    InputType input_type;
    int size;
    double time_sec;
    double time_ms;
    unsigned long long comparisons;
    int is_sorted_ok;
} BenchmarkResult;

BenchmarkResult benchmark_run_single(const char *algo_name, void (*sort_fn)(int *t, int n), InputType input_type, int size);
void benchmark_run_demo(void);
void benchmark_run_full(void);
void benchmark_run_tests(void);

#endif
