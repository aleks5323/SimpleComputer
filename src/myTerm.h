#ifndef myTerm_H
#define myTerm_H

void mt_clrscr (void);
int mt_gotoXY (int row, int col);
int mt_getscreensize (int * rows, int * cols);
int mt_setfgcolor (enum colors);
int mt_setbgcolor (enum colors);
#endif
