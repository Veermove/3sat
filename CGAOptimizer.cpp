#include "CGAOptimizer.hpp"

CGAOptimizer::CGAOptimizer() { }

CGAOptimizer::CGAOptimizer(int _population_size, int _crossover_prop, int _mutation_prop, CMax3SatProblem _problem)
{
    population_size = _population_size;
    crossover_prop = _crossover_prop; 
    mutation_prop = _mutation_prop; 
    problem = _problem;
}

bool CGAOptimizer::initialize(std::string filename)
{
    try 
    {
        clauses = problem.load(filename);
        // Not implemented "find max"
        // variable_quantity = problem.get_variable_number();
        variable_quantity = 50;
    } catch (...)
    {
        return false;
    }

    for (int i = 0; i < population_size; i++)
    {
        std::cout << i << "a" << std::endl;
        CGAIndividual *randomized;
        std::cout << i << "b" << std::endl;
        randomized->initialize_random(variable_quantity);
        std::cout << i << "c" << std::endl;
        solutions.push_back(randomized);
    }

    return true;
}

void CGAOptimizer::run_iteration()
{
    std::vector<CGAIndividual*> next_generation;
    std::cout << next_generation.size() << " < " << solutions.size() << std::endl;
    while (next_generation.size() < solutions.size())
    {
        CGAIndividual* parent_one = run_tournament();
        CGAIndividual* parent_two = run_tournament();

        CGAIndividual* child_one;
        CGAIndividual* child_two;
        std::tie(*child_one, *child_two) = run_crossover(*parent_one, *parent_two);
        
        (*child_one).perform_mutation(mutation_prop);
        (*child_two).perform_mutation(mutation_prop);
        
        next_generation.push_back(child_one);
        next_generation.push_back(child_two);
    }
    solutions = next_generation;
}

std::tuple<CGAIndividual, CGAIndividual> CGAOptimizer::run_crossover(CGAIndividual parent1, CGAIndividual parent2)
{
    const int bias = 50;
    srand (time(NULL));
    if (rand() % 100 < mutation_prop) 
    {
        return CGAIndividual::perform_crossover(parent1, parent2, bias);
    } else 
    {
        return std::make_pair(parent1, parent2);
    }
}

CGAIndividual* CGAOptimizer::run_tournament()
{
    const int tournament_size = 2;
    return helper.run_tournament(tournament_size, solutions, problem);
}

void CGAOptimizer::show_best()
{
    std::cout << "CGAOptimizer::show_best" << std::endl;
    CGAIndividual *winner = solutions[0];
    std::cout << "checkpoint 0" << std::endl;
    int winners_result = problem.compute(winner->get_values(), problem.get_clauses());

    std::cout << "checkpoint 1" << std::endl;


    for (int i = 1; i < solutions.size(); i++)
    {
        int cur_res = problem.compute(solutions[i]->get_values(), problem.get_clauses());
        if (cur_res > winners_result)
        {
            winners_result = cur_res;
            winner = solutions[i];
        }
    }
    std::cout << "checkpoint 2" << std::endl;
    std::cout << "Best result in current generation: " << winner->get_fitness() << std::endl;
}
