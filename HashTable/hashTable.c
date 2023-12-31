
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
//sqrt() function from math.h library is used to when calculating a prime number for table size,
//because checking if a number is prime until it's root is more efficient
#include <string.h>

int Run(int mod);

typedef struct node{
    char *userName;
    int isDeleted;
}NODE;


int main() {
    int mod;
    do{
        printf("lutfen mod secin.\n1.normal mod\n2.debug modu\n3.cikis\n");
        scanf("%d",&mod);
        if(mod==1 || mod==2){
            Run(mod);
        }
        else if(mod!=3){
            printf("gecersiz girdi, lutfen tekrar girin!\n");
        }
    } while (mod!=3);
    return 0;
}


//print table 
//inputs : table, table size
void viewTable(NODE *table, int M){
    int i;
    for(i=0;i<M;i++){
        if(table[i].isDeleted==0 && table[i].userName!=NULL)
            printf("%d. %s\n",i,table[i].userName);
        else
            printf("%d. ------\n",i);
    }
}

//finds a prime number that is suitable for table size
//inputs number of elemnts (N), load factor
//return: prime number(table size)
int findSuitablePrimeNumber(float N,float loadfactor){
    int num = N/loadfactor;
    int i=2;
    num--;
    while (i<sqrt(num)){ //might not be the most efficient way to this...
        num++;
        i=2;
        while(num%i!=0 && i<sqrt(num)) i++;
    }
    printf("tablo buyuklugu %d olarak secildi\n",num);
    return num;
}


//create table, initalize it's values
//inputs: pointer of table,table size
//return: table
NODE* initializeTable(NODE*table, int M){
    table = (NODE*) malloc((M)*sizeof (NODE));
    if(table==NULL) return NULL;
    int i;
    for(i=0;i<M;i++){
        table[i].userName = NULL;
        table[i].isDeleted = 0;
    }
    return table;
}

//create table
//inputs : table,load factor, number of elements, table size
//table size will be calculated within findSuitablePrimeNumber;
//return: tablo, M(table size)
NODE* createTable(NODE*table, float loadfactor, int N, int *M){
    float n = (float)N;
    *M = findSuitablePrimeNumber(n,loadfactor);
    table =  initializeTable(table,*M);
    return table;
}

//1. hash function
int hashFunction(unsigned long long value, int M){
    return value%M;
}

//2. hash function
int hashFunction2(unsigned long long value, int M){
    return 1+(value%(M-2));
}

//double hashing
int DoubleHash(unsigned long long value,int M,int i,int mod,char* userName){
    int h1= hashFunction(value,M);
    int h2= hashFunction2(value,M);
    int dh = (h1 + i*h2)%M;
    if(mod==2){
        printf("h1(\"%s\")%d\n",userName,h1);
        printf("h2(\"%s\")%d\n",userName,h2);
        printf("dh(\"%s\")%d\n",userName,dh);
    }
    return dh;
}

//by using Horner's method, transform given string
//into a integer value, so it can be hashed
//returns calculated value corresponding to userName 
unsigned long long numerizeUserName(char userName[]){
    int size = strlen(userName);
    int i=0,prime=17;
    unsigned long long total = 1*(userName[i]);//birler basama��n�n de�eri
    for(i=1;i<size;i++){
        total += ((userName[i])*prime); 
        prime*= prime;//prime karesi al
    }
    return total;
}


//search table for given userName
//return the index where search has stopped
int traverseTableNormalMod(NODE*table, char userName[], int M){
    unsigned long long numerizedUserName = numerizeUserName(userName);
    int i;
    int j=1;
    i = DoubleHash(numerizedUserName,M,j,1,userName);
            //if the element not deleted before or if it is not   //if userName's doesn't match      
            //equal to NULL, continue 							  //continue searching                          
    while ( (table[i].isDeleted==1 || table[i].userName!=NULL) && strcmp(table[i].userName,userName) != 0 && i!=M){
        j++;//increase j value to recall hash function                                      //if table size not reached
        i = DoubleHash(numerizedUserName,M,j,1,userName);                                   //continue searching
    }
    return i;
}

//same as traverseTableNormalMod but prints some different outputs to terminal for debug purposes.
int traverseTableDebugMod(NODE*table, char userName[], int M){
    unsigned long long numerizedUserName = numerizeUserName(userName);
    int j=1;
    int i = DoubleHash(numerizedUserName,M,j,2,userName);

    if(table[i].userName != NULL && strcmp(table[i].userName,userName)==0) printf("Kullanici adi %d konumunda bulundu.\n",i);
    else printf("Kullanici adi %d konumunda bulunamadi.\n",i);

    while ( (table[i].isDeleted==1 || table[i].userName!=NULL) && strcmp(table[i].userName,userName) != 0 && i!=M){
        j++;
        i = DoubleHash(numerizedUserName,M,j,2,userName);
        if(table[i].userName != NULL && strcmp(table[i].userName,userName)==0) printf("Kullanici adi %d konumunda bulundu.\n",i);
        else printf("Kullanici adi %d konumunda bulunamadi.\n",i);
    }
    return i;
}

//call traverseTable function depending on mod
//mod = 1 normal 
//mod = 2 debug 
int traverseTable(NODE*table, char userName[], int M, int mod){
    int i;
    if(mod==1)
        i= traverseTableNormalMod(table,userName,M);
    else
        i= traverseTableDebugMod(table,userName,M);
    return i;
}

//at the index i of the table, initialize userName
//and assign values userName and isDeleted
//returns index
int initializeElement(NODE* table, char* userName, int i){
    table[i].userName = (char*)calloc(12,sizeof (char));
    strcpy(table[i].userName,userName);
    table[i].isDeleted = 0;
    return i;
}

//check if user exists, if not add it to the table
//if return is not negative, adding user to table was successfull
int addElementToTable(NODE*table, char userName[],int M,int mod){
    int i = traverseTable(table,userName,M,mod);
    if(table[i].userName == NULL){ //if userName at location i is NULL, place the user here
        return initializeElement(table,userName,i);
    }
    else if(strcmp(table[i].userName,userName)==0){
        if(table[i].isDeleted==1){ //if user has been deleted before,
            table[i].isDeleted=0;  //assign it as undeleted.
            return i;
        }
        else{ 
            printf("Bu kullanici adi zaten var!\n");
            return -1;
        }
    }
    else if(i==M){//table full
        printf("tablo dolu!\n");
        return -2;
    }
    else{
        printf("beklenmedik bir hata olustu\n");
        return -3;
    }
}

//get userName input, print userName location at table if adding was successfull
int addUser(NODE*table, int M,int mod){
    char *userName = (char*) calloc(12,sizeof(char));
    printf("lutfen kullanici adini, en fazla on karakter olacak sekilde giriniz:\n");
    scanf("%s",userName);
    printf("girelen kullanici adi: %s\n",userName);
    int i = addElementToTable(table,userName,M,mod);
    if(i>=0)
        printf("kullanici tabloda %d. eleman olarak eklendi\n",i);
    free(userName);
    userName = NULL;
    return i;
}

//remove given item from table by assigning isDeleted to 1
int removeItemFromTable(NODE*table, int M,char* userName,int mod){
    int i = traverseTable(table,userName,M,mod);
    if(table[i].userName!=NULL && strcmp(userName,table[i].userName)==0 && table[i].isDeleted == 0){
        table[i].isDeleted = 1;
        return i;
    }
    else{
        return -1;
    }
}

//input user to be deleted.
int deleteUser(NODE*table, int M,int mod){
    if (table==NULL) return -99;
    char *userName = (char*) calloc(12,sizeof(char));
    printf("lutfen silmek istedigiz kullanicinin adini giriniz: \n");
    scanf("%s",userName);
    int i = removeItemFromTable(table,M,userName,mod);
    if(i>=0)
        printf("%d. konumdaki \"%s\" isimli kullanici silindi \n",i,userName);
    else
        printf("bu isimde kullanici bulunamadi!\n");
    free(userName);
    userName = NULL;
    return i;
}

//search for given user
//if it exists in table, print it's location
int findUser(NODE*table, int M,int mod){
    if (table==NULL) return -99;
    char *userName = (char*) calloc(12,sizeof(char));
    printf("lutfen bulmak istedigiz kullanicinin adini giriniz: \n");
    scanf("%s",userName);
    int i = traverseTable(table,userName,M,mod);
    if(table[i].userName!=NULL && strcmp(userName,table[i].userName)==0 && table[i].isDeleted == 0){
        printf("\"%s\" isimli kullanicinin konumu : %d\n",userName,i);
        free(userName);
        userName = NULL;
        return 0;
    }
    else{
        printf("bu isimde kullanici bulunamadi!\n");
        free(userName);
        userName=NULL;
        return -1;
    }
}

//recreate the table by getting rid off deleted elements
NODE* reHash(NODE *table, int M,int mod){
    int count=0,i,newLocation;;
    for(i=0;i<M;i++){
        if(table[i].userName != NULL && table[i].isDeleted == 0){
            count++;//undeleted # elements
        }
    }
    //temporary array that elements will be stored
    NODE * tempArr = (NODE *) calloc(count,sizeof (NODE));
    int j=0;
    for(i=0;i<M;i++){
    	//if user not has been deleted, add it to tempArr
    	//deallocate it's userName are in the table
        if(table[i].userName != NULL && table[i].isDeleted == 0){
            if(mod==2) printf("%d konumundaki %s kullanicisi silinmemis\n",i,table[i].userName);
            tempArr[j].userName = (char*) calloc(12,sizeof (char));
            strcpy(tempArr[j].userName,table[i].userName);
            tempArr[j].isDeleted = 0;
            j++;
            free(table[i].userName);
            table[i].userName=NULL;
        }
        //if user has been deleted, doesn't add it
        //deallocate it's userName are in the table
        else if(table[i].userName != NULL && table[i].isDeleted == 1){
            if(mod==2) printf("%d konumundaki %s kullanicisi silinmis\n",i,table[i].userName);
            free(table[i].userName);
            table[i].userName=NULL;
        }
    }
    //deallocate previous table
    free(table);
    table=NULL;
    //create new table
    NODE* newTable = NULL;
    newTable = initializeTable(newTable,M);
    if(newTable==NULL) return NULL;
    for(i=0;i<count;i++){ //hash and place elements in tempArray
        newLocation = addElementToTable(newTable,tempArr[i].userName,M,1);
        if(mod==2) printf("%s isimli kullanicinin tablodaki yeni yeri :%d\n",tempArr[i].userName,newLocation);
    }
    free(tempArr);//deallocate tempArray
    tempArr=NULL;
    return newTable;
}

int Run(int mod){
    int select=0,N,M;
    float loadfactor;
    NODE *table=NULL;
    printf("en fazla kac adet eleman tabloya eklenebilsin?\n");
    scanf("%d",&N);
    printf("lutfen 0 ila 1 arasinda load factor belirtin\n");
    scanf("%f",&loadfactor);
    table = createTable(table,loadfactor,N,&M);

    if(table!=NULL){
        printf("tablo basariyla olusturuldu!\n");
    } else{
        printf("tabloyu olustururken bir hata oldu!\n");
        return -1;
    }
    do {
        printf("Yapilacak islemi seciniz\n");
        printf("1)tabloya eleman ekle\n2)tablodan eleman sil\n3)tabloda eleman ara\n4)tabloyu goruntule\n5.reHash islemi yap\n"
               "0.cikis\n");
        scanf("%d",&select);
        if(select==1){
            addUser(table,M,mod);
        }
        else if(select==2){
            deleteUser(table,M,mod);
        }
        else if(select == 3){
            findUser(table,M,mod);
        }
        else if(select == 4){
            printf("\n------------------------------\n");
            printf("tablo:\n");
            viewTable(table,M);
            printf("\n------------------------------\n");
        }
        else if(select == 5){
            table = reHash(table,M,mod);
        }
        else if(select>5 ||select < 0){
            printf("yanlis operasyon sectiniz, lutfen tekrar secin!\n");
        }
    } while (select!=0);

    free(table);
    table=NULL;
    return 0;
}
