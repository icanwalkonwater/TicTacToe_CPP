//
// Created by lucas on 2/3/19.
//

#ifndef TICTACTOE_BOARDCELL_H
#define TICTACTOE_BOARDCELL_H

namespace tictactoe::model {

    class BoardCell {
    private:
        unsigned int owner_;

    public:
        constexpr const static unsigned int EMPTY = 0;

        BoardCell();

        BoardCell(const BoardCell &other);

        ~BoardCell() = default;

        // Getter state.
        unsigned int GetOwner() const noexcept;

        bool IsEmpty() const noexcept;

        // Tries to claim the cell.
        // Return true if the cell has been successfully claimed, otherwise false.
        bool Claim(unsigned int player) noexcept;
    };

}

#endif //TICTACTOE_BOARDCELL_H
