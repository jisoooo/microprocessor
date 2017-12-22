#include <stdio.h>

int map[20][30] = {
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	1,
	1,	2,	1,	1,	1,	1,	1,	1,	1,	2,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	2,	1,	1,	1,	1,	1,	1,	1,	2,	1,
	1,	2,	1,	0,	0,	0,	0,	0,	1,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	1,	0,	0,	0,	0,	0,	1,	2,	1,
	1,	2,	1,	0,	0,	0,	0,	0,	1,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	1,	0,	0,	0,	0,	0,	1,	2,	1,
	1,	2,	1,	0,	0,	0,	0,	0,	1,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	1,	0,	0,	0,	0,	0,	1,	2,	1,
	1,	2,	1,	1,	1,	1,	1,	1,	1,	2,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	2,	1,	1,	1,	1,	1,	1,	1,	2,	1,
	1,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	1,
	1,	2,	1,	1,	1,	1,	1,	2,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	2,	1,	1,	1,	1,	1,	2,	1,
	1,	2,	1,	0,	0,	0,	1,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	1,	0,	0,	0,	1,	2,	1,
	1,	2,	1,	1,	1,	1,	1,	2,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	2,	1,	1,	1,	1,	1,	2,	1,
	1,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	1,
	1,	2,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	2,	1,	1,	1,	1,	2,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	2,	1,
	1,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	1,	0,	0,	1,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	1,
	1,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	1,	0,	0,	1,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	1,
	1,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	1,	0,	0,	1,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	1,
	1,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	1,	0,	0,	1,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	1,
	1,	2,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	2,	1,	1,	1,	1,	2,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	2,	1,
	1,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1
};

void drawOneBlock(int row, int col, unsigned int color);
