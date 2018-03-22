#ifndef myTerm_H
#define myTerm_H

#include <signal.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <iostream>

enum colors {black, red, green, yellow, blue, purple, aquamarine, white, clr_default};
void mt_clrscr (void);
int mt_gotoXY (int row, int col);
int mt_getscreensize (int * rows, int * cols);
int mt_setfgcolor (colors color);
int mt_setbgcolor (colors color);

#endif
