#include "CGAIndividual.hpp"

CGAIndividual::CGAIndividual() { }

CGAIndividual::CGAIndividual(int s_size, CMax3SatProblem _problem) 
{
    for (int i = 0; i < s_size; i++)
    {
        values.push_back(false);
    }
    problem = _problem;
}

CGAIndividual::CGAIndividual(bool fill_value, int s_size, CMax3SatProblem _problem) 
{
    for (int i = 0; i < s_size; i++)
    {
        values.push_back(fill_value);
    }
    problem = _problem;
}

CGAIndividual::~CGAIndividual() { }

int CGAIndividual::get_fitness()
{
    return problem.compute(values, problem.get_clauses());
}

void CGAIndividual::perform_mutation(int prop_of_gene_mutation)
{
    srand (time(NULL));
    for (int i = 0; i < values.size(); i++)
    {
        if ((rand() % 100) + 1 <= prop_of_gene_mutation) 
        {
            values[i] = !values[i];
        }
    }
}

std::tuple<CGAIndividual, CGAIndividual> CGAIndividual::perform_crossover(CGAIndividual parent1, CGAIndividual parent2, int bias)
{
    // UNIFORM CROSSOVER
    int childsize = parent1.get_values().size();
    CGAIndividual child_one(childsize, parent1.get_problem());
    CGAIndividual child_two(childsize, parent1.get_problem());
    std::vector<bool> child_one_values;
    std::vector<bool> child_two_values;
    srand (time(NULL));
    for (int i = 0; i < childsize; i++)
    {
        if (rand() % 100 > bias) 
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

void CGAIndividual::initialize_random(int s_size)
{
    
    srand (time(NULL));
    for (int i = 0; i < s_size; i++)
    {
        bool val = (rand() % 100) % 2 == 0 ? true : false;
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

CMax3SatProblem CGAIndividual::get_problem()
{
    return problem;
}
