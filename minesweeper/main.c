#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Defines
#define TABLE_SIZE 8
#define NORMAL 2 //Mine number
#define WIN 1
#define LOSE -1
#define CONTINUE 0

//Variables
int subtable[TABLE_SIZE+2][TABLE_SIZE+2];
char table[TABLE_SIZE+2][TABLE_SIZE+2];
int numberOfMine;
int fCount = 0;

//Functions
void create_subtable();
void initialize_table();
void display_subtable();
void display_table();
void place_mines();
int check_match_won();
void explorer(int line, int column);
int dig(int line, int column);




int main()
{
    int line, column;
    int advance;
    char action;
    char yenidena;
    time_t start, end;
    printf("Welcome to MINESWEEPER GAME! \n");
    create_subtable();
    initialize_table();
    time(&start);
    do
    {
        
        display_table();
        printf("\n");
        printf("Please use this format to play: d,line,column or f,line,column or e,line,column\n");
        scanf("%c,%d,%d",&action,&line,&column);
        printf("\n");

        if(action == 'd')
        {
            advance = dig(line,column);
        }
        else if (action == 'f')
        {
            if(numberOfMine > fCount)
            {
                fCount++;
                table[line][column]='F';
                advance = check_match_won();
            }
        }
        else if (action == 'e')
        {
            if(fCount > 0)
            {
                fCount--;
            }
            table[line][column] = '#';
            advance = dig(line, column);
        }
        
        if(advance == LOSE)
        {
            time(&end);
            printf("GAME OVER. \n");
            display_subtable();
            printf("\nWANNA TRY AGAIN ? [Y][N]\n");
            scanf(" %c",&yenidena);
            switch (yenidena)
            {
            case 'N':
                printf("THANKS FOR PLAYING \n");
                return 0;
                break;
            
            case 'Y':
                fCount = 0;
                advance = CONTINUE;
                create_subtable();
                initialize_table();
                break;
            default:
                printf("WRONG INPUT \n");
                break;
            }
        }

        if(advance == WIN)
        {
            time(&end);
            printf("CONGRATS! YOU WON. \n");
            display_subtable();
            printf("\nWANNA TRY AGAIN ? [Y][N]\n");
            scanf(" %c",&yenidena);
            switch (yenidena)
            {
            case 'N':
                printf("THANKS FOR PLAYING \n");
                return 0;
                break;
            
            case 'Y':
                fCount = 0;
                advance = CONTINUE;
                create_subtable();
                initialize_table();
                break;
            default:
                printf("WRONG INPUT \n");
                break;
            }
        }
        
    } 
    while(1);
    
    return 0;
}

void create_subtable()
{
    int nbMine;

    for(int i = 0; i<=TABLE_SIZE + 1; i++)
    {
        for(int j = 0; j<=TABLE_SIZE + 1; j++)
        {
            subtable[i][j] = 0;
        }
    }

    for(int i = 0; i<=TABLE_SIZE; i++)
    {
        subtable[i][0] = 1;
        subtable[i][TABLE_SIZE+1] = 1;
    }
    for(int i = 0; i<=TABLE_SIZE; i++)
    {
        subtable[0][i] = 1;
        subtable[TABLE_SIZE+1][i] = 1;
    }
    nbMine = NORMAL;
    place_mines();
}

void initialize_table()
{

    for(int i = 0; i<=TABLE_SIZE + 1; i++)
    {
        for(int j = 0; j<=TABLE_SIZE + 1; j++)
        {
            table[i][j] = '#';
        }
    }

    for(int i = 0; i<=TABLE_SIZE + 1; i++)
    {
        table[i][0] = '*';
        table[i][TABLE_SIZE+1] = '*';
    }
    for(int i = 0; i<=TABLE_SIZE; i++)
    {
        table[0][i] = '*';
        table[TABLE_SIZE+1][i] = '*';
    }
}

void display_table()
{
    printf("\n");
    for(int i = 1; i<=TABLE_SIZE; i++)
    {
        printf("%3d",i);
    }
    printf("\n");

    for(int i=1; i<=TABLE_SIZE; i++)
    {
        printf("---");
    }
    printf("\n");

    for(int i = 1; i<=TABLE_SIZE; i++)
    {
        for (int j = 1; j <= TABLE_SIZE; j++)
        {
            printf("%3c", table[i][j]);
        }
        printf("  |%d", i);
        printf("\n");
    }

    for (int i = 1; i <= TABLE_SIZE; i++)
    {
        printf("---");
    }
    
}

void display_subtable()
{
    printf("\n");
    for(int i = 1; i<=TABLE_SIZE; i++)
    {
        printf("%3d",i);
    }
    printf("\n");

    for(int i=1; i<=TABLE_SIZE; i++)
    {
        printf("---");
    }
    printf("\n");

    for(int i = 1; i<=TABLE_SIZE; i++)
    {
        for (int j = 1; j <= TABLE_SIZE; j++)
        {
            printf("%3d", subtable[i][j]);
        }
        printf("  |%d", i);
        printf("\n");
    }

    for (int i = 1; i <= TABLE_SIZE; i++)
    {
        printf("---");
    }
}

void place_mines()
{
    srand(time(NULL));
    numberOfMine = NORMAL;
    int line, column;

    for (int i = 1; i <= numberOfMine; i++)
    {
        line = 1+rand()%TABLE_SIZE;
        column = 1+rand()%TABLE_SIZE;
        if(subtable[line][column] == -1)
        {
            i--;
        }
        subtable[line][column] = -1;

        for (int k = -1; k <= 1; k++)
        {
            for (int p = -1; p <= 1; p++)
            {
                if(subtable[line][column]==-1)
                {
                    if (subtable[line+k][column+p]!=-1)
                    {
                        subtable[line+k][column+p]++;
                    }
                    
                }
            }
            
        }
        

    }
    
}

int dig(int line, int column)
{
    int x = 0;
    if(subtable[line][column] == -1)
    {
        x = LOSE;
    }
    else if(subtable[line][column] > 0)
    {
        table[line][column] = ('0' + subtable[line][column]);
        x = check_match_won();
        x = CONTINUE;
    }
    else
    {
        explorer(line, column);
    }
    return x;
}

void explorer(int line, int column)
{
    int i,j;
    table[line][column] = '0' + subtable[line][column];

    for (i = -1; i <=1; i++)
    {
        for (j = -1; j <= 1; j++)
        {
            if(subtable[line+i][column+i] > 0 && table[line+i][column+j]== '#')
            {
                table[line+i][column+j] = '0' + subtable[line+i][column+j];
            }
            else if(subtable[line+i][column+j]==0 && table[line+i][column+j] == '#')
            {
                explorer(line+i,column+j);
            }
        }
        
    }
    
}

int check_match_won()
{
    int status, counter=0;
    for (int i = 1; i <= TABLE_SIZE; i++)
    {
        for (int j = 1; j <= TABLE_SIZE; j++)
        {
            if(table[i][j]=='F')
            {
                if(subtable[i][j]==-1)
                {
                    counter++;
                }
            }
        }
        
    }

    if(counter == NORMAL)
    {
        status = WIN;
    }
    else
    {
        status = CONTINUE;
    }

    return status;
    
}