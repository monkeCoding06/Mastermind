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

    StringVector generateColorCode(int colorCodeLength);

    void printColorCode();

protected:

    IntPair getFeedback(const StringVector &guess, StringVector &colorCodeToCheck);

    StringVector colorCode;


    std::string gameField[12][4];

    [[nodiscard]] StringVector getColorList() const
    { return colorList; }


public:
    explicit MasterMind(int codeLength);

};

#endif //MASTERMIND_MASTERMIND_H
