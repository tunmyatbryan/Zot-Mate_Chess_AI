/***********************************************************
*
*A simple GTK example
*simple.h: show a 2x2 board and move the king by clicking
*author: Weiwei Chen
*initial version: 01/22/13 EECS22L Winter 2013
*
***********************************************************/

#ifndef _GUI_H
#define _GUI_H


#define MAX_MSGLEN  100 
#define SQUARE_SIZE 50  
#define WINDOW_BORDER 10
#define BOARD_BORDER 10
#define BOARD_WIDTH  (8*SQUARE_SIZE)
#define BOARD_HEIGHT (8*SQUARE_SIZE)
#define WINDOW_WIDTH  (2*BOARD_WIDTH)
#define WINDOW_HEIGHT (BOARD_HEIGHT + 2*BOARD_BORDER)

//static const GdkRGBA black = {0, 0, 0, 1};
//static const GdkRGBA white = {1, 1, 1, 1};

enum GRID
{
	BLACK = 0,
	WHITE = 1,
	B_KING,
	B_QUEEN,
	B_BISHOP,
	B_KNIGHT,
	B_PAWN,
	B_ROOK,
	W_KING,
	W_QUEEN,
	W_BISHOP,
	W_KNIGHT,
	W_PAWN,
	W_ROOK,
	
};

#endif
