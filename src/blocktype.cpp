#include "blocktype.h"
#include "imgdefs.h"

/*
UL_COLOR BLOCK_TINT[] = {
    RGB15(31, 0, 0),    // BLOCK_L
    RGB15(31, 31, 0),   // BLOCK_J
    RGB15(31, 31, 31),  // BLOCK_O
    RGB15(0, 0, 31),    // BLOCK_T
    RGB15(0, 31, 31),   // BLOCK_I
    RGB15(31, 0, 31),   // BLOCK_Z
    RGB15(0, 31, 0)     // BLOCK_S
} ;
*/

/* note: this method and color selection are both subject to change in the next
 * revision, this is just a fix for being unable to tint a single image. colors
 * will change as SRS compliance gains higher priority. --1.1.0 2008-02-06;
 * main purpose is to move from ulib to libnds, SRS compliance isn't important
 * for now */
u16 *BLOCK_IMAGE[] = {
    (u16 *) square_red,         // BLOCK_L
    (u16 *) square_yellow,      // BLOCK_J
    (u16 *) square_white,       // BLOCK_O
    (u16 *) square_blue,        // BLOCK_T
    (u16 *) square_cyan,        // BLOCK_I
    (u16 *) square_magenta,     // BLOCK_Z
    (u16 *) square_green        // BLOCK_S
} ;

u16 *BLOCK_LIMAGE[] = {
    (u16 *) square_lred,        // BLOCK_L
    (u16 *) square_lyellow,     // BLOCK_J
    (u16 *) square_lwhite,      // BLOCK_O
    (u16 *) square_lblue,       // BLOCK_T
    (u16 *) square_lcyan,       // BLOCK_I
    (u16 *) square_lmagenta,    // BLOCK_Z
    (u16 *) square_lgreen       // BLOCK_S
} ;

/* BLOCK_OCCUPATION, reference like so:
 * memcpy(&occupation, BLOCK_OCCUPATION[type][position], sizeof(occupation));
 * where type is of BLOCK_TYPE and position is of type BLOCK_POSITION
 *
 * given coordinates are the INITIAL spawn points (assuming they are at that
 * angle - which is not the case unless it's rotated (only BLOCKPOS_0 is truly
 * 'initial')
 *
 * do transformations by subtracting and adding the given arrays */
SQUARE_LOCATION BLOCK_OCCUPATION[][4][4] = {
    // BLOCK_L
    { { {5, -2}, {3, -1}, {4, -1}, {5, -1} },   // BLOCKPOS_0
      { {4, -2}, {4, -1}, {4, 0}, {5, 0} },     // BLOCKPOS_90
      { {3, -1}, {4, -1}, {5, -1}, {3, 0} },    // BLOCKPOS_180
      { {3, -2}, {4, -2}, {4, -1}, {4, 0} } },  // BLOCKPOS_270

    // BLOCK_J
    { { {3, -2}, {3, -1}, {4, -1}, {5, -1} },   // BLOCKPOS_0
      { {4, -2}, {5, -2}, {4, -1}, {4, 0} },    // BLOCKPOS_90
      { {3, -1}, {4, -1}, {5, -1}, {5, 0} },    // BLOCKPOS_180
      { {4, -2}, {4, -1}, {3, 0}, {4, 0} } },   // BLOCKPOS_270

    // BLOCK_O
    { { {4, -2}, {5, -2}, {4, -1}, {5, -1} },   // BLOCKPOS_0
      { {4, -2}, {5, -2}, {4, -1}, {5, -1} },   // BLOCKPOS_90
      { {4, -2}, {5, -2}, {4, -1}, {5, -1} },   // BLOCKPOS_180
      { {4, -2}, {5, -2}, {4, -1}, {5, -1} } }, // BLOCKPOS_270

    // BLOCK_T
    { { {4, -2}, {3, -1}, {4, -1}, {5, -1} },   // BLOCKPOS_0
      { {4, -2}, {4, -1}, {5, -1}, {4, 0} },    // BLOCKPOS_90
      { {3, -1}, {4, -1}, {5, -1}, {4, 0} },    // BLOCKPOS_180
      { {4, -2}, {3, -1}, {4, -1}, {4, 0} } },  // BLOCKPOS_270

    // BLOCK_I
    { { {3, -1}, {4, -1}, {5, -1}, {6, -1} },   // BLOCKPOS_0
      { {5, -2}, {5, -1}, {5, 0}, {5, 1} },     // BLOCKPOS_90
      { {3, 0}, {4, 0}, {5, 0}, {6, 0} },       // BLOCKPOS_180
      { {4, -2}, {4, -1}, {4, 0}, {4, 1} } },   // BLOCKPOS_270

    // BLOCK_Z
    { { {3, -2}, {4, -2}, {4, -1}, {5, -1} },   // BLOCKPOS_0
      { {5, -2}, {4, -1}, {5, -1}, {4, 0} },    // BLOCKPOS_90
      { {3, -1}, {4, -1}, {4, 0}, {5, 0} },     // BLOCKPOS_180
      { {4, -2}, {3, -1}, {4, -1}, {3, 0} } },  // BLOCKPOS_270

    // BLOCK_S
    { { {4, -2}, {5, -2}, {3, -1}, {4, -1} },   // BLOCKPOS_0
      { {4, -2}, {4, -1}, {5, -1}, {5, 0} },    // BLOCKPOS_90
      { {4, -1}, {5, -1}, {3, 0}, {4, 0} },     // BLOCKPOS_180
      { {3, -2}, {3, -1}, {4, -1}, {4, 0} } }   // BLOCKPOS_270
} ;
