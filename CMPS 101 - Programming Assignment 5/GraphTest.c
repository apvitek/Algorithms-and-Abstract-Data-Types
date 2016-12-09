// GraphTest.c
// Andrea Vitek
// apborghi
// pa 5
// This program tests the function of the Graph ADT

#include<stdio.h>
#include "Graph.h"

// Forward declarations
void printStrongComponents(FILE *out, Graph G, List S);

int main(int argc, char * argv[]) {
    Graph G = newGraph(8);
    Graph copy, transposed;
    List S = newList();

    for (int i = 1; i <= getOrder(G) ; ++i) {
        append(S, i);
    }

    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 2, 5);
    addArc(G, 2, 6);
    addArc(G, 3, 4);
    addArc(G, 3, 7);
    addArc(G, 4, 3);
    addArc(G, 4, 8);
    addArc(G, 5, 1);
    addArc(G, 5, 6);
    addArc(G, 6, 7);
    addArc(G, 7, 6);
    addArc(G, 7, 8);
    addArc(G, 8, 8);

    printf("Adjacency list of G:\n");
    printGraph(NULL, G);

    printf("Graph size: %d\n", getSize(G));
    printf("Graph order: %d\n", getOrder(G));

    copy = copyGraph(G);

    printf("\nAdjacency list of Copy of G:\n");
    printGraph(NULL, copy);

    printf("Graph size: %d\n", getSize(copy));
    printf("Graph order: %d\n", getOrder(copy));

    printf("\nBefore running DFS() on G:\n");
    printf("Parent of 8: %d\n", getParent(G, 8));
    printf("Discovery time of 8: %d\n", getDiscover(G, 8));
    printf("Finishing time of 8: %d\n", getFinish(G, 8));

    printf("\nAfter running DFS() on G:\n");
    DFS(G, S);

    printf("Parent of 8: %d\n", getParent(G, 8));
    printf("Discovery time of 8: %d\n", getDiscover(G, 8));
    printf("Finishing time of 8: %d\n", getFinish(G, 8));

    transposed = transpose(G);
    printf("\nAdjacency list of Transpose of G:\n");
    printGraph(NULL, G);

    printf("\nAfter running DFS() on Transpose of G:\n");
    DFS(transposed, S);
    printStrongComponents(NULL, transposed, S);

    freeList(&S);
    freeGraph(&G);
    freeGraph(&copy);
    freeGraph(&transposed);

    return(0);
}

// Outputs the path in a Graph to a destination within it after DFS() has been run
void printStrongComponents(FILE *out, Graph G, List S) {
    if (out == NULL) {
        out = stdout;
    }

    int i = 1, current, connectedComponents = 0;
    List printStack = newList();

    // Count strongly connected components
    moveBack(S);

    while (index(S) != -1) {
        current = get(S);

        while (getParent(G, current) != NIL) {
            movePrev(S);
            current = get(S);
        }

        connectedComponents++;
        movePrev(S);
    }

    // Print strongly connected components
    moveBack(S);

    fprintf(out, "G contains %i strongly connected components:\n", connectedComponents);

    while (index(S) != -1 && i <= connectedComponents) {
        current = get(S);
        fprintf(out, "Component %d:", i);

        while (getParent(G, current) != NIL) {
            append(printStack, current);
            movePrev(S);
            current = get(S);
        }

        append(printStack, current);

        while (!isEmpty(printStack)) {
            fprintf(out, " %d", back(printStack));
            deleteBack(printStack);
        }

        movePrev(S);
        ++i;

        fprintf(out, "\n");
    }

    freeList(&printStack);
}

// Program output
//Adjacency list of G:
//1: 2
//2: 3 5 6
//3: 4 7
//4: 3 8
//5: 1 6
//6: 7
//7: 6 8
//8: 8
//
//Graph size: 14
//Graph order: 8
//
//Adjacency list of Copy of G:
//1: 2
//2: 3 5 6
//3: 4 7
//4: 3 8
//5: 1 6
//6: 7
//7: 6 8
//8: 8
//
//Graph size: 14
//Graph order: 8
//
//Before running DFS() on G:
//Parent of 8: 0
//Discovery time of 8: -1
//Finishing time of 8: -1
//
//After running DFS() on G:
//Parent of 8: 4
//Discovery time of 8: 5
//Finishing time of 8: 6
//
//Adjacency list of Transpose of G:
//1: 2
//2: 3 5 6
//3: 4 7
//4: 3 8
//5: 1 6
//6: 7
//7: 6 8
//8: 8
//
//
//After running DFS() on Transpose of G:
//G contains 4 strongly connected components:
//Component 1: 1 5 2
//Component 2: 3 4
//Component 3: 7 6
//Component 4: 8