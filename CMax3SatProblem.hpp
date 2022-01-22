#include "Pack.hpp"
#include <vector>

class CMax3SatProblem
{
    public:
        std::vector<Pack*> load(std::string filename); 
        int compute(std::vector<bool> solution, std::vector<Pack *> clauses);

    private:
        Pack* get_pack_from_line(std::string line);

};
