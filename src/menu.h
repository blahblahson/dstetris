#ifndef _MENU_H_
#define _MENU_H_

#define HOLD_DELAY 40

typedef enum {
    EXIT_NORMAL = 0,
    EXIT_RESTART,
    EXIT_MAINMENU
} EXIT_STATUS;

namespace Menu {
    void Main();
    void Info();
    void Configuration();
    unsigned short int Level(unsigned short int);
    unsigned short int LevelIncrement(unsigned short int);
    unsigned int Infinity(unsigned int);
    unsigned int DAS(unsigned int);
    unsigned int ShiftSpeed(unsigned int);
    unsigned int RandSeed(unsigned int);
}

#endif /* _MENU_H_ */
