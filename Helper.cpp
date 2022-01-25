#include "Helper.hpp"
#include <iostream>

CGAIndividual* Helper::run_tournament(int _tournament_size, 
    std::vector<CGAIndividual*> population, CMax3SatProblem *problem)
{
    std::cout << "Helper::run_tournament(...)" << std::endl;
    
    std::vector<CGAIndividual*> winners = {};

    for (int i = 0; i < _tournament_size; i++)
    {
        int winner_index = (rand() % population.size()) - 1;
        winners.push_back(population[winner_index]); 
        population.erase(population.begin() + winner_index);
    }

    CGAIndividual *winner = winners[0];

    int winners_result = winner->get_fitness();

    std::cout << "check 2 + " << winners.size() << std::endl;

    for (int i = 1; i < winners.size(); i++)
    {
        std::cout << "check 3 : " << winners.size() << std::endl;
        // int cur_res = problem->compute(winners[i]->get_values(), *problem->get_clauses_pointer());
        int cur_res = winners[i]->get_fitness();
        std::cout << "check 3 : " << i << " cur res " << cur_res << std::endl;
        if (cur_res > winners_result)
        {
            winners_result = cur_res;
            winner = winners[i];
        }
    }
    std::cout << "winner res " << winners_result << std::endl;
    return winner;
}

bool Helper::random_true_false(int _chance_of_truth)
{
    return (rand() % 100) + 1 <= _chance_of_truth;
}
