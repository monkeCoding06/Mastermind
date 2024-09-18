
#ifndef MASTERMIND_SOLVINGALGORITHM_H
#define MASTERMIND_SOLVINGALGORITHM_H

#include "MasterMind.h"
#include <cmath>

class SolvingAlgorithm
{
public:
    void solve(MasterMind &game);

    auto getFeedBackArray()
    { return feedBackArray; }


private:
    bool solved = false;
    int gameMove = 1;
    std::string currentGuess[4];
    int feedBackArray[12][2];
    int bestFeedbackIndex = -1;
    int bestFeedbackScore = -1;

    int possibilities = pow(6, 4);
    int possibleCodes[1296][4];


    void makeFirstGuess(MasterMind &game);

    void printGameField(MasterMind &game) const;

    int checkRightColors(MasterMind &game) const;

    int checkRightPositions(MasterMind &game) const;

    void checkAndSafe(MasterMind &game);

    void resolveFeedBack();

    void performNewGuessBasedOnFeedback(MasterMind &game);

    bool isCodeValid(int *code, MasterMind &game);

    static int checkRightColorsForCode(int *guess, int *code);

    static int checkRightPositionsForCode(int *guess, int *code);

    void createEveryPosibility();
};


#endif //MASTERMIND_SOLVINGALGORITHM_H
