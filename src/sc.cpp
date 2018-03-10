#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "myBigChars.h"
int value;

void printBoxes()
{
	bc_box(1, 1, 12, 60);
	bc_box(1, 61, 3, 68);
	bc_box(4, 61, 3, 68);
	bc_box(7, 61, 3, 68);
	bc_box(10, 61, 3, 68);
}

void printLabels()
{
	mt_gotoXY(1, 28);
	printf("Memory");
	mt_gotoXY(1, 66);
	printf("accumulator");
	mt_gotoXY(4, 66);
	printf("instrCount");
	mt_gotoXY(7, 66);
	printf("Operation");
	mt_gotoXY(10, 66);
	printf("Flags");
}

int main()
{
	sc_memoryInit();
	sc_regInit();
	flagsView();
	
	sc_memorySet(10, 5);
	sc_memorySet(20, 10);
	sc_memorySet(15, 26);
	sc_memorySet(17, 31);
	sc_memorySet(13, 87);
	sc_memorySet(120, 1);
	flagsView();
	
	//Работа с чтением и записью памяти в файл
	
	sc_memorySave((char*)"memory.dat");
	sc_memoryInit();
	sc_memoryGet(10, &value);
	printf("%d ", value);
	sc_memoryGet(20, &value);
	printf("%d ", value);
	sc_memoryGet(15, &value);
	printf("%d \n", value);
	
	sc_memoryLoad((char*)"memory.dat");
	
	sc_memoryGet(10, &value);
	printf("%d ", value);
	sc_memoryGet(20, &value);
	printf("%d ", value);
	sc_memoryGet(15, &value);
	printf("%d \n", value);
	
	//==========================================
	
	sc_regSet (1, 1);
	flagsView();
	
	sc_regSet (1, 0);
	flagsView();
	 
	sc_regSet (5, 1);
	flagsView();
	
	sc_regSet (10, 0);
	flagsView();

	sc_regGet(1, &value);
	printf("%d\n", value);
	flagsView();
	sc_regInit();
	int value=5,command=5, operand=6;
	
	printf("\n============ENCODING AND DECODING============\n");
	sc_commandEncode (75, 6, &value);
	
	printf("Encoded command: ");
	for (int j= 15; j>=1 ; j--)
	{
		printf("%d", (value>>(j-1))& 0x1);
	}
	
	sc_commandDecode (value, &command, &operand);
	printf("\nDecoded command: ");
	printf("%d_%d\n",command, operand);
	flagsView();
	
	sc_commandEncode (10, 500, &value);
	sc_commandDecode (value, &command, &operand);
	printf("%d_%d\n",command, operand);
	flagsView();
	mt_clrscr();
	/*mt_gotoXY (5, 10);
	printf("Text at position 5 10\n");
	int rows, cols;
	mt_getscreensize (&rows, &cols);
	printf("Rows: %d\nCols: %d\n", rows, cols);
	mt_setfgcolor (white);
	mt_setbgcolor (aquamarine);
	printf("Aquamarine text on white backgroud\n");
	printf("\e[0m");*/
	
	//bc_printA ((char*)"l");
	bc_box(1, 1, 10, 10);
	//int big[2]={0x79858579,0x79858585};
	
	int big[2];
	int c;
	scanf("%d", &c);
	getCharCode(c, big);
	bc_printbigchar(big, 2, 2,red, white);
	mt_clrscr();
	
	printBoxes();
	printLabels();
	
	return 0;
}
