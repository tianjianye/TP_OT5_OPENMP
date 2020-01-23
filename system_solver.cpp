#include <iostream>
#include <random>
#include <string>
#include <cstdint>
#include <fstream>
#include <limits>
#include <vector>
#include <sstream>
#include<chrono>

std::vector<double> getNextLineAndSplitIntoTokens(std::istream& str)
{
	std::vector<double>   result;
	std::string                line;
	std::getline(str, line);

	std::stringstream          lineStream(line);
	std::string                cell;

	while (std::getline(lineStream, cell, ','))
	{
		result.push_back(std::stod(cell));
	}
	// This checks for a trailing comma with no data after it.
	if (!lineStream && cell.empty())
	{
		// If there was a trailing comma then add an empty element.
		//result.push_back("");
	}
	return result;
}

int main(int argc, char** argv) {
	// Step 0 : Check command line and get arguments

	if (argc < 4) {
		printf("The correct command is %s fileName nbStep validationFile\n", argv[0]);
		exit(-1);
	}
	// Number of timestep
	int nb_step = std::atoi(argv[2]);


	// Filename of the file containing the data
	char *fileName = argv[1];

	std::ifstream inFile;
	inFile.open(argv[1]);

	if (!inFile) {
		std::cerr << "Unable to open file " << fileName << std::endl;
		std::cout << "\n";
		exit(-2);   // call system to stop
	}


	// Filename of the file containing the validation data
	std::ifstream validationFile;
	validationFile.open(argv[3]);

	if (!validationFile) {
		std::cerr << "Unable to open file " << argv[3] << std::endl;
		std::cout << "\n";
		exit(-2);   // call system to stop
	}

	// Step 1: Construct the required data structure
	double* variable_value_t;
	double* variable_value_prev_t;
	double** value_matrix;
	double* validation_matrix;

	// Step 1 : Read data from file and construct matrix
	std::string line;
	std::getline(inFile, line);

	int system_size = std::stod(line);

	variable_value_t = new double[system_size];
	variable_value_prev_t = new double[system_size];

	value_matrix = new double*[system_size];
	for (int i = 0; i < system_size; i++)
		value_matrix[i] = new double[system_size];

	std::vector<double> ret = getNextLineAndSplitIntoTokens(inFile);

	int lineCounter = 0;
	while (ret.size() != 0) {

		for (int i = 0; i < system_size; i++) {
			if (lineCounter == system_size) {
				variable_value_prev_t[i] = ret[i];
			}
			else {
				value_matrix[lineCounter][i] = ret[i];
			}
		}
		ret = getNextLineAndSplitIntoTokens(inFile);

		lineCounter++;
	}

	validation_matrix = new double[system_size];
	ret = getNextLineAndSplitIntoTokens(validationFile);
	for (int i = 0; i < system_size; i++) {
		validation_matrix[i] = ret[i];
	}

	auto t1 = std::chrono::high_resolution_clock::now();
	double min, max,sum;
	for (int t = 0; t<nb_step; t++) {
		min = variable_value_prev_t[0];
		max = variable_value_prev_t[0];
		for (int i = 0; i < system_size; i++) {
			variable_value_t[i] = 0;
			
			if (min > variable_value_prev_t[i]) {
				min = variable_value_prev_t[i];
			}
			if (max < variable_value_prev_t[i]) {
				max = variable_value_prev_t[i];
			}
			
		}
		#pragma omp parallel for
		for (int i = 0; i < system_size; i++) {
			for (int j = 0; j < system_size; j++) {
				variable_value_t[i] += variable_value_prev_t[j] * value_matrix[i][j];
			}
			
		}
		for (int i = 0; i < system_size; i++) {
			variable_value_t[i] = (double)(variable_value_t[i] - min) / (max - min);
			variable_value_prev_t[i] = variable_value_t[i];
		}
	}

	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	std::cout << "DURATION," << system_size << "," << nb_step << "," << duration << std::endl;

	// Step 3: Check if the system is correct
	bool system_is_valid = true;
	for (int i = 0; i < system_size; i++)
		if ((round(validation_matrix[i] * 100000.0) / 100000.0) != (round(variable_value_prev_t[i] * 100000.0) / 100000.0)) {
			system_is_valid = false;
			printf("%e != %e (%e)\n", validation_matrix[i], variable_value_prev_t[i], (round(variable_value_prev_t[i] * 100000.0) / 100000.0));

		}

	if (system_is_valid){
		//printf("System is valid !\n");
	}
	else {
		printf("System is NOT valid !\n");
		exit(-3);
	}
}
