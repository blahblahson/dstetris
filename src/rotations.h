#ifndef _ROTATIONS_H_
#define _ROTATIONS_H_

#include "blocktype.h"
#include "occupation.h"
#include "grid.h"
#include "fix.h"

/* most repetetive functions in the entire game
 * http://www.the-shell.net/img/srs_study.html */

// note - grid doesn't really need to be passed, but it is faster
namespace Rotation {
    bool I(BLOCK_POSITION, BLOCK_POSITION, SQUARE_LOCATION *, Grid *);
    bool J(BLOCK_POSITION, BLOCK_POSITION, SQUARE_LOCATION *, Grid *);
    bool L(BLOCK_POSITION, BLOCK_POSITION, SQUARE_LOCATION *, Grid *);
    bool S(BLOCK_POSITION, BLOCK_POSITION, SQUARE_LOCATION *, Grid *);
    bool Z(BLOCK_POSITION, BLOCK_POSITION, SQUARE_LOCATION *, Grid *);
    bool T(BLOCK_POSITION, BLOCK_POSITION, SQUARE_LOCATION *, Grid *);
};

#endif /* _ROTATIONS_H_ */
