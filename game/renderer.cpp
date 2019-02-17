//
// Created by lucas on 2/3/19.
//

#include <iostream>
#include <sstream>
#include "renderer.h"

using namespace tictactoe::model;
using namespace tictactoe::render;

std::ostream &PrintLine(std::ostream &os, const Board &board, const unsigned char line) {

    os << static_cast<int>(line);

    // Print each col
    // |x
    for (unsigned char col = 0; col < board.GetWidth(); ++col) {
        os << RENDER_VERTICAL << " ";
        switch (board.GetCell(col, line)->GetOwner()) {
            case 1:
                os << ANSI_RED << RENDER_PLAYER_1 << ANSI_RESET;
                break;
            case 2:
                os << ANSI_BLUE << RENDER_PLAYER_2 << ANSI_RESET;
                break;
            default:
                os << RENDER_EMPTY;
                break;
        }
        os << " ";
    }
    os << RENDER_VERTICAL
       << std::endl;

    return os;
}

void Renderer::PrintBoard(std::ostream &os, const Board &board) {
    // Print indexes
    os << " ";
    for (int col = 0; col < board.GetWidth(); ++col) {
        os << "  " << col << " ";
    }
    os << std::endl;

    // Print header
    // +-|-+
    os << " " << RENDER_CORNER_UP_LEFT;
    for (int col = 0; col < board.GetWidth() - 1; ++col)
        os << RENDER_HORIZONTAL << RENDER_SEPARATOR_TOP;
    os << RENDER_HORIZONTAL << RENDER_CORNER_UP_RIGHT
       << std::endl;

    // Print each line block
    // |x| |
    // +-+-+
    for (unsigned char line = 0; line < board.GetHeight() - 1; ++line) {

        // Print each col
        // |x
        PrintLine(os, board, line);

        // Print col footer
        // -+
        os << " " << RENDER_SEPARATOR_LEFT;
        for (int col = 0; col < board.GetWidth() - 1; ++col)
            os << RENDER_HORIZONTAL << RENDER_CROSS;
        os << RENDER_HORIZONTAL << RENDER_SEPARATOR_RIGHT
           << std::endl;
    }

    // Print last line
    PrintLine(os, board, static_cast<const unsigned char>(board.GetHeight() - 1));

    // Print footer
    os << " " << RENDER_CORNER_DOWN_LEFT;
    for (int col = 0; col < board.GetWidth() - 1; ++col)
        os << RENDER_HORIZONTAL << RENDER_SEPARATOR_DOWN;
    os << RENDER_HORIZONTAL << RENDER_CORNER_DOWN_RIGHT
       << std::endl;
}

std::string Renderer::ColorizePlayer(unsigned int player) {
    std::ostringstream oss;
    oss << ANSI_BOLD;

    switch (player) {
        case 1:
            oss << ANSI_RED << 1;
            break;
        case 2:
            oss << ANSI_BLUE << 2;
            break;
        default:
            oss << player;
    }

    oss << ANSI_RESET;

    return oss.str();
}
