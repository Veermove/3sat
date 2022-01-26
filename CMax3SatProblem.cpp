#include "CMax3SatProblem.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <vector>

CMax3SatProblem::~CMax3SatProblem()
{
    for (auto & value: clauses)
    {
        delete value;
    }
}

std::vector<Pack*> CMax3SatProblem::load(std::string filename)
{
    std::cout << "CMax3SatProblem::load" << std::endl;
    std::ifstream givenfile(filename.c_str());
    if (!givenfile.good())
    {
        throw "Failed to open file"; 
    }

    std::vector<Pack*> cases;

    for (std::string line; std::getline(givenfile, line); )
    {
        cases.push_back(get_pack_from_line(line));
    }

    givenfile.close();
    clauses = cases;
    return cases;
}

int CMax3SatProblem::compute(std::vector<bool> solution, std::vector<Pack *> clauses)
{
    // std::cout << "CMax3SatProblem::compute" << std::endl;
    int counter = 0;
    for (auto const& value: clauses)
    {
        if (value->is_staisfied_by(&solution))
        {
            counter++;
        }
    }
    return counter;
}

std::vector<Pack*>* CMax3SatProblem::get_clauses_pointer()
{
    return &clauses;
}

int CMax3SatProblem::get_variable_number()
{
    std::set<int> variables;
    for (auto &val : clauses)
    {
        variables.insert(val->getFirst());
        variables.insert(val->getThird());
        variables.insert(val->getSecond());
    }
    return variables.size();
}

Pack* CMax3SatProblem::get_pack_from_line(const std::string line)
{
    std::regex patter("\\( (-*\\d+)  (-*\\d+)  (-*\\d+)  \\)");
    std::smatch match; 
    if (std::regex_search(line, match, patter))
    {
        int first = std::stoi(match.str(1)); 
        int second = std::stoi(match.str(2));
        int third = std::stoi(match.str(3));
        bool first_negation = first < 0 || (first == 0 && !match.str(1).find("-"));
        bool second_negation = second < 0 || (second == 0 && !match.str(2).find("-"));
        bool third_negation = third < 0 || (third == 0 && !match.str(3).find("-"));
        return new Pack(std::abs(first), first_negation, 
            std::abs(second), second_negation, 
            std::abs(third), third_negation);
    } else 
    {
        throw "Failed to open file: Invalid clause";
    }
}
