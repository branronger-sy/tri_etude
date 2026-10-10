#include "benchmark.h"
#include <stdio.h>
#include <string.h>

static void print_help(void) {
  printf("Usage:\n");
  printf("  ./benchmark --demo [Type] [Algo]\n");
  printf("  ./benchmark --full [Type] [Algo]\n");
  printf("  ./benchmark --test [Algo]\n");
  printf("  ./benchmark [Type]  (ex: random, sorted, reverse, nearly, duplicates)\n");
}

int main(int argc, char *argv[]) {
  const char *arg1 = (argc > 1) ? argv[1] : "--demo";
  const char *arg2 = (argc > 2) ? argv[2] : NULL;
  const char *arg3 = (argc > 3) ? argv[3] : NULL;

  if (strcmp(arg1, "--demo") == 0) {
    benchmark_run_demo(arg2, arg3);
    return 0;
  }
  if (strcmp(arg1, "--full") == 0) {
    benchmark_run_full(arg2, arg3);
    return 0;
  }
  if (strcmp(arg1, "--test") == 0) {
    benchmark_run_tests(arg2);
    return 0;
  }
  if (strcmp(arg1, "--help") == 0 || strcmp(arg1, "-h") == 0) {
    print_help();
    return 0;
  }
  if (parse_input_type(arg1) >= 0 || strcmp(arg1, "all") == 0) {
    benchmark_run_full(arg1, arg2);
    return 0;
  }

  print_help();
  return 1;
}
