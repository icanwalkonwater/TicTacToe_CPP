//
// Created by lucas on 2/3/19.
//

#include <iostream>
#include "board.h"
#include "../game/renderer.h"

using namespace tictactoe::model;


Board::Board(const unsigned int board_width, const unsigned int board_height) noexcept
        : width_(board_width), height_(board_height),
          cells_(std::make_unique<std::vector<BoardCell>>(board_height * board_width, BoardCell())) {
}

Board::Board(Board &other) noexcept {
    height_ = other.height_;
    width_ = other.width_;
    cells_ = std::move(other.cells_);
}

unsigned int Board::GetWidth() const noexcept {
    return width_;
}

unsigned int Board::GetHeight() const noexcept {
    return height_;
}

BoardCell *Board::GetCell(unsigned int x, unsigned int y) const {
    if (x >= width_ || y >= height_)
        throw std::out_of_range("Invalid cell coordinates");

    return &(*cells_)[x * width_ + y];
}
