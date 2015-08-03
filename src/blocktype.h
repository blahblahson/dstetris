#ifndef _BLOCKTYPE_H_
#define _BLOCKTYPE_H_

#include <nds.h>

typedef struct {
    int x, y;
} SQUARE_LOCATION;

typedef enum {
    BLOCK_L = 0,
    BLOCK_J,
    BLOCK_O,
    BLOCK_T,
    BLOCK_I,
    BLOCK_Z,
    BLOCK_S,
    BLOCK_NONE
} BLOCK_TYPE;

// clockwise bearings
typedef enum {
    BLOCKPOS_0 = 0,
    BLOCKPOS_90,
    BLOCKPOS_180,
    BLOCKPOS_270
} BLOCK_POSITION;

// deprecated as of 1.1.0, use BLOCK_IMAGE and BLOCK_LIMAGE
//extern UL_COLOR BLOCK_TINT[];
extern u16 *BLOCK_IMAGE[];
extern u16 *BLOCK_LIMAGE[];
extern SQUARE_LOCATION BLOCK_OCCUPATION[][4][4];

#endif /* _BLOCKTYPE_H_ */
