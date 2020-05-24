cmake_minimum_required(VERSION 3.15)
project(gameOfLifeFAST C)

set(CMAKE_C_STANDARD 11)

add_executable(gameOfLifeFAST main.c game.c)