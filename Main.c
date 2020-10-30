#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "AI.h"
#include "Alive.h"
#include "chessLayout.h"
#include "Check.h"
#include "CheckMateTest"
#include "Legal.h"
#include "Locomotion"
#include "move.h"


/* global var */
	const char *fname;

/* Declaration for IO writing to a file */
int WriteToFile();

int main(){
	int gameType;
	char player1[SIZE];
	char player2[SIZE];
	int checkmate = 0;

	char initX[3];
	char initY[3];

	char Xpos[3];
	char Ypos[3];

	THEBOARD status;

tryAgain:
	printf("\tWELCOME TO ZOT-MATE, THE BEST CHESS SIMULATOR\n");
	printf("CHOOSE GAME TYPE:\n");
	printf("1. USER VS AI\n");
	printf("2. USER VS USER\n");
	printf("3. AI VS AI\n");
	
	printf("YOUR OPTION(type \"1\" or \"2\" or \"3\"): ");
	scanf("%d", &gameType);
	
	switch(gameType) {
		case 1:
		printf("User vs AI is still under progress, sorry.\n");
		return 0;
		break;
		
		case 2:
		printf("User vs User is still under progress, may have bugs.\n");
	color:	
		printf("CHOOSE YOUR COLOR:\n1. BLACK\n2. WHITE\n");
		printf("YOUR OPTION(type \"black\" or \"white\"): ");
        	scanf("%s", player1);
		
		if(strcmp(player1, "black") != 0 && strcmp(player1, "white") != 0){
			printf("incorrect input\n");
			goto color;
		}	

		if(strcmp(player1, "black") == 0){
			strcpy(player2, "white");
			printf("Player1 is BLACK\n");
			printf("Player2 is WHITE\n");
		} 
		else {
			strcpy(player2, "black");
			printf("Player1 is WHITE\n");
			printf("Player2 is BLACK\n");
		}

		printf("\n");
		printf("\n");
		printf("\n");
		status = Load_Pieces(player1, player2);
		board(status);
		
		while(!checkmate){
		printf("\nMAKE A MOVE FROM: ");
		printf("Y-axis(for example 'A5'): \n");
		scanf("%s", initX);
		printf("X-axis(for example 'B5'): \n");		
		scanf("%s", initY);

		printf("\nMAKE A MOVE FROM: ");
		printf("Y-axis(for example 'A5'): \n");
		scanf("%s", Xpos);
		printf("X-axis(for example 'B5'): \n");		
		scanf("%s", Ypos);
		
		CreateMove(initX, initY, Xpos, Ypos, status);
				
		printf("for now this will end the game - type \"1\"");
		scanf("%d", &checkmate);
		}
		break;

		case 3:
		printf("AI vs AI is still under progress sorry.\n");
		return 0;
		break;

		default:
		printf("Incorrect option, please try again.\n");
		goto tryAgain;
	}

return 0;
}

// Definition for WriteToFile
int WriteToFile()
{
	fname = "ChessLog.txt";
	FILE *File;
	File = fopen("ChessLog.txt", "w");
	
	int GameOver    = 0;
	int moveCounter = 0;

	// Error handling for file open 
	if ( !File )
	{
		printf("\nCan't open file \"%s\" for writing...\n",fname);
		return 1;
	}

	while ( GameOver <= 10 )
	{
		moveCounter++;
		
		fprintf(File, "MOVE #: "       );
		fprintf(File, "%d", moveCounter);
		fprintf(File, "\tPath ( "      );
		fprintf(File, " : "            );
		fprintf(File, ") "             );
		fprintf(File, "\tUser Color: " );
		fprintf(File, "\tPiece Type: " );
		fprintf(File, "\tTime: "       );
		fprintf(File, "\n"             );
		
		GameOver++;
	}
	fclose(File);
	printf("Successfully generated ChessLog.txt file.");
	return 0;
} // WriteToFile













