cmake_minimum_required(VERSION 3.13)
project(TicTacToe CXX)
set(CMAKE_CXX_STANDARD 17)

# Version number in TicTacToeConfig header file
set(TicTacToe_VERSION_MAJOR 1)
set(TicTacToe_VERSION_MINOR 0)
set(TicTacToe_VERSION_BUILD 0)
configure_file(
        "${PROJECT_SOURCE_DIR}/TicTacToeConfig.h.in"
        "${PROJECT_BINARY_DIR}/TicTacToeConfig.h"
)

add_subdirectory(libtictactoe)
add_subdirectory(game)
add_subdirectory(test)
