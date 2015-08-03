#ifndef _BLIT_H_
#define _BLIT_H_

#include <nds.h>
#include <string.h>
#include "globals.h"

void BlitImage(int, int, u16 *, const u16 *);

#define BlitMain(x,y,src) BlitImage(x,y,videobuf_main,src)
#define BlitSub(x,y,src) BlitImage(x,y,videobuf_sub,src)

#endif /* _BLIT_H_ */
