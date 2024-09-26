#include "SolvingAlgorithm.h"
#include <iostream>
#include <vector>
#include <string>

SolvingAlgorithm::SolvingAlgorithm(MasterMind &game) {
    auto colors = game.getColorList();
    currentGuess = {colors[0], colors[0], colors[1], colors[1]};
    createPossibilities(game);
}


void SolvingAlgorithm::solve(MasterMind &game) {
    while (!solved) {
        makeFirstGuess(game);
        printGameField(game);

        auto feedback = game.getFeedback(currentGuess);
        int rightColors = feedback.first;
        int rightPositions = feedback.second;

        std::cout << "Feedback - Right colors: " << rightColors
                  << ", Right positions: " << rightPositions << std::endl;

        eliminateImpossibleCodes(currentGuess, rightColors, rightPositions);



        currentGuess = selectNextGuess();

        std::cout << "Remaining possible codes: " << possibleCodes.size() << std::endl;

        if (rightPositions == 4) {
            solved = true;
            std::cout << "Found the correct combination: ";
            for (const auto &color : currentGuess) {
                std::cout << color << " ";
            }
            std::cout << std::endl;
        }



//        std::cout << "Current guess after feedback: ";
//        for (const auto &color : currentGuess) {
//            std::cout << color << " ";
//        }
//        std::cout << std::endl;
    }
}

void SolvingAlgorithm::makeFirstGuess(MasterMind &game) {
//    std::cout << "First guess: ";
    for (int i = 0; i < 4; ++i) {
        std::cout << currentGuess[i] << " ";
    }
    std::cout << std::endl;
    gameMove++;
}

void SolvingAlgorithm::createPossibilities(MasterMind &game) {
    std::vector<std::string> colorList = game.getColorList();
    for (int i = 0; i < 1296; ++i) {
        std::vector<std::string> possibility(4);
        int code = i;
        for (int j = 3; j >= 0; --j) {
            possibility[j] = colorList[code % 6];
            code /= 6;
        }
        possibleCodes.push_back(possibility);
    }
    std::cout << "Total possibilities: " << possibleCodes.size() << std::endl;
}

int SolvingAlgorithm::checkRightPositions(MasterMind &game) {
    int rightPositions = 0;
    for (int i = 0; i < 4; ++i) {
        if (currentGuess[i] == game.getColorCode()[i]) {
            rightPositions++;
        }
    }
    std::cout << "Right positions (correct color and position): " << rightPositions << std::endl;
    return rightPositions;
}

int SolvingAlgorithm::checkRightColors(MasterMind &game) {
    std::vector<std::string> secretCode = game.getColorList();
    std::vector<std::string> guess = { currentGuess[0], currentGuess[1], currentGuess[2], currentGuess[3] };

    int rightColors = 0;
    std::vector<bool> matchedSecret(4, false);
    std::vector<bool> matchedGuess(4, false);

    for (int i = 0; i < 4; ++i) {
        if (guess[i] == secretCode[i]) {
            matchedSecret[i] = true;
            matchedGuess[i] = true;
        }
    }


    for (int i = 0; i < 4; ++i) {
        if (!matchedGuess[i]) {
            for (int j = 0; j < 4; ++j) {
                if (!matchedSecret[j] && guess[i] == secretCode[j]) {
                    rightColors++;
                    matchedSecret[j] = true;
                    break;
                }
            }
        }
    }

    std::cout << "Right colors (correct color, wrong position): " << rightColors << std::endl;
    return rightColors;
}

void SolvingAlgorithm::eliminateImpossibleCodes(const std::vector<std::string>& guess, int rightColors, int rightPositions) {
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
            if (!matchedGuess[i]) {
                for (int j = 0; j < 4; ++j) {
                    if (!matchedCode[j] && possibleCode[i] == guess[j]) {
                        possibleRightColors++;
                        matchedCode[j] = true;
                        break;
                    }
                }
            }
        }

        if (possibleRightColors != rightColors || possibleRightPositions != rightPositions) {
            iterator = possibleCodes.erase(iterator);
        } else {
            ++iterator;
        }
    }
    std::cout << "Remaining possible codes: " << possibleCodes.size() << std::endl;
}

std::vector<std::string> SolvingAlgorithm::selectNextGuess() {
    if (!possibleCodes.empty()) {
        return possibleCodes.front();
    } else {
        std::cout << "No more possible guesses. Something went wrong." << std::endl;
        return {};
    }
}

void SolvingAlgorithm::performNewGuessBasedOnFeedback(MasterMind &game) {
    int rightPositions = checkRightPositions(game);
    int rightColors = checkRightColors(game);

    eliminateImpossibleCodes({ currentGuess[0], currentGuess[1], currentGuess[2], currentGuess[3] }, rightColors, rightPositions);

    if (possibleCodes.empty()) {
        std::cout << "No more possible guesses. Ending the game." << std::endl;
        return;
    }

    std::vector<std::string> nextGuess = selectNextGuess();
    std::copy(nextGuess.begin(), nextGuess.end(), currentGuess.begin());


    std::cout << "Next guess: \t";
    for (int i = 0; i < 4; ++i) {
        std::cout << currentGuess[i] << "\t";
    }
    std::cout << std::endl;
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

