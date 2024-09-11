
#ifndef MASTERMIND_MASTERMIND_H
#define MASTERMIND_MASTERMIND_H

#include <iostream>
#include "../Utility/RandomNumberGenerator.h"

class MasterMind
{
private:
    std::string colorList[8] = {"blue", "pink", "white", "red", "yellow", "grey", "green", "orange"};
    std::string colorCode[4] = {};

    void setColorCode();

    void printColorCode();


public:
    MasterMind();

    std::string gameField[12][4];

    auto getColorList()
    { return colorList; }

    auto getColorCode()
    { return colorCode; }

};


#endif //MASTERMIND_MASTERMIND_H
