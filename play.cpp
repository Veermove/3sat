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
    auto ti = time(NULL);
    srand (1643118323);
    std::cout << "TIME " << ti << std::endl; 
    const int population_size = 50;
    const int crossover_prop = 50;
    const int mutation_prop = 70;
    
    CMax3SatProblem* problem = new CMax3SatProblem();
    CGAOptimizer optimizer(population_size, crossover_prop, mutation_prop, problem);
    
    if (optimizer.initialize("testCases/m3s_50_0.txt"))
    {
        int iterations = 2;
        while (iterations > 0)
        {
            optimizer.show_best();
            optimizer.run_iteration();
            optimizer.show_best();
            iterations--;
        }
    } else 
    {
        std::cout << "Failed to open file" << std::endl;
    }

};
