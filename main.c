#include "cc65.h" /* for cc65_sin(), cc65_cos() */
#include "bg.h"

void NesMain(void) {
    int i, j;
    int x, y;
    int t, u;
    byte v_stat, h_stat;
    byte bgx = 0, bgy = 0;
    byte first;

    char str[10] = "DEMOSCENE";

    const char palettebg[] = {
        0x0f, 0x11, 0x21, 0x30,
        0x0f, 0x11, 0x21, 0x30,
        0x0f, 0x11, 0x21, 0x30,
        0x0f, 0x11, 0x21, 0x30
    };
    const char palettesp[] = {
        0x0f, 0x09, 0x19, 0x30,
        0x0f, 0x0f, 0x10, 0x21,
        0x0f, 0x09, 0x19, 0x21,
        0x0f, 0x15, 0x27, 0x30
    };

    __VBLANK;
    __INIT_PPU;

    set_palette_bg((char *)palettebg);
    set_palette_sprite((char *)palettesp);

    __PPU_ADDRESS(0x20, 0x00);
    v_stat = h_stat = 1;
    for (i = 0; i < 30; i++) {
        for (j = 0; j < 32; j += 4) {
            *REGIST_GRA = h_stat ? 0x01 : 0x03;
            *REGIST_GRA = h_stat ? 0x01 : 0x03;
            *REGIST_GRA = h_stat ? 0x01 : 0x03;
            *REGIST_GRA = h_stat ? 0x01 : 0x03;
            h_stat = h_stat ? 0 : 1;
        }
        if (i % 4 == 0) {
            h_stat = h_stat ? 0 : 1;
        }
    }
    __PPU_ADDRESS(0x24, 0x00);
    v_stat = h_stat = 1;
    for (i = 0; i < 30; i++) {
        for (j = 0; j < 32; j += 4) {
            *REGIST_GRA = h_stat ? 0x01 : 0x03;
            *REGIST_GRA = h_stat ? 0x01 : 0x03;
            *REGIST_GRA = h_stat ? 0x01 : 0x03;
            *REGIST_GRA = h_stat ? 0x01 : 0x03;
            h_stat = h_stat ? 0 : 1;
        }
        if (i % 4 == 0) {
            h_stat = h_stat ? 0 : 1;
        }
    }

    __SET_SCROLL(0, 0);
    __SET_PPU(0x00, 0x1e);

    t = 0;
    while (1) {
        __VBLANK;
        __SET_SCROLL(bgx, bgy);
        __SEND_DMA(0x07);

        first = 1;
        for (i = 0; i < 10; i++) {
            u = t + i * 10;
            u = 360 < u ? u - 360 : u;
            u = 360 < u ? u - 360 : u;
            x = 128 + cc65_cos(u) / 3;
            y = 120 + cc65_sin(u) / 3;
            if (y < 120) {
                set_dma((char *)0x0700, first, x, y, str[i], 0);
            } else {
                set_dma((char *)0x0700, first, x, y, str[i], 0x40);
            }
            first = 0;
        }

        t++;
        if (t > 360) t = 0;

        if (t % 2 == 0) {
            bgx++;
            if (bgx == 255) {
                bgx = 0;
            }
            bgy++;
            if (bgy == 240) {
                bgy = 0;
            }
        }
    }
}

void NMIProc(void) {
}
