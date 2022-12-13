#include <string.h>
#include "main.h"
#include "AIEngine.h"


int sum2[15] = { 0 };

void set_sum2()
{
	for (int i = 5; i < 15; i++) {
		sum2[i] = sum2[i - 1] + (1 << i);
	}
}

void initial()
{
	memset(board, 0, sizeof(board));
	memset(patnumber, 0, sizeof(patnumber));
	move = 0;
	ban = 1;
	level = 1;
	NowHashVal = 0;
}




