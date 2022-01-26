#pragma once

#include "CGAIndividual.hpp"

#include <random>
#include <vector>

// container class for helper functions
class Helper
{
    public:
        static CGAIndividual* run_tournament(int _tournament_size, std::vector<CGAIndividual*> population);

        static bool random_true_false(int _chance_of_truth);
};
