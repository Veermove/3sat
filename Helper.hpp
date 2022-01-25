#pragma once
#include "CGAIndividual.hpp"
#include <vector>
#include <random>
#include <ctime>

// container class for helper functions
class Helper
{
    public:
        static CGAIndividual* run_tournament(int _tournament_size, 
            std::vector<CGAIndividual*> population, CMax3SatProblem *problem);

        static bool random_true_false(int _chance_of_truth);
};
