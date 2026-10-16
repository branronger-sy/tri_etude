if (!exists("type")) type = "random"

csv = "results/".type.".csv"
out = "results/plot_".type.".png"

algos = "Bubble_Sort Selection_Sort Insertion_Sort Merge_Sort Quick_Sort Heap_Sort Qsort_std"

set datafile separator ","
set terminal pngcairo size 1400,850 enhanced font "Arial,12"
set output out

set title "Sorting Algorithms Benchmark - ".type." input" font ",16"
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
