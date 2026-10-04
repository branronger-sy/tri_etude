#include "metrics.h"
#include "tri.h"
void tri_bubble(int *t, int n) {
  if (!t || n <= 1)
    return;
  for (int i = 0; i < n - 1; i++) {
    int s = 0;
    for (int j = 0; j < n - 1 - i; j++) {
      g_comparisons++;
      if (t[j] > t[j + 1]) {
        int tmp = t[j];
        t[j] = t[j + 1];
        t[j + 1] = tmp;
        s = 1;
      }
    }
    if (!s)
      break;
  }
}
