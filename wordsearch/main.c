#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define SIZE 10
#define WORD_SIZE 4

void initializeMtr(char mtr[][SIZE],int size);
int wordSearch(char mtr[][SIZE], char word[]);
void printMtr(char mtr[][SIZE]);

int main() {

    srand(time(NULL));
    int r = rand();

    int i,j;
    int decision;
    char mtr[SIZE][SIZE];

    printf("Do you want to fill the matrix randomly or enter inputs by hand?\n1."
           "Generate randomly.\n2.Enter by hand.\n");
    scanf("%d",&decision);

    if(decision==1){
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                mtr[i][j] = 'a' + rand()%26;
            }
        }
    }
    else{
        initializeMtr(mtr,SIZE);
    }

    printf("your matrix:\n");
    printMtr(mtr);

    printf("enter word you want to search exactly as 4 characters : \n  ");
    char word[SIZE];
    scanf("%s",word);


    if(wordSearch(mtr,word)==0)
        printf("word doesn't exists");
    else
        printf("word exists");


    return 0;
}

void initializeMtr(char mtr[][SIZE],int size){
    int i,j;
    printf("please fill the matrix\n");
    for(i=0;i<SIZE;i++)
        for(j=0;j<SIZE;j++)
            scanf("%c",&mtr[i][j]);
}

void printMtr(char mtr[][SIZE]){
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            printf("%c",mtr[i][j]);
        }
        printf("\n");
    }

}

int searchLeft(char mtr[][SIZE], char word[],int i,int j){
    int wordIndex=0;
    while (word[wordIndex] == mtr[i][j] && wordIndex < WORD_SIZE){
        wordIndex++;
        j--;
    }
    if(wordIndex==WORD_SIZE-1 && word[wordIndex] == mtr[i][j]) return 1;
    else return 0;
}

int searchRight(char mtr[][SIZE], char word[],int i,int j){
    int wordIndex=0;
    while (word[wordIndex] == mtr[i][j] && wordIndex < WORD_SIZE){
        wordIndex++;
        j++;
    }
    if(wordIndex==WORD_SIZE-1 && word[wordIndex] == mtr[i][j]) return 1;
    else return 0;

}

int searchUp(char mtr[][SIZE], char word[],int i,int j){
    int wordIndex=0;
    while (word[wordIndex] == mtr[i][j] && wordIndex < WORD_SIZE){
        wordIndex++;
        i--;
    }
    if(wordIndex==WORD_SIZE-1 && word[wordIndex] == mtr[i][j]) return 1;
    else return 0;

}

int searchDown(char mtr[][SIZE], char word[],int i,int j){
    int wordIndex=0;
    while (word[wordIndex] == mtr[i][j] && wordIndex < WORD_SIZE){
        wordIndex++;
        i++;
    }
    if(wordIndex==WORD_SIZE-1 && word[wordIndex] == mtr[i][j]) return 1;
    else return 0;
}

int wordSearch(char mtr[][SIZE], char word[]){
    int i,j;
    int flag = 0;
    i=0;
    while(flag == 0 && i<SIZE){
        j=0;
        while (flag == 0 && j<SIZE){
            if(j-WORD_SIZE>-1) flag = searchLeft(mtr,word,i,j);
            if(j+WORD_SIZE<SIZE) flag = searchRight(mtr,word,i,j);
            if(i-WORD_SIZE>-1) flag = searchUp(mtr,word,i,j);
            if(i+WORD_SIZE<SIZE) flag = searchDown(mtr,word,i,j);
        }
    }
    return flag;
}
