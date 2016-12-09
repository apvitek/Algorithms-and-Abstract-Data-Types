// Graph.c
// Andrea Vitek
// apborghi
// pa 5
// Implementation file of the Graph ADT

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

// structs --------------------------------------------------------------------

// Private GraphObj struct
typedef struct GraphObj {
    int order; // Number of vertices
    int size; // Number of edges
    int connectedComponents; // Number of connected components

    List* neighbors; // ith element contains the neighbors of vertex i
    color* vertexColor; // ith element is the color (white, gray, black) of vertex i
    int* vertexParent; // ith element is the parent of vertex i
    int* discoveryTime; // ith element is the time at which the vertex i was discovered
    int* finishTime; // ith element is the time at which the vertex i was finished
} GraphObj;

/*** Constructors-Destructors ***/
// newGraph()
// Returns reference to a new Graph object
// All arrays initialized to size n (number or vertices) + 1
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));

    G->order = n;
    G->size = 0;

    G->neighbors = calloc((size_t) (n + 1), sizeof(List));
    G->vertexColor = calloc((size_t) (n + 1), sizeof(color));
    G->vertexParent = calloc((size_t) (n + 1), sizeof(int));
    G->discoveryTime = calloc((size_t) (n + 1), sizeof(int));
    G->finishTime = calloc((size_t) (n + 1), sizeof(int));

    for (int i = 1; i <= n; i++) {
        G->neighbors[i] = newList();
        G->vertexColor[i] = WHITE;
        G->discoveryTime[i] = UNDEF;
        G->finishTime[i] = UNDEF;
        G->vertexParent[i] = NIL;
    }

    return (G);
}

// freeGraph()
// Frees memory of a Graph object pointed to by *pG
void freeGraph(Graph* pG) {
    if (pG == NULL || (*pG) == NULL) {
        return;
    }

    for (int i = 1; i <= getOrder(*pG); i++) {
        freeList(&(*pG)->neighbors[i]);
    }

    free((*pG)->neighbors);
    free((*pG)->vertexColor);
    free((*pG)->vertexParent);
    free((*pG)->discoveryTime);
    free((*pG)->finishTime);
    free(*pG);
    *pG = NULL;
}

/*** Access functions ***/
// getOrder()
// Returns the order of the graph
// Pre: G is not NULL
int getOrder(Graph G) {
    if (G == NULL) {
        printf("List Error: calling getOrder() on NULL Graph reference\n");
        exit(1);
    }

    return G->order;
}

// getSize()
// Returns the size of the graph
// Pre: G is not NULL
int getSize(Graph G) {
    if (G == NULL) {
        printf("List Error: calling getSize() on NULL Graph reference\n");
        exit(1);
    }

    return G->size;
}

// getParent()
// Returns the parent of vertex u in the Breadth- First tree created by BFS(), or NIL if DFS() has not yet been called
// Pre: 1 <= u <= getOrder(G), G is not NULL
int getParent(Graph G, int u) {
    if (G == NULL) {
        printf("List Error: calling getParent() on NULL Graph reference\n");
        exit(1);
    }

    if (u < 1 || u > getOrder(G)) {
        printf("List Error: calling getParent() with invalid index\n");
        exit(1);
    }

    return G->vertexParent[u];
}

// getDiscover()
// Returns...
// Pre: 1 <= u <= getOrder(G), G is not NULL
int getDiscover(Graph G, int u) {
    if (G == NULL) {
        printf("List Error: calling getDiscover() on NULL Graph reference\n");
        exit(1);
    }

    if (u < 1 || u > getOrder(G)) {
        printf("List Error: calling getDiscover() with invalid index\n");
        exit(1);
    }

    return G->discoveryTime[u];
}

// getFinish()
// Returns...
// Pre: 1 <= u <= getOrder(G), G is not NULL
int getFinish(Graph G, int u) {
    if (G == NULL) {
        printf("List Error: calling getDiscover() on NULL Graph reference\n");
        exit(1);
    }

    if (u < 1 || u > getOrder(G)) {
        printf("List Error: calling getDiscover() with invalid index\n");
        exit(1);
    }

    return G->finishTime[u];
}

/*** Manipulation procedures ***/
// insertInAdjacencyList()
// Private function that inserts an element in a List in sorted order
void insertInAdjacencyList(List adjacencyList, int v) {
    if (adjacencyList == NULL) {
        return;
    }

    if (isEmpty(adjacencyList)) {
        append(adjacencyList, v);

    } else {
        moveFront(adjacencyList);

        while (index(adjacencyList) >= 0) {
            if (get(adjacencyList) > v) {
                insertBefore(adjacencyList, v);
                break;
            }

            moveNext(adjacencyList);

            if (index(adjacencyList) == -1) {
                append(adjacencyList, v);
            }
        }
    }
}

// addEdge()
// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u.
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G), G is not NULL
void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        printf("Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(1);
    }

    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        printf("Graph Error: calling addEdge() with invalid indexes\n");
        exit(1);
    }

    List adjacencyListForU = G->neighbors[u];
    insertInAdjacencyList(adjacencyListForU, v);

    List adjacencyListForV = G->neighbors[v];
    insertInAdjacencyList(adjacencyListForV, u);

    ++G->size;
}

// addArc()
// Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v)
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G), G is not NULL
void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        printf("List Error: calling addArc() on NULL Graph reference\n");
        exit(1);
    }

    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        printf("List Error: calling addArc() with invalid indexes\n");
        exit(1);
    }

    List adjacencyListForU = G->neighbors[u];
    insertInAdjacencyList(adjacencyListForU, v);

    ++G->size;
}

// visit()
// Private function
void visit(Graph G, List L, int x, int *time) {
    int current;

    G->vertexColor[x] = GRAY;
    G->discoveryTime[x] = ++(*time);

    moveFront(G->neighbors[x]);

    while (index(G->neighbors[x]) != -1) {
        current = get(G->neighbors[x]);

        if (G->vertexColor[current] == WHITE) {
            G->vertexParent[current] = x;
            visit(G, L, current, &(*time));
        }

        moveNext(G->neighbors[x]);
    }

    G->vertexColor[x] = BLACK;
    G->finishTime[x] = ++(*time);
    prepend(L, x);
}

// DFS()
// Runs the DFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly
// Pre: length(S)==getOrder(G), G is not NULL
void DFS(Graph G, List S) {
    if (G == NULL) {
        printf("Graph Error: calling DFS() on NULL Graph reference\n");
        exit(1);
    }

    if (length(S) != getOrder(G)) {
        printf("Graph Error: calling DFS() with length of List not equal to order of Graph\n");
        exit(1);
    }

    int current, time = 0;
    List temp = newList();

    for (int i = 1; i <= getOrder(G); i++) {
        G->vertexColor[i] = WHITE;
        G->vertexParent[i] = NIL;
        G->discoveryTime[i] = UNDEF;
        G->finishTime[i] = UNDEF;
    }

    moveFront(S);

    while (index(S) != -1) {
        current = get(S);

        if (G->vertexColor[current] == WHITE) {
            visit(G, temp, current, &time);
        }

        moveNext(S);
    }

    clear(S);
    moveFront(temp);

    // Transfer result to input list, thus making it an output
    while (index(temp) != -1) {
        append(S, get(temp));
        moveNext(temp);
    }

    freeList(&temp);
}

// transpose()
// Computes the transpose of G and returns it
// Pre: G is not NULL
Graph transpose(Graph G) {
    if (G == NULL) {
        printf("Graph Error: calling transpose() on NULL Graph reference\n");
        exit(1);
    }

    Graph transposedGraph = newGraph(getOrder(G));

    int i, x;

    for (i = 1; i <= getOrder(G); ++i) {
        moveFront(G->neighbors[i]);

        while (index(G->neighbors[i]) != -1) {
            x = get(G->neighbors[i]);
            addArc(transposedGraph, x, i);
            moveNext(G->neighbors[i]);
        }
    }

    return (transposedGraph);
}

// copyGraph()
// Return a copy of this Graph
Graph copyGraph(Graph G) {
    Graph copiedGraph = newGraph(getOrder(G));

    for (int i = 1; i <= getOrder(copiedGraph); ++i) {
        moveFront(G->neighbors[i]);

        while (index(G->neighbors[i]) != -1) {
            append(copiedGraph->neighbors[i], get(G->neighbors[i]));
            moveNext(G->neighbors[i]);
        }

        copiedGraph->vertexColor[i] = G->vertexColor[i];
        copiedGraph->vertexParent[i] = getParent(G, i);
        copiedGraph->discoveryTime[i] = getDiscover(G, i);
        copiedGraph->finishTime[i] = getFinish(G, i);
    }

    copiedGraph->size = getSize(G);

    return copiedGraph;
}

/*** Other operations ***/
// printGraph()
// Prints the adjacency list representation of G to the file pointed to by out
// Pre: G is not NULL
void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
        printf("List Error: calling printGraph() on NULL Graph reference\n");
        exit(1);
    }

    if (out == NULL) {
        out = stdout;
    }

    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->neighbors[i]);
    }

    fprintf(out,"\n");
}