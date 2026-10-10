#include "tri.h"
#include <stdlib.h>
void tri_bubble(int *t, int n) {
  if (!t || n <= 1)
    return;
  for (int i = 0; i < n - 1; i++) {
    int s = 0;
    for (int j = 0; j < n - 1 - i; j++) {
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

void tri_selection(int *t, int n) {
  if (!t || n <= 1)
    return;
  for (int i = 0; i < n - 1; i++) {
    int min = i;
    for (int j = i + 1; j < n; j++)
      if (t[j] < t[min])
        min = j;
    if (min != i) {
      int tmp = t[i];
      t[i] = t[min];
      t[min] = tmp;
    }
  }
}

void tri_insertion(int *t, int n) {
  if (!t || n <= 1)
    return;
  for (int i = 1; i < n; i++) {
    int key = t[i];
    int j = i - 1;
    while (j >= 0 && t[j] > key) {
      t[j + 1] = t[j];
      j--;
    }
    t[j + 1] = key;
  }
}

static void merge(int a[], int l, int m, int r) {
  int n1 = m - l + 1, n2 = r - m;
  int *L = (int *)malloc(n1 * sizeof(int));
  int *R = (int *)malloc(n2 * sizeof(int));
  for (int i = 0; i < n1; i++)
    L[i] = a[l + i];
  for (int j = 0; j < n2; j++)
    R[j] = a[m + 1 + j];
  int i = 0, j = 0, k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j])
      a[k++] = L[i++];
    else
      a[k++] = R[j++];
  }
  while (i < n1)
    a[k++] = L[i++];
  while (j < n2)
    a[k++] = R[j++];
  free(L);
  free(R);
}

static void merge_rec(int a[], int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    merge_rec(a, l, m);
    merge_rec(a, m + 1, r);
    merge(a, l, m, r);
  }
}

void tri_merge(int *t, int n) {
  if (!t || n <= 1)
    return;
  merge_rec(t, 0, n - 1);
}

void tri_quick(int *t, int n) {
  if (n <= 1)
    return;
  int pivot = t[n / 2], i = 0, j = n - 1;
  while (i <= j) {
    while (t[i] < pivot)
      i++;
    while (t[j] > pivot)
      j--;
    if (i <= j) {
      int tmp = t[i];
      t[i] = t[j];
      t[j] = tmp;
      i++;
      j--;
    }
  }
  tri_quick(t, j + 1);
  tri_quick(t + i, n - i);
}

static int cmp_int(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

void tri_qsort_std(int *t, int n) {
  if (!t || n <= 1)
    return;
  qsort(t, (size_t)n, sizeof(int), cmp_int);
}

void heap(int T[], int taille, int i) {
  int maxIdx = i;
  int gauche = 2 * i + 1;
  int droite = 2 * i + 2;
  if (gauche < taille && T[gauche] > T[maxIdx])
    maxIdx = gauche;
  if (droite < taille && T[droite] > T[maxIdx])
    maxIdx = droite;
  if (maxIdx != i) {
    int temp = T[i];
    T[i] = T[maxIdx];
    T[maxIdx] = temp;
    heap(T, taille, maxIdx);
  }
}

void tri_heap(int T[], int n) {
  if (!T || n <= 1)
    return;
  for (int i = n / 2 - 1; i >= 0; i--)
    heap(T, n, i);
  for (int i = n - 1; i > 0; i--) {
    int temp = T[0];
    T[0] = T[i];
    T[i] = temp;
    heap(T, i, 0);
  }
}