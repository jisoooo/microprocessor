#include "lcd.h"
#include "image.h"

unsigned int *phy_addr = FB_ADDR;

void drawOneBlock(int row, int col, unsigned int color){
  int i = row*24;
  int j = col*24;

  int p, q;

  for(p = i ; p < i+24; p++){
    for(q = j ; q < j+24 ; q++){
        phy_addr[p*800 + q] = color;
    }
  }
}
