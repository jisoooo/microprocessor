#include "lcd.h"
#include "image.h"
#include "itemlist.h"
#include <stdbool.h>
#include "interrupt.h"

#include <time.h>
#include <stdlib.h>

extern int map[20][30];
extern int start_map[20][30];
extern unsigned int pac_up[20][20];
extern unsigned int pac_down[20][20];
extern unsigned int pac_left[20][20];
extern unsigned int pac_right[20][20];

extern unsigned int enemy_red[20][20];
extern unsigned int enemy_purple[20][20];
extern unsigned int enemy_green[20][20];

struct player player={1, 1, DOWN, 3, 0};
struct enemy enemy_Red = {1, 5, 1, DOWN};
struct enemy enemy_Green = {1, 10, 1, DOWN};
struct enemy enemy_Purple = {1, 15, DOWN};
int score = 0;
bool 	collide = false;

extern item button_Up;
extern item button_Down;
extern item button_Left;
extern item button_Right;
extern item Heart1;
extern item Heart2;
extern item Heart3;

extern int *num_set[10];
extern int *char_set[3];


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
	draw_enemy();

	 draw_item(button_Up);
	 draw_item(button_Down);
	 draw_item(button_Left);
	 draw_item(button_Right);
	 draw_item(Heart1);
	 draw_item(Heart2);
	 draw_item(Heart3);
	 /*print level*/
	draw_char(45, 615, 0); //L
	draw_char(45, 640, 1); //E
	draw_char(45, 665, 2); //V
	draw_char(45, 690, 1); //E
	draw_char(45, 715, 0); //L
	draw_num(20, 745, 1); //level

	/*print score*/
	update_score();
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
	//if collide wall, cancel movement
	if(is_collide_wall(player.row, player.col)){
		printf("collide!");
		player.row = prev_row;
		player.col = prev_col;
	}
	//seed check
	is_eat_seed();
	//check collision with enemy
	is_collide_enemy();
	/*draw new location*/
	draw_player();
}



void move_enemy() {
	struct enemy enemy_arr[enemy_num] = { enemy_Green, enemy_Purple, enemy_Red };
	int prev_row, prev_col;
	int i;
	for (i = 0; i < enemy_num; i++) {
		struct enemy enemy = enemy_arr[i];

		//rand num
		srand(time(NULL));
		enemy.state = rand() % 4;

		/*erase previous location*/
		draw_one_block(enemy.row, enemy.col, BLACK);
		//if there was seed in enemy's previous position
		if (map[enemy.row][enemy.col] == SEED) {
			draw_seed(enemy.row,enemy.col);
		}

		/*update location*/
		switch (enemy.state) {
			case UP: //Up
			{
				if (enemy.row > 0)
					(enemy.row)--;
				break;
			}
			case DOWN:
			{//Down
				if (enemy.row < 19)
					(enemy.row)++;
				break;
			}
			case RIGHT: //Right
			{
				if (enemy.col < 29)
					(enemy.col)++;
				break;
			}
			case LEFT: //left
			{
				if (enemy.col > 0)
					(enemy.col)--;
				break;
			}
		}
		//if collide wall, cancel movement
		if (is_collide_wall(enemy.row, enemy.col)) {
			printf("collide!");
			enemy.row = prev_row;
			enemy.col = prev_col;
		}
		
		/*draw new location*/
		draw_enemy();
	}//for end
}

//Check if it collide wall
int is_collide_wall(int row, int col)
{
	int value = map[row][col];
	if (value == 1)
		return 1;
	return 0;
}

int is_eat_seed(){//, struct enemy **e) {
	/*take seed*/
	if (map[player.row][player.col] == 2) {
		map[player.row][player.col] = 0;
		score+=5;

		update_score();
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

/*print character and num*/
void draw_num(int row, int col, int num){
  int color = 0;
  int i, j, k, l;

  for(i = 0; i < 5; i++){
    for(j = 0; j < 4; j++){
      color = num_set[num][4*i+j];
      for(k = 0; k < 10; k++){
        for(l = 0; l < 10; l++){
          draw_one_cell(row+k, col+l, color);
        }
      }
      col += 10;
    }
    col -= 40;
    row += 10;
  }
}

void draw_char(int row, int col, int _char){
  int color = 0;
  int i, j, k, l;

  for(i = 0; i < 5; i++){
    for(j = 0; j < 4; j++){
      color = char_set[_char][4*i+j];
      for(k = 0; k < 5; k++){
        for(l = 0; l < 5; l++){
          draw_one_cell(row+k, col+l, color);
        }
      }
      col += 5;
    }
    col -= 20;
    row += 5;
  }
}

/*draw enemy*/
void draw_enemy() {

	int row = enemy_Red.row * 20;
	int col = enemy_Red.col * 20;
  int i,j;

	for(i=0; i<20; i++){
		for(j=0; j< 20; j++){
			 draw_one_cell(row + i, col + j,enemy_red[i][j]);
		}
	}

	row = enemy_Purple.row * 20;
	col = enemy_Purple.col * 20;

	for(i=0; i<20; i++){
		for(j=0; j< 20; j++){
			 draw_one_cell(row + i, col + j,enemy_purple[i][j]);
		}
	}

	row = enemy_Green.row * 20;
	col = enemy_Green.col * 20;

	for(i=0; i<20; i++){
		for(j=0; j< 20; j++){
			 draw_one_cell(row + i, col + j,enemy_green[i][j]);
		}
	}

}

//check collision with enemy
int is_collide_enemy()
{
	int i;
	collide = false;
	struct enemy enemy_arr [enemy_num] = { enemy_Green, enemy_Purple, enemy_Red };
	for (i = 0; i < enemy_num; i++) {
		if (enemy_arr[i].valid&&
			enemy_arr[i].col == player.col &&
			enemy_arr[i].row == player.row)
			collide = true;
	}

	if(collide){//collide
		enemy_arr[i].valid=0;
		if (player.power) {//bell eaten
			score = score + 50;
			update_score();
		}
		else {//enemy and pacman collide
			player.life--;
			erase_one_life();
			if (player.life <= 0)
				printf("game over\n");
				//game_stop();
		}
	}
}

void erase_one_life()
{
	int row = 160;
	int col = 0;
	int size = 60;
	int life = player.life;
	int i, j;

	if (life == 0)
		col = 605;
	else if (life == 1)
		col = 670;
	else if (life == 2)
		col = 735;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			draw_one_cell(row + i, col + j, BLACK);
		}
	}
}

void update_score()
{
	int h = score / 100;
	int m = (score % 100) / 10;
	int l = score % 10;
	draw_num(90, 630, h); //highest digit
	draw_num(90, 680, m); //middle digit
	draw_num(90, 730, l); //lowest digit
}

void draw_start_map() {
	int i, j;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 30; j++) {
			draw_one_block(i,j,start_map[i][j]);
		}
	}
}

int is_collide_life() {
	if (map[player.row][player.col] == 4) {
		map[player.row][player.col] = 0;
		if (player.life == 0) {
			(player.life)++;
			draw_item(Heart3);
		}
		else if (player.life == 1) {
			(player.life)++;
			draw_item(Heart2);
		}
		else if (player.life == 2) {
			(player.life)++;
			draw_item(Heart1);
		}
		else if (player.life == 3) {
			//do nothing
		}
	}
}