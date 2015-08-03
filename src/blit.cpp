#include "blit.h"

// takes 'raw' formatted image (src) - refer to utils/png2raw.cpp for my raw
// format. dest is a screen buffer (or whatever, maybe layering stuff..)
void BlitImage(int nx, int ny, u16 *dest, const u16 *src)
{
    u32 w, h;
    w = *((u32*)src);
    h = *(((u32*)src)+1);
    //src += sizeof(u32)*2;

    for(u32 y = 0; y < h; y++) {
        for(u32 x = 0; x < w; x++)
            if(src[y*w + x] & BIT(15))
                dest[(y+ny)*256 + nx + x] = src[y*w + x];
        //memcpy(dest+(y*256)+nx, src+(sizeof(u32)*2)+((y-ny)*w), w);
    }
}
