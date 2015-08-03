#ifndef _OCCUPATION_H_
#define _OCCUPATION_H_

#include "blocktype.h"
#include "gfxloc.h"
#include "fix.h"

enum OOB {
    OOB_UP = 0x1,
    OOB_DOWN = 0x2,
    OOB_LEFT = 0x4,
    OOB_RIGHT = 0x8
};

namespace Occupation { // in my pants
    void Subtract(SQUARE_LOCATION *, const SQUARE_LOCATION *);
    void SubtractFix(SQUARE_LOCATION *, const SQUARE_LOCATION *);
    void SubtractX(SQUARE_LOCATION *, int);
    void SubtractY(SQUARE_LOCATION *, int);
    void SubtractXY(SQUARE_LOCATION *, int, int);
    void Add(SQUARE_LOCATION *, const SQUARE_LOCATION *);
    void AddFix(SQUARE_LOCATION *, const SQUARE_LOCATION *);
    void AddX(SQUARE_LOCATION *, int);
    void AddY(SQUARE_LOCATION *, int);
    void AddXY(SQUARE_LOCATION *, int, int);
    void Copy(SQUARE_LOCATION *, const SQUARE_LOCATION *);
    void CopyFix(SQUARE_LOCATION *, const SQUARE_LOCATION *);
    int OutOfBounds(SQUARE_LOCATION *);
    int OutOfBoundsWhere(SQUARE_LOCATION *);
    int OutOfBounds(SQUARE_LOCATION *, int);
    int OutOfBoundsX(SQUARE_LOCATION *);
    int OutOfBoundsX(SQUARE_LOCATION *, int);
    int OutOfBoundsY(SQUARE_LOCATION *);
    int OutOfBoundsY(SQUARE_LOCATION *, int);
    bool UpperMost(SQUARE_LOCATION *, int);
    bool RightMost(SQUARE_LOCATION *, int);
    bool DownMost(SQUARE_LOCATION *, int);
    bool LeftMost(SQUARE_LOCATION *, int);
    bool Compare(SQUARE_LOCATION *, SQUARE_LOCATION *);
}

#endif /* _OCCUPATION_H_ */
