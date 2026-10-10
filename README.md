# Sorting Algorithms Benchmark in C

Étude comparative des algorithmes de tri en langage C avec mesure précise des temps d'exécution (en millisecondes), export automatique des résultats au format CSV et génération de courbes graphiques via Gnuplot.

---

##  Utilisation rapide

Le projet s'exécute facilement avec un seul script qui s'occupe automatiquement de la compilation et de l'exécution :
* **Linux / macOS** : `./run.sh`
* **Windows** : `run.bat` (ou simplement `run`)

### 1. Tests de validation
Vérifie la validité du tri de chaque algorithme sur différentes tailles et distributions :
```bash
# Linux
./run.sh test
./run.sh test Quick_Sort      # Tester un seul algorithme

# Windows
run test
run test Quick_Sort
```

### 2. Démo rapide
Affiche un benchmark rapide dans le terminal (tailles de 100 à 25 000 éléments) :
```bash
# Linux
./run.sh demo
./run.sh demo sorted          # Démo sur données déjà triées
./run.sh demo random Heap_Sort # Démo d'un algorithme spécifique

# Windows
run demo
run demo sorted
run demo random Heap_Sort
```

### 3. Benchmark complet & Génération des graphes
Lance les tests sur toutes les tailles (jusqu'à 100 000), exporte les fichiers `.csv` dans `results/` et trace les courbes `.png` avec Gnuplot :
```bash
# Linux
./run.sh full                 # Tous les types de données
./run.sh full random          # Uniquement les données aléatoires
./run.sh full sorted Heap_Sort # Un type et un algorithme spécifique

# Windows
run full
run full random
run full sorted Heap_Sort
```

Vous pouvez aussi lancer directement un type de données :
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
# Linux
./run.sh clean

# Windows
run clean
```

---

##  Algorithmes implémentés (7 algorithmes)

1. **Tri à bulles** (`Bubble_Sort` / `tri_bubble`) : $O(n^2)$
2. **Tri par sélection** (`Selection_Sort` / `tri_selection`) : $O(n^2)$
3. **Tri par insertion** (`Insertion_Sort` / `tri_insertion`) : $O(n^2)$ pire cas, $O(n)$ si quasi-trié
4. **Tri fusion** (`Merge_Sort` / `tri_merge`) : $O(n \log n)$
5. **Tri rapide** (`Quick_Sort` / `tri_quick` - pivot médian) : $O(n \log n)$
6. **Tri par tas** (`Heap_Sort` / `tri_heap`) : $O(n \log n)$
7. **Tri standard C** (`Qsort_std` / `tri_qsort_std`) : référence standard (`qsort`)

---

##  Types de données testés

* `random` : Nombres aléatoires non triés.
* `sorted` : Données déjà triées par ordre croissant.
* `reverse` : Données triées par ordre décroissant (pire cas).
* `nearly` : Données presque triées (avec un faible pourcentage de permutations).
* `duplicates` : Données contenant de nombreux doublons.

---

##  Structure du projet

```
tri_etude/
├── include/
│   ├── benchmark.h   # Déclarations du moteur de mesure et types de données
│   └── tri.h         # Prototypes des 7 algorithmes de tri
├── src/
│   ├── benchmark.c   # Mesures de temps précises et export CSV
│   ├── input.c       # Génération des différents types de tableaux
│   ├── main.c        # Interface en ligne de commande (CLI)
│   └── tri.c         # Implémentation des 7 algorithmes de tri
├── results/          # Fichiers CSV et graphes PNG générés
├── plot.gp           # Script Gnuplot pour tracer les courbes de performance
├── run.sh            # Script de compilation et d'exécution pour Linux / macOS
├── run.bat           # Script de compilation et d'exécution pour Windows
└── README.md         # Documentation du projet
```

---

##  Prérequis

* **GCC** (ou tout compilateur C supportant C99 / POSIX).
* **Gnuplot** *(optionnel)* : Nécessaire uniquement pour générer les images des courbes `.png`.
  * Arch Linux : `sudo pacman -S gnuplot`
  * Ubuntu / Debian : `sudo apt install gnuplot`
