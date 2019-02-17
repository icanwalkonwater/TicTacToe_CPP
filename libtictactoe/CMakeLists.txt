cmake_minimum_required(VERSION 3.13)

set(LIBTICTACTOE_SRCS
        board.cpp
        board_cell.cpp
        game_logic.cpp)

set(LIBTICTACTOE_SRCS_HEADER
        board.h
        board_cell.h
        game_logic.h)

add_library(libtictactoe STATIC ${LIBTICTACTOE_SRCS} ${LIBTICTACTOE_SRCS_HEADER})
set_target_properties(libtictactoe PROPERTIES OUTPUT_NAME "libtictactoe")

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

install(TARGETS libtictactoe
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES ${LIBTICTACTOE_SRCS_HEADER} DESTINATION include/libtictactoe)
