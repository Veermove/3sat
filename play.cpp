#include "CMax3SatProblem.hpp"
#include "CGAOptimizer.hpp"
#include <iostream>
#include <vector>
#include <string>

int main () 
{

    // 1643118223 -- 
    // 1643118284 -- corrupted size vs. prev_size
    //               Aborted (core dumped)
    // 1643118323 -- 
    auto time_seed = time(NULL);
    srand (time_seed);
    std::cout << "TIME " << time_seed << std::endl; 
    const int population_size = 50;
    const int crossover_prop = 50;
    const int mutation_prop = 70;
    
    CMax3SatProblem* problem = new CMax3SatProblem();
    CGAOptimizer optimizer(population_size, crossover_prop, mutation_prop, problem);
    
    if (optimizer.initialize("testCases/m3s_50_0.txt"))
    {
        int iterations = 10;
        optimizer.show_best();
        while (iterations > 0)
        {
           
            optimizer.run_iteration();
            optimizer.show_best();
            iterations--;
        }
    } else 
    {
        std::cout << "Failed to open file" << std::endl;
    }

};
