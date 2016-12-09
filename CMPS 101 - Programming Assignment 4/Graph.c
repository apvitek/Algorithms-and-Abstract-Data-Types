// Graph.c
// Andrea Vitek
// apborghi
// pa 4
// Implementation file of the List ADT

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

// structs --------------------------------------------------------------------

// Private GraphObj struct
typedef struct GraphObj {
    int order; // Number of vertices
    int size; // Number of edges
    int mostRecentVertexLabel; // Label of the vertex that was most recently used as source for BFS

    List* neighbors; // ith element contains the neighbors of vertex i
    color* vertexColor; // ith element is the color (white, gray, black) of vertex i
    int* vertexParent; // ith element is the parent of vertex i
    int* distanceFromSource; // ith element is the distance from the (most recent) source to vertex i
} GraphObj;

/*** Constructors-Destructors ***/
// newGraph()
// Returns reference to a new Graph object
// All arrays initialized to size n (number or vertices) + 1
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));

    G->order = n;
    G->size = 0;
    G->mostRecentVertexLabel = NIL;

    G->neighbors = calloc((size_t) (n + 1), sizeof(List));
    G->vertexColor = calloc((size_t) (n + 1), sizeof(color));
    G->vertexParent = calloc((size_t) (n + 1), sizeof(int));
    G->distanceFromSource = calloc((size_t) (n + 1), sizeof(int));

    for (int i = 1; i <= n; i++) {
        G->neighbors[i] = newList();
        G->vertexColor[i] = WHITE;
        G->distanceFromSource[i] = INF;
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
    free((*pG)->distanceFromSource);
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

// getSource()
// Returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called
// Pre: G is not NULL
int getSource(Graph G) {
    if (G == NULL) {
        printf("List Error: calling getSource() on NULL Graph reference\n");
        exit(1);
    }

    return G->mostRecentVertexLabel;
}

// getParent()
// Returns the parent of vertex u in the Breadth- First tree created by BFS(), or NIL if BFS() has not yet been called
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

// getDist()
// Returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called
// Pre: 1 <= u <= getOrder(G), G is not NULL
int getDist(Graph G, int u) {
    if (G == NULL) {
        printf("List Error: calling getDist() on NULL Graph reference\n");
        exit(1);
    }

    if (u < 1 || u > getOrder(G)) {
        printf("List Error: calling getDist() with invalid index\n");
        exit(1);
    }

    return G->distanceFromSource[u];
}

// getPath()
// Appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists
// Pre: 1 <= u <= getOrder(G), getSource(G) != NIL, G is not NULL
void getPath(List L, Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: calling getPath() on NULL Graph reference\n");
        exit(1);
    }

    if (L == NULL) {
        printf("Graph Error: calling getPath() on NULL List reference\n");
        exit(1);
    }

    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getPath() with invalid index\n");
        exit(1);
    }

    if (getSource(G) == NIL) {
        printf("Graph Error: calling getpath() with NIL source\n");
        exit(1);
    }

    if (u == getSource(G)) {
        append(L, u);

    } else if (getParent(G, u) == NIL) {
        append(L, NIL);

    } else {
        prepend(L, u);

        int x = getParent(G, u);

        while (x != getSource(G) && x != NIL) {
            prepend(L, x);
            x = getParent(G, x);
        }

        if (x == NIL) {
            prepend(L, NIL);

        } else {
            prepend(L, x);
        }
    }
}

/*** Manipulation procedures ***/
// makeNull()
// Deletes all edges of G, restoring it to its original (no edge) state
// Pre: G is not NULL
void makeNull(Graph G) {
    if (G == NULL) {
        printf("List Error: calling makeNull() on NULL Graph reference\n");
        exit(1);
    }

    for (int i = 1; i <= getOrder(G); i++) {
        clear(G->neighbors[i]);
        G->vertexColor[i] = WHITE;
        G->distanceFromSource[i] = INF;
        G->vertexParent[i] = NIL;
    }

    G->size = 0;
    G->mostRecentVertexLabel = NIL;
}

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

        while (getIndex(adjacencyList) >= 0) {
            if (get(adjacencyList) > v) {
                insertBefore(adjacencyList, v);
                break;
            }

            moveNext(adjacencyList);

            if (getIndex(adjacencyList) == -1) {
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

// BFS()
// Runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly
// Pre: 1 <= s <= getOrder(G), G is not NULL
void BFS(Graph G, int s) {
    if (G == NULL) {
        printf("List Error: calling BFS() on NULL Graph reference\n");
        exit(1);
    }

    if (s < 1 || s > getOrder(G)) {
        printf("List Error: calling BFS() with invalid index\n");
        exit(1);
    }

    G->mostRecentVertexLabel = s;
    int i, x, y;

    for (i = 1; i <= getOrder(G); i++) {
        G->vertexColor[i] = WHITE;
        G->distanceFromSource[i] = INF;
        G->vertexParent[i] = NIL;
    }

    G->vertexColor[s] = GRAY;
    G->distanceFromSource[s] = 0;
    G->vertexParent[s] = NIL;

    List L = newList();
    append(L, s);

    while (!isEmpty(L)) {
        x = front(L);
        deleteFront(L);

        if (!isEmpty(G->neighbors[x])) {
            moveFront(G->neighbors[x]);
        }

        while (getIndex(G->neighbors[x]) != -1) {
            y = get(G->neighbors[x]);

            if (G->vertexColor[y] == WHITE) {
                G->vertexColor[y] = GRAY;
                G->distanceFromSource[y] = (getDist(G, x) + 1);
                G->vertexParent[y] = x;
                append(L, y);
            }

            moveNext(G->neighbors[x]);
        }

        G->vertexColor[x] = BLACK;
    }

    freeList(&L);
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