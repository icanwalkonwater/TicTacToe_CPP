//
// Created by lucas on 2/17/19.
//

#include <criterion/criterion.h>
#include <iostream>
#include "../libtictactoe/board.h"
#include "../game/renderer.h"

using namespace tictactoe::model;
using namespace tictactoe::render;

/*Test(render, render_board_empty) {
    Board board;

    cr_log_info("Board empty 3x3");

    Renderer::PrintBoard(std::cout, board);
    std::flush(std::cout);
}*/

Test(render, render_board_fill) {
    Board board;

    board.GetCell(0, 0)->Claim(1);
    board.GetCell(1, 1)->Claim(1);
    board.GetCell(2, 1)->Claim(2);

    //cr_log_info("Board filled 3x3");

    Renderer::PrintBoard(std::cout, board);
    //std::flush(std::cout);
}

/*Test(render, render_board_unknown) {
    Board board;

    board.GetCell(0, 0).Claim(1);
    board.GetCell(1, 1).Claim(1);
    board.GetCell(2, 1).Claim(3);
    board.GetCell(2, 2).Claim(0);

    cr_log_info("Board filled unknown 3x3");

    Renderer::PrintBoard(std::cout, board);
    std::flush(std::cout);
}*/

/*Test(render, render_board_big) {
    Board board(10, 10);

    cr_log_info("Board empty 10x10");

    Renderer::PrintBoard(std::cout, board);
    std::flush(std::cout);
}*/
