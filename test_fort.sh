#!/bin/bash
clear
make clean >/dev/null
make >/dev/null
sh test.sh $1 $2 1
sh test.sh $1 $2 1
sh test.sh $1 $2 1
sh test.sh $1 $2 2
sh test.sh $1 $2 2
sh test.sh $1 $2 2
sh test.sh $1 $2 4
sh test.sh $1 $2 4
sh test.sh $1 $2 4
sh test.sh $1 $2 6
sh test.sh $1 $2 6
sh test.sh $1 $2 6
sh test.sh $1 $2 8
sh test.sh $1 $2 8
sh test.sh $1 $2 8
make clean >/dev/null
