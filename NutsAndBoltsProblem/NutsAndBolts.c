//MEHMET KE�EC� 20011103
//8.11.23 ALGOR�TMA ANAL�Z� HW2 SORU: 2
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *allocateArray(int *ptr, int size);
void fillArrayRandomly(int *array,int n);
void printArray(int *array,int n);
void randomize ( int *array, int n );
void findMatches(int *key,int *lock,int l,int r);
void takeArrayInput(int*,int);

int main() {
    int *key=NULL,*lock=NULL,N,choice;

    printf("Please enter number of elements:\n");
    scanf("%d",&N);
    key = allocateArray(key, N);
    lock = allocateArray(lock,N);

    printf("Do you want to fill the array manually or automatically?\n");
    printf("1.Fill manually\n2.Fill automatically\n");
    scanf("%d",&choice);
    if(choice==1){
        printf("please enter key values:\n");
        takeArrayInput(key,N);
        printf("please enter lock values:\n");
        takeArrayInput(lock,N);
    }
    else{

        fillArrayRandomly(key,N);
        fillArrayRandomly(lock,N);

        randomize(lock,N);
        //fillArrayRandomly fonksiyonunda zaten randomize() da �a��r�l�yor
        //ancak iki dizide de de�erler ayn� s�ra ile olu�uyor.
        //bu sorunu a�mak i�in lock dizisini bir kere daha randomize ettim.
    }

    printf("BEFORE MATCHING:\n");
    printf("keys:\n");
    printArray(key,N);
    printf("\nlocks:\n");
    printArray(lock,N);
    printf("\n---------------------------------------------------\n");

    findMatches(key,lock,0,N-1);

    printf("AFTER MATCHING:\n");
    printf("keys:\n");
    printArray(key,N);
    printf("\nlocks:\n");
    printArray(lock,N);

    return 0;
}

//diziyi kullan�c�dan girdi olarak al�r
void takeArrayInput(int *arr,int size){
    int i;
    for(i=0;i<size;i++){
        scanf("%d",&arr[i]);
    }
}

//rastgele pivot se�er, ancak bu fonksiyon kullan�lmam��t�r.
int choosePivot(int *arr,int left,int right){
    srand ( time(NULL) );
    int i;
    i = rand() % (right-left+1);
    return i;
}

//verilen pointerdan dinamik bir �ekilde verilen boyutta
//dizi allocate eder
int *allocateArray(int *ptr, int size){
    if(ptr==NULL)
        ptr = (int*)malloc(sizeof(int )*size);
    return ptr;
}

//verilen adreslerdeki de�erleri birbirleriyle de�i�tirir
void swap (int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//verilen diziyi shuffle eder
void randomize ( int *array, int n ){
    srand ( time(NULL) );
    int i,j;
    for (i = n-1; i > 0; i--)
    {
        j = rand() % (i+1);
        swap(&array[i], &array[j]);
    }
}

//verilen diziyi her indisin iki kat� ile doldurur,
//daha sonra elemanlar� shuffle etmek i�in randomize()
//fonksiyonunu �a��r�r
void fillArrayRandomly(int *array,int n){
    int i;
    for(i=0;i<n;i++){
        array[i] = i*2;
    }
    randomize(array,n);
}

//b dizisinden bir pivot kullanarak a dizisini
//pivota g�re s�ralar ve yeni pivotu d�ner
//l=left,r=right,pivot = pivotun indisi
int partition(int *a,int *b,int l,int r,int pivot){

    int i = l,j;
    for( j = l; j <r; j++){
        if (a[j] < b[pivot]){
            swap(&a[i],&a[j]);
            i++;
        }
        else if(a[j] == b[pivot]){ //pivota kar��l�k gelen eleman� en sa�a yerle�tirir
            swap(&a[j],&a[r]);
            j--;
            //�u anki j indisine yeni bir say� ta��nd���
            //i�in ve bu say�y� da pivot de�eri ile
            //kar��la�t�rabilmek i�in j de�erini bir azalt
        }
    }
    swap(&a[i],&a[r]); //pivota kar��l�k gelen de�eri yerine yerle�tirir

    return i;//i de�eri yeni pivotumuz olarak kullan�labilir
}

//quick sort gibi �al��an, recursive fonksiyon
//l = left, r = right
void findMatches(int *key,int *lock,int l,int r){

    int pivot;//pivotun indisi

    if(l<r){

        pivot = r; //pivotu en sa�daki eleman olarak se�

        //key dizisini partition et, yeni pivot se�
        pivot = partition(key,lock,l,r,pivot);
        //lock dizisini key'den se�ilen
        //pivot ile partition et
        partition(lock,key,l,r,pivot);

        findMatches(key,lock,l,pivot-1);
        findMatches(key,lock,pivot+1,r);
    }

}

//verilen pointerdaki diziyi yazd�r�r
void printArray(int *array,int n){
    int i;
    if(array!=NULL){
        for(i=0;i<n;i++){
            printf("%d ",array[i]);
        }
    }
}
