#!/usr/bin/gnuplot

set terminal pngcairo size 1000,700 
set output 'read_write.png'
set title "Array read/write - Intel(R) Core(TM) i7-4770"

set grid
set xlabel "Size [Bytes]"
set ylabel "Speed [GBytes/second]"

set logscale x 2
set logscale y 2

set xtics ("4K" 4*1024, "32K (L1)" 32*1024, "265K (L2)" 256*1024, "8M (L3)" 8*1024*1024, "1G" 1024*1024*1024)
 
plot 'read<std::uint8_t>.dat'   with lines linewidth 2 title 'read<std::uint8\_t>',   \
	 'read<std::uint32_t>.dat'  with lines linewidth 2 title 'read<std::uint32\_t>',  \
	 'read<std::uint64_t>.dat'  with lines linewidth 2 title 'read<std::uint64\_t>',  \
	 'read<__v32qu>.dat'        with lines linewidth 2 title 'read<\_\_v32qu\_t>',    \
     'write<std::uint8_t>.dat'  with lines linewidth 2 title 'write<std::uint8\_t>',  \
     'write<std::uint32_t>.dat' with lines linewidth 2 title 'write<std::uint32\_t>', \
	 'write<std::uint64_t>.dat' with lines linewidth 2 title 'write<std::uint64\_t>', \
	 'write<__v32qu>.dat'       with lines linewidth 2 title 'write<\_\_v32qu\_t>'
