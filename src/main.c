#include "lcd.h"
#include "interrupt.h"
#include "vic.h"
#include "img4.h"
#include "image.h"

extern int player_x;
extern int player_y;
//extern unsigned int * player;
int main(void){

   mango_uart_init(1, 115200);

   lcd_init();
  //gfx_init();
  mango_hw_init();

  drawOneBlock(10,10, 0xFF0000);
  //draw_image(player_x,player_y,120,120,player);

  mango_menu_main();
  return 0;
}
