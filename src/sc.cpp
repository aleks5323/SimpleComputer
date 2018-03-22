#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "myBigChars.h"
int value;
extern int ram[99];

void printBoxes()
{
	bc_box(1, 1, 12, 62);
	bc_box(1, 63, 3, 68);
	bc_box(4, 63, 3, 68);
	bc_box(7, 63, 3, 68);
	bc_box(10, 63, 3, 68);
	bc_box(13, 1, 10, 47);
	bc_box(13, 48, 10, 80);
}

void printLabels()
{
	mt_gotoXY(1, 28);
	printf("Memory");
	mt_gotoXY(1, 66);
	printf("accumulator");
	mt_gotoXY(4, 66);
	printf("instrCount");
	mt_gotoXY(7, 67);
	printf("Operation");
	mt_gotoXY(10, 68);
	printf("Flags");
	mt_gotoXY(13, 50);
	printf("Keys:");
}

void printMemory()
{
	int x=2;
	mt_gotoXY(x,2);
	for (int i=0; i<10; i++)
	{
		for (int j=0; j<10; j++)
		{
			printf("+%.4d ", ram[i*10+j]);
		}
		mt_gotoXY(++x, 2);
	}
}

int main()
{
	sc_memoryInit();
	sc_regInit();
	
	printBoxes();
	printLabels();
	printMemory();
	mt_gotoXY(24, 1);
	
	return 0;
}
