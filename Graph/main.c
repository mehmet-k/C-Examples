#include <stdio.h>
#define MAX 30

typedef struct edge{
    int w, n1,n2;
}EDGE;

typedef struct edge_list {
    EDGE data[MAX];
    int n;
    int max_node;
}EDGE_LIST;

EDGE_LIST create_MST(EDGE_LIST edgeList);
EDGE_LIST update_MST(EDGE_LIST edgeList);
EDGE_LIST sort_by_edges(EDGE_LIST edgeList);
void print_MST(EDGE_LIST edgeList);

int main() {
    EDGE_LIST edgeList;
    edgeList.n = 0;
    int decision;
    do{
        printf("Please select a operation: \n");
        printf("    1.Create MST(Warning: deletes existing tree and creates a new one)\n   "
                " 2.Add a new edge.\n    3.See final version of the MST.\n");
        scanf("%d",&decision);
        switch (decision) {
            case 1:
                //CREATE GRAPH FUNCTION
                edgeList = create_MST(edgeList);
                break;
            case 2:
                //ADD EDGE FUNCTION
                edgeList = update_MST(edgeList);

                break;
            case 3:
                print_MST(edgeList);
                break;
        }

        printf("Do you want to do another operation.\nType '1' for yes, type '0' for no\n");
        scanf("%d",&decision);
    } while (decision == 1);


    return 0;
}/*
int find_max_node(EDGE_LIST edgeList){
    int max = edgeList.data[0].w;
    for (int i = 1; i < edgeList.n; ++i) {
        if(max < edgeList.data[i].n1)
            max = edgeList.data[i].n1;
        if(max < edgeList.data[i].n2)
            max = edgeList.data[i].n2;
    }
}*/
EDGE_LIST create_MST(EDGE_LIST edgeList){
    printf("Please enter amount of edges: ");
    scanf("%d",&edgeList.n);
    printf("Please enter amount of nodes: ");
    scanf("%d",&edgeList.max_node);
    printf("Please enter data of the edges: \n");
    for (int i = 0; i < edgeList.n; ++i) {
        //printf("Edge %d: ",i+1);
        scanf("%d %d %d",&edgeList.data[i].w, &edgeList.data[i].n1, &edgeList.data[i].n2);
    }
    return edgeList;
}

void print_MST(EDGE_LIST edgeList){
    printf("\n        w n1 n2\n");
    for (int i = 0; i < edgeList.n; ++i) {
        printf("Edge %d: %d %d %d\n",i+1,edgeList.data[i].w, edgeList.data[i].n1, edgeList.data[i].n2);
    }
}

EDGE_LIST sort_by_edges(EDGE_LIST edgeList){//INSERTION SORT, sorts by w (weight of edge) variable in structs
    int i, j;
    EDGE key;
    for (i = 1; i < edgeList.n; i++) {
        key = edgeList.data[i];
        j = i - 1;
        while (j >= 0 && edgeList.data[j].w > key.w) {
            edgeList.data[j + 1] = edgeList.data[j];
            j = j - 1;
        }
        edgeList.data[j + 1] = key;
    }
    return edgeList;
}

void push(int stack[],int number,int *sp){
    stack[*sp] = number;
    *sp = *sp +1;
}

int pop(int stack[],int *sp){
    *sp = *sp -1;
    int number = stack[*sp];
    stack[*sp] = 0;
    return number;
}

int search(int n,int parent_array[],int stack[],int mtr[][MAX],int *sp,int dest ,int src,int org_src,int max_weight_index,EDGE_LIST e){
  printf("src: %d sp : %d \n",src,*sp);
    for(int i=1;i<=n;i++){
        printf("%d ",parent_array[i]);
    }
    printf("\n");
    int counter = 0;
    if(src == dest){
        return max_weight_index;
    }
    else{
        for(int j=1;j<=n;j++) {
            if (mtr[src][j] != -1 && parent_array[j] == 0) {
                push(stack, j, sp);
                parent_array[j] = src;
                counter++;
            }
        }
        if(counter == 0){
            src = parent_array[src];
            if(src == org_src)
                return 0;
            else
                search(n,parent_array,stack,mtr,sp,dest,src,org_src,max_weight_index,e);
        }
        else{
            /*
            for(int i=0;i<n;i++){
                printf(" %d ",stack[i]);
            }*/
            printf("\n");
            int temp;
            temp = src;
            src = pop(stack,sp);
            if(mtr[temp][src] > e.data[max_weight_index].w)
                max_weight_index = src-1;
            search(n,parent_array,stack,mtr,sp,dest,src,org_src,max_weight_index,e);
        }

    }

}
EDGE_LIST update_MST(EDGE_LIST edgeList){
    int max_weight_index= 0;
    int i;
    int visited[MAX] ;
    int stack[MAX] ;

    printf("\n");
    int j;
    EDGE tmpEdge;
    printf("Please enter data of the node you want to add: \n");
    scanf("%d %d %d",&tmpEdge.w,&tmpEdge.n1,&tmpEdge.n2);
    int mtr[MAX][MAX];//SETTING VALUES OF COST ADJ MTR
    for(i=0;i<=edgeList.max_node;i++){
        for(j=0;j<=8;j++){
            mtr[i][j] = -1;
        }
    }
    for(i=0;i<=edgeList.n;i++){//SETTING VALUES OF COST ADJ MTR
        mtr[edgeList.data[i].n1][edgeList.data[i].n2] = edgeList.data[i].w;
        mtr[edgeList.data[i].n2][edgeList.data[i].n1] = edgeList.data[i].w;
    }
    for(i=0;i<=edgeList.max_node;i++){
        for(j=0;j<=8;j++){
           printf(" %d ",mtr[i][j]);
        }
        printf("\n");
    }
    int temp = 0;
    int *sp = &temp;
    for(i=0;i<edgeList.max_node;i++){
        visited[i] = 0;
        stack[i] = 0;
    }
    visited[tmpEdge.n1] = tmpEdge.n1;
    max_weight_index = search(edgeList.max_node,visited,stack,mtr,sp,tmpEdge.n2,tmpEdge.n1,tmpEdge.n1,max_weight_index,edgeList);
    if(max_weight_index == 0){
        for(i=0;i<edgeList.max_node;i++){
            visited[i] = 0;
            stack[i] = 0;
        }
        visited[tmpEdge.n2] = tmpEdge.n2;
        *sp = 0;
        max_weight_index = search(edgeList.max_node,visited,stack,mtr,sp,tmpEdge.n1,tmpEdge.n2,tmpEdge.n2,max_weight_index,edgeList);
    }
/*
    for(i=1;i<=edgeList.n;i++){
        printf("%d ",visited[i]);
    }
    printf(" max weight : %d \n", max_weight_index);*/
    if(tmpEdge.w < edgeList.data[max_weight_index].w)
        edgeList.data[max_weight_index] = tmpEdge;

    printf("\n");print_MST(edgeList);
    edgeList = sort_by_edges(edgeList);

    return edgeList;
}