#include <sys/types.h>
#include <stdlib.h>
#include <curses.h>
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