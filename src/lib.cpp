#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "lib.h"
#define OVERFILL_MASK 0x01			//шестнадцатеричный литерал для 0000 0001
#define ZERO_MASK 0x02				//шестнадцатеричный литерал для 0000 0010
#define OUT_OF_MEMORY_MASK 0x04 	//шестнадцатеричный литерал для 0000 0100
#define IMPULSE_IGNORE_MASK 0x08 	//шестнадцатеричный литерал для 0000 1000
#define CMD_ERROR_MASK 0x10 		//шестнадцатеричный литерал для 0001 0000
#define bits(of) (int)sizeof(of)*CHAR_BIT

#define ANSI_COLOR_GREEN   "\x1b[32m" //Delete this later
#define ANSI_COLOR_YELLOW  "\x1b[33m" //Delete this later
#define ANSI_COLOR_RED     "\x1b[31m" //Delete this later
#define ANSI_COLOR_RESET   "\x1b[0m" //Delete this later

const int N = 100;
int ram[N-1];
unsigned char flags;

int sc_memoryInit ()
{
	for (int i = 0; i < N; i++)
	{
		ram[i] = 0;
	}
	printf(ANSI_COLOR_GREEN "Memory has been successfully initialized.\n" ANSI_COLOR_RESET); //Delete this line later
	return 0;
}

void flagsView()
{
	printf("Flags: ");
	for (int j= bits(flags); j>=1 ; j--)
	{
		printf("%d", (flags>>(j-1))& 0x1);
	}
	printf("\n");
}

int sc_memorySet (int address, int value)
{
	if (address < N && address >= 0)
	{
		ram[address] = value;
		printf("Ja GUT: [%d] => %d\n", address, ram[address]);
		return 0;
	}
	else
	{
		flags|=OUT_OF_MEMORY_MASK;
		printf(ANSI_COLOR_RED);											//Color
		printf("Out of range: [%d] \u2260> [%d]\n", value, address); 	//Color
		printf(ANSI_COLOR_RESET);										//Color
		return 1;
	}
	return 0;
}

int sc_memoryGet (int address, int * value)
{
	if (address < N && address >= 0)
	{
		*value = ram[address];
		return 0;
	}
	else
	{
		flags|=OUT_OF_MEMORY_MASK;
		printf(ANSI_COLOR_RED "Out of range\n" ANSI_COLOR_RESET); //Color
		return 1;
	}
	return 0;
}

int sc_regInit()
{
	flags&=0x0;
	printf(ANSI_COLOR_GREEN "Registers has been successfully initialized.\n" ANSI_COLOR_RESET); //Delete this line later
	return 0;
}

int sc_memorySave (char * filename)
{
	FILE *f = fopen(filename, "wb");
	
	if (f == NULL)
	{
		printf(ANSI_COLOR_RED "Error opening file for writing\n" ANSI_COLOR_RESET); //Color
		return 1;
	}
	fwrite(ram, 1, sizeof(ram), f);
	printf(ANSI_COLOR_YELLOW "Memory has been successfully saved\n" ANSI_COLOR_RESET);
	fclose (f);
	return 0;
}

int sc_memoryLoad (char * filename)
{
	FILE *f = fopen(filename, "rb");
	
	if (f == NULL)
	{
		printf(ANSI_COLOR_RED "Error opening file for reading\n" ANSI_COLOR_RESET); //Color
		return 1;
	}
	
	fread(ram, 1, sizeof(ram), f);
	printf(ANSI_COLOR_YELLOW "Memory has been successfully loaded\n" ANSI_COLOR_RESET);
	fclose (f);
	return 0;
}

int sc_regSet (int reg, int value)
{
	if (value > 1 || value < 0)
	{
		printf(ANSI_COLOR_RED "Incorrect value\n" ANSI_COLOR_RESET); //Color
		return 1;
	}
	else{
		switch(reg){
			case 1:{
				if(value==1)
					flags|=OVERFILL_MASK;
					else
						flags&=~OVERFILL_MASK;
				break;
			}
			case 2:{
				if(value==1)
					flags|=ZERO_MASK;
					else
						flags&=~ZERO_MASK;
				break;
			}
			case 3:{
				if(value==1)
					flags|=OUT_OF_MEMORY_MASK;
					else
						flags&=~OUT_OF_MEMORY_MASK;
				break;
			}
			case 4:{
				if(value==1)
					flags|=IMPULSE_IGNORE_MASK;
					else
						flags&=~IMPULSE_IGNORE_MASK;
				break;
			}
			case 5:{
				if(value==1)
					flags|=CMD_ERROR_MASK;
					else
						flags&=~CMD_ERROR_MASK;
				break;
			}
			default:{
				printf(ANSI_COLOR_RED "Incorrect register number\n" ANSI_COLOR_RESET); //Color
				return 1;
				break;
			}
		}
	return 0;	
	}
	return 0;
}

int sc_regGet (int reg, int * value)
{
	if ((reg <=0) || reg > bits(flags))
	{
		printf(ANSI_COLOR_RED "Incorrect register number\n" ANSI_COLOR_RESET); //Color
		return 1;
	}
	*value = (flags >> (reg-1)) & 0x1;
	return 0;
}

int sc_commandEncode (int command, int operand, int * value)
{
	if((command>=10 && command<=11)||(command>=20 && command<=21)||(command>=30 && command<=33)||(command>=40 && command<=43)||(command>=51 && command<=76)|| operand<=127)
	{
		*value=command;
		*value<<=(7);
		*value=*value^operand;
	}
	else {
		printf(ANSI_COLOR_RED "Error encoding command\n" ANSI_COLOR_RESET); //Color
		return 1;
	}
	return 0;
}

int sc_commandDecode (int value, int * command, int * operand)
{
	*operand=value&0x7F; 
	*command=(value&0x3F80)>>7; 
	if(!((*command>=10 && *command<=11)||(*command>=20 && *command<=21)||(*command>=30 && *command<=33)||(*command>=40 && *command<=43)||(*command>=51 && *command<=76)||((value>>14)==1))){
		flags=flags | (1<<(5-1));	
		printf(ANSI_COLOR_RED "Wrong command\n" ANSI_COLOR_RESET); //Color
		return 1;
	}
	return 0;
}
