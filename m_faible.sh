#!/bin/bash
clear
make clean >/dev/null
make >/dev/null
filepath="../"
sh multi_test.sh 128 1000 2 $filepath
sh multi_test.sh 128 1000 2 $filepath
sh multi_test.sh 128 1000 2 $filepath
sh multi_test.sh 128 1000 2 $filepath
sh multi_test.sh 128 1000 2 $filepath
sh multi_test.sh 128 1000 2 $filepath
sh multi_test.sh 256 1000 4 $filepath
sh multi_test.sh 256 1000 4 $filepath
sh multi_test.sh 256 1000 4 $filepath
sh multi_test.sh 256 1000 4 $filepath
sh multi_test.sh 256 1000 4 $filepath
sh multi_test.sh 256 1000 4 $filepath
make clean >/dev/null
