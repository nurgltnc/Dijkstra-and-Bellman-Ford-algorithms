//Dijikstra algorithm works incorrectly on negatively weighted edges
//You can see the difference with Bellman Ford algorithm

#include <stdio.h>
#include <stdlib.h>
#define MAX_VALUE 1000

typedef struct AdjencyList {
    struct Node *head;
} AdjencyList;

typedef struct Graph {
    int Vertices;
    AdjencyList *array;
} Graph;

typedef struct Node {
    int dest;
    int weight;
    struct Node *next;
} Node;

void Dijkstra(Graph *graph, int source) {
    int dist[graph->Vertices];
    int visited_status[graph->Vertices];

    for (int i = 0; i < graph->Vertices; ++i) {
        visited_status[i] = 0;
        dist[i] = MAX_VALUE;
    }
    dist[source] = 0;
    printf("------------------------------\n");
    printf("DEST\t|\tPATH\n");
    for (int k = 0; k < graph->Vertices; k++)
        printf("%d\t|\t%d\n", k, dist[k]);
    for (int i = 0; i < graph->Vertices -1; ++i) {
        int min = MAX_VALUE;
        int min_index;
        for (int j = 0; j < graph->Vertices; ++j) {
            if(visited_status[j] == 0 && dist[j] <= min){
                min = dist[j];
                min_index = j;
            }
        }
        visited_status[min_index] = 1;
        Node *Q = graph->array[min_index].head;
        while(Q != NULL){
            int v = Q->dest;
            int weight = graph->array[min_index].head->weight;
            if(visited_status[v] == 0 && dist[min_index] != MAX_VALUE && dist[v] > dist[min_index] + weight){
                dist[v] = dist[min_index] + weight;
                printf("------------------------------\n");
                printf("DEST\t|\tPATH\n");
                for (int k = 0; k < graph->Vertices; k++)
                    printf("%d\t|\t%d\n", k, dist[k]);
            }
            Q = Q->next;
        }
    }
}

void Bellman_Ford(Graph *graph, int source, int V){
    int dist[graph->Vertices];
    int parent[graph->Vertices];
    for (int i = 0; i < graph->Vertices; ++i) {
        dist[i] = MAX_VALUE;
        parent[i] = -1;
    }
    dist[source] = 0;
    parent[source] = -1;
    printf("---------------------------------------------------------------\n");
    printf("DEST\t|\tPATH\t|\tDEST\t|\tPARENT\n");
    for (int k = 0; k < graph->Vertices; k++)
        printf("%d\t|\t%d\t\t|\t%d\t|\t%d\n", k, dist[k], k, parent[k]);
    for (int i = 0; i < V-1; ++i) {
        for (int u = 0; u < V; ++u) {
            Node *temp = graph->array[u].head;
            while(temp != NULL){
                int v = temp->dest;
                int weight = temp->weight;
                if(dist[u] != MAX_VALUE && dist[v] > dist[u] + weight){
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    printf("---------------------------------------------------------------\n");
                    printf("DEST\t|\tPATH\t|\tDEST\t|\tPARENT\n");
                    for (int k = 0; k < graph->Vertices; k++)
                        printf("%d\t|\t%d\t\t|\t%d\t|\t%d\n", k, dist[k], k, parent[k]);
                }
                temp = temp->next;
            }
        }
    }
}

void Add_Edge(Graph *graph, int source, int destination, int weight){
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->dest = destination;
    new_node->weight = weight;
    new_node->next = graph->array[source].head;
    graph->array[source].head = new_node;
}

void Graph_Structure(Graph* graph) {
    for (int v = 0; v < graph->Vertices; ++v) {
        Node* temp = graph->array[v].head;
        printf("Edges of Node %d: ", v);
        while (temp) {
            printf("(%d, %d) ", temp->dest, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    FILE* file = fopen("graph.txt", "r");
    if(file == NULL){
        printf("File opening error!");
        return -1;
    }
    int V, E;
    fscanf(file, "%d %d", &V, &E);
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->Vertices = V;
    graph->array = (AdjencyList*)malloc(V* sizeof(AdjencyList));
    for (int i = 0;i < V; ++i) {
        graph->array[i].head = NULL;
    }

    for (int i = 0; i < E; ++i) {
        int source, destination, weight;
        fscanf(file, "%d %d %d", &source, &destination, &weight);
        Add_Edge(graph, source, destination, weight);
    }
    fclose(file);
    printf("Graph structure:(node, weight)\n");
    Graph_Structure(graph);
    printf("\n");
    printf("Each step result is written in tabular form.\n");
    printf("**DIJKSTRA**: \n");
    Dijkstra(graph, 0);
    printf("\n\n");
    printf("**BELLMAN-FORD**: \n");
    Bellman_Ford(graph, 0, V);
    free(graph);
    return 0;
}
