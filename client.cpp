#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <iostream>

int main(void)
{
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
        goto bail;
    }

    // 送信
    char message[32];
    while(true) {
        std::cin >> message[0] >> message[1];
        if (write(sock, message, strlen(message)) == -1)
        {
            perror("write");
            goto bail;
        }
    }

    // クローズ
    close(sock);
    return 0;
 
bail:
    // エラーが発生した場合の処理
    close(sock);
    return 1;
}
