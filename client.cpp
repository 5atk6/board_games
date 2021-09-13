#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <iostream>

int
main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cout << "Please run a client like this." << std::endl;
        std::cout << "./client 3 7" << std::endl;
        return 1;
    }

    // ソケット作成
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("socket");
        return 1;
    }

    // struct sockaddr_un 作成
    struct sockaddr_un sa = {0};
    sa.sun_family = AF_UNIX;
    strcpy(sa.sun_path, "/tmp/unix-domain-socket");

    // 接続
    if (connect(sock, (struct sockaddr*) &sa, sizeof(struct sockaddr_un)) == -1)
    {
        perror("connect");
        close(sock);
    }

    // 送信
    char message[32];
    message[0] = *argv[1];
    message[1] = *argv[2];
    if (write(sock, message, strlen(message)) == -1)
    {
        perror("write");
        close(sock);
    }

    // Get result
    char buffer[32];
    memset(buffer, 0, sizeof(buffer));
    int recv_size = read(sock, buffer, sizeof(buffer)-1);
    if (recv_size == -1) {
        perror("read");
        close(sock);
    }
    std::cout << buffer << std::endl;

    // クローズ
    close(sock);
    return 0;
}
