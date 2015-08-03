#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "text.h"
#include <nds.h>
#include <string.h>

extern int text_generic_ctable[];
extern u16 *videobuf_main;
extern u16 *videobuf_sub;
extern PRINTINFO pinfo;

void InitGlobals();

#define ClearVideoMain() memset(videobuf_main,0,256*192*2)
#define ClearVideoSub() memset(videobuf_sub,0,256*192*2)

#endif /* _GLOBALS_H_ */
