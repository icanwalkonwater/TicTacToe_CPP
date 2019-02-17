#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
//
// Created by lucas on 2/16/19.
//

#include <criterion/criterion.h>
#include <iostream>
#include "../libtictactoe/board.h"
#include "../libtictactoe/board.cpp"

using namespace tictactoe::model;

Test(lib_board, board_default) {
    Board board;

    cr_expect_eq(board.GetWidth(), 3, "Unexpected width");
    cr_expect_eq(board.GetHeight(), 3, "Unexpected height");

    for (unsigned char i = 0; i < 3; ++i) {
        for (unsigned char j = 0; j < 3; ++j) {
            BoardCell *cell = board.GetCell(i, j);
            cr_assert(cell->IsEmpty(), "Cell is not empty !");
        }
    }
}

Test(lib_board, board_5x7) {
    Board board(5, 7);

    cr_expect_eq(board.GetWidth(), 5, "Unexpected width");
    cr_expect_eq(board.GetHeight(), 7, "Unexpected height");
}

Test(lib_board, board_access) {
    Board board;

    cr_expect_none_throw(board.GetCell(0, 0), "Unexpected exception");
    cr_expect_none_throw(board.GetCell(2, 2), "Unexpected exception");
    cr_expect_any_throw(board.GetCell(-1, 0), "What the frick");
    cr_expect_any_throw(board.GetCell(1, 3), "Expected OFB, got nothing");
    cr_expect_any_throw(board.GetCell(1, 100), "This is getting scary");
}

Test(lib_board, board_cell) {
    BoardCell cell;

    cr_assert_eq(cell.GetOwner(), BoardCell::EMPTY, "The cell is not empty by default");
    cr_assert(cell.IsEmpty(), "It's not empty");

    cr_assert(cell.Claim(1), "Can't claim an empty cell");
    cr_assert_not(cell.Claim(1), "Can claim a claimed cell");
    cr_assert_eq(cell.GetOwner(), 1, "Wrong owner");
}

#pragma clang diagnostic push