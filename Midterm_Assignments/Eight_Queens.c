#include <stdio.h>
#include <stdlib.h>

void printboard(int** b){
    //function to print the board
    printf(" _______________________________________\n");
    for(int i = 0;i<8;i++){
        printf("|");
        for(int j=0;j<8;j++){
            if(b[i][j]==1) printf("  Q |");
            else printf("    |");
        }
        printf("\n");
        printf("|____|____|____|____|____|____|____|____|\n");
    }
}

int allowed(int **b, int row, int col){
    for(int i = 0; i<row; i++){
        //returns 0 if the column already contains a queen by iterating through previous rows
        if(b[i][col]==1) return 0;
    }
    int r = row-1;
    for(int i = col-1;i>=0;i--){
        //returns 0 if the upper left diagonal contains any queens by iterating through previous rows and columns
        if(r<0)break;
        if(b[r][i]) return 0;
        r--;
    }
    r = row-1;
    for(int i = col;i<8;i++){
        //returns 0 if the upper right diagonal contains any queens by iterating through previous rows and the rest of the columns
        if(r<0)break;
        if(b[r][i]) return 0;
        r--;
    }
    return 1;
}

int eightQueens(int **b, int row){
    if(row==8){
        //if all the queens have been placed, then we have succeeded so return 1
        return 1;
    }
    for(int i = 0; i<8; i++){
        //try placing the queen in each column
        if(allowed(b, row, i)==1){
            //if we are allowed to place the queen in that column, place the queen in that column
            b[row][i] = 1;
            if(eightQueens(b, row+1)==1) return 1;
            //check if a queen can be placed in any column of the next row and return 1 if it can.
        }
        b[row][i] = 0;//backtrack to the previous row when a queen cannot be placed in any of the columns of a row
    }
    return 0;//return 0 when a queen cannot be placed in any column of the row
}

void main(){
    int** board = (int **)malloc(8*sizeof(int*));//allocates memory for a 8x8 integer array using array pointers
    for(int i = 0;i<8;i++){
        board[i] = (int *)malloc(8*sizeof(int));
        for(int j=0;j<8;j++){
            board[i][j] = 0;
        }
    }
    if(eightQueens(board, 0)==1)printboard(board);//if a solution was found, then print the solution
    else printf("Failed");//if the solution was not found, print failed
}
