/****************************************************************/
/* FileIO.h 							*/
/* 								*/
/* Author: Michael Barbosa					*/
/* Date: 01/22/2018			 			*/
/* 								*/
/* Modifications: 						*/
/*
 * BIANCA DORONILA		01/25/2017			*/
/*	--- WriteToFile function				*/
/****************************************************************/
#include <stdio.h>
#include "FileIO.h"

int WriteToFile()
{
    char fname[SLEN] = "ChessLog.txt";
    FILE *File;
    File = fopen("ChessLog.txt", "w");
    /*int GameOver = 0;*/
    /*int moveCounter = 0;*/

    /*Error handling for file open*/
    if (!File)
    {
   	printf("\nCan't open file \"%s\" for writing!\n", fname);
	return 1;
    }
/*
    while(GameOver <= 10)
    {
	moveCounter++;
*/    

/*    fprintf(File, "\tPath ( ");*/
         /*fputc(GetBoardPosition(piece, x, y)), File);*/ 
/*    fprintf(File, " : ");*/
        /* fputc(GetBoardPosition(piece, x, y)), File); */
/*    fprintf(File, ") "); */
/*    fprintf(File, "\tUser Color: ");*/
	/* fputc(GetUserColor(), File); */
/*    fprintf(File, "\tPiece Type: ");*/
	/* fputc(GetPieceType(), File); */
/*    fprintf(File, "\tTime: ");*/
	/* fputc(GetCurrentTime(), File); */
/*    fprintf(File, "\n");
	GameOver++;
    }
    fclose(File);
    printf("Successfully generated ChessLog.txt file.");
*/

    return 0;
}



/* Definition to convert a string to a numerical move
int StringToMove(string, board)
{
	printf("Under Maintinance");
	return move;
}
*/

/* Definition to convert a numerical move to a string 
char MoveToString(move)
{
	printf("Under Maintinance");
	return string;
}
*/
void LogInitialize()
{
	FILE *File;
	File = fopen("ChessLog.txt", "w");
	fclose(File);
}




/* Definition to to log a move to a txt file*/
void LogMove(MOVE *movingPiece, int turncount)
{
	FILE *File;
	char initX = (char)movingPiece->initX+65;
	char initY = (char)movingPiece->initY+1;
	char finX = (char)movingPiece->finX+65;
	char finY = (char)movingPiece->finY+1;
	int color = movingPiece->Mover->color;

	/*create a txt file or add on to one*/
	File = fopen("ChessLog.txt", "a");
	fprintf(File, "Move count: %d ", turncount);
	fprintf(File, "Start: %c%d ", initX, initY);
	fprintf(File, "End: %c%d ", finX, finY);
	if(color)
	{
		fprintf(File, "color: Black");
	}	
	else
	{
		fprintf(File, "color: White");
	}
	
	fprintf(File, "\n");	
	/*if(mateFlag == 2 || mateFlag == 3)
	{*/
		fclose(File);
	//}
}


/* Definition to log a Check to a txt file */
void LogCheck(int color)
{
	FILE *File;
	/*add to the file*/
	File = fopen("ChessLog.txt", "a");
	if(color == 1)
	{
		fprintf(File, "Black is in Check");		
	}
	else
	{
		fprintf(File, "White is in Check");
	}
	fprintf(File, "\n");
	fclose(File);
}


/* Definition to log a Checkmate to a txt file*/
void  LogMate(int color)
{
	FILE *File;
	/*add to the file*/
	File = fopen("ChessLog.txt", "a");
	if(color == 1)
	{
		fprintf(File, "Black got meme'd by White");
	}
	else
	{
		fprintf(File, "White got meme'd by Black");
	}
	fprintf(File, "\n");
	fclose(File);
}

/*definition to log a stalemate to a txt file*/
void LogStaleMate(){
	FILE *File;
	/*add to the file*/
	File = fopen("ChessLog.txt", "a");
	fprintf(File, "The game ends in a stalemate, both of yall got meme'd");
	fprintf(File, "\n");
	fclose(File);
	
}

void LogEnpassant(){
	FILE *File;
	File = fopen("ChessLog.txt", "a");
	fprintf(File, "Special move \"en passant\" activated");
	fprintf(File, "\n");
	fclose(File);
}

void LogCastle(){
	FILE *File;
	File = fopen("ChessLog.txt", "a");
	fprintf(File, "Special move \"castle\" activated");;
	fprintf(File, "\n");
	fclose(File);
}

void LogPromotion(){
	FILE *File;
	File = fopen("ChessLog.txt", "a");
	fprintf(File, "Special move \"Promotion\" activated");
	fprintf(File, "\n");
	fclose(File);
}

        /*definiton of printFile*/
void PrintFile(){
        int check;
        FILE *fname;
        fname = fopen("ChessLog.txt", "r");
        /*if readable*/
        if(fname)
        {
                        /*while there is still a character to read*/
                while((check = getc(fname)) != EOF)
                {
                                /*print that character*/
                        putchar(check);
                }
                        /*close the file after we are done with it*/
                fclose(fname);
        }
	
}

