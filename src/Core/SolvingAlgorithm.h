#ifndef SOLVINGALGORITHM_H
#define SOLVINGALGORITHM_H

#include <vector>
#include <string>
#include <utility>
#include "MasterMind.h"

class SolvingAlgorithm {
public:
    explicit SolvingAlgorithm(MasterMind &game);

    void makeFirstGuess(MasterMind &game);
    void performNewGuessBasedOnFeedback(MasterMind &game);
    void solve(MasterMind &game);

private:
    void eliminateImpossibleCodes(const std::vector<std::string>& guess, int rightColors, int rightPositions);
    std::vector<std::string> selectNextGuess();

    int gameMove = 0;
    bool solved = false;
    std::vector<std::vector<std::string>> possibleCodes;
    std::vector<std::string> currentGuess;

    int feedBackArray[12][2]{};
    void createPossibilities(MasterMind &game);

    int checkRightColors(MasterMind &game);

    int checkRightPositions(MasterMind &game);


    void printGameField(MasterMind &game) const;
};

#endif
