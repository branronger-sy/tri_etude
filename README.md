# Sorting Algorithms Benchmark in C

Étude comparative des algorithmes de tri en langage C avec mesure précise des temps d'exécution (en millisecondes), export automatique des résultats au format CSV et génération de courbes graphiques via Gnuplot.

---

## Utilisation rapide

Le projet s'exécute avec un script qui assure automatiquement la compilation et l'exécution :
* **Linux / macOS** : `./run.sh`
* **Windows (PowerShell)** : `.\run` (ou `.\run.bat`)
* **Windows (CMD)** : `run` (ou `run.bat`)

### 1. Tests de validation
Vérifie la validité du tri de chaque algorithme sur différentes tailles et distributions :
```bash
./run.sh test
./run.sh test Quick_Sort

.\run test
.\run test Quick_Sort

run test
run test Quick_Sort
```

### 2. Démo rapide
Affiche un benchmark rapide dans le terminal (tailles de 100 à 25 000 éléments) :
```bash
./run.sh demo
./run.sh demo sorted
./run.sh demo random Heap_Sort

run demo
run demo sorted
run demo random Heap_Sort
```

### 3. Benchmark complet et génération des graphes
Lance les tests sur toutes les tailles (jusqu'à 100 000), exporte les fichiers CSV dans `results/` et trace les courbes PNG avec Gnuplot :
```bash
./run.sh full
./run.sh full random
./run.sh full sorted Heap_Sort

run full
run full random
run full sorted Heap_Sort
```

Lancement direct d'un type de données :
```bash
./run.sh random
./run.sh sorted
./run.sh reverse
./run.sh nearly
./run.sh duplicates
```

### 4. Nettoyage
Supprime le binaire compilé ainsi que les graphes générés :
```bash
./run.sh clean
run clean
```

---

## Algorithmes implémentés (7 algorithmes)

1. **Tri à bulles** (`Bubble_Sort` / `tri_bubble`) : $O(n^2)$
2. **Tri par sélection** (`Selection_Sort` / `tri_selection`) : $O(n^2)$
3. **Tri par insertion** (`Insertion_Sort` / `tri_insertion`) : $O(n^2)$ pire cas, $O(n)$ si quasi-trié
4. **Tri fusion** (`Merge_Sort` / `tri_merge`) : $O(n \log n)$
5. **Tri rapide** (`Quick_Sort` / `tri_quick` - pivot médian) : $O(n \log n)$
6. **Tri par tas** (`Heap_Sort` / `tri_heap`) : $O(n \log n)$
7. **Tri standard C** (`Qsort_std` / `tri_qsort_std`) : référence standard (`qsort`)

---

## Types de données testés

* `random` : Nombres aléatoires non triés.
* `sorted` : Données déjà triées par ordre croissant.
* `reverse` : Données triées par ordre décroissant (pire cas).
* `nearly` : Données presque triées (avec un faible pourcentage de permutations).
* `duplicates` : Données contenant de nombreux doublons.

---

## Structure du projet

```
tri_etude/
├── include/
│   ├── benchmark.h
│   └── tri.h
├── src/
│   ├── benchmark.c
│   ├── input.c
│   ├── main.c
│   └── tri.c
├── results/
├── plot.gp
├── run.sh
├── run.bat
└── README.md
```

---

## Prérequis

* **GCC** (ou tout compilateur C supportant C99 / POSIX).
* **Gnuplot** *(optionnel)* : Nécessaire uniquement pour générer les images des courbes `.png`.
  * Arch Linux : `sudo pacman -S gnuplot`
  * Ubuntu / Debian : `sudo apt install gnuplot`

