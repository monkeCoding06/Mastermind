
#ifndef MASTERMIND_SOLVINGALGORITHM_H
#define MASTERMIND_SOLVINGALGORITHM_H

#include "MasterMind.h"

class SolvingAlgorithm
{
public:
    void solve(MasterMind &game);


private:
    bool solved = false;
    int gameMove = 0;
    std::string currentGuess[4];


    void makeFirstGuess(MasterMind &game);

    void printGameField(MasterMind &game);

    int checkRightColors(MasterMind &game);

    int checkRightPositions(MasterMind &game);

    void checkAndSafe(MasterMind &game);
};


#endif //MASTERMIND_SOLVINGALGORITHM_H
