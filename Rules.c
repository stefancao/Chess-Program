/************************************************************************/
/***** RULES MODULE : source code for testing validity of moves *********/
/* authors: i9(Team 9)							*/		
/* rewrote ValidKnightMove 						*/
/* rewrote ValidBishopMove 						*/
/* rewrote ValidQueenMove 						*/
/* Added En Passant							*/
/* Added Call to En Passant in ValidPawnMove 				*/
/************************************************************************/

#include "Rules.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*safe function verifies if the king is or not; return 0 if the king is being threaten*/
int safe(int CBOARD[10][12], int SquareX, int SquareY, int white_or_black)
{
    int x, y;
    if (white_or_black == 1)
	{
        for (y = 0; y < 12; y++) 
		{
            for (x = 0; x < 10; x++)
			{
                if (CBOARD[x][y] < 0) 
				{
                    switch (CBOARD[x][y]) 
					{
                        case -2: /* check for pawn */
                        {
                            if (ValidPawnMove(CBOARD, x, y, SquareX, SquareY))
                            {
                                return 0;
                            }
                            break;
                        }
                        case -3:
                        {
                            if (ValidRookMove(CBOARD, x, y, SquareX, SquareY)) {
                                return 0;
                            }
                            break;
                        }
                        case -5:
                        {
                            if (ValidKnightMove(CBOARD, x, y, SquareX, SquareY))
                            {
                                return 0;
                            }
                            break;
                        }
                        case -7:
                        {
                            if (ValidBishopMove(CBOARD, x, y, SquareX, SquareY))
                            {
                                return 0;
                            }
                            break;
                        }
                        case -9:
                        {
                            if (ValidQueenMove(CBOARD, x, y, SquareX, SquareY))
                            {
                                return 0;
                            }
                            break;
                        }
                        default:
                        {
                            break;
                        }
                            
					} /*hctiws*/
				} /*fi*/
			} /* rof */
		} /* rof */
	} /* outer if */
    else
    {
        for (y = 0; y < 12; y++) 
		{
            for (x = 0; x < 10; x++) 
			{
                if (CBOARD[x][y] > 0) 
				{
                    switch (CBOARD[x][y]) 
					{
                        case 2: /* check for pawn */
                        {
                            if (ValidPawnMove(CBOARD, x, y, SquareX, SquareY))
                            {
                                return 0;
                            }
                            
                            break;
                        }
                        case 3:
                        {
                            if (ValidRookMove(CBOARD, x, y, SquareX, SquareY)) {
                                return 0;
                            }
                            
                            break;
                        }
                        case 5:
                        {
                            if (ValidKnightMove(CBOARD, x, y, SquareX, SquareY))
                            {
                                return 0;
                            }
                            
                            break;
                        }
                        case 7:
                        {
                            if (ValidBishopMove(CBOARD, x, y, SquareX, SquareY))
                            {
                                return 0;
                            }
                            
                            break;
                        }
                        case 9:
                        {
                            if (ValidQueenMove(CBOARD, x, y, SquareX, SquareY))
                            {
                                return 0;
                            }
                           
                            break;
                        }
                        default:
                        {
                            break;
                        }
                            
					} /*hctiws */
				} /*fi*/
			} /*rof*/
		} /*rof*/
	} /*esle*/
    return 1;
} /*EOF safe*/

int ValidRookMove(int CBOARD[10][12], int startX, int startY, int endX, int endY)
{
        int white = (CBOARD[startX][startY] > 0) ? 3: -3;
        int vert_d = (startY-endY > 0)? -1:1;
        int hor_d = (startX-endX> 0) ? -1:1;
        if((white == 3 && CBOARD[endX][endY]> 0) || (white == -3 && (CBOARD[endX][endY]<0 || CBOARD[endX][endY]==99)))
                return 0;
		if (startX - endX == 0){ /*If we are moving vertically*/
			for (startY = startY + vert_d; startY != endY; startY = startY + vert_d){
			/*	printf("vert-spot is %d\n", CBOARD[startX][startY]);*/
				if (CBOARD[startX][startY]){ /*check if we hit anything*/
					return 0;
				}
			}
		}
        else if (startY - endY == 0){ /*if we are moving vertically*/
                for (startX=startX+hor_d; startX != endX; startX=startX+hor_d){
/*printf("hori-spot is %d\n", CBOARD[startX][startY]);*/
                        if(CBOARD[startX][startY]) /*check if we hit anything*/
                                return 0;
			}
                }
      
        else
                return 0;
return 1;
}


/*Checks if Castling is valid */
int CanICastle(int CBOARD[File][Rank], int startX, int startY, int endX, int endY)
{
	assert(CBOARD);
	assert(startX);
	assert(startY);
	assert(endX);
	assert(endY);
	assert(CBOARD[startX][startY] == 10 || CBOARD[startX][startY] == -10);
	int white = (CBOARD[startX][startY] > 0) ? 1: 0;
	
	if((white && CBOARD[endX][endY] != 3) || (white == 0 && CBOARD[endX][endY] != -3)) /*Check Rook position for right type and color */
		return 0;
	if((white && HasWKingMoved != 0) || (white == 0 && HasBKingMoved != 0))/*If King Has Moved*/
		return 0;
	if(endX == 1 && endY == 2 && HasRook1Moved == 1) /*Check to see if corresponding rook has moved before*/
		return 0;
	else if (endX == 7 && endY == 2 && HasRook2Moved == 1)
		return 0;
	else if (endX == 1 && endY == 9 && HasRook3Moved == 1)
		return 0;
	else if (endX == 7 && endY == 9 && HasRook4Moved == 1)
		return 0;
  
	if(startX - endX> 0) /*Make sure there are no pieces between King and Rook */
		for (startX;startX = 1;startX--) {
			if (CBOARD[startX][startY] != 0)
				return 0;
		}
	else if(startX - endX < 0)
		for(startX;startX = 8; startX++) {
			if (CBOARD[startX][startY] != 0)
				return 0;
		} 
	return 1;
}



/* knight can jump over the pieces of two squuares horizontally or vertically, then move one space perpendicular ot those two squares to make an "L" shape */
int ValidKnightMove(int CBOARD[File][Rank], int startX, int startY, int endX, int endY)
{

/* but both colors have the same rules */
	if((CBOARD[startX][startY] == 5 && CBOARD[endX][endY]>0) || (CBOARD[startX][startY] == -5 && (CBOARD[endX][endY]<0 || CBOARD[endX][endY] == 99)))
                 return 0;

	if (CBOARD[endX][endY] == 99)
			return 0;
	else if((startX+2 == endX) && (startY-1 == endY)){
		return 1;}
	else if((startX-1 == endX) && (startY-2 == endY)){
		return 1;}
	else if((startX+1 == endX) && (startY-2 == endY)){
		return 1;}
	else if((startX-2 == endX) && (startY-1 == endY)){
		return 1;}
	else if((startX+2 == endX) && (startY+1 == endY)){
		return 1;}
	else if((startX+1 == endX) && (startY+2 == endY)){
		return 1;}
	else if((startX-2 == endX) && (startY+1 == endY)){
		return 1;}
	else if((startX-1 == endX) && (startY+2 == endY)){
		return 1;}
	else
		return 0;
} /* EOF moveknight*/

int ValidBishopMove(int CBOARD[File][Rank], int xi, int yi, int xf, int yf)
{
	int cases; /* keep in track of which slope case we are referring to*/
	double slope; /* slope of the diagonal that the bishop can move to*/
	int white = (CBOARD[xi][yi] > 0) ? 7 : -7;

	if (yf - yi == 0)
		return 0; /* making sure we dont get a 0 for denominator will crash program*/
	else
		slope = fabs((double)(xf - xi) / (yf - yi)); /*calculates abosulute value*/


	if ((white == 7 && CBOARD[xf][yf] > 0) || (white == -7 && (CBOARD[xf][yf] < 0|| CBOARD[xf][yf] == 99)))
	{

		return 0;
	}

	if (slope == 1.0) /*to varify that the slope not +1 or -1*/
	{
		
		if (xf > xi) /*running thru the right side of the initial coordinates*/
		{
			if (yf > yi) /* running thru the bottom right slope*/
			{
				cases = 4;
			}
			else if (yf < yi) /* running thru the upper right slope*/
			{
				cases = 3;
			}
		}
		else if (xf < xi) /* running thru the left side of the initial coordinates*/
		{
			if (yf > yi) /* running thru the bottom left slope*/
			{
				cases = 2;
			}
			else if (yf < yi) /* running thru the upper slope*/
			{
				
				cases = 1;
			}
		} /*EOF esle fi*/

		int counter = abs(xf - xi);
		
		int i;
		switch (cases)
		{
		case 4: /* bottom right slope*/
		{
			for (i = 1; i < counter; i++)
			{
				
				if (CBOARD[xi + i][yi + i] != 0)
				{
					
					return 0;
				}
			}
			break;
		}
		case 3: /* upper right slope*/
		{
			for (i = 1; i < counter; i++)
			{
				
				if (CBOARD[xi + i][yi - i] != 0)
				{
					
					return 0;
				}
			}
			break;
		}
		case 2: /* bottom left slope*/
		{
			for (i = 1; i < counter; i++)
			{
				
				if (CBOARD[xi - i][yi + i] != 0)
				{
					
					return 0;
				}
			}
			break;
		}
		case 1: /* upper left slope*/
		{
			for (i = 1; i < counter; i++)
			{
				
				if (CBOARD[xi - i][yi - i] != 0)
				{
					
					return 0;
				}
			}

			break;
		}
		} /*hctiws*/

		return 1;
	} /* fi */
	else
	{
		
		return 0;
	} /* EOF esle i*/
} /*EOF BISHOP*/







/* queen can move diagonally and horizontally and vertically as far as it wants until its path is blocked */
int ValidQueenMove(int CBOARD[File][Rank], int startX, int startY, int endX, int endY)
{
	if(ValidRookMove(CBOARD,startX,startY,endX,endY) ^ ValidBishopMove(CBOARD,startX,startY,endX,endY))
		return 1;
	else
		return 0;
} /* EOF movequeen*/

int ValidKingMove(int CBOARD[File][Rank], int startX, int startY, int endX, int endY){	
	int white = (CBOARD[startX][startY] > 0) ? 1:0;

	if ((safe(CBOARD, endX, endY, white)) == 0)
	{	
		
		return 0;
	}
	if (CBOARD[endX][endY]==99)
		return 0;
	else if(white && CBOARD[endX][endY] > 0 || white == 0 && CBOARD[endX][endY] < 0)
		return 0;
	else if(white && HasWKingMoved == 0 && startY == 9 && (endX == startX + 2 || endX == startX -2))
		return CanICastle(CBOARD,startX,startY,endX,endY);
	else if(white ==0 && HasBKingMoved == 0 && startY == 2 && (endX == startX +2 || endX == startX -2))
		return CanICastle(CBOARD,startX,startY,endX,endY);
	else if((endX == startX || endX == startX + 1 || endX == startX -1) && (endY == startY || endY == startY -1 || endY == startY +1))
		return 1;
	
	/* NEED TO CHECK FOR CHECKS OR CHECKMATE */

}

/* Possible moves for Pawn */
int ValidPawnMove(int CBOARD[File][Rank], int startX, int startY, int endX, int endY){
	if(CBOARD[startX][startY] == 20 || CBOARD[startX][startY] == 21){ 	/* white pawn */
		if(startY == 8){	/* if starting position, can move twice */
			if(endX == startX && (endY == (startY-1) || endY == (startY-2)) && CBOARD[endX][endY] == 0){	/* if click to move up once/twice and no piece there */
				if(endY == startY-2){
					if(CBOARD[startX][startY-1])
						return 0;
					CBOARD[startX][startY] = 21;
				}
				return 1;
			} 
			else if(((endX == startX-1 && endY == startY-1)||(endX == startX+1 && endY == startY-1)) && (CBOARD[endX][endY] < 0)){ 	/* if move diagonal-up to capture */
					return 1;
			}
			else{		/* else not up once/twice/capture, dont move */
				return 0;
			}
		}
		else{		/* else not starting position */
			if(endX == startX && (endY == (startY-1)) && CBOARD[endX][endY] == 0){	/*if click to move up once and no piece there*/
				return 1;
			}
			else if(((endX == startX-1 && endY == startY-1)||(endX == startX+1 && endY == startY-1)) && CBOARD[endX][endY] < 0){ 	/* if move diagonal-up to capture */
				return 1;
			}
			else if((CBOARD[endX][endY+1] == -21) && (endY-1 == 3)){		/*en Passant*/
				CBOARD[endX][endY+1] = 0;
				return 1;
			}
			else{		/* else not up once/capture, dont move */
				return 0;
			}
		}
	}
	else{		/* black pawn */
		if(startY == 3){		/* if starting position, can move twice */
			if(endX == startX && (endY == (startY+1) || endY == (startY+2)) && CBOARD[endX][endY] == 0){	/* if click to move down once/twice and no piece there */
				if(endY == startY+2)
					CBOARD[startX][startY] = -21;
				return 1;
			}
			else if(((endX == startX-1 && endY == startY+1)||(endX == startX+1 && endY == startY+1)) && CBOARD[endX][endY] > 0 && (CBOARD[endX][endY] != 99)){ 	/* if move diagonal-down and there's a black piece */
				return 1;
			}
			else{		/* else not down once/twice/capture, dont move */
				return 0;
			}
		}
		else{		/* else not starting position */
			if(endX == startX && (endY == (startY+1)) && CBOARD[endX][endY] == 0){		/*if click to move down once and no piece there*/
				return 1;
			}
			else if(((endX == startX-1 && endY == startY+1)||(endX == startX+1 && endY == startY+1)) && CBOARD[endX][endY] > 0 && (CBOARD[endX][endY] != 99)){ 	/* if move diagonal-down and there's a black piece */
				return 1;
			}
			else if((CBOARD[endX][endY-1] ==  21) && (endY+1 == 8)){		/*en Passant*/
				CBOARD[endX][endY-1] = 0;
				return 1;
			}	
			else{		/* else not down once/capture, dont move */
				return 0;
			}
		}		
	}
} /* EOF ValidPawnMove */

/* Promotes Pawn after having moved to its 8th rank*/
void PawnPromotion(int CBOARD[File][Rank], int startX, int startY){
	int promote;
	if((CBOARD[startX][startY] == 20)||(CBOARD[startX][startY]==21)){	/*white pawn*/
		if(startY == 2){
			while(1){
				printf("To promote to QUEEN type in 9,\n");
				printf("to promote to KNIGHT type in 5, \n");
				printf("to promote to BISHOP type in 7, \n");
				printf("to promote to ROOK type in 3: ");
				scanf(" %d", &promote);
				if(promote == 9 || promote == 5 || promote == 7 || promote == 3){
					break;
				}
				printf("Invalid input, please try again.\n");
			}
			CBOARD[startX][startY] = promote;
		}
	}
	else{		/*black pawn*/
		if(startY == 9){
			while(1){
				printf("To promote to QUEEN type in -9,\n");
				printf("to promote to KNIGHT type in -5, \n");
				printf("to promote to BISHOP type in -7, \n");
				printf("to promote to ROOK type in -3: ");
				scanf(" %d", &promote);
                                if(promote == -9 || promote == -5 || promote == -7 || promote == -3){
                                        break;
                                }
                                printf("Invalid input, please try again.\n");
			}
			CBOARD[startX][startY] = promote;
		}		
	}
} /* EOF PawnPromotion */






int Move(int Cboard[10][12], int x1, int y1, int x2, int y2){

int it_moved = 1;	/*it_moved = 0 - it can't move; = 1 - it moved; = 2 - it captured*/
/*printf("Inside Move it_moved is %d\n", it_moved);*/
int whichpiece = Cboard[x1][y1];
/*printf("which piece is %d\n", whichpiece);*/


switch(whichpiece)
{

	case 20: case -20: case 21: case -21:
		if(ValidPawnMove(Cboard, x1, y1, x2, y2) == 1){
			
			/*checks if first move, and pawn will double move, updates board with the info*/
			if(Cboard[x1][y1] >0 && y1 == 9 && y2 == y1-2)
				Cboard[x1][y1] += 1;
			else if(Cboard[x1][y1] <0 && y1 == 2 && y2 == y1+2)
				Cboard[x1][y1] += -1;
			
			/*check if capture, move the piece*/
			if(Cboard[x2][y2] != 0){

			Capture(Cboard, x1, y1, x2, y2);
			it_moved = 2;
			}
			
			else{
				Cboard[x2][y2] = Cboard[x1][y1];
				Cboard[x1][y1] = 0;
			}
			
			if((y2 = 2) || (y2 = 9)){
				PawnPromotion(Cboard, x2, y2);
			}
		
		}
		
		else{
		printf("Not a valid move\n");
		it_moved = 0;
		}
		break;
	
	case 3: case -3:
		if(ValidRookMove(Cboard, x1, y1, x2, y2) == 1){
		
			/*check if capture, move the piece*/
			if(Cboard[x2][y2] != 0){

			Capture(Cboard, x1, y1, x2, y2);
			it_moved = 2;
			}
			
			else{
				Cboard[x2][y2] = Cboard[x1][y1];
				Cboard[x1][y1] = 0;
			}
			
			/*top left rook*/
			if((x1 = 1) && (y1 = 2)){
				HasRook1Moved = 1;
			}
			
			/*top right rook*/
			else if((x1 = 8) && (y1 = 2)){
				HasRook2Moved = 1;
			}
			
			/*bottom left rook*/
			else if((x1 = 1) && (y1 = 9)){
				HasRook3Moved = 1;
			}
			
			/*bottom right rook*/
			else if((x1 = 8) && (y1 = 9)){
				HasRook4Moved = 1;
			}
		
		}
		
		else{
		printf("Not a valid move\n");
		it_moved = 0;
		}
		break;
	
	case 5: case -5:
		if(ValidKnightMove(Cboard, x1, y1, x2, y2) == 1){
		
			/*check if capture, move the piece*/
			if(Cboard[x2][y2] != 0){

			Capture(Cboard, x1, y1, x2, y2);
			it_moved = 2;
			}
			
			else{
				Cboard[x2][y2] = Cboard[x1][y1];
				Cboard[x1][y1] = 0;
			}
		
		}
		
		else{
		printf("Not a valid move\n");
		it_moved = 0;
		}
		break;
		
	case 7: case -7:
		if(ValidBishopMove(Cboard, x1, y1, x2, y2) == 1){
		
			/*check if capture, move the piece*/
			if(Cboard[x2][y2] != 0){

			Capture(Cboard, x1, y1, x2, y2);
			it_moved = 2;
			}
			
			else{
				Cboard[x2][y2] = Cboard[x1][y1];
				Cboard[x1][y1] = 0;
			}
		
		}
		
		else{
		printf("Not a valid move\n");
		it_moved = 0;
		}
		break;
		
	case 9: case -9:
		if(ValidQueenMove(Cboard, x1, y1, x2, y2) == 1){
		
			/*check if capture, move the piece*/
			if(Cboard[x2][y2] != 0){

			Capture(Cboard, x1, y1, x2, y2);
			it_moved = 2;
			}
			
			else{
				Cboard[x2][y2] = Cboard[x1][y1];
				Cboard[x1][y1] = 0;
			}
		
		}
		
		else{
		printf("Not a valid move\n");
		it_moved = 0;
		}
		break;
		
	case 10: case -10:
		if(ValidKingMove(Cboard, x1, y1, x2, y2) == 1){
		
			/*check if capture, move the piece*/
			if(Cboard[x2][y2] != 0){

			Capture(Cboard, x1, y1, x2, y2);
			it_moved = 2;
			}
			
			else{
				Cboard[x2][y2] = Cboard[x1][y1];
				Cboard[x1][y1] = 0;
			}
		
		}
		
		else{
		printf("Not a valid move\n");
		it_moved = 0;
		}
		
		/* check castling !!!STILL NEEDED!!!*/
		break;
		
	default :
		printf("No piece selected\n");
		it_moved = 0;

} /*end switch*/
	/* printf("it_moved end of Move = %d\n", it_moved);*/
	return it_moved;

/*if checkmate, print out You Win or You Lose, Start New Game or Quit */
}/*end move*/

void Capture(int Cboard[File][Rank], int x1, int y1, int x2, int y2){

	Cboard[x2][y2] = Cboard[x1][y1];
	Cboard[x1][y1] = 0;

}

/*checkmate funciton for king */
int checkmateking(int CBOARD[File][Rank], int xking, int yking)
	{
		if (CBOARD[xking][yking] == 10) /*white king*/
		{
			/*check if the WHITE KING's surroundings are available */
			if (ValidKingMove(CBOARD, xking, yking, (xking - 1), (yking - 1)) || ValidKingMove(CBOARD, xking, yking, (xking), (yking - 1)) || ValidKingMove(CBOARD, xking, yking, (xking + 1), (yking - 1)) || ValidKingMove(CBOARD, xking, yking, (xking - 1), (yking)) || ValidKingMove(CBOARD, xking, yking, (xking + 1), (yking)) || ValidKingMove(CBOARD, xking, yking, (xking - 1), (yking + 1)) || ValidKingMove(CBOARD, xking, yking, (xking), (yking + 1)) || ValidKingMove(CBOARD, xking, yking, (xking + 1), (yking + 1)))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		} /* EOF fi*/

		else if (CBOARD[xking][yking] == -10) /*black king*/
		{
			if (ValidKingMove(CBOARD, xking, yking, (xking - 1), (yking - 1)) || ValidKingMove(CBOARD, xking, yking, (xking), (yking - 1)) || ValidKingMove(CBOARD, xking, yking, (xking + 1), (yking - 1)) || ValidKingMove(CBOARD, xking, yking, (xking - 1), (yking)) || ValidKingMove(CBOARD, xking, yking, (xking + 1), (yking)) || ValidKingMove(CBOARD, xking, yking, (xking - 1), (yking + 1)) || ValidKingMove(CBOARD, xking, yking, (xking), (yking + 1)) || ValidKingMove(CBOARD, xking, yking, (xking + 1), (yking + 1)))
			{
				
				return 1;
			}
			else
			{
				return 0;
			}
		} /* EOF esle fi*/

	} /*EOF checkmate for kings*/
