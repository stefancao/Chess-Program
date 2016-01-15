/**************************************/
/* Chesstro.c 			      */
/* author: i9 (team 9)		      */
/* initial version: 01/21/15          */
/* latest verison: 02/01/15	      */
/**************************************/

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Constants.h"
#include "AI.c"
#include "Rules.h"

/*Global Variables */


static int counter = 0;
static int WorB = 0;		/*for en passant*/
static int pawnXd = 0;
static int pawnYd = 0;
int First_Move = 1;	/* For Logfile, prints when game started */




GtkWidget *window ;
GtkWidget *fixed ;
GtkWidget *chess_icon ;
GtkWidget *table ;

/* 8 by 8 Board used for GUI */
enum GRID Board[8][8];
enum GRID BasedBoard[8][8] = {
		{ WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK},
		{ BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE},
		{ WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK},
		{ BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE},
		{ WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK},
		{ BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE},
		{ WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK},
		{ BLACK, WHITE, BLACK, WHITE, BLACK, WHITE, BLACK, WHITE},
		};


int CBOARD[10][12] = {0};	/* A 10 by 12 board used for Rules and AI */
		
void InitPlayer()
{
	int wPlayer = Player;
	int bPlayer = Computer;
}

void InitCBOARD()
{

   int x, y;
 	for(x=0; x<10;x++)
		for (y=0;y<12;y++)
			CBOARD[x][y] = 0;


   for(x =0; x < 10; x++)
        for(y=0; y < 12; y++){
            if(y==0||y==1||y==10||y==11){
                CBOARD[x][y] = 99;}
            if(x==0||x==9)
                CBOARD[x][y] = 99;
            if(y==3 && x!=0 && x!=9)
                CBOARD[x][y] = -20;
            if(y==8 && x!=0 && x!=9)
                CBOARD[x][y] = 20;
   }
   CBOARD[1][2]=CBOARD[8][2]=-3;
   CBOARD[2][2]=CBOARD[7][2]=-5;
   CBOARD[3][2]=CBOARD[6][2]=-7;
   CBOARD[4][2]=-9;
   CBOARD[5][2]=-10;
   CBOARD[1][9]=CBOARD[8][9]=3;
   CBOARD[2][9]=CBOARD[7][9]=5;
   CBOARD[3][9]=CBOARD[6][9]=7;
   CBOARD[4][9]=9;
   CBOARD[5][9]=10;

}

void InitBoard()
{
    int x, y;
    for (x = 0; x < 8; x++)
        for (y = 0; y < 8; y++)
        {
            if (x %2 == 0)
                if (y%2==0)
                    Board[x][y] = WHITE;
                else
                    Board[x][y] = BLACK;
                else
                    if (y%2==0)
                        Board[x][y] = BLACK;
                    else
                        Board[x][y] = WHITE;
        }
    for(x = 0; x < 8; x++)
	{
	Board[x][6] = wPAWN;
	Board[x][1] = bPAWN;
	}
    Board[0][7] = Board[7][7] = wROOK;
    Board[1][7] = Board[6][7] = wKNIGHT;
    Board[2][7] = Board[5][7] = wBISHOP;
    Board[3][7] = wQUEEN;
    Board[4][7] = wKING;
   
    Board[0][0] = Board[7][0] = bROOK;
    Board[1][0] = Board[6][0] = bKNIGHT;
    Board[2][0] = Board[5][0] = bBISHOP;
    Board[3][0] = bQUEEN; 
    Board[4][0] = bKING;
   
}


void DrawBoard()
{
    int i, j;
    
    for(i = 0; i < 8; i ++)
    {
        for(j = 0; j < 8; j ++)
        {
            switch(Board[i][j])
            {
                case BLACK:
                    chess_icon = gtk_image_new_from_file("./Chess_Icon/Bsquare.jpg") ;
                    break;
                case WHITE:
                    chess_icon = gtk_image_new_from_file("./Chess_Icon/Wsquare.jpg") ;
                    break;
		case wPAWN:
		    if (BasedBoard[i][j] == WHITE)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/WPawnw.jpg") ;
			}	
		    else if (BasedBoard[i][j] == BLACK)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/WPawnb.jpg") ;
		  	}
		    break;
		case bPAWN:
		    if (BasedBoard[i][j] == WHITE)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/BPawnw.jpg") ;
			}	
		    else if (BasedBoard[i][j] == BLACK)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/BPawnb.jpg") ;
		  	}
		    break;
		case wKNIGHT:
		    if (BasedBoard[i][j] == WHITE)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/WKnightw.jpg") ;
			}	
		    else if (BasedBoard[i][j] == BLACK)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/WKnightb.jpg") ;
		  	}
		    break;
		case bKNIGHT:
		    if (BasedBoard[i][j] == WHITE)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/BKnightw.jpg") ;
			}	
		    else if (BasedBoard[i][j] == BLACK)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/BKnightb.jpg") ;
		  	}
		    break;
		case wBISHOP:
		    if (BasedBoard[i][j] == WHITE)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/WBishopw.jpg") ;
			}	
		    else if (BasedBoard[i][j] == BLACK)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/WBishopb.jpg") ;
		  	}
		    break;
		case bBISHOP:
		    if (BasedBoard[i][j] == WHITE)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/BBishopw.jpg") ;
			}	
		    else if (BasedBoard[i][j] == BLACK)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/BBishopb.jpg") ;
		  	}
		    break;
		case wROOK:
		    if (BasedBoard[i][j] == WHITE)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/WRookw.jpg") ;
			}	
		    else if (BasedBoard[i][j] == BLACK)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/WRookb.jpg") ;
		  	}
		    break;
		case bROOK:
		    if (BasedBoard[i][j] == WHITE)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/BRookw.jpg") ;
			}	
		    else if (BasedBoard[i][j] == BLACK)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/BRookb.jpg") ;
		  	}
		    break;
		case wQUEEN:
		    if (BasedBoard[i][j] == WHITE)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/WQueenw.jpg") ;
			}	
		    else if (BasedBoard[i][j] == BLACK)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/WQueenb.jpg") ;
		  	}
		    break;
		case bQUEEN:
		    if (BasedBoard[i][j] == WHITE)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/BQueenw.jpg") ;
			}	
		    else if (BasedBoard[i][j] == BLACK)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/BQueenb.jpg") ;
		  	}
		    break;
                case wKING:
		    if (BasedBoard[i][j] == WHITE)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/WKingw.jpg") ;
			}	
		    else if (BasedBoard[i][j] == BLACK)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/WKingb.jpg") ;
		  	}
                    break;
		case bKING:
		    if (BasedBoard[i][j] == WHITE)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/BKingw.jpg") ;
			}	
		    else if (BasedBoard[i][j] == BLACK)
			{
			chess_icon = gtk_image_new_from_file("./Chess_Icon/BKingb.jpg") ;
		  	}
                default:
                    break;
                    
            }
            gtk_table_attach(GTK_TABLE(table), chess_icon, i, i + 1, j, j + 1, GTK_FILL, GTK_FILL, 0, 0) ;
        }
    }
}



void UpdateBoard(void)
{
	int x, y;

	for(x = 1; x < 9; x++)	
	{
		for (y = 2; y < 10; y++)
		{
			if (CBOARD[x][y] == 0)
			{
				Board[x-1][y-2] = BasedBoard[x-1][y-2];	/* If blank, put a black or white tile there */
			}  
			else if (CBOARD[x][y] >= 2 && CBOARD[x][y] <= 21) /* White Pieces */
			{
				switch(CBOARD[x][y])
				{
					case 20:
						Board[x-1][y-2] = wPAWN;
						break; 
					case 21:				/*for en passant*/
						Board[x-1][y-2] = wPAWN;
						break; 
					case 3:
						Board[x-1][y-2] = wROOK;
						break;
					case 5:
						Board[x-1][y-2] = wKNIGHT;
						break;
					case 7:
						Board[x-1][y-2] = wBISHOP;
						break;
					case 9:
						Board[x-1][y-2] = wQUEEN;
						break;
					case 10:
						Board[x-1][y-2] = wKING;
						break;
				}
			}
			else if (CBOARD[x][y] <= -2 && CBOARD[x][y] >= -21) /* Black Pieces */
			{
				switch(CBOARD[x][y])
				{
					case -20:
						Board[x-1][y-2] = bPAWN;
						break;
					case -21:				/*for en passant*/
						Board[x-1][y-2] = bPAWN;
						break;
					case -3:
						Board[x-1][y-2] = bROOK;
						break;
					case -5:
						Board[x-1][y-2] = bKNIGHT;
						break;
					case -7:
						Board[x-1][y-2] = bBISHOP;
						break;
					case -9:
						Board[x-1][y-2] = bQUEEN;
						break;
					case -10:
						Board[x-1][y-2] = bKING;
						break;
				}
			}
			else
			{
			}
		}
	}


}


/* LogOfMoves Start print */
int LogOfMovesStart(void)
{

	FILE *f = fopen("LogOfMoves.txt", "a");                                      
        time_t current_time;	/* Get current time */                                                         
        char* c_time_string;                                                         
        current_time = time(NULL);                                                   
        c_time_string = ctime(&current_time);                                         
        fprintf(f, "***************************\n");                                 
        fprintf(f, "***************************\n\n");                               
        fprintf(f, "Started on %s\n", c_time_string);	/* Print current time when started*/             
        fclose(f);                                                                   

}


/* LogOfMoves End print */
int LogOfMovesEnd(void)
{
	FILE *f = fopen("LogOfMoves.txt", "a");                                              
        time_t current_time;                                                                 
        char* c_time_string;                                                                 
        current_time = time(NULL);                                                           
        c_time_string = ctime(&current_time);                                                
        fprintf(f, "\nEnded on %s\n", c_time_string);                                        
        fprintf(f, "***************************\n");                                         
        fprintf(f, "***************************\n\n");                                       
        fclose(f);
}



/* Switch x value in array to character */
char X_2_Char(int x_value)
{
	char char_x;
	switch(x_value)
        {
                case 0:
                        char_x = 'a';
                        break;
                case 1:
                        char_x = 'b';
                        break;
                case 2:
                        char_x = 'c';
                        break;
                case 3:
                        char_x = 'd';
                        break;
                case 4:
                        char_x = 'e';
                        break;
                case 5:
                        char_x = 'f';
                        break;
                case 6:
                        char_x = 'g';
                        break;
                case 7:
                        char_x = 'h';
                        break;
        }
	return char_x;

}


/* Switch y value in array to character */
char Y_2_Char(int y_value)
{
	char char_y;
        switch(y_value)
        {           
                case 0:
                        char_y = '8';
                        break;
                case 1:
                        char_y = '7';
                        break;
                case 2:
                        char_y = '6';
                        break;
                case 3:
                        char_y = '5';
                        break;
                case 4:
                        char_y = '4';
                        break;
                case 5:
                        char_y = '3';
                        break;
                case 6:
                        char_y = '2';
                        break;
                case 7:
                        char_y = '1';
                        break;
        }
        return char_y;
 
}

void CheckAI()
{
	if(WhiteOrBlackTurn % 2 == 0)
		{
		if(wPlayer == Player)
			printf("wPlayer is Player\n");
		else if (wPlayer == Computer)
			printf("wPlayer is Computer\n");
		}
	else if(WhiteOrBlackTurn %2 == 1)
		{
		if(bPlayer == Player)
			printf("bPlayer is Player\n");
		else if (bPlayer == Computer)
			printf("bPlayer is Computer\n");
			
		}	

}


void AIMoveFunction()
{
	printf("\nMy turn\n");
	/*Add anoop's AI function here */
	Random(CBOARD);
	UpdateBoard(); /*update board after the AI made its move because CBOARD should be updated */
	WhiteOrBlackTurn++; /*AI move is done, next move*/


    gtk_container_remove(GTK_CONTAINER(window), fixed) ;
    table = gtk_table_new (8, 8, TRUE) ;
    gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ;
    DrawBoard();
    
    /*set fixed*/
    
    fixed = gtk_fixed_new() ;
    gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ;
    gtk_container_add(GTK_CONTAINER(window), fixed) ;
    gtk_widget_show_all(window) ;
}




int WhereIsKing_X(int CBOARD[10][12], int white_or_black)	/* Determing the x position of King */
{
	int x, y;
	for(x = 0; x < 10; x++)
	{
		for(y = 0; y < 12; y++)
		{
			if (white_or_black == 0)
			{
				if(CBOARD[x][y] == 10)
				{
					return x;
				}
			}
			else if (white_or_black == 1)
			{
				if(CBOARD[x][y] == -10)
				{
					return x;
				}
			}
		}
	}
	
}

int WhereIsKing_Y(int CBOARD[10][12], int white_or_black)	/* Determining the y position of King*/
{

	int x, y;
	for(x = 0; x < 10; x++)
	{
		for(y = 0; y < 12; y++)
		{
			if (white_or_black == 0)
			{
				if(CBOARD[x][y] == 10)
				{
					return y;
				}
			}
			else if (white_or_black == 1)
			{
				if(CBOARD[x][y] == -10)
				{
					return y;
				}
			}
		}
	}
}



void MoveThePiece(int p_x, int p_y, int g_x, int g_y)
{
	char start_x;
	char start_y;
	char end_x;
	char end_y;
	int it_moved = -1; 
	int x, y;		/*for en passant*/
	if (p_x == g_x && p_y == g_y)
		{
		printf("same square!\n");
		return;
		}
	if (Board[p_x][p_y] == WHITE || Board[p_x][p_y] == BLACK)
		{
		printf("tile click was first!\n");
		return;
		}

	it_moved = Move(CBOARD,p_x +1, p_y + 2,g_x +1, g_y +2); 

/* translate Board coordinates to CBoard index*/

	UpdateBoard();
	
	if (First_Move == 1)	/* Print when started into Log file */
	{
		LogOfMovesStart();
	
		First_Move = 0;
	}

	start_x = X_2_Char(p_x);
	start_y = Y_2_Char(p_y);
	end_x = X_2_Char(g_x);
	end_y = Y_2_Char(g_y); 


	if(it_moved == 1)	/* It moved w/o capturing */
	{
		WhiteOrBlackTurn++;

		
		FILE *file = fopen("LogOfMoves.txt", "a");
		if (file == NULL)
		{
			printf("Error opening LogOfMoves.txt!\n");
			exit(1);
		}
		fprintf(file, "%c%c-%c%c\n", start_x, start_y, end_x, end_y);
		fclose(file);	

	
		/*following code is for en passant*/
		if(WorB+1 == WhiteOrBlackTurn)
		{
			if(CBOARD[pawnXd][pawnYd] == 21)
			{
				CBOARD[pawnXd][pawnYd] = 20;
			}
			if(CBOARD[pawnXd][pawnYd] == -21)
			{
				CBOARD[pawnXd][pawnYd] = -20;
			}
		}

                if(CBOARD[g_x+1][g_y+2] == 21 || CBOARD[g_x+1][g_y+2] == -21)
		{
                         pawnXd = g_x+1;
                         pawnYd = g_y+2;
                         WorB = WhiteOrBlackTurn;
                }/*EOF en passant*/
	}
	
	else if(it_moved == 2)	/* It captured */
	{
		WhiteOrBlackTurn++;
		printf("In capturing\n");


		
		/*following code is for en passant*/
		if(WorB+1 == WhiteOrBlackTurn)
		{
			if(CBOARD[pawnXd][pawnYd] == 21)
			{
				CBOARD[pawnXd][pawnYd] = 20;
			}
			if(CBOARD[pawnXd][pawnYd] == -21)
			{
				CBOARD[pawnXd][pawnYd] = -20;
			}
		}

                if(CBOARD[g_x+1][g_y+2] == 21 || CBOARD[g_x+1][g_y+2] == -21)
		{
                         pawnXd = g_x+1;
                         pawnYd = g_y+2;
                         WorB = WhiteOrBlackTurn;
                }/*EOF en passant*/



		FILE *file = fopen("LogOfMoves.txt", "a");
		if (file == NULL)
		{
			printf("Error opening LogOfMoves.txt!\n");
			exit(1);
		}

		fprintf(file, "%c%cX%c%c\n", start_x, start_y, end_x, end_y);
		fclose(file);	
	}


int a, b;                                                                 
int counter = 0;                                                              
for (a = 0; a < File; a++)                                                
        for (b = 0; b < Rank; b++)                                        
        {                                                                 
                 if (CBOARD[a][b] == 10 || CBOARD[a][b] == -10) /*if there's no white or black king start a new game*/
                 {                                                         
                         counter++;                                        
                 }/*fi*/                                                   
         } /*rof*/                                                         
if (counter != 2)                                                         
{                                                                         
	printf("End of the Game!\n");                                     
        new_game();                                                       
}/* fi */   


/* Check */
	int check, check_mate, x_king, y_king;
	x_king = WhereIsKing_X(CBOARD, WhiteOrBlackTurn % 2);
	y_king = WhereIsKing_Y(CBOARD, WhiteOrBlackTurn % 2);
	check = safe(CBOARD, x_king, y_king, ((WhiteOrBlackTurn+1) % 2));
	if (check == 0)
	{
		printf("King is in CHECK!\n");
		check_mate = checkmateking(CBOARD, x_king, y_king);
		if (check_mate == 0)
		{
			printf("CHECKMATE!\n");
			new_game();
		} 
		else
		{
		 	check = 1;
		} 

	}


    gtk_container_remove(GTK_CONTAINER(window), fixed) ;
    table = gtk_table_new (8, 8, TRUE) ;
    gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ;
    DrawBoard();
    
    /*set fixed*/
    
    fixed = gtk_fixed_new() ;
    gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ;
    gtk_container_add(GTK_CONTAINER(window), fixed) ;
    gtk_widget_show_all(window) ;

	if (wPlayer == Computer && WhiteOrBlackTurn %2 == 0)
		{
		AIMoveFunction();
		return;
		}	
	else if (bPlayer == Computer && WhiteOrBlackTurn %2 == 1)
		{
		AIMoveFunction();
		return;
		}


} /*eof movethe piece fn*/
    
void CoordToGrid(int c_x, int c_y, int *g_x, int *g_y)
{
    *g_x = (c_x - BOARD_BORDER) / SQUARE_SIZE;
    *g_y = (c_y - BOARD_BORDER) / SQUARE_SIZE;
}

static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
    g_print ("Welcome to Chesstro!\n");
}

static void Two_Coords(g_x, g_y)
{
	static int pcoord_x = -1, pcoord_y = -1;
	static int coord_x = -1, coord_y = -1;

	if (counter == 0)
		{
		if (Board[g_x][g_y] == BLACK || Board[g_x][g_y] == WHITE) /* checks if first click is a tile to avoid double click */
			return;
		pcoord_x = g_x;
		pcoord_y = g_y;
		if (WhiteOrBlackTurn % 2 == 0)
		{
			if (Board[pcoord_x][pcoord_y] < 0)
			{
				printf("It is white turn!\n");
				counter = -1;
			}
		}
		else 
		{
			if (Board[pcoord_x][pcoord_y] > 1)
			{
				printf("It is black turn!\n");
				counter = -1;
			}
		}
			
		printf("One More Click!\n");
		counter++;
		}
	else if (counter == 1)
		{
		coord_x = g_x;
		coord_y = g_y;
		counter++;
		}
	if (counter == 2)
		{
		MoveThePiece(pcoord_x, pcoord_y, coord_x, coord_y);
		counter = 0;
		}
	else if (counter > 2)
		{
		printf("Woah! something is wrong! please click again twice! :)\n");
		return;
		}
	return;
}

static gboolean
on_delete_event (GtkWidget *widget,
                 GdkEvent  *event,
                 gpointer   data)
{
    g_print ("delete event occurred\n");
    gtk_main_quit();
    return TRUE;
}

gint area_click (GtkWidget *widget,
                 GdkEvent  *event,
                 gpointer  data)
{
    int x1, y1 ;
    char words[MAX_MSGLEN] ;
    
    int coord_x, coord_y, grid_x, grid_y;
    int counter = 0;

    struct BOARD *chess_board ;
    struct SQUARE *chess_piece ;
    struct SQUARE *piece_dest ;
    
    GdkModifierType state ;
    
    gdk_window_get_pointer(widget->window, &coord_x, &coord_y, &state) ; 
    	CoordToGrid(coord_x, coord_y, &grid_x, &grid_y);
	    
	Two_Coords(grid_x, grid_y);

    return TRUE ;
}


void callback( GtkWidget *widget,
               gpointer   data )
{
    g_print ("Hello again - %s was pressed\n", (char *) data);
}


void Help(GtkWidget *widget, gpointer data)
{
	printf("\n\n******************** WELCOME TO THE HELP MENU FOR CHESSTRO ********************\n 1. Start playing Chesstro by using a mouse to click \"New Game\"\n 2. Select the mode of the player.\n 3. Start playing chess.\n 4. You can quit the game anytime by clicking \"Quit\"\n******************************************************************************* \n");

}

void new_game( GtkWidget *widget, 
		gpointer data)
{
	
	int play = 0;	
	InitBoard();
	WhiteOrBlackTurn = 0;
	counter = 0;
	
	
	printf("Please input: \n \t 1 for Player vs Player \n \t 2 for Player vs CPU \n \t 3 for CPU vs Player \n");
	
	scanf("%d", &play);

	if (play == 1)
		{
		printf("Player vs Player is now selected\n");
		wPlayer = Player;
		bPlayer = Player;
		}	
	else if (play == 2)
		{
		printf("Player vs CPU is now selected\n");
		wPlayer = Player;
		bPlayer = Computer;
		}
	else if (play == 3)
		{
		printf("CPU vs Player is now selected\n");
		wPlayer = Computer;
		bPlayer = Player;
		}
	/*else if (play == 4)
		{
		printf("CPU vs CPU is not selected\n");
		wPlayer = Computer;
		bPlayer = Computer;
		}*/
	else
		{
		InitPlayer();
		}

	InitCBOARD();

	g_print ("New game is pressed!\n");

	First_Move = 1;	/* Starting on New Move Log */
	LogOfMovesEnd();

	if(WhiteOrBlackTurn == 0 && wPlayer == Computer)
		AIMoveFunction();

    gtk_container_remove(GTK_CONTAINER(window), fixed) ;
    table = gtk_table_new (8, 8, TRUE) ;
    gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ;
    DrawBoard();
    
    /*set fixed*/
    
    fixed = gtk_fixed_new() ;
    gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ;
    gtk_container_add(GTK_CONTAINER(window), fixed) ;
    gtk_widget_show_all(window) ;
}

/* This callback quits the program */
gint delete_event( GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   data )
{

    LogOfMovesEnd(); /* Print the end time of Game into Log file */

    gtk_main_quit ();
    return(FALSE);
}

/* End - Added for buttons */




int main (int argc, char *argv[])
{
    char str[MAX_MSGLEN];

    gtk_init(&argc, &argv) ;
    InitBoard();
    InitCBOARD();   
    InitPlayer();
	wPlayer = Player;
	bPlayer = Computer;
    srand(time(NULL));
 
    /*create a new window */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
    gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT) ;
    gtk_container_set_border_width (GTK_CONTAINER(window), WINDOW_BORDER) ;
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER) ;
    gtk_window_set_title(GTK_WINDOW(window), "Let's play Chess!") ;
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE) ;
    
    
    /*register event handlers*/
    g_signal_connect(window, "delete_event", G_CALLBACK(on_delete_event), NULL) ;
    gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK) ;
    g_signal_connect(window, "button_press_event", G_CALLBACK(area_click), NULL) ;
   

    printf("Hello main!\n"); 
    /*create a table and draw the board*/
    table = gtk_table_new (8, 8, TRUE) ;
    gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ;
    DrawBoard();
    
    fixed = gtk_fixed_new() ; 
    gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ; 
    gtk_container_add(GTK_CONTAINER(window), fixed) ; 
    

    /*show the window*/
    gtk_widget_show_all(window) ;



    /* Start - Added for buttons */
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *table;

    gtk_init (&argc, &argv);

    /* Create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /* Set the window title */
    gtk_window_set_title (GTK_WINDOW (window), "Menu");

    /* Set a handler for delete_event that immediately exits GTK. */
    gtk_signal_connect (GTK_OBJECT (window), "delete_event",
                        GTK_SIGNAL_FUNC (delete_event), NULL);

    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);

    /* Create a 2x2 table */
    table = gtk_table_new (2, 2, TRUE);

    /* Put the table in the main window */
    gtk_container_add (GTK_CONTAINER (window), table);

    /* Create first button */
    button = gtk_button_new_with_label ("New Game");

    /* When the button is clicked, we call the "callback" function with a pointer to "button 1" as its argument */
    gtk_signal_connect (GTK_OBJECT (button), "clicked",
             GTK_SIGNAL_FUNC (new_game), NULL);


    /* Insert button 1 into the upper left quadrant of the table */
    gtk_table_attach_defaults (GTK_TABLE(table), button, 0, 1, 0, 1);

    gtk_widget_show (button);

    /* Create second button */

    button = gtk_button_new_with_label ("Help");

    /* When the button is clicked, we call the "callback" function with a pointer to "button 2" as its argument */
    gtk_signal_connect (GTK_OBJECT (button), "clicked",
              GTK_SIGNAL_FUNC (Help), NULL);
    /* Insert button 2 into the upper right quadrant of the table */
    gtk_table_attach_defaults (GTK_TABLE(table), button, 1, 2, 0, 1);

    gtk_widget_show (button);

    /* Create "Quit" button */
    button = gtk_button_new_with_label ("Quit");

    /* When the button is clicked, we call the "delete_event" function *      * and the program exits */
    gtk_signal_connect (GTK_OBJECT (button), "clicked",
                        GTK_SIGNAL_FUNC (delete_event), NULL);

    /* Insert the quit button into the both 
 *      * lower quadrants of the table */
    gtk_table_attach_defaults (GTK_TABLE(table), button, 0, 2, 1, 2);

    gtk_widget_show (button);

    gtk_widget_show (table);
    gtk_widget_show (window);
 
    
    /*show the window*/
    gtk_widget_show_all(window) ; 
    gtk_main() ;


	if(WhiteOrBlackTurn == 0 && wPlayer == Computer)
		AIMoveFunction();
    return 0 ;
}
