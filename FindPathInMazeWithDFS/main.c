#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DELAY 0.5
#define MAX_APPLES 7

void delay(double number_of_seconds);
char** allocateMatrix(int M,int N);
void readMatrix(char**,int M, int N); //reads matrix from file
void printMtr(char **mtr, int M,int N);
void printMtrIsNULLError();//disp error
int findRows();//find how many rows in matrix in given file
int findColumns();//find how many columns in matrix in given file
void DFS(char **mtr,int startX,int startY,int *points,int *flag);
void insertApples(char**mtr,int M,int N,int appleCount);
int findMtrStartPoint(char **mtr,int*x,int*y,int M,int N);//find the start point == b
int checkIfEndPointExists(char **mtr,int M,int N);
void freeMtr(char**mtr);
int main() {
    char **mtr=NULL;
    int decision = 0,M,N;
    int pts = 0;
    int *points = &pts;
    int X,Y;
    int *x=&X,*y=&Y,zero = 0,appleCount=0;
    int *flag = &zero;
    srand(time(NULL));
    do{
        printf("Please select your operation:\n");
        printf("1.Create Matrix\n2.View Matrix's current state\n3.Start search.\n0.Exit\n");
        scanf("%d",&decision);
        switch (decision) {
            case 1:
                mtr = NULL;
                M=findRows();
                N=findColumns();
               // printf("ROWS: %d, COLUMNS: %d\n", M,N);
                mtr = allocateMatrix(M,N);
                readMatrix(mtr,M,N); // read matrix from file
                if(checkIfEndPointExists(mtr,M,N) == 0 && findMtrStartPoint(mtr,x,y,M,N) == 0){
                    printMtr(mtr,M,N); // if b or c not specified don't accept input
                    printf("To add additional apples, enter a number between 0-%d\n(if you dont want to add any, enter 0)\n",MAX_APPLES);
                    do{
                        scanf("%d",&appleCount);
                        if(appleCount<0) printf("Apple count can't be smaller than 0! Please re-enter your apple count.\n");
                        else if(appleCount>7) printf("Apple count can't be larger than %d! Please re-enter your apple count.\n",MAX_APPLES);
                    } while ( appleCount < 0 ||appleCount >7); // if apple count not valid, retake input
                    insertApples(mtr,M,N,appleCount); // insert apples to matrix, warning: this DOESN'T affect the file
                    if(appleCount!= 0) printMtr(mtr,M,N); //if matrix has changed re-print the matrix
                }
                else{
                    printf("Starting-ending point is not specified, please re-enter the matrix!!\n");
                }
                break;
            case 2:
                printMtr(mtr,M,N);
                break;
            case 3:
                //printf("x:%d y:%d\n",*x,*y);
                *flag=0;// flag = 1 means c has reached, so it has to set 0 every time before DFS function call
                *points=0;
                DFS(mtr,*x,*y,points,flag); //start search
                printf("Total points : %d\n",*points);
                break;
            case 0:
                printf("exiting...\n");
                break;
        }

    } while (decision != 0);


    return 0;
}
void delay(double number_of_seconds){
    // Converting time into milli_seconds
    double milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}
int isMovable(char **mtr,int x,int y){ //if we can move to specified coordinates, return 1
    if((mtr[y][x] == ' ' || mtr[y][x] == 'c' || mtr[y][x] == 'O' ) && mtr[y][x] != '*')return 1;
    else return 0;
}
int isDeadEnd(char **mtr,int startX,int startY){ //check if we are on the dead-end in matrix, if so return 1
    if( (isMovable(mtr,startX,startY-1) == 0) &&
            (isMovable(mtr,startX,startY+1) == 0)&&
            (isMovable(mtr,startX+1,startY) == 0) &&
            (isMovable(mtr,startX-1,startY) == 0)){
        return 1;
    }
    else return 0;
}

int findMtrStartPoint(char **mtr,int*x,int*y,int M,int N){
    int i,j;
    for(i=0;i<M;i++){
        for(j=0;j<N;j++){
            if(mtr[i][j] == 'b'){
                *x = j;
                *y= i;
                return 0;
            }
        }
    }
    return -1;
}

int checkIfEndPointExists(char **mtr,int M,int N){
    int i,j;
    for(i=0;i<M;i++){
        for(j=0;j<N;j++){
            if(mtr[i][j] == 'c'){
                return 0;
            }
        }
    }
    return -1;
}

void DFS(char **mtr,int startX,int startY,int *points,int *flag){
    if(mtr[startY][startX] == 'c'){
        mtr[startY][startX] = '*';
        delay(DELAY);
        printMtr(mtr,findRows(),findColumns());
        printf("points : %d\n",*points);
        *flag=1; // if flag = 0, no more recursive call will happen
    }
    else{
        if(mtr[startY][startX] == ' ' ||mtr[startY][startX] == 'b'  || mtr[startY][startX] == 'O'){
            if(mtr[startY][startX] == 'O') *points+=10;
            mtr[startY][startX] = '*';
            delay(DELAY);
            printMtr(mtr,findRows(),findColumns());
            printf("points : %d\n",*points);
        }
        if(isDeadEnd(mtr,startX,startY)==1){
            *points-=5;
        }
        else{ // enter here if we are NOT on dead-end
              // if we are on dead-end, recursive calls won't happen, so we naturally return to our initial point
            if(isMovable(mtr,startX,startY+1) == 1 && *flag == 0)
                DFS(mtr,startX,startY+1,points,flag);
            if(isMovable(mtr,startX,startY-1) == 1&& *flag == 0)
                DFS(mtr,startX,startY-1,points,flag);
            if(isMovable(mtr,startX+1,startY) == 1 && *flag ==0)
                DFS(mtr,startX+1,startY,points,flag);
            if(isMovable(mtr,startX-1,startY) == 1 && *flag == 0)
                DFS(mtr,startX-1,startY,points,flag);
        }
        if(*flag == 0){ //puts ' ' (space) character if we are returning from a dead end
            mtr[startY][startX] = ' ';
            delay(DELAY);
            printMtr(mtr,findRows(),findColumns());
            printf("points : %d\n",*points);
        }
    }

}

char** allocateMatrix(int M, int N){
    char **mtr = (char**) malloc((M+1)*sizeof(char*));
    int i;
    for(i=0;i<=M;i++){
        mtr[i] = (char*)malloc((N+1)*sizeof (char ));
    }
    return mtr;
}

void readMatrix(char **mtr,int M,int N){
    int i,j;
    FILE *fp;
    char temp;
    fp = fopen ("maze.txt", "r");
    if(mtr == NULL){
        printMtrIsNULLError();
    }
    else if(fp == NULL){
        printf("the file does not exist!!\n");
    }
    else{
        for (i = 0; i <M ;i ++) {
            j=0;
            while (((temp=(char)fgetc(fp)) != EOF && temp!='\n')) { // read file to mtr columns until see \n char or EOF
                mtr[i][j] = temp;
                j++;
            }

        }
        for (i = 0; i <=M ;i ++) {
            for(j=N;j<=N;j++) {
                mtr[i][j]=' ';
            }
        }
        for(i=0;i<N;i++) mtr[M][i] = ' ';
    }
    fclose(fp);

}

void insertApples(char **mtr,int M,int N,int appleCount){
    int count = 0;
    int x,y;
    do{
        x = rand()%N;
        y = rand()%M;
        if(mtr[y][x] == ' '){
            mtr[y][x] = 'O';
            count++;
        }
    } while (count!=appleCount);



}
void printMtr(char **mtr, int M,int N){
    int i,j;
    if(mtr == NULL){
        printMtrIsNULLError();
    }
    else{
        for (i=0;i<=M;i++){
            for(j=0;j<=N;j++){
                printf("%c",mtr[i][j]);
            }
            printf("\n");
        }
    }
}

int findRows(){
    int rows=0;
    FILE *fp;
    char c;
    fp = fopen ("maze.txt", "r");
    if(fp == NULL) return -9999;
    c = (char)getc(fp);
    rows++;
    while (c != EOF){
        c = (char)getc(fp);
        if(c=='\n') rows++;
    }

    fclose(fp);
    return rows;
}

int findColumns(){
    int columns=0;
    FILE *fp;
    char c;
    fp = fopen ("maze.txt", "r");
    if(fp == NULL) return -9999;
    c = (char)getc(fp);
    while (c != '\n'){
        c = (char)getc(fp);
        columns++;
    }
    fclose(fp);
    return columns;
}

void printMtrIsNULLError(){
    printf("\n!!mtr is null!!\n");
}

void freeMtr(char **mtr){
    int i;
    int size1 = sizeof(mtr)/sizeof(mtr[0]);
    for(i=0; i<size1; i++) {
        free(mtr[i]);
    }
    free(mtr);
}