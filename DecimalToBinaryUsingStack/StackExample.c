#include <stdio.h>
#define STACK_SIZE 64
#define ERROR -999
void push(int stack[],int size,int *stack_pointer,int value);
int pop(int stack[],int size,int *stack_pointer);

int main() {
    int stack[STACK_SIZE] = {0};
    int base = 0,count,if_neg;
    int *stack_pointer;
	stack_pointer = &base;
    char binary_string[STACK_SIZE];
    int i,j,remainder,number,decision,flag,tmp;
    do{
    	*stack_pointer = 0;
        printf("Please enter the number: ");
        scanf("%d",&number);
        count = 0;
        if(number<0){
            if_neg = 1;
            number *= -1;
        }
        while(number > 0 ){ //sayıyı binarye çevirmek için stack'e push işlemleri yapıyorum
            push(stack,STACK_SIZE,stack_pointer,number%2);
            number /= 2;
            count ++;//sayının kaç bitle ifade edileceğini bulmak için tuttuğum değişken
        }

		printf("\n");

        i = 4;
        j = 1;
        while(i<count){//sayının kaç bitle ifade edileceğini buluyorum
            i *= j;
            j++;
        }
        for(j=0;j<i-count-1;j++){//binary string'in başına gereken kadar 0 koyuyorum
            binary_string[j] = '0';
        }
        for(j=i-count-1;j<i;j++){ //binary string'e sayının string karşılığını kaydediyorum
            //tmp = pop(stack,STACK_SIZE,stack_pointer) ;
            binary_string[j] =  pop(stack,STACK_SIZE,stack_pointer) + '0';
        }
        binary_string[i] = '\0';


        if(if_neg==1){
            //two's complement işlemi
            for(j=0;j<i;j++){
                if(binary_string[j]=='0'){
                	binary_string[j] = '1';
				}
                else{
                	binary_string[j] = '0';
				}
            }
            remainder = '1';
            for(j=i-1;j>=0;j--) {
                if (binary_string[j] == '1' && remainder == '1') {
                    binary_string[j] = '0';
                }
                else if (binary_string[j] == '0' && remainder == '1' ) {
                    binary_string[j] = '1';
                    remainder = '0';
                }
            }
        }
        printf("Binary representation of your input: ");
        for(j=0;j<i;j++){
            printf(" %c ",binary_string[j]);
        }
        printf("\n");
		flag = 0;
		//printf("sp : %d\n--------------\n",*stack_pointer); //FOR DEBUG PURPOSES
		*stack_pointer += 1;
        for(j=0;j<i;j++){
            if(binary_string[j] == '1'){
            	push(stack,STACK_SIZE,stack_pointer,1);
			}
            else if(binary_string[j] == '0'){
                if(*stack_pointer <= 0){
                	flag = 1;
                }
                else{
                	tmp = pop(stack,STACK_SIZE,stack_pointer);
                	flag = 0;
				}
            }
			printf("sp : %d\n",*stack_pointer);
        }

        /*
        printf("j=%d\n",j);
        printf("\nstack: ");//FOR DEBUG PURPOSES
        for(j=0;j<*stack_pointer;j++){
        	printf("%d" , stack[j]);
		}
		printf("\n");
        
        printf("\n");
		printf("sp : %d\n",*stack_pointer);
		*/
		
        if( *stack_pointer == 0 && flag == 0){
           printf("Zeros and ones are equal in binary represenatation.\n");
        }
        else if(*stack_pointer>0){
            printf("There are more ones in binary representation.\n");
        }
        else if(*stack_pointer == 0 && flag == 1 ){
             printf("There are more zeros in binary representation.\n"); 
        }
        else{
            printf("Undefined case.\n");
        }

        printf("\n");
        printf("Do you want to try with another number?\n   Type 1 for yes.\n   Type 0 for no\n");
        scanf("%d",&decision);
    } while (decision!=0);

    return 0;
}

void push(int stack[],int size,int *stack_pointer,int value){
    if(*stack_pointer>STACK_SIZE){
        printf("STACK OVERFLOW!\n");
    }
    else{
        stack[*stack_pointer] = value;
		*stack_pointer = (*stack_pointer) + 1;
        //printf("stack pointer: %d\n", *stack_pointer);
    }
}

int pop(int stack[],int size,int *stack_pointer){
    if(*stack_pointer<0){
        printf("STACK UNDERFLOW!\n");
    }
    else{
        int value = stack[*stack_pointer];
		*stack_pointer -= 1;
        //stack[*stack_pointer] = 0;
        //printf("stack pointer: %d\n", *stack_pointer);
        return value;
    }
    return ERROR;
}
