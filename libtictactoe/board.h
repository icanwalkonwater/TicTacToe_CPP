//
// Created by lucas on 2/3/19.
//

#ifndef TICTACTOE_BOARD_H
#define TICTACTOE_BOARD_H

#include <vector>
#include <ostream>
#include <memory>
#include "board_cell.h"

namespace tictactoe::model {

    class Board {
    private:
        unsigned int width_;
        unsigned int height_;
        std::unique_ptr<std::vector<BoardCell>> cells_;

    public:
        explicit Board(unsigned int board_width = 3, unsigned int board_height = 3) noexcept;

        Board(Board &other) noexcept;

        ~Board() = default;

        unsigned int GetWidth() const noexcept;

        unsigned int GetHeight() const noexcept;

        //
        /**
         * Get the cell at the given position.
         * No bound checks are performed, thus accessing a cell out of bounds will result
         * in undefined behaviour.
         * @param x - The column of the cell to get.
         * @param y - The line of the cell to get.
         * @return The cell that was queried.
         * @throw std::out_of_range When the coordinates are out of range.
         */
        BoardCell *GetCell(unsigned int x, unsigned int y) const;
    };

}

#endif //TICTACTOE_BOARD_H
