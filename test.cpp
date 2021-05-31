#include <gtest/gtest.h>

#include "board.h"

TEST(check_board_test, case01) {
    int board[9][9] = {0};
    board[0][0] = 1;
    board[0][1] = 1;
    board[0][2] = 1;
    board[0][3] = 1;
    board[0][4] = 1;
    for (int i = 0; i <= 4; i++) {
        EXPECT_EQ(check_board(0, i, board), 1);
    }
}

TEST(check_board_test, case02) {
    int board[9][9] = {0};
    board[0][0] = 1;
    board[1][0] = 1;
    board[2][0] = 1;
    board[3][0] = 1;
    board[4][0] = 1;
    for (int i = 0; i <= 4; i++) {
        EXPECT_EQ(check_board(i, 0, board), 1);
    }
}

TEST(check_board_test, case03) {
    int board[9][9] = {0};
    board[0][0] = 1;
    board[1][1] = 1;
    board[2][2] = 1;
    board[3][3] = 1;
    board[4][4] = 1;
    for (int i = 0; i <= 4; i++) {
        EXPECT_EQ(check_board(i, i, board), 1);
    }
}

TEST(check_board_test, case04) {
    int board[9][9] = {0};
    board[0][4] = 1;
    board[1][3] = 1;
    board[2][2] = 1;
    board[3][1] = 1;
    board[4][0] = 1;
    for (int i = 0; i <= 4; i++) {
        EXPECT_EQ(check_board(i, 4-i, board), 1);
    }
}
