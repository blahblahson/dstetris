#include <nds.h>
#include <stdio.h>
#include "menu.h"
#include "game.h"
#include "version.h"
#include "config.h"
#include "globals.h"

void Menu::Main()
{
    // clear bottom screen
    consoleClear();
    printf("test A\n");
    ClearVideoMain();
    printf("test\n");

    dsprintf(&pinfo, SCREENWIDTH/2 - pinfo.w*strlen("DSTETRIS")/2,
            SCREENHEIGHT/2, "DSTETRIS");

    printf("\n DSTETRIS\n ________\n\n"
            " A      - PLAY\n"
            " START  - CONFIGURATION\n"
            " SELECT - INFORMATION");

    while(1) {
        swiWaitForVBlank();
        scanKeys();
        int pressed = keysDown();

        if(pressed & KEY_A) {
            consoleClear();

            while(1) {
                Game *game = Game::Instance();
                int n = game->Run();
                delete game;
                if(n != EXIT_RESTART) break;
            }

            break;
        }
        else if(pressed & KEY_START) {
            Configuration();
            break;
        }
        else if(pressed & KEY_SELECT) {
            Info();
            break;
        }
    }
}

void Menu::Info()
{
    // clear both screens
    consoleClear();
    ClearVideoMain();

    printf("\n INFORMATION\n ___________\n\n"
            " DSTETRIS VERSION %d.%d.%d\n\n"
            " AUTHORS\n"
            "   Alvin Sipraga\n"
            "    <sipraga@digital-haze.net>\n\n"
            " LIBRARIES\n"
            "   libnds\n\n"
            " COMPILED\n"
            "   %s %s\n\n\n"
            " http://digital-haze.net/\n\n ___________\n\n"
            " A/START - MAIN MENU", VERSION_MAJOR, VERSION_MINOR,
            VERSION_REVISION, __DATE__, __TIME__);

    while(1) {
        swiWaitForVBlank();
        scanKeys();
        int pressed = keysDown();

        if(pressed & (KEY_A | KEY_START))
            return;
    }
}

void Menu::Configuration()
{
    CONFIG config;
    LoadConfig(&config);

    while(1) {
        // clear both screens
        consoleClear();
        ClearVideoMain();

        printf("\n CONFIGURATION\n _____________\n\n"
                " A      - LEVEL\n"
                " B      - LEVEL INCREMENT\n"
                " X      - INFINITY\n"
                " Y      - DELAYED AUTO SHIFT\n"
                " L      - SHIFT SPEED\n"
                " R      - RANDOM SEED\n\n"
                " START  - SAVE & RETURN\n"
                " SELECT - DON'T SAVE & RETURN");

        while(1) {
            swiWaitForVBlank();
            scanKeys();
            int pressed = keysDown();

            if(pressed & KEY_A) {
                config.level = Level(config.level);
                break;
            }
            else if(pressed & KEY_B) {
                config.linc = LevelIncrement(config.linc);
                break;
            }
            else if(pressed & KEY_X) {
                config.infinity = Infinity(config.infinity);
                break;
            }
            else if(pressed & KEY_Y) {
                config.das = DAS(config.das);
                break;
            }
            else if(pressed & KEY_L) {
                config.sspeed = ShiftSpeed(config.sspeed);
                break;
            }
            else if(pressed & KEY_R) {
                config.rseed = RandSeed(config.rseed);
                break;
            }
            else if(pressed & KEY_START) {
                WriteConfig(&config);
                return;
            }
            else if(pressed & KEY_SELECT)
                return;
        }
    }
}

unsigned short int Menu::Level(unsigned short int level)
{
    int ilevel = level;

    while(1) {
        // clear both screens
        consoleClear();
        ClearVideoMain();

        printf("\n LEVEL\n _____\n\n"
                " LEVEL (1-20) = %d\n\n"
                " L      - DECREMENT\n"
                " R      - INCREMENT\n\n"
                " START  - SAVE & RETURN\n"
                " SELECT - DON'T SAVE & RETURN", level);

        while(1) {
            swiWaitForVBlank();
            scanKeys();
            int pressed = keysDown();
            int held = keysHeld();

            if((pressed | held) & KEY_L && level > 1) {
                level--;
                break;
            }
            else if((pressed | held) & KEY_R && level < 20) {
                level++;
                break;
            }
            else if(pressed & KEY_START)
                return level;
            else if(pressed & KEY_SELECT)
                return ilevel;
        }
    }

    return 0;
}

unsigned short int Menu::LevelIncrement(unsigned short int linc)
{
    int ilinc = linc;

    while(1) {
        // clear both screens
        consoleClear();
        ClearVideoMain();

        printf("\n LEVEL INCREMENT\n _______________\n\n"
                " LEVEL INCREMENT (1-100) = %d\n\n"
                " L      - DECREMENT\n"
                " R      - INCREMENT\n\n"
                " START  - SAVE & RETURN\n"
                " SELECT - DON'T SAVE & RETURN", linc);

        while(1) {
            swiWaitForVBlank();
            scanKeys();
            int pressed = keysDown();
            int held = keysHeld();

            if((pressed | held) & KEY_L && linc > 1) {
                linc--;
                break;
            }
            else if((pressed | held) & KEY_R && linc < 100) {
                linc++;
                break;
            }
            else if(pressed & KEY_START)
                return linc;
            else if(pressed & KEY_SELECT)
                return ilinc;
        }
    }

    return 0;
}

unsigned int Menu::Infinity(unsigned int inf)
{
    int iinf = inf;

    while(1) {
        // clear both screens
        consoleClear();
        ClearVideoMain();

        printf("\n INFINITY\n ________\n\n"
                " INFINITY (0-600) = %d\n\n"
                " L      - DECREMENT\n"
                " R      - INCREMENT\n\n"
                " START  - SAVE & RETURN\n"
                " SELECT - DON'T SAVE & RETURN", inf);

        while(1) {
            swiWaitForVBlank();
            scanKeys();
            int pressed = keysDown();
            int held = keysHeld();

            if((pressed | held) & KEY_L && inf > 1) {
                inf--;
                break;
            }
            else if((pressed | held) & KEY_R && inf < 600) {
                inf++;
                break;
            }
            else if(pressed & KEY_START)
                return inf;
            else if(pressed & KEY_SELECT)
                return iinf;
        }
    }

    return 0;
}

unsigned int Menu::DAS(unsigned int das)
{
    int idas = das;

    while(1) {
        // clear both screens
        consoleClear();
        ClearVideoMain();

        printf("\n DELAY AFTER SHIFT\n _________________\n\n"
                " DAS (0-600) = %d\n\n"
                " L      - DECREMENT\n"
                " R      - INCREMENT\n\n"
                " START  - SAVE & RETURN\n"
                " SELECT - DON'T SAVE & RETURN", das);

        while(1) {
            swiWaitForVBlank();
            scanKeys();
            int pressed = keysDown();
            int held = keysHeld();

            if((pressed | held) & KEY_L && das > 1) {
                das--;
                break;
            }
            else if((pressed | held) & KEY_R && das < 600) {
                das++;
                break;
            }
            else if(pressed & KEY_START)
                return das;
            else if(pressed & KEY_SELECT)
                return idas;
        }
    }

    return 0;
}

unsigned int Menu::ShiftSpeed(unsigned int sspeed)
{
    int isspeed = sspeed;

    while(1) {
        // clear both screens
        consoleClear();
        ClearVideoMain();

        printf("\n SHIFT SPEED (WHEN HELD)\n _______________________\n\n"
                " DAS (1-512) = %d\n\n"
                " L      - DECREMENT\n"
                " R      - INCREMENT\n\n"
                " START  - SAVE & RETURN\n"
                " SELECT - DON'T SAVE & RETURN", sspeed);

        while(1) {
            swiWaitForVBlank();
            int pressed = keysDown();
            int held = keysHeld();

            if((pressed | held) & KEY_L && sspeed > 1) {
                sspeed--;
                break;
            }
            else if((pressed | held) & KEY_R && sspeed < 512) {
                sspeed++;
                break;
            }
            else if(pressed & KEY_START)
                return sspeed;
            else if(pressed & KEY_SELECT)
                return isspeed;
        }
    }

    return 0;
}

unsigned int Menu::RandSeed(unsigned int rseed)
{
    int irseed = rseed;

    while(1) {
        // clear both screens
        consoleClear();
        ClearVideoMain();

        printf("\n RANDOM SEED\n ___________\n\n"
                " SEED (0-4294967295) = %d\n\n"
                " L      - DECREMENT\n"
                " R      - INCREMENT\n\n"
                " START  - SAVE & RETURN\n"
                " SELECT - DON'T SAVE & RETURN", rseed);

        while(1) {
            swiWaitForVBlank();
            int pressed = keysDown();
            int held = keysHeld();

            if((pressed | held) & KEY_L) {
                rseed-= 41;
                break;
            }
            else if((pressed | held) & KEY_R) {
                rseed+= 97;
                break;
            }
            else if(pressed & KEY_START)
                return rseed;
            else if(pressed & KEY_SELECT)
                return irseed;
        }
    }

    return 0;
}
