#include <signal.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include "myTerm.h"
#include <iostream>

using namespace std;

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
	catch(...){
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
	catch(...){
		return -1;
	}
}

int mt_setfgcolor (colors color)
{
	try{
	printf("\e[4%dm",color);
	return 0;
	}
	catch(...){
		return -1;
	}
}

int mt_setbgcolor (colors color)
{
	try{
	printf("\e[3%dm", color);
	return 0;
	}
	catch(...){
		return -1;
	}
}
