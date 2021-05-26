#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT (in_port_t)50000 // サーバ(自分)のポート番号
#define BUF_LEN 512 // 送受信のバッファの大きさ

int main()
{
    // 変数宣言
    struct sockaddr_in me; // サーバの情報
    int soc_waiting; // listenするソケット
    int soc; //送受信に使うソケット
    char buf[BUF_LEN]; // 送受信のバッファ

    // サーバのアドレスを sockaddr_in 構造体に格納
    memset((char *)&me, 0, sizeof(me));
    me.sin_family = AF_INET;
    me.sin_addr.s_addr = htonl(INADDR_ANY);
    me.sin_port = htons(PORT);

    // IPv4でストリーム型のソケットを作成
    if((soc_waiting = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    // サーバのアドレスをソケットに設定
    if(bind(soc_waiting, (struct sockaddr *)&me, sizeof(me)) == -1) {
        perror("bind");
        exit(1);
    }

    // ソケットで待ち受けることを設定
    listen(soc_waiting, 1);

    // 接続要求が来るまでブロックする
    soc = accept(soc_waiting, NULL, NULL);

    // 接続待ちのためのソケットを閉じる
    close(soc_waiting);

    // こちらから先
    write(1, "Go ahead!\n", 10);

    // 送信のループ
    do {
        int n; // 読み込まれたバイト数
        n = read(0, buf, BUF_LEN); // 標準入力0から読む
        write(soc, buf, n); // ソケットsocに書き出す
        n = read(soc, buf, BUF_LEN); // ソケットsocから読む
        write(1, buf, n); // 標準出力1に書き出す
    } while (strncmp(buf, "quit", 4) != 0); // 終了判定
    
    // ソケットを閉じる
    close(soc);
}