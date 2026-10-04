#include "input.h"
#include <stdio.h>
#include <stdlib.h>

void generate_array(int *t, int n, InputType type)
{
    if (!t || n <= 0) return;

    switch (type) {
        case INPUT_RANDOM:
            for (int i = 0; i < n; i++) {
                t[i] = rand() % (n * 5 + 1);
            }
            break;

        case INPUT_SORTED:
            for (int i = 0; i < n; i++) {
                t[i] = i;
            }
            break;

        case INPUT_REVERSE_SORTED:
            for (int i = 0; i < n; i++) {
                t[i] = n - 1 - i;
            }
            break;

        case INPUT_NEARLY_SORTED: {
            for (int i = 0; i < n; i++) {
                t[i] = i;
            }
            // Perturb roughly 5% of elements by swapping with nearby elements
            int swaps = n / 20;
            if (swaps < 1 && n > 1) swaps = 1;
            for (int k = 0; k < swaps; k++) {
                int i = rand() % n;
                int j = rand() % n;
                int tmp = t[i];
                t[i] = t[j];
                t[j] = tmp;
            }
            break;
        }

        case INPUT_MANY_DUPLICATES:
            // High collision rate: values constrained to [0..9]
            for (int i = 0; i < n; i++) {
                t[i] = rand() % 10;
            }
            break;

        default:
            for (int i = 0; i < n; i++) {
                t[i] = rand();
            }
            break;
    }
}

const char *input_type_name(InputType type)
{
    switch (type) {
        case INPUT_RANDOM:          return "Random";
        case INPUT_SORTED:          return "Sorted";
        case INPUT_REVERSE_SORTED:  return "Reverse_Sorted";
        case INPUT_NEARLY_SORTED:   return "Nearly_Sorted";
        case INPUT_MANY_DUPLICATES: return "Many_Duplicates";
        default:                    return "Unknown";
    }
}

int save_array(const char *filename, const int *t, int n)
{
    if (!filename || !t || n <= 0) return 0;
    FILE *file = fopen(filename, "wb");
    if (!file) return 0;

    size_t written = fwrite(t, sizeof(int), (size_t)n, file);
    fclose(file);
    return written == (size_t)n;
}

int load_array(const char *filename, int *t, int n)
{
    if (!filename || !t || n <= 0) return 0;
    FILE *file = fopen(filename, "rb");
    if (!file) return 0;

    size_t read = fread(t, sizeof(int), (size_t)n, file);
    fclose(file);
    return read == (size_t)n;
}
