#include "action.h"
#include "itemlist.h"
#include "interrupt.h"
#include "image.h"

extern item button_Up;
extern item button_Down;
extern item button_Left;
extern item button_Right;

extern unsigned int touch_x;
extern unsigned int touch_y;
extern struct player player;

void button_action(){
  //action button Up
  printf("touch point: (%d, %d)\n", touch_x, touch_y);

    if (((touch_y>= button_Up.x) && (touch_y <= button_Up.x+button_Up.w))&&((touch_x>=button_Up.y)&&(touch_x<=button_Up.y+button_Up.h))){
      player.state=UP;
      printf("Up");
    }
    else if (((touch_y>= button_Down.x) && (touch_y <= button_Down.x+button_Down.w))&&((touch_x>=button_Down.y)&&(touch_x<=button_Down.y+button_Down.h))){
      player.state=DOWN;
      printf("Down");

    }
    else if (((touch_y>= button_Left.x) && (touch_y <= button_Left.x+button_Left.w))&&((touch_x>=button_Left.y)&&(touch_x<=button_Left.y+button_Left.h))){
      player.state=LEFT;
      printf("Left");

    }
    else if (((touch_y>= button_Right.x) && (touch_y <= button_Right.x+button_Right.w))&&((touch_x>=button_Right.y)&&(touch_x<=button_Right.y+button_Right.h))){
      player.state=RIGHT;
      printf("Right");

    }

}
