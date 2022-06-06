#include <stdio.h>
#include <stdlib.h>
#define MAX 30

typedef struct node {
  int vertex;
  struct node* next;
}NODE;

typedef struct edge{
    NODE n1;
    NODE n2;
    int w;
}EDGE;

typedef struct Graph {
  int numVertices;
  int visited[MAX];
  NODE *list[MAX];
}GRAPH;

GRAPH * createGraph(int vertices);
NODE* createNode(int v);

int main() {
    GRAPH * graph ;//createGraph(4);

    int vertices,edges,weight,src,dest;
    int decision,i;
    do{
        printf("Please select a operation: \n");
        printf("    1.Create MST(Warning: deletes existing tree and creates a new one)\n   "
               " 2.Add a new edge.\n    3.See final version of the MST.\n");
        scanf("%d",&decision);
        switch (decision) {
            case 1:
                //CREATE GRAPH FUNCTION
                printf("Please enter number of vertices: \n");
                scanf("%d",&vertices);
                createGraph(vertices);
                printf("Please enter number of edges: \n");
                scanf("%d",&edges);
                printf("Data of the graph: \n");
                for(i=0;i<vertices;i++){
                    //ADD EDGE
                }

                break;
            case 2:
                //ADD EDGE FUNCTION

                break;
            case 3:
                break;
        }

        printf("Do you want to do another operation.\nType '1' for yes, type '0' for no\n");
        scanf("%d",&decision);
    } while (decision == 1);

    return 0;
}
NODE* createNode(int v) {
    NODE* Node = malloc(sizeof(NODE));
    Node->vertex = v;
    //Node->next = NULL;
    return Node;
}

// Create graph
GRAPH * createGraph(int vertices) {
    GRAPH * graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    int i,j;
    for (i = 0; i < vertices; i++) {
        for(j=0;j<vertices;j++)
            graph->list[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(GRAPH * graph, int src, int dest) {
    // Add edge from src to dest
    NODE* newNode = createNode(dest);
    newNode->next = graph->list[src];
    graph->list[src] = newNode;

    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->list[dest];
    graph->list[dest] = newNode;
}

void printGraph(GRAPH * graph) {
    int v;
    for (v = 0; v < graph->numVertices; v++) {
        NODE* temp = graph->list[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}