cmake_minimum_required(VERSION 3.28)
project(Mastermind)

set(CMAKE_CXX_STANDARD 23)

add_executable(Mastermind main.cpp
        src/Core/MasterMind.cpp
        src/Core/MasterMind.h
        src/Utility/RandomNumberGenerator.cpp
        src/Utility/RandomNumberGenerator.h
        src/Core/SolvingAlgorithm.cpp
        src/Core/SolvingAlgorithm.h
)
