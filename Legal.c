/*
Change Log:
1/25 7:00 PM	-Raza 	- add the PawnLegalMoveListGen function and updated for black piece
1/25 7:30 PM	-Tun	- Update the full PawnLegalMoveListGen function
1/25 8:25 PM	-Tun	- Update the full KingLegalMoveListGen function
1/27 9:30 PM	-Tun	- Update the full RookLegalMoveListGen function
1/27 10:30 PM	-Tun	- Update the full BishopLegalMoveListGen function
1/27 10:45 PM	-Tun	- Update the full QueenLegalMoveListGen fnction
1/28 12:37 AM	-Tun	- Update the full KnightLegalMoveListGen fnction
1/28 2:00 PM	-Reza 	- Updated RookMoves to check for Bounds in if statement for seg faults.
						- Note: still need to implement extra checks for bishop, queen. i will do this tonight in meeting
1/28 10PM		-Reza	- Updated all function definitions for new Board struct
						- Updated all potential segfaults
						- Copy and PAste from Bishop and Rook into the Queen function
						- added code for white castling
1/28 10:56 PM	-Tun	- Updated the KingLegalMoveListGen function
				- move the castling code blocks from Queen to King function
				- Added code for black castling
1/28 11PM		- Reza	- added en passant under pawn.				
1/29  3AM		- Bianca		- Updated due to comment syntax error, GENERATES ERROR IF COMMENTED AFTER A LINE OF CODE
1/29 10AM		- Reza 	- debug and adding new fucntion compare move to list
1/30 10AM		- Tun	- Fix some of the syntax error due to the comments
1/30 10:16AM		- Tun	- Fix some compilling errors
1/31 4:00 PM	-Tun	- Updated the color changed: Black = 1 and White = 0 now
1/31 6:52 PM	-Tun	- Added extra check for Queen, Bishop and Rook. Make sure that the final position is not NULL before adding to the list.
2/2  9:30 PM	-Tun	- changed ++ to + 1 and -- to - 1 (Doesn't change inside for loop)
2/3  9:45 PM	-Tun	- Added extra if statements (inside if and while statements) for checking to make sure nothing is out of bound
*/
#include <stdio.h>

#include "Legal.h"
#include "move.h"
#include "chessLayout.h"



//cP is currentPiece



//generate legal move list for Pawn both for white and black
MLIST* PawnLegalMoveListGen(PIECE *cP, THEBOARD Board) 
{

	MLIST* possibleMovesList = CreateMoveList();
	MOVE *newMove = NULL;
	
	//black pawn only move down the board
	if (cP->color == 1) 
	{
		//check space below: Ypos is greater than or equal 1 to check out of bounce & the space is NULL
		if( cP->Ypos > 0 )
		{
			if( Board.board[cP->Xpos][cP->Ypos - 1] == NULL)
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos, cP->Ypos - 1, Board);
				AppendMoveList(possibleMovesList, newMove);
			
				//check if moved is zero and position at [x][6]. Two space down is free.
				if( cP->Ypos == 6 )
				{
					if( cP->moveCount == 0 && Board.board[cP->Xpos][cP->Ypos - 2] == NULL )
					{
						newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos, cP->Ypos - 2, Board);
						AppendMoveList(possibleMovesList, newMove);
					}
				}
			}
		}
		
		//check capture moves
		//check down, left [x - 1,y - 1] (x > 0 and y > 0) and there is white color piece
		if ( cP->Xpos > 0 && cP->Ypos > 0 )
		{
			if ( Board.board[cP->Xpos - 1][cP->Ypos - 1] != NULL && Board.board[cP->Xpos - 1][cP->Ypos - 1]->color == 0)
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - 1, cP->Ypos - 1, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}
		
		//check down, right [Xpos + 1, yPos - 1] (x < 7, y > 0) and there is white color piece
		if( cP->Xpos < 7 && cP->Ypos > 0 )
		{
			if ( Board.board[cP->Xpos + 1][cP->Ypos - 1] != NULL && Board.board[cP->Xpos + 1][cP->Ypos - 1]->color == 0)
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + 1, cP->Ypos - 1, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}
			
			
		//en passant black pawn
		
		//check right, then if good move right, down
		if( cP->Ypos == 3 && cP->Xpos < 7 )
		{
			if ( Board.board[cP->Xpos + 1][cP->Ypos])
			{
				if ( Board.board[cP->Xpos + 1][cP->Ypos]->type == 'P' && Board.board[cP->Xpos + 1][cP->Ypos]->color != cP->color && Board.board[cP->Xpos + 1][cP->Ypos]->moveCount == 1)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + 1, cP->Ypos - 1, Board);
					AppendMoveList(possibleMovesList, newMove);
				}
			}
		}
		//check left, if good move left, down
		if( cP->Ypos == 3 && cP->Xpos > 0 )
		{
			if ( Board.board[cP->Xpos - 1][cP->Ypos])
			{
				if ( Board.board[cP->Xpos - 1][cP->Ypos]->type == 'P' && Board.board[cP->Xpos - 1][cP->Ypos]->color != cP->color && Board.board[cP->Xpos - 1][cP->Ypos]->moveCount == 1)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - 1, cP->Ypos - 1, Board);
					AppendMoveList(possibleMovesList, newMove);
				}
			}
		}
		
	}
	
	//white pawn only move up the board
	else	
	{	
		//check space up: Ypos is less than or equal 6 to check out of bounce & the space is NULL
		if( cP->Ypos < 7 )
		{
			if( Board.board[cP->Xpos][cP->Ypos + 1] == NULL)
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos, cP->Ypos + 1, Board);
				AppendMoveList(possibleMovesList, newMove);
				//check if moved is zero and position at [x][1]. Two space up is free
				if (cP->Ypos == 1 && cP->moveCount == 0 && Board.board[cP->Xpos][cP->Ypos + 2] == NULL)
					{
						newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos, cP->Ypos + 2, Board);
						AppendMoveList(possibleMovesList, newMove);
					}
			}
		}
		
		//check capture moves
		//check up, left [x - 1,y + 1] (x > 0 and y < 7) & there is black color piece
		if( cP->Xpos > 0 && cP->Ypos < 7 ){
			if ( Board.board[cP->Xpos - 1][cP->Ypos + 1] != NULL && Board.board[cP->Xpos - 1][cP->Ypos + 1]->color == 1)
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - 1, cP->Ypos + 1, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}
		
		//check up, right [Xpos + 1, yPos + 1] (x < 7, y < 7) & There is black color piece
		if( cP->Xpos < 7 && cP->Ypos < 7 )
		{
			if ( Board.board[cP->Xpos + 1][cP->Ypos + 1] != NULL && Board.board[cP->Xpos + 1][cP->Ypos + 1]->color == 1)
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + 1, cP->Ypos + 1, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}
		

		//en passant, white pawn (moves up)
		//check right(x + 1, y), if good then move right, up (x + 1, y + 1)
		if( cP->Ypos == 4 && cP->Xpos < 7 )
		{
			if(Board.board[cP->Xpos + 1][cP->Ypos] != NULL)
			{
				if ( Board.board[cP->Xpos + 1][cP->Ypos]->type == 'P' && Board.board[cP->Xpos + 1][cP->Ypos]->color != cP->color && Board.board[cP->Xpos + 1][cP->Ypos]->moveCount == 1)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + 1, cP->Ypos + 1, Board);
					AppendMoveList(possibleMovesList, newMove);
				}
			}	
		}
	
		//check left, if good move left, up
		if(cP->Ypos == 4 && cP->Xpos > 0 )
		{
			if (Board.board[cP->Xpos - 1][cP->Ypos] != NULL)
			{
				if ( Board.board[cP->Xpos - 1][cP->Ypos]->type == 'P' && Board.board[cP->Xpos - 1][cP->Ypos]->color != cP->color && Board.board[cP->Xpos - 1][cP->Ypos]->moveCount == 1)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - 1, cP->Ypos + 1, Board);
					AppendMoveList(possibleMovesList, newMove);
				}		
			}
		}
		
	}
	return possibleMovesList;
}


//generate legal move list for King both for white and black
//It will check NULL space or enemy piece for each space 8 direcions
MLIST* KingLegalMoveListGen(PIECE *cP, THEBOARD Board) 
{

	MLIST* possibleMovesList = CreateMoveList();
	MOVE *newMove = NULL;


	//SPECIAL CASE: CASTLING
		//CASE1 WHITE KING
	
	//check color to be white, and either rook is in its original spot (or both)
	if (cP->color == 0 && cP->moveCount == 0)
	{
		//CASE 1a CASTLE RIGHT, check that down right square is rook, rook ==0, and F0 and G0 are not occupied
		if(Board.board[7][0] != NULL)
		{
			if(Board.board[7][0]->type == 'R' && Board.board[7][0]->moveCount == 0 && Board.board[6][0] == NULL && Board.board[5][0] == NULL)
			{	
				//note that we do not add the move of the rook. Locomotion must handle the case where a king moves over two spots then move the rook accordingly
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + 2, cP->Ypos, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}
		

		//CASE 1b CASTLE LEFT. check down left square is rook, rook movecount ==0, and 3 spot between is NULL
		if(Board.board[0][0] != NULL)
		{
			if(Board.board[0][0]->type == 'R' && Board.board[0][0]->moveCount == 0 && Board.board[1][0] == NULL && Board.board[2][0] == NULL && Board.board[3][0] == NULL)
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - 2, cP->Ypos, Board);
				AppendMoveList(possibleMovesList, newMove);
		
			}
		}
	}

	//Speical Case: CASTLING
	//SPECIAL CASE2: BLACK KING
	//check color to be black, and either rook is in its original spot (or both)
	if (cP->color == 1 && cP->moveCount == 0)
	{
		//CASE 1a CASTLE RIGHT, check that down right square is rook, rook ==0, and F8 and G8 are not occupied
		if(Board.board[7][7] != NULL)
		{
			if(Board.board[7][7]->type == 'R' && Board.board[7][7]->moveCount == 0 && Board.board[6][7] == NULL && Board.board[5][7] == NULL)
			{
				//note that we do not add the move of the rook. Locomotion must handle the case where a king moves over two spots then move the rook accordingly
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + 2, cP->Ypos, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}
		
		//CASE 1b CASTLE LEFT. check down left square is rook, rook movecount == 0, and 3 spot between is NULL
		if(Board.board[0][7] != NULL)
		{
			if(Board.board[0][7]->type == 'R' && Board.board[0][7]->moveCount == 0 && Board.board[1][7] == NULL && Board.board[2][7] == NULL && Board.board[3][7] == NULL)
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - 2, cP->Ypos, Board);
				AppendMoveList(possibleMovesList, newMove);
			}		
		}
	}


//end special case : castling for both black and white king


		//check space below: Ypos > 0 to check out of bounce & (the space is NULL || occupied by different color)
		if( cP->Ypos > 0 )
		{
			if ( ( Board.board[cP->Xpos][cP->Ypos - 1] == NULL || cP->color != Board.board[cP->Xpos][cP->Ypos - 1]->color ) )
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos, cP->Ypos - 1, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}
		
		//check space up: Ypos < 7 to check out of bounce & (the space is NULL || occupied by different color)
		if( cP->Ypos < 7 )
		{
			if ( ( Board.board[cP->Xpos][cP->Ypos + 1] == NULL || cP->color != Board.board[cP->Xpos][cP->Ypos + 1]->color ) )
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos, cP->Ypos + 1, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}

		//check space right: Xpos < 7 to check out of bounce & (the space is NULL || occupied by different color)
		if(cP->Xpos < 7)
		{
			if ( ( Board.board[cP->Xpos + 1][cP->Ypos] == NULL || cP->color != Board.board[cP->Xpos + 1][cP->Ypos]->color ) )
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + 1, cP->Ypos, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}

		//check space left: Xpos > 0 to check out of bounce & (the space is NULL || occupied by different color)
		if(cP->Xpos > 0 )
		{
			if ( ( Board.board[cP->Xpos - 1][cP->Ypos] == NULL || cP->color != Board.board[cP->Xpos - 1][cP->Ypos]->color ) )
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - 1, cP->Ypos, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}

		//check space right up: Xpos < 7 && Ypos < 7 to check out of bounce & (the space is NULL || occupied by different color)
		if(cP->Xpos < 7 && cP->Ypos < 7)
		{
			if ( ( Board.board[cP->Xpos + 1][cP->Ypos + 1] == NULL || cP->color != Board.board[cP->Xpos + 1][cP->Ypos + 1]->color ) )
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + 1, cP->Ypos + 1, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}

		//check space left up: Xpos > 0 && Ypos < 7 to check out of bounce & (the space is NULL || occupied by different color)
		if(cP->Xpos > 0 && cP->Ypos < 7)
		{
			if (( Board.board[cP->Xpos - 1][cP->Ypos + 1] == NULL || cP->color != Board.board[cP->Xpos - 1][cP->Ypos + 1]->color ) )
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - 1, cP->Ypos + 1, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}

		//check space right down: Xpos < 7 && Ypos > 0 to check out of bounce & (the space is NULL || occupied by different color)
		if(cP->Xpos < 7 && cP->Ypos > 0)
		{
			if ( ( Board.board[cP->Xpos + 1][cP->Ypos - 1] == NULL || cP->color != Board.board[cP->Xpos + 1][cP->Ypos - 1]->color ) )
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + 1, cP->Ypos - 1, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}

		//check space left down: Xpos > 0 && Ypos > 0 to check out of bounce & (the space is NULL || occupied by different color)
		if(cP->Xpos > 0 && cP->Ypos > 0)
		{
			if ( ( Board.board[cP->Xpos - 1][cP->Ypos - 1] == NULL || cP->color != Board.board[cP->Xpos - 1][cP->Ypos - 1]->color ) )
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - 1, cP->Ypos - 1, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}
		
		return possibleMovesList;
}


//generate legal move list for Rook both for white and black
//It will check NULL space or enemy piece for each space 4 horizontal and vertical direcions
MLIST* RookLegalMoveListGen(PIECE *cP, THEBOARD Board)
{
	MLIST* possibleMovesList = CreateMoveList();
	MOVE *newMove = NULL;
	int x = 1, y = 1;
		
		y = 1; 
		//reset y value for another direction because we are moving in y axis
		//check space below: until the loop reach occupied space 
		//current Ypos > 0 to check out of bounce. It has at least one space left to move down.
		if (cP->Ypos > 0 ) 
		{
			//check the space until it reach not NULL space && BOUNDS
			while ( (cP->Ypos - y) >= 0 && Board.board[cP->Xpos][cP->Ypos - y] == NULL) 
			{
				//move down 1 space each time
				if((cP->Ypos - y) >= 0)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos, cP->Ypos - y, Board); 
					AppendMoveList(possibleMovesList, newMove);
				}
				y++;
			}
			
			//check the last not NULL space. If the space is occupied the enemy, it can be capture.
			//current color is not the same with the occupied color
			//1/28 -Reza added extra  && in if statement to check for bounds. 
			//1/31 -Tun added extra check to make sure that the space is not NULL.
			if((cP->Ypos - y) >= 0 )
			{
				if ( Board.board[cP->Xpos][cP->Ypos - y] != NULL && cP->color != Board.board[cP->Xpos][cP->Ypos - y]->color)
				{
							newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos, cP->Ypos - y, Board);
							AppendMoveList(possibleMovesList, newMove);
				}
			}
			
		}


		y = 1; 
		//reset y value for another direction because we are moving in y axis
		//check space up: until the loop reach occupied space 
		//current Ypos < 7 to check out of bounce. It has at least one space left to move up.
		if (cP->Ypos < 7 ) 
		{
			//check the space until it reach not NULL space.
			while ( (cP->Ypos + y) <= 7 && Board.board[cP->Xpos][cP->Ypos + y] == NULL) 
			{
				//move up 1 space each time
				if((cP->Ypos + y) <= 7)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos, cP->Ypos + y, Board); 
					AppendMoveList(possibleMovesList, newMove);
				}
				y++;
			}
			
			//check the last not NULL space. If the space is occupied the enemy, it can be capture.
			//current color is not the same with the occupied color
			if((cP->Ypos + y) <= 7)
			{
				if (  Board.board[cP->Xpos][cP->Ypos + y] != NULL && cP->color != Board.board[cP->Xpos][cP->Ypos + y]->color )
				{
							newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos, cP->Ypos + y, Board);
							AppendMoveList(possibleMovesList, newMove);
				}
			}
			
		}
	

		x = 1; 
		//reset x value for another direction because we are moving in x axis
		//check space right: until the loop reach occupied space 
		//current Xpos < 7 to check out of bounce. It has at least one space left to move up.
		if (cP->Xpos < 7 ) 
		{
			//check the space until it reach not NULL space.
			while ( (cP->Xpos + x) <= 7 && Board.board[cP->Xpos + x][cP->Ypos] == NULL )
			{
				 //move up 1 space each time
				if((cP->Xpos + x) <= 7)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + x, cP->Ypos, Board);
					AppendMoveList(possibleMovesList, newMove);
				}
				x++;
			}
			
			//check the last not NULL space. If the space is occupied the enemy, it can be capture.
			//current color is not the same with the occupied color
			if((cP->Xpos + x) <= 7)
			{
				if ( Board.board[cP->Xpos + x][cP->Ypos] != NULL && cP->color != Board.board[cP->Xpos + x][cP->Ypos]->color )
				{
							newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + x, cP->Ypos, Board);
							AppendMoveList(possibleMovesList, newMove);
				}
			}
		}


		x = 1; 
		//reset x value for another direction because we are moving in x axis
		//check space left: until the loop reach occupied space 
		//current Xpos > 7 to check out of bounce. It has at least one space left to move up.
		if (cP->Xpos > 0 ) 
		{
			 //check the space until it reach not NULL space.
			while ( (cP->Xpos - x) >= 0 && Board.board[cP->Xpos - x][cP->Ypos] == NULL )
			{
				//move up 1 space each time
				if((cP->Xpos - x) >= 0)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - x, cP->Ypos, Board); 
					AppendMoveList(possibleMovesList, newMove);
				}
				x++;
			}
			
			//check the last not NULL space. If the space is occupied the enemy, it can be capture.
			//current color is not the same with the occupied color
			if((cP->Xpos - x) >= 0 )
			{
				if ( Board.board[cP->Xpos - x][cP->Ypos] != NULL && cP->color != Board.board[cP->Xpos - x][cP->Ypos]->color )
				{
						newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - x, cP->Ypos, Board);
						AppendMoveList(possibleMovesList, newMove);
				}
			}
		}
		
	return possibleMovesList;
}




//generate legal move list for bishop both for white and black
//It will check NULL space or enemy piece for each space 4 diagonal direcions
MLIST* BishopLegalMoveListGen(PIECE *cP, THEBOARD Board) 
{
	MLIST* possibleMovesList = CreateMoveList();
	MOVE *newMove = NULL;
	int x, y;
		
		x = 1; y = 1; 
		//reset x and y value for another direction
		//check space up right (x++ and y++): until the loop reach occupied space 
		//current Xpos < 7 && Ypos < 7 to check out of bounce. It has at least one space left to move up right.
		if (cP->Xpos < 7 && cP->Ypos < 7 ) 
		{
			//check the space until it reach not NULL space.
			while ( (cP->Xpos + x) <= 7 && (cP->Ypos + y) <= 7 && Board.board[cP->Xpos + x][cP->Ypos + y] == NULL) 
			{
				//move up right 1 space each time
				if((cP->Xpos + x) <= 7 && (cP->Ypos + y) <= 7)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + x, cP->Ypos + y, Board); 
					AppendMoveList(possibleMovesList, newMove);
				}
				x++; 
				y++;
			}
			
			//check the last not NULL space. If the space is occupied the enemy, it can be capture.
			//current color is not the same with the occupied color
			if((cP->Xpos + x) <= 7 && (cP->Ypos + y) <= 7 )
			{
				if ( Board.board[cP->Xpos + x][cP->Ypos + y] != NULL && cP->color != Board.board[cP->Xpos + x][cP->Ypos + y]->color)
				{
						newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + x, cP->Ypos + y, Board);
						AppendMoveList(possibleMovesList, newMove);
				}
			}
		}


		x = 1; y = 1; 
		//reset x and y value for another direction
		//check space up left (x - 1 and y++): until the loop reach occupied space 
		//current Xpos > 0 && Ypos < 7 to check out of bounce. It has at least one space left to move up left.
		if (cP->Xpos > 0 && cP->Ypos < 7 ) 
		{
			//check the space until it reach not NULL space.
			while ( (cP->Xpos - x) >= 0 && (cP->Ypos + y) <= 7 && Board.board[cP->Xpos - x][cP->Ypos + y] == NULL ) 
			{
				//move up right 1 space each time
				if((cP->Xpos - x) >= 0 && (cP->Ypos + y) <= 7)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - x, cP->Ypos + y, Board); 
					AppendMoveList(possibleMovesList, newMove);
				}
				x++; 
				y++;
			}
			
			//check the last not NULL space. If the space is occupied the enemy, it can be capture.
			//current color is not the same with the occupied color
			if((cP->Xpos - x) >= 0 && (cP->Ypos + y) <= 7)
			{
				if ( Board.board[cP->Xpos - x][cP->Ypos + y] != NULL && cP->color != Board.board[cP->Xpos - x][cP->Ypos + y]->color )
				{
						newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - x, cP->Ypos + y, Board);
						AppendMoveList(possibleMovesList, newMove);
				}
			}
		}


		x = 1; y = 1; 
		//reset x and y value for another direction
		//check space down left (x - 1 and y - 1): until the loop reach occupied space 
		//current Xpos > 0 && Ypos > 0 to check out of bounce. It has at least one space left to move down left.
		if (cP->Xpos > 0 && cP->Ypos > 0 )
		{
			//check the space until it reach not NULL space.
			while ( (cP->Xpos - x) >= 0 && (cP->Ypos - y) >= 0 && Board.board[cP->Xpos - x][cP->Ypos - y] == NULL ) 
			{
				//move up right 1 space each time
				if((cP->Xpos - x) >= 0 && (cP->Ypos - y) >= 0 )
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - x, cP->Ypos - y, Board); 
					AppendMoveList(possibleMovesList, newMove);
				}
				x++; 
				y++;
			}
			
			//check the last not NULL space. If the space is occupied the enemy, it can be capture.
			//current color is not the same with the occupied color
			if( (cP->Xpos - x) >= 0 && (cP->Ypos - y) >= 0)
			{
				if ( Board.board[cP->Xpos - x][cP->Ypos - y] != NULL && cP->color != Board.board[cP->Xpos - x][cP->Ypos - y]->color)
				{
						newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - x, cP->Ypos - y, Board);
						AppendMoveList(possibleMovesList, newMove);
				}
			}
		}


		x = 1; y = 1; 
		//reset x and y value for another direction
		//check space down right (x++ and y - 1): until the loop reach occupied space 
		//current Xpos < 7 && Ypos > 0 to check out of bounce. It has at least one space left to move down right.
		if (cP->Xpos < 7 && cP->Ypos > 0 ) 
		{
			//check the space until it reach not NULL space.
			while ( (cP->Xpos + x) <= 7 && (cP->Ypos - y) >= 0 && Board.board[cP->Xpos + x][cP->Ypos - y] == NULL ) 
			{
				//move up right 1 space each time
				if((cP->Xpos + x) <= 7 && (cP->Ypos - y) >= 0)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + x, cP->Ypos - y, Board); 
					AppendMoveList(possibleMovesList, newMove);
				}
				x++; 
				y++;
			}
			
			//check the last not NULL space. If the space is occupied the enemy, it can be capture.
			//current color is not the same with the occupied color
			if((cP->Xpos + x) <= 7 && (cP->Ypos - y) >= 0 )
			{
				if ( Board.board[cP->Xpos + x][cP->Ypos - y] != NULL && cP->color != Board.board[cP->Xpos + x][cP->Ypos - y]->color )
				{
						newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + x, cP->Ypos - y, Board);
						AppendMoveList(possibleMovesList, newMove);
				}
			}
		}
		
		return possibleMovesList;

}


//generate legal move list for queen both for white and black
//It will check NULL space or enemy piece for each space 4 diagonal 2 vertical 2 horizontal positions
//It will just use rook and bishop functions
MLIST* QueenLegalMoveListGen(PIECE *cP, THEBOARD Board)
{

	MLIST* possibleMovesList = CreateMoveList();
	MOVE *newMove = NULL;
	int x, y;	
	
	
	//FIRST SET OF MOVES: DIAGONAL (CopyPasta from Bishop)
		
		x = 1; y = 1; 
		//reset x and y value for another direction
		//check space up right (x++ and y++): until the loop reach occupied space 
		//current Xpos < 7 && Ypos < 7 to check out of bounce. It has at least one space left to move up right.
		if (cP->Xpos < 7 && cP->Ypos < 7 ) 
		{
			//check the space until it reach not NULL space.
			while ( (cP->Xpos + x) <= 7 && (cP->Ypos + y) <= 7 && Board.board[cP->Xpos + x][cP->Ypos + y] == NULL ) 
			{
				//move up right 1 space each time
				if((cP->Xpos + x) <= 7 && (cP->Ypos + y) <= 7)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + x, cP->Ypos + y, Board); 
					AppendMoveList(possibleMovesList, newMove);
				}
				x++; 
				y++;
			}
			
			//check the last not NULL space. If the space is occupied the enemy, it can be capture.
			//current color is not the same with the occupied color
			if((cP->Xpos + x) <= 7 && (cP->Ypos + y) <= 7)
			{
				if ( Board.board[cP->Xpos + x][cP->Ypos + y] != NULL && cP->color != Board.board[cP->Xpos + x][cP->Ypos + y]->color )
				{
						newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + x, cP->Ypos + y, Board);
						AppendMoveList(possibleMovesList, newMove);
				}
			}
		}


		x = 1; y = 1; 
		//reset x and y value for another direction
		//check space up left (x - 1 and y++): until the loop reach occupied space 
		//current Xpos > 0 && Ypos < 7 to check out of bounce. It has at least one space left to move up left.
		if (cP->Xpos > 0 && cP->Ypos < 7 ) 
		{
			//check the space until it reach not NULL space.
			while ( (cP->Xpos - x) >= 0 && (cP->Ypos + y) <= 7 && Board.board[cP->Xpos - x][cP->Ypos + y] == NULL )
			{
				//move up right 1 space each time
				if((cP->Xpos - x) >= 0 && (cP->Ypos + y) <= 7)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - x, cP->Ypos + y, Board); 
					AppendMoveList(possibleMovesList, newMove);
				}
				x++; 
				y++;
			}
			
			//check the last not NULL space. If the space is occupied the enemy, it can be capture.
			//current color is not the same with the occupied color
			if((cP->Xpos - x) >= 0 && (cP->Ypos + y) <= 7 )
			{
				if ( Board.board[cP->Xpos - x][cP->Ypos + y] != NULL && cP->color != Board.board[cP->Xpos - x][cP->Ypos + y]->color )
				{
						newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - x, cP->Ypos + y, Board);
						AppendMoveList(possibleMovesList, newMove);
				}
			}
		}


		x = 1; y = 1; 
		//reset x and y value for another direction
		//check space down left (x - 1 and y - 1): until the loop reach occupied space 
		//current Xpos > 0 && Ypos > 0 to check out of bounce. It has at least one space left to move down left.
		if (cP->Xpos > 0 && cP->Ypos > 0 )
		{
			//check the space until it reach not NULL space.
			while ( (cP->Xpos - x) >= 0 && (cP->Ypos - y) >= 0 && Board.board[cP->Xpos - x][cP->Ypos - y] == NULL ) 
			{
				//move up right 1 space each time
				if((cP->Xpos - x) >= 0 && (cP->Ypos - y) >= 0)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - x, cP->Ypos - y, Board); 
					AppendMoveList(possibleMovesList, newMove);
				}
				x++; 
				y++;
			}
			
			//check the last not NULL space. If the space is occupied the enemy, it can be capture.
			//current color is not the same with the occupied color
			if( (cP->Xpos - x) >= 0 && (cP->Ypos - y) >= 0 )
			{
				if ( Board.board[cP->Xpos - x][cP->Ypos - y] != NULL && cP->color != Board.board[cP->Xpos - x][cP->Ypos - y]->color )
				{
						newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - x, cP->Ypos - y, Board);
						AppendMoveList(possibleMovesList, newMove);
				}
			}
		}


		x = 1; y = 1; 
		//reset x and y value for another direction
		//check space down right (x++ and y - 1): until the loop reach occupied space 
		//current Xpos < 7 && Ypos > 0 to check out of bounce. It has at least one space left to move down right.
		if (cP->Xpos < 7 && cP->Ypos > 0 ) 
		{
			//check the space until it reach not NULL space.
			while ( (cP->Xpos + x) <= 7 && (cP->Ypos - y) >= 0 && Board.board[cP->Xpos + x][cP->Ypos - y] == NULL  ) 
			{
				//move up right 1 space each time
				if((cP->Xpos + x) <= 7 && (cP->Ypos - y) >= 0 )
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + x, cP->Ypos - y, Board);
					AppendMoveList(possibleMovesList, newMove);
				}
				x++; 
				y++;
			}
			
			//check the last not NULL space. If the space is occupied the enemy, it can be capture.
			//current color is not the same with the occupied color
			if((cP->Xpos + x) <= 7 && (cP->Ypos - y) >= 0 )
			{
				if ( Board.board[cP->Xpos + x][cP->Ypos - y] != NULL  && cP->color != Board.board[cP->Xpos + x][cP->Ypos - y]->color)
				{
						newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + x, cP->Ypos - y, Board);
						AppendMoveList(possibleMovesList, newMove);
				}
			}
		}
		
	//SECOND SET OF MOVED: UP/DOWN (CopyPasta from ROOK)
		
		y = 1; 
		//reset y value for another direction because we are moving in y axis
		//check space below: until the loop reach occupied space 
		//current Ypos > 0 to check out of bounce. It has at least one space left to move down.
		if (cP->Ypos > 0 ) 
		{
			//check the space until it reach not NULL space && BOUNDS
			while ( (cP->Ypos - y) >= 0 && Board.board[cP->Xpos][cP->Ypos - y] == NULL ) 
			{
				//move down 1 space each time
				if((cP->Ypos - y) >= 0)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos, cP->Ypos - y, Board); 
					AppendMoveList(possibleMovesList, newMove);
				}
				y++;
			}
			
			//check the last not NULL space. If the space is occupied the enemy, it can be capture.
			//current color is not the same with the occupied color
			//1/28 -Reza added extra  && in if statement to check for bounds. 
			if((cP->Ypos - y) >= 0 )
			{
				if ( Board.board[cP->Xpos][cP->Ypos - y] != NULL && cP->color != Board.board[cP->Xpos][cP->Ypos - y]->color)
				{
							newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos, cP->Ypos - y, Board);
							AppendMoveList(possibleMovesList, newMove);
				}
			}
		}


		y = 1; 
		//reset y value for another direction because we are moving in y axis
		//check space up: until the loop reach occupied space 
		//current Ypos < 7 to check out of bounce. It has at least one space left to move up.
		if (cP->Ypos < 7 ) 
		{
			//check the space until it reach not NULL space.
			while ( (cP->Ypos + y) <= 7 && Board.board[cP->Xpos][cP->Ypos + y] == NULL ) 
			{
				//move up 1 space each time
				if((cP->Ypos + y) <= 7)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos, cP->Ypos + y, Board); 
					AppendMoveList(possibleMovesList, newMove);
				}
				y++;
			}
			
			//check the last not NULL space. If the space is occupied the enemy, it can be capture.
			//current color is not the same with the occupied color
			if((cP->Ypos + y) <= 7)
			{
				if ( Board.board[cP->Xpos][cP->Ypos + y] != NULL && cP->color != Board.board[cP->Xpos][cP->Ypos + y]->color)
				{
							newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos, cP->Ypos + y, Board);
							AppendMoveList(possibleMovesList, newMove);
				}
			}
			
		}
	

		x = 1; 
		//reset x value for another direction because we are moving in x axis
		//check space right: until the loop reach occupied space 
		//current Xpos < 7 to check out of bounce. It has at least one space left to move up.
		if (cP->Xpos < 7 ) 
		{
			//check the space until it reach not NULL space.
			while ( (cP->Xpos + x) <= 7 && Board.board[cP->Xpos + x][cP->Ypos] == NULL) 
			{
				//move up 1 space each time
				if((cP->Xpos + x) <= 7)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + x, cP->Ypos, Board); 
					AppendMoveList(possibleMovesList, newMove);
				}
				x++;
			}
			
			//check the last not NULL space. If the space is occupied the enemy, it can be capture.
			//current color is not the same with the occupied color
			if((cP->Xpos + x) <= 7)
			{
				if ( Board.board[cP->Xpos + x][cP->Ypos] != NULL && cP->color != Board.board[cP->Xpos + x][cP->Ypos]->color)
				{
							newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + x, cP->Ypos, Board);
							AppendMoveList(possibleMovesList, newMove);
				}
			}
			
		}


		x = 1; 
		//reset x value for another direction because we are moving in x axis
		//check space left: until the loop reach occupied space 
		//current Xpos > 7 to check out of bounce. It has at least one space left to move up.
		if (cP->Xpos > 0 ) 
		{
			//check the space until it reach not NULL space.
			while ( (cP->Xpos - x) >= 0 && Board.board[cP->Xpos - x][cP->Ypos] == NULL) 
			{
				//move up 1 space each time
				if((cP->Xpos - x) >= 0)
				{
					newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - x, cP->Ypos, Board); 
					AppendMoveList(possibleMovesList, newMove);
				}
				x++;
			}
			
			//check the last not NULL space. If the space is occupied the enemy, it can be capture.
			//current color is not the same with the occupied color
			if((cP->Xpos - x) >= 0 )
			{
				if ( Board.board[cP->Xpos - x][cP->Ypos] != NULL && cP->color != Board.board[cP->Xpos - x][cP->Ypos]->color)
				{
						newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - x, cP->Ypos, Board);
						AppendMoveList(possibleMovesList, newMove);
				}
			}
		}
		
		return possibleMovesList;
		
}


//generate legal move list for Knight both for white and black
//It will check NULL space or enemy piece for each space 8 direcions
MLIST* KnightLegalMoveListGen(PIECE *cP, THEBOARD Board)
{

	MLIST* possibleMovesList = CreateMoveList();
	MOVE *newMove = NULL;

		//check space two up one right: x+1 and y+2 : Xpos <= 6 && Ypos <= 5 to check out of bounce 
		//&& (the space is NULL || occupied by different color)
		if(cP->Xpos <= 6 && cP->Ypos <= 5)
		{
			if ( (Board.board[cP->Xpos + 1][cP->Ypos + 2] == NULL || cP->color != Board.board[cP->Xpos + 1][cP->Ypos + 2]->color ) )
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + 1, cP->Ypos + 2, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}


		//check space two up one left: x-1 and y+2 : Xpos >= 1 && Ypos <= 5 to check out of bounce 
		//&& (the space is NULL || occupied by different color)
		if(cP->Xpos >= 1 && cP->Ypos <= 5)
		{
			if ( ( Board.board[cP->Xpos - 1][cP->Ypos + 2] == NULL || cP->color != Board.board[cP->Xpos - 1][cP->Ypos + 2]->color ) )
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - 1, cP->Ypos + 2, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}


		//check space one up two right: x+2 and y+1 : Xpos <= 5 && Ypos <= 6 to check out of bounce 
		//&& (the space is NULL || occupied by different color)
		if(cP->Xpos <= 5 && cP->Ypos <= 6)
		{
			if (( Board.board[cP->Xpos + 2][cP->Ypos + 1] == NULL || cP->color != Board.board[cP->Xpos + 2][cP->Ypos + 1]->color ) )
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + 2, cP->Ypos + 1, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}


		//check space one up two left: x-2 and y+1 : Xpos >= 2 && Ypos <= 6 to check out of bounce 
		//&& (the space is NULL || occupied by different color)
		if(cP->Xpos >= 2 && cP->Ypos <= 6)
		{
			if (( Board.board[cP->Xpos - 2][cP->Ypos + 1] == NULL || cP->color != Board.board[cP->Xpos - 2][cP->Ypos + 1]->color ) )
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - 2, cP->Ypos + 1, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}


		//check space two down one right: x+1 and y-2 : Xpos <= 6 && Ypos >= 2 to check out of bounce 
		//&& (the space is NULL || occupied by different color)
		if(cP->Xpos <= 6 && cP->Ypos >= 2)
		{
			if ( ( Board.board[cP->Xpos + 1][cP->Ypos - 2] == NULL || cP->color != Board.board[cP->Xpos + 1][cP->Ypos - 2]->color ) )
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + 1, cP->Ypos - 2, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}


		//check space two down one left: x-1 and y-2 : Xpos >= 1 && Ypos >= 2 to check out of bounce 
		//&& (the space is NULL || occupied by different color)
		if(cP->Xpos >= 1 && cP->Ypos >= 2)
		{
			if (( Board.board[cP->Xpos - 1][cP->Ypos - 2] == NULL || cP->color != Board.board[cP->Xpos - 1][cP->Ypos - 2]->color ) )
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - 1, cP->Ypos - 2, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}


		//check space one down two right: x+2 and y-1 : Xpos <= 5 && Ypos >= 1 to check out of bounce 
		//&& (the space is NULL || occupied by different color)
		if(cP->Xpos <= 5 && cP->Ypos >= 1)
		{
			if ( ( Board.board[cP->Xpos + 2][cP->Ypos - 1] == NULL || cP->color != Board.board[cP->Xpos + 2][cP->Ypos - 1]->color ) )
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos + 2, cP->Ypos - 1, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}


		//check space one down two left: x-2 and y-1 : Xpos >= 2 && Ypos >= 1 to check out of bounce 
		//&& (the space is NULL || occupied by different color)
		if(cP->Xpos >= 2 && cP->Ypos >= 1)
		{
			if (( Board.board[cP->Xpos - 2][cP->Ypos - 1] == NULL || cP->color != Board.board[cP->Xpos - 2][cP->Ypos - 1]->color ) )
			{
				newMove = CreateMove(cP->Xpos, cP->Ypos, cP->Xpos - 2, cP->Ypos - 1, Board);
				AppendMoveList(possibleMovesList, newMove);
			}
		}
		
		return possibleMovesList;
}






