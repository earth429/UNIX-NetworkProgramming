#include "goban.h"

static char goban_my_stone; // 自分の石
static char goban_peer_stone; // 相手の石

// 碁盤の定義と初期化
static char goban_plane[5][6] = {
    "+123+",
    "a...|",
    "b...|",
    "c...|",
    "+---+"};

static int goban_soc; // ソケットのディスクリプタ

/* 公開される関数群 */

// 碁盤の初期化
// soc: 通信用ソケット
// my_stone: 自分の石
// peer_stone: 相手の石
void goban_init(int soc, char my_stone, char peer_stone) {
    // これらのデータは最後まで保持される
    goban_soc = soc;
    goban_my_stone = my_stone;
    goban_peer_stone = peer_stone;
}

// 碁盤の表示
void goban_show() {
    int i;
    for (i = 0; i < 5; i++) {
        printf("%s\n", goban_plane[i]);
    }
}