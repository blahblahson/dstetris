#ifndef _TEXT_H_
#define _TEXT_H_

#include <nds.h>
#include <stdio.h>
#include <string.h>

// right now this only works with monospace text

// undefine this to remove clipping
#define TEXT_CLIP

// predefined generic character table
extern int text_generic_ctable[];

struct PRINTINFO {
    u32 w, h;
    u16 *dest;
    u16 *src;
    int chartable[128];
};

void dsprintstr(PRINTINFO *, unsigned int, unsigned int, const char *);
//int dsprintf_noclip(PRINTINFO *, unsigned int, unsigned int, const
//        char *, ...);

#define dsprintf(inf,x,y,fmt...) ({ char __dspfstr[1024]; \
        sprintf(__dspfstr,##fmt); dsprintstr(inf,x,y,__dspfstr); })
#define TEXTLEN(inf,str) (strlen(str)*inf.w)

#endif /* _TEXT_H_ */
