#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "settings.h"
#include "AIEngine.h"
#include "HashTable.h"
#include "GenPat.h"
#include "initial.h"
#include "SearchOpening.h"
#include "main.h"

void displayBoard(void);
void ManvsMan(void);


void initial(void);
void ManvsAI(void);
unsigned char getMove(void);
void putpiece(unsigned char Y, unsigned char X, int Player);
//Encoding:GBK / GB2312

//Display Board
char BlankBoardArray[SIZE][SIZE * CHARSIZE + 1] =
{
	"©»©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©¿",//line 15
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
	"©³©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©·" };//line 1

char NowBoardArray[SIZE][SIZE * CHARSIZE + 1];
const static char alphabet[] = "  A B C D E F G H I J K L M N O";
const static char Pic[4][2] =
{
	"¡ñ",
	"¡ò",
	"¡ø",
	"¡÷"
};

const unsigned char QUIT = 0xff;
int board[SIZE][SIZE];


//Record previous moves
unsigned char history[SIZE*SIZE];
unsigned long long NowHashVal = 0;
int move = 0;
int ban = 1;
int level = 1;
//clear stdin buffer
void fflush_std(void)
{
	char c;
	while ((c = getchar()) != '\n'&&c != EOF)
		;
}

int main()
{
	//system("color f0");
	printf("Initializing...");
	//try to open renju book.
	size = openbook();
	set_sum2();
	GenPat();//generate pattern book
	printf("Done.\n");

	while (1) {
		initial();
		displayBoard();
	
		printf("Press 1: Man VS Man (forbidden move enabled)\nPress 2: Man VS AI  (enabled) (DEFAULT)\nPress 3: Man VS Man (disabled)\nPress 4: Man VS AI  (disabled)\nPress q to quit:\n");
		char choose = getchar();
		if (choose == '\n')
			ManvsAI();
		else if (choose == '1') {
			fflush_std();
			ManvsMan();
		}
		else if (choose == '3') {
			fflush_std();
			ban = 0;
			ManvsMan();
		}
		else if (choose == '4') {
			fflush_std();
			ban = 0;
			ManvsAI();
		}
		else if (choose == 'q')
			break;
		else {
			fflush_std();
			ManvsAI();
		}
	}
	return 0;
}


void displayBoard(void)
{
	
#ifdef _WIN32
	system("cls"); 
#else
	system("clear"); 
#endif
	printf("\n");
	memcpy(NowBoardArray, BlankBoardArray, sizeof(BlankBoardArray));
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (board[i][j] < 5 && board[i][j]>0)
				memcpy(NowBoardArray[0] + i * (CHARSIZE * SIZE + 1) + j * CHARSIZE, Pic[board[i][j] - 1], 2);

	for (int i = 0; i < SIZE; i++) {
		if (SIZE - i > 9)
			printf("%d%s\n", SIZE - i, NowBoardArray[SIZE - i - 1]);
		else
			printf(" %d%s\n", SIZE - i, NowBoardArray[SIZE - i - 1]);
	}
	printf("%s\n", alphabet);
}


void ManvsMan(void)
{
	displayBoard();
	int Player = 1;
	while (1) {

		unsigned char pos;
		pos = getMove();

		if (pos == QUIT)
			break;

		printf("%c%d\n", getx(pos) + 'A', gety(pos) + 1);
		getPointPat(pos >> 4, pos & 0xf);
		if (isWin(move&0x1)) {
			printf("%s wins.\n", Player == 1 ? "Black" : "White");
			break;
		}

		if (isBan(move&0x1)) {
			printf("Forbidden move. White wins.\n");
			break;
		}

		if (move == SIZE*SIZE) {
			printf("Tie.\n");
			break;
		}//TIE
		history[move++] = pos;
	}
	printf("Input any to continue...\n");
	fflush_std();
}

int redo(void)
{
	if (history[move] != 0) {
		putpiece(gety(history[move]), getx(history[move]), (move&0x1)+1);
		NowHashVal ^= psunumber[move & 0x1][history[move] - (history[move] >> 4)];
		move++;
		return 1;
	}
	return 0;
}

int undo()
{
	if (move) {
		--move;
		putpiece(gety(history[move]), getx(history[move]), 0);
		NowHashVal ^= psunumber[move & 0x1][history[move]-(history[move]>>4)];
		if (move)
			putpiece(gety(history[move - 1]), getx(history[move - 1]), !(move & 0x1) + 1);
		return 1;
	}
	return 0;
}

unsigned char getMove(void)
{
	//use one unsigned char to express a pos. low 4 bits exprees x,and high 4 bits y.
	unsigned char pos;
	
	while (1) {
		int Player = (move & 0x1) + 1;
		//avoid unsafe scanf
		char input[INPUTSIZE] = { 0 };
		printf("Please input your move (eg H7 or h7 or 7h or 7H)\nPress q to return menu\nPress t to ask AI for help, press R/r to undo:\n");
		int i = 0;
		for (; i < INPUTSIZE && (input[i] = getchar()) != '\n' && input[i] != EOF; i++)
			;
		if (i == INPUTSIZE)
			fflush_std();

		int k;
		for (k = 0; k < INPUTSIZE && !(input[k] >= 'A'&&input[k] <= 'O' || input[k] >= 'a'&&input[k] <= 'o'); k++)
			;

		if (input[0] == 'q'&& input[1] == '\n') {
			pos = QUIT;
			return pos;
		}
		else if ((input[0] == 'r' || input[0] == 'R') && input[1] == '\n') {
			undo();
			continue;
		}
		else if ((input[0] == 'u' || input[0] == 'U') && input[1] == '\n') {
			redo();
			continue;
		}

		else if ((input[0] == 't' || input[0] == 'T') && input[1] == '\n') {
			pos = AIMove();
			continue;
		}
		else if (k < INPUTSIZE) {
			int i = (k == 0 ? atoi(input + 1) : atoi(input));
			if (i <= SIZE&&i > 0) {
				pos = i - 1;
				pos <<= 4;
				pos += (input[k] <= 'O' ? input[k] - 'A' : input[k] - 'a');
				unsigned y = gety(pos);
				unsigned x = getx(pos);
				if (board[y][x] == 0) {
					putpiece(y, x, Player);
					return pos;
				}
				else
					printf("Forbidden position. ");
			}
		}

		else {
			printf("Invalid input. ");
			continue;
		}
	}
}

void ManvsAI(void)
{
	unsigned char pos;
	displayBoard();
	int Player = 1;
	int first = 0;
	printf("Press 1: AI first  (Hard)\nPress 2: You first (Normal) (DEFAULT)\nPress 3: AI first  (Easy)\nPress 4: You first (Newbee)\nPress q to return:\n");
	int choose = getchar();
	if (choose == '\n')
		;
	else if (choose == 'q') {
		fflush_std();
		return;
	}
	else if (choose == '1' || choose == '3'||choose=='2') {
		if (choose == '3')
			level = 0;
		if (choose == '1' ||choose=='3')
			first = 1;
		
			fflush_std();
	}
	else {
		level = 0;
		fflush_std();
	}

	if (first) {
		AIMove();
		Player = rvsPlayer(Player);
	}

	while (1) {
		
		//Man's turn
		pos = getMove();
		
		if (pos == QUIT)
			break;

		getPointPat(pos >> 4, pos & 0xf);
		if (isWin(move&0x1)) {
			printf("You win.\n");
			//getMove();
			break;
		}

		if (isBan(move & 0x1)) {
			printf("Forbidden move. AI wins.\n");
			break;
		}

		if (move == SIZE*SIZE) {
			printf("Tie.\n");
			break;
		}//TIE
		NowHashVal ^= psunumber[move & 0x1][pos - (pos >> 4)];
		history[move++] = pos;
		Player = rvsPlayer(Player);

		 //AI's turn
		pos = AIMove();
		getPointPat(pos >> 4, pos & 0xf);
		if (isWin(!(move & 0x1))) {
			printf("AI wins.\n");
			//getMove();
			break;
		}

		if (move == SIZE*SIZE) {
			printf("Tie.\n");
			break;
		}//TIE
		Player = rvsPlayer(Player);
	}
	printf("Input any to continue...\n");
	fflush_std();
}


void putpiece(unsigned char Y, unsigned char X, int Player)
{
	if (Player) {
		board[Y][X] = Player + 2;
		displayBoard();
		board[Y][X] = Player;
	}
	else {
		board[Y][X] = 0;
		displayBoard();
	}
}


