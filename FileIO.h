/****************************************************************/
/* FileIO.h 							*/
/* 								*/
/* Author: Michael Barbosa					*/
/* Date: 01/22/2018			 			*/
/* 								*/
/* Modifications: 						*/
/*	Bianca Doronila		- 01/25/2018			*/
/*	Cesar Alvarenga		- 				*/
/*		updated the parameters for StringToMove Cesar	*/
/*		 - 9:30PM					*/
/*								*/
/****************************************************************/

#ifndef FILEIO_H
#define FILEIO_H

#include "move.h"
#include "chessLayout.h"
#define SLEN 40

/* write into file */
int WriteToFile();

/* Converts a string to a numerical move set */
/*int StringToMove(char input[3], THEBOARD Board);*/

/* Converts a numerical move to a string */
/*int MoveToString(board);*/

/*initialize log file*/
void LogInitialize();

/* Writes a move to a log file*/
void LogMove(MOVE *movingPiece, int turncount);

/* Writes check to a log file */
void LogCheck(int fcolor);

/* Writes checkmate to a log file */
void LogMate(int color);

/*write stalemate to a log file*/
void LogStaleMate();

/*prints to log when en passant happens*/
void LogEnpassant();

/*prints to log when caslting happens*/
void LogCastle();

/*print to log when a promotion happens*/
void LogPromotion();

/*prints the log file*/
void PrinttFile();

#endif
