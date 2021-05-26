#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

// 戻り値：待ち受けソケットのディスクリプタ
// port：接続先のポート番号
// backlog：待ち受けの数
int mserver_socket(in_port_t port, int backlog) {
    // 変数の宣言
    struct sockaddr_in me; // 自分のソケットのアドレス
    int soc_waiting; // 待ち受けソケットのディスクリプタ

    // 自分のアドレスをsockaddr_in構造体に設定
    memset((char *)&me, 0, sizeof(me));
    me.sin_family = AF_INET;
    me.sin_addr.s_addr = htonl(INADDR_ANY);
    me.sin_port = htons(port);

    // IPv4でストリーム型のソケットの作成
    if ((soc_waiting = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }

    // ソケットに自分のアドレスを設定
    if (bind(soc_waiting, (struct sockaddr *)&me, sizeof(me)) == -1) {
        perror("bind");
        return -1;
    }

    // ソケットで接続待ちの設定
    if (listen(soc_waiting, backlog) == -1) {
        perror("listen");
        return -1;
    }
    fprintf(stderr, "successfully setup, now waiting...\n");

    // 待ち受け用のディスクリプタを返す
    return soc_waiting;
}


// マルチアクセプト
