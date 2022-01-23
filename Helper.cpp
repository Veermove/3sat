#include "Helper.hpp"
#include <iostream>

CGAIndividual* Helper::run_tournament(int _tournament_size, 
    std::vector<CGAIndividual*> population, CMax3SatProblem problem)
{
    srand (time(NULL));
    std::vector<CGAIndividual*> winners;
    for (int i = 0; i < _tournament_size; i++)
    {
        int winner_index = (rand() % population.size()) - 1;
        winners.push_back(population[winner_index]); 
        population.erase(population.begin() + winner_index);
    }
    
    CGAIndividual *winner = winners[0];
    int winners_result = problem.compute(winner->get_values(), problem.get_clauses());
    for (int i = 1; i < winners.size(); i++)
    {
        int cur_res = problem.compute(winners[i]->get_values(), problem.get_clauses());
        if (cur_res > winners_result)
        {
            winners_result = cur_res;
            winner = winners[i];
        }
    }
    std::cout << "winner res " << winners_result << std::endl;
    return winner;
}
