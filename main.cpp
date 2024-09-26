#include "src/Core/MasterMind.h"
#include "src/Core/SolvingAlgorithm.h"

int main()
{
    MasterMind masterMind;
    SolvingAlgorithm solvingAlgorithm(masterMind);

solvingAlgorithm.solve(masterMind);
}
