
#include <unordered_map>
#include "SolvingAlgorithm.h"

void SolvingAlgorithm::solve(MasterMind &game)
{
    if (gameMove == 1) {
        makeFirstGuess(game);
    }

    makeFirstGuess(game);
    if (!solved && gameMove < 12) {
        solve(game);
    }
}

void SolvingAlgorithm::makeFirstGuess(MasterMind &game)
{
    gameMove++;
    auto colorList = game.getColorList();
    auto gameField = game.gameField;
    for (int i = 0; i < 4; i++) {
        currentGuess[i] = colorList[RandomNumberGenerator::generateRandomNumber(0, 7)];
        gameField[gameMove - 1][i] = currentGuess[i];
    }


    printGameField(game);
    checkRightColors(game);
    checkRightPositions(game);
}

void SolvingAlgorithm::printGameField(MasterMind &game)
{
    auto gameField = game.gameField;
    std::cout << std::endl;
    for (int j = 0; j < 4; j++) {
        std::cout << "\t" << gameField[gameMove - 1][j];
    }
    std::cout << "\t" << gameMove << "\t";
}

int SolvingAlgorithm::checkRightColors(MasterMind &game)
{
    std::string *colorCode = game.getColorCode();
    auto gameField = game.gameField;

    std::unordered_map<std::string, int> colorCodeCount, guessCount;
    for (int i = 0; i < 4; i++) {
        colorCodeCount[colorCode[i]]++;
        guessCount[currentGuess[i]]++;
    }

    int count = 0;
    for (const auto &pair: guessCount) {
        count += std::min(pair.second, colorCodeCount[pair.first]);
    }

    std::cout << "common colors: " << count << "\t";
    return count;
}

int SolvingAlgorithm::checkRightPositions(MasterMind &game)
{
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (currentGuess[i] == game.getColorCode()[i]) {
            count++;
        }
    }

    std::cout << "perfect colors: " << count << "\t";

    return count;
}

void SolvingAlgorithm::checkAndSafe(MasterMind &game)
{


}