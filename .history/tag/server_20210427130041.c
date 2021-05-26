// 鬼ごっこゲームのサーバプログラム

#include "session.h"
#include "tag.h"

int main(void)
{
    int soc; // ソケットのディスクリプタ

    // 接続受付まで
    if (soc = setup_server(PORT)) == -1) {
        exit(1);
    }
}