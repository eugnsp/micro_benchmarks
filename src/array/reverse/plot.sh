#!/usr/bin/gnuplot

set terminal pngcairo size 1000,700 
set output 'reverse.png'
set title "Array reverse - Intel(R) Core(TM) i7-4770"

set grid
set xlabel "Size [Bytes]"
set ylabel "Speed [GBytes/second]"

set logscale x 2
set logscale y 2

set xtics ("4K" 4*1024, "32K (L1)" 32*1024, "265K (L2)" 256*1024, "8M (L3)" 8*1024*1024, "1G" 1024*1024*1024)
 
plot 'reverse<float>.dat'   with lines linewidth 2 title 'reverse<float>',   \
	 'reverse<double>.dat'  with lines linewidth 2 title 'reverse<double>',  \
	 'block_reverse<float>.dat'   with lines linewidth 2 title 'block\_reverse<float>',   \
	 'block_reverse<double>.dat'  with lines linewidth 2 title 'block\_reverse<double>',  \
	 'sse_reverse<float>.dat'   with lines linewidth 2 title 'sse\_reverse<float>',   \
	 'sse_reverse<double>.dat'  with lines linewidth 2 title 'sse\_reverse<double>',  \
