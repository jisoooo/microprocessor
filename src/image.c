#include "lcd.h"
#include "image.h"
#include "itemlist.h"
#include <stdbool.h>

extern int map[20][30];
extern unsigned int pac_up[20][20];
extern unsigned int pac_down[20][20];
extern unsigned int pac_left[20][20];
extern unsigned int pac_right[20][20];

extern unsigned int enemy_red[20][20];
extern unsigned int enemy_purple[20][20];
extern unsigned int enemy_green[20][20];

struct player player={1, 1, DOWN, 3};
struct enemy enemy_Red = {1, 5, 1, DOWN};
struct enemy enemy_Green = {1, 10, 1, DOWN};
struct enemy enemy_Purple = {1, 15, DOWN};

extern item button_Up;
extern item button_Down;
extern item button_Left;
extern item button_Right;
extern item Heart1;
extern item Heart2;
extern item Heart3;


void draw_item(item it){
	int p=0;
  int q=0;
	int i=0;
	int j=0;

 for(i=it.x; i<it.x+it.h;i++){
 	for(j=it.y;j<it.y+it.w; j++){
 		draw_one_cell(i, j, it.data[p*it.w+q]);
 		q++;
 	}
 	q=0;
 	p++;
 }

}
void draw_one_block(int row, int col, unsigned int color){
  //printf("draw_one block in\n");
  int i = row*20;
  int j = col*20;

  int p, q;

  for (p = i; p < i + 20; p++) {
	  for (q = j; q < j + 20; q++)
		  draw_one_cell(p, q, color);
  }
}

void draw_background_initial()
{
	int i, j;
	int p,q;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 30; j++) {
      if(map[i][j]==BLACK_WALL)
        draw_one_block(i, j,0x0);
      else if(map[i][j] == BLUE_WALL)
        draw_one_block(i, j,0xFF);
      else if(map[i][j] == SEED)
        draw_seed(i, j);
    }
	}
	 draw_item(button_Up);
	 draw_item(button_Down);
	 draw_item(button_Left);
	 draw_item(button_Right);
	 draw_item(Heart1);
	 draw_item(Heart2);
	 draw_item(Heart3);

}

void draw_background()
{
	int i, j;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 30; j++) {
      if(map[i][j]==BLACK_WALL);
      else if(map[i][j] == BLUE_WALL);
      else if(map[i][j] == SEED)
        draw_seed(i, j);
    }
	}
}

//seed�� �迭�� �޾Ƽ� ������ ������, ������ ������ ������ ����
void draw_seed(int row, int col) {
	int p, q;
	draw_one_block(row, col, 0x0);
	if (map[row][col] == 2)
	{
    int i = row*20;
    int j = col*20;
    for (p = i + 8; p < i + 12; p++) {
  	  for (q = j + 8; q < j + 12; q++)
			draw_one_cell(p, q, 0xFFFF00);
		}
	}
}

//draw player
void draw_player() {
	int row = player.row * 20;
	int col = player.col * 20;
  int i,j;
	if(player.state == UP){
		for(i=0; i<20; i++){
			for(j=0; j< 20; j++){
				 draw_one_cell(row + i, col + j,pac_up[i][j]);
			}
		}
	}
	else if(player.state ==DOWN){
		for(i=0; i<20; i++){
			for(j=0; j< 20; j++){
				 draw_one_cell(row + i, col + j,pac_down[i][j]);
			}
		}
	}
	else if(player.state == RIGHT){
		for(i=0; i<20; i++){
			for(j=0; j< 20; j++){
				 draw_one_cell(row + i, col + j,pac_right[i][j]);
			}
		}
	}
	else if(player.state == LEFT){
		for(i=0; i<20; i++){
			for(j=0; j< 20; j++){
				 draw_one_cell(row + i, col + j,pac_left[i][j]);
			}
		}
	}
}

void move_player() {
	int prev_row = player.row;
	int prev_col = player.col;

	/*erase previous location*/
	draw_one_block(player.row, player.col, BLACK);
	/*update location*/

	switch (player.state) {
		case UP: //Up
		{
			if (player.row > 0)
				(player.row)--;
			break;
		}
		case DOWN:
		{//Down
			if (player.row < 19)
				(player.row)++;
			break;
		}
		case RIGHT: //Right
		{
			if (player.col < 29)
				(player.col)++;
			break;
		}
		case LEFT: //left
		{
			if (player.col > 0)
				(player.col)--;
			break;
		}
	}
	//collide war, cancel movement
	if(is_collide_wall()){
		printf("collide!");
		player.row = prev_row;
		player.col = prev_col;
	}
	//seed check
	collision_check();
	/*draw new location*/
	draw_player();
}

//Check if it collide wall
int is_collide_wall()
{
	int value = map[player.row][player.col];
	if(value == 1)
		return 1;
	return 0;
}

int collision_check(){//, struct enemy **e) {
	/*take seed*/
	if (map[player.row][player.col] == 2) {
		map[player.row][player.col] = 0;
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
