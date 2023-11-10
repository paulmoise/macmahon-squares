cmake_minimum_required(VERSION 3.25)
project(macmahon_squares)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(macmahon_squares
        board.cpp
        board.hpp
        helper.cpp
        helper.hpp
        piece.cpp
        piece.hpp
        main.cpp
        puzzlegame.cpp
        puzzlegame.hpp
        puzzlegame.hpp)
