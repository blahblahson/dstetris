#include <nds.h>
#include <string.h>
#include "globals.h"
#include "texttable.h"

// generic character table stuff
#define GCT_WIDTH 6
#define n(x) (GCT_WIDTH*(x))
int text_generic_ctable[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    n(0), n(1), n(2), n(3), n(4), n(5), n(6), n(7), n(8), n(9), n(10), n(11),
    n(12), n(13), n(14), n(15), n(16), n(17), n(18), n(19), n(20), n(21),
    n(22), n(23), n(24), n(25), n(26), n(27), n(28), n(29), n(30), n(31),
    n(32), n(33), n(34), n(35), n(36), n(37), n(38), n(39), n(40), n(41),
    n(42), n(43), n(44), n(45), n(46), n(47), n(48), n(49), n(50), n(51),
    n(52), n(53), n(54), n(55), n(56), n(57), n(58), n(59), n(60), n(61),
    n(62), n(63), n(64), n(65), n(66), n(67), n(68), n(69), n(70), n(71),
    n(72), n(73), n(74), n(75), n(76), n(77), n(78), n(79), n(80), n(81),
    n(82), n(83), n(84), n(85), n(86), n(87), n(88), n(89), n(90), n(91),
    n(92), n(93), n(94),
    0
};
/* the format of this is:
 !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
 * first thing being space, last being ~, 0x00 to 0x1F and 0x7F are all 0, so
 * they display a space (or nothing) */
#undef GCT_WIDTH
#undef n

u16 *videobuf_main;
u16 *videobuf_sub;
PRINTINFO pinfo;

void _pinfo_init(u16 *dest)
{
    pinfo.w = *((u32*) texttable)/95;
    pinfo.h = *(((u32*) texttable)+1);
    printf("%d, %d\n", pinfo.w, pinfo.h);
    pinfo.src = (u16 *) texttable + 2;
    pinfo.dest = dest;
    memcpy(pinfo.chartable, text_generic_ctable, 128);
}

void _videobuf_init()
{
    videobuf_main = (u16 *) BG_BMP_RAM(0);
    videoSetMode(MODE_5_2D | DISPLAY_BG3_ACTIVE);
    vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
    BG3_CR = BG_BMP16_256x256 | BG_BMP_BASE(0);

    // no rotation or shearing    
    BG3_XDY = 0;
    BG3_XDX = 1 << 8;
    BG3_YDX = 0;
    BG3_YDY = 1 << 8;
    lcdMainOnTop();
}

void InitGlobals()
{
    _videobuf_init();
    _pinfo_init(videobuf_main);
}
