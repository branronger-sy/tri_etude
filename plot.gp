if (!exists("type")) type = "random"

csv = "results/".type.".csv"
out = "results/plot_".type.".png"

system("mkdir -p results")

tmpdir = "/tmp/gnuplot_plots"
system("rm -rf ".tmpdir)
system("mkdir -p ".tmpdir)

algos = "Bubble_Sort Selection_Sort Insertion_Sort Merge_Sort Quick_Sort Heap_Sort Qsort_std"

do for [a in algos] {
    tmp = tmpdir."/".type."_".a.".dat"
    system(sprintf("awk -F, -v alg=%s 'NR>1 && $1==alg {print $3, $5}' %s > %s", a, csv, tmp))
}

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

plot for [a in algos] tmpdir."/".type."_".a.".dat" using 1:($2 > 0 ? $2 : 1e-3) \
     title a smooth csplines with lines lw 2

system("rm -rf ".tmpdir)
