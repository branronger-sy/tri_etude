#define _POSIX_C_SOURCE 199309L
#include "benchmark.h"
#include "input.h"
#include "metrics.h"
#include "tri.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define COLOR_RESET  "\033[0m"
#define COLOR_BOLD   "\033[1m"
#define COLOR_GREEN  "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_CYAN   "\033[36m"
#define COLOR_RED    "\033[31m"

typedef struct {
    const char *name;
    void (*sort_fn)(int *t, int n); //AI (pointeur de fonction generique)
    int is_quadratic;
} RegisteredAlgorithm;

static RegisteredAlgorithm g_algorithms[] = {
    {"Bubble_Sort",    tri_bubble,    1},
    {"Selection_Sort", tri_selection, 1},
    {"Insertion_Sort", tri_insertion, 1},
    {"Merge_Sort",     tri_merge,     0},
    {"Quick_Sort",     tri_quick,     0},
    {"Heap_Sort",      tri_heap,      0},
    {"Qsort_std_ref",  tri_qsort_std, 0},
};

static const int NUM_ALGORITHMS = sizeof(g_algorithms) / sizeof(g_algorithms[0]);

static void ensure_results_dir(void) //AI
{
    struct stat st = {0};
    if (stat("results", &st) == -1) {
        mkdir("results", 0755);
    }
}

BenchmarkResult benchmark_run_single(const char *algo_name, void (*sort_fn)(int *t, int n), InputType input_type, int size)
{
    BenchmarkResult res;
    res.algorithm_name = algo_name;
    res.input_type = input_type;
    res.size = size;
    res.time_sec = 0.0;
    res.time_ms = 0.0;
    res.comparisons = 0;
    res.is_sorted_ok = (size <= 1) ? 1 : 0;

    if (size <= 0 || !sort_fn) return res;

    int *arr = (int *)malloc((size_t)size * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Erreur malloc pour taille %d\n", size);
        return res;
    }

    generate_array(arr, size, input_type);

    reset_comparisons();
    double t_start = get_time_sec();
    sort_fn(arr, size);
    double t_end = get_time_sec();

    res.time_sec = t_end - t_start;
    res.time_ms = res.time_sec * 1000.0;
    res.comparisons = g_comparisons;
    res.is_sorted_ok = is_sorted(arr, size);

    free(arr);
    return res;
}

void benchmark_run_demo(void)
{
    printf("\n%s========================================================================%s\n", COLOR_CYAN, COLOR_RESET);
    printf("                  DEMO BENCHMARK DES ALGORITHMES DE TRI                 \n");
    printf("%s========================================================================%s\n\n", COLOR_CYAN, COLOR_RESET);

    int demo_sizes[] = {100, 500, 1000, 5000, 10000};
    int num_demo_sizes = sizeof(demo_sizes) / sizeof(demo_sizes[0]);

    printf("+-----------------+--------------+--------+-------------+----------------+----------+\n");
    printf("| %-15s | %-12s | %-6s | %-11s | %-14s | %-8s |\n",
           "Algorithme", "Type", "Taille", "Temps (ms)", "Comparaisons", "Statut");
    printf("+-----------------+--------------+--------+-------------+----------------+----------+\n");

    for (int s = 0; s < num_demo_sizes; s++) {
        int n = demo_sizes[s];
        for (int a = 0; a < NUM_ALGORITHMS; a++) {
            if (strcmp(g_algorithms[a].name, "Bubble_Sort") != 0 &&
                strcmp(g_algorithms[a].name, "Selection_Sort") != 0) {
                continue;
            }

            BenchmarkResult res = benchmark_run_single(g_algorithms[a].name, g_algorithms[a].sort_fn, INPUT_RANDOM, n);
            const char *status_str = res.is_sorted_ok ? (COLOR_GREEN "[PASS]" COLOR_RESET) : (COLOR_RED "[FAIL]" COLOR_RESET);

            printf("| %-15s | %-12s | %-6d | %8.3f ms | %14llu | %-17s |\n",
                   g_algorithms[a].name, input_type_name(res.input_type), res.size,
                   res.time_ms, res.comparisons, status_str);
        }
        printf("+-----------------+--------------+--------+-------------+----------------+----------+\n");
    }

    printf("\n%s[OK]%s Demo terminee avec succes.\n\n", COLOR_GREEN, COLOR_RESET);
}

void benchmark_run_full(void)
{
    ensure_results_dir();

    const char *csv_path = "results/benchmark_summary.csv";
    FILE *f = fopen(csv_path, "w");
    if (!f) {
        fprintf(stderr, "Erreur creation fichier %s\n", csv_path);
        return;
    }

    fprintf(f, "Algorithm,InputType,Size,Time_Seconds,Time_MS,Comparisons,Sorted\n");

    int full_sizes[] = {100, 500, 1000, 2500, 5000, 10000, 25000, 50000, 100000};
    int num_sizes = sizeof(full_sizes) / sizeof(full_sizes[0]);

    printf("\nExecution du benchmark complet (sauvegarde dans %s)...\n", csv_path);

    for (int t = 0; t < INPUT_TYPE_COUNT; t++) {
        InputType itype = (InputType)t;
        printf("--> Cas: %s\n", input_type_name(itype));

        for (int s = 0; s < num_sizes; s++) {
            int n = full_sizes[s];

            for (int a = 0; a < NUM_ALGORITHMS; a++) {
                if (g_algorithms[a].is_quadratic && n > 25000) {
                    continue;
                }

                BenchmarkResult res = benchmark_run_single(g_algorithms[a].name, g_algorithms[a].sort_fn, itype, n);
                if (res.is_sorted_ok) {
                    fprintf(f, "%s,%s,%d,%.6f,%.3f,%llu,%d\n",
                            res.algorithm_name, input_type_name(res.input_type),
                            res.size, res.time_sec, res.time_ms, res.comparisons, res.is_sorted_ok);
                }
            }
        }
    }

    fclose(f);
    printf("\n%s[OK]%s Benchmark complet termine! Fichier sauvegarde dans %s\n\n", COLOR_GREEN, COLOR_RESET, csv_path);
}

void benchmark_run_tests(void)
{
    printf("\n=======================================================\n");
    printf("         TESTS DE VALIDATION DES ALGORITHMES           \n");
    printf("=======================================================\n\n");

    int test_sizes[] = {0, 1, 2, 10, 100, 1000};
    int num_sizes = sizeof(test_sizes) / sizeof(test_sizes[0]);
    int total_tests = 0;
    int passed_tests = 0;

    for (int a = 0; a < NUM_ALGORITHMS; a++) {
        if (strcmp(g_algorithms[a].name, "Bubble_Sort") != 0 &&
            strcmp(g_algorithms[a].name, "Selection_Sort") != 0) {
            continue;
        }

        int algo_passed = 1;
        printf("Test de %-16s ... ", g_algorithms[a].name);

        for (int t = 0; t < INPUT_TYPE_COUNT; t++) {
            for (int s = 0; s < num_sizes; s++) {
                int n = test_sizes[s];
                total_tests++;

                BenchmarkResult res = benchmark_run_single(g_algorithms[a].name, g_algorithms[a].sort_fn, (InputType)t, n);
                if (!res.is_sorted_ok) {
                    algo_passed = 0;
                    fprintf(stderr, "\n  [ECHEC] type=%s, taille=%d\n", input_type_name((InputType)t), n);
                } else {
                    passed_tests++;
                }
            }
        }

        if (algo_passed) {
            printf("%s[PASSE]%s\n", COLOR_GREEN, COLOR_RESET);
        } else {
            printf("%s[ECHEC]%s\n", COLOR_RED, COLOR_RESET);
        }
    }

    printf("\nResume: %d / %d tests valides.\n\n", passed_tests, total_tests);
}
