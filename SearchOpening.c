#include "SearchOpening.h"
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "settings.h"
#include "main.h"
#include "HashTable.h"
//#define _CRT_SECURE_NO_WARNINGS

long openbook(void);
unsigned char rerot(unsigned char, char );
unsigned long long rotate(char);

struct bookpoint {
	unsigned char pos;
	int level;
	unsigned long long HashVal;
};

struct bookpoint bookhistory[SIZE*SIZE];
unsigned char* buffer=NULL;
unsigned char rotatehistory[SIZE*SIZE];
long size;

//Use hashcode to distinguish distinct boards.
unsigned char SearchOpening(int mp)
{
	unsigned long long rotHashVal[16] = { 0 };
	rotHashVal[0] = NowHashVal;
	for (int i = 1; i < 16; i++) {
		rotHashVal[i] = rotate(i);
	}

	bookhistory[0].pos = 0x77;
	bookhistory[0].HashVal = psunumber[0][0x70];
	bookhistory[0].level = 0;
	
	if (size == 0)
		return 0xf0;

	int bmove = 1;
	unsigned char posi;
	int tlevel;
	long i = 1;

	if (mp) 
		for (i=3; i < size - 2; i += 2) 
			if (buffer[i - 2] == 0xff)
				break;	
	
	for (; i < size - 2; i += 2)
	{
		posi = buffer[i + 1];
		//8f branch node
		//4f over node
		//0f simple node

		if (buffer[i] == 0x8f || buffer[i] == 0xcf)
			bookhistory[bmove - 1].level++;

		if (buffer[i] == 0x4f || buffer[i] == 0xcf) {
			tlevel = bookhistory[bmove - 1].level - 1;
			for (; bmove>1 && bookhistory[bmove - 1].level != tlevel; bmove--)
				;
		}
		bookhistory[bmove].pos = posi;

		if (posi - (posi >> 4) >= 225)
			return 0xf2;
		bookhistory[bmove].HashVal = bookhistory[bmove - 1].HashVal^psunumber[bmove & 0x1][posi - (posi >> 4)];
		bookhistory[bmove].level = bookhistory[bmove - 1].level;

		bmove++;

		if (bmove == move + 1) {
			for (short k = bmove - 1; k > 0; k -= 2) {
				unsigned long long tmpHashVal = (bookhistory[bmove - 1].HashVal^psunumber[k & 0x1][bookhistory[k].pos - (bookhistory[k].pos >> 4)]);
				for (char dir = 0; dir < 16; dir++) {
					if (tmpHashVal == rotHashVal[dir]) {
						return rerot(bookhistory[k].pos, dir);
					}
				}

			}
		}
	}
	return 0xf1;
}


unsigned char turn90(unsigned char pos)
{
	return ((pos & 0xf) << 4) - (pos >> 4) + 14;
}

unsigned char mirror_hor(unsigned char pos)
{
	return (pos & 0xf0) + 14 - (pos & 0xf);
}

unsigned char mirror_inc(unsigned char pos)
{
	return ((pos & 0xf) << 4) + (pos >> 4);
}

//consider 16 kinds of symmetrical or asymmetrical or mirror board
unsigned long long rotate(char direction)
{
	unsigned long long rotateHashVal = 0;
	unsigned char posi= 0;
	for (unsigned char i = 0; i < move; i++) {
		posi = history[i];
		for (char k = 0; k < (direction >> 2); k++) 
			posi = turn90(posi);
		if (direction & 0x1)
			posi = mirror_hor(posi);
		if ((direction & 0x3) >> 1)
			posi = mirror_inc(posi);
		rotateHashVal ^= psunumber[i & 0x1][posi - (posi >> 4)];
	}

	return rotateHashVal;
}

//re-rotate: first in last out.
unsigned char rerot(unsigned char pos, char dir)
{
	char turn = ((dir >> 2) * 3) & 0x3;
	
	if ((dir & 0x3) >> 1)
		pos = mirror_inc(pos);
	if (dir & 0x1)
		pos = mirror_hor(pos);

	for (char i = 0; i < turn; i++)
		pos = turn90(pos);

	return pos;
}


long openbook(void)
{
	FILE *fp;
	long size;
	size_t result;
	if ((fp = fopen("renjubook", "rb")) == NULL)
	{
		puts("Fail to open file.");
		return 0;
	}

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	buffer = (unsigned char*)malloc(sizeof(unsigned char)*size);

	if (buffer == NULL) {
		fputs("Memory error", stderr);
		return 0;
	}

	result = fread(buffer, 1, size, fp);

	if (result != size) {
		fputs("Reading error", stderr);
		return 0;
	}
	return size;
}

