#include <unordered_map>
#include "SolvingAlgorithm.h"
#include <algorithm>

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

    if (gameMove > 11) {
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

    for (int i = 0; i < 4; ++i) {
        gameField[gameMove][i] = currentGuess[i];
    }

    printGameField(game);
    checkAndSafe(game);
    gameMove++;
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

int SolvingAlgorithm::checkRightColors(MasterMind &game) const
{
    const auto &colorCode = game.getColorCode();
    const auto &guess = game.gameField[gameMove];

    std::unordered_map<std::string, int> colorCodeCount, guessCount;

    for (int i = 0; i < 4; ++i) {
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
    for (int i = 0; i < 4; ++i) {
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
    bool foundValidGuess = false;

    for (int i = 0; i < possibilities; i++) {
        if (isCodeValid(possibleCodes[i], game)) {
            for (int j = 0; j < 4; ++j) {
                currentGuess[j] = game.getColorList()[possibleCodes[i][j]];
                game.gameField[gameMove][j] = currentGuess[j];
            }
            foundValidGuess = true;
            break;
        }
    }

    if (!foundValidGuess) {
        std::cerr << "No valid guess found!" << std::endl;
    }

    printGameField(game);
    checkAndSafe(game);
    gameMove++;
}

int SolvingAlgorithm::checkRightColorsForCode(int guess[4], int code[4])
{
    std::unordered_map<int, int> codeCount, guessCount;

    for (int i = 0; i < 4; ++i) {
        codeCount[code[i]]++;
        guessCount[guess[i]]++;
    }

    int count = 0;
    for (const auto &pair: guessCount) {
        count += std::min(pair.second, codeCount[pair.first]);
    }
    return count;
}
int SolvingAlgorithm::checkRightPositionsForCode(int guess[4], int code[4])
{
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        if (guess[i] == code[i]) {
            ++count;
        }
    }
    return count;
}

bool SolvingAlgorithm::isCodeValid(int code[4], MasterMind &game)
{
    const auto &colorList = game.getColorList();

    for (int prevMove = 0; prevMove < gameMove; prevMove++) {
        int tempGuess[4];
        for (int i = 0; i < 4; i++) {
            tempGuess[i] = std::distance(colorList.begin(),
                                         std::find(colorList.begin(), colorList.end(), game.gameField[prevMove][i]));
        }

        int expectedRightColors = feedBackArray[prevMove][0];
        int expectedRightPositions = feedBackArray[prevMove][1];

        int actualRightColors = checkRightColorsForCode(tempGuess, code);
        int actualRightPositions = checkRightPositionsForCode(tempGuess, code);

        if (actualRightColors != expectedRightColors || actualRightPositions != expectedRightPositions) {
            return false;
        }
    }
    return true;
}

void SolvingAlgorithm::createEveryPosibility()
{
    for (int i = 0; i < possibilities; ++i) {
        int code = i;
        for (int j = 3; j >= 0; --j) {
            possibleCodes[i][j] = code % 6;
            code /= 6;
        }
    }
}
