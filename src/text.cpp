#include <nds.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "text.h"

void dsprintstr(PRINTINFO *info, unsigned int x, unsigned int y, const char
        *str)
{
    printf("dsprintstr called\n");
#ifdef TEXT_CLIP
    if(x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT ||
            x + info->w > SCREEN_WIDTH || y + info->h > SCREEN_HEIGHT)
        return;
#endif

    unsigned int i;
    unsigned int pos, ypos, xpos;
    printf("\nstrlen = %d\nh = %d, w = %d\n", strlen(str), info->h, info->w);

    for(i = 0; i < strlen(str); i++) {
        pos = x + i*info->w;
        for(ypos = y; ypos < y+info->h; ypos++) {
            for(xpos = pos; xpos < pos + info->w; xpos++) {
                if(info->src[ypos-y * info->w + info->chartable[(int) str[i]] +
                        xpos - pos] == RGB15(31,0,31)) {
                    //printf("magenta!\n");
                    continue;
                }
                info->dest[ypos * SCREEN_WIDTH + xpos] = info->src[(ypos - y) *
                    570 + info->chartable[(int) str[i]] + xpos - pos] |
                    BIT(15);
                //printf("b(%d,%d)%x:::", ypos, xpos, info->src[ypos - y * 570 +
                //        info->chartable[(int) str[i]] + xpos - pos]);
            }
        }
    }
    printf("\nstrlen = %d\nh = %d, w = %d\n", strlen(str), info->h, info->w);

    printf("printed something\n");
}

// guaranteed no-clipping (even with TEXT_CLIP defined)
/*int dsprintf_noclip(PRINTINFO *info, unsigned int x, unsigned int y, const char *format, ...)
{
    int ret;
    va_list ap;
    char *str = NULL;
    unsigned int i;
    unsigned int pos, ypos, xpos;

    printf("\nva_start\n");
    va_start(ap, format);
    printf("vsprintf\n");
    ret = vsprintf(str, format, ap);
    printf("result = %d, len = %d\n", ret, strlen(str));
    printf("va_end\n");
    va_end(ap);
    printf("loop\n");

    for(i = 0; i < strlen(str); i++) {
        pos = x + i*info->w;
        for(ypos = y; ypos < y+info->h; ypos++) {
            for(xpos = pos; xpos < pos + info->w; xpos++) {
                if(info->src[ypos-y * 570 + info->chartable[(int) str[i]] +
                        xpos - pos] & ~BIT(15) == RGB15(31,0,0))
                    continue;
                info->dest[ypos * SCREEN_WIDTH + xpos] = info->src[ypos - y *
                    570 + info->chartable[(int) str[i]] + xpos - pos];
            }
        }
    }
    printf("end loop\n");

    return ret;
}*/
