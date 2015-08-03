#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "text.h"
#include "globals.h"

Game* Game::_instance = 0;

Game::Game()
{
    grid = new Grid;
    LoadConfig(&config);
    srand(config.rseed);
    clearedlines = 0;
    score = 0;
    level = config.level;
}

Game::~Game()
{
    delete cblock;
    delete nblock;
    delete grid;

    _instance = NULL;
}

Game* Game::Instance()
{
    if(_instance == NULL)
        _instance = new Game;
    return _instance;
}

EXIT_STATUS Game::Run()
{
    // initial setup
    nblock = new Block;
    cblock = new Block;
    cblock->Spawn();

    ticks = 0;
    status = GAME_RUNNING;

    while(1) {
        swiWaitForVBlank();
        ++ticks;

        // I should change this
        if(ticks % 600)
            WriteConfig(&config);

        if((clearedlines % config.linc) && level != 20)
            level++;

        switch(status) {
            case GAME_PAUSED:
                switch(PauseScreen()) {
                    case EXIT_NORMAL:
                        break;
                    case EXIT_RESTART:
                        return EXIT_RESTART;
                    case EXIT_MAINMENU:
                        return EXIT_MAINMENU;
                    default:
                        break;
                }

                status = GAME_RUNNING;
                break;
                
            case GAME_OVER:
                return OverScreen();

            default:
                break;
        }


        scanKeys();
        int pressed = keysDown();

        if(pressed & KEY_START) {
            status = GAME_PAUSED;
            continue;
        }

        nblock->Update();
        cblock->Update();
        grid->Update();
        Draw();

        if(config.level != 20 && !(ticks % ((20 - config.level)*5)))
            cblock->Transform(0, FIX(1));
    }
}

void Game::PumpBlocks()
{
    // should be called by cblock, and cblock should delete itself
    cblock = nblock;
    cblock->Spawn();
    nblock = new Block;
}

EXIT_STATUS Game::PauseScreen()
{
    /*ulStartDrawing2D();
    ulDrawString(SCREENWIDTH/2 - ulGetStringWidth("PAUSE")/2,
            SCREENHEIGHT/2, "PAUSE");
    ulEndDrawing();*/
    dsprintf(&pinfo, SCREENWIDTH/2 - TEXTLEN(pinfo, "PAUSE")/2, SCREENHEIGHT/2,
            "PAUSE");

    consoleClear();
    printf("\n PAUSE\n _____\n\n"
            " START  - UNPAUSE\n"
            " SELECT - RESTART\n"
            " L+R    - MAIN MENU");

    while(1) {
        swiWaitForVBlank();
        scanKeys();
        int pressed = keysDown();
        int held = keysHeld();

        if(pressed & KEY_START) {
            consoleClear();
            return EXIT_NORMAL;
        }
        else if(pressed & KEY_SELECT) {
            consoleClear();
            return EXIT_RESTART;
        }
        else if(((pressed | held) & KEY_R) && ((pressed | held) & KEY_L)) {
            consoleClear();
            return EXIT_MAINMENU;
        }
    }
}

EXIT_STATUS Game::OverScreen()
{
    grid->GameOver();

    consoleClear();
    printf("\n GAME OVER\n _________\n\n"
            " START  - MAIN MENU\n"
            " SELECT - RESTART");
    
    while(1) {
        swiWaitForVBlank();
        scanKeys();
        int pressed = keysDown();

        if(pressed & KEY_START) {
            consoleClear();
            return EXIT_MAINMENU;
        }
        else if(pressed & KEY_SELECT) {
            consoleClear();
            return EXIT_RESTART;
        }
    }
}

void Game::Draw()
{
    dsprintf(&pinfo, SCORE_POS_X, SCORE_POS_Y, "%d", score);
    dsprintf(&pinfo, SCORE_POS_X, SCORE_POS_Y+10, "SCORE");

    dsprintf(&pinfo, CLEAREDLINES_POS_X, CLEAREDLINES_POS_Y, "%d",
            clearedlines);
    dsprintf(&pinfo, CLEAREDLINES_POS_X, CLEAREDLINES_POS_Y+10, "LINES");
}
