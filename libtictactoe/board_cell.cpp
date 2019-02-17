//
// Created by lucas on 2/3/19.
//

#include <ostream>
#include "board_cell.h"
#include "../game/renderer.h"

using namespace tictactoe::model;

BoardCell::BoardCell() : owner_(EMPTY) {
}

BoardCell::BoardCell(const BoardCell &other) {
    owner_ = other.owner_;
}

unsigned int BoardCell::GetOwner() const noexcept {
    return owner_;
}

bool BoardCell::Claim(unsigned int player) noexcept {
    if (!IsEmpty())
        return false;

    owner_ = player;
    return true;
}

bool BoardCell::IsEmpty() const noexcept {
    return owner_ == EMPTY;
}
