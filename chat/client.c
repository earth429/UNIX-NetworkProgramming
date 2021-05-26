#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT (in_port_t)50000 // サーバ(相手)のポート番号
#define BUF_LEN 512 // 送受信のバッファの大きさ

int main()
{
    // 変数宣言
    struct hostent *server_ent; // サーバの情報
    struct sockaddr_in server; // サーバのアドレス
    int soc; // ソケットのディスクリプタ
    char hostname[] = "localhost"; // サーバのホスト名
    char buf[BUF_LEN]; // 送受信のバッファ

    // サーバのホスト名からアドレス情報を得る
    if((server_ent = gethostbyname(hostname)) == NULL) {
        perror("gethostbyname");
        exit(1);
    }

    // サーバのアドレスを sockaddr_in 構造体に格納
    memset((char *)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    memcpy((char *)&server.sin_addr, server_ent->h_addr, server_ent->h_length);

    // IPv4でストリーム型のソケットを作成
    if((soc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    // サーバに接続
    if(connect(soc, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("connect");
        exit(1);
    }

    // 相手が先
    write(1, "Wait\n", 5);

    // 送信のループ
    do {
        int n; // 読み込まれたバイト数
        n = read(soc, buf, BUF_LEN); // ソケットsocから読む
        write(1, buf, n); // 標準出力1に書き出す
        n = read(0, buf, BUF_LEN); // 標準入力0から読む
        write(soc, buf, n); // ソケットsocに書き出す
    } while (strncmp(buf, "quit", 4) != 0); // 終了判定
    
    // ソケットを閉じる
    close(soc);
}