// FindPath.h
// Andrea Vitek
// apborghi
// pa 4
// This program reads a Graph ADT from an input file and computes sample shortest paths
// which are printed out to an output test file

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

// Forward declarations
void runBFSonGraphFromFile(char *inputFile, char *outputFile);
void printPath(FILE* out, Graph G, List path, int destination);

// Main function
int main(int argc, char * argv[]) {
    // Check command lines for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    runBFSonGraphFromFile(argv[1], argv[2]);

    return(0);
}

// Performs BFS on an input file and writes a selection of shortest paths to an output file
void runBFSonGraphFromFile(char *inputFile, char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (in == NULL) {
        printf("Unable to open file \"%s\" for reading\n", inputFile);
        exit(1);
    }

    if (out == NULL) {
        printf("Unable to open file \"%s\" for writing\n", outputFile);
        exit(1);
    }

    int readingSize = 1;
    Graph G;

    int number = 0;
    int otherNumber = 0;
    int pairRead = 1;
    int BFSRead = 0;
    int graphPrinted = 0;
    List path = newList();

    while (fscanf(in, "%d,", &number) > 0) {
        if (readingSize == 1) {
            G = newGraph(number);
            readingSize = 0;

        } else {
            switch (pairRead) {
                case 0:
                    if (number == 0 && otherNumber == 0) {
                        BFSRead = 1;
                        pairRead = 1;
                        break;
                    }

                    if (BFSRead == 0) {
                        if (number != otherNumber) {
                            addEdge(G, otherNumber, number);
                        }

                    } else {
                        if (graphPrinted == 0) {
                            printGraph(out, G);
                            graphPrinted = 1;
                        }

                        BFS(G, otherNumber);
                        clear(path);
                        getPath(path, G, number);
                        printPath(out, G, path, number);
                    }

                    pairRead = 1;
                    break;

                case 1:
                    otherNumber = number;
                    pairRead--;
                    break;

                default:
                    break;
            }
        }
    }

    fclose(in);
    fclose(out);
    freeList(&path);
    freeGraph(&G);
}

// Outputs the path in a Graph to a destination within it after BFS() has been run
void printPath(FILE* out, Graph G, List path, int destination) {
    if (out == NULL) {
        out = stdout;
    }

    fprintf(out, "The distance from %d to %d is ", getSource(G), destination);

    if (front(path) == NIL) {
        fprintf(out, "infinity\n");
        fprintf(out, "No %d-%d path exists", getSource(G), destination);

    } else {
        fprintf(out, "%d\n", getDist(G, destination));
        fprintf(out, "A shortest %d-%d path is: ", getSource(G), destination);
        printList(out, path);
    }

    fprintf(out,"\n");
}