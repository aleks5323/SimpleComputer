#include <sys/ioctl.h>
#include <stdio.h>
#include "myTerm.h"

void mt_clrscr (void)
{
	printf("\e[H\E[J");
}

int mt_gotoXY (int row, int col)
{
	try{
		printf("\e[%d;%dH", row, col);
		return 0;
	}
	catch(){
		return -1;
	}
	
}

int mt_getscreensize (int * rows, int * cols)
{
	try{
		struct winsize w;	
	ioctl(1, TIOCGWINSZ, &w);
	*rows = w.ws_row;
	*cols = w.ws_col;
	return 0;
	}
	catch(){
		return -1;
	}
	
}

int mt_setfgcolor (enum colors)
{
		try{
		printf("\E[4%d%dm", colors);
		return 0;
	}
	catch(){
		return -1;
	}
}

int mt_setbgcolor (enum colors)
{
		try{
		printf("\E[3%d%dm", colors);
		return 0;
	}
	catch(){
		return -1;
	}
}
