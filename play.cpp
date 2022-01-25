#include "CMax3SatProblem.hpp"
#include "CGAOptimizer.hpp"
#include <iostream>
#include <vector>
#include <string>

int main () 
{
    auto time_seed = time(NULL);
    srand (time_seed);
    std::cout << "TIME " << time_seed << std::endl; 
    const int population_size = 100;
    const int crossover_prop = 10;
    const int mutation_prop = 10;
    const int parental_bias = 50;
    
    CMax3SatProblem* problem = new CMax3SatProblem();
    CGAOptimizer optimizer(population_size, crossover_prop, mutation_prop, parental_bias, problem);
    
    if (optimizer.initialize("testCases/m3s_350_50.txt"))
    {
        int iterations = 100;
        optimizer.show_best();
        while (iterations > 0)
        {
            optimizer.run_iteration();
            optimizer.show_best();
            iterations--;
        }
        // optimizer.show_best();
    } else 
    {
        std::cout << "Failed to open file" << std::endl;
    }

};
