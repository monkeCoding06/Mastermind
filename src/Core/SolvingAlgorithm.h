#ifndef SOLVINGALGORITHM_H
#define SOLVINGALGORITHM_H

#include <vector>
#include <string>
#include <utility>
#include "MasterMind.h"


class SolvingAlgorithm{
public:
    explicit SolvingAlgorithm(MasterMind &game);

    void makeFirstGuess(MasterMind &game);
    void performNewGuessBasedOnFeedback(MasterMind &game);
    int solve(MasterMind &game);

private:
    void eliminateImpossibleCodes(const StringVector & guess, int rightColors, int rightPositions,  MasterMind &game);
    StringVector selectNextGuess(MasterMind &game);

    int gameMove = 0;
    bool solved = false;
    std::vector<std::vector<std::string>> possibleCodes;
    StringVector currentGuess;

    void createPossibilities(MasterMind &game);


    void printGameField(MasterMind &game) const;
};

#endif
