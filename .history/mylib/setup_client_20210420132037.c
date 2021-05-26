#include "mylib.h"

// 戻り値：ソケットのディスクリプタ
// hostname：接続先のホスト名
// port：接続先のポート番号
int setup_client(char *hostname, in_port_t port) {
    // 変数の宣言
    struct hostent *server_ent; // 接続先のホストの情報
    struct sockaddr_in server; // 接続先のソケットのアドレス
    int soc; // 通信に使うソケット

    // 接続先のホスト名からホストの情報を得る
    if ((server_ent = gethostbyname(hostname)) == NULL) {
        perror("gethostbyname");
        return -1;
    }

    // 接続先のアドレスをsockaddr_in構造体に設定
    memset((char *)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

}