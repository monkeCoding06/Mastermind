#include "SolvingAlgorithm.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

SolvingAlgorithm::SolvingAlgorithm(MasterMind &game)
{
    StringVector colors = game.getColorList();
    currentGuess = {colors[0], colors[0], colors[1], colors[1]};
    createPossibilities(game);
}

int SolvingAlgorithm::solve(MasterMind &game)
{
    if (gameMove == 0)
    {
        makeFirstGuess(game);
        printGameField(game);
    }

    if (solved)
    {
        std::cout << "Found right code!";
        return gameMove;
    }

    if (gameMove >= 12)
    {
        std::cout << "Max amount of moves reached." << std::endl;
        return gameMove;
    }

    performNewGuessBasedOnFeedback(game);
    printGameField(game);
    solve(game);
    return gameMove;
}

void SolvingAlgorithm::makeFirstGuess(MasterMind &game)
{
    for (int i = 0; i < 4; i++)
    {
        game.gameField[gameMove][i] = currentGuess[i];
    }
    gameMove++;
}

void SolvingAlgorithm::createPossibilities(MasterMind &game)
{
    StringVector colorList = game.getColorList();
    for (int i = 0; i < 1296; i++)
    {
        StringVector possibility(4);
        int code = i;
        for (int j = 3; j >= 0; j--)
        {
            possibility[j] = colorList[code % colorList.size()];
            code /= colorList.size();
        }
        possibleCodes.push_back(possibility);
    }
    std::cout << "Total possibilities: " << possibleCodes.size() << std::endl;
}


void
SolvingAlgorithm::eliminateImpossibleCodes(const StringVector &guess, int rightColors, int rightPositions)
{
    auto iterator = possibleCodes.begin();
    while (iterator != possibleCodes.end())
    {
        int possibleRightPositions = 0;
        int possibleRightColors = 0;

        StringVector possibleCode = *iterator;

        BoolVector matchedGuess(4, false);
        BoolVector matchedCode(4, false);

        for (int i = 0; i < 4; i++)
        {
            if (possibleCode[i] == guess[i])
            {
                possibleRightPositions++;
                matchedGuess[i] = true;
                matchedCode[i] = true;
            }
        }

        for (int i = 0; i < 4; i++)
        {
            if (matchedGuess[i])
            {
                continue;
            }

            for (int j = 0; j < 4; j++)
            {
                if (matchedCode[j])
                {
                    continue;
                }

                if (possibleCode[i] == guess[j])
                {
                    possibleRightColors++;
                    matchedCode[j] = true;
                    break;
                }
            }
        }

        if (possibleRightColors != rightColors || possibleRightPositions != rightPositions)
        {
            iterator = possibleCodes.erase(iterator);
        } else
        {
            iterator++;
        }
    }
    std::cout << "\tRemaining possible codes: " << possibleCodes.size() << "\t |" << std::endl
              << "------------------------------------------------------------------------------------------"
              << std::endl;
}

StringVector SolvingAlgorithm::selectNextGuess(MasterMind &game)
{
    if (possibleCodes.empty())
    {
        std::cout << "No more possible guesses. Something went wrong." << std::endl;
        return {};
    }

    for (StringVector guessToCheck: possibleCodes)
    {
        std::string codeConvertedToStringArr[4];
        for (int i = 0; i < 4; i++)
        {
            codeConvertedToStringArr[i] = guessToCheck[i];
        }

        for (StringVector guess: possibleCodes)
        {
            IntPair feedback = game.getFeedback(guess, codeConvertedToStringArr);

            int rightColors = feedback.first;
            int rightPositions = feedback.second;


//            std::cout << "feedback " << std::endl;
//            std::cout << rightPositions << "|" << rightColors;
//            std::cout << std::endl;



        }
    }


    return possibleCodes.front();
}


void SolvingAlgorithm::performNewGuessBasedOnFeedback(MasterMind &game)
{
    IntPair feedback = game.getFeedback(currentGuess, game.colorCode);
    int rightColors = feedback.first;
    int rightPositions = feedback.second;

    if (rightPositions == 4)
    {
        solved = true;
        return;
    }

    std::cout << " | Feedback - Right colors: " << rightColors << ", Right positions: " << rightPositions << std::endl;

    eliminateImpossibleCodes(currentGuess, rightColors, rightPositions);

    if (possibleCodes.empty())
    {
        std::cout << "No more possible guesses. Ending the game." << std::endl;
        return;
    }

    currentGuess = selectNextGuess(game);
    for (int i = 0; i < 4; i++)
    {
        game.gameField[gameMove][i] = currentGuess[i];
    }

    gameMove++;
}

void SolvingAlgorithm::printGameField(MasterMind &game) const
{
    if (solved)
    { return; }
    std::cout << gameMove;

    auto gameField = game.gameField;
    for (int j = 0; j < 4; j++)
    {
        std::cout << "\t" << gameField[gameMove - 1][j];
    }
    std::cout << "\t";
}
