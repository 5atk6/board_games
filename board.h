#ifndef BOARD_H
#define BOARD_H

#define WHITE -1
#define BLACK 1
#define WIN 1

using namespace std;

void print_board(int board[9][9]);
int check_board(int x, int y, int board[9][9]);

#endif
