#ifndef _GRID_H_
#define _GRID_H_

#include "blocktype.h"
#include "gfxloc.h"
#include "fix.h"
#include "occupation.h"

/* use after ulib init else everything will be corrupted */
class Grid {
    public:
        Grid();
        ~Grid();

        void ClearLine(unsigned int); // y
        void MoveLine(unsigned int, unsigned int); // source, dest
        void Clear();
        void Update();
        void Draw();
        void CheckLines();
        void GameOver();

        bool Floored(SQUARE_LOCATION *);
        void Overlay(SQUARE_LOCATION *, BLOCK_TYPE);
        bool Obstruct(SQUARE_LOCATION *);
        int ObstructWhere(SQUARE_LOCATION *);

        BLOCK_TYPE grid[GRIDW][GRIDH];
        BLOCK_TYPE ngrid[GRIDW][2]; /* while grid-y approaches infinity
                                       downwards, ngrid-y approaches infinity
                                       upwards (see Grid::Floored() - it makes
                                       it more straightforward) */
} ;

#endif /* _GRID_H_ */
