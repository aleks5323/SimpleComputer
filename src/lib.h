#ifndef lib_H
#define lib_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sc_memoryInit();
void flagsView();
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int * value);
int sc_regInit();
int sc_memorySave (char * filename);
int sc_memoryLoad (char * filename);
int sc_regSet (int reg, int value);
int sc_regGet (int reg, int * value);
int sc_commandEncode (int command, int operand, int * value);
int sc_commandDecode (int value, int * command, int * operand);

#endif
