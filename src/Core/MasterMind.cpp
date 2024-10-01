
#include "MasterMind.h"

StringVector MasterMind::generateColorCode(int colorCodeLength)
{

    StringVector generatedColorCode;
    for (int i = 0; i < colorCodeLength; i++)
    {
        generatedColorCode.push_back(colorList[RandomNumberGenerator::generateRandomNumber(0, 5)]);
    }

    colorCode = generatedColorCode;
    return generatedColorCode;
}

void MasterMind::printColorCode()
{
    std::cout << "------------------------------------------------------------------------------------------";
    std::cout << std::endl;
    std::cout << "set color code: " << std::endl;
    for (auto &color: colorCode)
    {
        std::cout << "\t" << color;
    }
    std::cout << std::endl;
    std::cout << "------------------------------------------------------------------------------------------";
    std::cout << std::endl;
}


MasterMind::MasterMind(int codeLength)
{
    this->generateColorCode(codeLength);
    this->printColorCode();
}


IntPair MasterMind::getFeedback(const StringVector &guess, StringVector &colorCodeToCheck)
{
//    for (int i = 0; i < 4; ++i)
//    {
//        std::cout << colorCodeToCheck[i] << " ";
//    }
//    std::cout << std::endl;
//
//
//    for (int i = 0; i < 4; ++i)
//    {
//        std::cout << guess[i] << " ";
//    }
//    std::cout << std::endl;

    int rightPositions = 0;
    int rightColors = 0;
    bool matchedSecret[4] = {false};
    bool matchedGuess[4] = {false};

    for (int i = 0; i < 4; ++i)
    {
        if (guess[i] == colorCodeToCheck[i])
        {
            rightPositions++;
            matchedSecret[i] = true;
            matchedGuess[i] = true;
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        if (!matchedGuess[i])
        {
            for (int j = 0; j < 4; ++j)
            {
                if (!matchedSecret[j] && guess[i] == colorCodeToCheck[j])
                {
                    rightColors++;
                    matchedSecret[j] = true;
                    break;
                }
            }
        }
    }

    return {rightColors, rightPositions};
}