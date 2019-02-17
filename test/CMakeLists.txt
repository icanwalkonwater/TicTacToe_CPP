cmake_minimum_required(VERSION 3.13)

set(TEST_TICTACTOE_SRCS
        board_test.cpp
        logic_test.cpp
        render_test.cpp)

add_executable(tictactoe_test ${TEST_TICTACTOE_SRCS})
target_link_libraries(tictactoe_test PUBLIC libtictactoe)
target_link_libraries(tictactoe_test PUBLIC criterion)
target_link_libraries(tictactoe_test PUBLIC tictactoe_debug)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/test)