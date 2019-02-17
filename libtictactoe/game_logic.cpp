//
// Created by lucas on 2/6/19.
//

#include <iostream>
#include "game_logic.h"

using namespace tictactoe::logic;

GameLogic::GameLogic(const unsigned int players, const unsigned int board_width, const unsigned int board_height,
                     const unsigned int row_to_win)
        : row_to_win_(row_to_win), players_(players), board_(board_width, board_height) {
    if (row_to_win > std::max(board_width, board_height))
        throw std::invalid_argument("row_to_win is too large for the board");
}

const Board &GameLogic::GetBoard() const noexcept {
    return board_;
}

unsigned int GameLogic::GetRowToWin() const noexcept {
    return row_to_win_;
}

unsigned int GameLogic::GetPlayerAmount() const noexcept {
    return players_;
}

unsigned int GameLogic::GetCurrentPlayer() const noexcept {
    return static_cast<unsigned int>(active_player_index_ + 1);
}

unsigned int GameLogic::GetRound() const noexcept {
    return round_;
}

bool GameLogic::ValidateInput(const unsigned int x, const unsigned int y) const noexcept {
    try {
        return board_.GetCell(x, y)->IsEmpty();
    } catch (const std::out_of_range &e) {
        return false;
    }
}

bool GameLogic::PerformRound(const unsigned int x, const unsigned int y) noexcept {
    BoardCell *cell = board_.GetCell(x, y);
    cell->Claim(GetCurrentPlayer());

    // Check victory and abort round if victory
    if (round_ >= row_to_win_ - 1 && CheckVictory(x, y)) {
        return true;
    }

    // Increment active player and round
    ++active_player_index_;
    if (active_player_index_ == players_) {
        ++round_;
        active_player_index_ = 0;
    }

    return false;
}

bool GameLogic::CheckVictory(const unsigned int x, const unsigned int y) const noexcept {
    // Check horizontal
    unsigned int count_horizontal = ExploreDirection({-1, 0}, x - 1, y)
                                    + ExploreDirection({1, 0}, x + 1, y);
    // Increment because we count the last cell.
    if (++count_horizontal >= row_to_win_)
        return true;

    // Check vertical
    unsigned int count_vertical = ExploreDirection({0, -1}, x, y - 1)
                                  + ExploreDirection({0, 1}, x, y + 1);
    if (++count_vertical >= row_to_win_)
        return true;

    // Check normal diagonal
    unsigned int count_normal_diagonal = ExploreDirection({-1, -1}, x - 1, y - 1)
                                         + ExploreDirection({1, 1}, x + 1, y + 1);
    if (++count_normal_diagonal >= row_to_win_)
        return true;

    // Check inverse diagonal
    unsigned int count_inverse_diagonal = ExploreDirection({-1, 1}, x - 1, y + 1)
                                          + ExploreDirection({1, -1}, x + 1, y - 1);
    return ++count_inverse_diagonal >= row_to_win_;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

unsigned int GameLogic::ExploreDirection(const Direction direction,
                                         const unsigned int x,
                                         const unsigned int y) const noexcept {
    try {
        // Get the next cell in that direction.
        if (board_.GetCell(x, y)->GetOwner() != GetCurrentPlayer())
            // If not from the current player, stop here the recursion.
            return 0;
        else
            // This cell belongs to the player, continue the recursion with the next cell.
            return ExploreDirection(direction, x + direction.dx, y + direction.dy) + 1;

    } catch (std::out_of_range &e) {
        // The cell was out of the board, stop the recursion.
        return 0;
    }
}

#pragma clang diagnostic pop
