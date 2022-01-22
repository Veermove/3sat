#include <iostream>
#include <vector>
#include <string>
#include "CMax3SatProblem.hpp"

int main () 
{
    CMax3SatProblem problem;
    // problem.load("m3s_50_0.txt");

    std::vector<bool> a;
    a.push_back(false);
    a.push_back(true);

    std::cout << "hello: " << problem.compute(a, problem.load("testCases/test_pr.txt")) << std::endl;
};
