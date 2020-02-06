#!/bin/bash
clear
make clean >/dev/null
make >/dev/null
sh multi_test.sh 64 100 $1
sh multi_test.sh 64 100 $1
sh multi_test.sh 64 100 $1
sh multi_test.sh 64 500 $1
sh multi_test.sh 64 500 $1
sh multi_test.sh 64 500 $1
sh multi_test.sh 64 1000 $1
sh multi_test.sh 64 1000 $1
sh multi_test.sh 64 1000 $1
make clean >/dev/null
