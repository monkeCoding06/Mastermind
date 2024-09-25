#include "src/Core/MasterMind.h"
#include "src/Core/SolvingAlgorithm.h"

int main()
{
    MasterMind masterMind; // Create MasterMind instance
    SolvingAlgorithm solvingAlgorithm(masterMind); // Pass MasterMind instance to SolvingAlgorithm

    // Call methods to solve the game
    solvingAlgorithm.makeFirstGuess(masterMind); // Make the first guess
    int i = 0;
    while(i <= 12 ){
        solvingAlgorithm.performNewGuessBasedOnFeedback(masterMind); // Perform the algorithm based on feedback
        i++;
    }
}
