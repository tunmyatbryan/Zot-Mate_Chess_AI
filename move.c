/*
Source file for move
Change Log:
1/25 3:50 	-Reza 	- Added Def. for AppendMove, DeleteMoveList, DeleteMove
			- Questionable Assert on ln.107 under DeleteMove funct
			- Questionable free() under DeleteMove. see function.
initial: ???
change 1: added definition for
 
*/
#include <stdlib.h>
#include <assert.h>
#include "move.h"
#include "chessLayout.h"


/*Create a new Move List*/
MLIST *CreateMoveList()
{
	MLIST *newList = (MLIST*)malloc(sizeof(MLIST));

	if (newList != NULL)
	{
		newList->Length = 0;
		newList->First = NULL;
		newList->Last = NULL;
	}

	assert(newList);

	return newList;
}
/*Delete Move List*/
void DeleteMoveList(MLIST *list)
{
	MENTRY *e, *n;
	MOVE *m;
	assert(list);
	e = list->First;
	while(e)
	{
		n = e->Next;
		m = DeleteMoveEntry(e);
		DeleteMove(m);
		e = n;
	}
	
	free(list);
}
/*Delete a move entry*/
MOVE *DeleteMoveEntry(MENTRY *e)
{
	assert(e);
	
	if(e->Prev == NULL)
	{
		e->List->First = e->Next;
		if(e->Next)
			e->Next->Prev = NULL;
	
	}
	else if (e->Next == NULL)
	{
		e->List->Last = e->Prev;
		if(e->Prev)
			e->Prev->Next = NULL;
	}
	else 
	{
		e->Prev->Next = e->Next;
		e->Next->Prev = e->Prev;
	}
	
	e->List->Length--;
	MOVE *m;
	assert(e);
	m = e->PotentialMove;
	free(e);
	return(m);
}


/*Append Move List*/
void AppendMoveList (MLIST *list, MOVE *PossibleMove)
{
	assert(list);
	assert (PossibleMove);

	MENTRY *e = NULL;
	e = (MENTRY*)malloc(sizeof(MENTRY));
	assert(e);

	e->List = list;
	e->Next = NULL;
	e->Prev = NULL;
	e->PotentialMove = PossibleMove;

	if (list->Last)
	{		
		e->List = list;
		e->Next = NULL;
		e->Prev = list->Last;
		list->Last->Next = e;
		list->Last = e;
	}

	else
	{
		e->List = list;
		e->Next = NULL;
		e->Prev = NULL;
		list->First = e;
		list->Last = e;
	}

	list->Length++;

}



/*Create a Move*/
MOVE *CreateMove(unsigned char initialX, unsigned char  initialY, unsigned char finalX, unsigned char finalY, THEBOARD Board)
{
	/*MOVE *move = malloc(sizeof(MOVE));*/
	MOVE *move = (MOVE *)malloc(sizeof(MOVE));
	if (move == NULL)
	{
		return NULL;
	}

	move->initX = initialX;
	move->initY = initialY;
	move->finX = finalX;
	move->finY = finalY;

	/*This Part is likely buggy, we need to test the passing around an array of pointers*/
	/* and how to assign the pointers in the array to other pointers in our structures*/

	/*since THEBAORD Parameter was added, this two lines needed editing - cesar*/
	move->Mover = Board.board[initialX][initialY];
	move->Capture = Board.board[finalX][finalY];
	
	/*added variables for minimax and maximin*/
	move->min = -1;
	move->max = 0;
	if(move->Capture == NULL)
		move->score = 0;
	else
		move->score = move->Capture->value;

	return move;
}

/*Delete a Move*/
void DeleteMove(MOVE *TargetMove)
{
	assert(TargetMove);
	
	//Handle Pointers first
	free(TargetMove);  	
}

