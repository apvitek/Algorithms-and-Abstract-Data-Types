// List.c
// Andrea Vitek
// apborghi
// pa 5
// Implementation of the List ADT

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    int length;
    Node cursor;
    int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data) {
    Node N = malloc(sizeof(NodeObj));

    N->data = data;
    N->next = NULL;
    N->prev = NULL;

    return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// Returns reference to new empty List object.
List newList(void) {
    List L;

    L = malloc(sizeof(ListObj));
    L->front = L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;

    return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        while (!isEmpty(*pL)) {
            deleteBack(*pL);
        }

        free(*pL);
        *pL = NULL;
    }
}

// clear()
// Empties the list
void clear(List L) {
    moveFront(L);

    while (L->length != 0) {
        deleteBack(L);
    }
}


// Access functions -----------------------------------------------------------

// index()
// Returns the index of the cursor on the list, -1 if cursor is undefined
// Pre: !isEmpty(L)
int index(List L) {
    if (L == NULL) {
        printf("List Error: calling index() on NULL List reference\n");
        exit(1);
    }

    return(L->index);
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L) {
    if (L == NULL) {
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);
    }

    if (isEmpty(L)) {
        printf("List Error: calling front() on an empty List\n");
        exit(1);
    }

    return(L->front->data);
}

// back()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int back(List L) {
    if (L == NULL) {
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);
    }

    if (isEmpty(L)) {
        printf("List Error: calling front() on an empty List\n");
        exit(1);
    }

    return(L->back->data);
}

// length()
// Returns the length of L.
int length(List L) {
    if (L == NULL) {
        printf("List Error: calling length() on NULL List reference\n");
        exit(1);
    }

    return(L->length);
}

// get()
// Returns the cursor of L, if it exists
// Pre: !isEmpty(L)
int get(List L) {
    if (L == NULL) {
        printf("List Error: calling get() on NULL List reference\n");
        exit(1);
    }

    if (L->cursor == NULL) {
        printf("List Error: cursor is null\n");
        exit(1);
    }

    return(L->cursor->data);
}

// moveFront()
// Moves the cursor at the front of the list
void moveFront(List L) {
    if (L == NULL) {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(1);
    }

    if (!isEmpty(L)) {
        L->index = 0;
    }

    L->cursor = L->front;
}

// moveBack()
// Moves the cursor at the back of the list
void moveBack(List L) {
    if (L == NULL) {
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(1);
    }

    L->index = L->length - 1;
    L->cursor = L->back;
}

// movePrev()
// Moves the cursor in the previous position in the list
void movePrev(List L) {
    if (L == NULL) {
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(1);
    }

    if (L->cursor != NULL) {
        L->cursor = L->cursor->prev;
        L->index--;
    }
}

// moveNext()
// Moves the cursor in the next position in the list
void moveNext(List L) {
    if (L == NULL) {
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(1);
    }

    if (L->cursor != NULL) {
        L->cursor = L->cursor->next;
        L->index++;

        if (L->index == L->length) {
            L->index = -1;
        }
    }
}

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L){
    if (L == NULL) {
        printf("List Error: calling isEmpty() on NULL List reference\n");
        exit(1);
    }

    return(L->length == 0);
}


// Manipulation procedures ----------------------------------------------------

// append()
// Places new data element at the end of L
void append(List L, int data) {
    Node N = newNode(data);

    if (L == NULL) {
        printf("List Error: calling append() on NULL List reference\n");
        exit(1);
    }

    if (isEmpty(L)){
        L->front = L->back = N;

    } else {
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
    }

    L->length++;
}

// prepend()
// Places new data element at the beginning of L
void prepend(List L, int data) {
    Node N = newNode(data);

    if (L == NULL) {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(1);
    }

    if (isEmpty(L)){
        L->front = L->back = N;

    } else {
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
    }

    L->length++;
}

// deleteFront()
// Deletes element at front of L
// Pre: !isEmpty(L)
void deleteFront(List L) {
    Node N = NULL;

    if (L == NULL) {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(1);
    }

    if (isEmpty(L)) {
        printf("List Error: calling deleteFront on an empty List\n");
        exit(1);
    }

    N = L->front;

    if (length(L) > 1) {
        L->front = L->front->next;
        L->front->prev = NULL;

    } else {
        L->front = L->back = NULL;
    }

    if (L->index >= 0) {
        L->index--;
    }

    if (L->index == -1) {
        L->cursor = NULL;
    }

    L->length--;
    freeNode(&N);
}

// deleteBack()
// Deletes element at back of L
// Pre: !isEmpty(L)
void deleteBack(List L) {
    Node N = NULL;

    if (L == NULL) {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }

    if (isEmpty(L)) {
        printf("List Error: calling deleteBack() on an empty List\n");
        exit(1);
    }

    N = L->back;

    if (length(L) > 1) {
        L->back = L->back->prev;
        L->back->next = NULL;

    } else {
        L->front = L->back = NULL;
    }

    if (L->index == L->length - 1) {
        L->index = -1;
    }

    L->length--;
    freeNode(&N);
}

// delete()
// Deletes the element pointed to by the cursor
void delete(List L) {
    Node N = NULL;

    if (L == NULL) {
        printf("List Error: calling delete() on NULL List reference\n");
        exit(1);
    }

    if (L->cursor != NULL) {
        N = L->cursor;

        if (L->index == 0) {
            deleteFront(L);
        } else if (L->index == L->length - 1) {
            deleteBack(L);
        } else {
            N->prev->next = N->next;
            N->next->prev = N->prev;
            L->index = -1;
        }

        L->length--;
        freeNode(&N);
    }
}
// insertBefore
// Inserts a new element before the cursor
void insertBefore(List L, int data) {
    if (L == NULL) {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(1);
    }

    if (L->cursor != NULL) {
        if (L->cursor->prev == NULL) {
            prepend(L, data);

        } else {
            Node N = newNode(data);

            N->prev = L->cursor->prev;
            N->next = L->cursor;
            N->prev->next = N;
            L->cursor->prev = N;

            L->index++;
            L->length++;
        }
    }
}

// insertAfter
// Inserts a new element after the cursor
void insertAfter(List L, int data) {
    if (L == NULL) {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(1);
    }

    if (L->cursor != NULL) {
        if (L->cursor->next == NULL) {
            append(L, data);

        } else {
            Node N = newNode(data);

            N->prev = L->cursor;
            N->next = L->cursor->next;
            L->cursor->next = N;
            N->next->prev = N;

            L->length++;
        }
    }
}


// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L) {
    if (L == NULL) {
        printf("List Error: calling printList() on NULL List reference\n");
        exit(1);
    }

    Node N = NULL;

    if (out == NULL) {
        out = stdout;
    }

    for (N = L->front; N != NULL; N = N->next) {
        fprintf(out, "%d ", N->data);
    }

    fprintf(out,"\n");
}

// copyList()
// returns a copy of the current list
List copyList(List L) {
    if (L == NULL) {
        printf("List Error: calling copyList() on NULL List reference\n");
        exit(1);
    }

    List copiedList = newList();
    Node N = NULL;

    for (N = L->front; N != NULL; N = N->next) {
        append(copiedList, N->data);
    }

    return copiedList;
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){
    int eq = 0;
    Node N = NULL;
    Node M = NULL;

    if (A == NULL || B == NULL) {
        return 0;
    }

    eq = ( A->length == B->length );
    N = A->front;
    M = B->front;

    while (eq && N != NULL) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }

    return eq;
}