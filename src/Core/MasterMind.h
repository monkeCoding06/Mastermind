#ifndef MASTERMIND_MASTERMIND_H
#define MASTERMIND_MASTERMIND_H

#include <iostream>
#include <vector> // Include vector header
#include "../Utility/RandomNumberGenerator.h"

class MasterMind
{
private:
    std::vector<std::string> colorList = {"blue", "pink", "white", "red", "yellow", "grey"};
    std::string colorCode[4] = {};

    void setColorCode();
    void printColorCode();

public:
    MasterMind();

    std::string gameField[12][4];

    auto getColorList() const
    { return colorList; } // Return as std::vector<std::string>

    auto getColorCode() const
    { return colorCode; }
};

#endif //MASTERMIND_MASTERMIND_H
