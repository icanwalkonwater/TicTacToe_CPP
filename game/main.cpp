#include <iostream>
#include "../libtictactoe/game_logic.h"
#include "renderer.h"

using namespace tictactoe::logic;
using namespace tictactoe::render;

void AskInput(unsigned int *const x, unsigned int *const y) {
    std::cout << "Your play (format: $x $y): ";
    std::cin >> *x;
    std::cin >> *y;
}

int main(int argc, char *argv[]) {

    std::cout << ANSI_BOLD << "Welcome to this shitty tic tac toe !" << std::endl
              << "------------------------------------" << ANSI_RESET << std::endl;

    std::cout << "Choose the size of the board (format: $height $width): ";

    unsigned int height;
    unsigned int width;
    std::cin >> height;
    std::cin >> width;

    GameLogic logic(2, height, width, std::min(height, width));

    std::cout << "Starting game..." << std::endl
              << std::endl;


    unsigned int x;
    unsigned int y;

    do {
        std::cout << "Round: " << ANSI_BOLD << logic.GetRound() << ANSI_RESET
                  << " | Player " << Renderer::ColorizePlayer(logic.GetCurrentPlayer()) << std::endl;
        Renderer::PrintBoard(std::cout, logic.GetBoard());

        do {
            AskInput(&x, &y);
            std::cout << std::endl;
        } while (!logic.ValidateInput(x, y));

    } while (!logic.PerformRound(x, y));

    Renderer::PrintBoard(std::cout, logic.GetBoard());
    std::cout << "Player " << Renderer::ColorizePlayer(logic.GetCurrentPlayer())
              << " has won in " << logic.GetRound() << " round(s) !"
              << std::endl;

    return EXIT_SUCCESS;
}