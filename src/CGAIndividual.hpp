#pragma once

#include "CMax3SatProblem.hpp"  

#include <random>
#include <tuple>
#include <vector>

class CGAIndividual
{

    public:
        CGAIndividual();
        CGAIndividual(const CGAIndividual &other);
        CGAIndividual(int s_size, CMax3SatProblem *_problem);
        CGAIndividual(bool fill_value, int s_size, CMax3SatProblem *_problem);
        ~CGAIndividual();

        // fitness
        int get_fitness();

        // mutation
        void perform_mutation(const int prop_of_gene_mutation);
        
        // crossover
        static std::tuple<CGAIndividual, CGAIndividual> perform_crossover(CGAIndividual parent1, 
            CGAIndividual parent2, const int bias);

        void randomize(const int s_size);
        void set_values(const std::vector<bool> _values);
        
        std::vector<bool> get_values(); 
        CMax3SatProblem* get_problem();

    private:
        std::vector<bool> values;
        CMax3SatProblem *problem;

};
