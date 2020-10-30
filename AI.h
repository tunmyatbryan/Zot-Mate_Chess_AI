/*
 *
 *Header file for AI.h
 *
 * */

#ifndef AI_h
#define AI_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "chessLayout.h"
#include "Alive.h"
#include "move.h"
#include "Legal.h"
#include "Locomotion.h"
#include "Check.h"

//random numbe generator with no repeats
/*
	#include <time.h>
	
	srand(time(0));
	
	int u, v, repeat, randomNumber;
	int listLength = list->Length; //length for alive list, or legal list. used for mod op
	int arrayOfUsedNumbers[listLength];
	
	for(u = 0; u < listLength; u++)
	{
		repeat = 0;
		
		do
		{
			repeat = 0;
			randomNumber = rand() % listLength;
			
			//tranverse the populated array and test the Random Number
			for(v = 0; v < u; v++)
			{
				if (randomNumber == arrayOfUsedNumbers[v])
					repeat = 1;
			}
		} while (repeat);
		
		arrayofUsedNumbers[u] = randomNumber;
		
		//do something with random variable int randomNumber; 
				
	}
	
*/


MOVE *AIRandomMove(ALIST *alivelist, THEBOARD *board);

MOVE* RecursiveCall(MLIST *masterList, THEBOARD *Board);


#endif
