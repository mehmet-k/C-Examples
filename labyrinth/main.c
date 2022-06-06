#include <stdio.h>
#include <stdlib.h>
#define APPLE_COUNT 3

int createMtr(int *mtr);

int main() {
    int **mtr=NULL;
    createMtr(*mtr);
    if(mtr == NULL){
        printf("Couldn't read the file!\n");
    }
    else{

    }

    return 0;
}


int createMtr(int **mtr){
    FILE *fp;
    fp = fopen ("labirent", "rt");
    if (fp == NULL) return 0;

}