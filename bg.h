#ifndef __BG_H
#define __BG_H

#include "register.h"

#define __INIT_PPU            \
    *REGIST_PPU_CTRL1 = 0x00; \
    *REGIST_PPU_CTRL2 = 0x00;
#define __SET_PPU(flag1, flag2) \
    *REGIST_PPU_CTRL1 = flag1;  \
    *REGIST_PPU_CTRL2 = flag2;

#define __PPU_ADDRESS(high, low) \
    *REGIST_ADR = high;          \
    *REGIST_ADR = low;

#define __SET_SCROLL(x, y) \
    *REGIST_SCROLL = x;    \
    *REGIST_SCROLL = y;

#define __SEND_DMA(addr) *REGIST_DMA = addr;

#define __VBLANK \
    while (!(*REGIST_PPU_STS & 0x80));
#define __ZERO_SPRITE \
    while ( (*REGIST_PPU_STS & 0x40)); \
    while (!(*REGIST_PPU_STS & 0x40));

typedef unsigned char byte;


void fill_background(byte address1, byte address2, byte val, byte cnt) {
    byte i;

    *REGIST_ADR = address1;
    *REGIST_ADR = address2;
    for (i = 0; i < cnt; i++)
    {
        *REGIST_GRA = val;
    }
}

void set_background(byte address1, byte address2, byte *bg, byte cnt) {
    byte i;

    *REGIST_ADR = address1;
    *REGIST_ADR = address2;

    for (i = 0; i < cnt; i++) {
        *REGIST_GRA = *(bg + i);
    }
}

//座標から背景のアドレス計算
void get_background_address(byte screen, byte x, byte y, char *ret)
{
    unsigned int pos;

    switch (screen) {
    case 0:        //左下
        pos = 0x2000;
        break;
    case 1:        //右下
        pos = 0x2800;
        break;
    case 2:        //左上
        pos = 0x2400;
        break;
    case 3:        //右上
        pos = 0x2c00;
        break;
    }

    pos += y * 0x20 + x;
    *(ret + 0) = (pos & 0xff00) >> 8;
    *(ret + 1) =  pos & 0x00ff;
}

void set_palette_bg(byte *palette) {
    byte i;

    *REGIST_ADR = 0x3f;
    *REGIST_ADR = 0x00;

    for (i = 0; i < 16; i++) {
        *REGIST_GRA = *(palette + i);
    }
}

void set_sprite(byte first, byte x, byte y, byte index, byte flag) {
    if (first) {
        *REGIST_SPR_ADR = 0x00;
    }
    *REGIST_SPR_GRA = y;     // y - 1
    *REGIST_SPR_GRA = index; // pattern index
    *REGIST_SPR_GRA = flag;  // attribute : VHP000CC
    *REGIST_SPR_GRA = x;     // x
}

void set_palette_sprite(byte *palette) {
    byte i;

    *REGIST_ADR = 0x3f;
    *REGIST_ADR = 0x10;

    for (i = 0; i < 16; i++) {
        *REGIST_GRA = *(palette + i);
    }
}


void init_dma(byte *address)
{
    byte i;
    for (i = 0; i < 255; i++) {
        *(address + i) = 0;
    }
}

void set_dma(byte *address, byte first, byte x, byte y, byte index, byte flag) {
    static byte cnt;
    if (first) {
        cnt = 0;
    }
    *(address + cnt + 0) = y;
    *(address + cnt + 1) = index;
    *(address + cnt + 2) = flag;
    *(address + cnt + 3) = x;
    cnt += 4;
}

#endif /* __BG_H */
