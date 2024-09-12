
#ifndef MASTERMIND_SOLVINGALGORITHM_H
#define MASTERMIND_SOLVINGALGORITHM_H

#include "MasterMind.h"

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


    void makeFirstGuess(MasterMind &game);

    void printGameField(MasterMind &game);

    int checkRightColors(MasterMind &game);

    int checkRightPositions(MasterMind &game);

    void checkAndSafe(MasterMind &game);

    void resolveFeedBack();

    void performNewGuessBasedOnFeedback(MasterMind &game);
};


#endif //MASTERMIND_SOLVINGALGORITHM_H
