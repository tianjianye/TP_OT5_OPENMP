#!/bin/bash
export OMP_NUM_THREADS=$3
./sys.o "../data_openmp/input/matrice_file_$1.csv" $2 "../data_openmp/output/validation_matrice_file_$1_$2.csv"
