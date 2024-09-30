
#include "MasterMind.h"

void MasterMind::setColorCode()
{
    int colorCodeLength = std::end(colorCode) - std::begin(colorCode);

    for (int i = 0; i < colorCodeLength; i++)
    {
        colorCode[i] = colorList[RandomNumberGenerator::generateRandomNumber(0, 5)];
    }


}

void MasterMind::printColorCode()
{
    std::cout << "------------------------------------------------------------------------------------------"
              << std::endl;
    std::cout << "set color code: " << std::endl;
    for (auto &color: colorCode)
    {
        std::cout << "\t" << color;
    }
    std::cout << std::endl;
    std::cout << "------------------------------------------------------------------------------------------"
              << std::endl;
}


MasterMind::MasterMind()
{
    this->setColorCode();
    this->printColorCode();
}


std::pair<int, int> MasterMind::getFeedback(const std::vector<std::string> &guess, std::string colorCodeToCheck[4])
{
    for (int i = 0; i < 4; ++i)
    {
        std::cout << colorCodeToCheck[i] << " ";
    }
    std::cout << std::endl;

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