cmake_minimum_required(VERSION 3.17)
project(othelloAssignment C)

set(CMAKE_C_STANDARD 11)

add_executable(othelloAssignment game.c game.h functions.c)