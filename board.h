#ifndef board_h
#define board_h

void displayBoard(void);
void ManvsMan(void);
int isWin(void);
int mymax(int, int);
void initial(void);
int mymin(int, int);
char isnOutRange(int, int);
void ManvsAI(void);
unsigned char AIMove(void);
unsigned char getMove(void);
int isBan(void);
int rvsPlayer(int);
unsigned char getx(unsigned char pos);
unsigned char gety(unsigned char pos);
void putpiece(unsigned char Y, unsigned char X, int Player);

extern unsigned long long psunumber[][];


#endif