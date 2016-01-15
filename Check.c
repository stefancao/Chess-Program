int safe(int CBOARD[10][12], int SquareX, int SquareY)
{
	int x, y;
    if (CBOARD[SquareX][SquareY] >= 2 && CBOARD[SquareX][SquareY] <= 10) {
        for (y = 0; y < 12; y++) {
            for (x = 0; x < 10; x++) {
                if (CBOARD[x][y] < 0) {
                    switch (CBOARD[x][y]) {
                        case -2: /* check for pawn */
                        {
                            if (ValidPawnMove(CBOARD, x, y, SquareX, SquareY))
                            {
                                return 0;
                            }
                            /*else
                            {
                                return 1;
                            }*/
                            break;
                        }
                        case -3:
                        {
                            if (ValidRookMove(CBOARD, x, y, SquareX, SquareY)) {
                                return 0;
                            }
                            /*else
                            {
                                return 1;
                            }*/
                            break;
                        }
                        case -5:
                        {
                            if (ValidKnightMove(CBOARD, x, y, SquareX, SquareY))
                            {
                                return 0;
                            }
                            /*else
                            {
                                return 1;
                            }*/
                            break;
                        }
                        case -7:
                        {
                            if (ValidBishopMove(CBOARD, x, y, SquareX, SquareY))
                            {
                                return 0;
                            }
                            /*else
                            {
                                return 1;
                            }*/
                            break;
                        }
                        case -9:
                        {
                            if (ValidQueenMove(CBOARD, x, y, SquareX, SquareY))
                            {
                                return 0;
                            }
                            /*else
                            {
                                return 1;
                            }*/
                            break;
                        }
                        default:
                        {
                           /* return 1;*/
                            break;
                        }
                            
                    }
                }
                /*else
                {
                    return 1;
                }*/
            }
        }
    }
    else
    {
        for (y = 0; y < 12; y++) {
            for (x = 0; x < 10; x++) {
                if (CBOARD[x][y] > 0) {
                    switch (CBOARD[x][y]) {
                        case 2: /* check for pawn */
                        {
                            if (ValidPawnMove(CBOARD, x, y, SquareX, SquareY))
                            {
                                return 0;
                            }
                            /*else
                            {
                                return 1;
                            }*/
                            break;
                        }
                        case 3:
                        {
                            if (ValidRookMove(CBOARD, x, y, SquareX, SquareY)) {
                                return 0;
                            }
                            /*else
                            {
                                return 1;
                            }*/
                            break;
                        }
                        case 5:
                        {
                            if (ValidKnightMove(CBOARD, x, y, SquareX, SquareY))
                            {
                                return 0;
                            }
                            /*else
                            {
                                return 1;
                            }*/
                            break;
                        }
                        case 7:
                        {
                            if (ValidBishopMove(CBOARD, x, y, SquareX, SquareY))
                            {
                                return 0;
                            }
                            /*else
                            {
                                return 1;
                            }*/
                            break;
                        }
                        case 9:
                        {
                            if (ValidQueenMove(CBOARD, x, y, SquareX, SquareY))
                            {
                                return 0;
                            }
                            /*else
                            {
                                return 1;
                            }*/
                            break;
                        }
                        default:
                        {
                            /*return 1;*/
                            break;
                        }
                            
                    }
                }
            }
        }
    }
	return 1;
}
