/**************************************************************/
/***** Rules.h: Header file for testing validity of rules *****/
/**************************************************************/

#ifndef RULES_H
#define RULES_H

#include <stdio.h>
#include "Constants.h"

/* FUNCTIONS */
/*safe function checks if the king's surrounding is safe or not; verify if the king is being threaten or not*/
int safe(int CBOARD[10][12], int SquareX, int SquareY, int white_or_black);

/* check for valid king move */
int ValidKingMove(int Cboard[File][Rank], int startX, int startY, int endX, int endY);

/* checks if Rook Move is valid */
int ValidRookMove(int CBOARD[File][Rank], int startX, int startY, int endX, int endY);

/* checks if Castling is valid */
int CanICastle (int CBOARD[File][Rank], int startX, int startY, int endX, int endY);

/* checks if Pawn Move is valid */
int ValidPawnMove(int CBOARD[File][Rank], int startX, int startY, int endX, int endY);

/* functions for Knightmoves*/
int ValidKnightMove(int CBOARD[File][Rank], int startX, int startY, int endX, int endY);

/*functions for BishopMoves*/

int ValidBishopMove(int CBOARD[File][Rank], int xi, int yi, int xf, int yf);

/* functions for QueenMove*/
int ValidQueenMove(int CBOARD[File][Rank], int startX, int startY, int endX, int endY);

/* Promotes Pawn after having moved to its 8th rank*/
void PawnPromotion(int CBOARD[File][Rank], int startX, int startY);

/*Move function that moves the valid piece*/
int Move(int Cboard[File][Rank], int startX, int startY, int endX, int endY);
/*capture function takes away opponent's piece*/
void Capture(int Cboard[File][Rank], int startX, int startY, int endX, int endY);

/*checkmate function for king*/
int checkmateking(int CBOARD[File][Rank], int xking, int yking);

#endif
