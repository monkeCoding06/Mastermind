#ifndef MASTERMIND_MASTERMIND_H
#define MASTERMIND_MASTERMIND_H

#include <iostream>
#include <vector>
#include "../Utility/RandomNumberGenerator.h"

class MasterMind
{
    friend class SolvingAlgorithm;


private:
    std::vector<std::string> colorList = {"blue", "pink", "white", "red", "yellow", "grey"};
    std::string colorCode[4] = {};

    void setColorCode();
    void printColorCode();

public:
    MasterMind();

    std::string gameField[12][4];

    auto getColorList() const
    { return colorList; }

    auto getColorCode() const
    { return colorCode; }

protected:

    std::pair<int, int> getFeedback(const std::vector<std::string>& guess);
};

#endif //MASTERMIND_MASTERMIND_H
