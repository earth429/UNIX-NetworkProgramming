// 3目並べの後手(サーバ)プログラム

#include "goban.h"

int main(void)
{
    int soc; // ソケットのディスクリプタ
    char my_stone = 'o'; // 自分の石
    char peer_stone = 'x'; // 相手の石

    // 接続受付完了まで
    if ((soc = setup_server(PORT)) == -1) {
        exit(1);
    }

    // 碁盤の初期化
    goban_init(soc, my_stone, peer_stone);

    // ループ
    while(1) {
        // 相手の番
        goban_show();
        printf("Wait.\n");
        if (goban_peer_turn() == -1) {
            break;
        }
        // 自分の番
        goban_show();
        printf("Go ahead.\n");
        if (goban_my_turn() == -1) {
            break;
        }

        // 終了処理
        goban_destroy();
    }
}