#include <stdio.h>
#include <cs50.h>

//CONNECT 4

/*
coordinates:
[0][0] [0][1] [0][2] [0][3] [0][4] ...
[1][0] [1][1] [1][2] [1][3] [1][4] ...
[2][0] [2][1] [2][2] [2][3] [2][4] ...
...
[5][0] ...
*/




int main(void)
{
    //constants for board width and height
    unsigned short width=7;
    unsigned short height=6;

    if((width*height)%2!=0)
    {
        printf("Board area must be an even number\n");
        return 1;
    }

    //the board
    char board[height][width];

    //counts of how many pieces are in each row
    unsigned short pieceCount[width];
    for(unsigned short s=0; s<width; s++)
    {
        pieceCount[s]=0;
    }

    //dictates who won (or if the game is still playing)
    char winner='p';

    //current player
    char currentPlayer='X';

    //current column
    int dropColumn=0;

    //how many in a row
    short inARow=0;



    //set all spaces on the board to empty
    for(short y=0; y<height; y++)
    {
        for(short x=0; x<width; x++)
        {
            board[y][x]='-';
        }
    }


    //instructions
    printf("\nEnter a column number to drop a piece. Only integers between 1 and %i will work.\n", width);
    printf("Pieces are affected by gravity, so any dropped piece will take the lowest possible space in each column.\n");
    printf("Turns are automatically taken. There is no Undo button, so choose a column wisely.\n");
    printf("After each turn, the updated board will be printed.\n");
    printf("The first player to get 4 in a row (horizontally, vertically, diagonally) wins. The game will automatically detect a 4-in-a-row and declare a winner.\n");
    printf("Enter 5709 to stop the game (the number 5709 looks like the word STOP if you squint really hard).\n");

    //////////////////////////////////////////////////////////////////////////////
    short x=0;
    short y=0;
    int turn=1;

    //gameplay
    while((winner!='X' && winner!='O') && turn<=width*height/2)
    {

        //print scale
        printf("\n");
        for(int s=1; s<=width; s++)
        {
            printf("    %i    ", s);
        }
        printf("\n");

        //print divider
        for(int d=1; d<=(9*width); d++)
        {
            printf("_");
        }
        printf("\n");


        //print the board
        for(y=0; y<height; y++)
        {
            for(int p=1; p<=3; p++)
            {
                for(x=0; x<width; x++)
                {
                    printf("   ");

                    if(board[y][x]=='X')
                    {
                        if(p==1 || p==3)
                        {
                            printf("X X");
                        }
                        if(p==2)
                        {
                            printf(" X ");
                        }
                    }
                    else if(board[y][x]=='O')
                    {
                        if(p==1 || p==3)
                        {
                            printf(" O ");
                        }
                        if(p==2)
                        {
                            printf("O O");
                        }
                    }
                    else
                    {
                        printf("---");
                    }

                    printf("   ");
                }
                printf("\n");
            }
            printf("\n\n");
        }

        x=0;
        y=0;

        //////////////////////////
        printf("Turn %i\n", turn);

        //ask player to enter column to drop, reprompt if off the board
        do
        {
            dropColumn=get_int("%c enter column: ", currentPlayer);
            dropColumn--;

            if(dropColumn==5708)
            {
                printf("GAME STOPPED\n\n");
                return 0;
            }
            else if(dropColumn<0 || dropColumn>width-1)
            {
                printf("*Column number must be between 1 and %hu.\n", width);
            }
            else if(pieceCount[dropColumn]>=height)
            {
                printf("*Column is full. Choose another column.\n");
            }

        }
        while((dropColumn<0 || dropColumn>width-1) || pieceCount[dropColumn]>=height);



        //place the piece on the lowest empty space possible in the selected row
        for(short p=height-1; p>=0; p--)
        {
            if(board[p][dropColumn]=='-')
            {
                board[p][dropColumn]=currentPlayer;
                pieceCount[dropColumn]++;
                dropColumn=-1;
                break;
            }
        }



        ///////////////////////////////////////////////////////////

        //CONNECT 4 CHECKS

        //horizontal
        for(y=0; y<height; y++)
        {
            for(x=0; x<width; x++)
            {
                if(board[y][x]==currentPlayer)
                {
                    inARow++;
                }
                else
                {
                    inARow=0;
                }

                if(inARow>=4)
                {
                    winner=currentPlayer;
                }
            }
            inARow=0;
        }
        inARow=0;
        x=0;
        y=0;

        //vertical
        for(x=0; x<width; x++)
        {
            for(y=0; y<height; y++)
            {
                if(board[y][x]==currentPlayer)
                {
                    inARow++;
                }
                else
                {
                    inARow=0;
                }

                if(inARow>=4)
                {
                    winner=currentPlayer;
                }
            }
            inARow=0;
        }


        //diagonal (bottom left to top right) bottom half

        //check the current diagonal
        for(int startX=0; startX<=width-4; startX++)
        {
            //set starting coordinates for x and y
            x=startX;
            y=height-1;
            inARow=0;

            //move up the diagonal, repeat as long as both x and y stay in bounds
            while(y>=0 && x<=width-1)
            {
                if(board[y][x]==currentPlayer)
                {
                    inARow++;
                }
                else
                {
                    inARow=0;
                }

                if(inARow>=4)
                {
                    winner=currentPlayer;
                }

                x++;
                y--;
            }

            //move x/y to next start position and check next diagonal
        }




        //diagonal (bottom left to top right) top half

        //check current diagonal
        for(int startY=height-1; startY>=3; startY--)
        {
            //set starting coords
            x=0;
            y=startY;
            inARow=0;

            //move up the diagonal
            while(y>=0 && x<=width-1)
            {
                if(board[y][x]==currentPlayer)
                {
                    inARow++;
                }
                else
                {
                    inARow=0;
                }

                if(inARow>=4)
                {
                    winner=currentPlayer;
                }

                x++;
                y--;
            }
        }



        //diagonal (bottom right to top left) bottom half
        for(int startX=width-1; startX>=3; startX--)
        {
            //starting coords
            x=startX;
            y=height-1;
            inARow=0;

            //move up the diagonal
            while(y>=0 && x>=0)
            {
                if(board[y][x]==currentPlayer)
                {
                    inARow++;
                }
                else
                {
                    inARow=0;
                }

                if(inARow>=4)
                {
                    winner=currentPlayer;
                }

                x--;
                y--;
            }
        }


        //diagonal (bottom right to top left) top half
        for(int startY=height-1; startY>=3; startY--)
        {
            //start coords
            x=width-1;
            y=startY;
            inARow=0;

            //move up the diagonal
            while(y>=0 && x>=0)
            {
                if(board[y][x]==currentPlayer)
                {
                    inARow++;
                }
                else
                {
                    inARow=0;
                }

                if(inARow>=4)
                {
                    winner=currentPlayer;
                }

                x--;
                y--;
            }
        }




        //change player
        if(currentPlayer=='X')
        {
            currentPlayer='O';
        }
        else
        {
            currentPlayer='X';
            turn++;
        }

        x=0;
        y=0;

        printf("\n\n\n");
    }


    ////////////////////////////////////////////////////////////////////////


    //print scale
    printf("\n");
    for(int s=1; s<=width; s++)
    {
        printf("    %i    ", s);
    }
    printf("\n");

    //print divider
    for(int d=1; d<=(9*width); d++)
    {
        printf("_");
    }
    printf("\n");

    //print the board
    for(y=0; y<height; y++)
    {
        for(int p=1; p<=3; p++)
        {
            for(x=0; x<width; x++)
            {
                printf("   ");

                if(board[y][x]=='X')
                {
                    if(p==1 || p==3)
                    {
                        printf("X X");
                    }
                    if(p==2)
                    {
                        printf(" X ");
                    }
                }
                else if(board[y][x]=='O')
                {
                    if(p==1 || p==3)
                    {
                        printf(" O ");
                    }
                    if(p==2)
                    {
                        printf("O O");
                    }
                }
                else
                {
                    printf("---");
                }

                printf("   ");
            }
            printf("\n");
        }
        printf("\n\n");
    }


    //declare a winner
    if(winner=='X' || winner=='O')
    {
        printf("PLAYER %c WINS!\n\n", winner);
    }
    else
    {
        printf("TIE!\n\n");
    }

    return 0;
}