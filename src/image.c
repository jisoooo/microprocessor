#include "lcd.h"
#include "image.h"
#include <stdbool.h>

unsigned int *phy_addr = FB_ADDR;

//cell 1개 (800 * 480 의 1칸)
void draw_one_cell(int row, int col, int color) {
	phy_addr[row * 800 + col ] = color;
}

//24 * 24 
void draw_one_block(int row, int col, unsigned int color){
  int i = row*24;
  int j = col*24;

  int p, q;

  for (p = i; p < i + 24; p++) {
	  for (q = j; q < j + 24; q++)
		  draw_one_cell(p, q, color);
  }
}

void draw_background()
{
	int i, j;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 30; j++) {
			switch (map[i][j]) {
			case BLACK_WALL:
				draw_one_block(i, j, BLACK);
				break;
		    case BLUE_WALL:
				draw_one_block(i, j, BLUE);
				break;
			case SEED:
				draw_seed(i, j);
				break;
		   }
		}
	}
}

//seed의 배열을 받아서 있으며 노란색, 없으면 검은색 배경을 띠움
void draw_seed(int i, int j) {
	int p, q;
	draw_one_block(i, j, BLACK);
	if (map[i][j] ==2)
	{
		int col = i * 24;
		int row = j * 24;
		for (p = col + 6; p < col + 12; p++) {
			for (q = row + 6; row + 12; q++);
			draw_one_cell(p, q, YELLOW);
		}
	}
}

//draw player
void draw_player(struct player *p) {
	int color = 0x00FF00;
	draw_one_block(p->row, p->col, color);
}

void move_player(struct player *p, int direction) {

	/*erase previous location*/
	draw_one_block(p->row, p->col, BLACK);

	/*update location*/
	switch (direction) {
		case 0: //left
		{
			if (p->col > 0)
				(p->col)--;
			break;
		}
		case 1: //Right
		{
			if (p->col < 29)
				(p->col)++;
			break;
		}
		case 2: //Up
		{
			if (p->row > 0)
				(p->row)--;
			break;
		}
		case 3: 
		{//Down
			if (p->row < 19)
				(p->row)++;
			break;
		}
	}
	collision_check(p);
	/*draw new location*/
	draw_player(p);
}

int collision_check(struct player *p){//, struct enemy **e) {
	/*take seed*/
	if (map[p->row][p->col] == 2) {
		map[p->row][p->col] = 0;
		/*score update*/
	}
	return 0;
	/*encounter enemy*/
	/*
	int i;
	for (i = 0; i < 3; i++) {
		if ((p->row == e[i]->row) && (p->col == e[i]->col)) {
			if (e[i]->valid == 1) {
				//game over
			}
		}
	}*/
}