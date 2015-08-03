#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "blocktype.h"
#include "grid.h"
#include "gfxloc.h"

/* todo: make this more random */
#define RANDBLOCK ((rand() % 7) + 1)

/* delay (in 1/60 seconds) where block moves slower than normal with key-press */
#define BLOCK_INERTIA 20

/* infinity, also in 1/60 seconds */
#define BLOCK_INFINITY 40

/* block contexts - 'next' blocks ignore boundary rules while current blocks
 * are maintained inside the grid and can be rotated, moved, etc.; current
 * blocks abide by boundary rules and other transformation rules */
typedef enum {
    BLOCK_CURRENT,
    BLOCK_NEXT
} BLOCK_CONTEXT;

typedef enum {
    ROTATE_CLOCKWISE = 0,
    ROTATE_COUNTERCLOCKWISE,
    ROTATE_CLOCK = 0,
    ROTATE_CCLOCK = 1
} BLOCK_ROTATE;

class Block {
    public:
        Block();
        ~Block();
        void Spawn(); // context: BLOCK_NEXT -> BLOCK_CURRENT
        void Update();
        void Draw();
        void Rotate(BLOCK_ROTATE);
        void Transform(int, int);
        void Lock();
        void Floor();

        static BLOCK_TYPE RandBlock();

    private:
        Grid *grid;
        BLOCK_CONTEXT context;
        BLOCK_TYPE type;
        SQUARE_LOCATION occupation[4]; // occupied area, negative handled
                                        // but not drawn
        BLOCK_POSITION position;

        // various internal stuff
        int inertia;
        unsigned int infinity;
        bool pushing;

        int inertia_len;
        int sspeed;
} ;

#endif /* _BLOCK_H_ */
