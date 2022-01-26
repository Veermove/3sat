#pragma once

#include "Pack.hpp"

#include <vector>

class CMax3SatProblem
{
    public:
        ~CMax3SatProblem();
        std::vector<Pack*> load(std::string filename); 
        int compute(std::vector<bool> solution, std::vector<Pack *> clauses);
        int get_variable_number();

        std::vector<Pack*>* get_clauses_pointer();
    private:
        Pack* get_pack_from_line(std::string line);

        std::vector<Pack*> clauses;

};
