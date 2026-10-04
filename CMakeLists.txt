cmake_minimum_required(VERSION 3.15)
project(blunder-engine LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)


# Define executable
add_executable(ai-play
    src/main.cpp
    src/Print.cpp
)

target_include_directories(ai-play PRIVATE include)