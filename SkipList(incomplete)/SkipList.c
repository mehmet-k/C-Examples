#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct list{
    int level;
    int data;
    struct list *next;
    struct list *below;
}LIST;

int search_in_list(LIST *,int );
void view_list_elements(LIST *head);
void add_num(LIST**);
void remove_num(LIST**);
void create_shortcuts(LIST *head,LIST *);
int generate_random_num(int );
void create_node(LIST**,int,int);
#define MAX 100
int main() {
    int decision1,num = 1;
    LIST *head=NULL;
    LIST *shortcuts=NULL;
    LIST *array[50];
    do{
        printf("Please choose what would you like to do:\n");
        printf("    1.Add a new number to the list.\n");
        printf("    2.Remove a number from the list.\n");
        printf("    3.Find if a specific number exists.\n");
        printf("    4.See all of the numbers in the list.\n");
        printf("    5.Exit\n");
        scanf("%d",&decision1);

        switch (decision1) {
            case 1:
                printf("2");
                printf("Please enter the number you would like to add: ");
                scanf("%d",&num);
                create_node(&head,num,1);
                create_shortcuts(head,shortcuts);
                break;
            case 2:
                remove_num(&head);
                create_shortcuts(head,shortcuts);
                break;
            case 3:
                printf("Data of list element you would like to check?");
                scanf("%d",&num);
                if(search_in_list(head,num)==-1){
                    printf("There is no element with such data in the list.\n");
                }
                else(printf("That element exists in the list\n"));
                break;
            case 4:
                view_list_elements(head);
                break;
            case 5:
                printf("exiting...");
                break;
            default:
                printf("unrecognized input!");
                break;
        }


    } while (decision1 != 5);

    return 0;
}

int search_in_list(LIST *head,int num){



    if (head == NULL){
        return -1;
    }
    else {
        return head->data;
    }
}

void view_list_elements(LIST *head){
    printf("---------------\n");
    while(head!=NULL) {
        printf(" %d " , head->data);
        head = head->next;
    }
    printf("---------------\n");
}

int generate_random_num(int list_size){
    time_t t1;
    int number;
    srand (  (unsigned)time (&t1));
    number = rand()%list_size;
    return number;
}

void create_shortcuts(LIST *head,LIST *shortcuts){
    int list_size= 0;
    int i=0,j;
    int counter;
    int random_num ;
    int level_counter=2;
    LIST *tmp;
    LIST *levels = malloc(sizeof (LIST));
    if(head!=NULL){

        shortcuts = calloc(1,sizeof(LIST));
        tmp = head;
        while(tmp!=NULL){
            tmp = tmp->next;
            list_size++;
        }

        while(list_size>1){
            counter = 0;
            while(counter<=list_size/2){
                random_num = generate_random_num(list_size);
                counter++;
                tmp = head;
                for(j=0;j<random_num;j++) {
                    tmp = tmp->next;
                }
                levels[counter] = *tmp;
                levels[counter].level = level_counter;
                levels = realloc(levels,counter);
                //shortcuts[i] = *tmp;
                i++;
            }
            level_counter++;
            list_size /= 2;
        }
    }


}
int find_order(LIST *head,int num){
    int i=0;
    while(head!=NULL && num > head->data) {
        head = head->next;
        i++;
    }
    if(i==0){
        return 1;
    }
    else if(head == NULL){
        return 2;
    }
    else{
        return i;
    }
}
void create_node(LIST **head,int num,int level){
    int i;
    LIST *element = malloc(sizeof (LIST));
    element->data = num;
    element->level = level;
    int status = find_order(*head,num);
    if(status==1){//adding node to start
        element->next=*head;
        *head=element;
    }
    else if(status==2){//adding node to end
        LIST *tmp ;
        tmp = *head;
        while(tmp->next!=NULL){
            tmp = tmp->next;
        }
        tmp->next = element;
        element->next = NULL;
    }
    else{//adding node to middle
        LIST *tmp=*head;
        i=0;
        while(i<status){
            tmp = tmp->next;
            i++;
        }
        element->next = tmp->next;
        tmp->next = element;
    }

}
void remove_num(LIST **head) {
    int num;
    printf("Please enter the number you would like to remove: ");
    scanf("%d", &num);

}