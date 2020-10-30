#ifndef LEGAL_H
#define LEGAL_H

#include<stdio.h>

#include "move.h"
#include "chessLayout.h"
#include "Check.h"


/*
Param: The current Piece struct, or a pointer to the struct
Param: The 2D array of Board
Output: A pointer to the list of legal moves for the Pawn, of type MLIST from struct MoveList
*/

//generate legal move list for Pawn both for white and black
MLIST* PawnLegalMoveListGen(PIECE *cP, THEBOARD Board);

//generate legal move list for King both for white and black
MLIST* KingLegalMoveListGen(PIECE *cP, THEBOARD Board);

//generate legal move list for Rook both for white and black
MLIST* RookLegalMoveListGen(PIECE *cP, THEBOARD Board);

//generate legal move list for bishop both for white and black
MLIST* BishopLegalMoveListGen(PIECE *cP, THEBOARD Board);

//generate legal move list for queen both for white and black
MLIST* QueenLegalMoveListGen(PIECE *cP, THEBOARD Board);

//generate legal move list for knight both for white and black
MLIST* KnightLegalMoveListGen(PIECE *cP, THEBOARD Board);

#endif
