cmake_minimum_required(VERSION 3.17)
project(Game)

set(CMAKE_CXX_STANDARD 11)

add_executable(Game
        gameTest.cpp
        Auxiliaries.cpp Auxiliaries.h
        Character.cpp Character.h
        Soldier.cpp Soldier.h
        Sniper.cpp Sniper.h
        Medic.cpp Medic.h
        Game.cpp Game.h
        board.cpp board.h
        Exceptions.cpp Exceptions.h)