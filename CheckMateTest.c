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
	
	printf("starting testcheckmate, calling TCLA() \n");
	
	/*First see if color is in check*/
	/*previous: state = TestCheckLegalAttacker(...)*/
	attacker = TestCheckLegalAttacker(Board, color);
	
	/*If "color is not in check, return 0*/
	if (attacker == NULL) /*revious: state ==0*/
	{
		printf("no attacker so return 0\n");
		return 0;
	}
	/*"color" is in check, must test for checkMate	*/
	else if (attacker != NULL) /*previous: state == 1*/
	{
		printf("found attacker, moving on to 3.1-3.3\n");
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
					if (Board.board[i][j]->type == 'k' && Board.board[i][j]->color == color)
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
					
		printf("found king. setting attacker coordinates \n");		
		
		xAttacker = attacker->Xpos;
		yAttacker = attacker->Ypos;
		
		/*handle which AliveList to traverse to kill attacker's move*/
		if (color == 0) /*white;*/
			currentAEntry = white->First;
		else if (color == 1) /*black*/
			currentAEntry = black->First;
		printf("found color of defender color, now traverse ALIST \n");
		
		while (currentAEntry) /*traverse thru the list until EndOfList*/
		{
			switch(currentAEntry->AlivePiece->type) /*Case is what type of piece we have for List {Q, B, R, N, P}. no king*/
			{
				case ('Q'):
				{
					printf("found alive queen. calling QLMLG \n");
					possibleMoves = QueenLegalMoveListGen(currentAEntry->AlivePiece, Board);
					printf("done withth QLMLG \n");
					break;
				}
				case ('B'):
				{
					printf(" found alive bishop, calling listgen\n");
					possibleMoves = BishopLegalMoveListGen(currentAEntry->AlivePiece, Board);
					printf("done with bishop listgen \n");
					break;
				}
				case ('R'):
				{
					printf("found alive Rook. calling listgen \n");
					possibleMoves = RookLegalMoveListGen(currentAEntry->AlivePiece, Board);
					printf("done with rook list gen \n");
					break;
				}
				case ('N'):
				{
					printf("found alive knight. calling listgen \n");
					possibleMoves = KnightLegalMoveListGen(currentAEntry->AlivePiece, Board);
					printf("done with knight listgen \n");
					break;
				}
				case ('P'):
				{
					printf("found alive pawn. calling listgen \n");
					possibleMoves = PawnLegalMoveListGen(currentAEntry->AlivePiece, Board);
					printf("done with knight listgen \n");
					break;
				}
			} /*end switch, we have a piece and the MLIST. traverse MLIST until if x/yAttackr is found*/
			
			/*Traverse thru the generatedMoveList and find a match for finX == xattacker, and for Y.*/
			if(possibleMoves->Length != 0)
			{
				printf("listlength !=0, traversing list to find move \n");
				currentMEntry = possibleMoves->First;
				
				while(currentMEntry)
				{
					currentMove = currentMEntry->PotentialMove;
					
					if((currentMove->finX == xAttacker) && (currentMove->finY == yAttacker)) /*compare final coord*/
					{
						printf("found piece to kill attacker. return 1 \n");
						return 1; /*we can kill the attacker, thus only in check and return 1;*/
					}
					currentMEntry = currentMEntry->Next;
				} /*end while loop of currentPiece Moves*/
				
			}
			printf("current piece has no kill move against king attacker. delete possiblemoves \n");
			 
			DeleteMoveList(possibleMoves); /*delete possibleMoves so we can create a new list for next Alive.*/
			
			printf("deleted possible moves. now setting next entry \n");
			
			currentAEntry = currentAEntry->Next;
			
		} /*end of aliveListMoves. If we reach this point, no color player can attack 1-color attacker.*/
		
		printf("done with 3.1, now to find a king move instead \n");
		
		/*3.2*/
		/*generate legal moves for king to check for */
		king = Board.board[xKing][yKing];
		possibleMoves = KingLegalMoveListGen(king, Board);
		currentMEntry = possibleMoves->First;
		
		printf("3.2 assignments done, if listlength != 0, test moves \n");
		if (possibleMoves->Length != 0) /*if length == 0 then no mech legal move for king, so just skip the code and try to block*/
		{
			while(currentMEntry)
			{
				printf("for each possible move, we need to fill tempboard and call movepiece on it \n");
				/*fill the temp board*/
				for(int i = 0; i < 8; i++)
				{
					for(int j = 0; j < 8; j++)
					{
						tempBoard.board[i][j] = Board.board[i][j];
					}	
				}
			
				MovePiece(currentMEntry->PotentialMove, &tempBoard, 0, white, black);
				printf("movepiece on tempboard for king potential . calling testchecklegal\n");
				state = TestCheckLegal(tempBoard, color);
				printf("found the state from testchecklegal. \n");
				
				if(state == 0)
				{
					printf("state ==0, so we return 1 \n");
					return 1;
				}
				
				currentMEntry = currentMEntry->Next;
				printf("state != 0 so we need to find next move entry \n");
			}
		}
		printf(" no moves for king. calling deletemovelist then on to 3.3\n");
		
		DeleteMoveList(possibleMoves);
		printf("deleted movelist for king \n");
		
		/*if we reach this point, king cannot move away from attack. must block.*/
		
		if(attacker->type == 'N')
		{
			printf("attacker is a knight. return 2 \n");
			return 2;
		}
		else
		{
			printf(" attacker not knight. init 3.3\n");
			int xDifference, yDifference;
			xDifference = xKing - xAttacker;
			yDifference = yKing - yAttacker;
			int i, j;
			PIECE *potentialBlocker = NULL;

			/*1*/
			if(xDifference == 0 && yDifference > 0)
			{
				printf("case 1 xdiff is 0, y diff is +\n");
				i = xKing;
				for(j = yKing - 1; j > yAttacker; j--)
				{
					printf("calling tclb \n");
					potentialBlocker = TestCheckLegalBlocker(Board, color, i, j);
					printf("tclb complete\n");
					if(potentialBlocker != NULL)
					{
						printf("found blocker. return1 \n");
						return 1;
					}
				}
			}

			/*2*/
			else if(xDifference == 0 && yDifference < 0)
			{
			
				printf("case 2 xdiff is 0, y diff is -\n");
				i = xKing;
				for(j = yKing + 1; j < yAttacker; j++)
				{
					printf("calling tclb \n");
					potentialBlocker = TestCheckLegalBlocker(Board, color, i, j);
					printf("tclb complete\n");
					if(potentialBlocker != NULL)
						return 1;
				}
			}

			/*3*/
			else if(xDifference > 0 && yDifference == 0)
			{
				printf("case 3 xdiff is +, y diff is 0\n");
				j = yKing;
				for(i = xKing - 1; i > xAttacker; i--)
				{
					printf("calling tclb \n");
					potentialBlocker = TestCheckLegalBlocker(Board, color, i, j);
					printf("tclb complete\n");
					if(potentialBlocker != NULL)
					{
						printf("found blocker. return1 \n");
						return 1;
					}
				}
			}

			/*4*/
			else if(xDifference < 0 && yDifference == 0)
			{
				printf("case 4 xdiff is -, y diff is 0\n");
				j = yKing;
				for(i = xKing + 1; i < xAttacker; i++)
				{
					printf("calling tclb \n");
					potentialBlocker = TestCheckLegalBlocker(Board, color, i, j);
					printf("tclb complete\n");
					if(potentialBlocker != NULL)
					{
						printf("found blocker. return1 \n");
						return 1;
					}
				}
			}

			/*5*/
			else if(xDifference < 0 && yDifference > 0)
			{
				printf("case 5 xdiff is -, y diff is +\n");
				i = xKing + 1;
				for(j = yKing - 1; j > yAttacker; j--, i++)
				{
					printf("calling tclb \n");
					potentialBlocker = TestCheckLegalBlocker(Board, color, i, j);
					printf("tclb complete\n");
					if(potentialBlocker != NULL)
					{
						printf("found blocker. return1 \n");
						return 1;
					}
				}

			}

			/*6*/
			else if(xDifference > 0 && yDifference < 0)
			{
				printf("case 6 xdiff is +, y diff is -\n");
				i = xKing - 1;
				for(j = yKing + 1; j < yAttacker; j++, i--)
				{
					printf("calling tclb \n");
					potentialBlocker = TestCheckLegalBlocker(Board, color, i, j);
					printf("tclb complete\n");
					if(potentialBlocker != NULL)
					{
						printf("found blocker. return1 \n");
						return 1;
					}
				}
			}

			/*7*/
			else if(xDifference > 0 && yDifference > 0)
			{
				printf("case7 xdiff is +, y diff is +\n");
				i = xKing - 1;
				for(j = yKing - 1; j > yAttacker; j--, i--)
				{
					printf("calling tclb \n");
					potentialBlocker = TestCheckLegalBlocker(Board, color, i, j);
					printf("tclb complete\n");
					if(potentialBlocker != NULL)
					{
						printf("found blocker. return1 \n");
						return 1;
					}
				}
			}

			/*8*/
			else if(xDifference < 0 && yDifference < 0)
			{
				printf("case8 xdiff is -, y diff is -\n");
				i = xKing + 1;
				for(j = yKing + 1; j < yAttacker; j++, i++)
				{
					printf("calling tclb \n");
					potentialBlocker = TestCheckLegalBlocker(Board, color, i, j);
					printf("tclb complete\n");
					if(potentialBlocker != NULL)
					{
						printf("found blocker. return1 \n");
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


	printf(" nothing do do. checkmate. game over. you suck. return 2\n");
	return 2;
}
