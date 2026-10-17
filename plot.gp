if (!exists("type")) type = "random"

csv = "results/".type.".csv"

if (!exists("algo") || strlen(algo) == 0) {
    algos = "Bubble_Sort Selection_Sort Insertion_Sort Merge_Sort Quick_Sort Heap_Sort Qsort_std"
    out = "results/plot_".type.".png"
    plot_title = "Sorting Algorithms Benchmark - ".type." input"
} else {
    algos = algo
    out = "results/plot_".type."_".algo.".png"
    plot_title = "Sorting Benchmark - ".algo." (".type." input)"
}

set datafile separator ","
set terminal pngcairo size 1400,850 enhanced font "Arial,12"
set output out

set title plot_title font ",16"
set xlabel "Input size (n)"
set ylabel "Time (ms)"
set logscale x
set logscale y
set grid
set key outside right center
set border 3

set samples 500

plot for [a in algos] csv using (strcol(1) eq a ? column(3) : NaN):(strcol(1) eq a ? (column(5) > 0 ? column(5) : 1e-3) : NaN) \
     title a smooth csplines with lines lw 2
