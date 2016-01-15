/************************************/
/* AI.c				    */
/* author: i9(team 9)		    */
/************************************/

#include <stdio.h>
#include "Rules.h"
#include <time.h>

int pCOLOR;

int MakeGoodChoices(int CBOARD[File][Rank]);
int EvalPos(int CBOARD[File][Rank],int startX,int startY,int endX,int endY);
void Random(int CBOARD[File][Rank]);

int MakeGoodChoices(int CBOARD[File][Rank]){
int max,score;
int i,j,i2,j2;
int currentbestX,currentbestY,nextbestX,nextbestY;

pCOLOR = WhiteOrBlackTurn;

if(pCOLOR %2 == 1)
	printf("computer is black \n");
else if (pCOLOR %2 == 0)
	printf("computer is white \n");





for (i = 1; i < File-1; i++) /*Loop through every square on board */
	for (j = 2; j < Rank-3; j++) {
		if (pCOLOR%2==0 && (CBOARD[i][j] > 0 && CBOARD[i][j] != 99) || pCOLOR%2==1 && CBOARD[i][j] < 0){ /*If square has your piece*/
			for (i2 = 1; i2 < File-1; i2++) /*Loop through every square on the board again*/
				for (j2 = 2; j2 < Rank-3; j2++) {
					switch (CBOARD[i][j]){ /*switch for what type of Piece you landed on in first loop*/
					case 20: case -20: case 21: case -21: /*I.e. if Pawn, check if its possible to move to square from second loop*/
						if( ValidPawnMove(CBOARD,i,j,i2,j2) ){
							score = EvalPos(CBOARD,i,j,i2,j2); /*If its valid give the move a score*/
							if(score > max){  /*If the score is the best we have so far set it to max and store the move*/
								max = score;
								currentbestX = i;
								currentbestY = j;
								nextbestX = i2;
								nextbestY = j2;
							}
						}
						break;
					case 3: case -3: /*Do the same for all of the Piece types*/
						if(ValidRookMove(CBOARD,i,j,i2,j2)){
							score = EvalPos(CBOARD,i,j,i2,j2);
							if(score > max){
								max = score;
								currentbestX = i;
								currentbestY = j;
								nextbestX = i2;
								nextbestY = j2;
							}
						}
						break;
					case 5: case -5:
						if(ValidKnightMove(CBOARD,i,j,i2,j2)){
							score = EvalPos(CBOARD,i,j,i2,j2);
							if(score > max){
								max = score;
								currentbestX = i;
								currentbestY = j;
								nextbestX = i2;
								nextbestY = j2;
							}
						}
						break;
					case 7: case -7:
						if(ValidBishopMove(CBOARD,i,j,i2,j2)){
							score = EvalPos(CBOARD,i,j,i2,j2);
							if(score > max){
								max = score;
								currentbestX = i;
								currentbestY = j;
								nextbestX = i2;
								nextbestY = j2;
							}
						}
						break;
					case 9: case -9:
						if(ValidQueenMove(CBOARD,i,j,i2,j2)){
							score = EvalPos(CBOARD,i,j,i2,j2);
							if(score > max){
								max = score;
								currentbestX = i;
								currentbestY = j;
								nextbestX = i2;
								nextbestY = j2;
							}
						}
						break;
					case 10: case -10:
						if(ValidKingMove(CBOARD,i,j,i2,j2)){
							score = EvalPos(CBOARD,i,j,i2,j2);
							if(score > max){
								max = score;
								currentbestX = i;
								currentbestY = j;
								nextbestX = i2;
								nextbestY = j2;
							}
						}
					
					}
				}			
		}
	}
		printf("x1 = %d y1 =%d\n", currentbestX, currentbestY);
		printf("x2 = %d y2 = %d\n", nextbestX, nextbestY);
		Move(CBOARD,currentbestX,currentbestY,nextbestX,nextbestY); /*Make the best move we found so far*/
/*	else
		{
			printf("Random is initiated\n");
			Random(CBOARD);
		} */
}


int EvalPos(int CBOARD[File][Rank], int startX, int startY, int endX, int endY){
	int i,j;
	int current_score=0;
	int possible_score=0;
	int DUMMY[File][Rank];
	
	pCOLOR = WhiteOrBlackTurn;
	for (i = 0; i < File; i++) /*Copy Current Board to DUMMY Board*/
		for(j = 0; j < Rank; j++){
			DUMMY[i][j] = CBOARD[i][j];
		}
	for (i = 0; i < File; i++) /*Run through Current Board and assign score to position based on Material*/
		for(j = 0; j < Rank; j++){
			if ((pCOLOR%2==0 && CBOARD[i][j] != 99) && CBOARD[i][j] != 0){
				switch(CBOARD[i][j]){
				
				case 20: case 21:
					current_score += 1;
					break;
				case -20: case -21:
					current_score -= 1;
					break;
				case 3:
					current_score += 5;
					break;
				case -3: 
					current_score -= 5;
					break;
				case 5: 
					current_score+= 3;
					break;
				case -5:
					current_score -= 3;
					break;
				case 7:
					current_score += 3;
					break;
				case -7:
					current_score -= 3;
					break;
				case 9:
					current_score += 9;
					break;
				case -9:
					current_score -= 9;
					break;
				case 10:
					current_score += 1000;
					break;
				case -10:
					current_score -= 1000;
					break;
				}	
			}	
		}

	Move(DUMMY,startX,startY,endX,endY); /*Make Hypothetical Move*/
	for (i = 0; i < File; i++) /*Run through Dummy Board which has Hypothetical Move and assign score to position based on Material*/
		for(j = 0; j < Rank; j++){
			if ((pCOLOR%2==1 && DUMMY[i][j] != 99) && DUMMY[i][j] != 0){
				switch(DUMMY[i][j]){
				
				case -20: case -21:
					possible_score += 1;
					break;
				case 20: case 21:
					possible_score -= 1;
					break;
				case -3:
					possible_score += 5;
					break;
				case 3:
					possible_score -= 5;
					break;
				case -5: 
					possible_score += 3;
					break;
				case 5: 
					possible_score -= 3;
					break;
				case -7:
					possible_score += 3;
					break;
				case 7:
					possible_score -= 3;
					break;
				case -9:
					possible_score += 9;
					break;
				case 9:
					possible_score -= 9;
					break;
				case -10:
					possible_score += 1000;
					break;
				case 10:
					possible_score -= 1000;
					break;
				}	
			}
		}
	return possible_score - current_score;/*return the best difference between our score and the opponents.*/	
}


void Random(int CBOARD[File][Rank])
{
	int x, y, x1, y1, x2, y2;
	int random;
	int counter = 0;
	static int count = 0;

	pCOLOR = WhiteOrBlackTurn;
	printf("\nWithin Random Move Loop\n");

	while(1)
	{
	
		if (pCOLOR % 2 == 0 && wPlayer == Computer)
			{
			x2 ==0;
			if (count == 0) /*first move*/
				{
				if(ValidPawnMove(CBOARD,5,8,5,6))
					{
					Move(CBOARD,5,8,5,6);
					count++;
					return;
					}
				else 
					{
					count = 5;					

					}
				}			
			else if (count == 1)
				{
				if(ValidBishopMove(CBOARD,6,9,3,6))
					{
				Move(CBOARD,6,9,3,6);
				count++;
				return;
					}
				else
					{
					count = 4;
					}
				}
			else if (count == 2)
				{
				if(ValidQueenMove(CBOARD,4,9,6,7))
					{
				Move(CBOARD,4,9,6,7);
				count++;
				return;
					}
				else
					{
					count = 4;
					}
				}
			else if (count == 3)
				{
				if(ValidQueenMove(CBOARD,6,7,6,3))
					{
				Move(CBOARD,6,7,6,3);
				count++;
				return;
					}
				else
					{
					count = 4;
					}
				}
			else if (count == 4)
				{
				if(ValidKnightMove(CBOARD,7,9,8,7))
					{
					Move(CBOARD,7,9,8,7);
					count++;
					return;
					}
				else
					{
					count = 5;
					}
				}
			else if (count == 5)
				{
				if(ValidKnightMove(CBOARD,8,7,7,9))
					{
					Move(CBOARD,8,7,7,9);
					count--;
					return;
					}
				}
			else
				{

				printf("WHITE AI GIVES UP D; \n");
				return;
				}
			
			}
			

		if (pCOLOR % 2 == 1 && bPlayer == Computer)
			{
			/*x2 = 0;
			random = (rand()%9+1) * (rand()%3+1) +2;

			while (random >=2)
			{
			for (x = 2; x <File-2; x++)
				for (y = 1; y < Rank-1; y++)
					{
					if (CBOARD[x][y] <0)
						{
						random--;
						if (random <= 2)
							{
							printf("%d this is CBOARD\n", CBOARD[x][y]);
							x1 = x;
							y1 = y;
							x = File -2;
							y = Rank -1;
							x2 == 5;
							break;
							}
						}
					}
			
			if (x2 == 5)
				break;
			}
			
			printf("did we make it?\n");
			*/
			
			for(x = 2; x < File-2; x++)
				for(y = 1; y < Rank - 1; y++)
					{
					if (CBOARD[x][y] < 0)
						counter++;
					}			
			random = rand()%counter;	
			counter = 0;
			
			
			for(x = 2; x < File-2; x++)
				for(y = 1; y < Rank - 1; y++)
					{
					if (counter == random && CBOARD[x][y] < 0)
						{
						x1 = x;
						y1 = y;
						break;
						}
					if (CBOARD[x][y] < 0)
						{
						counter++;
						}
					}

			for (x = 2; x < File-2; x++)
				for (y = 1; y < Rank-1; y++)
					{
					if (CBOARD[x][y] == 99)
						continue;
					else if (CBOARD[x][y] < 0)
						continue;
					else
					switch(CBOARD[x1][y1])
					{
						case -20: case -21:
						if(ValidPawnMove(CBOARD,x1,y1,x,y))
							{
							if(!(Move(CBOARD,x1,y1,x,y)))
								break;
							else
							return;
							}
						break;
						case -3:
						if(ValidRookMove(CBOARD,x1,y1,x,y))
							{
							if(!(Move(CBOARD,x1,y1,x,y)))
								break;
							else
							return;
							}
						break;
						case -5:
						if(ValidKnightMove(CBOARD,x1,y1,x,y))
							{
							if(!(Move(CBOARD,x1,y1,x,y)))
								break;
							else
							return;
							}
						break;
						case -7:
						if(ValidBishopMove(CBOARD,x1,y1,x,y))
							{
							if(!(Move(CBOARD,x1,y1,x,y)))
								break;
							else
							return;
							}
						break;
						case -9:
						if(ValidQueenMove(CBOARD,x1,y1,x,y))
							{
							if(!(Move(CBOARD,x1,y1,x,y)))
								break;
							else
							return;
							}
						break;
						case -10:
						if(ValidKingMove(CBOARD,x1,y1,x,y))
							{
							if(!(Move(CBOARD,x1,y1,x,y)))
								break;
							else
							return;
							}
					}
					}
			}
	}



}
