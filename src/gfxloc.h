#ifndef _GFXLOC_H_
#define _GFXLOC_H_

/* locations of various graphic stuff, the grid, next block etc. */

// size of grid, in squares
#define GRIDW 10
#define GRIDH 20

// position of grid, in pixels
#define GRID_POS_X 50
#define GRID_POS_Y 2

// utility defines to work out block placement
#define BLOCKX(x) ((x*9)+GRID_POS_X)
#define BLOCKY(y) ((y*9)+GRID_POS_Y)

// location of 'next' block, in pixels
#define NBLOCK_POS_X (BLOCKX((GRIDW+3)))
#define NBLOCK_POS_Y (BLOCKY(1))

// utility defines for 'next' block
#define NBLOCKX(x) ((x*9)+NBLOCK_POS_X)
#define NBLOCKY(y) ((y*9)+NBLOCK_POS_Y)

// score
#define SCORE_POS_X NBLOCKX(0)
#define SCORE_POS_Y NBLOCKY(0) + 50

// lines
#define CLEAREDLINES_POS_X SCORE_POS_X
#define CLEAREDLINES_POS_Y SCORE_POS_Y + 50

#endif /* _GFXLOC_H_ */
