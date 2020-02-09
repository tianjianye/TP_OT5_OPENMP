#!/bin/bash
clear
make clean >/dev/null
make >/dev/null
sh test.sh 128 1000 1
sh test.sh 128 1000 1
sh test.sh 128 1000 1
sh test.sh 256 1000 2
sh test.sh 256 1000 2
sh test.sh 256 1000 2
sh test.sh 512 1000 4
sh test.sh 512 1000 4
sh test.sh 512 1000 4
make clean >/dev/null
