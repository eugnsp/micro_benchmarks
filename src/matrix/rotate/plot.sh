#!/usr/bin/gnuplot

set terminal pngcairo size 1000,700 
set output 'rotate.png'
set title "Matrix 90 deg rotation speed - Intel(R) Core(TM) i7-4770"

set grid
set xlabel "Matrix size (Bytes)"
set ylabel "Speed [10^9 Matrix element/second]"

set logscale x 2
set logscale y 2

set xtics ("4K" 4*1024, "32K (L1)" 32*1024, "265K (L2)" 256*1024, "8M (L3)" 8*1024*1024, "1G" 1024*1024*1024, "4G" 4*1024*1024*1024)
 
plot 'transpose.dat' 			 with lines linewidth 2 title 'transpose', \
	 'flip_ud.dat'   			 with lines linewidth 2 title 'flip\_ud', \
	 'flip_transpose_rotate.dat' with lines linewidth 2 title 'flip\_transpose\_rotate', \
	 'cycle_rotate.dat' 		 with lines linewidth 2 title 'cycle\_rotate', \
	 'buffer_rotate.dat' 		 with lines linewidth 2 title 'buffer\_rotate'
