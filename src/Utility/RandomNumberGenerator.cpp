//
// Created by lkohlfuerst on 10/09/2024.
//

#include "RandomNumberGenerator.h"
#include <random>

int RandomNumberGenerator::generateRandomNumber(int min, int max)
{
    std::random_device rd;   // Random device for seeding
    std::mt19937 gen(rd());  // Mersenne Twister engine
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}
