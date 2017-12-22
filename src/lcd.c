#include <stdio.h>

#include "lcd.h"
#include "interrupt.h"
//#include "img4.h"


void lcd_pwr_on(void){
  LCD_PWR_CON  = (LCD_PWR_CON & ~(3<<18)) | (1<<18);
  LCD_PWR_DAT  |= (1<<9);
}

void lcd_Pwr_off(void){
  LCD_PWR_DAT  &= ~(1<<9);
}

void lcd_bl_on(int level){
  LCD_BL_CON = (LCD_BL_CON & ~(3<<30)) | (2<<30);

  TCFG0_REG = (TCFG0_REG & ~(0xFF)) | 0xFF;
  TCFG1_REG = (TCFG1_REG & ~(0xF<<4)) | (4<<4);

  TCNTB1_REG = MAX_BL_LEV;
  if(level >= MAX_BL_LEV)
    TCMPB1_REG = MAX_BL_LEV-1;
  else
    TCMPB1_REG = level;

  TCON_REG |= (1<<9);
  TCON_REG = (TCON_REG & ~(0xF<<8)) | (1<<11) | (1<<8) ;
}

unsigned int get_hclk(void){
  unsigned int mpll, mdiv, pdiv, sdiv;
  unsigned int hclkx2, hclk;

  mdiv = (MPLL_CON_REG>> 16) & 0x3FF;
  pdiv = (MPLL_CON_REG>> 8)  & 0x3F;
  sdiv = (MPLL_CON_REG>> 0)  & 0x7;
  mpll = mdiv * FIN;
  mpll /= (pdiv * (1<<sdiv));

  hclkx2 = mpll / (((CLK_DIV0_REG & (0x7<<9)) >> 9) + 1);
  hclk = hclkx2 / (((CLK_DIV0_REG & (0x1<<8)) >> 8) + 1);

  printf("\nmpll : %d, hclkx2:%d, hclk:%d\n", mpll, hclkx2, hclk);

  return hclk;
}

void init_lcd_reg(void){
  unsigned int hclk = get_hclk();

  printf("VCLK : %d, CLKVAL:%d\n", S3CFB_PIXEL_CLOCK, (int)(hclk/S3CFB_PIXEL_CLOCK));

  HOSTIFB_MIFPCON_REG = 0x0;
  SPCON_REG &= (~0x3);
  SPCON_REG |= 0x1;

  GPICON_REG = 0xAAAAAAAA;
  GPJCON_REG = 0xAAAAAAAA;

  S3C_VIDCON0 = S3C_VIDCON0_VIDOUT_RGB_IF |
    S3C_VIDCON0_PNRMODE_BGR_P |
    S3C_VIDCON0_CLKVAL_F((int)(hclk/S3CFB_PIXEL_CLOCK)) |
    S3C_VIDCON0_CLKDIR_DIVIDED |
    S3C_VIDCON0_CLKSEL_F_HCLK;

  S3C_VIDCON1 = S3C_VIDCON1_IHSYNC_INVERT |
    S3C_VIDCON1_IVSYNC_INVERT |
    S3C_VIDCON1_IVDEN_NORMAL;

  S3C_VIDTCON0 = S3C_VIDTCON0_VBPD(S3CFB_VBP - 1) |
    S3C_VIDTCON0_VFPD(S3CFB_VFP - 1) |
    S3C_VIDTCON0_VSPW(S3CFB_VSW - 1);

  S3C_VIDTCON1 = S3C_VIDTCON1_HBPD(S3CFB_HBP - 1) |
    S3C_VIDTCON1_HFPD(S3CFB_HFP - 1) |
    S3C_VIDTCON1_HSPW(S3CFB_HSW - 1);

  S3C_VIDTCON2 = S3C_VIDTCON2_LINEVAL(S3CFB_VRES - 1) |
    S3C_VIDTCON2_HOZVAL(S3CFB_HRES - 1);

  S3C_WINCON0 = S3C_WINCONx_BUFSEL_0 |
    S3C_WINCONx_BUFAUTOEN_DISABLE |
    S3C_WINCONx_HAWSWP_DISABLE |
    S3C_WINCONx_BURSTLEN_4WORD |
    S3C_WINCONx_BPPMODE_F_24BPP_888;
}

void set_wincon0_enable(void){
  S3C_WINCON0 |= S3C_WINCONx_ENWIN_F_ENABLE;
}

void set_vidcon0_enable(void){
  S3C_VIDCON0 |= (S3C_VIDCON0_ENVID_ENABLE |
  S3C_VIDCON0_ENVID_F_ENABLE);
}

void set_lcd_pos(int ltx, int lty, int rbx, int rby){
  S3C_VIDOSD0A = S3C_VIDOSDxA_OSD_LTX_F(ltx) |
    S3C_VIDOSDxA_OSD_LTY_F(lty);

  S3C_VIDOSD0B = S3C_VIDOSDxB_OSD_RBX_F(rbx- 1) |
    S3C_VIDOSDxB_OSD_RBY_F(rby- 1);
}

void draw_image(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int *data){
  unsigned int *phy_addr = FB_ADDR;
  int i, j, k;
  int hbase, vbase;
   w=120;
   h=120;
  int col, row;
  int temp;

  S3C_VIDW00ADD0B0 = FB_ADDR; // Buffer Address
  S3C_VIDW00ADD1B0 = S3C_VIDWxxADD1_VBASEL_F(FB_ADDR +
    (PAGE_WIDTH + S3CFB_OFFSET) * S3CFB_VRES);
  S3C_VIDW00ADD2  = S3C_VIDWxxADD2_OFFSIZE_F(S3CFB_OFFSET) |
    S3C_VIDWxxADD2_PAGEWIDTH_F(PAGE_WIDTH);



  for(i=0; i<w*h*3 ; i+=3){

   row = i/(h*3);
   col = (i%(w*3))/3;

   phy_addr[(row+y)*800 + (col+x)]   = /*0xFFFF00;*/ ((data[i]<<16) | (data[i + 1] <<8)| (data[i+2]));
  }

  set_wincon0_enable();
  set_vidcon0_enable();
}

void init_background(void){
  int i=0;
  unsigned int * temp_addr= FB_ADDR;
  for(i=0; i<800*480; i++)
    temp_addr[i]=0;
}

void lcd_init(){
  int i=0;
  lcd_bl_on(MAX_BL_LEV-1);
  lcd_pwr_on();
  init_lcd_reg();

  set_lcd_pos(0, 0, S3CFB_HRES, S3CFB_VRES);

  init_background();


}
