TIMEFORMAT='%3R'

#for((n=1; n<= 30; n+= 1)); do echo "$n"; time OMP_NUM_THREADS=$n proj2 2 $1 $2 0; done > N$1k$2.dat 2>&1

awk ' NR == 3 { t1 = $1}; NR % 3 == 1 { t = $1 }; NR % 3 == 0 {s = $1}; {print t, s, t1}' N$1k$2.dat > N$1k$2_tmp.dat

awk ' NR % 3 == 0 {print $1, $3 / $2}' N$1k$2_tmp.dat > N$1k$2_clean.dat

gnuplot -persist <<-EOFMarker
	set terminal postscript eps enhanced color font 'Helvetica,10'
	set xlabel "Number of threads"
	set ylabel "Speedup"
	set output "Speedup_N$1_k$2.eps"
	plot "N$1k$2_clean.dat" w lp title 'N=$1 k=$2', "identity.dat" w l title 'limit'
EOFMarker
