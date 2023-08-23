cmake_minimum_required(VERSION 3.10)

project(chess-engine C)

add_executable(${PROJECT_NAME}
    src/main.c
    src/common.h
    src/fen.c
    src/fen.h
    src/move.c
    src/move.h
)