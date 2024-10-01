#include "src/Core/MasterMind.h"
#include "src/Core/SolvingAlgorithm.h"

int main()
{
    MasterMind masterMind;
    SolvingAlgorithm solvingAlgorithm(masterMind);

    int test = solvingAlgorithm.solve(masterMind);

    std::cout << "in main: " << test << std::endl;

}
