#ifndef IMAGE
#define IMAGE
#include <stdio.h>
#include "s3c6410.h"
enum background { BLACK_WALL, BLUE_WALL, SEED};
enum color { BLACK = 0x0, BLUE = 0xFF, YELLOW = 0xFFFF00 };
enum state{UP, DOWN, RIGHT, LEFT};

struct player {
	int col;
	int row;
	int state;
};

struct enemy {
	int col;
	int row;
	int valid;
};



//void draw_one_cell(int row, int col, int color);
void draw_one_block(int row, int col, unsigned int color);
void draw_background();
void draw_seed(int i, int j);
void draw_player(struct player *p);
void move_player(struct player *p, int direction);
int collision_check(struct player *p);
void draw_black();
#endif
