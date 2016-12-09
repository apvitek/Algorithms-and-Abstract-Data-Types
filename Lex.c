// Lex.c
// Andrea Vitek
// 1559060
// pa 2
// This program reads strings from a text file, sorts them using a separate List ADT
// and exports the sorted strings to a text file

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 160

// Forward declarations
void insertionSortForList(char** inputListStrings, int inputListStringsSize, List inputListIndexes);
char** getInputStrings(char filename[], int* arraySize);
void printListInOrder(char** inputListStrings, List inputListIndexes);
void writeOutputFile(char filename[], char** inputListStrings, List inputListIndexes);

// Main function
int main(int argc, char * argv[]) {
    // Check command lines for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    int* arraySize = malloc(sizeof(int));
    char** stringsArray = getInputStrings(argv[1], arraySize);
    List inputListIndexes = newList();

    insertionSortForList(stringsArray, *arraySize, inputListIndexes);

    writeOutputFile(argv[2], stringsArray, inputListIndexes);

    for (int i = 0; i < *arraySize; ++i) {
        free(stringsArray[i]);
    }

    free(arraySize);
    free(stringsArray);
    freeList(&inputListIndexes);

    return(0);
}

// insertionSortForList()
// Performs insertionSort to sort the indexes of a String array in alphabetical order by storing
// the array's sorted indexed in a List ADT
void insertionSortForList(char** inputListStrings, int inputListStringsSize, List inputListIndexes) {
    append(inputListIndexes, 0);

    for (int j = 1; j < inputListStringsSize; j++) {
        moveFront(inputListIndexes);

        while (index(inputListIndexes) >= 0) {
            int cursor = get(inputListIndexes);

            if (strcmp(inputListStrings[j], inputListStrings[cursor]) < 0) {
                insertBefore(inputListIndexes, j);
                break;
            }

            moveNext(inputListIndexes);

            if (index(inputListIndexes) == -1) {
                append(inputListIndexes, j);
            }
        }
    }
}

// getInputStrings()
// Returns an array of strings from an input file
char** getInputStrings(char filename[], int* arraySize) {
    int count = 0;
    FILE *in;
    char line[MAX_LEN];
    char tokenlist[MAX_LEN];
    char* token;

    in = fopen(filename, "r");

    if (in == NULL) {
        //printf("Unable to open file %s for reading\n", argv[1]);
        printf("Unable to open file for reading\n");
        exit(1);
    }

    // Count the number of strings in the input file
    while (fgets(line, MAX_LEN, in) != NULL) {
        token = strtok(line, " \n");
        tokenlist[0] = '\0';

        while (token != NULL) {
            strcat(tokenlist, token);
            token = strtok(NULL, "\0");

            // Only count if the line is not empty
            if (strcmp(tokenlist, "") != 0) {
                count++;
            }
        }
    }

    // Reset the input file reading cursor
    rewind(in);

    char** stringsArray = malloc(count * sizeof(char*));

    for (int i = 0 ; i < count; ++i) {
        stringsArray[i] = malloc(count * sizeof(char));
    }

    int i = 0;

    while (fgets(line, MAX_LEN, in) != NULL) {
        token = strtok(line, " \n");
        tokenlist[0] = '\0';

        while (token != NULL) {
            strcat(tokenlist, token);
            token = strtok(NULL, "\0");

            if (strcmp(tokenlist, "") != 0) {
                strcpy(stringsArray[i], tokenlist);
            }

            i++;
        }
    }

    fclose(in);

    *arraySize = count;

    return stringsArray;
}

// printListInOrder()
// Prints the Strings of an array in the correct alphabetical order to the console
// following their sorted indexes in a List ADT
void printListInOrder(char** inputListStrings, List inputListIndexes) {
    moveFront(inputListIndexes);

    while (index(inputListIndexes) >= 0) {
        printf("%s\n", inputListStrings[get(inputListIndexes)]);
        moveNext(inputListIndexes);
    }
}

// writeOutputFile()
// Prints the Strings of an array in the correct alphabetical order to an output file
// following their sorted indexes in a List ADT
void writeOutputFile(char filename[], char** inputListStrings, List inputListIndexes) {
    FILE * out = fopen(filename, "w");

    if (out == NULL) {
        printf("Unable to open file \"%s\" for writing\n", filename);
        exit(1);
    }

    moveFront(inputListIndexes);

    while (index(inputListIndexes) >= 0) {
        fprintf(out, "%s\n", inputListStrings[get(inputListIndexes)]);
        moveNext(inputListIndexes);
    }

    fclose(out);
}