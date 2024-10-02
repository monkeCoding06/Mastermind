#ifndef MASTERMIND_MASTERMIND_H
#define MASTERMIND_MASTERMIND_H

#include <iostream>
#include <vector>
#include <cmath>
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
//    std::vector<std::vector<std::string>> gameField;


    [[nodiscard]] StringVector getColorList() const
    { return colorList; }

    int amountOfColors = colorList.size();
    int possibilities;
    int codeLength;


public:
    explicit MasterMind(int length)
    {
        this->codeLength = length;
        this->possibilities = pow(amountOfColors, codeLength);

        StringVector codeToSet = this->generateColorCode(length);
        this->setColorCode(codeToSet);
        this->printColorCode();
    }

    explicit MasterMind(StringVector code)
    {

        this->codeLength = code.size();
        this->possibilities = pow(amountOfColors, codeLength);

        this->setColorCode(code);
        this->printColorCode();
    }


    void setColorCode(StringVector &code);
};

#endif //MASTERMIND_MASTERMIND_H
