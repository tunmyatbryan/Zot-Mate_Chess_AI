/*
Change Log:
1/31 8:45 PM	-Tun 	- fully updated TestCheckLegal function
2/1	 			-Reza	- added TestCheckMate
						- added helper function for TestCheckMate
						- TestCheckMate 70% done at 12PM
2/1 7:00 PM	-Tun	- fully added TestCheckLegalBlocker function
2/2 11:30	- Reza	- final polish before logical debug
*/

#include <stdlib.h>
#include <stdio.h>

#include "Check.h"

/*
This function will check that desire color king is under check or not
If the king is under check, the move is not legal
It will scan the whole Board.board to find the king. Compare the type and color. Until it reaches the king with the DesireColor.
It will use the king position[x][y].
From the king position,
(1) Check two space right up and left up for white king OR black king. If there is a different Queen or King or pawn or bishop, CheckFlag = 1.
(2) Check diagonal right up, left up, right down and left down. If there is different color queen or bishop, CheckFlag = 1.
(3) Check vertical and horizontal (right, left, up and down) in 4 direction. If there is different color queen or Rook, CheckFlag = 1.
(4) Check the position for knight. If there is different color knight, CheckFlag = 1.
(5) Return the CheckFlag.
*/
int TestCheckLegal(THEBOARD Board, int DesireColor)
{
	/*
	scan Board.board[x][y] to find the king with DesireColor
	CheckFlag = 1 means Desire King is under checked. The move is not legal
	CheckFlag = 0 means Desire King is not under checked
	*/	
	int x, y, i, j, CheckFlag = 0;
	/*Create a new variable for King. ccP is current comparing piece. ccP will be compare with the King location.*/
	PIECE *KingPiece = NULL;
	PIECE *ccP;

	/*CopareType will compare the pieces with 'K'. CompareColor has to be same as DesireColor.*/
	char CompareType;
	int CompareColor;

	/*search the Board.board x axis*/
	for(i = 0; i <= 7; i++)
	{
		/*search the Board.board y axis*/
		for(j = 0; j <= 7; j++)
		{
			/*
			KingPiece is assigned by Board.board[x][y]. CompareType is assigned type we scan and CompareColor is assigned color we scan.
			As soon as the king and Desire color is match, get out of the loop and use that x and y value of king position.
			*/
			KingPiece = Board.board[i][j];
			if (KingPiece != NULL)
			{
				CompareType = KingPiece->type;
				CompareColor = KingPiece->color;
				if(CompareType == 'K' && CompareColor == DesireColor)
				{
					x = i;
					y = j;
					i = 8;
					j = 8;
				}
			}
		}
	}
	
	/*
		start checking 1 space right up down and left up down for pawn, king, bishop and queen
		It will check for both black and white pawns because black pawns move down and white pawns move up	
		checking 1 right up and 1 left up for black pawns for DesireColor white king	
	*/
	if(DesireColor == 0 && y <= 6)
	{
		/*checking right up 1 position*/
		if(x < 7)
		{
			/*reset the value for i and j. right up position from king position*/
			i = x+1;
			j = y+1;	
			ccP = Board.board[i][j];	
			if (Board.board[i][j] != NULL)
			{
				if(ccP->color == 1 && (ccP->type == 'Q' || ccP->type == 'K' || ccP->type == 'P' || ccP->type == 'B'))
				{
					CheckFlag = 1;
					return CheckFlag;
					/*for mod: return Board.board[i][j];*/
				}
			}
		}
		
		/*checking left up 1 position*/
		if(x > 0)
		{
			/*reset the value for i and j. left up position from king position*/
			i = x-1;
			j = y+1;
			ccP = Board.board[i][j];
			if (Board.board[i][j] != NULL)
			{
				if(ccP->color == 1 && (ccP->type == 'Q' || ccP->type == 'K' || ccP->type == 'P' || ccP->type == 'B') )
				{
					CheckFlag = 1;
					return CheckFlag;
				}
			}
		}
	}
	
	/*checking 1 right down and 1 left down for white pawns for DesireColor black king*/	
	if(DesireColor == 1 && y >= 1)
	{

		/*checking right down 1 position*/
		if(x < 7)
		{
			/*reset the value for i and j. right down position from king position*/
			i = x+1;
			j = y-1;
			ccP = Board.board[i][j];
			if (Board.board[i][j] != NULL)
			{
				if(ccP->color == 0 && (ccP->type == 'Q' || ccP->type == 'K' || ccP->type == 'P' || ccP->type == 'B') )
				{
					CheckFlag = 1;
					return CheckFlag;
				}
			}
		}
		
		/*checking left down 1 position*/
		if(x > 0)
		{
			/*reset the value for i and j. left down position from king position*/
			i = x-1;
			j = y-1;
			ccP = Board.board[i][j];
			if (Board.board[i][j] != NULL)
			{
				if(ccP->color == 0 && (ccP->type == 'Q' || ccP->type == 'K' || ccP->type == 'P' || ccP->type == 'B') )
				{
					CheckFlag = 1;
					return CheckFlag;
				}
			}
		}
	}
/*end checking 1 space right up down and left up down for pawn, king, bishop and queen	*/


/*start checking for bishop diagonal checking right up diagonal for queen or bishop*/
	if (x < 7 && y < 7 )
		{
			/*reset i and j. Going right up [x++][y++]*/
			i = x+1;
			j = y+1;
			
			/*check the space until it reach not NULL space.*/
			while ( i <= 7 && j <= 7 && Board.board[i][j] == NULL ) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i++;
				j++;
			}
			
			/*check the last not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is Queen or bishop.*/
			if( i<=7 && j<=7 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color != DesireColor && (ccP->type == 'Q' || ccP->type == 'B') )
					{
						CheckFlag = 1;
						return CheckFlag;
					}
				}
			}
		}
		
		/*checking left up diagonal for queen or bishop*/
		if (x > 0 && y < 7 ) 
		{
			/*reset i and j. Going left up [x--][y++]*/
			i = x-1;
			j = y+1;
			
			/*check the space until it reach not NULL space.*/
			while ( i >= 0 && j <= 7 && Board.board[i][j] == NULL)
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i--;
				j++;
			}
			
			/*check the last not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is Queen or bishop.*/
			ccP = Board.board[i][j];
			if(i >= 0 && j <= 7)
			{
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color != DesireColor && (ccP->type == 'Q' || ccP->type == 'B') )
					{
						CheckFlag = 1;
						return CheckFlag;
					}
				}
			}
		}		
		
		/*checking left down diagonal for queen or bishop*/
		if (x > 0 && y > 0 ) 
		{
			/*reset i and j. Going left up [x--][y--]*/
			i = x-1;
			j = y-1;
			
			/*check the space until it reach not NULL space.*/
			while (i >= 0 && j >= 0 && Board.board[i][j] == NULL ) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i--;
				j--;
			}

			/*check the last not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is Queen or bishop.*/
			if( i >= 0 && j >= 0 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color != DesireColor && (ccP->type == 'Q' || ccP->type == 'B') )
					{
						CheckFlag = 1;
						return CheckFlag;
					}
				}
			}
		}		
		
		/*checking right down diagonal for queen or bishop*/
		if (x < 7 && y > 0 ) 
		{
			/*reset i and j. Going left up [x++][y--]*/
			i = x+1;
			j = y-1;
			
			/*check the space until it reach not NULL space.*/
			while (i <= 7 && j >= 0 && Board.board[i][j] == NULL) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i++;
				j--;
			}
			
			/*check the last not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is Queen or bishop.*/
			if( i <= 7 && j >= 0 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color != DesireColor && (ccP->type == 'Q' || ccP->type == 'B') )
					{
						CheckFlag = 1;
						return CheckFlag;
					}
				}
			}
		}		
/*end checking diagonal for bishop and queen*/


/*start checking horizontal and vertical for Rook*/
		/*checking down vertical for queen or Rook*/
		if ( y > 0 ) 
		{
			/*reset i and j. Going down [x][y--]*/
			i = x;
			j = y-1;
			
			/*check the space until it reach not NULL space.*/
			while (j >= 0 && Board.board[i][j] == NULL ) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				j--;
			}
			
			/*check the last not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is Queen or Rook.*/
			if( j >= 0 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color != DesireColor && (ccP->type == 'Q' || ccP->type == 'R') )
					{
						CheckFlag = 1;
						return CheckFlag;
					}
				}
			}
		}
		
		/*checking up vertical for queen or Rook*/
		if ( y < 7 ) 
		{
			/*reset i and j. Going down [x][y--]*/
			i = x;
			j = y+1;
			
			/*check the space until it reach not NULL space.*/
			while ( j <= 7 && Board.board[i][j] == NULL) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				j++;
			}
			
			/*check the last not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is Queen or Rook.*/
			if( j <= 7 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color != DesireColor && (ccP->type == 'Q' || ccP->type == 'R') )
					{
						CheckFlag = 1;
						return CheckFlag;
					}
				}
			}
		}

		/*checking right horizontal for queen or bishop*/
		if ( x < 7 ) 
		{
			/*reset i and j. Going down [x][y--]*/
			i = x+1;
			j = y;
			
			/*check the space until it reach not NULL space.*/
			while (i <= 7 && Board.board[i][j] == NULL) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i++;
			}
			
			/*check the last not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is Queen or bishop.*/
			if( i <= 7 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color != DesireColor && (ccP->type == 'Q' || ccP->type == 'R') )
					{
						CheckFlag = 1;
						return CheckFlag;
					}
				}
			}
		}

		/*checking left horizontal for queen or bishop*/
		if ( x > 0 ) 
		{
			/*reset i and j. Going down [x][y--]*/
			i = x-1;
			j = y;
			
			/*check the space until it reach not NULL space.*/
			while ( i >= 0 && Board.board[i][j] == NULL) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i--;
			}
			
			/*check the last not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is Queen or bishop.*/
			if( i >= 0 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color != DesireColor && (ccP->type == 'Q' || ccP->type == 'R') )
					{
						CheckFlag = 1;
						return CheckFlag;
					}
				}
			}
		}
/*end checking vertical and horizontal for Queen and rook*/

/*start checking 2+1 space for Knight*/
		/*checking two up one right: x+1 and y+2 for Knight*/
		if ( x <= 6 && y <= 5) 
		{
			/*reset i and j. Going to [x+1][y+2]*/
			i = x+1;
			j = y+2;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if(ccP->color != DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = 1;
					return CheckFlag;
				}
			}
		}
		
		/*checking two up one left: x-1 and y+2 for Knight*/
		if ( x >= 1 && y <= 5) 
		{
			/*reset i and j. Going to [x-1][y+2]*/
			i = x-1;
			j = y+2;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if(Board.board[i][j] != NULL && ccP->color != DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = 1;
					return CheckFlag;
				}
			}
		}

		/*checking one up two right: x+2 and y+1 for Knight*/
		if ( x <= 1 && y <= 6) 
		{
			/*reset i and j. Going to [x+2][y+1]*/
			i = x+2;
			j = y+1;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if(ccP->color != DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = 1;
					return CheckFlag;
				}
			}
		}

		/*checking one up two left: x-2 and y+1 for Knight*/
		if ( x >= 2 && y <= 6) 
		{
			/*reset i and j. Going to [x-2][y+1]*/
			i = x-2;
			j = y+1;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if(ccP->color != DesireColor &&  ccP->type == 'H' )
				{
				CheckFlag = 1;
				return CheckFlag;
				}
			}
		}

		/*checking two down one right: x+1 and y-2 for Knight*/
		if ( x <= 6 && y >= 2) 
		{
			/*reset i and j. Going to [x+1][y-2]*/
			i = x+1;
			j = y-2;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if(ccP->color != DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = 1;
					return CheckFlag;
				}
			}
		}

		/*checking two down one left: x-1 and y-2 for Knight*/
		if ( x >= 1 && y >= 2) 
		{
			/*reset i and j. Going to [x-1][y-2]*/
			i = x-1;
			j = y-2;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color != DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = 1;
					return CheckFlag;
				}
			}
		}

		/*checking one down two right: x+2 and y-1 for Knight*/
		if ( x <= 5 && y >= 1) 
		{
			/*reset i and j. Going to [x+2][y-1]*/
			i = x+2;
			j = y-1;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color != DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = 1;
					return CheckFlag;
				}
			}
		}

		/*checking one down two left: x-2 and y-1 for Knight*/
		if ( x >= 2 && y >= 1) 
		{
			/*reset i and j. Going to [x-2][y-1]*/
			i = x-2;
			j = y-1;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color != DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = 1;
					return CheckFlag;
				}
			}
		}
/*end checking horizontal and vertical for Rook*/

	/*if the checking conditions are all clear, CheckFlag = 0 and return. It means legal check move.*/
	return CheckFlag;
}

/*
	Verifies recent move by "color" does not put "color in check
	return type
		0 - Not in check aka legal move
		1 - In check aka illegal
*/

int TestCheckMate(THEBOARD Board, int color, ALIST *white, ALIST *black)
{	
	/*Local Variables*/
	int	state = 0; /*0 - no check, 1 - check, 2 -checkMate*/
	int	xKing, yKing; /*coordinates {0, 1, ..., 7} of "color" King.*/
	int	xAttacker, yAttacker; /*coordinates of 1-"color" attacker.*/
	THEBOARD tempBoard;
	PIECE 	*attacker 		= NULL; /*pointer to attacking piece if found*/
	PIECE	*king			= NULL;
	MLIST 	*possibleMoves 	= NULL; /*used to generate a list of moves per piece*/
	MENTRY 	*currentMEntry 	= NULL; /*used to traverse possibleMovesList of a player we are inspecting (to kill attacker/block)*/
	MOVE	*currentMove	= NULL; /*used to keep track of Move struct of MENTRY*/
	AENTRY 	*currentAEntry 	= NULL; /*used to traverse AliveList of int color*/
	
/*	printf("starting testcheckmate, calling TCLA() \n");*/
	
	/*First see if color is in check*/
	/*previous: state = TestCheckLegalAttacker(...)*/
	attacker = TestCheckLegalAttacker(Board, color);
	
	/*If "color is not in check, return 0*/
	if (attacker == NULL) /*revious: state ==0*/
		return 0;
		
	/*"color" is in check, must test for checkMate	*/
	else if (attacker != NULL) /*previous: state == 1*/
	{
		/* 
			Control Flow
done			1.	Scan color's Alive list and note down the King Coordinate using xKing and yKing.note the attacker's coordinates too 
			2.	mod tun's code.
			3.	Order of verifying the checkMate
				3.1	Note the attacker's coordinates, call Generate LegalMoves for all color's pieces to kill attacker
					3.1.1	Handle whether black or white ALIST is traversed
						3.1.1.a	Traverse appropriate ALIST
					3.1.2	Must create a case statement and call appropriate type
					3.1.3	After List Generated, traverse and compare x/yfinal to x/yattacker
						3.1.3.a	if no similarity, then delete the list and back to 3.1.1.a
						3.1.3.b if similarity, we can kill attacker thus returning 1 - we are in check only 9
				
				3.2 if failed, try to move the king in nbhd.		
				3.3 If failed, then find attacker's line of motion, and try and block it. Special exclusion to 3.2: attacker of type knight
					3.3 can be implemented into 3.1 *possibly*
				 
		*/
		
		/*traverse board, find color's King. Note X, Y coordinate*/
		int end = 0; /*simple flag for when we find King*/
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (Board.board[i][j] != NULL)
				{
					if (Board.board[i][j]->type == 'K' && Board.board[i][j]->color == color)
					{
						xKing = i;
						yKing = j;
						end = 1; /*set the flag*/
						break; /*break inner for*/
					}
				}
			}
			
			if(end) break; /*found King, so break outer for*/
		}
		
		xAttacker = attacker->Xpos;
		yAttacker = attacker->Ypos;
		
		/*handle which AliveList to traverse to kill attacker's move*/
		if (color == 0) /*white;*/
			currentAEntry = white->First;
		else if (color == 1) /*black*/
			currentAEntry = black->First;
		
		while (currentAEntry) /*traverse thru the list until EndOfList*/
		{
			switch(currentAEntry->AlivePiece->type) /*Case is what type of piece we have for List {Q, B, R, N, P}. no king*/
			{
				case ('Q'):
				{
					possibleMoves = QueenLegalMoveListGen(currentAEntry->AlivePiece, Board);
					break;
				}
				case ('B'):
				{
					possibleMoves = BishopLegalMoveListGen(currentAEntry->AlivePiece, Board);
					break;
				}
				case ('R'):
				{
					possibleMoves = RookLegalMoveListGen(currentAEntry->AlivePiece, Board);
					break;
				}
				case ('H'):
				{
					possibleMoves = KnightLegalMoveListGen(currentAEntry->AlivePiece, Board);
					break;
				}
				case ('P'):
				{
					possibleMoves = PawnLegalMoveListGen(currentAEntry->AlivePiece, Board);
					break;
				}
				case ('K'):
					break;
				default:
				{
					return 1;
				}
			} /*end switch, we have a piece and the MLIST. traverse MLIST until if x/yAttackr is found*/
			
			/*Traverse thru the generatedMoveList and find a match for finX == xattacker, and for Y.*/
			if(currentAEntry->AlivePiece->type != 'K')
			{
				if(possibleMoves->Length != 0)
				{
					currentMEntry = possibleMoves->First;
				
					while(currentMEntry)
					{
						currentMove = currentMEntry->PotentialMove;
					
						if((currentMove->finX == xAttacker) && (currentMove->finY == yAttacker)) /*compare final coord*/
						{
							return 1; /*we can kill the attacker, thus only in check and return 1;*/
						}
						currentMEntry = currentMEntry->Next;
					} /*end while loop of currentPiece Moves*/
				
				}
			 
				DeleteMoveList(possibleMoves); /*delete possibleMoves so we can create a new list for next Alive.*/
				
			}
			currentAEntry = currentAEntry->Next;
			
		} /*end of aliveListMoves. If we reach this point, no color player can attack 1-color attacker.*/
		
		/*3.2*/
		/*generate legal moves for king to check for */
		king = Board.board[xKing][yKing];
		possibleMoves = KingLegalMoveListGen(king, Board);
		currentMEntry = possibleMoves->First;
		
		if (possibleMoves->Length != 0) /*if length == 0 then no mech legal move for king, so just skip the code and try to block*/
		{
			while(currentMEntry)
			{
				/*fill the temp board*/
				for(int i = 0; i < 8; i++)
				{
					for(int j = 0; j < 8; j++)
					{
						tempBoard.board[i][j] = Board.board[i][j];
					}	
				}
			
				MovePiece(currentMEntry->PotentialMove, &tempBoard, 0, white, black);
				state = TestCheckLegal(tempBoard, color);
				
				if(state == 0)
				{
					return 1;
				}
				
				currentMEntry = currentMEntry->Next;
			}
		}
		
		DeleteMoveList(possibleMoves);
		
		/*if we reach this point, king cannot move away from attack. must block.*/
		
		if(attacker->type == 'H')
		{
			return 2;
		}
		else
		{
			int xDifference, yDifference;
			xDifference = xKing - xAttacker;
			yDifference = yKing - yAttacker;
			int i, j;
			PIECE *potentialBlocker = NULL;

			/*1*/
			if(xDifference == 0 && yDifference > 0)
			{
				i = xKing;
				for(j = yKing - 1; j > yAttacker; j--)
				{
					potentialBlocker = TestCheckLegalBlocker(Board, color, i, j);
					if(potentialBlocker != NULL)
					{
						return 1;
					}
				}
			}

			/*2*/
			else if(xDifference == 0 && yDifference < 0)
			{
			
				i = xKing;
				for(j = yKing + 1; j < yAttacker; j++)
				{
					potentialBlocker = TestCheckLegalBlocker(Board, color, i, j);
					if(potentialBlocker != NULL)
						return 1;
				}
			}

			/*3*/
			else if(xDifference > 0 && yDifference == 0)
			{
				j = yKing;
				for(i = xKing - 1; i > xAttacker; i--)
				{
					potentialBlocker = TestCheckLegalBlocker(Board, color, i, j);
					if(potentialBlocker != NULL)
					{
						return 1;
					}
				}
			}

			/*4*/
			else if(xDifference < 0 && yDifference == 0)
			{
				j = yKing;
				for(i = xKing + 1; i < xAttacker; i++)
				{
					potentialBlocker = TestCheckLegalBlocker(Board, color, i, j);
					if(potentialBlocker != NULL)
					{
						return 1;
					}
				}
			}

			/*5*/
			else if(xDifference < 0 && yDifference > 0)
			{
				i = xKing + 1;
				for(j = yKing - 1; j > yAttacker; j--, i++)
				{
					potentialBlocker = TestCheckLegalBlocker(Board, color, i, j);
					if(potentialBlocker != NULL)
					{
						return 1;
					}
				}

			}

			/*6*/
			else if(xDifference > 0 && yDifference < 0)
			{
				i = xKing - 1;
				for(j = yKing + 1; j < yAttacker; j++, i--)
				{
					potentialBlocker = TestCheckLegalBlocker(Board, color, i, j);
					if(potentialBlocker != NULL)
					{
						return 1;
					}
				}
			}

			/*7*/
			else if(xDifference > 0 && yDifference > 0)
			{
				i = xKing - 1;
				for(j = yKing - 1; j > yAttacker; j--, i--)
				{
					potentialBlocker = TestCheckLegalBlocker(Board, color, i, j);
					if(potentialBlocker != NULL)
					{
						return 1;
					}
				}
			}

			/*8*/
			else if(xDifference < 0 && yDifference < 0)
			{
				i = xKing + 1;
				for(j = yKing + 1; j < yAttacker; j++, i++)
				{
					potentialBlocker = TestCheckLegalBlocker(Board, color, i, j);
					if(potentialBlocker != NULL)
					{
						return 1;
					}
				}
	

			}

			else
			{
				/*error*/
			}
		}	
	}

	return 2;
}


/*
This function will check that desire color king is under check or not
If the king is under check, it will return the pointer of the attacker.
If the king is not under check, it will return NULL.
It will scan the whole Board.board to find the king. Compare the type and color. Until it reaches the king with the DesireColor.
It will use the king position[x][y].
From the king position,
(1) Check two space right up and left up for white king OR black king. If there is a different Queen or King or pawn or bishop, CheckFlag = attacker pointer.
(2) Check diagonal right up, left up, right down and left down. If there is different color queen or bishop, CheckFlag = attacker pointer.
(3) Check vertical and horizontal (right, left, up and down) in 4 direction. If there is different color queen or Rook, CheckFlag = attacker pointer.
(4) Check the position for knight. If there is different color knight, CheckFlag = attacker pointer.
(5) Return the CheckFlag as soon as the attacker is found.
*/

PIECE *TestCheckLegalAttacker(THEBOARD Board, int DesireColor)
{
	/*
	scan Board.board[x][y] to find the king with DesireColor
	CheckFlag = ccP means Desire King is under checked. The move is not legal
	CheckFlag = 0 means Desire King is not under checked
	*/	
	int x, y, i, j;
	PIECE *CheckFlag = NULL;

	/*Create a new variable for King. ccP is current comparing piece. ccP will be compare with the King location.*/
	PIECE *KingPiece = NULL;
	PIECE *ccP = NULL;

	/*CopareType will compare the pieces with 'K'. CompareColor has to be same as DesireColor.*/
	char CompareType;
	int CompareColor;

	/*search the Board.board x axis*/
	for(i = 0; i <= 7; i++)
	{
		/*search the Board.board y axis*/
		for(j = 0; j <= 7; j++)
		{
			/*
			KingPiece is assigned by Board.board[x][y]. CompareType is assigned type we scan and CompareColor is assigned color we scan.
			As soon as the king and Desire color is match, get out of the loop and use that x and y value of king position.
			*/
			KingPiece = Board.board[i][j];
			if (KingPiece != NULL)
			{
				CompareType = KingPiece->type;
				CompareColor = KingPiece->color;
				if(CompareType == 'K' && CompareColor == DesireColor)
				{
					x = i;
					y = j;
					i = 8;
					j = 8;
				}
			}
		}
	}

/*start checking 1 space right up, down and left up, down for pawn, king, bishop and queen*/
/*It will check for both black and white pawns because black pawns move down and white pawns move up*/	
	/*checking 1 right up and 1 left up for black pawns for DesireColor white king	*/
	if(DesireColor == 0 && y <= 6)
	{
		/*checking right up 1 position*/
		if(x < 7)
		{
			/*reset the value for i and j. right up position from king position*/
			i = x+1;
			j = y+1;
			ccP = Board.board[i][j];
			if(Board.board[i][j] != NULL)
			{
				if(ccP->color == 1 && (ccP->type == 'Q' || ccP->type == 'K' || ccP->type == 'P' || ccP->type == 'B') )
				{
					CheckFlag = ccP;
					return CheckFlag;
					/*for mod: return Board.board[i][j];*/
				}
			}
		}
		
		/*checking left up 1 position*/
		if(x > 0)
		{
			/*reset the value for i and j. left up position from king position*/
			i = x-1;
			j = y+1;
			ccP = Board.board[i][j];
			if(Board.board[i][j] != NULL)
			{
				if(ccP->color == 1 && (ccP->type == 'Q' || ccP->type == 'K' || ccP->type == 'P' || ccP->type == 'B') )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}
	}
	
	/*checking 1 right down and 1 left down for white pawns for DesireColor black king	*/
	if(DesireColor == 1 && y >= 1)
	{
		/*checking right down 1 position*/
		if(x < 7)
		{
			/*reset the value for i and j. right down position from king position*/
			i = x+1;
			j = y-1;
			ccP = Board.board[i][j];
			if(Board.board[i][j] != NULL)
			{
				if(ccP->color == 0 && (ccP->type == 'Q' || ccP->type == 'K' || ccP->type == 'P' || ccP->type == 'B') )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}
		
		/*checking left down 1 position*/
		if(x > 0)
		{
			/*reset the value for i and j. left down position from king position*/
			i = x-1;
			j = y-1;
			ccP = Board.board[i][j];
			if(Board.board[i][j] != NULL)
			{
				if(ccP->color == 0 && (ccP->type == 'Q' || ccP->type == 'K' || ccP->type == 'P' || ccP->type == 'B') )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}
	}
/*end checking 1 space right up down and left up down for pawn, king, bishop and queen	*/


/*start checking for bishop diagonal*/
		/*checking right up diagonal for queen or bishop*/
		if (x < 7 && y < 7 )
		{
			/*reset i and j. Going right up [x++][y++]*/
			i = x+1;
			j = y+1;
			
			/*check the space until it reach not NULL space.*/
			while (Board.board[i][j] == NULL && i <= 7 && j <= 7) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i++;
				j++;
			}
			
			/*check the last not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is Queen or bishop.*/
			if( i <= 7 && j <= 7 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color != DesireColor && (ccP->type == 'Q' || ccP->type == 'B') )
					{
						CheckFlag = ccP;
						return CheckFlag;
				
					}
				}
			}
		}
		
		/*checking left up diagonal for queen or bishop*/
		if (x > 0 && y < 7 ) 
		{
			/*reset i and j. Going left up [x--][y++]*/
			i = x-1;
			j = y+1;
			
			/*check the space until it reach not NULL space.*/
			while (Board.board[i][j] == NULL && i >= 0 && j <= 7) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i--;
				j++;
			}
			
			/*check the last not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is Queen or bishop.*/
			if( i >= 0 && j <= 7 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color != DesireColor && (ccP->type == 'Q' || ccP->type == 'B') )
					{
						CheckFlag = ccP;
						return CheckFlag;
					}
				}
			}
		}		
		
		/*checking left down diagonal for queen or bishop*/
		if (x > 0 && y > 0 ) 
		{
			/*reset i and j. Going left up [x--][y--]*/
			i = x-1;
			j = y-1;
			
			/*check the space until it reach not NULL space.*/
			while (Board.board[i][j] == NULL && i >= 0 && j >= 0) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i--;
				j--;
			}
			
			/*check the last not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is Queen or bishop.*/
			if( i >= 0 && j >= 0 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color != DesireColor && (ccP->type == 'Q' || ccP->type == 'B') )
					{
						CheckFlag = ccP;
						return CheckFlag;
					}
				}
			}
		}		
		
		/*checking right down diagonal for queen or bishop*/
		if (x < 7 && y > 0 ) 
		{
			/*reset i and j. Going left up [x++][y--]*/
			i = x+1;
			j = y-1;
			
			/*check the space until it reach not NULL space.*/
			while (Board.board[i][j] == NULL && i <= 7 && j >= 0) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i++;
				j--;
			}
			
			/*check the last not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is Queen or bishop.*/
			if( i <= 7 && j >= 0 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color != DesireColor && (ccP->type == 'Q' || ccP->type == 'B') )
					{
						CheckFlag = ccP;
						return CheckFlag;
					}
				}
			}
		}			
/*end checking diagonal for bishop and queen*/


/*start checking horizontal and vertical for Rook*/

		/*checking down vertical for queen or Rook*/
		if ( y > 0 ) 
		{
			/*reset i and j. Going down [x][y--]*/
			i = x;
			j = y-1;
			
			/*check the space until it reach not NULL space.*/
			while (Board.board[i][j] == NULL && j >= 0) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				j--;
			}
			
			/*check the last not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is Queen or Rook.*/
			if( j >= 0 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color != DesireColor && (ccP->type == 'Q' || ccP->type == 'R') )
					{
						CheckFlag = ccP;
						return CheckFlag;
					}
				}
			}
		}
		
		/*checking up vertical for queen or Rook*/
		if ( y < 7 ) 
		{
			/*reset i and j. Going down [x][y--]*/
			i = x;
			j = y+1;
			
			/*check the space until it reach not NULL space.*/
			while (Board.board[i][j] == NULL && j <= 7) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				j++;
			}
			
			/*check the last not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is Queen or Rook.*/
			if( j <= 7 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color != DesireColor && (ccP->type == 'Q' || ccP->type == 'R') )
					{
						CheckFlag = ccP;
						return CheckFlag;
					}
				}
			}
		}

		/*checking right horizontal for queen or bishop*/
		if ( x < 7 ) 
		{
			/*reset i and j. Going down [x][y--]*/
			i = x+1;
			j = y;
			
			/*check the space until it reach not NULL space.*/
			while (Board.board[i][j] == NULL && i <= 7) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i++;
			}
			
			/*check the last not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is Queen or bishop.*/
			if( i <= 7 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color != DesireColor && (ccP->type == 'Q' || ccP->type == 'R') )
					{
						CheckFlag = ccP;
						return CheckFlag;
					}
				}
			}
		}

		/*checking left horizontal for queen or bishop*/
		if ( x > 0 ) 
		{
			/*reset i and j. Going down [x][y--]*/
			i = x-1;
			j = y;
			
			/*check the space until it reach not NULL space.*/
			while (Board.board[i][j] == NULL && i >= 0) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i--;
			}
			
			/*check the last not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is Queen or bishop.*/
			if( i >= 0 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color != DesireColor && (ccP->type == 'Q' || ccP->type == 'R') )
					{
						CheckFlag = ccP;
						return CheckFlag;
					}
				}
			}
		}
/*end checking vertical and horizontal for bishop and rook*/

/*start checking 2+1 space for Knight*/

		/*checking two up one right: x+1 and y+2 for Knight*/
		if ( x <= 6 && y <= 5) 
		{
			/*reset i and j. Going to [x+1][y+2]*/
			i = x+1;
			j = y+2;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color != DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}
		
		/*checking two up one left: x-1 and y+2 for Knight*/
		if ( x >= 1 && y <= 5) 
		{
			/*reset i and j. Going to [x-1][y+2]*/
			i = x-1;
			j = y+2;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color != DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}

		/*checking one up two right: x+2 and y+1 for Knight*/
		if ( x <= 1 && y <= 6) 
		{
			/*reset i and j. Going to [x+2][y+1]*/
			i = x+2;
			j = y+1;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color != DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}

		/*checking one up two left: x-2 and y+1 for Knight*/
		if ( x >= 2 && y <= 6) 
		{
			/*reset i and j. Going to [x-2][y+1]*/
			i = x-2;
			j = y+1;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color != DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}

		/*checking two down one right: x+1 and y-2 for Knight*/
		if ( x <= 6 && y >= 2) 
		{
			/*reset i and j. Going to [x+1][y-2]*/
			i = x+1;
			j = y-2;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color != DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}

		/*checking two down one left: x-1 and y-2 for Knight*/
		if ( x >= 1 && y >= 2) 
		{
			/*reset i and j. Going to [x-1][y-2]*/
			i = x-1;
			j = y-2;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color != DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}

		/*checking one down two right: x+2 and y-1 for Knight*/
		if ( x <= 5 && y >= 1) 
		{
			/*reset i and j. Going to [x+2][y-1]*/
			i = x+2;
			j = y-1;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color != DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}

		/*checking one down two left: x-2 and y-1 for Knight*/
		if ( x >= 2 && y >= 1) 
		{
			/*reset i and j. Going to [x-2][y-1]*/
			i = x-2;
			j = y-1;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is not the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color != DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}
/*end checking horizontal and vertical for Rook*/

	/*if the checking conditions are all clear, CheckFlag = 0 and return. It means legal check move.*/
	return CheckFlag;
}


/*
When the king is under check and there is no space to move to get out of check. So we want to find a blocker.
This function will find that desire color blocker that can save the king from check.
If the blcoker is found, it will return the pointer of the blocker.
If the blcoker is not found, it will return NULL.
It will receive the Desire space X and Y and desire color.
From the desire position,
(1) Check two space right up and left up for white king OR black king. If there is a different Queen or King or pawn or bishop, CheckFlag = attacker pointer.
(2) Check diagonal right up, left up, right down and left down. If there is different color queen or bishop, CheckFlag = attacker pointer.
(3) Check vertical and horizontal (right, left, up and down) in 4 direction. If there is different color queen or Rook, CheckFlag = attacker pointer.
(4) Check the position for knight. If there is different color knight, CheckFlag = attacker pointer.
(5) Return the CheckFlag as soon as the blocker is found.
*/
PIECE *TestCheckLegalBlocker(THEBOARD Board, int DesireColor, int DesireX, int DesireY)
{
	/*
	Assign x and y as desireX and desireY.
	i and j will be used to find the blocker
	*/	
	int x, y, i, j;
	x = DesireX;
	y = DesireY;
	PIECE *CheckFlag = NULL;

	/*Create a new variable for the piece we want to compare. ccP is current comparing piece.*/
	PIECE *ccP;

/*start checking 1 space down and 2 space down for pawn. 1 space up and 2 space up for pawn.*/
/*2 space is for the pawn that is not moved yet.*/

/*It will check for both black and white pawns because black pawns move down and white pawns move up*/
	/*checking for white pawn*/
	if(DesireColor == 0 && y <= 7)
	{
		/*checking 1 space below for white pawn*/
		/*reset the value for i and j. [x][y-1]*/
		i = x;
		j = y-1;
		ccP = Board.board[i][j];

		/*checking 1 space below is occupied by white pawn*/
		if(Board.board[i][j] != NULL)
		{
			if(ccP->color == 0 && ccP->type == 'P')
			{
				CheckFlag = ccP;
				return CheckFlag;
			}
		}

		/*checking 2 space below for white pawn*/
		/*if the first 1 space is empty. The second space has to occupied by white pawn and that pawn is not moved yet*/
		ccP = Board.board[i][j-1];
		if( Board.board[i][j] == NULL && Board.board[i][j-1] != NULL ){
			if(ccP->color == 0 && ccP->type == 'P' && ccP->moveCount == 0)
			{
				CheckFlag = ccP;
				return CheckFlag;
			}
		}
	}
	
	/*checking for black pawn*/
	if(DesireColor == 1 && y >= 0)
	{
		/*checking 1 space up for black pawn*/
		/*reset the value for i and j. [x][y+1]*/
		i = x;
		j = y+1;
		ccP = Board.board[i][j];

		/*checking 1 space up is occupied by white pawn*/
		if(Board.board[i][j] != NULL)
		{
			if(ccP->color == 1 && ccP->type == 'P')
			{
				CheckFlag = ccP;
				return CheckFlag;
			}
		}

		/*checking 2 space up for white pawn*/
		/*if the first 1 space is empty. The second space has to occupied by white pawn and that pawn is not moved yet*/
		ccP = Board.board[i][j+1];
		if(Board.board[i][j+1] != NULL && Board.board[i][j] == NULL)
		{
			if(ccP->color == 1 && ccP->type == 'P' && ccP->moveCount == 0)
			{
				CheckFlag = ccP;
				return CheckFlag;
			}
		}
	}

/*end checking for pawn*/


/*start checking for bishop diagonal*/
		/*checking right up diagonal for queen or bishop*/
		if (x < 7 && y < 7 )
		{
			/*reset i and j. Going right up [x++][y++]*/
			i = x+1;
			j = y+1;
			
			/*check the space until it reach not NULL space.*/
			while (Board.board[i][j] == NULL && i <= 7 && j <= 7) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i++;
				j++;
			}
			
			/*check the last not NULL space. If the space is occupied the pieces, check it's color and type.*/
			/*current color is the same with the occupied color. If the piece is Queen or bishop.*/
			if( i <= 7 && j <= 7 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color == DesireColor && (ccP->type == 'Q' || ccP->type == 'B') )
					{
						CheckFlag = ccP;
						return CheckFlag;
				
					}
				}
			}
		}
		
		/*checking left up diagonal for queen or bishop*/
		if (x > 0 && y < 7 ) 
		{
			/*reset i and j. Going left up [x--][y++]*/
			i = x-1;
			j = y+1;
			
			/*check the space until it reach not NULL space.*/
			while (Board.board[i][j] == NULL && i >= 0 && j <= 7) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i--;
				j++;
			}
			
			/*check the last not NULL space. If the space is occupied the pieces, check it's color and type.*/
			/*current color is the same with the occupied color. If the piece is Queen or bishop.*/
			if( i >= 0 && j <= 7 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color == DesireColor && (ccP->type == 'Q' || ccP->type == 'B') )
					{
						CheckFlag = ccP;
						return CheckFlag;
					}
				}
			}
		}		
		
		/*checking left down diagonal for queen or bishop*/
		if (x > 0 && y > 0 ) 
		{
			/*reset i and j. Going left up [x--][y--]*/
			i = x-1;
			j = y-1;
			
			/*check the space until it reach not NULL space.*/
			while (Board.board[i][j] == NULL && i >= 0 && j >= 0) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i--;
				j--;
			}
			
			/*check the last not NULL space. If the space is occupied the pieces, check it's color and type.*/
			/*current color is the same with the occupied color. If the piece is Queen or bishop.*/
			if( i >= 0 && j >= 0 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color == DesireColor && (ccP->type == 'Q' || ccP->type == 'B') )
					{
						CheckFlag = ccP;
						return CheckFlag;
					}
				}
			}
		}		
		
		/*checking right down diagonal for queen or bishop*/
		if (x < 7 && y > 0 ) 
		{
			/*reset i and j. Going left up [x++][y--]*/
			i = x+1;
			j = y-1;
			
			/*check the space until it reach not NULL space.*/
			while (Board.board[i][j] == NULL && i <= 7 && j >= 0) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i++;
				j--;
			}
			
			/*check the last not NULL space. If the space is occupied the pieces, check it's color and type.*/
			/*current color is the same with the occupied color. If the piece is Queen or bishop.*/
			if( i <= 7 && j >= 0 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color == DesireColor && (ccP->type == 'Q' || ccP->type == 'B') )
					{
						CheckFlag = ccP;
						return CheckFlag;
					}
				}
			}
		}			
/*end checking diagonal for bishop and queen*/


/*start checking horizontal and vertical for Rook*/

		/*checking down vertical for queen or Rook*/
		if ( y > 0 ) 
		{
			/*reset i and j. Going down [x][y--]*/
			i = x;
			j = y-1;
			
			/*check the space until it reach not NULL space.*/
			while (Board.board[i][j] == NULL && j >= 0) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				j--;
			}
			
			/*check the last not NULL space. If the space is occupied the pieces, check it's color and type.*/
			/*current color is the same with the occupied color. If the piece is Queen or Rook.*/
			if( j >= 0 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color == DesireColor && (ccP->type == 'Q' || ccP->type == 'R') )
					{
						CheckFlag = ccP;
						return CheckFlag;
					}
				}
			}
		}
		
		/*checking up vertical for queen or Rook*/
		if ( y < 7 ) 
		{
			/*reset i and j. Going down [x][y--]*/
			i = x;
			j = y+1;
			
			/*check the space until it reach not NULL space.*/
			while (Board.board[i][j] == NULL && j <= 7) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				j++;
			}
			
			/*check the last not NULL space. If the space is occupied the pieces, check it's color and type.*/
			/*current color is the same with the occupied color. If the piece is Queen or Rook.*/
			if( j <= 7 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color == DesireColor && (ccP->type == 'Q' || ccP->type == 'R') )
					{
						CheckFlag = ccP;
						return CheckFlag;
					}
				}
			}
		}

		/*checking right horizontal for queen or bishop*/
		if ( x < 7 ) 
		{
			/*reset i and j. Going down [x][y--]*/
			i = x+1;
			j = y;
			
			/*check the space until it reach not NULL space.*/
			while (Board.board[i][j] == NULL && i <= 7) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i++;
			}
			
			/*check the last not NULL space. If the space is occupied the pieces, check it's color and type.*/
			/*current color is the same with the occupied color. If the piece is Queen or bishop.*/
			if( i <= 7 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color == DesireColor && (ccP->type == 'Q' || ccP->type == 'R') )
					{
						CheckFlag = ccP;
						return CheckFlag;
					}
				}
			}
		}

		/*checking left horizontal for queen or bishop*/
		if ( x > 0 ) 
		{
			/*reset i and j. Going down [x][y--]*/
			i = x-1;
			j = y;
			
			/*check the space until it reach not NULL space.*/
			while (Board.board[i][j] == NULL && i >= 0) 
			{
				/*assign the current position to ccP*/
				ccP = Board.board[i][j];
				i--;
			}
			
			/*check the last not NULL space. If the space is occupied the pieces, check it's color and type.*/
			/*current color is the same with the occupied color. If the piece is Queen or bishop.*/
			if( i >= 0 )
			{
				ccP = Board.board[i][j];
				if(Board.board[i][j] != NULL)
				{
					if(ccP->color == DesireColor && (ccP->type == 'Q' || ccP->type == 'R') )
					{
						CheckFlag = ccP;
						return CheckFlag;
					}
				}
			}
		}
/*end checking vertical and horizontal for bishop and rook*/

/*start checking 2+1 space for Knight*/

		/*checking two up one right: x+1 and y+2 for Knight*/
		if ( x <= 6 && y <= 5) 
		{
			/*reset i and j. Going to [x+1][y+2]*/
			i = x+1;
			j = y+2;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the pieces, check it's color and type.*/
			/*current color is the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color == DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}
		
		/*checking two up one left: x-1 and y+2 for Knight*/
		if ( x >= 1 && y <= 5) 
		{
			/*reset i and j. Going to [x-1][y+2]*/
			i = x-1;
			j = y+2;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the pieces, check it's color and type.*/
			/*current color is the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color == DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}

		/*checking one up two right: x+2 and y+1 for Knight*/
		if ( x <= 1 && y <= 6) 
		{
			/*reset i and j. Going to [x+2][y+1]*/
			i = x+2;
			j = y+1;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the pieces, check it's color and type.*/
			/*current color is the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color == DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}

		/*checking one up two left: x-2 and y+1 for Knight*/
		if ( x >= 2 && y <= 6) 
		{
			/*reset i and j. Going to [x-2][y+1]*/
			i = x-2;
			j = y+1;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the pieces, check it's color and type.*/
			/*current color is the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color == DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}

		/*checking two down one right: x+1 and y-2 for Knight*/
		if ( x <= 6 && y >= 2) 
		{
			/*reset i and j. Going to [x+1][y-2]*/
			i = x+1;
			j = y-2;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the pieces, check it's color and type.*/
			/*current color is the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color == DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}

		/*checking two down one left: x-1 and y-2 for Knight*/
		if ( x >= 1 && y >= 2) 
		{
			/*reset i and j. Going to [x-1][y-2]*/
			i = x-1;
			j = y-2;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color == DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}

		/*checking one down two right: x+2 and y-1 for Knight*/
		if ( x <= 5 && y >= 1) 
		{
			/*reset i and j. Going to [x+2][y-1]*/
			i = x+2;
			j = y-1;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color == DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}

		/*checking one down two left: x-2 and y-1 for Knight*/
		if ( x >= 2 && y >= 1) 
		{
			/*reset i and j. Going to [x-2][y-1]*/
			i = x-2;
			j = y-1;
			ccP = Board.board[i][j];
			/*check that is not NULL space. If the space is occupied the enemy, it can be capture.*/
			/*current color is the same with the occupied color. If the piece is knight. Knight is H*/
			if(Board.board[i][j] != NULL)
			{
				if( ccP->color == DesireColor &&  ccP->type == 'H' )
				{
					CheckFlag = ccP;
					return CheckFlag;
				}
			}
		}
/*end checking horizontal and vertical for Rook*/

	/*if the checking conditions are all clear, CheckFlag = NULL and return. It means there is no available blocker.*/
	return CheckFlag;
}


/*
This function will check that Defender piece is under attack or not
If the Defender piece is under attack, it will return the pointer of the attacker.
If the Defender is not under attack, it will return NULL.
Set x and y position from Defender piece. Defender->Xpor.
From the Defender piece position,
(1) Check two space right up and left up for white king OR black king. If there is a different Queen or King or pawn or bishop, CheckFlag = attacker pointer.
(2) Check diagonal right up, left up, right down and left down. If there is different color queen or bishop, CheckFlag = attacker pointer.
(3) Check vertical and horizontal (right, left, up and down) in 4 direction. If there is different color queen or Rook, CheckFlag = attacker pointer.
(4) Check the position for knight. If there is different color knight, CheckFlag = attacker pointer.
(5) Return the CheckFlag as soon as the attacker is found.
*/


