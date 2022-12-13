//#ifndef main_h
//#define main_h


#define SIZE 15
extern unsigned char history[SIZE*SIZE];
extern int move;
extern int ban;
extern int level;
extern unsigned long long NowHashVal;
extern void putpiece(unsigned char Y, unsigned char X, int Player);
extern int board[SIZE][SIZE];

//extern int mymin(int, int);
//extern int mymax(int, int);
//extern unsigned char getx(unsigned char pos);
//extern unsigned char gety(unsigned char pos);
//extern int rvsPlayer(int);
//extern char isnOutRange(int iY, int iX);
extern void displayBoard(void);


static inline char isnOutRange(int iY, int iX)
{
	return iY >= 0 && iY < SIZE && iX >= 0 && iX < SIZE;
}

static inline int mymax(int x, int y)
{
	if (x < y)
		return y;
	return x;
}
static inline int mymin(int x, int y)
{
	if (x < y)
		return x;
	return y;
}

//Player==1 Black;
//Player==2 White
static inline int rvsPlayer(int Player)
{
	return 1 + (Player & 0x1);
}


static inline unsigned char getx(unsigned char pos)
{
	return pos & 0xf;
}

static inline unsigned char gety(unsigned char pos)
{
	return pos >> 4;
}
//#endif
