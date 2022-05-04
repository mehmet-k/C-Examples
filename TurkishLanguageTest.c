#include <stdio.h>
#define STR_SIZE 100
int check_connexion(char a, char b);
int main() {
    char string[STR_SIZE] = {0},str_tmp[STR_SIZE],str_tmp2[STR_SIZE],char_tmp;
    int connex_locations[STR_SIZE];
    int i;
    printf("sentence?\n");
    gets(string);

    i = 0;
    int j= 0;
    while(string[i+1] != '\0'){
        if(string[i] == ' '){
            if(check_connexion(string[i+1],string[i-1]) == 1){
                connex_locations[j] = i;
                j++;
            }
        }
        i++;
    }
    int k,y;
    printf("connexions: \n");
    for(i=0;i<j;i++){
        k=connex_locations[i]-1;
        y=0;
        while(k != -1 && string[k] != ' '){
            str_tmp[y] = string[k];
            k--;
            y++;
        }
        str_tmp[y] = '\0';
        for(k=0;k<y/2;k++){
            char_tmp = str_tmp[k] ;
            str_tmp[k] = str_tmp[y-k-1];
            str_tmp[y-k-1] = char_tmp;
        }
        k=connex_locations[i]+1;
        y=0;
        while(string[k] != ' ' && string[k] != '\0'){
            str_tmp2[y] = string[k];
            k++;
            y++;
        }
        str_tmp2[y] = '\0';
        printf("%d. connexion is between: %s and %s\n", i+1,str_tmp,str_tmp2);
    }


    return 0;
}

int check_connexion(char a, char b){
    int state = 0;
   if(a>='a'){
        a -= 32;
   }
   if(b>='a'){
        b -= 32;
   }

    if(a=='A' || a=='E' || a== 'I' || a=='O' || a== 'U'){
        if(b!='A' && b!='E' && b!= 'I' && b!='O' && b!= 'U'){
            state = 1;
        }
    }
    return state;
}