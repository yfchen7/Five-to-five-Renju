
#include <stdio.h>
#include <string.h>
#include "GenPat.h"

int mystrstr(char* dest1, const char* dest2, char len1);

//Generate pattern book when initializing.

const static char yuchanglian1[] = "0111101";
const static char yuchanglian2[] = "1011110";
const static char yuchanglian3[] = "00111011";
const static char yuchanglian4[] = "11011100";
const static char yuchanglian5[] = "111101";
const static char yuchanglian6[] = "101111";
const static char yuchanglian7[] = "111011";
const static char yuchanglian8[] = "110111";
const static char yuchanglian9[] = "111011011";
const static char yuchanglian10[] = "110110111";

const static char yuchongsi1[] = "1010110";
const static char yuchongsi2[] = "0110101";
const static char yuchongsi3[] = "0101101";
const static char yuchongsi4[] = "1011010";

const static char chengwu[] = "11111";//0
const static char shuangchong[] = "11011011";
const static char huosi[] = "011110";//1
const static char chongsihuosan1[] = "0011101";//2
const static char chongsihuosan2[] = "1011100";//3
const static char chongsi1[] = "11101";//4
const static char chongsi2[] = "10111";//5
const static char chongsi3[] = "11110";//6
const static char chongsi4[] = "01111";//7
const static char chongsi5[] = "11011";//8
const static char huosan1[] = "0011100";//9
const static char huosan2[] = "001110";//10
const static char huosan3[] = "011100";//11
const static char tiaosan1[] = "011010";//12
const static char tiaosan2[] = "010110";//13
const static char huoer1[] = "001100";//14
const static char huoer2[] = "011000";//15
const static char huoer3[] = "000110";//16
const static char tiaoer1[] = "001010";//17
const static char tiaoer2[] = "010100";//18
const static char jianer[] = "010010";//19
const static char miansan1[] = "11100";//20
const static char miansan2[] = "00111";//21
const static char miansan3[] = "01110";//22
const static char miansan4[] = "01011";//23
const static char miansan5[] = "11010";//24
const static char miansan6[] = "11001";
const static char miansan7[] = "10011";
const static char miansan8[] = "10101";
const static char mianer1[] = "11000";
const static char mianer2[] = "00011";
const static char mianer3[] = "10100";
const static char mianer4[] = "00101";
const static char mianer5[] = "01001";
const static char mianer6[] = "10010";
const static char mianer7[] = "10001";
const static char huoyi1[] = "000100";//25
const static char huoyi2[] = "001000";//26
const static char huoyi3[] = "010000";//27
const static char huoyi4[] = "000010";//28
const static char changlian[] = "111111";//29



unsigned char posarray[15] = { 0 };

struct patnum patbook[1 << 16];

struct patnum getpat(unsigned char* posarray, char len1)
{
	struct patnum pattern = { 0 };
	int a1 = 0;
	int a2 = 0;
	int a3 = 0;
	pattern.changlian += mystrstr(posarray, changlian, len1);
	pattern.chengwu += mystrstr(posarray, chengwu, len1);

	a1 += mystrstr(posarray, yuchanglian1, len1);
	a1 += mystrstr(posarray, yuchanglian2, len1);
	a3 += mystrstr(posarray, yuchanglian3, len1);
	a3 += mystrstr(posarray, yuchanglian4, len1);
	pattern.chongsi += a1;
	pattern.yuchanglian += a1;
	pattern.miansan += a1;
	pattern.yuchanglian += a3;
	
	pattern.yuchanglian += mystrstr(posarray, yuchanglian5, len1);
	pattern.yuchanglian += mystrstr(posarray, yuchanglian6, len1);
	pattern.yuchanglian += mystrstr(posarray, yuchanglian7, len1);
	pattern.yuchanglian += mystrstr(posarray, yuchanglian8, len1);
	pattern.yuchanglian += mystrstr(posarray, yuchanglian9, len1);
	pattern.yuchanglian += mystrstr(posarray, yuchanglian10, len1);

	pattern.chongsi += mystrstr(posarray, shuangchong, len1) << 1;

	pattern.huosi += mystrstr(posarray, huosi, len1);
	pattern.chongsi += mystrstr(posarray, chongsihuosan1, len1);
	pattern.chongsi += mystrstr(posarray, chongsihuosan2, len1);
	pattern.chongsi += mystrstr(posarray, chongsi1, len1);
	pattern.chongsi += mystrstr(posarray, chongsi2, len1);
	pattern.chongsi += mystrstr(posarray, chongsi3, len1);
	pattern.chongsi += mystrstr(posarray, chongsi4, len1);
	pattern.chongsi += mystrstr(posarray, chongsi5, len1);

	a2 += mystrstr(posarray, yuchongsi1, len1);
	a2 += mystrstr(posarray, yuchongsi2, len1);
	a2 += mystrstr(posarray, yuchongsi3, len1);
	a2 += mystrstr(posarray, yuchongsi4, len1);
	pattern.miansan += a2;
	pattern.yuchongsi += a2;


	pattern.huosan += mystrstr(posarray, huosan1, len1);
	pattern.huosan += mystrstr(posarray, huosan2, len1);
	pattern.huosan += mystrstr(posarray, huosan3, len1);
	pattern.huosan += mystrstr(posarray, tiaosan1, len1);
	pattern.huosan += mystrstr(posarray, tiaosan2, len1);

	pattern.miansan += mystrstr(posarray, miansan1, len1);
	pattern.miansan += mystrstr(posarray, miansan2, len1);
	pattern.miansan += mystrstr(posarray, miansan3, len1);
	pattern.miansan += mystrstr(posarray, miansan4, len1);
	pattern.miansan += mystrstr(posarray, miansan5, len1);
	pattern.miansan += mystrstr(posarray, miansan6, len1);
	pattern.miansan += mystrstr(posarray, miansan7, len1);
	pattern.miansan += mystrstr(posarray, miansan8, len1);
	
	pattern.lianer1 += mystrstr(posarray, huoer1, len1);
	pattern.lianer2 += mystrstr(posarray, huoer2, len1);
	pattern.lianer2 += mystrstr(posarray, huoer3, len1);
	pattern.tiaoer += mystrstr(posarray, tiaoer1, len1);
	pattern.tiaoer += mystrstr(posarray, tiaoer2, len1);
	pattern.jianer += mystrstr(posarray, jianer, len1);
	pattern.mianer += mystrstr(posarray, mianer1, len1);
	pattern.mianer += mystrstr(posarray, mianer2, len1);
	pattern.mianer += mystrstr(posarray, mianer3, len1);
	pattern.mianer += mystrstr(posarray, mianer4, len1);
	pattern.mianer += mystrstr(posarray, mianer5, len1);
	pattern.mianer += mystrstr(posarray, mianer6, len1);
	pattern.mianer += mystrstr(posarray, mianer7, len1);
	pattern.huoyi1 += mystrstr(posarray, huoyi1, len1);
	pattern.huoyi1 += mystrstr(posarray, huoyi2, len1);
	pattern.huoyi2 += mystrstr(posarray, huoyi3, len1);
	pattern.huoyi2 += mystrstr(posarray, huoyi4, len1);

	return pattern;
}

void GenPat(void)
{
	int index = 0;
	int len1 = 5;
	int sum = 0;
	for (; len1<16; len1++) {
		for (index = 0; index<(1 << len1); index++) {
			for (int k = 0; k<len1; k++) {
				posarray[k] = (index >> k) & 0x1;
			}

			patbook[sum + index] = getpat(posarray, len1);
		}
		sum += index;
	}
}


//Return the number of dest2 in dest1
int mystrstr(char* dest1, const char* dest2, char len1)
{
	int i, j, k;
	int  cnt = 0;
	for (i = j = k = 0; i<len1;)
	{
		if (dest1[i] + '0' == dest2[j])
		{
			j++;
			i++;
		}
		else
		{
			j = 0;
			i = ++k;
			continue;
		}
		int len2 = strlen(dest2);
		if (j == len2)
		{
			memset(dest1 + k, 5, len2);
			cnt++;
			k = i;
			j = 0;
		}
	}
	if (cnt > 0)
		return 1;
	return 0;
}
