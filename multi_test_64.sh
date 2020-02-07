#!/bin/bash
clear
make clean >/dev/null
make >/dev/null
filepath=$(<config.txt)
sh multi_test.sh 64 100 $1 $filepath
sh multi_test.sh 64 100 $1 $filepath
sh multi_test.sh 64 100 $1 $filepath
sh multi_test.sh 64 500 $1 $filepath
sh multi_test.sh 64 500 $1 $filepath
sh multi_test.sh 64 500 $1 $filepath
sh multi_test.sh 64 1000 $1 $filepath
sh multi_test.sh 64 1000 $1 $filepath
sh multi_test.sh 64 1000 $1 $filepath
make clean >/dev/null
