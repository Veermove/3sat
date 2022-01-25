#include "CGAOptimizer.hpp"

CGAOptimizer::CGAOptimizer() { }

CGAOptimizer::CGAOptimizer(int _population_size, int _crossover_prop, int _mutation_prop, CMax3SatProblem *_problem)
{
    population_size = _population_size;
    crossover_prop = _crossover_prop; 
    mutation_prop = _mutation_prop; 
    problem = _problem;
}

CGAOptimizer::~CGAOptimizer() 
{
    for (auto & value: clauses)
    {
        delete value;
    }
    for (auto & value: solutions)
    {
        delete value;
    }
}

bool CGAOptimizer::initialize(std::string filename)
{
    try 
    {
        clauses = problem->load(filename);
        // Not implemented "find max"
        // variable_quantity = problem->get_variable_number();
        variable_quantity = 50;
    } catch (...)
    {
        return false;
    }

    for (int i = 0; i < population_size; i++)
    {
        CGAIndividual *randomized = new CGAIndividual(false, variable_quantity, problem);
        (*randomized).initialize_random(variable_quantity);
        solutions.push_back(randomized);
    }

    return true;
}

void CGAOptimizer::run_iteration()
{
    std::vector<CGAIndividual*> next_generation;
    // std::cout << next_generation.size() << " < " << solutions.size() << std::endl;
    while (next_generation.size() < solutions.size())
    {
        // std::cout << "START SIZE " << next_generation.size() << std::endl;
        
        CGAIndividual *parent_one = run_tournament();
        CGAIndividual *parent_two = run_tournament();
        // std::cout << "safe 1" << std::endl;
        CGAIndividual *child_one = new CGAIndividual(false, variable_quantity, problem);
        CGAIndividual *child_two = new CGAIndividual(false, variable_quantity, problem);

        // std::cout << "safe 2" << std::endl;

        std::tie(*child_one, *child_two) = run_crossover(*parent_one, *parent_two);

        // std::cout << "safe 3" << std::endl;
        
        (*child_one).perform_mutation(mutation_prop);
        (*child_two).perform_mutation(mutation_prop);
        
        next_generation.push_back(child_one);
        next_generation.push_back(child_two);

        // std::cout << "END SIZE " << next_generation.size() << std::endl;
    }
    solutions = next_generation;
    // std::cout << "endof CGAOptimizer::run_iteration()" << std::endl;
}

std::tuple<CGAIndividual, CGAIndividual> CGAOptimizer::run_crossover(CGAIndividual parent1, CGAIndividual parent2)
{
    const int bias = 50;
    srand (time(NULL));
    if (Helper::random_true_false(crossover_prop)) 
    {
        return CGAIndividual::perform_crossover(parent1, parent2, bias);
    } else 
    {
        return std::make_pair(parent1, parent2);
    }
}

CGAIndividual* CGAOptimizer::run_tournament()
{
    // std::cout << "CGAOptimizer::run_tournament" << std::endl;
    const int tournament_size = 10;
    return Helper::run_tournament(tournament_size, solutions, problem);
}

void CGAOptimizer::show_best()
{
    CGAIndividual *winner = solutions[0];
    int winners_result = problem->compute(winner->get_values(), *(problem->get_clauses_pointer()));

    for (int i = 1; i < solutions.size(); i++)
    {
        int cur_res = problem->compute(solutions[i]->get_values(), *(problem->get_clauses_pointer()));
        if (cur_res >= winners_result)
        {
            winners_result = cur_res;
            winner = solutions[i];
        }
    }
    std::cout << "Best result in current generation: " << winner->get_fitness() << "/" << problem->get_clauses_pointer()->size() << std::endl;
}
