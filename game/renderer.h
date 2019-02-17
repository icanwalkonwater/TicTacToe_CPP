//
// Created by lucas on 2/3/19.
//

#ifndef TICTACTOE_RENDERER_H
#define TICTACTOE_RENDERER_H

#define RENDER_EMPTY                " "
#define RENDER_PLAYER_1             "X"
#define RENDER_PLAYER_2             "O"
#define RENDER_HORIZONTAL          "\u2501\u2501\u2501"
#define RENDER_VERTICAL            "\u2503"
#define RENDER_CORNER_UP_LEFT      "\u250f"
#define RENDER_CORNER_UP_RIGHT     "\u2513"
#define RENDER_CORNER_DOWN_LEFT    "\u2517"
#define RENDER_CORNER_DOWN_RIGHT   "\u251b"
#define RENDER_SEPARATOR_TOP       "\u2533"
#define RENDER_SEPARATOR_DOWN      "\u253b"
#define RENDER_SEPARATOR_LEFT      "\u2523"
#define RENDER_SEPARATOR_RIGHT     "\u252b"
#define RENDER_CROSS               "\u254b"

#define ANSI_RESET                 "\033[0m"
#define ANSI_BOLD                  "\033[1m"
#define ANSI_RED                   "\033[31m"
#define ANSI_BLUE                  "\033[34m"
#define ANSI_BRIGHT_GREEN          "\033[32;1m"
#define ANSI_BRIGHT_BLUE           "\033[34;1m"

#include <ostream>
#include "../libtictactoe/board.h"

using namespace tictactoe::model;

namespace tictactoe::render {

    class Renderer {
    public:
        static void PrintBoard(std::ostream &os, const Board &board);

        static std::string ColorizePlayer(unsigned int player);
    };
}

#endif //TICTACTOE_RENDERER_H
