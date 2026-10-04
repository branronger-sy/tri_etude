#include "tri.h"

//AI (weak symbols: permet de compiler sans bloquer sur le code de B et C)
__attribute__((weak)) void tri_insertion(int *t, int n) { (void)t; (void)n; }
__attribute__((weak)) void tri_merge(int *t, int n) { (void)t; (void)n; }
__attribute__((weak)) void tri_quick(int *t, int n) { (void)t; (void)n; }
__attribute__((weak)) void tri_heap(int *t, int n) { (void)t; (void)n; }
__attribute__((weak)) void tri_qsort_std(int *t, int n) { (void)t; (void)n; }
