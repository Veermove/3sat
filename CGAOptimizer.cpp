#include "CGAOptimizer.hpp"

CGAOptimizer::CGAOptimizer() { }

CGAOptimizer::CGAOptimizer(int _population_size, int _crossover_prop, int _mutation_prop, int _parental_bias,
     CMax3SatProblem *_problem)
{
    population_size = _population_size;
    crossover_prop = _crossover_prop; 
    mutation_prop = _mutation_prop; 
    parental_bias = _parental_bias;
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

bool CGAOptimizer::initialize(const std::string filename)
{
    try 
    {
        clauses = problem->load(filename);
        variable_quantity = problem->get_variable_number();
    } catch (...)
    {
        return false;
    }

    for (int i = 0; i < population_size; i++)
    {
        CGAIndividual *randomized = new CGAIndividual(true, variable_quantity, problem);
        (*randomized).randomize(variable_quantity);
        solutions.push_back(randomized);
    }

    return true;
}

void CGAOptimizer::run_iteration()
{
    std::vector<CGAIndividual*> next_generation;

    while (next_generation.size() < solutions.size())
    {
        CGAIndividual *parent_one = run_tournament();
        CGAIndividual *parent_two = run_tournament();

        // CGAIndividual child_one(false, variable_quantity, problem);
        // CGAIndividual child_two(false, variable_quantity, problem);

        // std::tie(child_one, child_two) = run_crossover(*parent_one, *parent_two);

        // child_one.perform_mutation(mutation_prop);
        // child_two.perform_mutation(mutation_prop);

        // next_generation.push_back(&child_one);
        // next_generation.push_back(&child_two);

        CGAIndividual *child_one = new CGAIndividual(false, variable_quantity, problem);
        CGAIndividual *child_two = new CGAIndividual(false, variable_quantity, problem);

        std::tie(*child_one, *child_two) = run_crossover(*parent_one, *parent_two);

        child_one->perform_mutation(mutation_prop);
        child_two->perform_mutation(mutation_prop);

        next_generation.push_back(child_one);
        next_generation.push_back(child_two);
    }

    for (const auto &val : solutions)
    {
        delete val;
    }

    solutions = next_generation;
}

std::tuple<CGAIndividual, CGAIndividual> CGAOptimizer::run_crossover(const CGAIndividual parent1, const CGAIndividual parent2)
{
    if (Helper::random_true_false(crossover_prop)) 
    {
        return CGAIndividual::perform_crossover(parent1, parent2, parental_bias);
    } else 
    {
        return std::make_pair(parent1, parent2);
    }
}

CGAIndividual* CGAOptimizer::run_tournament()
{
    const int tournament_size = 10;
    return Helper::run_tournament(tournament_size, solutions);
}

void CGAOptimizer::show_best()
{
    CGAIndividual *winner = solutions[0];
    // int winners_result = problem->compute(winner->get_values(), *(problem->get_clauses_pointer()));

    int winners_result = winner->get_fitness();

    for (int i = 1; i < solutions.size(); i++)
    {
        int cur_res = solutions[i]->get_fitness();
        if (cur_res >= winners_result)
        {
            winners_result = cur_res;
            winner = solutions[i];
        }
    }
    std::cout << "Best result in current generation: " << winner->get_fitness() << "/" << problem->get_clauses_pointer()->size();
    std::string genome = " , genome: ";
    for (auto const &val : winner->get_values()) 
    {
        genome += val ? '1' : '0';
    }
    // std::cout << genome;
    std::cout << std::endl;
}
