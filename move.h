/*
Header file for move.h
Change Log:
1/25 15:38 - added comment asking what CreateMove does
1/28 7:17 - cesar - added the board parameter in createMove
...
..
.

*/
#ifndef MOVE_H
#define MOVE_H
#include "chessLayout.h"
#include <stdlib.h>

typedef struct MoveList MLIST;
typedef struct MoveListEntry MENTRY;
typedef struct Move MOVE;

struct MoveList{
	unsigned int Length;
	MENTRY *First;
	MENTRY *Last;
};

struct MoveListEntry{
	MLIST *List;
	MENTRY *Next;
	MENTRY *Prev;
	MOVE *PotentialMove;
};

struct Move{
	unsigned char initX;
	unsigned char initY;
	PIECE *Mover;
	unsigned char finX;
	unsigned char finY;
	PIECE *Capture;
	int score;
	int min;
	int max;
};

/* creates a set of moves */
MLIST *CreateMoveList();

/* deletes a set of moves */
void DeleteMoveList(MLIST *list);

/*delete move entry*/
MOVE *DeleteMoveEntry(MENTRY *e);

/*append a set of moves */
void AppendMoveList(MLIST *list, MOVE *PossibleMove);

/*create a move*/
MOVE *CreateMove(unsigned char initialX,unsigned char initialY,
		unsigned char finalX,unsigned char finalY, THEBOARD Board); //what does this function do? -reza 1/25

/*delete a move*/
void DeleteMove(MOVE *TargetMove);

#endif
