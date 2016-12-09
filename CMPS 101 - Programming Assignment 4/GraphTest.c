//// GraphTest.c
//// Andrea Vitek
//// apborghi
//// pa 4
//// This program tests the function of the Graph ADT
//
//#include<stdio.h>
//#include "Graph.h"
//
//void printPath(FILE* out, Graph G, List path, int destination);
//
//int main(int argc, char * argv[]) {
//    Graph G = newGraph(6);
//    List path = newList();
//
//    addEdge(G, 1, 2);
//    addEdge(G, 1, 3);
//    addEdge(G, 2, 4);
//    addEdge(G, 2, 5);
//    addEdge(G, 2, 6);
//    addEdge(G, 3, 4);
//    addEdge(G, 4, 5);
//    addEdge(G, 5, 6);
//
//    printGraph(NULL, G);
//
//    printf("Graph size: %d\n", getSize(G));
//    printf("Graph order: %d\n", getOrder(G));
//
//    printf("Source: %d\n", getSource(G));
//    printf("Parent of 1: %d\n", getParent(G, 1));
//    printf("Distance from 1: %d\n\n", getDist(G, 1));
//
//    printf("Running BFS() with source 1\n");
//    BFS(G, 1);
//    printf("Source: %d\n", getSource(G));
//    getPath(path, G, 5);
//    printPath(NULL, G, path, 5);
//
//    makeNull(G);
//    clear(path);
//    printGraph(NULL, G);
//
//    addArc(G, 1, 2);
//    addArc(G, 1, 3);
//    addArc(G, 2, 4);
//    addArc(G, 2, 5);
//    addArc(G, 2, 6);
//    addArc(G, 3, 4);
//    addArc(G, 4, 5);
//    addArc(G, 5, 6);
//    printGraph(NULL, G);
//
//    printf("Graph size: %d\n", getSize(G));
//    printf("Graph order: %d\n", getOrder(G));
//
//    printf("Source: %d\n", getSource(G));
//    printf("Parent of 1: %d\n", getParent(G, 1));
//    printf("Distance from 1: %d\n\n", getDist(G, 1));
//
//    printf("Running BFS() with source 1\n");
//    BFS(G, 1);
//    printf("Source: %d\n", getSource(G));
//    getPath(path, G, 5);
//    printPath(NULL, G, path, 5);
//
//    freeList(&path);
//    freeGraph(&G);
//
//    return(0);
//}
//
//// Outputs the path in a Graph to a destination within it after BFS() has been run
//void printPath(FILE* out, Graph G, List path, int destination) {
//    if (out == NULL) {
//        out = stdout;
//    }
//
//    fprintf(out, "The distance from %d to %d is ", getSource(G), destination);
//
//    if (front(path) == NIL) {
//        fprintf(out, "infinity\n");
//        fprintf(out, "No %d-%d path exists", getSource(G), destination);
//
//    } else {
//        fprintf(out, "%d\n", getDist(G, destination));
//        fprintf(out, "A shortest %d-%d path is: ", getSource(G), destination);
//        printList(out, path);
//    }
//
//    fprintf(out,"\n");
//}
//
//// Program output
////1: 2 3
////2: 1 4 5 6
////3: 1 4
////4: 2 3 5
////5: 2 4 6
////6: 2 5
////
////Graph size: 8
////Graph order: 6
////Source: 0
////Parent of 1: 0
////Distance from 1: -1
////
////Running BFS() with source 1
////Source: 1
////The distance from 1 to 5 is 2
////A shortest 1-5 path is: 1 2 5
////
////1:
////2:
////3:
////4:
////5:
////6:
////
////1: 2 3
////2: 4 5 6
////3: 4
////4: 5
////5: 6
////6:
////
////Graph size: 8
////Graph order: 6
////Source: 0
////Parent of 1: 0
////Distance from 1: -1
////
////Running BFS() with source 1
////Source: 1
////The distance from 1 to 5 is 2
////A shortest 1-5 path is: 1 2 5