cmake_minimum_required(VERSION 3.10)

project(chess-engine C)

add_executable(${PROJECT_NAME}
    src/main.c
    src/common.h
    src/fen.c
    src/fen.h
    src/valid_move.c
    src/valid_move.h
)