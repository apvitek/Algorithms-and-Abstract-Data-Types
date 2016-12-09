// Graph.h
// Andrea Vitek
// apborghi
// pa 5
// Header file of the Graph ADT

#ifndef CMPS_101_PROGRAMMING_ASSIGNMENT_5_GRAPH_H
#define CMPS_101_PROGRAMMING_ASSIGNMENT_5_GRAPH_H

typedef enum {GRAY = 0, BLACK = 1, WHITE = 2} color;
#define UNDEF -1
#define NIL 0

#include "List.h"

/*** Exported Type ***/
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif