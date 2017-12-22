#include "lcd.h"
#include "interrupt.h"
#include "vic.h"
//#include "item.h"
//#include "img4.h"
//#include "image.h"

//extern unsigned int * player;
int main(void){

   mango_uart_init(1, 115200);

   lcd_init();
  //gfx_init();
  mango_hw_init();

  //draw_image(player_x,player_y,120,120,player);
  mango_menu_main();
  draw_background();
  return 0;
}
