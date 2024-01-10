/*
	MEHMET KEÇECÝ 
	20011103
	17.12.2023
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 255

#define SKIPX 1
#define SKIPY 2
#define SEQ 3
#define FORK_HERE 4


char* createStringDynamically(int*);
int** createMatrixDynamically(int m,int n);
void freeMatrix(int**mtr,int size1);
void printFormattedMatrix(int** mtr,char*str1,char*str2);
int lcs(int **mtr, int **flags,char *s1,char *s2);
void printLCS(int** flags, char* prevString, char* str1, int i,int j,int count,int max);

int main() {
    int  **mtr,**flags,size1,size2;
    char *str1,*str2;
    int max;
    int ex;
    do{
        printf("input first string:\n");
        str1 = createStringDynamically(&size1);
        
		printf("input second string:\n");
        str2 = createStringDynamically(&size2);
        
        printf("str1:%s\nstr2:%s\n",str1,str2);
        
		size1++;
        size2++;
        mtr = createMatrixDynamically(size1,size2);
        flags = createMatrixDynamically(size1,size2);
        
		printf("initial matrixes:\n");
        printFormattedMatrix(mtr,str1,str2);
		printFormattedMatrix(flags,str1,str2);
    
		max = lcs(mtr,flags,str1,str2);
        printf("result:\n");
        if(max == -2) printf("at least one the strings is NULL!!\n");
        else if(max == -1) {
            printf("max substring :%d\n",0);
            printf("there is no LCS!\n");
        }
        else{
            printf("max substring :%d\n",max);
            printf("substrings:\n");
            printLCS(flags,"",str1, strlen(str1), strlen(str2),0,max);
        }
        //FREE VARIABLES
        free(str1);
        str1=NULL;
        free(str2);
        str2=NULL;
        freeMatrix(mtr,size1);
        freeMatrix(flags,size1);

        printf("press 0 to exit or any key to keep trying: \n");
        scanf("%d",&ex);
    } while (ex!=0);

    return 0;
}
//free given matrix
//IN : matrix pointer, size of rows
void freeMatrix(int**mtr,int size1){
    int i;
    for(i=0;i<size1;i++){
        free(mtr[i]);
        mtr[i] = NULL;
    }
    free(mtr);
    mtr = NULL;
}
/*
	Put string 1 horizontally, string 2 vertically,
	and print matrix in the middle
	IN : matrix pointer, strign 1 and string 2
*/
void printFormattedMatrix(int** mtr,char*str1,char*str2){
    int m = strlen(str1);
    m++;
    int n = strlen(str2);
    n++;
    int i,j;
    printf("    ");
    for(i=0;i<n;i++){
        printf(" %c",str2[i]);
    }
    printf("\n");
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(j==0 && i!=0)
                printf("%c ",str1[i-1]);
            else if(i==0 && j==0)
                printf("  ");
            printf(" %d",mtr[i][j]);
        }
        printf("\n");
    }
}

/*
	with given size m and n,
	allocate a matrix
	IN : column m, rows n
*/
int** createMatrixDynamically(int m,int n){
    int** mtr = (int**) calloc(m,sizeof (int*));
    int i;
    for(i=0;i<m;i++){
        mtr[i] = (int*) calloc(n,sizeof (int));
    }
    return mtr;
}

/*
	read string from user to buffer, get it's size
	and allocate an string with that size
	IN: adress of an integer
	RETURNS: pointer of string and size of this string
			 by pointer
	
*/
char* createStringDynamically(int *size){
    char buffer[BUFFER];
    scanf("%s",buffer);
    *size = strlen(buffer);
    char* string = (char*)calloc(*size,sizeof (char ));
    strcpy(string,buffer);
    return string;
}

//IN: a , b
//RETURNS: max of (a,b)
int max(int a, int b){
    if(a>=b) return a;
    else return b;
}

/*
	calculate length of LCS, mark label matrix
	accordingly
	IN: mtr = values, flags= labels matrixes,
		s1 = string1, s2 = string2
	RETURNS : length of LCS
*/
int lcs(int **mtr, int **flags,char *s1,char *s2){
    int s1size = strlen(s1);
    int s2size = strlen(s2);
    int maxx=-1;
    int i,j;
    if(s1==NULL || s2 == NULL) return -2;
    else if(s1size==1 && s2size==1 && strcmp(s1,s2)!=0) return -1;
    for(i=0;i<s1size+1;i++){
        for(j=0;j<s2size+1;j++){
            if(i == 0 ){
                mtr[i][j] = 0;
                flags[i][j] = SKIPY;
            }
            else if(j == 0){
                mtr[i][j] = 0;
                flags[i][j] = SKIPX;
            }
            else if(s1[i-1]==s2[j-1]){
                mtr[i][j] = 1 + mtr[i-1][j-1];
                maxx = max(maxx,mtr[i][j]);
                flags[i][j] = SEQ;//LABEL : INCLUDED IN SEQUENCE
            }
            else if(flags[i][j-1] == SEQ && flags[i-1][j] == SEQ){
                mtr[i][j] = mtr[i-1][j];
                flags[i][j] = FORK_HERE; //HAS TWO POSSIBLE SOURCES
            }
            else if(  mtr[i-1][j] >  mtr[i][j-1]){
                mtr[i][j] = mtr[i-1][j];
                flags[i][j] = SKIPX;
            }
            else {
                mtr[i][j] = mtr[i][j-1];
                flags[i][j] = SKIPY;
            }
        }
        printf("Iteration : %d\n",i);
        printf("values:\n");
        printFormattedMatrix(mtr,s1,s2);
        printf("flags:\n");
        printFormattedMatrix(flags,s1,s2);
        printf("----------------------------------\n");
    }
    return maxx;
}

/*
	prints string in reverse
	IN: string , count = size
*/
void putStringInReverse(char * string,int count){
    printf("\n");
    int k;
    for (k = count; k >= 0 ; --k) {
        printf("%c",string[k]);
    }
    printf("\n");
}

/*
	in label matrix, iterate until fork label or matrix ends
	IN: flags = label matrix, buffer = LCS string, str1 = string given by user,
		i,j = indexes of matrix, count = common letters found so far
*/
void iterateUntilFork(int** flags,char*buffer, char* str1, int *i,int *j,int *count){
    while( (*i >= 1 || *j>=1 )  && flags[*i][*j] != FORK_HERE  ){
        if(flags[*i][*j] == SEQ ){
            buffer[*count] = str1[*i-1];
            (*count)++;
            (*i)--;
            (*j)--;
        }
        else if(flags[*i][*j] == SKIPX){
            (*i)--;
        }
        else{ // flags[i][j] == SKIPY
            (*j)--;
        }
    }
}

/*
	prints LCS for given flags(labels) matrix
	IN: str1 =	string that is horizontal values of matrix
				required to get common letters
		prevString =required to save previous string in case of
					recursive call. If you are calling this func-
					tion in main(), just pass ""
		i,j= indexes of flags, if you call this function in main()
			 pass 0 and 0
		count = count common letters, if you call this function in main()
			 pass 0
		max = length of lcs
*/
void printLCS(int** flags, char* prevString, char* str1, int i,int j,int count,int max){
    char* buffer = (char*) calloc(BUFFER,sizeof (char));
    strcpy(buffer,prevString);

    iterateUntilFork(flags,buffer,str1,&i,&j,&count);

    if(flags[i][j] == FORK_HERE ){
        printLCS(flags,buffer,str1,i-1,j,count,max);
        printLCS(flags,buffer,str1,i,j-1,count,max);
    }
    else if(max==count){
    	putStringInReverse(buffer,count);
	} 

    free(buffer);
    buffer = NULL;

}
