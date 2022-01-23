#pragma once
#include "CGAIndividual.hpp"
#include <vector>
#include <random>
#include <ctime>

// container class for helper functions
class Helper
{
    public:
        CGAIndividual* run_tournament(int _tournament_size, 
            std::vector<CGAIndividual*> population, CMax3SatProblem problem);
};
