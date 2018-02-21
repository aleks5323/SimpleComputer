#include <sys/ioctl.h>
#include <stdio.h>
#include "myTerm.h"

void mt_clrscr (void)
{
	printf("\e[H\E[J");
}

int mt_gotoXY (int row, int col)
{
	printf("\e[%d;%dH", row, col);
	return 0;
}

int mt_getscreensize (int * rows, int * cols)
{
	struct winsize w;
	
	ioctl(1, TIOCGWINSZ, &w);
	*rows = w.ws_row;
	*cols = w.ws_col;
	return 0;
}
