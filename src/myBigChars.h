#ifndef myBigChars_H
#define myBigChars_H
#include "myTerm.h"

#define D_ZERO	{0x2424243C, 0x3C242424}
#define D_ONE	{0x18181818, 0x18181818}
#define D_TWO	{0x2020203C, 0x3C04043C}
#define D_THREE	{0x2020203C, 0x03C20203C}
#define D_FOUR	{0x3C242424, 0x20202020}
#define D_FIVE	{0x404043C, 0x03C20203C}
#define D_SIX	{0x404043C, 0x3C24243C}
#define D_SEVEN	{0x2020203C, 0x20202020}
#define D_EIGHT	{0x3C24243C, 0x3C242424}
#define D_NINE	{0x3C24243C, 0x3C202020}
#define D_A		{0x24242418, 0x2424243C}
#define D_B		{0x1C24241C, 0x1C24241C}
#define D_C		{0x404043C, 0x3C040404}
#define D_D		{0x2424241C, 0x1C242424}
#define D_E		{0x3C04043C, 0x3C040404}
#define D_F		{0x404043C, 0x404043C}
#define D_G		{0x4040438, 0x1C242434}
#define D_PLUS	{0x7E181800, 0x18187E}

int bc_printA (char * str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(int *big, int x, int y,colors fgcolor, colors bgcolor);
int bc_setbigcharpos(int *big, int x, int y, int value);
int bc_getbigcharpos(int *big, int x, int y, int *value);
int bc_bigcharwrite(int fd, int *big, int count);
int bc_bigcharread(int fd, int *big, int need_count, int *count);
#endif
