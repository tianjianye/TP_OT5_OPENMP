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
    std::getline(str,line);

    std::stringstream          lineStream(line);
    std::string                cell;

    while(std::getline(lineStream,cell, ','))
    {
        result.push_back( std::stod(cell) );
    }
    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty())
    {
        // If there was a trailing comma then add an empty element.
        //result.push_back("");
    }
    return result;
}

class System {
public:
    System() { };
    
    double* variable_value_t;
    double* variable_value_prev_t;
    double** value_matrix;
    double* validation_matrix;
    int system_size;
};


int main(int argc, char** argv) {
    // Step 0 : Check command line and get arguments
    
    if (argc < 4) {
        printf("The correct command is %s fileName nbStep validationFile\n",argv[0]);
        exit(-1);
    }
    // Number of timestep
    int nb_step = std::atoi(argv[2]);
    
    
    // Filename of the file containing the data
    char *fileName = argv[1];
    
    std::ifstream inFile;
    inFile.open(argv[1]);
    
    if (!inFile) {
        std::cerr << "Unable to open file "<<fileName<< std::endl;
        std::cout<<"\n";
        exit(-2);   // call system to stop
    }
    
    
    // Filename of the file containing the validation data
    std::ifstream validationFile;
    validationFile.open(argv[3]);
    
    if (!validationFile) {
        std::cerr << "Unable to open file "<<argv[3]<< std::endl;
        std::cout<<"\n";
        exit(-2);   // call system to stop
    }
    
    // Step 1: Construct the required data structure
    System* systems;
    
    // Step 1 : Read data from file and construct matrix
    std::string                line;
    std::getline(inFile,line);

    int nb_system = std::stod(line); 
    systems = new System[nb_system];
    
    for (int s = 0; s < nb_system; s++) {
        std::getline(inFile,line);

        int ssystem_size = std::stod(line);
        systems[s].system_size = ssystem_size;
                
        systems[s].variable_value_t = new double[systems[s].system_size];
        systems[s].variable_value_prev_t = new double[systems[s].system_size];
        
        systems[s].value_matrix = new double*[systems[s].system_size];
        for (int i = 0; i < systems[s].system_size; i++)
            systems[s].value_matrix[i] = new double[systems[s].system_size];
        
        std::vector<double> ret;
        for (int lineCounter = 0; lineCounter <= systems[s].system_size; lineCounter++) {
            ret = getNextLineAndSplitIntoTokens(inFile);
            
            for (int i = 0; i < systems[s].system_size; i++) {
                if (lineCounter == systems[s].system_size) {
                    systems[s].variable_value_prev_t[i] = ret[i];
                } else {
                    systems[s].value_matrix[lineCounter][i] = ret[i];
                }
            }
        }
        
        systems[s].validation_matrix = new double[systems[s].system_size];
        ret = getNextLineAndSplitIntoTokens(validationFile);
        for (int i = 0; i < systems[s].system_size; i++) {
            systems[s].validation_matrix[i] = ret[i];
        }
    }
    
    auto t1 = std::chrono::high_resolution_clock::now();
    //TODO: Implemnt solver
	
	double min, max,sum;
	double* variable_value_t;
    double* variable_value_prev_t;
	double** value_matrix;
	double* validation_matrix;
	int system_size;

	//#pragma omp parallel for
	for(int s =0;s<nb_system;s++){
		variable_value_t=systems[s].variable_value_t;
		variable_value_prev_t=systems[s].variable_value_prev_t;
		value_matrix=systems[s].value_matrix;
		validation_matrix=systems[s].validation_matrix;
		system_size=systems[s].system_size;
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
			//#pragma omp parallel for schedule(dynamic,4)
			//#pragma omp parallel for collapse(2)		
			for (int i = 0; i < system_size; i++) {

				for (int j = 0; j < system_size; j++) {
					variable_value_t[i] += variable_value_prev_t[j] * value_matrix[i][j];
				}
				
			}
			for (int i = 0; i < systems[s].system_size; i++) {
				variable_value_t[i] = (double)(variable_value_t[i] - min) / (max - min);
				variable_value_prev_t[i] = variable_value_t[i];
			}
		}
	}
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout<<"DURATION,"<<nb_system<<","<<nb_step<<","<<duration<<std::endl;    
    
    
    // Step 3: Check if the system is correct
    bool system_is_valid = true;
    for (int s = 0; s < nb_system; s++) {
        for (int i = 0; i < systems[s].system_size; i++)
            if (systems[s].validation_matrix[i] != (round(systems[s].variable_value_prev_t[i]*10000000000.0)/10000000000.0) && !std::isnan(systems[s].variable_value_prev_t[i])) {
                system_is_valid = false;
                printf("%d/%d -- %10.10e != %10.10e (%10.10e)\n",i,s,systems[s].validation_matrix[i],systems[s].variable_value_prev_t[i],
                       (round(systems[s].variable_value_prev_t[i]*10000000000.0)/10000000000.0));
                
            }
    }
    
    if (!system_is_valid)
        exit(-3);
    
}
