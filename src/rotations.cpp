#include "rotations.h"

#define OOBCHECK (!Occupation::OutOfBounds(occupation) && \
        !grid->Obstruct(occupation))

bool Rotation::I(BLOCK_POSITION tp, BLOCK_POSITION position, SQUARE_LOCATION
        *occupation, Grid *grid)
{
    if(tp == BLOCKPOS_90 && position == BLOCKPOS_0) {
        Occupation::AddX(occupation, FIX(2));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(-3));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(3), FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(-3), FIX(3));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_270 && position == BLOCKPOS_0) {
        Occupation::AddX(occupation, FIX(-2));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(3));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(-3), FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(3), FIX(3));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_180 && position == BLOCKPOS_90) {
        Occupation::AddX(occupation, FIX(-2));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(3));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(-3), FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(3), FIX(2));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_0 && position == BLOCKPOS_90) {
        Occupation::AddX(occupation, FIX(-2));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(3));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(-2));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(-3), FIX(-3));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_270 && position == BLOCKPOS_180) {
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(-3));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(3), FIX(-2));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(-3), FIX(3));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_90 && position == BLOCKPOS_180) {
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(3));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(-3), FIX(2));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(3), FIX(3));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_0 && position == BLOCKPOS_270) {
        Occupation::AddX(occupation, FIX(2));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(-3));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(-2));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(3), FIX(3));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_180 && position == BLOCKPOS_270) {
        Occupation::AddX(occupation, FIX(2));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(-3));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(3), FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(-3), FIX(2));
        if(OOBCHECK) return true;
    }
    
    return false;
}

bool Rotation::J(BLOCK_POSITION tp, BLOCK_POSITION position, SQUARE_LOCATION
        *occupation, Grid *grid)
{
    if(tp == BLOCKPOS_90 && position == BLOCKPOS_0) {
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(-1), FIX(-3));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_270 && position == BLOCKPOS_0) {
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(1), FIX(-3));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_180 && position == BLOCKPOS_90) {
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(1), FIX(3));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_0 && position == BLOCKPOS_90) {
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(1), FIX(3));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_270 && position == BLOCKPOS_180) {
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(1), FIX(-3));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_90 && position == BLOCKPOS_180) {
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(-1), FIX(-3));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_0 && position == BLOCKPOS_270) {
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(-1), FIX(3));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_180 && position == BLOCKPOS_270) {
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(-1), FIX(3));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
    }
    
    return false;
}

// exactly the same as J
bool Rotation::L(BLOCK_POSITION tp, BLOCK_POSITION position, SQUARE_LOCATION
        *occupation, Grid *grid)
{
    return J(tp, position, occupation, grid);
}

// also the same
bool Rotation::S(BLOCK_POSITION tp, BLOCK_POSITION position, SQUARE_LOCATION
        *occupation, Grid *grid)
{
    return J(tp, position, occupation, grid);
}

// and this
bool Rotation::Z(BLOCK_POSITION tp, BLOCK_POSITION position, SQUARE_LOCATION
        *occupation, Grid *grid)
{
    return J(tp, position, occupation, grid);
}

// some impossible moves, otherwise the same as J
bool Rotation::T(BLOCK_POSITION tp, BLOCK_POSITION position, SQUARE_LOCATION
        *occupation, Grid *grid)
{
    if(tp == BLOCKPOS_90 && position == BLOCKPOS_0) {
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(-1), FIX(-3));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_270 && position == BLOCKPOS_0) {
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(1), FIX(-3));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_180 && position == BLOCKPOS_90) {
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(-1));
        //if(OOBCHECK) return true; // impossible move
        Occupation::AddXY(occupation, FIX(1), FIX(3));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_0 && position == BLOCKPOS_90) {
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(1), FIX(3));
        //if(OOBCHECK) return true; // impossible move
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_270 && position == BLOCKPOS_180) {
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(1), FIX(-3));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(-1));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_90 && position == BLOCKPOS_180) {
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(-1), FIX(-3));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_0 && position == BLOCKPOS_270) {
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(-1));
        if(OOBCHECK) return true;
        Occupation::AddXY(occupation, FIX(-1), FIX(3));
        //if(OOBCHECK) return true; // impossible move
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
    }
    else if(tp == BLOCKPOS_180 && position == BLOCKPOS_270) {
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
        Occupation::AddY(occupation, FIX(-1));
        //if(OOBCHECK) return true; // impossible move
        Occupation::AddXY(occupation, FIX(-1), FIX(3));
        if(OOBCHECK) return true;
        Occupation::AddX(occupation, FIX(1));
        if(OOBCHECK) return true;
    }
    
    return false;
}

