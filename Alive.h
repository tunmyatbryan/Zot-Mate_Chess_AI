/*
 * Header file for Alive.h
 * 
 *
 */
#ifndef ALIVE_H
#define ALIVE_H

#include <assert.h>
#include"chessLayout.h"

typedef struct AliveList ALIST;
typedef struct AliveListEntry AENTRY;

/*implement header struct that points to both the black and white lists?
 * adds complexity but reduces what has to be passed around*/

struct AliveList{
	unsigned int Length;
	unsigned int Color; /*for now 0 is white, 1 is black*/
	AENTRY *First;
	AENTRY *Last;
};
struct AliveListEntry{
	ALIST *List;
	AENTRY *Next;
	AENTRY *Prev;
	PIECE *AlivePiece;
};

ALIST *CreateAliveList(THEBOARD MasterBoard, int color);

void DeleteAliveList(ALIST *list);

void AppendAliveList(ALIST *list, PIECE *piece);

PIECE *DeleteAliveEntry(AENTRY *e);

#endif
