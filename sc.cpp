#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define OVERFILL_MASK 0x01			//шестнадцатеричный литерал для 0000 0001
#define ZERO_MASK 0x02				//шестнадцатеричный литерал для 0000 0010
#define OUT_OF_MEMORY_MASK 0x04 	//шестнадцатеричный литерал для 0000 0100
#define IMPULSE_IGNORE_MASK 0x08 	//шестнадцатеричный литерал для 0000 1000
#define CMD_ERROR_MASK 0x10 		//шестнадцатеричный литерал для 0001 0000
#define bits(of) (int)sizeof(of)*CHAR_BIT

const int N = 100;

int ram[N-1];
unsigned char flags;
unsigned char k = 3;
int value;

int sc_memoryInit ()
{
	for (int i = 0; i < N; i++)
	{
		ram[i] = 0;
	}
	return 0;
}

void flagsView()
{
	for (int j=1; j <= bits(flags); j++)
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
		printf("Ja GUT: %d\n", ram[address]);
		return 0;
	}
	else
	{
		flags=flags | (1<<(k-1));
		printf("Out of range\n");
		return 1;
	}
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
		flags=flags | (1<<(k-1));
		printf("Out of range\n");
		return 1;
	}
}

int sc_regInit()
{
	for (int j=1; j <= bits(flags); j++)
	{
		flags = flags>>(j-1)&0x0;
	}
	return 0;
}

int sc_memorySave (char * filename)
{
	FILE *f = fopen(filename, "wb");
	
	if (f == NULL)
	{
		printf("Error opening file for writing");
		exit(1);
	}
	
	fwrite(ram, 1, sizeof(ram), f);
	fclose (f);
	
	return 0;
}

int sc_memoryLoad (char * filename)
{
	FILE *f = fopen(filename, "rb");
	
	if (f == NULL)
	{
		printf("Error opening file for reading");
		exit(1);
	}
	
	fread(ram, 1, sizeof(ram), f);
	fclose (f);
	
	return 0;
}

int sc_regSet (int reg, int value)
{
	if (value > 1 || value < 0)
	{
		printf("Incorrect value");
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
				printf("Incorrect register number");
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
		printf("Incorrect register number");
		
	}
	*value = (flags >> (reg-1)) & 0x1;
	return 0;
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
	
	
	/*sc_memorySave((char*)"memory.dat");
	sc_memoryInit();
	sc_memoryGet(10, &value);
	printf("%d ", value);
	sc_memoryGet(20, &value);
	printf("%d ", value);
	sc_memoryGet(15, &value);
	printf("%d ", value);
	sc_memoryLoad((char*)"memory.dat");
	sc_memoryGet(10, &value);
	printf("%d ", value);
	sc_memoryGet(20, &value);
	printf("%d ", value);
	sc_memoryGet(15, &value);
	printf("%d ", value);*/
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
	
	printf("\n");
	return 0;
}
