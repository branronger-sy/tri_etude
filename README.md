Absolutely. Here's a clean **multi-file C project** where each responsibility is separated. This is a good structure for your sorting benchmark.

```text
project/
│
├── main.c
│
├── sorting.c
├── sorting.h
│
├── timer.c
├── timer.h
│
├── data.c
├── data.h
│
├── benchmark.c
├── benchmark.h
│
├── plot.gp
│
└── results.dat
```

Below is what I would put in **each file**.

---

## `sorting.h`

Contains the declarations of your sorting algorithms.

```c
#ifndef SORTING_H
#define SORTING_H

void insertion_sort(int *array, int n);
void selection_sort(int *array, int n);
void bubble_sort(int *array, int n);
void quick_sort(int *array, int n);
void merge_sort(int *array, int n);

#endif
```

---

## `sorting.c`

Contains the actual implementations.

For now, I'll put only **insertion sort** and leave the others ready for you to implement.

```c
#include "sorting.h"

void insertion_sort(int *array, int n)
{
    for (int i = 1; i < n; i++) {

        int key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = key;
    }
}

void selection_sort(int *array, int n)
{
    /* TODO */
}

void bubble_sort(int *array, int n)
{
    /* TODO */
}

void quick_sort(int *array, int n)
{
    /* TODO */
}

void merge_sort(int *array, int n)
{
    /* TODO */
}
```

---

# `timer.h`

This exposes the timer function.

```c
#ifndef TIMER_H
#define TIMER_H

double measure_time(void (*sort)(int *, int), int *array, int n);

#endif
```

Notice this:

```c
void (*sort)(int *, int)
```

That's a **function pointer**.

It means the timer can receive any sorting algorithm.

For example:

```c
measure_time(insertion_sort, array, n);
```

---

# `timer.c`

The timer implementation:

```c
#include <time.h>
#include "timer.h"

double measure_time(void (*sort)(int *, int), int *array, int n)
{
    struct timespec start;
    struct timespec end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    sort(array, n);

    clock_gettime(CLOCK_MONOTONIC, &end);

    return (end.tv_sec - start.tv_sec)
         + (end.tv_nsec - start.tv_nsec) / 1e9;
}
```

Now the timer doesn't care whether it's:

```text
insertion
selection
bubble
quick
merge
```

It simply receives a function and measures it.

---

# `data.h`

This contains the data-generation functions.

```c
#ifndef DATA_H
#define DATA_H

void generate_random(int *array, int n);
void generate_sorted(int *array, int n);
void generate_reversed(int *array, int n);
void generate_semi_sorted(int *array, int n);

#endif
```

---

# `data.c`

```c
#include <stdlib.h>
#include "data.h"

void generate_random(int *array, int n)
{
    for (int i = 0; i < n; i++)
        array[i] = rand();
}

void generate_sorted(int *array, int n)
{
    for (int i = 0; i < n; i++)
        array[i] = i;
}

void generate_reversed(int *array, int n)
{
    for (int i = 0; i < n; i++)
        array[i] = n - i;
}

void generate_semi_sorted(int *array, int n)
{
    /* Start sorted */
    for (int i = 0; i < n; i++)
        array[i] = i;

    /* Randomly disturb some elements */
    for (int i = 0; i < n / 10; i++) {

        int a = rand() % n;
        int b = rand() % n;

        int temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }
}
```

Now your program can easily choose:

```bash
./comp random
./comp sorted
./comp reversed
./comp semi-sorted
```

---

# `benchmark.h`

This contains the benchmark interface.

```c
#ifndef BENCHMARK_H
#define BENCHMARK_H

void run_benchmark(const char *data_type);

#endif
```

---

# `benchmark.c`

This is where the experiment is organized.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "benchmark.h"
#include "sorting.h"
#include "timer.h"
#include "data.h"

void run_benchmark(const char *data_type)
{
    int sizes[] = {
        1000,
        5000,
        10000,
        50000,
        100000
    };

    int nb_sizes = sizeof(sizes) / sizeof(sizes[0]);

    FILE *file = fopen("results.dat", "w");

    if (file == NULL) {
        perror("results.dat");
        return;
    }

    for (int i = 0; i < nb_sizes; i++) {

        int n = sizes[i];

        int *original = malloc(n * sizeof(int));
        int *array = malloc(n * sizeof(int));

        if (original == NULL || array == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        /*
         * Generate the requested type of data
         */
        if (strcmp(data_type, "random") == 0)
            generate_random(original, n);

        else if (strcmp(data_type, "sorted") == 0)
            generate_sorted(original, n);

        else if (strcmp(data_type, "reversed") == 0)
            generate_reversed(original, n);

        else if (strcmp(data_type, "semi-sorted") == 0)
            generate_semi_sorted(original, n);

        else {
            printf("Unknown data type: %s\n", data_type);
            free(original);
            free(array);
            fclose(file);
            return;
        }

        /*
         * Copy original data
         * and benchmark insertion sort
         */
        for (int j = 0; j < n; j++)
            array[j] = original[j];

        double insertion_time =
            measure_time(insertion_sort, array, n);

        /*
         * Save result
         */
        fprintf(file, "%d %.9f\n",
                n,
                insertion_time);

        printf("%d elements -> %.9f seconds\n",
               n,
               insertion_time);

        free(original);
        free(array);
    }

    fclose(file);
}
```

For now this benchmarks only insertion sort.

Later you'll add:

```c
selection_sort
bubble_sort
quick_sort
merge_sort
```

and the `.dat` file will have multiple columns.

---

# `main.c`

This becomes extremely small.

```c
#include <stdio.h>
#include <stdlib.h>

#include "benchmark.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {

        printf("Usage: %s <data-type>\n", argv[0]);

        printf("\nData types:\n");
        printf("  random\n");
        printf("  sorted\n");
        printf("  reversed\n");
        printf("  semi-sorted\n");

        return EXIT_FAILURE;
    }

    run_benchmark(argv[1]);

    /*
     * Automatically generate the graph
     */
    system("gnuplot plot.gp");

    return EXIT_SUCCESS;
}
```

This is exactly the benefit of separating everything.

`main.c` basically says:

```text
"Give me a data type."
        ↓
"Run benchmark."
        ↓
"Generate graph."
```

---

# `plot.gp`

For your current single algorithm:

```gnuplot
set terminal png
set output "graph.png"

set title "Insertion Sort Performance"
set xlabel "Number of elements"
set ylabel "Time (seconds)"

set grid

plot "results.dat" using 1:2 \
    smooth csplines \
    title "Insertion Sort"
```

Later, when you have five algorithms:

```gnuplot
plot \
    "results.dat" using 1:2 smooth csplines title "Insertion Sort", \
    "results.dat" using 1:3 smooth csplines title "Selection Sort", \
    "results.dat" using 1:4 smooth csplines title "Bubble Sort", \
    "results.dat" using 1:5 smooth csplines title "Quick Sort", \
    "results.dat" using 1:6 smooth csplines title "Merge Sort"
```

---

# `results.dat`

You **don't really need to write this manually**.

It is generated by `benchmark.c`.

For one algorithm it will look like:

```text
1000 0.000002100
5000 0.000041200
10000 0.000162300
50000 0.004103200
100000 0.016823100
```

Later, with five algorithms:

```text
1000    0.000003    0.000002    0.000004    0.000001    0.000002
5000    0.000041    0.000035    0.000050    0.000006    0.000010
10000   0.000162    0.000140    0.000180    0.000012    0.000022
...
```

---

# Compile everything

From inside `project/`:

```bash
gcc main.c sorting.c timer.c data.c benchmark.c -o comp
```

Then:

```bash
./comp random
```

or:

```bash
./comp semi-sorted
```

or:

```bash
./comp sorted
```

or:

```bash
./comp reversed
```

The complete flow becomes:

```text
./comp semi-sorted
       │
       ▼
    main.c
       │
       ▼
 benchmark.c
       │
       ├──────────────► data.c
       │                  │
       │                  ▼
       │             generate_semi_sorted()
       │
       ├──────────────► sorting.c
       │                  │
       │                  ▼
       │             insertion_sort()
       │
       ├──────────────► timer.c
       │                  │
       │                  ▼
       │             measure_time()
       │
       ▼
 results.dat
       │
       ▼
   plot.gp
       │
       ▼
   graph.png
```

### One thing I'd change for your final project

Once you add all five algorithms, I'd make **one more abstraction**: an array of sorting functions and their names.

Then instead of writing:

```c
measure_time(insertion_sort, ...);
measure_time(selection_sort, ...);
measure_time(bubble_sort, ...);
measure_time(quick_sort, ...);
measure_time(merge_sort, ...);
```

you can have:

```c
SortFunction algorithms[] = {
    insertion_sort,
    selection_sort,
    bubble_sort,
    quick_sort,
    merge_sort
};
```

and loop over them. That will make `benchmark.c` much cleaner and is a very nice use of **function pointers in C**.

Continue organizing the benchmark

* Add all five sorting algorithms
* Use function pointers in benchmark.c
