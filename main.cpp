#include "src/Core/MasterMind.h"
#include "src/Core/SolvingAlgorithm.h"

//TODO: fix the mastermind constructor, so i can manually set the code length and the code itself outside of any of the mastermind class

int main()
{
    MasterMind masterMind(4);
    SolvingAlgorithm solvingAlgorithm(masterMind);

    int test = solvingAlgorithm.solve(masterMind);

    std::cout << "in main: " << test << std::endl;

}
