#include <iostream>

using namespace std;
#define WHITE -1
#define BLACK 1
#define WIN 1

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

int check_board(int x, int y, int board[9][9])
{
    int periphery[3][3] = {0};
    int ret = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }

            for (int k = 1; k <= 4; k++) {
                int ix = x + i * k;
                int iy = y + j * k;
                if (ix < 0 || ix >= 9 || iy < 0 || iy >= 9) {
                    continue;
                }

                if (board[ix][iy] == board[x][y]) {
                    if (k == 4) {
                        periphery[i+1][j+1] = k;
                    }
                    continue;
                } else {
                    periphery[i+1][j+1] = k - 1;
                    break;
                }
            }
        }
    }

    int a = periphery[0][0] + periphery[2][2];
    int b = periphery[1][0] + periphery[1][2];
    int c = periphery[2][0] + periphery[0][2];
    int d = periphery[0][1] + periphery[2][1];
    if (a >= 4 || b >= 4 || c >= 4 || d >= 4) {
        ret = 1;
    }

    return ret;
}

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
