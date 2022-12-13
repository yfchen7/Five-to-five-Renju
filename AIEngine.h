
#ifndef AIEngine_h
#define AIEngine_h



extern unsigned char AIMove(void);
extern int isWin(int mp);
extern int isBan(int mp);

extern void getPointPat(char y, char x);
extern unsigned char patnumber[2][16];

#endif