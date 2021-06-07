#include <iostream>
#include "board.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define MODE_INTERACTIVE 1
#define MODE_SERVER      2

int player = BLACK;

int receive_position(int x, int y, int board[9][9])
{
    int ret = 0;
    x--;
    y--;

    if (x < 0 || x >= 9 || y < 0 || y >= 9) {
        cout << "Please input 1 to 9." << endl;
        return ret;
    }

    if (board[x][y] == 0) {
        board[x][y] = player;
        print_board(board);
        ret = check_board(x, y, board);
        if (ret == WIN) {
            cout << player << " wins!" << endl;
            return ret;
        }
    } else {
        cout << "Please input other place." << endl;
        return ret;
    }

    player = player * (-1);
    return ret;
}

int main()
{
    int board[9][9] = {0};
    int x, y;

    cout << "Please type 1 or 2." << endl;
    cout << "1 is interactive mode, 2 is server mode." << endl;
    int mode;
    cin >> mode;

    int sock, ret, fd;
    if (mode == MODE_SERVER) {
        sock = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sock == -1) {
            perror("socket");
        }

        struct sockaddr_un sa = {0};
        sa.sun_family = AF_UNIX;
        strcpy(sa.sun_path, "/tmp/unix-domain-socket");

        remove(sa.sun_path);

        ret = ::bind(sock, (struct sockaddr*) &sa, sizeof(struct sockaddr_un));
        if (ret == -1) {
            perror("bind");
        }

        if (listen(sock, 128) == -1) {
            perror("listen");
        }

        fd = accept(sock, NULL, NULL);
        if (fd == -1) {
            perror("accept");
        }
    }


    while (true) {
        if (mode == MODE_INTERACTIVE) {
            cin >> x >> y;
        } else if (mode == MODE_SERVER) {
            char buffer[32];
            int recv_size = read(fd, buffer, sizeof(buffer)-1);
            if (recv_size == -1) {
                perror("read");
                close(fd);
            }

            buffer[recv_size] = '\0';
            x = buffer[0] - '0';
            y = buffer[1] - '0';

        }

        if(receive_position(x, y, board) == WIN) {
            break;
        }
    }

    cout << "Finish this game." << endl;
    if (close(fd) == -1) {
        perror("close");
    }
    return 0;
}
