#!/bin/sh

set -e

./read_write | tee read_write.dat
cat read_write.dat | ./process.pl
./plot.sh
