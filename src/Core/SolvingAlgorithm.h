
#ifndef MASTERMIND_SOLVINGALGORITHM_H
#define MASTERMIND_SOLVINGALGORITHM_H

#include "MasterMind.h"

class SolvingAlgorithm
{
public:
    void solve(MasterMind &game);


private:
    int gameMove = 0;

    void makeFirstGuess(MasterMind &game);

    void printGameField(MasterMind &game);

};


#endif //MASTERMIND_SOLVINGALGORITHM_H
