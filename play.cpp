#include "CMax3SatProblem.hpp"
#include "CGAOptimizer.hpp"
#include <iostream>
#include <vector>
#include <string>

int main () 
{
    const int population_size = 50;
    const int crossover_prop = 50;
    const int mutation_prop = 70;
    CMax3SatProblem problem;
    CGAOptimizer optimizer(population_size, crossover_prop, mutation_prop, problem);
    if (optimizer.initialize("testCases/m3s_50_0.txt"))
    {
        // optimizer.show_best();
        optimizer.run_iteration();
        // optimizer.show_best();
    } else 
    {
        std::cout << "Failed to open file" << std::endl;
    }

    
};
