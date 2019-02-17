//
// Created by lucas on 2/6/19.
//

#ifndef TICTACTOE_GAMELOGIC_H
#define TICTACTOE_GAMELOGIC_H


#include <stdint-gcc.h>
#include "board.h"

using namespace tictactoe::model;

namespace tictactoe::logic {

    class GameLogic {
    private:
        struct Direction {
            const signed int dx;
            const signed int dy;
        };

        Board board_;
        unsigned int row_to_win_;
        unsigned int players_;
        unsigned int active_player_index_ = 0;
        unsigned int round_ = 1;

    public:
        explicit GameLogic(unsigned int players = 2,
                           unsigned int board_width = 3,
                           unsigned int board_height = 3,
                           unsigned int row_to_win = 3);


        GameLogic(GameLogic &other) = delete;

        const Board &GetBoard() const noexcept;

        unsigned int GetRowToWin() const noexcept;

        unsigned int GetPlayerAmount() const noexcept;

        unsigned int GetCurrentPlayer() const noexcept;

        /**
         * @return Get the current round number.
         */
        unsigned int GetRound() const noexcept;

        /**
         * Used to check wether the input can actually be processed.
         * @param x - Column of the cell to check
         * @param y - Line of the cell to check
         * @return True if the cell is empty, otherwise false
         */
        bool ValidateInput(unsigned int x, unsigned int y) const noexcept;

        /**
         * Perform a round of the game for the active player.
         * It assumes that #validateInput() has been called with the same values just before.
         * @param x - Column of the cell to claim.
         * @param y - Line of the cell to claim.
         * @return True if the current player has won the game, otherwise false.
         */
        bool PerformRound(unsigned int x, unsigned int y) noexcept;

        /**
         * Check if the active player has won.
         * Automatically called by PerformRound().
         * @param x - Column of the last played cell.
         * @param y - Line of the last played cell.
         * @return True if the player has won.
         */
        bool CheckVictory(unsigned int x, unsigned int y) const noexcept;

        /**
         * Explore one direction of the board and count the cells that belongs to the current player.
         * @param direction - The direction to procede in.
         * @param x         - The x coordinate of the cell to explore.
         * @param y         - The y coordinate of the cell to explore.
         * @return The length of the path of claimed cell from the current player.
         */
        unsigned int ExploreDirection(Direction direction,
                                      unsigned int x,
                                      unsigned int y) const noexcept;
    };
}

#endif //TICTACTOE_GAMELOGIC_H
