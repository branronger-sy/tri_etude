# Sorting Algorithms Benchmark in C

## How to Build, Test and Run

### 1. Run Validation Tests
Compile and verify the correctness of all sorting algorithms:
```bash
make test
```
*Output: Verifies that each algorithm correctly sorts arrays of sizes 1 to 1,000 across all input types (`PASSE` / `ECHEC`).*

### 2. Run a Quick Demo
Execute a fast benchmark across array sizes from 100 to 10,000:
```bash
make demo
```

### 3. Run Dedicated Benchmarks (CSV Generation)
Run benchmarks on specific data distributions to generate CSV files in `results/`:
- **Random data:**
  ```bash
  make random
  ```
  *(saves to `results/random.csv`)*
- **Sorted data:**
  ```bash
  make sorted
  ```
  *(saves to `results/sorted.csv`)*
- **Reverse sorted data:**
  ```bash
  make reverse
  ```
  *(saves to `results/reverse.csv`)*
- **Nearly sorted data:**
  ```bash
  make nearly
  ```
  *(saves to `results/nearly.csv`)*
- **Many duplicate values:**
  ```bash
  make duplicates
  ```
  *(saves to `results/duplicates.csv`)*
- **All distributions at once:**
  ```bash
  make full
  ```

### 4. Direct Executable Usage
You can also run `./benchmark` directly with specific parameters:
```bash
./benchmark --demo [Type] [Algorithm]
./benchmark --full [Type] [Algorithm]
./benchmark --test [Algorithm]
```
Examples:
```bash
./benchmark --demo sorted Quick_Sort
./benchmark --test Insertion_Sort
```

### 5. Clean Up
Remove the compiled binary:
```bash
make clean
```
*(No `.o` intermediate files or temporary folders are created, keeping the workspace 100% clean).*

---

## Description du Projet

Projet comparatif des algorithmes de tri en langage C avec mesure précise des temps d'exécution (en millisecondes) et génération automatique des fichiers CSV pour l'analyse graphique.

### Algorithmes Implémentés
1. **Tri à bulles** (`tri_bubble`)
2. **Tri par sélection** (`tri_selection`)
3. **Tri par insertion** (`tri_insertion`)
4. **Tri fusion** (`tri_merge`)
5. **Tri rapide** (`tri_quick` - pivot médian)
6. **Tri standard C** (`tri_qsort_std` - bibliothèque standard `qsort` pour référence)

### Structure du Répertoire
```
tri_etude/
├── include/
│   ├── benchmark.h   # Déclarations du moteur de mesure et types d'entrées
│   └── tri.h         # Prototypes des algorithmes de tri
├── src/
│   ├── benchmark.c   # Mesures de temps et génération CSV
│   ├── input.c       # Génération des différents types de tableaux
│   ├── main.c        # Interface en ligne de commande
│   └── tri.c         # Implémentation unifiée de tous les algorithmes
├── results/          # Fichiers CSV générés pour chaque type d'entrée
├── Makefile          # Script de compilation directe
└── README.md
```
