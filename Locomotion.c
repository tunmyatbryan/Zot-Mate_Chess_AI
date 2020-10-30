#include "Locomotion.h"

/*updated function parameters and function - cesar 1/27/2018 11:45PM*/
void MovePiece(MOVE *DesiredMove, THEBOARD *InputBoard, int update, ALIST *white, ALIST *black)
{
	PIECE *CapturedPiece = NULL;
	CapturedPiece = DesiredMove->Capture;
	ALIST *CapturedList = NULL;
	AENTRY *CapturedEntry = NULL;
	int compX, compY;
	int capX, capY;
	int CapturedColor;
	int esc = 0;
	
	int finalX, finalY;
	int initialX, initialY;
	finalX = DesiredMove->finX;
	finalY = DesiredMove->finY;
	initialX = DesiredMove->initX;
	initialY = DesiredMove->initY;
	PIECE *TempPiece = NULL;
	
	compX = finalX - initialX;

	//handle en passant.
	if(DesiredMove->Mover->type == 'P' && initialX != finalX && CapturedPiece == NULL) 
	{

		if(update)
		{
			CapturedColor = 1- DesiredMove->Mover->color;
			if(CapturedColor == 0)
				CapturedList = white;
			
			else
				CapturedList = black;
			
			CapturedEntry = CapturedList->First;
			
			if(CapturedColor == 0)
			{
				capX = DesiredMove->finX;
				capY = DesiredMove->finY + 1;
			}
			else
			{
				capX = DesiredMove->finX;
				capY = DesiredMove->finY - 1;
			}

			
			while(esc == 0)
			{
				compX = CapturedEntry->AlivePiece->Xpos;	
				compY = CapturedEntry->AlivePiece->Ypos;
				
				if((compX == capX)&&(compY == capY))
				{
					esc = 1;
					CapturedPiece = DeleteAliveEntry(CapturedEntry);
					DeletePiece(CapturedPiece);
				}	
				
				else
					CapturedEntry=CapturedEntry->Next;
			}
		
		}

		//return void;
		TempPiece = InputBoard->board[initialX][initialY];
		TempPiece->Xpos = finalX;
		TempPiece->Ypos = finalY;
		InputBoard->board[finalX][finalY] = TempPiece;
		if(update)
			InputBoard->board[finalX][finalY]->moveCount++;
		InputBoard->board[initialX][initialY] = NULL;
		InputBoard->board[finalX][initialY] = NULL;
		
		CapturedList = NULL;
		CapturedEntry = NULL;
		
		LogEnpassant();
		return;
		
	}
	
	/*handle castling */

	else if(DesiredMove->Mover->type == 'K' && (compX == 2 || compX == -2))
	{
		if(DesiredMove->Mover->color == 0)
		{
			if(compX > 0)
			{
				InputBoard->board[5][0] = InputBoard->board[7][0];
				InputBoard->board[5][0]->Xpos = 5;
				InputBoard->board[7][0] = NULL;
			}
			else
			{
				InputBoard->board[3][0] = InputBoard->board[0][0];
				InputBoard->board[3][0]->Xpos = 3;
				InputBoard->board[0][0] = NULL;
			}
		}
		
		else
		{
			if(compX > 0)
			{
				InputBoard->board[5][7] = InputBoard->board[7][7];
				InputBoard->board[5][7]->Xpos = 5;
				InputBoard->board[7][7] = NULL;
			}
			else
			{
				InputBoard->board[3][7] = InputBoard->board[0][7];
				InputBoard->board[3][7]->Xpos = 3;
				InputBoard->board[0][7] = NULL;
			}
		
		}
	
	
	}
	
	//not enpassant, not castling
	else if((CapturedPiece)&&(update == 1))
	/*if there is a capture and updates are enabled*/
	{	
		CapturedColor = CapturedPiece->color;
		if(CapturedColor == 0)
			CapturedList = white;
	
		else
			CapturedList = black;
	
		CapturedEntry = CapturedList->First;
		capX = DesiredMove->finX;
		capY = DesiredMove->finY;
		while(esc == 0)
		{
			compX = CapturedEntry->AlivePiece->Xpos;	
			compY = CapturedEntry->AlivePiece->Ypos;
				
			if((compX == capX)&&(compY == capY))
			{
				esc = 1;
				CapturedPiece = DeleteAliveEntry(CapturedEntry);
				DeletePiece(CapturedPiece);
			}	
			else
				CapturedEntry=CapturedEntry->Next;	
		}						
	}
	
	
	/*Handle the movement of the piece*/
	

	
	

	TempPiece = InputBoard->board[initialX][initialY];
	TempPiece->Xpos = finalX;
	TempPiece->Ypos = finalY;
	InputBoard->board[finalX][finalY] = TempPiece;
	if(update)
		InputBoard->board[finalX][finalY]->moveCount++;
	if(update == 0)
	{
		TempPiece->Xpos = initialX;
		TempPiece->Ypos = initialY;
	}
	InputBoard->board[initialX][initialY] = NULL;
	

	/*Clean up*/
/*	CapturedPiece = NULL;*/
	CapturedList = NULL;
	CapturedEntry = NULL;	
}


void MovePieceAI(MOVE *DesiredMove, THEBOARD *InputBoard)
{
	PIECE *CapturedPiece = NULL;
	CapturedPiece = DesiredMove->Capture;
	
	int finalX, finalY;
	int initialX, initialY;
	finalX = DesiredMove->finX;
	finalY = DesiredMove->finY;
	initialX = DesiredMove->initX;
	initialY = DesiredMove->initY;
	PIECE *TempPiece = NULL;
	int compX = finalX - initialX;


	//handle en passant.
	if(DesiredMove->Mover->type == 'P' && initialX != finalX && CapturedPiece == NULL) 
	{

		TempPiece = InputBoard->board[initialX][initialY];
		TempPiece->Xpos = finalX;
		TempPiece->Ypos = finalY;
		InputBoard->board[finalX][finalY] = TempPiece;
		InputBoard->board[initialX][initialY] = NULL;
		InputBoard->board[finalX][initialY] = NULL;
		
		return;
		
	}
	
	/*handle castling */

	else if(DesiredMove->Mover->type == 'K' && (compX == 2 || compX == -2))
	{
		if(DesiredMove->Mover->color == 0)
		{
			if(compX > 0)
			{
				InputBoard->board[5][0] = InputBoard->board[7][0];
				InputBoard->board[5][0]->Xpos = 5;
				InputBoard->board[7][0] = NULL;
			}
			else
			{
				InputBoard->board[3][0] = InputBoard->board[0][0];
				InputBoard->board[3][0]->Xpos = 3;
				InputBoard->board[0][0] = NULL;
			}
		}
		
		else
		{
			if(compX > 0)
			{
				InputBoard->board[5][7] = InputBoard->board[7][7];
				InputBoard->board[5][7]->Xpos = 5;
				InputBoard->board[7][7] = NULL;
			}
			else
			{
				InputBoard->board[3][7] = InputBoard->board[0][7];
				InputBoard->board[3][7]->Xpos = 3;
				InputBoard->board[0][7] = NULL;
			}
		
		}
	
	}
	
	/*Handle the movement of the piece*/
	

	
	

	TempPiece = InputBoard->board[initialX][initialY];
	TempPiece->Xpos = finalX;
	TempPiece->Ypos = finalY;
	InputBoard->board[finalX][finalY] = TempPiece;
	InputBoard->board[initialX][initialY] = NULL;
	
	return;

}




/*function definition of Promotion*/
void Promotion(PIECE *Pawn, THEBOARD *Board, int option, int aicolor)
{
	assert(option >= 0 && option < 4);
	char piece;
	int check = 1;
	
	/*Player v Player, ask what they want to promote to*/
	if(option == 1)
	{
		while(check)
		{
			printf("Select your piece: \n");
			printf("1. Bishop ('B')");
			printf("2. Rook ('R')");
			printf("3. Knight ('H')");
			printf("4. Queen ('Q')");
			printf("Your piece: \n");
			scanf(" %c", &piece);

		
			if(piece == 'B' || piece == 'R' || piece == 'H' || piece == 'Q')
			{
				Pawn->type = piece;
				check = 0;
			
			}
		}
	}
	
	else if(option == 2)
	{
		/*if ai is white and at the end, or if ai is black and at the end, promote to Q*/
		if ((aicolor == 0 && Pawn->Ypos == 7) || (aicolor == 1 && Pawn->Ypos == 0))
			Pawn->type = 'Q';
		
		/*else we are dealing with the player. player can decide promotion*/	
		else
		{
			while(check)
			{
				printf("Select your piece: \n");
				printf("1. Bishop ('B')");
				printf("2. Rook ('R')");
				printf("3. Knight ('H')");
				printf("4. Queen ('Q')");
				printf("Your piece: \n");
				scanf(" %c", &piece);

		
				if(piece == 'B' || piece == 'R' || piece == 'H' || piece == 'Q')
				{
					Pawn->type = piece;
					check = 0;
			
				}
			}
		}	
	
	}
	
	/*else we have ai v ai, and they should choose Queen (most beneficial)*/
	else
		Pawn->type = 'Q';

	
	LogPromotion();
	/*
	char option;
	int check = 1;
	
	while(check)
	{
		printf("Select your piece: \n");
		printf("1. Bishop ('B')");
		printf("2. Rook ('R')");
		printf("3. Knight ('H')");
		printf("4. Queen ('Q')");
		printf("Your option: \n");
		scanf(" %c", &option);

		
		if(option == 'B' || option == 'R' || option == 'H' || option == 'Q')
		{
			Board.board[Pawn->Xpos][Pawn->Ypos]->type = option;
			check = 0;
			
		}
	}
	
	return Pawn;
	
	*/
}

void Capture(PIECE *capturedPiece, THEBOARD Board){
	assert (capturedPiece);
	PIECE *temp;
	temp = capturedPiece;
	/*delete the piece that has been captured*/
	DeletePiece(capturedPiece);
	/*make the space empty on the board*/
	Board.board[temp->Xpos][temp->Ypos] = NULL;
	
}
