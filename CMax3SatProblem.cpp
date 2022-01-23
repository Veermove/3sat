#include "CMax3SatProblem.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <unordered_map>
#include <cstdlib>

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
    return cases;
}

int CMax3SatProblem::compute(std::vector<bool> solution, std::vector<Pack *> clauses)
{
    std::cout << "CMax3SatProblem::compute" << std::endl;
    
    // creating a map of true/false to corresponding int
    std::unordered_map<int, bool> solutionMap;
    
    // iteratre through vector "solution" of <bool>
    for (std::vector<bool>::iterator itr = solution.begin(); itr != solution.end(); ++itr)
    {
        solutionMap[itr._M_offset + 1] = *itr;
    }
    int counter = 0;

    // iteratre through vector "clauses" of <Pack *>
    for (auto const& value: clauses)
    {
        std::cout << " compute: " << value->toString() << std::endl;
        // get variable
        int firstVar = value->getFirst();
        // check if this variable is negated and if this negated variable is true 
        if (value->first_getIsNegated() && !solutionMap[firstVar])
        {
            counter++;
            continue;
        } else if (solutionMap[firstVar]) // else check if non negated variable is ture
        {
            counter++;
            continue;
        }

        int secondVar = value->getSecond();
        if (value->second_getIsNegated() && !solutionMap[secondVar])
        {
            counter++;
            continue;
        } else if (solutionMap[secondVar])
        {
            counter++;
            continue;
        }

        int thirdVar = value->getThird();
        if (value->third_getIsNegated() && !solutionMap[thirdVar])
        {
            counter++;
            continue;
        } else if (solutionMap[thirdVar])
        {
            counter++;
            continue;
        }
    }
    return counter;
}


Pack* CMax3SatProblem::get_pack_from_line(std::string line)
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
