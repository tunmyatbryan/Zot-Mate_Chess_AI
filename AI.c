/*
*
*Header file for AI.c
*
* */


/*The function has been cleaned up a bit still probably need further debugging*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "AI.h"



MOVE *AIRandomMove(ALIST *alivelist, THEBOARD *Board)
{
	THEBOARD *DuplicateBoard;
	srand((unsigned int)time(NULL));
	MLIST *daddyLegalList = CreateMoveList();
	MLIST *concatenateList;
	MENTRY *mcurrent;
	MOVE *randmove;

	AENTRY *current;

	PIECE *piece;
	/*int count = Board->globalCount;
	*/
	

	
	
	int alistlength, llistlength;
	int randpiece, randm;
	/*int esc = 1;*/

	char piecetype;

	srand((unsigned int)time(NULL));

	/*set length of alivelist.*/

	alistlength = alivelist->Length;

	/*if color is white, then we can start a bandit*/
	/*if (color == 0)
	{


	}*/

	/*if color is black, then we can start a defense*/
	/*if (color == 1)	
	{


	}*/


	/*select all pieces from the alive list and create daddyList */
	current = alivelist->First;

	while (current)
	{

		/*figure out what piece type it is and call the proper legal moves function*/

		piece = current->AlivePiece;
		piecetype = piece->type;

		switch (piecetype)
		{
		case 'P':	/*Pawn case*/
		{
			concatenateList = PawnLegalMoveListGen(piece, *Board);
			break;
		}
		case 'R':	/*Rook case*/
		{
			concatenateList = RookLegalMoveListGen(piece, *Board);
			break;
		}
		case 'B':	/*Bishop case*/
		{
			concatenateList = BishopLegalMoveListGen(piece, *Board);
			break;
		}
		case 'H':	/*Knight case*/
		{
			concatenateList = KnightLegalMoveListGen(piece, *Board);
			break;
		}
		case 'K':	/*King case*/
		{
			concatenateList = KingLegalMoveListGen(piece, *Board);
			break;
		}
		case 'Q':	/*Queen case*/
		{
			concatenateList = QueenLegalMoveListGen(piece, *Board);
			break;
		}
		default:
			printf("piece type not recognized, AI error");
			return NULL;
		}

		/*check that there are entries on the list and continue*/
		
		mcurrent = concatenateList->First;
		while(mcurrent)
		{
			randmove = mcurrent->PotentialMove;
			AppendMoveList(daddyLegalList, randmove);
			mcurrent = mcurrent->Next;
		}

		//DeleteMoveList(concatenateList);
		current = current->Next;
		
	}
	
	int color = alivelist->First->AlivePiece->color;
	
	piece = TestCheckLegalAttacker(*Board, color);
	if (piece != NULL)
	{
		randm = rand() % daddyLegalList->Length;

		mcurrent = daddyLegalList->First;
		if (mcurrent == NULL)
		{
			printf("No first move in legal move list, AI quitting");
			return NULL;
		}

		while (randm > 0)
		{
			mcurrent = mcurrent->Next;
			randm--;
		}

		randmove = mcurrent->PotentialMove;
		
	}
	else
	{
	
		/*Create a duplicate board for simulation*/
	
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				DuplicateBoard->board[i][j] = Board->board[i][j];

		/*select a random move from the legal moves list*/

	
		randmove = RecursiveCall(daddyLegalList, DuplicateBoard);
	

		/*

	*/

	
		int initialX, initialY, finalX, finalY;
		initialX = randmove->initX;
		initialY = randmove->initY;
		finalX = randmove->finX;
		finalY = randmove->finY;

		randmove = CreateMove(initialX, initialY, finalX, finalY, *Board);



		/*
		legallist = NULL;
		current = NULL;
		piece = NULL;
		*/
		/*return that move*/
	
		DeleteMoveList(daddyLegalList);
	
		return randmove;
	}

}

MOVE* RecursiveCall(MLIST *masterList, THEBOARD *Board)
{
	MLIST* dumpList = CreateMoveList();
	THEBOARD DuplicateBoard;
	PIECE *enemyAttacker;
	int enemyColor;

	/*can be implemented recursively*/
	MLIST* sublist;
	MENTRY* subentry;
	MOVE* submove;
	PIECE* subpiece;

	MOVE *randmove;

	MENTRY* mentry;
	MOVE *mcurrent, *mmax, *mhighscore;
	PIECE *pcurrent;
	/*char ptype;*/ 
	/*int color, value, Xpos, Ypos, min, max;*/

	/*PIECE *aiPiece;*/
	PIECE *aiDefender;
	/*MOVE* daddyMove;*/
	int minFlag = 0;
	int random;

	

	/*asign basic tradeoff points for each possible move, find min and max of each move*/
	{
		mentry = masterList->First;
		

		while (mentry)
		{	
			/*create temp board for each potential move*/
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					DuplicateBoard.board[i][j] = Board->board[i][j];
				}
			}
			minFlag = 0;
			mcurrent = mentry->PotentialMove;
			pcurrent = mcurrent->Mover;
			enemyColor = 1 - mcurrent->Mover->color;
			/*find attacker & defender for each move, set tradeoff points*/
			enemyAttacker = TestCheckLegalBlocker(*Board, enemyColor, mcurrent->finX, mcurrent->finY);
			aiDefender = TestCheckLegalBlocker(*Board, 1 -enemyColor, mcurrent->finX, mcurrent->finY);

			if (aiDefender)
				mentry->PotentialMove->score += 15;
			if (enemyAttacker)
			{
				minFlag = 1;
				mentry->PotentialMove->score -= mentry->PotentialMove->Mover->value;
				mentry->PotentialMove->min = -2;
			}
			/*if no enemyAttacker for the move, execute move and analyze next potential*/
			
			{
				/*Prioritize an open pawn promotion	*/
				if (pcurrent->type == 'P' && (mcurrent->finY == 7 || mcurrent->finY == 0))
				{	
					mcurrent = randmove;
					int initialX, initialY, finalX, finalY;
					initialX = randmove->initX;
					initialY = randmove->initY;
					finalX = randmove->finX;
					finalY = randmove->finY;

					randmove = CreateMove(initialX, initialY, finalX, finalY, DuplicateBoard);
					DeleteMoveList(dumpList);
					return randmove;

				}
				/*create a 'hold' piece in memory*/
				PIECE* phold = NewPiece(pcurrent->type, pcurrent->color, pcurrent->value, 
										pcurrent->Xpos, pcurrent->Ypos);

				/*Locomotion the move on dupe board, modifiying the piece coordinates*/
				MovePieceAI(mcurrent, &DuplicateBoard);

				/*Generate a new List for the moved piece. No attacker to worry about*/
				switch (pcurrent->type)
				{
				case 'P':	/*Pawn case*/
				{
					sublist = PawnLegalMoveListGen(pcurrent, DuplicateBoard);
					break;
				}
				case 'R':	/*Rook case*/
				{
					sublist = RookLegalMoveListGen(pcurrent, DuplicateBoard);
					break;
				}
				case 'B':	/*Bishop case*/
				{
					sublist = BishopLegalMoveListGen(pcurrent, DuplicateBoard);
					break;
				}
				case 'H':	/*Knight case*/
				{
					sublist = KnightLegalMoveListGen(pcurrent, DuplicateBoard);
					break;
				}
				case 'K':	/*King case*/
				{
					sublist = KingLegalMoveListGen(pcurrent, DuplicateBoard);
					break;
				}
				case 'Q':	/*Queen case*/
				{
					sublist = QueenLegalMoveListGen(pcurrent, DuplicateBoard);
					break;
				}
				default:
					printf("piece type not recognized, AI error");
					return NULL;
				}

				/*traverse the sublist, find min, max, avg. of each move score*/
				if (sublist->Length != 0)
				{
					subentry = sublist->First;

					while (subentry)
					{
						submove = subentry->PotentialMove;
						subpiece = submove->Mover;
						/*min = 0 is a special flag to signify that the spot wont get attacked*/
						if (minFlag == 0)
							mcurrent->min = 0;
						/*find attacker & defender for each move, set tradeoff points*/
						/*if king is found as a potential move, set max = 300 making it a check move */
						{
							enemyAttacker = TestCheckLegalBlocker(DuplicateBoard, enemyColor, submove->finX, submove->finY);
							aiDefender = TestCheckLegalBlocker(DuplicateBoard, 1 - enemyColor, submove->finX, submove->finY);
							if (aiDefender)
								submove->score += 15;
							if(DuplicateBoard.board[submove->finX][submove->finY] != NULL)
								if (DuplicateBoard.board[submove->finX][submove->finY]->type == 'K')
									mcurrent->max = 300;
							
							if (enemyAttacker && minFlag == 0)
							{
								submove->score -= submove->Mover->value;
								mcurrent->min = -1*mcurrent->Mover->value;
							}
						}
						/*compared max and mins of mcurrent*/
						if (submove->score > mcurrent->max)
							mcurrent->max = submove->score;
						else if (submove->score < mcurrent->min)
							mcurrent->min = submove->score;
						
						subentry = subentry->Next;
					}
				}

				/*reset the piece and delete sublist, phold*/
				pcurrent->Xpos = phold->Xpos;
				pcurrent->Ypos = phold->Ypos;
				DeletePiece(phold);
				DeleteMoveList(sublist);
			}

			mentry = mentry->Next;
		}

		
	}

	/*now our masterlist has a proper score, max and min
	find pointers for highest max and highest score MOVE
	prune out any min = -1 moves from masterlist*/
	mentry = masterList->First;
	mmax = mentry->PotentialMove;
	mhighscore = mentry->PotentialMove;
	while (mentry)
	{
		int flag = 0;
		mcurrent = mentry->PotentialMove;

		/*if move is open, and points to king, put him in check*/
		if (mcurrent->max == 300)
		{	
			randmove = mcurrent;
			int initialX, initialY, finalX, finalY;
			initialX = randmove->initX;
			initialY = randmove->initY;
			finalX = randmove->finX;
			finalY = randmove->finY;

			randmove = CreateMove(initialX, initialY, finalX, finalY, *Board);
			DeleteMoveList(dumpList);
			return randmove;
		}
		if ((mentry->PotentialMove->score > mhighscore->score) && mentry->PotentialMove->min != -1)
			mhighscore = mentry->PotentialMove;
		if ((mentry->PotentialMove->max) > mmax->max && mentry->PotentialMove->min != -1)
			mmax = mentry->PotentialMove;

		/*remove moves with badflag*/
		if (mentry->PotentialMove->min == -2)
		{
			subentry = mentry->Next;
			flag = 1;
			submove = DeleteMoveEntry(mentry);
			AppendMoveList(dumpList, submove);
		}
		

		if (flag == 1)
			mentry = subentry;
		else
			mentry = mentry->Next;
	}

	/*ideal move assignment*/
	if (mmax == mhighscore)
	{
		randmove = mmax;
		int initialX, initialY, finalX, finalY;
		initialX = randmove->initX;
		initialY = randmove->initY;
		finalX = randmove->finX;
		finalY = randmove->finY;

		randmove = CreateMove(initialX, initialY, finalX, finalY, *Board);
		DeleteMoveList(dumpList);
		return randmove;
	}
	else if (mmax->score >= 0)
	{ 
		randmove = mmax;
		int initialX, initialY, finalX, finalY;
		initialX = randmove->initX;
		initialY = randmove->initY;
		finalX = randmove->finX;
		finalY = randmove->finY;

		randmove = CreateMove(initialX, initialY, finalX, finalY, *Board);
		DeleteMoveList(dumpList);
		return randmove;
	}
		
	else if (mhighscore->min >= 0)
	{
		randmove = mhighscore;
		int initialX, initialY, finalX, finalY;
		initialX = randmove->initX;
		initialY = randmove->initY;
		finalX = randmove->finX;
		finalY = randmove->finY;

		randmove = CreateMove(initialX, initialY, finalX, finalY, *Board);
		DeleteMoveList(dumpList);
		return randmove;
	}
	else if (mhighscore->min != -2 && mhighscore->score > 0)
	{
		randmove = mhighscore;
		int initialX, initialY, finalX, finalY;
		initialX = randmove->initX;
		initialY = randmove->initY;
		finalX = randmove->finX;
		finalY = randmove->finY;

		randmove = CreateMove(initialX, initialY, finalX, finalY, *Board);
		DeleteMoveList(dumpList);
		return randmove;
	}
	else if (mmax->max >= 0 && mmax->min != -2)
	{ 
		randmove = mmax;
		int initialX, initialY, finalX, finalY;
		initialX = randmove->initX;
		initialY = randmove->initY;
		finalX = randmove->finX;
		finalY = randmove->finY;

		randmove = CreateMove(initialX, initialY, finalX, finalY, *Board);
		DeleteMoveList(dumpList);
		return randmove;
	}

	if (masterList->Length != 0)
	{
		mentry = masterList->First;
		while(mentry) /*&& minFlag*/
		{
			if(mentry->PotentialMove->Capture != NULL)
			{
				randmove = mentry->PotentialMove;
				int initialX, initialY, finalX, finalY;
				initialX = randmove->initX;
				initialY = randmove->initY;
				finalX = randmove->finX;
				initialY = randmove->finY;

				randmove = CreateMove(initialX, initialY, finalX, finalY, *Board);
				DeleteMoveList(dumpList);
				return randmove;
			}
			
			mentry = mentry->Next;
		}
		
		mentry = masterList->First;
		random = rand() % masterList->Length;
		for (int i = random; i > 0; i--)
			mentry = mentry->Next;

		randmove = mentry->PotentialMove;
		int initialX, initialY, finalX, finalY;
		initialX = randmove->initX;
		initialY = randmove->initY;
		finalX = randmove->finX;
		finalY = randmove->finY;

		randmove = CreateMove(initialX, initialY, finalX, finalY, *Board);
		DeleteMoveList(dumpList);
		return randmove;
	}

	mentry = dumpList->First;
	random = rand() % dumpList->Length;
	for (int i = random; i > 0; i--)
		mentry = mentry->Next;
	
	randmove = mentry->PotentialMove;
	int initialX, initialY, finalX, finalY;
	initialX = randmove->initX;
	initialY = randmove->initY;
	finalX = randmove->finX;
	finalY = randmove->finY;

	randmove = CreateMove(initialX, initialY, finalX, finalY, *Board);
	DeleteMoveList(dumpList);
	return randmove;


}
