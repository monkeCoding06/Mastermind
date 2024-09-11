//
// Created by lkohlfuerst on 11/09/2024.
//

#include "SolvingAlgorithm.h"

void SolvingAlgorithm::solve(MasterMind &game)
{
    makeFirstGuess(game);
}

void SolvingAlgorithm::makeFirstGuess(MasterMind &game)
{
    auto colorList = game.getColorList();
    auto gameField = game.gameField;
    for (int i = 0; i < 4; i++) {
        gameField[gameMove][i] = colorList[RandomNumberGenerator::generateRandomNumber(0, 7)];
    }
    gameMove++;
    printGameField(game);
}

void SolvingAlgorithm::printGameField(MasterMind &game)
{
    auto gameField = game.gameField;
    for (int j = 0; j < 4; j++) {
        std::cout << "\t" << gameField[gameMove - 1][j];
    }
    std::cout << "\t" << gameMove << std::endl;
}
