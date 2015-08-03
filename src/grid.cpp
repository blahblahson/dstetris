#include "grid.h"
#include "blocktype.h"
#include "square.h"
#include "game.h"
#include "blit.h"
#include "imgdefs.h"
#include "globals.h"

Grid::Grid()
{
    //img = ulLoadImageFilePNG((const char *) square, (int) square_size,
    //        UL_IN_VRAM, UL_PF_PAL4);

    Clear();
}

Grid::~Grid()
{
    //ulDeleteImage(img);
}

void Grid::ClearLine(unsigned int y)
{
    Game::Instance()->clearedlines++;
    Game::Instance()->score += Game::Instance()->level * 100;

    if(y >= GRIDH)
        return;

    if(!y)
        for(int i = 0; i < GRIDW; i++)
            grid[i][y] = BLOCK_NONE;
    else
        for(unsigned int i = y; i > 0; i--)
            MoveLine(i-1, i);
}

void Grid::MoveLine(unsigned int source, unsigned int dest)
{
    if(source >= GRIDH || dest >= GRIDH)
        return;

    for(int i = 0; i < GRIDW; i++) {
        grid[i][dest] = grid[i][source];
        grid[i][source] = BLOCK_NONE;
    }
}

void Grid::Clear()
{
    for(int i = 0; i < GRIDW; i++)
        for(int j = 0; j < GRIDH; j++)
            grid[i][j] = BLOCK_NONE;

    for(int i = 0; i < GRIDW; i++)
        for(int j = 0; j < 2; j++)
            ngrid[i][j] = BLOCK_NONE;
}

void Grid::Update()
{
    CheckLines();
    Draw();
}

/* before calling this, call ulStartDrawing2D() */
void Grid::Draw()
{
    // draw border of grey squares
    //ulSetImageTint(img, RGB15(15, 15, 15));
    int o;
    for(o = 0; o <= GRIDH; o++)
        BlitMain(BLOCKX(0)-9, BLOCKY(o), (u16 *) square_border);
        //ulDrawImageXY(img, BLOCKX(0)-9, BLOCKY(o));
    o--;
    for(int i = 0; i <= GRIDW; i++)
        BlitMain(BLOCKX(i), BLOCKY(o), (u16 *) square_border);
        //ulDrawImageXY(img, BLOCKX(i), BLOCKY(o));
    for(; o >= 0; o--)
        BlitMain(BLOCKX(GRIDW), BLOCKY(o), (u16 *) square_border);
        //ulDrawImageXY(img, BLOCKX(GRIDW), BLOCKY(o));

    // draw grid
    for(int i = 0; i < GRIDW; i++) {
        for(int j = 0; j < GRIDH; j++) {
            if(grid[i][j] == BLOCK_NONE)
                continue;

            BlitMain(BLOCKX(i), BLOCKY(j), BLOCK_IMAGE[grid[i][j]]);
            //ulSetImageTint(img, BLOCK_TINT[grid[i][j]]);
            //ulDrawImageXY(img, BLOCKX(i), BLOCKY(j));
        }
    }
}

void Grid::CheckLines()
{
    for(int i = 0; i < GRIDH; i++) {
        for(int j = 0; j < GRIDW; j++) {
            if(grid[j][i] == BLOCK_NONE) break;
            if(j == GRIDW - 1) {
                ClearLine(i);
                // potential boop
            }
        }
    }
}

void Grid::GameOver()
{
    int ticks = 0;
    int line = 19;

    while(ticks < 60) {
        swiWaitForVBlank();
        if((ticks % 3) == 0) {
            // draw border of grey squares
            Draw();
            /*ulSetImageTint(img, RGB15(15, 15, 15));
            int o;
            for(o = 0; o <= GRIDH; o++)
                ulDrawImageXY(img, BLOCKX(0)-9, BLOCKY(o));
            o--;
            for(int i = 0; i <= GRIDW; i++)
                ulDrawImageXY(img, BLOCKX(i), BLOCKY(o));
            for(; o >= 0; o--)
                ulDrawImageXY(img, BLOCKX(GRIDW), BLOCKY(o));*/

            //ulSetImageTint(img, RGB15(8, 8, 8));
            for(int i = 19; i >= line; i--) {
                for(int j = 0; j < GRIDW; j++) {
                    if(grid[j][i] == BLOCK_NONE)
                        continue;
                    BlitMain(BLOCKX(j), BLOCKY(i), (u16 *) square_fill);
                    //ulDrawImageXY(img, BLOCKX(j), BLOCKY(i));
                }
            }

            // I have no idea how much this is needed, whatever
            // I'm half a sleep so sure, libdns go!
            for(int i = 0; i < line; i++) {
                for(int j = 0; j < GRIDW; j++) {
                    if(grid[j][i] == BLOCK_NONE)
                        continue;
                    BlitMain(BLOCKX(j), BLOCKY(i), BLOCK_IMAGE[grid[j][i]]);
                    //ulSetImageTint(img, BLOCK_TINT[grid[j][i]]);
                    //ulDrawImageXY(img, BLOCKX(j), BLOCKY(i));
                }
            }

            //ulEndDrawing();
            line--;
        }

        if(!line) {
            dsprintf(&pinfo, BLOCKX(GRIDW/2) - TEXTLEN(pinfo, "GAME OVER")/2,
                    BLOCKY(GRIDH/2), "GAME OVER");
            //ulDrawString(BLOCKX(GRIDW/2) - ulGetStringWidth("GAME OVER")/2,
            //        BLOCKY(GRIDH/2), "GAME OVER");
            break;
        }

        ticks++;
    }
}

// warning: this doesn't check for OOB x coordinates, although it's used where
// that shouldn't happen
bool Grid::Floored(SQUARE_LOCATION *subject)
{
    //printf("floor check for { (%d,%d), (%d,%d), (%d,%d), (%d,%d) }\n", subject[0].x, subject[0].y, subject[1].x, subject[1].y, subject[2].x, subject[2].y, subject[3].x, subject[3].y);
    for(int i = 0; i < 4; i++) {
        if((UNFIX(subject[i].y) + 1) >= GRIDH)
            return true; // on true floor
        // accommodate blocks that are above the view; this algorithm SHOULD
        // work even for queried occupations with top y-axis greater than or
        // equal to -2
        else if((UNFIX(subject[i].y) + 1) < 0) { // -1
            if(ngrid[UNFIX(subject[i].x)][(UNFIX(subject[i].y) * -1) - 2] !=
                    BLOCK_NONE) // n(x,0)
                return true;
        }
        else if(grid[UNFIX(subject[i].x)][UNFIX(subject[i].y) + 1] !=
                BLOCK_NONE) {
            return true;
        }
    }

    return false;
}

// literally overlay a given occupation to the grid (in other words, apply it).
// basically take every coordinate in subject and translate it to a locked-in
// grid piece
void Grid::Overlay(SQUARE_LOCATION *subject, BLOCK_TYPE type)
{
    // feeling lazy, but this should really check every coordinate for boundary
    // problems before overlaying
    for(int i = 0; i < 4; i++) {
        if(UNFIX(subject[i].y) < 0)
            ngrid[UNFIX(subject[i].x)][(UNFIX(subject[i].y) * -1) - 1] = type;
        else // positive
            grid[UNFIX(subject[i].x)][UNFIX(subject[i].y)] = type;
    }
}

bool Grid::Obstruct(SQUARE_LOCATION *subject)
{
    for(int i = 0; i < 4; i++) {
        if(UNFIX(subject[i].y) < 0) {
            if(ngrid[UNFIX(subject[i].x)][(UNFIX(subject[i].y) * -1) - 1] !=
                    BLOCK_NONE)
                return true;
        }
        else if(grid[UNFIX(subject[i].x)][UNFIX(subject[i].y)] != BLOCK_NONE)
            return true;
    }

    return false;
}

int Grid::ObstructWhere(SQUARE_LOCATION *subject)
{
    int ret = 0;

    for(int i = 0; i < 4; i++) {
        // this is horrible
        if((UNFIX(subject[i].y) < 0) ?
                (ngrid[UNFIX(subject[i].x)][(UNFIX(subject[i].y) * -1) - 1] !=
                 BLOCK_NONE) : (grid[UNFIX(subject[i].x)][UNFIX(subject[i].y)]
                     != BLOCK_NONE)) {
            if(Occupation::UpperMost(subject, i)) ret |= OOB_UP;
            if(Occupation::RightMost(subject, i)) ret |= OOB_RIGHT;
            if(Occupation::DownMost(subject, i))  ret |= OOB_DOWN;
            if(Occupation::LeftMost(subject, i))  ret |= OOB_LEFT;
        }
    }

    return ret;
}
