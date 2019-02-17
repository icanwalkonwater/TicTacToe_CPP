cmake_minimum_required(VERSION 3.13)

set(GAME_SRCS
        main.cpp
        renderer.cpp)

set(GAME_SRCS_HEADER
        renderer.h)

add_executable(tictactoe ${GAME_SRCS} ${GAME_SRCS_HEADER})
set_target_properties(tictactoe PROPERTIES OUTPUT_NAME "tictactoe")
target_link_libraries(tictactoe PUBLIC libtictactoe)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_library(tictactoe_debug STATIC ${GAME_SRCS} ${GAME_SRCS_HEADER})