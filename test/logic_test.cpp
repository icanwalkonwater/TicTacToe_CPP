#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
//
// Created by lucas on 2/17/19.
//

#include <criterion/criterion.h>
#include <iostream>
#include "../libtictactoe/game_logic.h"
#include "../game/renderer.h"

using namespace tictactoe::logic;
using namespace tictactoe::render;

Test(lib_logic, logic_default) {
    GameLogic logic;

    cr_expect_eq(logic.GetPlayerAmount(), 2, "Wrong default player count");
    cr_expect_eq(logic.GetBoard().GetWidth(), 3, "Wrong default width");
    cr_expect_eq(logic.GetBoard().GetHeight(), 3, "Wrong default height");
    cr_expect_eq(logic.GetRowToWin(), 3, "Wrong default row_to_win");
}

Test(lib_logic, logic_3_5x7_4) {
    GameLogic logic(3, 5, 7, 4);

    cr_expect_eq(logic.GetPlayerAmount(), 3, "Wrong player count");
    cr_expect_eq(logic.GetBoard().GetWidth(), 5, "Wrong width");
    cr_expect_eq(logic.GetBoard().GetHeight(), 7, "Wrong height");
    cr_expect_eq(logic.GetRowToWin(), 4, "Wrong row_to_win");
}

Test(lib_logic, logic_startup) {
    GameLogic logic;

    cr_assert_eq(logic.GetCurrentPlayer(), 1, "First player is not player 1");
}

Test(lib_logic, logic_explore_simple) {
    GameLogic logic;

    cr_assert_eq(logic.GetCurrentPlayer(), 1, "Current player is not #1, can't test");

    cr_assert_eq(logic.ExploreDirection({1, 0}, 1, 1), 0, "Exploration went wrong 0");

    logic.GetBoard().GetCell(1, 1)->Claim(1);
    cr_assert(logic.GetBoard().GetCell(1, 1)->GetOwner() == 1);
    cr_assert_eq(logic.ExploreDirection({1, 0}, 1, 1), 1, "Exploration went wrong 1");

    logic.GetBoard().GetCell(2, 1)->Claim(1);
    cr_assert(logic.GetBoard().GetCell(2, 1)->GetOwner() == 1);
    cr_assert_eq(logic.ExploreDirection({1, 0}, 1, 1), 2, "Exploration went wrong 2.1");
    cr_assert_eq(logic.ExploreDirection({-1, 0}, 1, 1), 1, "Exploration went wrong 2.2");

    logic.GetBoard().GetCell(0, 1)->Claim(1);
    cr_assert(logic.GetBoard().GetCell(0, 1)->GetOwner() == 1);
    cr_assert_eq(logic.ExploreDirection({1, 0}, 1, 1), 2, "Exploration went wrong 3");
}

Test(lib_logic, logic_explore_multiple) {
    GameLogic logic;

    /* Layout
     *
     *  xxx
     *  -xy
     *  --x
     */

    // Already tested in another test
    logic.GetBoard().GetCell(0, 0)->Claim(1);
    logic.GetBoard().GetCell(1, 0)->Claim(1);
    logic.GetBoard().GetCell(2, 0)->Claim(1);

    logic.GetBoard().GetCell(1, 1)->Claim(1);
    logic.GetBoard().GetCell(2, 2)->Claim(1);

    logic.GetBoard().GetCell(2, 1)->Claim(2);

    cr_expect_eq(logic.ExploreDirection({1, 0}, 0, 0), 3, "Exploration 3 cells wrong");
    cr_expect_eq(logic.ExploreDirection({1, 1}, 0, 0), 3, "Exploration 3 cells diag wrong");
    cr_expect_eq(logic.ExploreDirection({-1, 0}, 2, 0), 3, "Exploration 3 cells backward wrong");
    cr_expect_eq(logic.ExploreDirection({-1, -1}, 2, 2), 3, "Exploration 3 cells diag backward wrong");

    cr_expect_eq(logic.ExploreDirection({-1, 0}, 0, 0), 1, "Exploration out of bound wrong");
    cr_expect_eq(logic.ExploreDirection({-1, 1}, 0, 2), 0, "Exploration empty corner wrong");
    cr_expect_eq(logic.ExploreDirection({1, 1}, -5, 7), 0, "Exploration out of board wrong");
    cr_expect_eq(logic.ExploreDirection({1, 0}, 1, 1), 1, "Exploration player 2 wrong");
}

Test(lib_logic, logic_explore_complex) {
    GameLogic logic(2, 5, 5, 5);

    /*
     * Layout
     *
     * xxxxx
     * xyxyx
     * -xxyx
     * --x--
     * ----x
     */

    for (unsigned char i = 0; i < 5; ++i)
        logic.GetBoard().GetCell(i, 0)->Claim(1);

    logic.GetBoard().GetCell(0, 1)->Claim(1);
    logic.GetBoard().GetCell(1, 1)->Claim(2);
    logic.GetBoard().GetCell(2, 1)->Claim(1);
    logic.GetBoard().GetCell(3, 1)->Claim(2);
    logic.GetBoard().GetCell(4, 1)->Claim(1);

    logic.GetBoard().GetCell(1, 2)->Claim(1);
    logic.GetBoard().GetCell(2, 2)->Claim(1);
    logic.GetBoard().GetCell(3, 2)->Claim(2);
    logic.GetBoard().GetCell(4, 2)->Claim(1);

    logic.GetBoard().GetCell(2, 3)->Claim(1);
    logic.GetBoard().GetCell(4, 4)->Claim(1);

    cr_expect_eq(logic.ExploreDirection({1, 0}, 0, 0), 5, "Line explored wrong");
    cr_expect_eq(logic.ExploreDirection({1, 1}, 0, 0), 1, "Diag p2 explore wrong");
    cr_expect_eq(logic.ExploreDirection({1, 1}, 0, 1), 3, "Diag explore wrong");
    cr_expect_eq(logic.ExploreDirection({1, 0}, 0, 1), 1, "Line multi wrong");
    cr_expect_eq(logic.ExploreDirection({0, 1}, 2, 0), 4, "Line vert explore wrong");
}

Test(lib_logic, logic_victory) {
    GameLogic logic;

    /*
     * Layout
     *
     * x-x
     * xx-
     * --x
     */

    logic.GetBoard().GetCell(0, 0)->Claim(1);
    logic.GetBoard().GetCell(2, 0)->Claim(1);

    logic.GetBoard().GetCell(0, 1)->Claim(1);
    logic.GetBoard().GetCell(1, 1)->Claim(1);

    logic.GetBoard().GetCell(2, 2)->Claim(1);

    cr_expect(logic.CheckVictory(0, 0), "No victory detected 1");
    cr_expect(logic.CheckVictory(1, 1), "No victory detected 2");
    cr_expect(logic.CheckVictory(2, 2), "No victory detected 3");

    cr_expect_not(logic.CheckVictory(2, 0), "Victory detected 1");
    cr_expect_not(logic.CheckVictory(0, 1), "Victory detected 2");

    // Not real victories but works because we trust the given cell.
    cr_expect(logic.CheckVictory(1, 0), "Victory detected 3");
    cr_expect(logic.CheckVictory(0, 2), "Victory detected 4");
}

Test(lib_logic, logic_input) {
    GameLogic logic;

    cr_expect(logic.ValidateInput(0, 0), "Failed validation 1");
    cr_expect(logic.ValidateInput(2, 2), "Failed validation 2");
    cr_expect_not(logic.ValidateInput(3, 0), "Failed validation 3");
    cr_expect_not(logic.ValidateInput(-5, 7), "Failed validation 4");
    cr_expect_not(logic.ValidateInput(1, 7), "Failed validation 5");
}

Test(lib_logic, logic_round) {
    GameLogic logic;

    cr_assert_eq(logic.GetRound(), 1, "Wrong round 1");
    cr_assert_eq(logic.GetCurrentPlayer(), 1, "Wrong first player");
    cr_assert_not(logic.PerformRound(0, 0), "Unexpected win");

    cr_assert_eq(logic.GetRound(), 1, "Wrong round 1");
    cr_assert_eq(logic.GetCurrentPlayer(), 2, "Wrong player playing");
    cr_assert_not(logic.PerformRound(1, 0), "Unexpected win");

    cr_assert_eq(logic.GetRound(), 2, "Wrong round 2");
    cr_assert_eq(logic.GetCurrentPlayer(), 1, "Wrong player turn");
    cr_assert_not(logic.PerformRound(1, 1), "Unexpected win");

    cr_assert_eq(logic.GetRound(), 2, "Wrong round 2");
    cr_assert_eq(logic.GetCurrentPlayer(), 2, "Wrong player turn");
    cr_assert_not(logic.PerformRound(2, 0), "Unexpected win");

    cr_assert_eq(logic.GetRound(), 3, "Wrong round 3");
    cr_assert_eq(logic.GetCurrentPlayer(), 1, "Wrong player turn");
    cr_assert(logic.PerformRound(2, 2), "We must win at this point");
}

#pragma clang diagnostic push