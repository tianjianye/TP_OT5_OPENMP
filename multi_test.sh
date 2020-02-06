#!/bin/bash
export OMP_NUM_THREADS=$3
./multisys.o "../input_data_exo_1.2/multiple_matrice_file_$1.csv" $2 "../output_data_exo_1.2/validation_multiple_matrice_file_$1_$2.csv"
