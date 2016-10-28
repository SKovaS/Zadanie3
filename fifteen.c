#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define DIM_MIN 3
#define DIM_MAX 9


int board[DIM_MAX][DIM_MAX];
int win_board[DIM_MAX][DIM_MAX];

int d;

void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

string blank_char = " * ";
int blank = 0;
int bx = 0;
int by = 0;
int tx = 0;
int ty = 0;

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

   
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }
    
 
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }
    
   
    greet();


    init();


    while (true)
    {
      
        clear();
        
        draw();

        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        if (won())
        {
            printf("ftw!\n");
            break;
        }

        printf("Tile to move: ");
        int tile = GetInt();
        
        if (tile == 0)
        {
            break;
        }
        
        fprintf(file, "%i\n", tile);
        fflush(file);

        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(600000);
        }

        usleep(50000);
    }
    
    fclose(file);


    return 0;
}

void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(600000);
}


void init(void)
{
    int count=d*d-1;
    for(int i=0; i<d; i++){
        for(int j=0; j<d; j++){
            board[i][j] = count;
            count--;    
        }
    }
    if((d*d)%2==0){
        board[d-1][d-3] = 1;
        board[d-1][d-2] = 2;
    }
    board[d-1][d-1] = blank;
    bx = by = d-1;
    
    count = 1;
    for(int i=0; i<d; i++){
        for(int j=0; j<d; j++){
            win_board[i][j] = count;
            count++;    
        }
    }
    win_board[d-1][d-1] = blank;
}

void draw(void)
{
    printf("\n");
    for(int i=0; i<d; i++){
        for(int j=0; j<d; j++){
            if(board[i][j]==0){
                printf("  %s", blank_char);
            } else if(board[i][j]>=10){
                printf("   %d", board[i][j]);
            } else if(board[i][j] >= 1 && board[i][j] <= 9){
                printf("   0%d", board[i][j]);
            }
        }
        printf("\n\n");
    }
}

bool move(int tile)
{
    bool moved = false;
    if(tile <= 0 || tile > (d*d)-1){
        return false;
    }
    
    bool found_tile = false;
    while(found_tile == false){
        for(int i=0; i<d; i++){
            for(int j=0; j<d; j++){
                if(tile == board[i][j]){
                    ty = i;
                    tx = j;
                    found_tile = true;
                    break;
                }
            }
        }
    }
    
    bool found_b_pos = false;
    
    if(board[ty-1][tx] == blank){
        if(d>ty-1 && ty-1>=0){
            found_b_pos = true;
        }
    }
    if(board[ty+1][tx] == blank){
        if(d>ty+1 && ty+1>=0){
            found_b_pos = true;
        }
    }
    if(board[ty][tx-1] == blank){
        if(d>tx-1 && tx-1>=0){
            found_b_pos = true;
        }
    }
    if(board[ty][tx+1] == blank){
        if(d>tx+1 && tx+1>=0){
            found_b_pos = true;
        }
    }
    
    if(found_b_pos == true){
        board[by][bx] = board[ty][tx];
        by = ty;
        bx = tx;
        board[ty][tx] = blank;
        moved = true;
    }
    else
    {
	    found_b_pos = false;
	return 0;
    }
	
    return moved;
}

bool won(void)
{
    bool won = false;
    bool winning = false;
    int win_count=1;
    
    for(int i=0; i<d; i++){
        for(int j=0; j<d; j++){
            if(board[i][j] == win_board[i][j]){
                winning = true;
            } else{
                winning = false;
                return won;
            }
            win_count++; 
        }
    }
    won = winning;
    return won;
}
