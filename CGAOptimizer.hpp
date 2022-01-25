#pragma once
#include "CMax3SatProblem.hpp"
#include "CGAIndividual.hpp"
#include "Helper.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

class CGAOptimizer
{
    public:
        CGAOptimizer();
        CGAOptimizer(int _population_size, int _crossover_prop, int _mutation_prop, int _parental_bias, 
            CMax3SatProblem *_problem);
        ~CGAOptimizer();

        bool initialize(std::string filename);
        void run_iteration();

        void show_best();
    
    private:
        CGAIndividual* run_tournament();
        std::tuple<CGAIndividual, CGAIndividual> run_crossover(CGAIndividual parent1, CGAIndividual parent2);

        // number of CGAIndividuals - solutions exisiting in one generation
        int population_size;
        
        // propobility of parent crossover in % 
        int crossover_prop;

        // propobility of mutation in %
        int mutation_prop;

        // bias towards one parent during corssover:
        // set equal to 0      --> only consider parent 1
        // set equal to 50     --> no bias
        // set equal to >100   --> only consider parent 2
        int parental_bias;

        std::vector<Pack*> clauses;
        std::vector<CGAIndividual*> solutions;

        CMax3SatProblem *problem; 

        int variable_quantity;
};
