#!/bin/bash
clear
make clean >/dev/null
make >/dev/null
export OMP_NUM_THREADS=1
sh test.sh $1 $2 >./result/result_$1_$2_1.txt
sh test.sh $1 $2 >>./result/result_$1_$2_1.txt
sh test.sh $1 $2 >>./result/result_$1_$2_1.txt
sh test.sh $1 $2 >>./result/result_$1_$2_1.txt
sh test.sh $1 $2 >>./result/result_$1_$2_1.txt
export OMP_NUM_THREADS=2
sh test.sh $1 $2 >./result/result_$1_$2_2.txt
sh test.sh $1 $2 >>./result/result_$1_$2_2.txt
sh test.sh $1 $2 >>./result/result_$1_$2_2.txt
sh test.sh $1 $2 >>./result/result_$1_$2_2.txt
sh test.sh $1 $2 >>./result/result_$1_$2_2.txt
export OMP_NUM_THREADS=4
sh test.sh $1 $2 >./result/result_$1_$2_4.txt
sh test.sh $1 $2 >>./result/result_$1_$2_4.txt
sh test.sh $1 $2 >>./result/result_$1_$2_4.txt
sh test.sh $1 $2 >>./result/result_$1_$2_4.txt
sh test.sh $1 $2 >>./result/result_$1_$2_4.txt
export OMP_NUM_THREADS=6
sh test.sh $1 $2 >./result/result_$1_$2_6.txt
sh test.sh $1 $2 >>./result/result_$1_$2_6.txt
sh test.sh $1 $2 >>./result/result_$1_$2_6.txt
sh test.sh $1 $2 >>./result/result_$1_$2_6.txt
sh test.sh $1 $2 >>./result/result_$1_$2_6.txt
export OMP_NUM_THREADS=7
sh test.sh $1 $2 >./result/result_$1_$2_7.txt
sh test.sh $1 $2 >>./result/result_$1_$2_7.txt
sh test.sh $1 $2 >>./result/result_$1_$2_7.txt
sh test.sh $1 $2 >>./result/result_$1_$2_7.txt
sh test.sh $1 $2 >>./result/result_$1_$2_7.txt
export OMP_NUM_THREADS=8
sh test.sh $1 $2 >./result/result_$1_$2_8.txt
sh test.sh $1 $2 >>./result/result_$1_$2_8.txt
sh test.sh $1 $2 >>./result/result_$1_$2_8.txt
sh test.sh $1 $2 >>./result/result_$1_$2_8.txt
sh test.sh $1 $2 >>./result/result_$1_$2_8.txt

