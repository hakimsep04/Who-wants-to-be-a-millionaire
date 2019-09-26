cmake_minimum_required(VERSION 3.9)
project(MillionaireGame)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Weffc++ -pedantic -g")

add_executable(MillionaireGame src/server/server.cpp src/server/game.cpp src/server/game.h src/client/client.cpp)