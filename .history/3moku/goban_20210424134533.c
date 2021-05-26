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

// 相手の番の処理
int goban_peer_turn() {
    char data[10]; // 受信バッファ
    int x, y; // 座標

    // ソケットから読む
    read(goban_soc, data, 10);

    // 先頭バイトを見て終了か判定
    if (data[0] == 'q') {
        return -1;
    }

    // 座標データの取り出し
    y = (int)data[0] - (int)'a' + 1;
    x = (int)data[1] - (int)'0';

    // データの更新
    goban_plane[y][x] = goban_peer_stone;

    return 1;
}

// 自分の番の処理
int goban_my_turn() {
    char data[10]; // 送信バッファ
    int x, y; // 座標

    // キーボード入力
    while(1) {
        fgets(data, 10, stdin);
        if (data[0] == 'q') {
            write(goban_soc, data, 1);
            return -1;
        }
        if (data[0] < 'a' || data[0] > 'c' || data[1] < '1' || data[1] > '3') {
            continue;
        }
        break;
    }

    // データの更新
    y = (int)data[0] - (int)'a' + 1;
    x = (int)data[1] - (int)'0';
    goban_plane[y][x] = goban_my_stone;

    // 送信
    write(goban_soc, data, 10);

    return 1;
}

// 終了処理
void goban_destroy() {
    close(goban_soc);
}