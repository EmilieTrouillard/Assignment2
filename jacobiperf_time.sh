TIMEFORMAT='%3R'
#for((N=10; N<570; N += 50)); do (time jacobi 0 $N 2 $1); done >no_kmax_jac_tmp.dat 2>&1
#for((N=10; N<570; N += 50)); do (time jacobi 1 $N 2 $1); done >no_kmax_gau_tmp.dat 2>&1
awk ' NR % 2 == 1 ' no_kmax_jac_tmp.dat > iter_no_kmax_jac.dat
awk ' NR % 2 == 1 ' no_kmax_gau_tmp.dat > iter_no_kmax_gau.dat

awk ' NR % 2 == 1 { n = $1 ; k = $2 } NR % 2 == 0 {t = $1}; {print n , k, t}' no_kmax_jac_tmp.dat > data_no_kmax_jac.dat
awk ' NR % 2 == 1 { n = $1 ; k = $2 } NR % 2 == 0 {t = $1}; {print n , k, t}' no_kmax_gau_tmp.dat > data_no_kmax_gau.dat

awk ' NR % 2 == 0 ' data_no_kmax_jac.dat > no_kmax_jac_tmp.dat
awk ' NR % 2 == 0 ' data_no_kmax_gau.dat > no_kmax_gau_tmp.dat

awk ' {print $1, $2 / $3 }' no_kmax_jac_tmp.dat > perf_no_kmax_jac.dat
awk ' {print $1, $2 / $3 }' no_kmax_gau_tmp.dat > perf_no_kmax_gau.dat

awk ' {print $1, $3 }' no_kmax_jac_tmp.dat > times_no_kmax_jac.dat
awk ' {print $1, $3 }' no_kmax_gau_tmp.dat > times_no_kmax_gau.dat

gnuplot -persist <<-EOFMarker
	set terminal postscript eps enhanced color font 'Helvetica,10'
	set xlabel "Matrix size"
	set ylabel "Total time (s)"
	set output "perf_seq10-4thr.eps"
	plot "times_no_kmax_gau.dat" w lp title 'gauss_seidel', "times_no_kmax_jac.dat" w lp title 'jacobi'
EOFMarker
