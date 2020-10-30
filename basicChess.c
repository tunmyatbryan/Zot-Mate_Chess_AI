/*working ascii symbol board*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "chessLayout.h"
#include "move.h"


int main(void){
        int gameType;
        int player1;
        int player2;

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
        
                printf("CHOOSE YOUR COLOR:\n0. WHITE\n1. BLACK\n");
                printf("YOUR OPTION(type \"0\" or \"1\"): ");
                scanf("%d", &player1);
                player2 = 1 - player1;

                if(player1 == '1'){
                        printf("Player1 is BLACK\n");
                        printf("Player2 is WHITE\n");
                }
                else {
                        printf("Player1 is WHITE\n");
                        printf("Player2 is BLACK\n");
                }
	
		printf("\n");
                printf("\n");
                printf("\n");
			
		status = InitializeBoard();
		PrintBoard(status);

		int esc = 1;
		int iX,iY,fX,fY;
		PIECE *DesiredMove;

		while(esc == 1)
		{
			printf("Enter initial X:");
			scanf("%d", &iX);
			printf("Enter initial Y: ");
			scanf ("%d", &iY);
			DesiredMove = status.board[iX][iY];
			printf("Enter final X: ");
			scanf("%d", &fX);
			printf("Enter final Y: ");
			scanf("%d", &fY);
			status.board[fX][fY] = DesiredMove;
			status.board[iX][iY] = NULL;
			DesiredMove = NULL;
			PrintBoard(status);
			printf("exit?");
			scanf("%d", &esc);

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
/*board function definition*/
/*
#include <stdio.h>
#include <stdlib.h>
int main(void){
int x, y;


for(x = 7; x >= 6; x--){
        for(y = 0; y <= 7; y++){
                if(x == 6 && y == 0){
                        printf("A1 ");
                }

                if(x == 6){
                        printf("P ");
                }

                else if(y == 0 && x == 7){
                        printf("A0 R ");
                }
                else if(y == 1 && x == 7){
                        printf("D ");
                }
                else if(y == 2 && x == 7){
                        printf("H ");
                }
                else if(y == 3 && x == 7){
                        printf("K ");
                }
                else if(y == 4 && x == 7){
                        printf("Q ");
                }
		 else if(y == 5 && x == 7){
                        printf("H ");
                        }
                else if(y == 6 && x == 7){
                        printf("B ");
                }
                else if(y == 7 && x == 7){
                        printf("R ");
                        printf("\n");
                }
        }

}

printf("\t\tPLAYER 2  PIECES\n");

printf("A2 \n");
printf("A3 \n");
printf("A4 \n");
printf("A5 \n");

for(x = 1; x >= 0; x--){
        for(y = 0; y <= 7; y++){
                if(x == 1 && y == 0){
                        printf("A6 ");
                }
                if(x == 1){
                        printf("P ");
                        if(y == 7){
                        printf("\n");
                        }
                }
		
		else if(y == 0 && x == 0){
                        printf("A7 R ");
                }
                else if(y == 1 && x == 0){
                        printf("B ");
                }
                else if(y == 2 && x == 0){
                        printf("H ");
                }
                else if(y == 3 && x == 0){
                        printf("Q ");
                }
                else if(y == 4 && x == 0){
                        printf("K ");
                }
                else if(y == 5 && x == 0){
                        printf("H ");
                }
                else if(y == 6 && x == 0){
                        printf("B ");
                }
                else if(y == 7 && x == 0){
                        printf("R ");
                }
        }

}

printf("\t\tPLAYER 1 PIECES\n");

printf("   ");
for(x = 7; x >=0; x--){
        printf("B%d", x);
}
return 0;
}	
*/
