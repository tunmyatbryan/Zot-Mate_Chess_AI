/* Psuedocode for main function glue logic*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "move.h"
#include "Alive.h"
#include "chessLayout.h"
#include "Legal.h"
#include "Check.h"
#include "Locomotion.h"
#include "AI.h"
#include "FileIO.h"

MOVE *playerturn(THEBOARD InputBoard, int playercolor);

int main (void)
{
	/*Ask player to select color*/
	int menuchoice;
	int playercolor;
	int aicolor;
	int MenuEsc = 1;
	while(MenuEsc == 1)
	{
		printf("1.Player vs Player \n2.Player vs AI \n3.AI vs AI\n\nPlease Make your Selection: ");
		scanf("%d", &menuchoice);
		if((menuchoice > 0)&&(menuchoice < 4))
		{
			MenuEsc = 0;
		}
		else
		{
		printf("Input invalid, plese choose an option 1-3\n\n");
		}
	}
	MenuEsc = 1;
	
	while(MenuEsc == 1)
	{
		if(menuchoice == 3)
		{
			MenuEsc = 0;
			playercolor = 0;
		}
		else
		{
			printf("which side would you like to play (0 for white/1 for black):");
			scanf("%d", &playercolor);
			if((playercolor == 1)||(playercolor == 0))
			{
				MenuEsc = 0;
			}
			else
			{
				printf("Invalid input, please choose an option 0 or 1");
			}
		}
	}
	printf("\n");
	aicolor = 1-playercolor;

	/*Initialize the board and necessary values*/	
	int turn = 0; /*This will count the number of turns completed (as in moves made)*/
	int turncolor = 0; /*0 if it is white's turn, 1 if it is black's turn*/
	LogInitialize();
	THEBOARD MasterBoard = InitializeBoard();	/*create board*/
							/*populate board with piecs*/
	PrintBoard(MasterBoard);					
	ALIST *WhiteAlive = CreateAliveList(MasterBoard, 0);
	ALIST *BlackAlive = CreateAliveList(MasterBoard, 1);		/*generate alive lists(may need to pass the board)*/
	
	/*Game start*/
	int esc = 1;
	int mechlegal = 0;
	int checklegal = 0;

	int mate = 0; /*0=nothing, 1=check, 2=checkmate, 3=stalemate*/
	/*int stalemate;*/

	int LListLength = 0;
	int compareX, compareY;
	
	int ctrl = 0;
	int x,y;

	char piecetype;
	PIECE *DesiredPiece = NULL; 
	MOVE *DesiredMove = NULL;
	MLIST *LegalList = NULL;
	MENTRY *NextMove = NULL;
	THEBOARD DuplicateBoard;

	while(esc == 1)
	{
		printf("GUCCI GANG\n");
		if (menuchoice == 3)
		{
			/*sleep(1);*/
		}
		ctrl = 0;
		/*establish which color's turn it is*/
		turncolor = turn%2;
	/*	printf("Turn start \nturncolor = %d \n", turncolor);*/

		/*Get a pointer to a move from either the AI or the player*/
		if(turncolor == 0)
		{
			if (menuchoice == 1) 
			{
				DesiredMove = playerturn(MasterBoard, 0);
			}
			else if (menuchoice == 2) 
			{
				if(aicolor == 0)
				{
					printf("AI Thinking . . .\n");
					DesiredMove = AIRandomMove(WhiteAlive, &MasterBoard);
				}
				else
				{
					DesiredMove = playerturn(MasterBoard, 0);
				}
			}

			else if (menuchoice == 3)
			{
				printf("AI Thinking . . . \n");
				DesiredMove = AIRandomMove(WhiteAlive, &MasterBoard);
			}
		}
		else if(turncolor == 1) 
		{
			if (menuchoice == 1) 
			{
				DesiredMove = playerturn(MasterBoard, 1);
			}
			else if(menuchoice == 2) 
			{
				if(aicolor == 1)
				{
					printf("AI Thinking . . .\n");
					DesiredMove = AIRandomMove(BlackAlive, &MasterBoard);
				}
				else
				{
					DesiredMove = playerturn(MasterBoard, 1); 
				}
			}
			else if(menuchoice == 3)
			{
				printf("AI Thinking. . .\n");
				DesiredMove = AIRandomMove(BlackAlive, &MasterBoard);
			}

		}
		else
		{
			printf("this wasn't supposed to happen, something fucked up");
			esc = 0;
		}

		/*Now that we have the potential move, we need to check the legality of the move*/
		

	/*	printf("DEBUG desired move: %d %d to %d %d \n", DesiredMove->initX, DesiredMove->initY, DesiredMove->finX, DesiredMove->finY);	*/

		mechlegal = 0;
		checklegal = 0;		/*set the two legality flags to 0*/

		/*check the mechanical legality, based upon the piece type*/
		DesiredPiece = DesiredMove->Mover;
		piecetype = DesiredPiece->type;
	/*	printf("DEBUG piecetype: %c \n", piecetype); */
		switch(piecetype) 
		{
			case 'P':
				LegalList = PawnLegalMoveListGen(DesiredPiece, MasterBoard);
				break;
			case 'R':
				LegalList = RookLegalMoveListGen(DesiredPiece, MasterBoard);
				break;
			case 'B':
				LegalList = BishopLegalMoveListGen(DesiredPiece, MasterBoard);
				break;
			case 'H':
				LegalList = KnightLegalMoveListGen(DesiredPiece, MasterBoard);
				break;
			case 'K':
				LegalList = KingLegalMoveListGen(DesiredPiece, MasterBoard);
				break;
			case 'Q':
				LegalList = QueenLegalMoveListGen(DesiredPiece, MasterBoard);
				break;
			default:
				printf("piece type not found, error");
		}
				/*Check the potential move is on the legal list*/
		LListLength = LegalList->Length;
	/*	printf("DEBUG LListLength: %d \n", LListLength);*/
		if(LListLength == 0)
		{
			mechlegal = 0;			/*if the list is of length 0 then the potential 
							  move cannot be on it, thus it fails the legal
							  test*/
		/*	printf("DEBUG Legal List Length = 0\n");*/

			DeleteMoveList(LegalList); 	/*clean up legal list*/
		}
		else
		{
			NextMove = LegalList->First;

			while(ctrl == 0)
			{
				compareX = NextMove->PotentialMove->finX;
				compareY = NextMove->PotentialMove->finY;
			/*	printf("DEBUG Compare X: %d \n", compareX);
				printf("DEBUG Compare Y: %d \n", compareY);
			*/	if((compareX == DesiredMove->finX)&&(compareY == DesiredMove->finY))
				/*if the final xy of the desired move and a move on the list match*/
				{
					/*The Desired Move is on the Legal Move List*/
				/*	printf("DEBUG mechanically valid move\n");*/
					mechlegal = 1;
					ctrl = 1;
					DeleteMoveList(LegalList);
				/*	printf("DEBUG move list deleted\n\n");*/
				}
				else
				/*if the desired XY does not match the current list entry*/
				{
					NextMove = NextMove->Next;
					if(NextMove == NULL)
					/*if we have reached the end of the list*/
					{
						mechlegal = 0;
						ctrl = 1;
					/*	printf("DEBUG The move is not on the legal move list\n");*/
						DeleteMoveList(LegalList); 
					}
				}
			}
		}
		
		/*Check the status of the mechlegal flag*/
		if(mechlegal == 0)
		/*if the move is mechanically illegal then there is no need to test check*/
		{
			printf("The desired move is mechanically illegal\n");

		}
		else if(mechlegal == 1) 
		/*if the move is mechanically legal we can test check*/
		{
			/*Check if making the legal move puts the current player in check*/
				/* duplicate the current board*/
			for(x=0; x<8; x++)
			{
				for(y=0; y<8; y++)
				{
					DuplicateBoard.board[x][y] = MasterBoard.board[x][y]; /*This may need to be fixed*/
				}
			}

			/*FOR DEBGGING ONLY
			printf("\n DUPLICATE BOARD\n");
			PrintBoard(DuplicateBoard);
			printf("\n");
			--------*/

			/* execute the move on the duplicate board*/
			MovePiece(DesiredMove, &DuplicateBoard, 0, WhiteAlive, BlackAlive);
		/*	printf("DEBUG Created duplicate board and executed move\n");*/
				/* pass the board and a color flag to TestCheck()*
				 * return 1 if in check, 0 if not in check
				 * set checklegal to 1-TestCheck()*/

			/*FOR DEBUGGING ONLY
			printf("\n DUPLICATE BOARD W/ SIMULATED MOVE\n");
			PrintBoard(DuplicateBoard);
			printf("\n");
			---------*/

			checklegal = TestCheckLegal(DuplicateBoard, turncolor);
		/*	printf("DEBUG Test check legal executed\n");*/
			checklegal = 1-checklegal;
			
				/* if checklegal = 0 then the move places the current player in check
				 * and is illegal
				 * if checklegal = 0 then pass the MasterBoard to the CheckMate()
				 * function to determine if it is Mate
				 * If it is mate, start endgame procedure
				 * If it is not mate but check, say the move is illegal and ask for
				 * another input (don't increment turn counter)
				 * If checklegal = 1, say the move is legal and execute the move*/
			if(checklegal == 0)
			/*if the desired move places its own side in check*/
			{
				printf("The desired move is illegal, it puts your own king in check\n");
			}		
			else 
			/*if the move is mechanically legal and does not put its own color in check then
			 * execute the move
			 * log the move
			 * increment the turn counter*/
			{	/*Print the board and see if the other side is in check/checkmate*/
				MovePiece(DesiredMove, &MasterBoard, 1, WhiteAlive, BlackAlive);
			
				if(DesiredMove->Mover->type == 'P' && (DesiredMove->Mover->Ypos == 0 || DesiredMove->Mover->Ypos == 7))
					Promotion(DesiredMove->Mover, &MasterBoard, menuchoice, aicolor);
				
			/*	printf("DEBUG Made the move on the MasterBoard\n");*/
				PrintBoard(MasterBoard);
				LogMove(DesiredMove, turn);

				mate = TestCheckMate(MasterBoard, 1-turncolor, WhiteAlive, BlackAlive);
			/* as of 2/3 @ 2pm this function was causing segmentation faults*/			
			/*	printf("DEBUG TestCheckmate Executed. mate = %d \n", mate);*/
				turn++; 
			}
				/* need to delete duplicate board once finished*/
		/*	DeleteBoard(DuplicateBoard);	*/
		}		
		/*Test the mate flag here*/
		if (mate == 1)
		/*if the other side is in check*/
		{
			if(turncolor == 0)
			{
				printf("Black is in check\n");
				LogCheck(1);		
			}
			else if(turncolor == 1)
			{
				printf("White is in check\n");
				LogCheck(0);
			}
		
		}
		else if (mate == 2)
		/*If the other side is in check mate*/
		{
			if(turncolor == 0)
			{
				printf("That's checkmate! White wins, get meme'd Black\n");
				LogMate(1);
			}
			else if(turncolor == 1)
			{
				printf("That's checkmate! Black wins, get meme'd White\n");
				LogMate(0);
			}
			esc = 0;
		}		
	/*Clean Up ahead of the next turn */
/*	printf("DEBUG Got to turn Clean up\n");*/
	DeleteMove(DesiredMove);
	DesiredPiece = NULL;
	DesiredMove = NULL;
	LegalList = NULL;
	NextMove = NULL;
	}
	/*Endgame procedure*/
	
	/*Delete the Alive Lists*/
	DeleteAliveList(WhiteAlive);
	DeleteAliveList(BlackAlive);	
	
	/*Clean up the board (?)*/
	DeleteBoard(&MasterBoard);
	DeleteBoard(&DuplicateBoard);
	
	return 0;
}


MOVE *playerturn(THEBOARD InputBoard, int playercolor)
{
	int iX, iY;
	int fX, fY;
	int esc = 1;
	int PieceColor;
/*	printf("%d",playercolor);*/
	PIECE *TempPiece = NULL;
	MOVE *DesiredMove = NULL;	

	while (esc == 1)
	{
		/*ask user for first part of input*/
		printf("Please enter the initial X position (0-7)\n");
		scanf("%d", &iX);
		if((iX<0) || (iX>7))
		{
			printf("numerical input out of range, please enter a value 0-7\n");
		}
		else
		{
			printf("Please enter the initial Y position (0-7)\n");
			scanf("%d", &iY);
			if((iY>7)||(iY<0))
			{
			 printf("numerical input out of range, please enter a value 0-7\n");
			}
			else
			{
			/*check that that input references a piece within the board*/
				TempPiece = InputBoard.board[iX][iY];
				if(TempPiece)
				{
					/*check if the piece is the right color*/
					PieceColor = TempPiece->color;
					if(PieceColor == playercolor)
					{
					esc = 0;
					}
					else
					{
					printf("You can't move that color piece \n");
					}
				}
				else
				{
				printf("You can't select an empty space\n");
				}
			}
		}
	}
	
	esc = 1;
	/*	PrintPiece(TempPiece);*/
	TempPiece = NULL;

	while(esc == 1)
	{
		/*Get the second part of the input*/
		printf("Please enter the final X position:\n");
		scanf("%d", &fX);
		if((fX<0) || (fX>7))
		{
			printf("numerical input out of range, please enter a value 0-7\n");
		}
		else
		{
			printf("Please enter the final Y position\n");
			scanf("%d", &fY);
			
			if ((fY<0)||(fY>7))
			{
				printf("numerical input out of range, please input a number 0-7\n");
			}
			else
			{
				esc = 0;
			}
		}
	}
	/*Return that move*/
	DesiredMove = CreateMove(iX,iY,fX,fY,InputBoard);
	
	return DesiredMove;

}

