#!/usr/bin/gnuplot

set terminal pngcairo size 1000,700 
set output 'copy.png'
set title "Matrix copy with transposition - Intel(R) Core(TM) i7-4770"

set grid
set xlabel "Matrix size (Bytes)"
set ylabel "Speed [10^9 Matrix element/second]"

set logscale x 2
set logscale y 2

set xtics ("4K" 4*1024, "32K (L1)" 32*1024, "265K (L2)" 256*1024, "8M (L3)" 8*1024*1024, "1G" 1024*1024*1024)
 
plot 'copy.dat' 			        with lines linewidth 2 title 'copy', \
	 'copy_transp_contig_write.dat' with lines linewidth 2 title 'copy\_transp\_contig\_write', \
	 'copy_transp_contig_read.dat'  with lines linewidth 2 title 'copy\_transp\_contig\_read', \
	 'copy_transp_mkl.dat' 		    with lines linewidth 2 title 'copy\_transp\_mkl'
