#ifndef _ATTACK_H_

#define _ATTACK_H_

#include <ncurses.h>

struct point
{
    int y;
    int x;
};


struct at
{
    point curpos;
    point dir;
    int period;
    int tp;
    int bomb;
    chtype ch;
};


#endif