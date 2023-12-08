#include <stdio.h>
#include <stdlib.h>
#define SIZE 100
int** allocateMatrix(int M, int N);
void enterGraphData(int **mtr, int edges);
void runDFS(int **mtr,int start,int nodes);
void printMtr(int **mtr, int nodes);
void runBFS(int **mtr, int nodes,int start);
//Functions to implement BFS using queue
struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);
struct queue {
    int items[SIZE];
    int front;
    int rear;
};

int main() {
    int decision;
    int **mtr; //cost adj matrix pointer to store graph data
    int edges,nodes;
    do {
        printf("Please choose your operation:\n");
        printf("1.Enter Graph.\n2.Print Cost Adjenct Matrix.\n3.Run DFS.\n4.Run BFS.\n");
        scanf("%d",&decision);
        switch (decision) {
            case 1:
                printf("Please enter number of nodes graph \n");
                scanf("%d",&nodes);
                printf("Please enter number of edges graph \n");
                scanf("%d",&edges);
                mtr = allocateMatrix(nodes,nodes); // dynamically allocate cost adj matrix
                enterGraphData(mtr,edges);
                break;
            case 2:
                printMtr(mtr,nodes);
                break;
            case 3:
                runDFS(mtr,0,nodes);
                break;
            case 4:
                runBFS(mtr,nodes,0);
                break;
        }


    } while (decision != 0);



    return 0;
}
void runDFS(int **mtr,int start,int nodes){
    int i;
    printf("visited node : %d\n",start);
    for(i=0;i<nodes;i++){
        if(mtr[start][i]!=0){
            mtr[start][i] = 0;
            runDFS(mtr,i,nodes);
        }
    }
}

void runBFS(int **mtr, int nodes,int start) {
    struct queue* q = createQueue();
    int i;
    int temp;
    for(i=0;i<nodes;i++)
        mtr[i][start] = 0;
    int current;
    while (!isEmpty(q)) {
       // printQueue(q);
        current = dequeue(q);
        for(i=0;i<nodes;i++)
            mtr[i][start] = 0;
        printf("Current node:  %d\n", current);
        for(i=0;i<nodes;i++)
            if(mtr[i][current]!=0)
                enqueue(q,i);
        //struct node* temp = graph->adjLists[currentVertex];
    }
}
int** allocateMatrix(int M, int N){
    int **mtr = (int**) malloc((M+1)*sizeof(int*));
    int i;
    for(i=0;i<M;i++)
        mtr[i] = (int*)malloc((N+1)*sizeof (int ));

    int j;

    for(i=0;i<M;i++)
        for(j=0;j<M;j++)
          mtr[i][j] = 0; //set matrix values

    return mtr;
}

void enterGraphData(int **mtr, int edges){
    int i;
    int x,y;
    for(i=0;i<edges;i++) {
        printf("Please enter edges in this format: node1 node2\n");
        scanf("%d %d", &y, &x);
        mtr[y][x] = 1;
    }
}
void printMtr(int **mtr, int nodes){
    int i,j;
    for(i=0;i<nodes;i++){
        for(j=0;j<nodes;j++){
            printf(" %d ",mtr[i][j]);
        }
        printf("\n");
    }
}

struct queue* createQueue() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

// Check if the queue is empty
int isEmpty(struct queue* q) {
    if (q->rear == -1)
        return 1;
    else
        return 0;
}

// Adding elements into queue
void enqueue(struct queue* q, int value) {
    if (q->rear == SIZE - 1)
        printf("\nQueue is Full!!");
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

// Removing elements from queue
int dequeue(struct queue* q) {
    int item;
    if (isEmpty(q)) {
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}
