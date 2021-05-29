#include <iostream>
#include "board.h"

int main()
{
    int board[9][9] = {0};
    int x, y, ret;
    int player = 1;

    while (true) {
        cin >> x >> y;

        if (x == 0 && y == 0) {
            cout << "Terminate this game." << endl;
            break;
        }

        x--;
        y--;

        if (x < 0 || x >= 9 || y < 0 || y >= 9) {
            cout << "Please input 1 to 9." << endl;
            continue;
        }

        if (board[x][y] == 0) {
            board[x][y] = player;
            print_board(board);
            ret = check_board(x, y, board);
            if (ret == WIN) {
                cout << player << " wins!" << endl;
                break;
            }
        } else {
            cout << "Please input other place." << endl;
            continue;
        }

        player = player * (-1);
    }

    return 0;
}
