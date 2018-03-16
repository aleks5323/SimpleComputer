#include "myBigChars.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int digits[18][2] = {
	{0x2424243C, 0x3C242424},	//D_ZERO
	{0x18181818, 0x18181818},	//D_ONE
	{0x2020203C, 0x3C04043C},	//D_TWO
	{0x2020203C, 0x03C20203C},	//D_THREE
	{0x3C242424, 0x20202020},	//D_FOUR
	{0x404043C, 0x03C20203C},	//D_FIVE
	{0x404043C, 0x3C24243C},	//D_SIX
	{0x2020203C, 0x20202020},	//D_SEVEN
	{0x3C24243C, 0x3C242424},	//D_EIGHT
	{0x3C24243C, 0x3C202020},	//D_NINE
	{0x24242418, 0x2424243C},	//D_A
	{0x1C24241C, 0x1C24241C},	//D_B
	{0x404043C, 0x3C040404},	//D_C
	{0x2424241C, 0x1C242424},	//D_D
	{0x3C04043C, 0x3C040404},	//D_E
	{0x404043C, 0x404043C},		//D_F
	{0x4040438, 0x1C242434},	//D_G
	{0x7E181800, 0x18187E}		//D_PLUS
};

int bc_printA (char * str)
{
    if(!str)
    	return -1;
   printf("\E(0%s\E(B", str);
    return 0;

}

int bc_box ( int x1, int y1, int x2, int y2 )
{
	for (int i = 0; i < x2; i++)
	{
		for (int j = 0; j < y2; j++)
		{
			mt_gotoXY(x1 + i, y1 + j);
			if (i == 0 && j == 0) bc_printA((char*)BOXCHAR_TL);
			else if (i == 0 && j == y2 - 1)
			{
				bc_printA((char*)BOXCHAR_TR);
				bc_printA((char*)"\n");
			}
			else if (i == x2 - 1 && j == 0)
			bc_printA((char*)BOXCHAR_BL);
			else if (i == x2 - 1 && j == y2 - 1)
			{
				bc_printA((char*)BOXCHAR_BR);
				bc_printA((char*)"\n");
			}
			else if ((i == 0 || i == x2 - 1) && (j > 0 && j < y2))
			bc_printA((char*)BOXCHAR_HOR);
			else if ((i > 0 && i < x2) && (j == 0 || j == y2 -1))
			bc_printA((char*)BOXCHAR_VERT);
		}
	}
	return 0;
}

int bc_printbigchar(int *big, int x, int y,colors fgcolor, colors bgcolor)
{
    mt_setfgcolor(fgcolor);
    mt_setbgcolor(bgcolor);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            mt_gotoXY(x + i, y + j);
            int value;
            bc_getbigcharpos(big, j, i, &value);
            if (!value)
                write(1, " ", 1);
            else
                bc_printA((char*)BOXCHAR_REC);
        }
		mt_setbgcolor(clr_default);
		mt_setfgcolor(clr_default);
    }
    return 0;
}

int bc_setbigcharpos(int *big, int x, int y, int value)
{
    if (x < 0 || x > 7 || y < 0 || y > 7 || value > 1 || value < 1)
        return -1;
    int pos = (y > 3) ? 1 : 0;
    y %= 4;
    if (!value)
        big[pos] &= ~(1 << (y * 8 + x));
    if (value)
        big[pos] |= 1 << (y * 8 + x);
    return 0;
}

int bc_getbigcharpos(int *big, int x, int y, int *value)
{
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return -1;
    int pos = y / 4;
    y %= 4;
    if (big[pos] & (1 << (y * 8 + x)))
        *value = 1;
    else
        *value = 0;
    return 0;
}

int bc_bigcharwrite(int fd, int *big, int count)
{
    for (int i = 0; i < count * 2; i++)
    {
        if (write(fd, &big[i], sizeof(int)) == -1)
        {
            return -1;
        }
    }
    return 0;
}

int bc_bigcharread(int fd, int *big, int need_count, int *count)
{
    for (*count = 0; (*count < need_count * 2); *count += 1)
    {
        if (read(fd, &big[*count], sizeof(int)) == -1)
        {
            return -1;
        }
    }
    return 0;
}

void getCharCode(int number, int *big)
{
	big[0]=digits[number][0];
	big[1]=digits[number][1];
}
