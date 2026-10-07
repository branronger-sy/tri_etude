#include "benchmark.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void generate_array(int *t, int n, InputType type) {
    if (!t || n<=0) return;
    switch (type) {
        case INPUT_RANDOM:
            for (int i=0; i<n; i++) t[i]=rand()%(n*5+1);
            break;
        case INPUT_SORTED:
            for (int i=0; i<n; i++) t[i]=i;
            break;
        case INPUT_REVERSE_SORTED:
            for (int i=0; i<n; i++) t[i]=n-1-i;
            break;
        case INPUT_NEARLY_SORTED: {
            for (int i=0; i<n; i++) t[i]=i;
            int swaps=n/20;
            if (swaps<1 && n>1) swaps=1;
            for (int k=0; k<swaps; k++) {
                int i=rand()%n, j=rand()%n;
                int tmp=t[i]; t[i]=t[j]; t[j]=tmp;
            }
            break;
        }
        case INPUT_MANY_DUPLICATES:
            for (int i=0; i<n; i++) t[i]=rand()%10;
            break;
        default:
            for (int i=0; i<n; i++) t[i]=rand();
            break;
    }
}

const char *input_type_name(InputType type) {
    switch (type) {
        case INPUT_RANDOM:          return "Random";
        case INPUT_SORTED:          return "Sorted";
        case INPUT_REVERSE_SORTED:  return "Reverse_Sorted";
        case INPUT_NEARLY_SORTED:   return "Nearly_Sorted";
        case INPUT_MANY_DUPLICATES: return "Many_Duplicates";
        default:                    return "Unknown";
    }
}

const char *input_type_filename(InputType type) {
    switch (type) {
        case INPUT_RANDOM:          return "results/random.csv";
        case INPUT_SORTED:          return "results/sorted.csv";
        case INPUT_REVERSE_SORTED:  return "results/reverse_sorted.csv";
        case INPUT_NEARLY_SORTED:   return "results/nearly_sorted.csv";
        case INPUT_MANY_DUPLICATES: return "results/many_duplicates.csv";
        default:                    return "results/benchmark.csv";
    }
}

int parse_input_type(const char *str) {
    if (!str) return -1;
    if (strcasecmp(str, "random")==0) return INPUT_RANDOM;
    if (strcasecmp(str, "sorted")==0) return INPUT_SORTED;
    if (strcasecmp(str, "reverse")==0 || strcasecmp(str, "reverse_sorted")==0) return INPUT_REVERSE_SORTED;
    if (strcasecmp(str, "nearly")==0  || strcasecmp(str, "nearly_sorted")==0)  return INPUT_NEARLY_SORTED;
    if (strcasecmp(str, "duplicates")==0 || strcasecmp(str, "many_duplicates")==0) return INPUT_MANY_DUPLICATES;
    return -1;
}

int save_array(const char *filename, const int *t, int n) {
    if (!filename || !t || n<=0) return 0;
    FILE *file=fopen(filename, "wb");
    if (!file) return 0;
    size_t written=fwrite(t, sizeof(int), (size_t)n, file);
    fclose(file);
    return written==(size_t)n;
}

int load_array(const char *filename, int *t, int n) {
    if (!filename || !t || n<=0) return 0;
    FILE *file=fopen(filename, "rb");
    if (!file) return 0;
    size_t read=fread(t, sizeof(int), (size_t)n, file);
    fclose(file);
    return read==(size_t)n;
}
