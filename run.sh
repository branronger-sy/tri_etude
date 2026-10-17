#!/bin/bash

if [ "$1" = "clean" ]; then
    rm -f benchmark benchmark.exe results/plot_*.png
    echo "Projet nettoyé."
    exit 0
fi

if [ "$1" = "check" ] || [ "$1" = "check-all" ]; then
    echo "=== 1. Vérification Linux ==="
    gcc -Wall -Wextra -O2 -Iinclude -o benchmark src/benchmark.c src/input.c src/main.c src/tri.c && ./benchmark --test
    echo ""
    echo "=== 2. Vérification Windows (Cross-compilation) ==="
    if command -v x86_64-w64-mingw32-gcc >/dev/null 2>&1; then
        x86_64-w64-mingw32-gcc -Wall -Wextra -O2 -Iinclude -o benchmark.exe src/benchmark.c src/input.c src/main.c src/tri.c
        echo "Compilation Windows réussie : benchmark.exe créé avec succès."
    else
        echo "mingw-w64-gcc n'est pas installé sur ce système."
    fi
    echo ""
    echo "Validation complete pour Linux et Windows terminee avec succes !"
    exit 0
fi

mkdir -p results

gcc -Wall -Wextra -O2 -Iinclude -o benchmark src/benchmark.c src/input.c src/main.c src/tri.c
if [ $? -ne 0 ]; then
    echo "Erreur lors de la compilation !"
    exit 1
fi
echo "Compilation réussie."

CMD=${1:-demo}
shift 2>/dev/null || true

if [ "$CMD" = "demo" ] || [ "$CMD" = "full" ] || [ "$CMD" = "test" ]; then
    ./benchmark --$CMD "$@"
else
    ./benchmark "$CMD" "$@"
fi

if command -v gnuplot >/dev/null 2>&1 && [ -f plot.gp ]; then
    TYPE=""
    ALGO=""
    if [ "$CMD" = "full" ]; then
        TYPE="${1:-all}"
        ALGO="$2"
    elif [ "$CMD" = "random" ] || [ "$CMD" = "sorted" ] || [ "$CMD" = "reverse" ] || [ "$CMD" = "nearly" ] || [ "$CMD" = "duplicates" ]; then
        TYPE="$CMD"
        ALGO="$1"
    elif [ "$CMD" = "all" ]; then
        TYPE="all"
        ALGO="$1"
    fi

    [ "$TYPE" = "reverse" ] && TYPE="reverse_sorted"
    [ "$TYPE" = "nearly" ] && TYPE="nearly_sorted"
    [ "$TYPE" = "duplicates" ] && TYPE="many_duplicates"

    if [ -n "$TYPE" ]; then
        GNUPLOT_EXTRA=""
        if [ -n "$ALGO" ]; then
            GNUPLOT_EXTRA="; algo='$ALGO'"
        fi

        if [ "$TYPE" != "all" ]; then
            echo "Génération du graphe pour $TYPE..."
            gnuplot -e "type='$TYPE'$GNUPLOT_EXTRA" plot.gp
        else
            echo "Génération de tous les graphes..."
            for t in random sorted reverse_sorted nearly_sorted many_duplicates; do
                gnuplot -e "type='$t'$GNUPLOT_EXTRA" plot.gp
            done
        fi
        echo "Graphes enregistrés dans results/"
    fi
fi
