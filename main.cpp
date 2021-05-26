#include <iostream>

using namespace std;

void print_board()
{
    int x = 9;
    int y = 9;

    cout << " ";
    for (int ix = 1; ix <=x; ix++) {
        cout << " " << ix;
    }
    cout << endl;
    for (int iy = 1; iy <= y; iy++) {
        cout << iy << " ";
        for (int ix = 1; ix <= x; ix++) {
            cout << "+ ";
        }
        cout << endl;
    }
}

int main()
{
    print_board();

    return 0;
}
