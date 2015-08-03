#ifndef _GAME_H_
#define _GAME_H_

#include "block.h"
#include "grid.h"
#include "menu.h"
#include "config.h"

#define SCREENWIDTH 256
#define SCREENHEIGHT 192

typedef enum {
    GAME_RUNNING = 0,
    GAME_PAUSED,
    GAME_OVER
} GAME_STATUS;

class Game {
    public:
        ~Game();
        static Game *Instance();
        EXIT_STATUS Run();
        void PumpBlocks();
        EXIT_STATUS PauseScreen();
        EXIT_STATUS OverScreen();
        void Draw();

        inline void SetStatus(GAME_STATUS s) { status = s; };
        inline unsigned int GetTicks() { return ticks; };
        inline Grid *GetGrid() { return grid; };
        inline Block *GetCBlock() { return cblock; };
        inline Block *GetNBlock() { return nblock; };

        CONFIG config;
        int level;
        unsigned int clearedlines;
        unsigned int score;

    private:
        static Game *_instance;
        Grid *grid;
        Block *cblock; // current block
        Block *nblock; // next block

        unsigned int ticks;
        GAME_STATUS status;

    protected:
        Game();
} ;

#endif /* _GAME_H_ */
