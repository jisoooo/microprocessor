#ifndef IMAGE
#define IMAGE
#include <stdio.h>
#include "item.h"
#include "s3c6410.h"
enum background { BLACK_WALL, BLUE_WALL, SEED};
enum color { BLACK = 0x0, BLUE = 0xFF, YELLOW = 0xFFFF00 };
enum state{UP, DOWN, RIGHT, LEFT};

struct player {
	int col;
	int row;
	int state; //direction
	int life;
};

struct enemy {
	int col;
	int row;
	int valid;
	int state; //direction
};



//void draw_one_cell(int row, int col, int color);
void draw_one_block(int row, int col, unsigned int color);
void draw_background();
void draw_seed(int i, int j);
void draw_item(item it);
void draw_player();
void move_player();
int collision_check();
void draw_black();
void draw_background_initial();
void draw_num(int row, int col, int num);
void draw_char(int row, int col, int _char);
void draw_enemy();
#endif
