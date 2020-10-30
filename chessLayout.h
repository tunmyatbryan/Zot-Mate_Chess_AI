/*this is the header file for printBoard.c */


#ifndef PRINTBOARD_H
#define PRINTBOARD_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <assert.h>

#define SIZE 8

struct piece{
	unsigned char type;
	int color;		/*0 is WHITE , 1 is BLACK*/
	int value;
	unsigned char moveCount;
	unsigned char Xpos;
	unsigned char Ypos;
};

typedef struct piece PIECE;

struct theBoard{
	PIECE *board[SIZE][SIZE];

};

typedef struct theBoard THEBOARD;

/* This function will be used at the start to load the pieces */
THEBOARD InitializeBoard(void);

/*This function will delete a board*/
void DeleteBoard(THEBOARD *BoardtoDelete);

/*This function will be used to load the board where the pieces are at*/
void PrintBoard(THEBOARD chess_board);


/*will assign the proper color to the player and his pieces*/
PIECE *NewPiece(char type, int color, int value, char Xpos, char Ypos);

/*will delete a piece*/
void DeletePiece(PIECE *p);

/*for testing purposes -- a function that will print the values of a piece*/
void PrintPiece(PIECE *p);
#endif
