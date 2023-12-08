//MEHMET KEÇECÝ 20011103
//8.11.23 ALGORÝTMA ANALÝZÝ HW2 SORU: 2
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
        //fillArrayRandomly fonksiyonunda zaten randomize() da çaðýrýlýyor
        //ancak iki dizide de deðerler ayný sýra ile oluþuyor.
        //bu sorunu aþmak için lock dizisini bir kere daha randomize ettim.
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

//diziyi kullanýcýdan girdi olarak alýr
void takeArrayInput(int *arr,int size){
    int i;
    for(i=0;i<size;i++){
        scanf("%d",&arr[i]);
    }
}

//rastgele pivot seçer, ancak bu fonksiyon kullanýlmamýþtýr.
int choosePivot(int *arr,int left,int right){
    srand ( time(NULL) );
    int i;
    i = rand() % (right-left+1);
    return i;
}

//verilen pointerdan dinamik bir þekilde verilen boyutta
//dizi allocate eder
int *allocateArray(int *ptr, int size){
    if(ptr==NULL)
        ptr = (int*)malloc(sizeof(int )*size);
    return ptr;
}

//verilen adreslerdeki deðerleri birbirleriyle deðiþtirir
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

//verilen diziyi her indisin iki katý ile doldurur,
//daha sonra elemanlarý shuffle etmek için randomize()
//fonksiyonunu çaðýrýr
void fillArrayRandomly(int *array,int n){
    int i;
    for(i=0;i<n;i++){
        array[i] = i*2;
    }
    randomize(array,n);
}

//b dizisinden bir pivot kullanarak a dizisini
//pivota göre sýralar ve yeni pivotu döner
//l=left,r=right,pivot = pivotun indisi
int partition(int *a,int *b,int l,int r,int pivot){

    int i = l,j;
    for( j = l; j <r; j++){
        if (a[j] < b[pivot]){
            swap(&a[i],&a[j]);
            i++;
        }
        else if(a[j] == b[pivot]){ //pivota karþýlýk gelen elemaný en saða yerleþtirir
            swap(&a[j],&a[r]);
            j--;
            //þu anki j indisine yeni bir sayý taþýndýðý
            //için ve bu sayýyý da pivot deðeri ile
            //karþýlaþtýrabilmek için j deðerini bir azalt
        }
    }
    swap(&a[i],&a[r]); //pivota karþýlýk gelen deðeri yerine yerleþtirir

    return i;//i deðeri yeni pivotumuz olarak kullanýlabilir
}

//quick sort gibi çalýþan, recursive fonksiyon
//l = left, r = right
void findMatches(int *key,int *lock,int l,int r){

    int pivot;//pivotun indisi

    if(l<r){

        pivot = r; //pivotu en saðdaki eleman olarak seç

        //key dizisini partition et, yeni pivot seç
        pivot = partition(key,lock,l,r,pivot);
        //lock dizisini key'den seçilen
        //pivot ile partition et
        partition(lock,key,l,r,pivot);

        findMatches(key,lock,l,pivot-1);
        findMatches(key,lock,pivot+1,r);
    }

}

//verilen pointerdaki diziyi yazdýrýr
void printArray(int *array,int n){
    int i;
    if(array!=NULL){
        for(i=0;i<n;i++){
            printf("%d ",array[i]);
        }
    }
}
