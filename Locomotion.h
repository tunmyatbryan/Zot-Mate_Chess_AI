/* updated the header files and function parameters - cesar 1/27/2018 11:45PM*/

#ifndef LOCOMOTION_H
#define LOCOMOTION_H

#include "move.h"
#include "chessLayout.h"
#include "Alive.h"
#include "FileIO.h"
#include <stdlib.h>
#include <stdlib.h>
#include <assert.h>

/* move piece function declaration */
void MovePiece(MOVE *DesiredMove, THEBOARD *InputBoard, int update, ALIST *white, ALIST *black);

void MovePieceAI(MOVE *DesiredMove, THEBOARD *InputBoard);

/*function to promote the pawn*/
void Promotion(PIECE *Pawn, THEBOARD *Board, int option, int aicolor);

/*function to handle how a piece gets captured*/
void Capture(PIECE *capturedPiece, THEBOARD Board);

#endif

