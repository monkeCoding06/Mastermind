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

    void setColorCode(StringVector &code);

protected:

    IntPair getFeedback(const StringVector &guess, StringVector &colorCodeToCheck);

    StringVector colorCode;


    std::vector<std::vector<std::string>> gameField;


    [[nodiscard]] StringVector getColorList() const
    { return colorList; }

    int amountOfColors = colorList.size();
    int possibilities;
    int codeLength = 4;


public:
    explicit MasterMind()
    {
        this->possibilities = pow(amountOfColors, codeLength);
        gameField.resize(12, std::vector<std::string>(codeLength));


        StringVector codeToSet = this->generateColorCode(4);
        this->setColorCode(codeToSet);
        this->printColorCode();
    }

    explicit MasterMind(StringVector code)
    {

        this->codeLength = code.size();
        if (codeLength != 4)
        {
            std::cerr << "Error: The code you entered is " << this->codeLength << " long, but it has to be 4"
                      << std::endl << "____________________________________________________________________"
                      << std::endl << "MasterMind(std::vector<std::string>(4))" << std::endl
                      << "                                    ^" << std::endl
                      << "                                    | vector has to have 4 elements" << std::endl
                      << "____________________________________________________________________" << std::endl;
            return;
        }

        this->possibilities = pow(amountOfColors, codeLength);
        gameField.resize(12, std::vector<std::string>(codeLength));


        this->setColorCode(code);
        this->printColorCode();
    }


};

#endif //MASTERMIND_MASTERMIND_H
