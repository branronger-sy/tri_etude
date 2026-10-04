#include "tri.h"
#include "metrics.h"

/**
 * Selection Sort
 * --------------
 * Reference:
 * - Cormen, Leiserson, Rivest, Stein (CLRS), Chapter 2, Exercises.
 * - Knuth, The Art of Computer Programming, Vol 3, Section 5.2.3.
 * - Sedgewick, Algorithms in C, Chapter 6.
 *
 * Characteristics:
 * - Time Complexity:
 *     - Best Case:    Theta(n^2) comparisons
 *     - Average Case: Theta(n^2) comparisons
 *     - Worst Case:   Theta(n^2) comparisons
 * - Space Complexity: O(1) (In-place)
 * - Stability:        Unstable (long-distance swap can invert relative order)
 * - Swaps:            At most n - 1 swaps (optimal for minimal memory writes)
 */
void tri_selection(int *t, int n)
{
    if (!t || n <= 1) return;

    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            g_comparisons++;
            if (t[j] < t[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int tmp = t[i];
            t[i] = t[min_index];
            t[min_index] = tmp;
        }
    }
}
