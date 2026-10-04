#include "benchmark.h"
#include <stdio.h>
#include <string.h>

static void print_help(void)
{
    printf("Usage:\n");
    printf("  ./bin/benchmark --demo    Demo interactive rapide\n");
    printf("  ./bin/benchmark --full    Benchmark complet et generation CSV\n");
    printf("  ./bin/benchmark --test    Tests de validation unitaire\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2 || strcmp(argv[1], "--demo") == 0) {
        benchmark_run_demo();
        return 0;
    }

    if (strcmp(argv[1], "--full") == 0) {
        benchmark_run_full();
        return 0;
    }

    if (strcmp(argv[1], "--test") == 0) {
        benchmark_run_tests();
        return 0;
    }

    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        print_help();
        return 0;
    }

    print_help();
    return 1;
}
