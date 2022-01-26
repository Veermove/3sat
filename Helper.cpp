#include "Helper.hpp"

#include <iostream>

CGAIndividual* Helper::run_tournament(int _tournament_size, std::vector<CGAIndividual*> population)
{
    std::vector<CGAIndividual*> winners = {};

    for (int i = 0; i < _tournament_size; i++)
    {
        int winner_index = rand() % population.size();
        winners.push_back(population[winner_index]); 
        population.erase(population.begin() + winner_index);
    }

    CGAIndividual *winner = winners[0];

    int winners_result = winner->get_fitness();

    for (int i = 1; i < winners.size(); i++)
    {
        int cur_res = winners[i]->get_fitness();
        if (cur_res > winners_result)
        {
            winners_result = cur_res;
            winner = winners[i];
        }
    }
    return winner;
}

bool Helper::random_true_false(int _chance_of_truth)
{
    return (rand() % 100) + 1 <= _chance_of_truth;
}
