#include <sys/types.h>
#include <stdlib.h>
#include <ncurses.h>
#include <signal.h>

#define BUF_LEN 20
#define MIN_X 1
#define MIN_Y 1
#define MAX_X 60
#define MAX_Y 20

// 移動キーの割り当て
#define NORTH 'k'
#define SOUTH 'j'
#define EAST 'l'
#define WEST 'h'
#define QUIT 'q'

// プライベート変数
static int session_soc; // socket
static fd_set mask; // fd mask
static int width; // width of the mask
static char my_char, peer_char; // character

typedef struct {
    int x, y; // current position
    char look; // character
} PLAYER;

static PLAYER me, peer; // 自分と相手の情報を保持する変数

static char buf[BUF_LEN]; // 送受信兼用バッファ

staic WINDOW *win; // 表示用ウィンドウ

// sessionモジュールにプライベートな関数
static void hide(PLAYER *who);
static void show(PLAYER *who);
static int update(PLAYER *who, int c);
static int interpret(PLAYER *who);
static void die();

// sessionモジュールの初期化
// soc: ソケットのディスクリプタ
// mc: 自分の表示用の文字, mx: 自分の初期x座標, my: 自分の初期y座標
// pc: 相手の表示用の文字, px: 相手の初期x座標, py: 相手の初期y座標
void session_init(int soc, char mc, int mx, int my, char pc, int px, int py) {
    // 初期データの設定
    session_soc = soc;
    width = soc + 1;
    FD_ZERO(&mask);
    FD_SET(0, &mask);
    FD_SET(session_soc, &mask);
    me.look = mc;
    peer.look = pc;
    me.x = mx;
    peer.x = px;
    me.y = my;
    peer.y = py;

    // cursesの初期化
    initscr();
    signal(SIGINT, die);

    // ウィンドウ枠
    win = newwin(MAX_Y + 2, MAX_X + 2, 0, 0);
    box(win, '|', '-');

    // 端末設定
    cbreak();
    noecho();
}
