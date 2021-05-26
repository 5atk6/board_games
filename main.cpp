#include <iostream>

using namespace std;
#define WHITE -1
#define BLACK 1

void print_board(int board[9][9])
{
    int x = 9;
    int y = 9;

    cout << " ";
    for (int ix = 0; ix <x; ix++) {
        cout << " " << ix+1;
    }
    cout << endl;
    for (int iy = 0; iy < y; iy++) {
        cout << iy + 1<< " ";
        for (int ix = 0; ix < x; ix++) {
            if (board[iy][ix] == 0) {
                cout << "+";
            } else if (board[iy][ix] == WHITE) {
                cout << "●";
            } else if (board[iy][ix] == BLACK) {
                cout << "◯";
            }
            cout << " ";
        }
        cout << endl;
    }
}

int main()
{
    int board[9][9] = {0};
    int x, y;
    int player = 1;

    while (true) {
        cin >> x >> y;
        if (x == 0 && y == 0) {
            cout << "Terminate this game." << endl;
            break;
        }

        x--;
        y--;
        if (board[y][x] == 0) {
            board[y][x] = player;
            print_board(board);
        } else {
            cout << "Please input other place." << endl;
        }

        player = player * (-1);
    }

    return 0;
}
