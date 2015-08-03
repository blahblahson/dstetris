#include <stdlib.h>
#include "block.h"
#include "game.h"
#include "occupation.h"
#include "fix.h"
#include "rotations.h"
#include "globals.h"
#include "blit.h"

/* observation - you can't call this in Game::Game(), so call it accordingly in
 * Game::Run() instead */
Block::Block()
{
    // always starts as a next block
    grid = Game::Instance()->GetGrid();
    context = BLOCK_NEXT; // refer to Game class
    type = RandBlock();
    Occupation::CopyFix(occupation, BLOCK_OCCUPATION[type][BLOCKPOS_0]);
    Occupation::AddY(occupation, FIX(2)); // move out of invisible area
    Occupation::SubtractX(occupation, FIX(2)); // move left since it's
                                                // initially centered
    position = BLOCKPOS_0;
    infinity = 0;
    pushing = false;
    inertia_len = Game::Instance()->config.das;
    sspeed = Game::Instance()->config.sspeed;
}

Block::~Block()
{
}

void Block::Spawn()
{
    context = BLOCK_CURRENT;
    Occupation::SubtractY(occupation, FIX(2)); // move back
    Occupation::AddX(occupation, FIX(2));

    if(grid->Obstruct(occupation))
        Game::Instance()->SetStatus(GAME_OVER);

    if(Game::Instance()->level == 20)
        Floor();
}

void Block::Update()
{
    // handle input, move block accordingly and such
    if(context == BLOCK_CURRENT) { // handle input
        // directional input
        // pressed
        int pressed = keysDown();
        if(pressed & KEY_RIGHT)
            Transform(FIX(1), 0);
        if(pressed & KEY_LEFT)
            Transform(FIX(-1), 0);
        if(pressed & KEY_UP)
            Transform(0, FIX(1));
        if(pressed & KEY_DOWN) {
            Floor();
            Lock();
        }

        // held
        int held = keysHeld();
        if(held & KEY_RIGHT)
            if(inertia > inertia_len)
                Transform(sspeed, 0);
        if(held & KEY_LEFT)
            if(inertia > inertia_len)
                Transform(-sspeed, 0);
        if(held & KEY_DOWN)
            if(inertia > inertia_len)
                Transform(0, sspeed);

        if(pressed & KEY_A)
            Rotate(ROTATE_CLOCKWISE);
        if(pressed & KEY_B)
            Rotate(ROTATE_COUNTERCLOCKWISE);

        if(context == BLOCK_CURRENT && !grid->Floored(occupation) &&
                Game::Instance()->level == 20)
            Floor();

        if((held & (KEY_RIGHT | KEY_LEFT | KEY_UP | KEY_DOWN)) ||
                (pressed & (KEY_A | KEY_B)))
            if(inertia <= inertia_len) inertia++;
        else
            inertia = 0; // reset inertia

        if(infinity && (Game::Instance()->GetTicks() >= infinity))
            Lock();
    }

    Draw();
}

void Block::Draw()
{
    for(int i = 0; i < 4; i++) {
        // don't draw off-screen, only track it. manual check since
        // Occupation:: functions do not check for OOB upwards
        if(context == BLOCK_CURRENT && UNFIX(occupation[i].y) < 0)
            continue;

        // make current blocks slightly lighter
        /*if(context == BLOCK_CURRENT)
            ulSetImageTint(grid->img, BLOCK_TINT[type] | RGB15(15, 15, 15));
        else
            ulSetImageTint(grid->img, BLOCK_TINT[type]);*/

        // draw based on context
        if(context == BLOCK_CURRENT)
            BlitMain(BLOCKX(UNFIX(occupation[i].x)),
                    BLOCKY(UNFIX(occupation[i].y)), BLOCK_LIMAGE[type]);
        else {
            BlitMain(BLOCKX(UNFIX(occupation[i].x)),
                    BLOCKY(UNFIX(occupation[i].y)), BLOCK_IMAGE[type]);
            dsprintf(&pinfo, NBLOCKX(0), NBLOCKY(3), "NEXT BLOCK");
        }
    }
}

void Block::Rotate(BLOCK_ROTATE rtype)
{
    // make boop noise here

    // O doesn't rotate at all really
    if(type == BLOCK_O)
        return;

    SQUARE_LOCATION to[4];
    BLOCK_POSITION tp = position;

    Occupation::Copy(to, occupation);
    Occupation::SubtractFix(occupation, BLOCK_OCCUPATION[type][position]);

    if(rtype == ROTATE_CLOCKWISE)
        position = position == BLOCKPOS_270 ? BLOCKPOS_0 : ((BLOCK_POSITION)
                (position + 1));
    else // presumably ROTATE_COUNTERCLOCKWISE
        position = position == BLOCKPOS_0 ? BLOCKPOS_270 : ((BLOCK_POSITION)
                (position - 1));

    Occupation::AddFix(occupation, BLOCK_OCCUPATION[type][position]);

    if(Occupation::OutOfBounds(occupation) || grid->Obstruct(occupation)) {
        int r = false;
        switch(type) {
            case BLOCK_I:
                r = Rotation::I(tp, position, occupation, grid);
                break;
            case BLOCK_J:
                r = Rotation::J(tp, position, occupation, grid);
                break;
            case BLOCK_L:
                r = Rotation::L(tp, position, occupation, grid);
                break;
            case BLOCK_S:
                r = Rotation::S(tp, position, occupation, grid);
                break;
            case BLOCK_Z:
                r = Rotation::Z(tp, position, occupation, grid);
                break;
            case BLOCK_T:
                r = Rotation::T(tp, position, occupation, grid);
            default:
                break;
        }

        if(!r) {
            Occupation::Copy(occupation, to);
            position = tp;
        }
    }

    /* by this point, if it could have been rotated it will have been,
     * otherwise it will remain the same (by subsequent trial and error
     * transformations and checks) */

    if(grid->Floored(occupation)) {
        if(!Occupation::Compare(to, occupation))
            infinity = Game::Instance()->GetTicks() +
                Game::Instance()->config.infinity;
    }
    else
        infinity = 0;

    // again, boop noise
}

// use negatives for negative transformation
void Block::Transform(int x, int y)
{
    if(context == BLOCK_NEXT)
        return;

    if(grid->Floored(occupation) && y) { // if already floored and attempted y
                                        // transformation
        if(Game::Instance()->GetTicks() >= infinity -
                (Game::Instance()->config.infinity/2))
            Lock();

        return;
    }

    Occupation::AddXY(occupation, x, y);
    if(Occupation::OutOfBounds(occupation) || grid->Obstruct(occupation)) {
        Occupation::SubtractXY(occupation, x, y);
        pushing = true;
    }
    else
        pushing = false;

    if(grid->Floored(occupation)) {
        if(!pushing)
            infinity = Game::Instance()->GetTicks() +
                Game::Instance()->config.infinity;
    }
    else
        infinity = 0;
    // maybe make a boop noise here
}

// register block occupation with the grid, delete self and call
// Game::Instance()->PumpBlocks()
void Block::Lock()
{
    grid->Overlay(occupation, type);
    delete this;
    Game::Instance()->PumpBlocks();
}

void Block::Floor()
{
    while(!grid->Floored(occupation))
        Transform(0, 1);
}

// pick a block from a bag
// somewhat inefficient right now, fix later
// also not random enough
BLOCK_TYPE Block::RandBlock()
{
    static BLOCK_TYPE bag[7];
    static int pos = -1;

    if(pos == -1) { // empty bag
        // fill it
        for(int i = 0; i < 7; i++) {
            bag[i] = (BLOCK_TYPE) (rand() % 7);
            
            for(int j = 0; i != 7 && j < i; j++)
                while(bag[j] == bag[i])
                    bag[i] = (BLOCK_TYPE) (rand() % 7);
        }

        pos = 6;
    }

    Game::Instance()->config.rseed = (unsigned int) rand();

    return bag[pos--];
}
