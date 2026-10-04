# Etude et Benchmark des Algorithmes de Tri en C

Projet de comparaison des algorithmes de tri en C avec mesures de temps et de comparaisons, et generation de graphes via Gnuplot.

## Repartition des taches
- Person A: Infrastructure, tri.h, Makefile, generateur d'entrees (input.c), benchmark, Bubble Sort et Selection Sort.
- Person B: Merge Sort, Quick Sort (2 pivots), Heap Sort, reference qsort().
- Person C: Insertion Sort, scripts Gnuplot, rapport et presentation.

## Compilation et execution
Compiler le projet:
```bash
make
```

Lancer la demo rapide:
```bash
make demo
```

Lancer les tests de validation:
```bash
make test
```

Lancer le benchmark complet (genere results/benchmark_summary.csv):
```bash
make full
```

Nettoyer les fichiers binaires:
```bash
make clean
```
