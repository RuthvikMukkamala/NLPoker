cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MyProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directory
include_directories(include/core)

# Add the executable
add_executable(MyProject src/main.cpp
                         src/Player.cpp
                         src/Hand.cpp
                         src/GameState.cpp
                         src/Card.cpp
                         src/Deck.cpp
                         src/Evaluator.cpp)
