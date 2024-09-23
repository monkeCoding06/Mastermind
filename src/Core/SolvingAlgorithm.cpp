#include <vector>
#include <unordered_map>
#include <algorithm>
#include "SolvingAlgorithm.h"

void SolvingAlgorithm::solve(MasterMind &game)
{
    if (gameMove == 1) {
        createEveryPosibility();
        makeFirstGuess(game);
    }

    if (solved) {
        std::cout << "\n\tPattern found!" << std::endl;
        return;
    }

    if (gameMove >= 12) {
        return;
    }

    performNewGuessBasedOnFeedback(game);
    solve(game);
}


void SolvingAlgorithm::makeFirstGuess(MasterMind &game)
{
    auto colorList = game.getColorList();
    auto &gameField = game.gameField;

    currentGuess[0] = colorList[0];
    currentGuess[1] = colorList[0];
    currentGuess[2] = colorList[1];
    currentGuess[3] = colorList[1];

    for (int i = 0; i < 4; i++) {
        gameField[gameMove][i] = currentGuess[i];
    }

    printGameField(game);
    checkAndSafe(game);
    gameMove++;
}


int SolvingAlgorithm::checkRightColors(MasterMind &game) const
{
    const auto &colorCode = game.getColorCode();
    const auto &guess = game.gameField[gameMove];

    std::unordered_map<std::string, int> colorCodeCount, guessCount;

    for (int i = 0; i < 4; i++) {
        colorCodeCount[colorCode[i]]++;
        guessCount[guess[i]]++;
    }

    int count = 0;
    for (const auto &pair: guessCount) {
        count += std::min(pair.second, colorCodeCount[pair.first]);
    }

    std::cout << "common colors: " << count << "\t";
    return count;
}

int SolvingAlgorithm::checkRightPositions(MasterMind &game) const
{
    const auto &colorCode = game.getColorCode();
    const auto &gameField = game.gameField;

    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (gameField[gameMove][i] == colorCode[i]) {
            count++;
        }
    }

    std::cout << "perfect colors: " << count << "\t";
    return count;
}

void SolvingAlgorithm::checkAndSafe(MasterMind &game)
{
    int rightColors = checkRightColors(game);
    int rightPositions = checkRightPositions(game);

    if (rightPositions == 4) {
        solved = true;
    }

    feedBackArray[gameMove][0] = rightColors;
    feedBackArray[gameMove][1] = rightPositions;
}


void SolvingAlgorithm::performNewGuessBasedOnFeedback(MasterMind &game)
{
    if (solved) { return; }


    printGameField(game);
    gameMove++;
}



void SolvingAlgorithm::createEveryPosibility()
{
    for (int i = 0; i < possibilities; i++) {
        int code = i;
        for (int j = 3; j >= 0; --j) {
            possibleCodes[i][j] = code % 6;
            code /= 6;
        }
    }
}


void SolvingAlgorithm::printGameField(MasterMind &game) const
{
    auto gameField = game.gameField;
    std::cout << std::endl;
    for (int j = 0; j < 4; j++) {
        std::cout << "\t" << gameField[gameMove][j];
    }
    std::cout << "\t" << gameMove << "\t";
}

