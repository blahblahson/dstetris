#include <string.h>
#include "occupation.h"

// subtract all x and y values in arg from all x and y values in subject
// respectively
void Occupation::Subtract(SQUARE_LOCATION *subject, const SQUARE_LOCATION *arg)
{
    for(int i = 0; i < 4; i++) {
        subject[i].x -= arg[i].x;
        subject[i].y -= arg[i].y;
    }
}

void Occupation::SubtractFix(SQUARE_LOCATION *subject, const SQUARE_LOCATION
        *arg)
{
    for(int i = 0; i < 4; i++) {
        subject[i].x -= FIX(arg[i].x);
        subject[i].y -= FIX(arg[i].y);
    }
}

void Occupation::SubtractX(SQUARE_LOCATION *subject, int x)
{
    for(int i = 0; i < 4; i++)
        subject[i].x -= x;
}

void Occupation::SubtractY(SQUARE_LOCATION *subject, int y)
{
    for(int i = 0; i < 4; i++)
        subject[i].y -= y;
}

void Occupation::SubtractXY(SQUARE_LOCATION *subject, int x, int y)
{
    for(int i = 0; i < 4; i++) {
        subject[i].x -= x;
        subject[i].y -= y;
    }
}

// add all x and y values in arg to all x and y values in subject respetively
void Occupation::Add(SQUARE_LOCATION *subject, const SQUARE_LOCATION *arg)
{
    for(int i = 0; i < 4; i++) {
        subject[i].x += arg[i].x;
        subject[i].y += arg[i].y;
    }
}

void Occupation::AddFix(SQUARE_LOCATION *subject, const SQUARE_LOCATION *arg)
{
    for(int i = 0; i < 4; i++) {
        subject[i].x += FIX(arg[i].x);
        subject[i].y += FIX(arg[i].y);
    }
}

void Occupation::AddX(SQUARE_LOCATION *subject, int x)
{
    for(int i = 0; i < 4; i++)
        subject[i].x += x;
}

void Occupation::AddY(SQUARE_LOCATION *subject, int y)
{
    for(int i = 0; i < 4; i++)
        subject[i].y += y;
}

void Occupation::AddXY(SQUARE_LOCATION *subject, int x, int y)
{
    for(int i = 0; i < 4; i++) {
        subject[i].x += x;
        subject[i].y += y;
    }
}

// copy contents of src into dest
void Occupation::Copy(SQUARE_LOCATION *dest, const SQUARE_LOCATION *src)
{
    /*for(int i = 0; i < 4; i++) {
        dest[i].x = FIX(src[i].x);
        dest[i].y = FIX(src[i].y);
    }*/

    // probably faster
    memcpy(dest, src, sizeof(SQUARE_LOCATION)*4);
}

void Occupation::CopyFix(SQUARE_LOCATION *dest, const SQUARE_LOCATION *src)
{
    for(int i = 0; i < 4; i++) {
        dest[i].x = FIX(src[i].x);
        dest[i].y = FIX(src[i].y);
    }

    // probably faster
    //memcpy(dest, src, sizeof(SQUARE_LOCATION)*4);
}

int Occupation::OutOfBounds(SQUARE_LOCATION *occupation)
{
    for(int i = 0; i < 4; i++) {
        if(UNFIX(occupation[i].x) < 0 || UNFIX(occupation[i].x) >= GRIDW ||
                UNFIX(occupation[i].y) >= GRIDH)
            return 1; // in future, maybe return by what margin
    }

    return 0;
}

int Occupation::OutOfBoundsWhere(SQUARE_LOCATION *occupation)
{
    int ret = 0;

    for(int i = 0; i < 4; i++) {
        if(UNFIX(occupation[i].x) < 0)      ret |= OOB_LEFT;
        if(UNFIX(occupation[i].x) >= GRIDW) ret |= OOB_RIGHT;
        //if(UNFIX(occupation[i].y) < 0)      ret |= OOB_UP;
        // can't move up normally
        if(UNFIX(occupation[i].y) >= GRIDH) ret |= OOB_DOWN;
    }

    return ret;
}

int Occupation::OutOfBounds(SQUARE_LOCATION *occupation, int i)
{
    if(UNFIX(occupation[i].x) < 0 || UNFIX(occupation[i].x) >= GRIDW ||
            UNFIX(occupation[i].y) >= GRIDH)
        return 1;

    return 0;
}

int Occupation::OutOfBoundsX(SQUARE_LOCATION *occupation)
{
    for(int i = 0; i < 4; i++) {
        if(UNFIX(occupation[i].x) < 0 || UNFIX(occupation[i].x) >= GRIDW)
            return 1;
    }

    return 0;
}

int Occupation::OutOfBoundsX(SQUARE_LOCATION *occupation, int i)
{
    if(UNFIX(occupation[i].x) < 0 || UNFIX(occupation[i].x) >= GRIDW)
        return 1;

    return 0;
}

int Occupation::OutOfBoundsY(SQUARE_LOCATION *occupation)
{
    for(int i = 0; i < 4; i++) {
        if(UNFIX(occupation[i].y) >= GRIDH)
            return 1;
    }

    return 0;
}

int Occupation::OutOfBoundsY(SQUARE_LOCATION *occupation, int i)
{
    if(UNFIX(occupation[i].y) >= GRIDH)
        return 1;

    return 0;
}

bool Occupation::UpperMost(SQUARE_LOCATION *subject, int i)
{
    int ret = true;

    for(int j = 0; j < 4; j++)
        ret = subject[i].y >= subject[j].y;

    return ret;
}

bool Occupation::RightMost(SQUARE_LOCATION *subject, int i)
{
    int ret = true;

    for(int j = 0; j < 4; j++)
        ret = subject[i].x >= subject[j].x;

    return ret;
}

bool Occupation::DownMost(SQUARE_LOCATION *subject, int i)
{
    int ret = true;

    for(int j = 0; j < 4; j++)
        ret = subject[i].y <= subject[j].y;

    return ret;
}

bool Occupation::LeftMost(SQUARE_LOCATION *subject, int i)
{
    int ret = true;

    for(int j = 0; j < 4; j++)
        ret = subject[i].x <= subject[j].x;

    return ret;
}

bool Occupation::Compare(SQUARE_LOCATION *a, SQUARE_LOCATION *b)
{
    for(int i = 0; i < 4; i++) {
        if(a[i].x != b[i].x) return false;
        if(a[i].y != b[i].y) return false;
    }

    return true;
}
