#include <nds.h>
#include <fat.h>
#include "globals.h"
#include "menu.h"
#include "blit.h"
#include "imgdefs.h"
#include <stdio.h>

int main()
{
    consoleDemoInit();
    printf("Loading...\n");
    fatInitDefault();
    printf("FAT loaded\n");
    irqInit();
    irqEnable(IRQ_VBLANK);
    printf("IRQs enabled\n");
    InitGlobals();
    printf("Globals initialized\n");

    /*for(int x = 0; x < 256; x++)
        for(int y = 0; y < 192; y++)
            videobuf_main[y*256 + x] = RGB15(31,0,0)|BIT(15);*/

    printf("asdf\n");
    dsprintf(&pinfo, 0, 0, "asdf");
    BlitMain(50,50,(u16 *) square_red);
    printf("asdf2\n");
    //while(1) Menu::Main();

    return 0;
}
