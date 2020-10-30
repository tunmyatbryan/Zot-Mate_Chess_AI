#include <stdlib.h>
#include <assert.h>
#include "Alive.h"



/*Create a new Alive List*/

ALIST *CreateAliveList(THEBOARD MasterBoard, int color)
{
	ALIST *newlist = (ALIST*)malloc(sizeof(ALIST));

	if (newlist != NULL)
	{
		newlist->Length = 0;
		newlist->Color = color;
		newlist->First = NULL;
		newlist->Last = NULL;
	}

	assert(newlist);
	
	/*iterate throught the board and populate the AliveList for the given color*/
	int i, j;
	int PieceColor;
	PIECE *CurrentPiece;	
	for(j=0; j<8 ; j++)
	{
		for(i=0; i<8 ;i++)
		{
			CurrentPiece = MasterBoard.board[i][j];
			if(CurrentPiece)
			{
				PieceColor = CurrentPiece->color;
			
				if(PieceColor == color)
				/*if the piece color is correct add it to the alive list*/
				{
					AppendAliveList(newlist, CurrentPiece);				
				}
			}
			if(newlist->Length == 16)
			/*if the list has 16 entries, meaning the max number of pieces, break*/
			{
				i = 8;
				j = 8;
			}
		}
	}
	CurrentPiece = NULL;
	return newlist;
}

/*Delete Alive List*/

void DeleteAliveList(ALIST *list)
{
	assert(list);
	
	AENTRY *e, *n;
	PIECE *p;
	assert(list);
	e = list ->First;
	while(e)
	{
		n = e->Next;
		p = DeleteAliveEntry(e);
		DeletePiece(p);
		e = n;	
	}
	
	free(list);
}

/*Append Alive List*/

void AppendAliveList(ALIST *list, PIECE *piece)
{
	assert(list);
	assert(piece);

	AENTRY *e = NULL;
	e = (AENTRY*)malloc(sizeof(AENTRY));
	assert(e);

	e->List = list;
	e->Next = NULL;
	e->Prev = NULL;
	e->AlivePiece = piece;

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

PIECE *DeleteAliveEntry(AENTRY *e)
{
	assert(e);
	/*handle de ptr*/
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
	PIECE *p;
	p = e->AlivePiece;
	free(e);
	return(p);
	
}
