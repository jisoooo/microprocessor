#include <stdio.h>
#include "sprite.h"
#include "graphics.h"
#include "frame.h"

#include "img4.h"


extern unsigned *scr_target;

void sprite_resource_init() {


	// int i;
	// for (i = 0; i < 80*80; i++) {
	// 	int alpha = (spr_key.data[i] >> 24) & 0xFF;
	// 	alpha /= 3;
	// 	spr_key.data[i] = (spr_key.data[i] & 0xFFFFFF) | (alpha << 24);
	// }
	// for (i = 0; i < 120; i++) {
	// 	spr_pixelsky.data[i] = spr_pixelsky.data[239];
	// }
  //
	// spr_key.ofx = 0;
	// spr_key.ofy = 0;
	// spr_dgt.ofx = 0;
	// spr_dgt.ofy = 0;
}

void sprite_draw(sprite *spr, float __x, float __y) {
	int x, y;
	int dx1, dy1, dx2, dy2;
	int cx1, cy1, cx2, cy2;

	x = (int)__x - spr->ofx;
	y = (int)__y - spr->ofy;

	dx1 = x;
	dy1 = y;
	dx2 = x + spr->w;
	dy2 = y + spr->h;

	if (dx1 >= SCREENW || dx2 <= 0 || dy1 >= SCREENH || dy2 <= 0)
		return;

	cx1 = 0;
	cy1 = 0;
	cx2 = 0;
	cy2 = 0;

	if (dx1 < 0) {
		cx1 = -dx1;
		dx1 = 0;
	}

	if (dy1 < 0) {
		cy1 = -dy1;
		dy1 = 0;
	}

	if (dx2 >= SCREENW) {
		cx2 = dx2 - SCREENW;
		dx2 = SCREENW;
	}

	if (dy2 >= SCREENH) {
		cy2 = dy2 - SCREENH;
		dy2 = SCREENH;
	}

	gfx_bitblck_ext(scr_target, spr->data,
		dx1, dy1, dx2, dy2,
		SCREENW, SCREENH,
		cx1, cy1, spr->w - cx2, spr->h - cy2,
		spr->w, spr->h);
}

void sprite_draw_clear(unsigned wrapper) {
	gfx_bitblck_ext(scr_target, &wrapper,
		0, 0, SCREENW, SCREENH,
		SCREENW, SCREENH,
		0, 0, 1, 1,
		1, 1);
}
