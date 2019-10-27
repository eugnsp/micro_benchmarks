#!/bin/sh

set -e

./read_write | tee read_write.txt
cat read_write.txt | ./process.pl
./plot.sh
