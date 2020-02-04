cmake_minimum_required(VERSION 3.14)
## Giving a name to the project
project(weird_golf_game)

## Including headers, from both the current project and from the imported libraries
include_directories(include)
include_directories(submodules/spdlog)

## I want to use the C++17 standard, forsooth!
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(submodules/spdlog)

add_executable(weird_golf_game src/Main.cpp src/Logger.cpp src/FileLogger.cpp include/Logger.h include/FileLogger.h)
target_link_libraries(weird_golf_game spdlog::spdlog)
