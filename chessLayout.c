#include "chessLayout.h"

	/*Load_Pieces function definition*/
THEBOARD InitializeBoard(void){

		/*initialize variables */
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;

		/*piece values*/
	int pawn = 1;
	int knight = 16;/* Note that the character used for the night is 'h'*/
	int rook = 25;
	int bishop = 25;
	int queen = 49;
	int king = 255;

		/*create our 2D array that will be the board*/
	THEBOARD chess_board;

		/*allocate space in memory for each member of the array*/
	for(i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++){
			chess_board.board[i][j] = (PIECE*)malloc(sizeof(PIECE));
		}
	}

		/*making each space NULL*/
	for(x = 0; x <= 7; x++ ){
       		 for(y = 0; y <= 7; y++){
			chess_board.board[x][y] = NULL;
        	}
	}

		/*assigning the pointers of the board to each piece*/
		/*top side pieces */
	for(y = 6; y < 8; y++){
		for(x = 0; x < 8; x++){
			
			if(y == 6){
				chess_board.board[x][y] = NewPiece('P', 1, pawn, x, y);
                	}
			
			else if(x == 0 && y == 7){
				chess_board.board[x][y] = NewPiece('R', 1, rook, x, y);
			}
			else if(x == 1 && y == 7){
				chess_board.board[x][y] = NewPiece('H', 1, bishop, x, y);
			}
			else if(x == 2 && y == 7){
				chess_board.board[x][y] = NewPiece('B', 1, knight, x, y);
			}
			else if(x == 3 && y == 7){
				chess_board.board[x][y] = NewPiece('Q', 1, king, x, y);
			}
			else if(x == 4 && y == 7){
				chess_board.board[x][y] = NewPiece('K', 1, queen, x, y);		
			}
			else if(x == 5 && y == 7){
				chess_board.board[x][y] = NewPiece('B', 1, knight, x, y);
			}
			else if(x == 6 && y == 7){
				 chess_board.board[x][y] = NewPiece('H', 1, bishop, x, y);
			}
			else if(x == 7 && y == 7){
				chess_board.board[x][y] = NewPiece('R', 1, rook, x, y);	
			}
		}

	}

		/*bottom side pieces*/
	for(y = 0; y < 2; y++){
		for(x = 0; x < 8; x++){
			if(y == 1){
				chess_board.board[x][y] = NewPiece('P', 0, pawn, x, y);			
			}
			else if(x == 0 && y == 0){
				chess_board.board[x][y] = NewPiece('R', 0, rook, x, y);
			}
			else if(x == 1 && y == 0){
				chess_board.board[x][y] = NewPiece('H', 0, bishop, x, y);
			}
			else if(x == 2 && y == 0){
				chess_board.board[x][y] = NewPiece('B', 0, knight, x, y);
			}
			else if(x == 3 && y == 0){
				chess_board.board[x][y] = NewPiece('Q', 0, queen, x, y);
			}
			else if(x == 4 && y == 0){
				chess_board.board[x][y] = NewPiece('K', 0, king, x, y);
			}
			else if(x == 5 && y == 0){
				chess_board.board[x][y] = NewPiece('B', 0, knight, x, y);
			}
			else if(x == 6 && y == 0){
        	 		chess_board.board[x][y] = NewPiece('H', 0, bishop, x, y);
			}
			else if(x == 7 && y == 0){
				chess_board.board[x][y] = NewPiece('R', 0, rook, x, y);
			}
		}

	}	
	
	

	return chess_board;
}

/*definition of board function*/
void PrintBoard(THEBOARD chess_board){
	int x = 0, y = 0;

        for(y = 7; y >= 0; y--){
                printf("%d ", y);
                for(x = 0; x < 8; x++){
                        if(chess_board.board[x][y] == NULL){
                                printf("|  |");
                        } else {
				if(chess_board.board[x][y]->color == 0)
				{
                                	printf("|w%c|", chess_board.board[x][y]->type );
				} else 
				{
					printf("|b%c|", chess_board.board[x][y]->type);
				}
                        }
                        if(x == 7){
                                printf("\n");
                        }
			

                }
        }
	
        printf("  ");
        for(x = 0; x < 8; x++){
                printf("  %d ", x);
        }
	printf("\n");
	printf("\n");
	printf("\n");

}

/*definition of DeletePiece*/
void DeleteBoard(THEBOARD *BoardtoDelete){
	int x;
	int y;

		/*free every piece*/
	for(x = 0; x < 8; x++){
		for(y = 0; y < 8; y++){
			if(BoardtoDelete->board[x][y])
			{
				DeletePiece(BoardtoDelete->board[x][y]);
			}
			BoardtoDelete->board[x][y] = NULL;
		}
	}
	free(BoardtoDelete);
}

/*defintion of creating piece*/
PIECE *NewPiece(char type, int color, int value, char Xpos, char Ypos){
	PIECE *p;
	p = (PIECE*)malloc(sizeof(PIECE));
	if(! p){
		perror("No more memory.");
		exit(10);
	}
	p->type = type;
	p->moveCount = 0;
	p->color = color;
	p->value = value;
	p->Xpos = Xpos;
	p->Ypos = Ypos;
	return p;
}


/*definition of deleting piece*/
void DeletePiece(PIECE *p){
	assert(p);
	free(p);
}

/*definition of printing piece */
void PrintPiece(PIECE *p){
	assert(p);
	printf("Piece type: %c \n", p->type);
	printf("Piece color: %d \n", p->color);
	printf("Piece value: %d \n", p->value);
	printf("Piece xpos: %d \n", p->Xpos);
	printf("Piece ypos: %d \n", p->Ypos);
}
