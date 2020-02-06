cmake_minimum_required(VERSION 3.14)
## Giving a name to the project
project(weird_golf_game)

## Including headers, from both the current project and from the imported libraries
include_directories(include)
include_directories(submodules/spdlog)
include_directories(submodules/enet/include)

## I want to use the C++17 standard, forsooth!
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(submodules/spdlog)
add_subdirectory(submodules/enet)

add_executable(weird_golf_game
	src/Main.cpp
	src/Logger/Logger.cpp
	src/Logger/FileLogger.cpp
	src/AI/State.cpp
	src/AI/StateTransition.cpp
	src/AI/StateMachine.cpp
	src/AI/PushdownState.cpp
	src/AI/PushdownMachine.cpp
	src/Network/GameServer.cpp
	src/Network/GameClient.cpp
	src/Network/NetworkBase.cpp
	include/Logger/Logger.h
	include/Logger/FileLogger.h
	include/AI/State.h
	include/AI/StateTransition.h
	include/AI/StateMachine.h
	include/AI/PushdownState.h
	include/AI/PushdownMachine.h
	include/Network/GameServer.h
	include/Network/NetworkBase.h
	include/Network/GameClient.h)
target_link_libraries(weird_golf_game spdlog::spdlog enet)
