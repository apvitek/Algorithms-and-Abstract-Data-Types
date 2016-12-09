// FindComponents.c
// Andrea Vitek
// apborghi
// pa 5
// This program reads a Graph ADT from an input file and computes DFS on an input file and writes a selection of shortest paths to an output file.

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

// Forward declarations
void runDFSonGraphFromFile(char *inputFile, char *outputFile);
void printStrongComponents(FILE *out, Graph G, List S);

// Main function
int main(int argc, char * argv[]) {
    // Check command lines for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    runDFSonGraphFromFile(argv[1], argv[2]);

    return(0);
}

// Performs DFS on an input file and writes a selection of shortest paths to an output file
void runDFSonGraphFromFile(char *inputFile, char *outputFile) {
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
    Graph original, transposed;

    int number = 0;
    int otherNumber = 0;
    int pairRead = 1;
    List stack = newList();

    while (fscanf(in, "%d,", &number) > 0) {
        if (readingSize == 1) {
            original = newGraph(number);
            readingSize = 0;

        } else {
            switch (pairRead) {
                case 0:
                    if (number == 0 && otherNumber == 0) {
                        fprintf(out, "Adjacency list representation of G:\n");
                        printGraph(out, original);

                        // Initialize stack to standard order
                        for (int i = 1; i <= getOrder(original); ++i) {
                            append(stack, i);
                        }

                        DFS(original, stack);
                        transposed = transpose(original);
                        DFS(transposed, stack);
                        printStrongComponents(out, transposed, stack);

                        break;
                    }

                    addArc(original, otherNumber, number);
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
    freeList(&stack);
    freeGraph(&original);
    freeGraph(&transposed);
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

        fprintf(out,"\n");
    }

    freeList(&printStack);
}