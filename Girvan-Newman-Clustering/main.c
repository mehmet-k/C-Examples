/*
 * MEHMET KEÇECİ
 * 20011103
 * 7.01.2023
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "DanglingPointer"

#define MAX_NODES 20

struct queue {
    int items[MAX_NODES];
    int front;
    int rear;
};
void printMatrix(int adjacencyMatrix[][MAX_NODES],int nodeCount);
int readGraphFromTXT(int adjacencyMatrix[][MAX_NODES]);
void iteration(int AdjMatrix[][MAX_NODES],float countMatrix[][MAX_NODES],int nodeCount,int t,int k);
int printCommunities(int AdjMatrix[][MAX_NODES],int nodeCount,int * flag, int t);

int main() {
    // Initialize the adjacency matrix
    int adjacencyMatrix[MAX_NODES][MAX_NODES] = {{0}};
    float countMatrix[MAX_NODES][MAX_NODES] = {{0}};

    int t=1,k=2;

    printf("t value: \n");
    scanf("%d",&t);

    printf("k value: \n");
    scanf("%d",&k);

    int nodeCount = readGraphFromTXT(adjacencyMatrix);
    printMatrix(adjacencyMatrix, nodeCount);

    iteration(adjacencyMatrix,countMatrix,nodeCount,t,k);
    return 0;
}

int charToIndex(char * label) {
    return label[0] - 'A';
}

int indexToCharValue(int index){
    return index+'A';
}
int readGraphFromTXT(int adjacencyMatrix[][MAX_NODES]){
    FILE *fp = fopen("graph.txt", "r");
    int nodeCount=0;
    char * token;
    char line[100];
    int a,b;
    // Open the file containing the graph data
    if (fp == NULL) {
        printf("Could not open file\n");
        return -1;
    }
    while (fgets(line, sizeof(line), fp) != NULL) {
        token = strtok(line,":");
        a = charToIndex(token);
        if(a>nodeCount) nodeCount=a;
        while(token[1]!=';'){
            token = strtok(NULL,",");
            b = charToIndex(token);
            adjacencyMatrix[a][b] = 1;
        }
    }
    fclose(fp);
    return nodeCount+1;
}

void printMatrix(int adjacencyMatrix[][MAX_NODES],int nodeCount){
    int i,j;
    for(i=0;i<nodeCount;i++){
        for(j=0;j<nodeCount;j++){
            printf("%d ",adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

void printMatrixFloat(float adjacencyMatrix[][MAX_NODES],int nodeCount){
    int i,j;
    for(i=0;i<nodeCount;i++){
        for(j=0;j<nodeCount;j++){
            printf("%.2f ",adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

// Create a queue
struct queue * createQueue() {
    struct queue * Q = malloc(sizeof (struct queue));
    Q->front = -1;
    Q->rear = -1;
    return Q;
}

// Check if the queue is empty
int isEmpty(struct queue* q) {
    if (q->rear == -1)
        return 1;
    else
        return 0;
}

void enqueue(struct queue* q, int value) {
    if (q->rear == MAX_NODES - 1)
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
        printf("Queue is empty");
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


// Print the queue
void printQueue(struct queue* q) {
    int i = q->front;

    if (isEmpty(q)) {
        printf("Queue is empty\n");
    } else {
        printf("Queue contains \n");
        for (i = q->front; i < q->rear + 1; i++) {
            printf("%d ", q->items[i]);
        }
        printf("\n");
    }
}

void destroyQueue(struct queue *q){
    free(q);
}

// BFS algorithm
int bfs(int AdjMatrix[][MAX_NODES],float scores[MAX_NODES],float countMatrix[][MAX_NODES],int nodeCount,int startNode) {
    int visited[MAX_NODES] = {0};
    int currentNode,i;
    int peopleCount=0;
    struct queue * Q = createQueue();

    visited[startNode] = 1;
    enqueue(Q, startNode);

    while (isEmpty(Q)==0) {
        currentNode = dequeue(Q);
        peopleCount++;
        for(i=0;i<nodeCount;i++){
            if(AdjMatrix[currentNode][i]!=0){
                scores[i]++; //calculate amount of possible ways to that node
            }
            if(AdjMatrix[currentNode][i]!=0 && visited[i]==0){
                enqueue(Q,i);
                visited[i] = 1;
            }
        }
    }
    destroyQueue(Q);
    return currentNode;//return last node visited
}

void zeroArray(float visited[MAX_NODES]){
    int i;
    for(i=0;i<MAX_NODES;i++) visited[i] = 0;
}

float calculateCreditOfNode(float creditsSoFar,float destScore,float startScore){
    return (1+creditsSoFar)*(destScore/startScore);
}

void calcCreditsRecursively(int AdjMtr[][MAX_NODES], float countMatrix[][MAX_NODES],float scores[MAX_NODES],int labels[MAX_NODES],
                            int isCalculated[MAX_NODES], int currentNode,int nodeCount,float prevCredits){
    int i;
    for(i=0;i<nodeCount;i++){
        //if this edge not already calculated or node hieararchy is lower than current node
        if(AdjMtr[currentNode][i] == 1 && labels[i]<labels[currentNode] && isCalculated[i]!=1 ){
            prevCredits = calculateCreditOfNode(prevCredits,scores[i],scores[currentNode]);
            countMatrix[currentNode][i] += prevCredits;
            isCalculated[i] = 1;
            calcCreditsRecursively(AdjMtr,countMatrix,scores,labels,isCalculated,i,nodeCount,prevCredits);
        }
        //if this edge not already calculated or node hieararchy is higher than current node
        else if(AdjMtr[currentNode][i] == 1 && labels[i]>labels[currentNode] && isCalculated[i]!=1 ){
            //if hiearchy is higher, it means that this node has no credits from before, so
            //set cretisSoFar to 0
            prevCredits = calculateCreditOfNode(0,scores[i],scores[currentNode]);
            countMatrix[currentNode][i] += prevCredits;
            isCalculated[i] = 1;
            calcCreditsRecursively(AdjMtr,countMatrix,scores,labels,isCalculated,i,nodeCount,prevCredits);
        }
    }
}

void calcCredits(int AdjMtr[][MAX_NODES], float countMatrix[][MAX_NODES],float scores[MAX_NODES], int lastNodeVisited,int startNode,int nodeCount){
    int labels[MAX_NODES] = {0};
    int calculated[MAX_NODES] = {0};
    int currentNode=startNode,i,labelCount = 1;
    struct queue * Q = createQueue();
    /*
     * BFS to label the nodes hierarchically
     * */
    enqueue(Q,currentNode);
    labels[currentNode] = labelCount;
    while (isEmpty(Q)==0) {
        labelCount++;
        currentNode = dequeue(Q);
        for(i=0;i<nodeCount;i++){
            if(AdjMtr[currentNode][i]==1 && labels[i]==0){
                enqueue(Q,i);
                labels[i] = labelCount;
            }
        }
    }
    /*
     * recursively calculate the edge credits with the help of labeled nodes
     * */
    calcCreditsRecursively(AdjMtr,countMatrix,scores,labels,calculated,lastNodeVisited,nodeCount,0);
}

float roundToOneDecimal(float num) {
    return roundf(num * 10) / 10; // Multiply by 10, round, then divide by 10
}

void calculateEdgeBetweness(int AdjMatrix[][MAX_NODES],float countMatrix[][MAX_NODES],int nodeCount){
    int i,j;
    float scores[MAX_NODES] = {0};
    int lastNodeVisited;
    for(i=0;i<nodeCount;i++){
        //calculate node scores by bfs
        lastNodeVisited = bfs(AdjMatrix,scores,countMatrix,nodeCount,i);
        //calculate edge betweness credits
        calcCredits(AdjMatrix,countMatrix,scores,lastNodeVisited,i,nodeCount);
        zeroArray(scores);
    }
    //merge edge credits of same edge
    //for example to get edge A - B:
    //matrix cell [A][B] and [B][A] should be merged
    for(i=0;i<nodeCount;i++){
        j=i;
        while(j<nodeCount){
            if(AdjMatrix[i][j] == 1){
                countMatrix[i][j] = countMatrix[i][j] + countMatrix[j][i];
                countMatrix[j][i] = 0;
            }
            j++;
        }
    }
    //divide every edge by 2
    //also get rid of little calculation errors by rounding
    for(i=0;i<nodeCount;i++){
        for(j=0;j<nodeCount;j++){
            countMatrix[i][j] /= 2;
            countMatrix[i][j] = roundToOneDecimal(countMatrix[i][j]);
        }
    }
}

void findGreatestEdgeBetwenessAndCut(int AdjMatrix[][MAX_NODES],int nodeCount,int communityCount){

    float countMatrix[MAX_NODES][MAX_NODES] = {0};

    calculateEdgeBetweness(AdjMatrix,countMatrix,nodeCount);
    int i,j;
    float max = 0;
    //find the max value of edge betweness
    for(i=0;i<nodeCount;i++){
        j=i;
        while(j<nodeCount){
            if(countMatrix[i][j]>max){
                max = countMatrix[i][j];
            }
            j++;
        }
    }
    //remove edges that have credit equal to max edge betweness
    for(i=0;i<nodeCount;i++){
        j=i;
        while(j<nodeCount){
            if(countMatrix[i][j]==max){
                AdjMatrix[i][j] = 0;
                AdjMatrix[j][i] = 0;
                //printf("edge %c to %c has been cut, credit :%.2f\n", indexToCharValue(i), indexToCharValue(j),countMatrix[i][j]);
            }
            j++;
        }
    }

   // printMatrixFloat(countMatrix,nodeCount);
}

void iteration(int AdjMatrix[][MAX_NODES],float countMatrix[][MAX_NODES],int nodeCount,int t,int k){
    int flag = 0;//to check is t satisfied
    int communityCount = 1,tmpCommunityCount;
    int itrCount = 1;
    int ctrl=0;
    do{
        findGreatestEdgeBetwenessAndCut(AdjMatrix,nodeCount,communityCount);
        printf("communities at iteration %d: \n ",itrCount);
        //to check if community count changes
        tmpCommunityCount = communityCount;
        communityCount = printCommunities(AdjMatrix,nodeCount,&flag,t);
        //checks amount of itearitions community size doesnt change
        if(communityCount==tmpCommunityCount) ctrl++;
        else ctrl = 0;

        itrCount++;
    } while (flag!=1 && ctrl != k);
}

void printRelations(int AdjMatrix[][MAX_NODES],int nodeCount){
    int i,j;
    printf("\n------------relations------------\n");
    for(i=0;i<nodeCount;i++){
        printf("%c: ", indexToCharValue(i));
        for(j=0;j<nodeCount;j++){
            if(AdjMatrix[i][j] == 1){
                printf("%c ", indexToCharValue(j));
            }
        }
        printf("\n");
    }
    printf("------------------------------\n");
}

//to only print communities and count amount of nodes
int recursiveCommunityMemberSearch(int AdjMatrix[][MAX_NODES],int nodeCount,int visited[],int startNode,int currentCount){
    int i;
    currentCount++;
    for(i=0;i<nodeCount;i++){
        if(AdjMatrix[startNode][i]==1 && visited[i]!=1){
            printf("%c ", indexToCharValue(i));
            visited[i] = 1;
            currentCount = recursiveCommunityMemberSearch(AdjMatrix,nodeCount,visited,i,currentCount);
        }
    }
    return currentCount;
}

int printCommunities(int AdjMatrix[][MAX_NODES],int nodeCount,int * flag, int t){
    int visited[MAX_NODES] = {0};
    int i;
    int communityCount=0;
    int personCount;

    for(i=0;i<nodeCount;i++){
        if(visited[i] == 0){
            communityCount++;//count communities
            visited[i] = 1;
            printf("%c ", indexToCharValue(i));
            //count and print nodes in a community
            personCount = recursiveCommunityMemberSearch(AdjMatrix,nodeCount,visited,i,0);
            if(personCount<=t) *flag = 1;// if t satisfied, set flag to 1
            printf("\n");
        }
    }
    printf("-----------------------------------\n");
    return communityCount;
}
#pragma clang diagnostic pop