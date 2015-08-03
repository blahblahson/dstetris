#include "config.h"
#include <nds.h>
#include <stdio.h>

// todo: better error checking

void LoadConfig(CONFIG *config)
{
    FILE *f = fopen("dstetris.conf", "r");
    if(!f) {
        config->level = 20;
        config->linc = 10;
        config->infinity = 40;
        config->das = 30;
        config->sspeed = 128;
        config->rseed = 7525;
        WriteConfig(config);
    }
    else {
        fread(config, 1, sizeof(CONFIG), f);
        fclose(f);
    }
}

void WriteConfig(const CONFIG *config)
{
    FILE *f = fopen("dstetris.conf", "w+");
    fwrite(config, 1, sizeof(CONFIG), f);
    fflush(f);
    fclose(f);
}
