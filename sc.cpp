#include <stdio.h>
#include <stdlib.h>
const int N = 100;

int ram[N-1];
int flags;
unsigned char k = 1;
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
	for (int j=1; j < 32; j++)
	{
		printf("%d", flags>>(j-1));
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
	for (int j=1; j < 32; j++)
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

/*int sc_regSet (int register, int value)
{
	if ()
}*/

int sc_regGet (int reg, int * value)
{
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
	
	
	
	printf("\n");
	return 0;
}
