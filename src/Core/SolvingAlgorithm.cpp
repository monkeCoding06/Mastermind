#include <unordered_map>
#include "SolvingAlgorithm.h"
#include <algorithm>

void SolvingAlgorithm::solve(MasterMind &game) {
    if (gameMove == 0) {
        makeFirstGuess(game);
        createEveryPosibility();
    }

    if (!solved && gameMove <= 11) {
        performNewGuessBasedOnFeedback(game);
        solve(game);
    }
}

void SolvingAlgorithm::makeFirstGuess(MasterMind &game)
{
    auto colorList = game.getColorList();
    auto gameField = game.gameField;

    currentGuess[0] = colorList[0];
    currentGuess[1] = colorList[0];
    currentGuess[2] = colorList[1];
    currentGuess[3] = colorList[1];

    for (int i = 0; i < 4; i++) {
        gameField[gameMove][i] = currentGuess[i];
    }

    printGameField(game);
    checkAndSafe(game);
    resolveFeedBack();
    gameMove++;
}



void SolvingAlgorithm::printGameField(MasterMind &game)
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
    auto colorCode = game.getColorCode();
    auto guess = game.gameField[gameMove];

    std::unordered_map<std::string, int> colorCodeCount;
    std::unordered_map<std::string, int> guessCount;

    for (int i = 0; i < 4; i++) {
        colorCodeCount[colorCode[i]]++;
    }

    for (int i = 0; i < 4; i++) {
        guessCount[guess[i]]++;
    }

    int count = 0;

    for (const auto &pair: guessCount) {
        if (colorCodeCount.find(pair.first) != colorCodeCount.end()) {
            count += std::min(pair.second, colorCodeCount[pair.first]);
        }
    }

    std::cout << "common colors: " << count << "\t";

    return count;
}

int SolvingAlgorithm::checkRightPositions(MasterMind &game) const
{
    int count = 0;
    auto colorCode = game.getColorCode();
    auto gameField = game.gameField;
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

void SolvingAlgorithm::resolveFeedBack()
{
    if (gameMove <= 0) return;

    for (int gameMoveIterator = 0; gameMoveIterator < gameMove; gameMoveIterator++) {
        int rightColors = feedBackArray[gameMoveIterator][0];
        int rightPositions = feedBackArray[gameMoveIterator][1];

        int currentFeedbackScore = rightColors + (rightPositions * 2);

        if (currentFeedbackScore > bestFeedbackScore) {
            bestFeedbackScore = currentFeedbackScore;
            bestFeedbackIndex = gameMoveIterator;
        }
    }
    std::cout << "current best game: " << (bestFeedbackIndex + 1) << std::endl;
}

int getColorIndex(const std::string &color, const std::vector<std::string> &colorList)
{
    auto it = std::find(colorList.begin(), colorList.end(), color);
    if (it != colorList.end()) {
        return std::distance(colorList.begin(), it);
    }
    return -1;
}

void SolvingAlgorithm::performNewGuessBasedOnFeedback(MasterMind &game) {
    bool foundValidGuess = false;
    for (int i = 0; i < possibilities; i++) {
        if (isCodeValid(possibleCodes[i], game)) {
            for (int j = 0; j < 4; j++) {
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
    resolveFeedBack();
    gameMove++;
}

int SolvingAlgorithm::checkRightColorsForCode(int guess[4], int code[4])
{
    std::unordered_map<int, int> codeCount;
    std::unordered_map<int, int> guessCount;

    for (int i = 0; i < 4; i++) {
        codeCount[code[i]]++;
        guessCount[guess[i]]++;
    }

    int count = 0;
    for (const auto &pair: guessCount) {
        if (codeCount.find(pair.first) != codeCount.end()) {
            count += std::min(pair.second, codeCount[pair.first]);
        }
    }
    return count;
}

int SolvingAlgorithm::checkRightPositionsForCode(int guess[4], int code[4])
{
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (guess[i] == code[i]) {
            count++;
        }
    }
    return count;
}

bool SolvingAlgorithm::isCodeValid(int code[4], MasterMind &game)
{
    std::vector<std::string> colorList = game.getColorList();

    for (int prevMove = 0; prevMove < gameMove; prevMove++) {
        int tempGuess[4];
        for (int i = 0; i < 4; i++) {
            tempGuess[i] = getColorIndex(game.gameField[prevMove][i], colorList);
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

void SolvingAlgorithm::createEveryPosibility() {
    for (int i = 0; i < possibilities; i++) {
        int code = i;
        for (int j = 3; j >= 0; j--) {
            possibleCodes[i][j] = code % 6;
            code /= 6;
        }
    }

    for (int i = 0; i < possibilities; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << possibleCodes[i][j] + 1 << " ";
        }
        std::cout << std::endl;
    }
}
