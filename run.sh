#!/bin/bash

if [ "$1" = "clean" ]; then
    rm -f benchmark results/plot_*.png
    echo "Projet nettoyé."
    exit 0
fi

mkdir -p results

gcc -Wall -Wextra -O2 -Iinclude -o benchmark src/*.c
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
    if [ "$CMD" = "full" ]; then
        TYPE="$1"
    elif [ "$CMD" = "random" ] || [ "$CMD" = "sorted" ] || [ "$CMD" = "reverse" ] || [ "$CMD" = "nearly" ] || [ "$CMD" = "duplicates" ]; then
        TYPE="$CMD"
    fi

    [ "$TYPE" = "reverse" ] && TYPE="reverse_sorted"
    [ "$TYPE" = "nearly" ] && TYPE="nearly_sorted"
    [ "$TYPE" = "duplicates" ] && TYPE="many_duplicates"

    if [ "$CMD" = "full" ] || [ -n "$TYPE" ]; then
        if [ -n "$TYPE" ] && [ "$TYPE" != "all" ]; then
            echo "Génération du graphe pour $TYPE..."
            gnuplot -e "type='$TYPE'" plot.gp
        else
            echo "Génération de tous les graphes..."
            for t in random sorted reverse_sorted nearly_sorted many_duplicates; do
                gnuplot -e "type='$t'" plot.gp
            done
        fi
        echo "Graphes enregistrés dans results/"
    fi
fi
