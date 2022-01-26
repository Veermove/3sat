#include "CGAIndividual.hpp"

#include "Helper.hpp"

#include <iostream>

CGAIndividual::CGAIndividual() { }

CGAIndividual::CGAIndividual(const CGAIndividual &other)
{
    problem = other.problem;
    values = other.values;
    for (int i = 0; i < other.values.size(); i++) 
    {
        values[i] = other.values[i];
    }
}

CGAIndividual::CGAIndividual(int s_size, CMax3SatProblem *_problem) 
{
    for (int i = 0; i < s_size; i++)
    {
        values.push_back(false);
    }
    problem = _problem;
}

CGAIndividual::CGAIndividual(bool fill_value, int s_size, CMax3SatProblem *_problem) 
{
    for (int i = 0; i < s_size; i++)
    {
        values.push_back(fill_value);
    }
    problem = _problem;
}

CGAIndividual::~CGAIndividual() 
{
    values.clear();
}

int CGAIndividual::get_fitness()
{   
    auto problem_clauses = *(problem->get_clauses_pointer()); 
    return problem->compute(values, problem_clauses);
}

void CGAIndividual::perform_mutation(int prop_of_gene_mutation)
{
    for (int i = 0; i < values.size(); i++)
    {
        if (Helper::random_true_false(prop_of_gene_mutation)) 
        {
            values[i] = !values[i];
        }
    }
}

std::tuple<CGAIndividual, CGAIndividual> CGAIndividual::perform_crossover(
    CGAIndividual parent1, CGAIndividual parent2, int bias)
{
    // std::cout << "CGAIndividual::perform_crossover" << std::endl;
    // UNIFORM CROSSOVER
    int childsize = parent1.get_values().size();
    CGAIndividual child_one(childsize, parent1.get_problem());
    CGAIndividual child_two(childsize, parent1.get_problem());

    std::vector<bool> child_one_values = parent1.get_values();
    std::vector<bool> child_two_values = parent2.get_values();

    for (int i = 0; i < childsize; i++)
    {
        if (rand() % 100 >= bias) 
        {
            child_one_values[i] = parent1.get_values()[i];
            child_two_values[i] = !parent1.get_values()[i];
        } else 
        {
            child_one_values[i] = parent2.get_values()[i];
            child_two_values[i] = !parent2.get_values()[i];
        }
    }
    child_one.set_values(child_one_values);
    child_two.set_values(child_two_values);

    return std::make_pair(child_one, child_two);
}

void CGAIndividual::randomize(int s_size)
{
    values.clear();
    for (int i = 0; i < s_size; i++)
    {
        int ra = (rand() % 100);  
        bool val = ra % 2 == 0 ? true : false;
        values.push_back(val);
    }
}

void CGAIndividual::set_values(std::vector<bool> _values)
{
    values = _values;
}

std::vector<bool> CGAIndividual::get_values()
{
    return values;
}

CMax3SatProblem* CGAIndividual::get_problem()
{
    return problem;
}
