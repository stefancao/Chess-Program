/**************************************/
/* Constants for chesstro	      */
/* author: i9 (team 9)		      */
/* initial version: 01/21/15          */
/* latest versoin: 02/01/15	      */
/**************************************/

#ifndef Constants_H
#define Constants_H


#define MAX_MSGLEN  100
#define SQUARE_SIZE 50
#define WINDOW_BORDER 10
#define BOARD_BORDER 10
#define BOARD_WIDTH  (8*SQUARE_SIZE)
#define BOARD_HEIGHT (8*SQUARE_SIZE)
#define WINDOW_WIDTH  (BOARD_WIDTH + 2*BOARD_BORDER)
#define WINDOW_HEIGHT (BOARD_HEIGHT + 2*BOARD_BORDER)
#define File 10
#define Rank 12

#define Computer 1
#define Player 0

static int WhiteOrBlackTurn = 0;
static int HasRook1Moved = 0;
static int HasRook2Moved = 0;
static int HasRook3Moved = 0;
static int HasRook4Moved = 0;
static int HasWKingMoved = 0;
static int HasBKingMoved = 0;

static int wPlayer;
static int bPlayer;




/* PIECE TYPE INTEGER REPRESENTATIONS*/
/* Black Pieces = negative integers
 *  * White Pieces = positive integers
 *   * Pawn = 20 or 21, 21 if has double jumped, otherwise 20
 *    * Rook = 3
 *     * Knight = 5
 *      * Bishop = 7
 *       * Queen = 9
 *        * King = 10
 *         * Barrier = 99 */

enum GRID {
    BLACK = 0,
    WHITE = 1,
    wPAWN = 20,
    bPAWN = -20,
    wROOK = 3,
    bROOK = -3,
    wKNIGHT = 5,
    bKNIGHT = -5,
    wBISHOP = 7,
    bBISHOP = -7,
    wQUEEN = 9,
    bQUEEN = -9,
    wKING = 10,
    bKING = -10,
};


#endif
