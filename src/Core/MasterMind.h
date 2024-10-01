#ifndef MASTERMIND_MASTERMIND_H
#define MASTERMIND_MASTERMIND_H

#include <iostream>
#include <vector>
#include "../Utility/RandomNumberGenerator.h"

typedef std::vector<std::string> StringVector;
typedef std::vector<bool> BoolVector;
typedef std::pair<int, int> IntPair;

class MasterMind
{
    friend class SolvingAlgorithm;


private:
    StringVector colorList = {"blue", "pink", "white", "red", "yellow", "grey"};

    void setColorCode();

    void printColorCode();

public:
    MasterMind();

    std::string colorCode[4] = {};

    std::string gameField[12][4];

    [[nodiscard]] StringVector getColorList() const { return colorList; }

protected:

    IntPair getFeedback(const std::vector<std::string> &guess, std::string colorCodeToCheck[4]);
};

#endif //MASTERMIND_MASTERMIND_H
