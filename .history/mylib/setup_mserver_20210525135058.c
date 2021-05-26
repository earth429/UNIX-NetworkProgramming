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
}