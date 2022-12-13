
#include "main.h"
#include "SearchOpening.h"
#include "HashTable.h"
#include <stdio.h>
#include "GenPat.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "initial.h"
//#define DEBUG
//#define HASH
#define DEPTH_VCF 21
#define DEPTH_VCT 4
struct trypoint
{
	int y;
	int x;
	unsigned long long HashVal;
};
int isValid(unsigned char);
void addPat(struct patnum* pat, int Player);
void getBoardPat(int Player);
int evaBoard(int Player, int order);
int evaluation(int Player, int depth, int mdepth, int alpha, int beta, int extra);
//int evaluation1(int Player, int depth, int mdepth, int alpha, int beta, int extra);

int Block4(void);

int evaPoint(int Player, int order);
void getPointPat(char y, char x);
int findVCF(int Player, int depth, int mdepth);

int findVCT(int Player, int depth, int mdepth, int extend, int extra, int mode);

struct trypoint tryHistory[225];

int node = 0;
int Hashhit = 0;
int nexty, nextx;


const static int pow2[] =
{
	1,1 << 1,1 << 2,1 << 3,1 << 4,1 << 5,1 << 6,1 << 7,1 << 8,
	1 << 9,1 << 10,1 << 11,1 << 12,1 << 13,1 << 14
};

//Record 2 players' patten number.
unsigned char patnumber[2][16];
int newmove;
int vnode = 0;
int fnode = 0;
unsigned char pos;

struct prepos
{
	char y;
	char x;
	int score;
};

struct prepos Searchlist[50][225];
unsigned char AIMove(void)
{
	newmove = -1;
	vnode = 0;
	node = 0;
	Hashhit = 0;
	fnode = 0;
	clock_t clockstart, clockend;
	clockstart = clock();
#ifdef HASH
	memset(HashTable, 0, sizeof(HashTable));
#endif
	tryHistory[move - 1].HashVal = NowHashVal;
	tryHistory[move - 1].y = history[move - 1] >> 4;
	tryHistory[move - 1].x = history[move - 1] & 0xf;
	pos = 0xff;
	if (!move) {
		putpiece(7, 7, 1);
		pos = 0x77;
	}
	else if (level || move & 0x1) 
		pos = SearchOpening(move & 0x1);

	if (isValid(pos)) {
		putpiece(pos >> 4, pos & 0xf, (move & 0x1) + 1);
		printf("OP found\n");
	}
	
	else if (Block4()) {
		pos = (nexty << 4) + nextx;
		putpiece(pos >> 4, pos & 0xf, (move & 0x1) + 1);
	}
	else if (findVCF((move & 0x1) + 1, 1, 2)||findVCF((move & 0x1) + 1, 1,4)|| findVCF((move & 0x1) + 1, 1, 6) || findVCF((move & 0x1) + 1, 1, 18)) {
		putpiece(pos >> 4, pos & 0xf, (move & 0x1) + 1);
		printf("VCF found\n");
	}

	else if (findVCT((move & 0x1) + 1, 1, 2, 0, 0,6)||findVCT((move&0x1)+1,1,8,0,0,4)) {
		putpiece(pos >> 4, pos & 0xf, (move & 0x1) + 1);
		printf("VCT found\n");
		printf("vnode:%d, ", vnode);
		printf("fnode:%d\n", fnode);
	}
	
	else {
		vnode -= 20000;
		printf("Thinking at level %s...\n",level?"5-7":"5");
		for (int i = 0; i < 50; i++)
			Searchlist[1][i].score = -99999;
		int score = evaluation((move & 0x1) + 1, 1, 5, -99999, 99999, 0);
		unsigned pos1 = (nexty << 4) + nextx;
		if (level) {
			score = evaluation((move & 0x1) + 1, 1, 7, -99999, 99999, 0);
			if (score > -99998)
				pos = (nexty << 4) + nextx;
			else
				pos = pos1;
		}
		else
			pos = pos1;
		putpiece(pos >> 4, pos & 0xf, (move & 0x1) + 1);
		printf("AI rating:%d\n", score);
		printf("node:%d\n", node);
		printf("vnode:%d, ", vnode + 20000);
		printf("fnode:%d\n", fnode);
	}
	printf("%c%d\n", getx(pos) + 'A', gety(pos) + 1);
	//printf("newmove:%d, ", newmove);
	//printf("hashhit:%d\n", Hashhit);
	clockend = clock();
	printf("Time:%.2f\n", (double)(clockend - clockstart) / CLOCKS_PER_SEC);
	NowHashVal ^= psunumber[move & 0x1][pos - (pos >> 4)];
	history[move++] = pos;
	return pos;
}

int isValid(unsigned char pos)
{
	if ((pos & 0xf) < 0xf && (pos >> 4) < 0xf)
		return 1;
	return 0;
}

int patscore[2][16] =
{
	//zhao7
	{ 95000,95000,8000,47,59,25,32,30,30,28,12,6,4,-100,-50},
	{ 99999,99999,30000,30000,3000,31,45,40,40,35,14,7,6,-120,-60}
 //{ 95000,95000,8000,40,59,25,32,30,30,28,12,6,5,-100,-50},
//{ 99999,99999,30000,30000,3000,32,45,40,40,35,15,7,6,-120,-60 }

};



int isBan(int mPlayer)
{
	if (mPlayer||!ban)
		return 0;
	else if (patnumber[0][0] > 0 || patnumber[0][2] + patnumber[0][3] > 1 || patnumber[0][4] > 1)
		return 1;
	else return 0;
}

int isWin(int mPlayer)
{
	if (mPlayer&&patnumber[1][0] > 0)
		return 1;
	else if (patnumber[mPlayer][1] > 0)
		return 1;
	return 0;
}

static inline void trydo(int y, int x, int Player)
{
	//if (!isnOutRange(y, x))
		//donothing();
	board[y][x] = Player;
#ifdef HASH
	tryHistory[move].HashVal = tryHistory[move - 1].HashVal^psunumber[Player - 1][(y << 4) - y + x];
#endif
	tryHistory[move].y = y;
	tryHistory[move].x = x;
	move++;
#ifdef DEBUG
	displayBoard();
#endif
}

static inline void tryundo(void)
{
	move--;
	board[tryHistory[move].y][tryHistory[move].x] = 0;
#ifdef DEBUG
	displayBoard();
#endif
}

#ifdef HASH
void hashnode(unsigned long long HashVal)
{
	unsigned index = HashVal&mask;
	HashTable[index].HashVal = HashVal;
	HashTable[index].mode = 1;
}
#endif


static inline int cmp1(const void *a, const void *b) //use for qsort
{
	return (*(struct prepos *)b).score - (*(struct prepos *)a).score;
}

static inline void renew(int y, int x)
{
	nexty = y;
	nextx = x;
}

static inline int stretch(int y, int x, int Player)
{
	int k, l;
	int cnt = 1;
	int rmp = rvsPlayer(Player) - 1;
	for (k = -4; k < 5; k++) {
		for (l = -4; l < 5; l++) {
			if (!isnOutRange(y + k, x + l) || board[y + k][x + l] != 0)
				continue;
			trydo(y + k, x + l, rvsPlayer(Player));
			//board[y + k][x + l] = rvsPlayer(Player);
			getPointPat(y, x);
			if (patnumber[Player - 1][3] > 0) {
				tryundo();
				//board[y + k][x + l] = 0;
				continue;
			}
		
			getPointPat(y + k, x + l);
			if (isBan(rmp)) {
				tryundo();
				//board[y + k][x + l] = 0;
				return 0;
			}
			if (patnumber[rmp][2] > 0||patnumber[rmp][3]>1)
			{
				tryundo();
				return -1;
			}
			if (patnumber[rmp][3] == 1) {
				int c = stretch(y + k, x + l,rvsPlayer(Player));
				if (!c) {
					tryundo();
					return -1;
				}
				else if (c == -1) {
					tryundo();
					return 0;
				}
				else
					cnt += c;
			}
		
			//trydo(y + k, x + l, rvsPlayer(Player));
			return cnt;
		}
	}
	return 0;
}

//放弃了。技不如人。因为天性愚钝，又无人请教。2020.2.15
//Simple AlphaBeta pruning

int evaluation(int Player, int depth, int mdepth, int alpha, int beta, int extra) //For odd depth
{
	if (depth <= 5 && node > 3000000)
		return alpha;
	int rmp = rvsPlayer(Player) - 1;
	int val = -99999;
	int valid = 0;
	int cnt = 0;
	//if (depth == 1) {
		//cnt = 30;
		//goto INIT;
	//}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j])
				continue;
			valid = 0;

			for (int k = -2; k<3; k++)
				for (int l = -2; l<3; l++)
					if (isnOutRange(i + k, j + l) && board[i + k][j + l] != 0)
						valid = 1;
			if (!valid)
				continue;
			trydo(i, j, Player);
			
			getPointPat(i, j);
			if (isBan(Player - 1)) {
				tryundo();	
				continue;
			}

			if (patnumber[Player - 1][2] > 0 || patnumber[Player - 1][3] > 1 || patnumber[Player - 1][3]>0 && patnumber[Player - 1][4]>0) {
				tryundo();
				if (depth == 1) {
					nexty = i;
					nextx = j;
				}
				return 99999;
			}

			if (patnumber[Player - 1][3] == 1 && depth <= mdepth) {
			
				valid = stretch(i, j, Player);
				if (valid == -1) {
					tryundo();
					continue;
				}

				if (!valid) {
					tryundo();
					if (depth == 1) {
						nexty = i;
						nextx = j;
					}
					return 99999;
				}
				else if (valid & 0x1)
					val = evaluation(Player, depth + 1, mdepth, alpha, beta, extra + 1);
				else
					val = -evaluation(rvsPlayer(Player), depth + 1, mdepth, -beta, -alpha, extra + 2);

				tryundo();
				for (int i = 0; i<valid; i++)
					tryundo();

				if (depth==1&&node > 3000000)
					return -99998;
				if (alpha < val) {
					alpha = val;
					if (depth == 1)
						renew(i, j);
				}
			
				if (alpha >= beta)
					return alpha;
				continue;
			}

		
			if (extra & 0x1 ? depth >= mdepth - 1 : depth >= mdepth) {
				node++;
				val = evaBoard(Player, 0) - evaBoard(rvsPlayer(Player), 1);
				tryundo();

				if (val >= beta)
					return val;

				if (val > alpha)
					alpha = val;
				continue;
			}

			else {
				if (depth == 1 && mdepth == 7) {
					tryundo();
					continue;
				}
				getBoardPat(rvsPlayer(Player));
				if (patnumber[rmp][3] + patnumber[rmp][2] + patnumber[rmp][4] + patnumber[rmp][0] + patnumber[rmp][1] > 0) {
					tryundo();
					//board[i][j] = 0;
					continue;
				}
				tryundo();
				//int tmp = evaPoint(rvsPlayer(Player), 1);
				//trydo(i, j, rvsPlayer(Player));
				//getPointPat(i, j);
				//tryundo();
				Searchlist[depth][cnt].score = evaPoint(Player, 0) - evaPoint(rvsPlayer(Player), 1);
				Searchlist[depth][cnt].y = i;
				Searchlist[depth][cnt].x = j;
				cnt++;
			}
		}
	}

	if (extra & 0x1 ? depth >= mdepth - 1 : depth >= mdepth)
		return alpha;
	if(!(depth==1&&mdepth==7))
		qsort(Searchlist[depth], cnt, sizeof(struct prepos), cmp1);

	if (move == 225)
		return evaBoard(Player, 0) - evaBoard(rvsPlayer(Player), 1);

	if (!cnt&&mdepth!=7)
		return alpha;
	
	if (depth == 1) {
		printf("Sorted.\n");
		if (alpha == -99999) {
			nexty = Searchlist[depth][0].y;
			nextx = Searchlist[depth][0].x;
		}
	}
	
	if (depth == 1 && mdepth == 7)
		cnt = 25;
	for (int i = 0; i < cnt&&i < 25 && Searchlist[depth][i].score>-99999; i++)
	{
		if (depth == 1)
			printf("%c%d ", 'A' + Searchlist[depth][i].x, Searchlist[depth][i].y + 1);
		trydo(Searchlist[depth][i].y, Searchlist[depth][i].x, Player);

		val = -evaluation(rvsPlayer(Player), depth + 1, mdepth, -beta, -alpha, extra);

		//if (depth == 3) {
			//if (findVCF(rvsPlayer(Player), 1, 8) || findVCT(rvsPlayer(Player), 1, 2, 0, 0, 0))
				//val = -99999;
		//}

		if (depth == 1 && node > 3000000) {
			
			tryundo();
			if (i <= 1)
				alpha = -99998;
			break;
		}


		if (alpha < val)
		{
			if((mdepth==7 && cnt > 3 ||mdepth==5&&cnt<=3)&&depth==1&& (findVCF(rvsPlayer(Player), 1, 8) || findVCT(rvsPlayer(Player), 1, 6, 0, 0, 0)))
					val = Searchlist[depth][i].score = -99999;
			else {
				alpha = val;
				if (depth == 1) {
					renew(Searchlist[depth][i].y, Searchlist[depth][i].x);
					newmove = i;
					if (mdepth == 5) {
						for (int k = i; k > 0; k--) {
							struct prepos tmp;
							tmp = Searchlist[depth][k - 1];
							Searchlist[depth][k - 1] = Searchlist[depth][k];
							Searchlist[depth][k] = tmp;
						}
					}
				}
			}
		}
		if (depth == 1) {

			printf("%d ", val);
		}
		tryundo();
		
		if (alpha >= beta)
			return alpha;
	}
	
	return alpha;
}

//VCT还是太慢，无法做杀。
//没有局部分块评估，效率和棋力大大降低。
int findVCT(int Player, int depth, int mdepth, int extend,int extra,int mode)
{
	if (vnode > 70000)
		return 0;
#ifdef HASH
	if(depth==1)
		memset(HashTable, 0, sizeof(HashTable));
	
	else if (HashTable[tryHistory[move - 1].HashVal&mask].mode == 1 && HashTable[tryHistory[move - 1].HashVal&mask].HashVal == tryHistory[move - 1].HashVal)
	{
		Hashhit++;
		return 0;
	}
#endif
	vnode++;
	if (mode) {
		if (depth > mdepth + extra || depth > mdepth + 10) {
			//if ( findVCF(Player, 1, mode))
				//return 1;
			return 0;
		}
	}
	else {
		if (depth > mdepth + extra || depth > mdepth + 6) {
			//if (findVCF(Player, 1, 4))
				//return 1;
			return 0;
		}
	} 
	int rmp = rvsPlayer(Player) - 1;
	int val = 0;
	int valid = 0;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j])
				continue;
			valid = 0;

			for (int k = -2; k < 3; k++)
				for (int l = -2; l < 3; l++)
					if (isnOutRange(i + k, j + l) && board[i + k][j + l] != 0)
						valid = 1;
			if (!valid)
				continue;
			trydo(i, j, Player);

			getPointPat(i, j);


			if (isBan(Player - 1)) {
				tryundo();
				continue;
			}

			if (depth & 0x1) { //Attack

				if (patnumber[Player - 1][2] > 0 || patnumber[Player - 1][3] > 1) {
					tryundo();
					if (depth == 1)
						pos = (i << 4) + j;
					return 1;
				}

				if (patnumber[Player - 1][3] == 1) {

					valid = stretch(i, j, Player);
					if (valid == -1) {
						tryundo();
						continue;
					}

					if (!valid) {
						tryundo();
						if (depth == 1)
							pos = (i << 4) + j;
						return 1;
					}
					else if (valid & 0x1)
						val = findVCT(Player, depth+2, mdepth, 0,extra+2,mode);
					else
						val = 0;
#ifdef HASH
					if (!val)
						hashnode(tryHistory[move - 1].HashVal);
#endif
					tryundo();
					for (int i = 0; i < valid; i++)
						tryundo();

					if (val == 1) {
						if (depth == 1)
							pos = (i << 4) + j;
						return 1;
					}
					
					continue;
				}

				if (patnumber[Player - 1][4]) {
					getBoardPat(rvsPlayer(Player));
					if (!patnumber[rmp][4]) {
						val = findVCT(rvsPlayer(Player), depth + 1, mdepth, 0, extra, mode);
						tryundo();
						if (val == 1) {
							if (depth == 1)
								pos = (i << 4) + j;
							return 1;
						}
#ifdef HASH
						hashnode(tryHistory[move].HashVal);
#endif
						continue;
					}
				}
				tryundo();
				continue;
			}
			else //Defend
			{
				if (patnumber[Player - 1][2] > 0 || patnumber[Player - 1][3] > 1 || patnumber[Player - 1][3] > 0 && patnumber[Player - 1][4] > 0) {
					tryundo();
					return 0;
				}
				if (patnumber[Player - 1][3] == 1) {

					valid = stretch(i, j, Player);
					if (valid == -1) {
						tryundo();
						continue;
					}

					if (!valid) {
						tryundo();
						return 0;
					}
					else if (valid & 0x1)
						val = findVCT(Player, depth + 2 , mdepth, valid + 1, extra+2,mode);
					else
						val = 1;
#ifdef HASH
					if(!val)
						hashnode(tryHistory[move - 1].HashVal);
#endif

					tryundo();
					for (int i = 0; i < valid; i++)
						tryundo();

					if (val == 0)
						return 0;

					continue;
				}
				getBoardPat(rvsPlayer(Player));
				//getPointPat(tryHistory[move - 2 - extend].y, tryHistory[move - 2 - extend].x);
				if (patnumber[rmp][4] > 0) {
					tryundo();
					continue;
				}
				else {
					val = findVCT(rvsPlayer(Player), depth + 1, mdepth, 0,extra,mode);
					tryundo();
					if (val == 0) {
#ifdef HASH
						hashnode(tryHistory[move].HashVal);
#endif

						return 0;
					}
				}
			}

		}
	}
	return depth & 0x1 ? 0 : 1;
}

int findVCF(int Player, int depth, int mdepth)
{
	if (depth > mdepth)
		return 0;
	fnode++;
	int val = 0;
	int valid = 0;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j])
				continue;
			valid = 0;

			for (int k = -2; k < 3; k++)
				for (int l = -2; l < 3; l++)
					if (isnOutRange(i + k, j + l) && board[i + k][j + l] != 0)
						valid = 1;
			if (!valid)
				continue;
			trydo(i, j, Player);

			getPointPat(i, j);
			if (isBan(Player - 1)) {
				tryundo();
				continue;
			}

			if (patnumber[Player - 1][2] > 0 || patnumber[Player - 1][3] > 1) {
				tryundo();
				if (depth == 1)
					pos = (i << 4) + j;
				return 1;
			}

			if (patnumber[Player - 1][3] == 1) {

				valid = stretch(i, j, Player);
				if (valid == -1) {
					tryundo();
					continue;
				}

				if (!valid) {
					tryundo();
					if (depth == 1)
						pos = (i << 4) + j;
					return 1;
				}
				else if (valid & 0x1)
					val = findVCF(Player, depth + 2, mdepth);
				else
					val = 0;

				//if (!val)
					//hashnode(tryHistory[move - 1].HashVal);

				tryundo();
				for (int i = 0; i < valid; i++)
					tryundo();

				if (val == 1) {
					if (depth == 1)
						pos = (i << 4) + j;
					return 1;
				}

				continue;
			}
			tryundo();
			continue;
		}
	}
	return 0;
}


int Block4(void)
{
	int mp = move & 0x1;
	int cnt = 0;
	getPointPat(history[move - 2] >> 4, history[move - 2] &0xf);//chengwu order0
	if (patnumber[mp][2] + patnumber[mp][3] > 0) {
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++) {
				if (board[i][j])
					continue;
				trydo(i, j, mp + 1);
				getPointPat(tryHistory[move - 1].y, tryHistory[move - 1].x);
				tryundo();
				if (isBan(mp))
					continue;
				if (patnumber[mp][1]+ patnumber[mp][0]>0) {
					nexty = i;
					nextx = j;
					return 1;
				}
			}
	}
	getPointPat(tryHistory[move - 1].y, tryHistory[move - 1].x);//huosi order1
	if ((cnt=patnumber[!mp][2]) > 0) {
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++) {
				if (board[i][j])
					continue;
				trydo(i,j,mp+1);
				getPointPat(tryHistory[move - 2].y, tryHistory[move - 2].x);
				tryundo();
				if (patnumber[!mp][2]<cnt) {
					nexty = i;
					nextx = j;
					return 1;
				}
			}
	}
	if ((cnt=patnumber[!mp][3]) > 0) {//chongsi order1
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++) {
				if (board[i][j])
					continue;
				trydo(i, j, mp + 1);
				getPointPat(tryHistory[move - 2].y, tryHistory[move - 2].x);
				tryundo();
				if (patnumber[!mp][3]<cnt) {
					nexty = i;
					nextx = j;
					return 1;
				}
			}
	}
	return 0;
}

//get pos points
int evaPoint(int Player, int order)
{
	int score = 0;
	for (int i = 0; i < (Player == 1 &&ban ? 15 : 13); i++) {
		score += patnumber[Player - 1][i] * patscore[order][i];
	}	

	return score;
}

//get points
int evaBoard(int Player, int order)
{
	getBoardPat(Player);
	int mp = Player - 1;
	int score = 0;
	for (int i = 0; i < (Player == 1&&ban ? 15 : 13); i++) {
		score += patnumber[mp][i] * patscore[order][i];
	}

	return score;
}


void getPointPat(char y, char x)
{
	int Player = board[y][x];
	int head, cnt, index;
	int rPlayer = rvsPlayer(Player);
	memset(patnumber + Player - 1, 0, 16);
	//heng
	for (head = x; head >= 1 && board[y][head - 1] != rPlayer; head--)
		;
	for (cnt = index = 0; head < SIZE && board[y][head] != rPlayer; head++) {
		if (board[y][head] == Player)
			index += pow2[cnt];
		cnt++;
	};
	if (cnt >= 5) {
		index += sum2[cnt - 1];
		addPat(&(patbook[index]), Player - 1);
	}

	//shu
	for (head = y; head >= 1 && board[head - 1][x] != rPlayer; head--)
		;
	for (cnt = index = 0; head < SIZE &&board[head][x] != rPlayer; head++) {
		if (board[head][x] == Player)
			index += pow2[cnt];
		cnt++;
	}
	if (cnt >= 5) {
		index += sum2[cnt - 1];
		addPat(&(patbook[index]), Player - 1);
	}

	//zuoxie
	for (head = 0; y + head >= 1 && x + head >= 1 && board[y + head - 1][x + head - 1] != rPlayer; head--)
		;
	for (cnt = index = 0; y + head < SIZE&&x + head < SIZE&&board[y + head][x + head] != rPlayer; head++) {
		if (board[y + head][x + head] == Player)
			index += pow2[cnt];
		cnt++;
	}
	if (cnt >= 5) {
		index += sum2[cnt - 1];
		addPat(&(patbook[index]), Player - 1);
	}

	//youxie
	for (head = 0; y - head <= 13 && x + head >= 1 && board[y - head + 1][x + head - 1] != rPlayer; head--)
		;
	for (cnt = index = 0; y - head >= 0 && x + head < SIZE&& board[y - head][x + head] != rPlayer; head++) {
		if (board[y - head][x + head] == Player)
			index += pow2[cnt];
		cnt++;
	}
	if (cnt >= 5) {
		index += sum2[cnt - 1];
		addPat(&(patbook[index]), Player - 1);
	}
	if (Player == 2||!ban) {
		patnumber[1][3] += patnumber[1][13];
		patnumber[1][4] += patnumber[1][14];
	}
}


void getBoardPat(int Player)
{
	int mPlayer = Player - 1;
	int rPlayer = rvsPlayer(Player);
	int head, cnt, index;
	memset(patnumber + mPlayer, 0, 16);

	for (int i = 0; i < SIZE; i++) { //heng
		head = 0;
		for (; head < 11;) {
			index = 0;
			if (board[i][head + 1] == rPlayer) {
				head += 2;
				continue;
			}
			if (board[i][head] == rPlayer) {
				head++;
				continue;
			}
			for (cnt = 0; head < SIZE&&board[i][head] != rPlayer; head++) {
				if (board[i][head] == Player)
					index += pow2[cnt];
				cnt++;
			}
			if (cnt < 5)
				continue;

			index += sum2[cnt - 1];

			addPat(&(patbook[index]), mPlayer);
		}
	}

	for (int i = 0; i < SIZE; i++) { //shu
		head = 0;
		for (; head < 11;) {
			index = 0;
			if (board[head + 1][i] == rPlayer) {
				head += 2;
				continue;
			}
			if (board[head][i] == rPlayer) {
				head++;
				continue;
			}
			for (cnt = 0; head < SIZE&&board[head][i] != rPlayer; head++) {
				if (board[head][i] == Player)
					index += pow2[cnt];
				cnt++;
			}
			if (cnt < 5)
				continue;
			index += sum2[cnt - 1];
			addPat(&(patbook[index]), mPlayer);
		}
	}

	for (int i = 0; i < SIZE - 4; i++) { //zuoxie1
		head = 0;
		for (; head < 11 - i;) {
			index = 0;
			if (board[head + 1][i + head + 1] == rPlayer) {
				head += 2;
				continue;
			}
			if (board[head][i + head] == rPlayer) {
				head++;
				continue;
			}
			for (cnt = 0; head < SIZE - i && board[head][i + head] != rPlayer; head++) {
				if (board[head][i + head] == Player)
					index += pow2[cnt];
				cnt++;
			}
			if (cnt < 5)
				continue;
			index += sum2[cnt - 1];
			addPat(&(patbook[index]), mPlayer);
		}
	}

	for (int i = 1; i < SIZE - 4; i++) { //zuoxie2
		head = 0;
		for (; head < 11 - i;) {
			index = 0;
			if (board[head + i + 1][head + 1] == rPlayer) {
				head += 2;
				continue;
			}
			if (board[head + i][head] == rPlayer) {
				head++;
				continue;
			}
			for (cnt = 0; head < SIZE - i&& board[head + i][head] != rPlayer; head++) {
				if (board[head + i][head] == Player)
					index += pow2[cnt];
				cnt++;
			}
			if (cnt < 5)
				continue;
			index += sum2[cnt - 1];
			addPat(&(patbook[index]), mPlayer);
		}
	}

	for (int i = 0; i < SIZE - 4; i++) { //youxie1
		head = 0;
		for (; head < 11 - i;) {
			index = 0;
			/*
			if (board[head + 1][SIZE-i-head] == rPlayer) {
			head += 2;
			continue;
			}
			*/
			if (board[head][SIZE - i - head - 1] == rPlayer) {
				head++;
				continue;
			}
			for (cnt = 0; head < SIZE - i&& board[head][SIZE - i - head - 1] != rPlayer; head++) {
				if (board[head][SIZE - i - head - 1] == Player)
					index += pow2[cnt];
				cnt++;
			}
			if (cnt < 5)
				continue;
			index += sum2[cnt - 1];
			addPat(&(patbook[index]), mPlayer);
		}
	}

	for (int i = 1; i < SIZE - 4; i++) { //youxie2
		head = 0;
		for (; head < 11 - i;) {
			index = 0;
			if (board[head + i + 1][SIZE - head] == rPlayer) {
				head += 2;
				continue;
			}
			if (board[head + i][SIZE - head - 1] == rPlayer) {
				head++;
				continue;
			}
			for (cnt = 0; head < SIZE - i&&board[head + i][SIZE - head - 1] != rPlayer; head++) {
				if (board[head + i][SIZE - head - 1] == Player)
					index += pow2[cnt];
				cnt++;
			}
			if (cnt < 5)
				continue;
			index += sum2[cnt - 1];
			addPat(&(patbook[index]), mPlayer);
		}
	}
	if (Player == 2||!ban) {
		patnumber[1][3] += patnumber[1][13];
		patnumber[1][4] += patnumber[1][14];
	}
}


void addPat(struct patnum* pat, int i)
{

	patnumber[i][0] += pat->changlian;
	patnumber[i][1] += pat->chengwu;
	patnumber[i][2] += pat->huosi;
	patnumber[i][3] += pat->chongsi;
	
	patnumber[i][4] += pat->huosan;
	patnumber[i][5] += pat->miansan;

	patnumber[i][6] += pat->lianer1;
	patnumber[i][7] += pat->lianer2;
	patnumber[i][8] += pat->tiaoer;
	patnumber[i][9] += pat->jianer;
	
	patnumber[i][10] += pat->mianer;
	patnumber[i][11] += pat->huoyi1;
	patnumber[i][12] += pat->huoyi2;
	patnumber[i][13] += pat->yuchanglian;
	patnumber[i][14] += pat->yuchongsi;

}
