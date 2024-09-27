#include "SolvingAlgorithm.h"
#include <iostream>
#include <vector>
#include <string>

SolvingAlgorithm::SolvingAlgorithm(MasterMind &game)
{
    auto colors = game.getColorList();
    currentGuess = {colors[0], colors[0], colors[1], colors[1]};
    createPossibilities(game);
}

void SolvingAlgorithm::solve(MasterMind &game)
{
    if (gameMove == 0) {
        makeFirstGuess(game);
        printGameField(game);
    }

    if (solved) {
        std::cout << "Found right code!";
        return;
    }

    if (gameMove >= 12) {
        std::cout << "Max amount of moves reached." << std::endl;
        return;
    }

    performNewGuessBasedOnFeedback(game);
    printGameField(game);
    solve(game);
}

void SolvingAlgorithm::makeFirstGuess(MasterMind &game)
{
    for (int i = 0; i < 4; ++i) {
        game.gameField[gameMove][i] = currentGuess[i];
    }
    gameMove++;
}

void SolvingAlgorithm::createPossibilities(MasterMind &game)
{
    std::vector<std::string> colorList = game.getColorList();
    for (int i = 0; i < 1296; ++i) {
        std::vector<std::string> possibility(4);
        int code = i;
        for (int j = 3; j >= 0; --j) {
            possibility[j] = colorList[code % colorList.size()];
            code /= colorList.size();
        }
        possibleCodes.push_back(possibility);
    }
    std::cout << "Total possibilities: " << possibleCodes.size() << std::endl;
}

void SolvingAlgorithm::eliminateImpossibleCodes(const std::vector<std::string> &guess, int rightColors, int rightPositions)
{
    auto iterator = possibleCodes.begin();
    while (iterator != possibleCodes.end()) {
        int possibleRightPositions = 0;
        int possibleRightColors = 0;

        std::vector<std::string> possibleCode = *iterator;

        std::vector<bool> matchedGuess(4, false);
        std::vector<bool> matchedCode(4, false);

        for (int i = 0; i < 4; ++i) {
            if (possibleCode[i] == guess[i]) {
                possibleRightPositions++;
                matchedGuess[i] = true;
                matchedCode[i] = true;
            }
        }

        for (int i = 0; i < 4; ++i) {
            if (matchedGuess[i]) {
                continue;
            }

            for (int j = 0; j < 4; ++j) {
                if (matchedCode[j]) {
                    continue;
                }

                if (possibleCode[i] == guess[j]) {
                    possibleRightColors++;
                    matchedCode[j] = true;
                    break;
                }
            }
        }

        if (possibleRightColors != rightColors || possibleRightPositions != rightPositions) {
            iterator = possibleCodes.erase(iterator);
        } else {
            ++iterator;
        }
    }
    std::cout << "\tRemaining possible codes: " << possibleCodes.size() << "\t |" << std::endl
              << "------------------------------------------------------------------------------------------"
              << std::endl;
}

std::vector<std::string> SolvingAlgorithm::selectNextGuess()
{
    if (!possibleCodes.empty()) {
        return possibleCodes.front();
    } else {
        std::cout << "No more possible guesses. Something went wrong." << std::endl;
        return {};
    }
}

void SolvingAlgorithm::performNewGuessBasedOnFeedback(MasterMind &game)
{
    std::pair<int, int> feedback = game.getFeedback(currentGuess);
    int rightColors = feedback.first;
    int rightPositions = feedback.second;

    if (rightPositions == 4) {
        solved = true;
        return;
    }

    std::cout << " | Feedback - Right colors: " << rightColors << ", Right positions: " << rightPositions << std::endl;

    eliminateImpossibleCodes(currentGuess, rightColors, rightPositions);

    if (possibleCodes.empty()) {
        std::cout << "No more possible guesses. Ending the game." << std::endl;
        return;
    }

    currentGuess = selectNextGuess();
    for (int i = 0; i < 4; ++i) {
        game.gameField[gameMove][i] = currentGuess[i];
    }

    gameMove++;
}

void SolvingAlgorithm::printGameField(MasterMind &game) const
{
    if (solved) { return; }
    std::cout << gameMove;

    auto gameField = game.gameField;
    for (int j = 0; j < 4; j++) {
        std::cout << "\t" << gameField[gameMove - 1][j];
    }
    std::cout << "\t";
}
