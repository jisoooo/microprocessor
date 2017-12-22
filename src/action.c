#include "action.h"
#include "itemlist.h"
#include "interrupt.h"

extern item button_Up;
extern item player;
extern unsigned int touch_x;
extern unsigned int touch_y;

void button_action(){
  //action button Up
    if (((touch_x>= button_Up.x) && (touch_x <= button_Up.x+button_Up.w))&&((touch_y>=button_Up.y)&&(touch_y<=button_Up.y+button_Up.h))){
      player.y+=20;
    }


}
