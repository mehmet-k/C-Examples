#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int vertex;
  struct node* next;
}NODE;

typedef struct Graph {
  int numVertices;
  int* visited;
  struct node** adjLists;
}GRAPH;

NODE* createNode(int v);
GRAPH * createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);


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
                printf("Data of the graph: ");
                for(i= 0;i<edges;i++){
                    scanf("%d %d %d",&weight, &src,&dest);
                    addEdge(graph,src,dest);
                }
                break;
            case 2:
                //ADD EDGE FUNCTION

                break;
            case 3:
                printGraph(graph);
                break;
        }

        printf("Do you want to do another operation.\nType '1' for yes, type '0' for no\n");
        scanf("%d",&decision);
    } while (decision == 1);

  return 0;
}

// DFS algo
void DFS(struct Graph* graph, int vertex) {
    struct node* adjList = graph->adjLists[vertex];
    struct node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("Visited %d \n", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

// Create a node
NODE* createNode(int v) {
    NODE* Node = malloc(sizeof(NODE));
    Node->vertex = v;
    Node->next = NULL;
    return Node;
}

// Create graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct node*));

    graph->visited = malloc(vertices * sizeof(int));

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Add edge
void addEdge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest
    NODE* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Print the graph
void printGraph(struct Graph* graph) {
    int v;
    for (v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}
