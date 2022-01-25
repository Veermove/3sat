#pragma once
#include "CMax3SatProblem.hpp"  
#include <vector>
#include <tuple>
#include <random>

class CGAIndividual
{

    public:
        CGAIndividual();
        CGAIndividual(const CGAIndividual &other);
        CGAIndividual(int s_size, CMax3SatProblem *_problem);
        CGAIndividual(bool fill_value, int s_size, CMax3SatProblem *_problem);
        ~CGAIndividual();

        // FITNESS
        int get_fitness();

        // MUTATION
        void perform_mutation(int prop_of_gene_mutation);
        
        // CROSSOVER
        static std::tuple<CGAIndividual, CGAIndividual> perform_crossover(CGAIndividual parent1, CGAIndividual parent2, int bias);

        void initialize_random(int s_size);
        void set_values(std::vector<bool> _values);
        std::vector<bool> get_values(); 
        CMax3SatProblem* get_problem();
    private:
        std::vector<bool> values;
        CMax3SatProblem *problem;

};
