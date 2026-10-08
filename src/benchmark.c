#define _POSIX_C_SOURCE 199309L
#include "benchmark.h"
#include "tri.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

static double get_time_sec(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

static int is_sorted(const int *t, int n) {
  if (!t || n <= 1)
    return 1;
  for (int i = 1; i < n; i++)
    if (t[i - 1] > t[i])
      return 0;
  return 1;
}

static void ensure_results_dir(void) {
  struct stat st = {0};
  if (stat("results", &st) == -1)
    mkdir("results", 0755);
}

static void benchmark_one(const char *name, void (*sort_fn)(int *t, int n),
                          InputType input_type, int size, FILE *csv_f) {
  if (size <= 0 || !sort_fn)
    return;
  int *arr = (int *)malloc((size_t)size * sizeof(int));
  if (!arr) {
    printf("Erreur d'allocation pour n=%d\n", size);
    return;
  }

  generate_array(arr, size, input_type);

  double t_start = get_time_sec();
  sort_fn(arr, size);
  double t_end = get_time_sec();

  double time_sec = t_end - t_start;
  double time_ms = time_sec * 1000.0;
  int ok = is_sorted(arr, size);

  if (csv_f)
    fprintf(csv_f, "%s,%s,%d,%.6f,%.3f,%d\n", name, input_type_name(input_type),
            size, time_sec, time_ms, ok);
  else
    printf("%-16s | %-14s | %-6d | %8.3f ms | %s\n", name,
           input_type_name(input_type), size, time_ms, ok ? "OK" : "ERREUR");

  free(arr);
}

static void run_algorithms(InputType itype, int size, const char *filter,
                           FILE *csv_f) {
  int quadratic_limit = (!csv_f || size <= 25000);
  int fast_limit = (!csv_f || size <= 100000);

  if (!filter || strcmp(filter, "Bubble_Sort") == 0)
    if (quadratic_limit)
      benchmark_one("Bubble_Sort", tri_bubble, itype, size, csv_f);
  if (!filter || strcmp(filter, "Selection_Sort") == 0)
    if (quadratic_limit)
      benchmark_one("Selection_Sort", tri_selection, itype, size, csv_f);
  if (!filter || strcmp(filter, "Insertion_Sort") == 0)
    if (quadratic_limit)
      benchmark_one("Insertion_Sort", tri_insertion, itype, size, csv_f);
  if (!filter || strcmp(filter, "Merge_Sort") == 0)
    if (fast_limit)
      benchmark_one("Merge_Sort", tri_merge, itype, size, csv_f);
  if (!filter || strcmp(filter, "Quick_Sort") == 0)
    if (fast_limit)
      benchmark_one("Quick_Sort", tri_quick, itype, size, csv_f);
  if (!filter || strcmp(filter, "Qsort_std") == 0)
    if (fast_limit)
      benchmark_one("Qsort_std", tri_qsort_std, itype, size, csv_f);
}

void benchmark_run_demo(const char *type_str, const char *filter) {
  int demo_sizes[] = {100, 500, 1000, 5000, 10000};
  int num = sizeof(demo_sizes) / sizeof(demo_sizes[0]);

  int parsed = parse_input_type(type_str);
  InputType itype = (parsed >= 0) ? (InputType)parsed : INPUT_RANDOM;

  printf("\n=== Demo Benchmark (Type: %s) ===\n\n", input_type_name(itype));
  printf("%-16s | %-14s | %-6s | %-11s | %s\n", "Algorithme", "Type", "Taille",
         "Temps (ms)", "Statut");
  printf("---------------------------------------------------------------\n");

  for (int s = 0; s < num; s++)
    run_algorithms(itype, demo_sizes[s], filter, NULL);

  printf("\nDemo terminee avec succes.\n\n");
}

static void run_type_benchmark(InputType itype, const char *filter) {
  const char *csv_path = input_type_filename(itype);
  FILE *f = fopen(csv_path, "w");
  if (!f) {
    printf("Erreur de creation du fichier %s\n", csv_path);
    return;
  }

  fprintf(f, "Algorithm,InputType,Size,Time_Seconds,Time_MS,Sorted\n");

  int full_sizes[] = {100, 500, 1000, 2500, 5000, 10000, 25000, 50000, 100000};
  int num = sizeof(full_sizes) / sizeof(full_sizes[0]);

  printf("--> %-15s (sauvegarde dans %s)...\n", input_type_name(itype),
         csv_path);

  for (int s = 0; s < num; s++)
    run_algorithms(itype, full_sizes[s], filter, f);

  fclose(f);
}

void benchmark_run_full(const char *type_str, const char *filter) {
  ensure_results_dir();
  int parsed = parse_input_type(type_str);
  if (parsed >= 0) {
    printf("\nBenchmark pour le cas: %s\n", input_type_name((InputType)parsed));
    run_type_benchmark((InputType)parsed, filter);
  } else {
    printf("\nBenchmark complet pour tous les types...\n");
    for (int t = 0; t < INPUT_TYPE_COUNT; t++)
      run_type_benchmark((InputType)t, filter);
  }
  printf("\nBenchmark termine avec succes.\n\n");
}

static int test_algo(const char *name, void (*sort_fn)(int *t, int n)) {
  int test_sizes[] = {1, 2, 10, 100, 1000};
  int num = sizeof(test_sizes) / sizeof(test_sizes[0]);
  int ok = 1;
  for (int t = 0; t < INPUT_TYPE_COUNT; t++) {
    for (int s = 0; s < num; s++) {
      int n = test_sizes[s];
      int *arr = (int *)malloc((size_t)n * sizeof(int));
      if (!arr)
        continue;
      generate_array(arr, n, (InputType)t);
      sort_fn(arr, n);
      if (!is_sorted(arr, n)) {
        ok = 0;
        printf("  Echec: %s type=%s n=%d\n", name,
               input_type_name((InputType)t), n);
      }
      free(arr);
    }
  }
  printf("Test %-16s : %s\n", name, ok ? "PASSE" : "ECHEC");
  return ok;
}

void benchmark_run_tests(const char *filter) {
  printf("\n=== Tests de validation ===\n\n");
  if (!filter || strcmp(filter, "Bubble_Sort") == 0)
    test_algo("Bubble_Sort", tri_bubble);
  if (!filter || strcmp(filter, "Selection_Sort") == 0)
    test_algo("Selection_Sort", tri_selection);
  if (!filter || strcmp(filter, "Insertion_Sort") == 0)
    test_algo("Insertion_Sort", tri_insertion);
  if (!filter || strcmp(filter, "Merge_Sort") == 0)
    test_algo("Merge_Sort", tri_merge);
  if (!filter || strcmp(filter, "Quick_Sort") == 0)
    test_algo("Quick_Sort", tri_quick);
  if (!filter || strcmp(filter, "Qsort_std") == 0)
    test_algo("Qsort_std", tri_qsort_std);
  printf("\n");
}
