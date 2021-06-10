cmake_minimum_required(VERSION 3.17)
project(Game)

set(CMAKE_CXX_STANDARD 11)

add_executable(Game
        gameTest.cpp
        Character.cpp Character.h
        Soldier.cpp Soldier.h
        Auxiliaries.cpp Auxiliaries.h Game.cpp Game.h Sniper.cpp Sniper.h Medic.cpp Medic.h board.cpp board.h)