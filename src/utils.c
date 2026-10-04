#include "utils.h"
#include <string.h>

void copy_array(int *dest, const int *src, int n)
{
    if (dest && src && n > 0) {
        memcpy(dest, src, (size_t)n * sizeof(int));
    }
}

int is_sorted(const int *t, int n)
{
    if (!t || n <= 1) return 1;
    for (int i = 1; i < n; i++) {
        if (t[i - 1] > t[i]) {
            return 0;
        }
    }
    return 1;
}
