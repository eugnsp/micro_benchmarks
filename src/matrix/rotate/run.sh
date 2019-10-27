#!/bin/sh

set -e

./rotate | tee rotate.txt
cat rotate.txt | ./process.pl
./plot.sh
