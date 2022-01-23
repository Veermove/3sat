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
        CGAOptimizer(int _population_size, int _crossover_prop, int _mutation_prop, CMax3SatProblem _problem);

        bool initialize(std::string filename);
        void run_iteration();

        void show_best();
    
    private:
        CGAIndividual* run_tournament();
        std::tuple<CGAIndividual, CGAIndividual> run_crossover(CGAIndividual parent1, CGAIndividual parent2);

        int population_size;
        int crossover_prop;
        int mutation_prop;

        std::vector<Pack*> clauses;
        std::vector<CGAIndividual*> solutions;

        CMax3SatProblem problem; 
        Helper helper;

        int variable_quantity;
};
