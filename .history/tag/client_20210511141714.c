// 鬼ごっこゲームのクライアントプログラム

#include "session.h"
#include "tag.h"

int main(void)
{
    int soc; // ソケットのディスクリプタ
    char hostname[HOSTNAME_LENGTH]; // サーバ(相手)のホスト名

    // サーバのホスト名の入力
    printf("input server's hostname: ");
    fgets(hostname, HOSTNAME_LENGTH, stdin);
    chop_newline(hostname, HOSTNAME_LENGTH);

    // 接続まで
    if ((soc = setup_client(hostname, PORT)) == -1) {
        exit(1);
    }

    // セッションモジュールの初期化
    session_init(soc, 'x', 10, 10, 'o', 1, 1);

    // セッションのループ
    session_loop();
}