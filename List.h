// List.h
// Andrea Vitek
// 1559060
// pa 2
// Header file of the List ADT

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_


// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object.
List newList(void);

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);

// clear()
// Empties the list
void clear(List L);


// Access functions -----------------------------------------------------------

// index()
// Returns the index of the cursor on the list, -1 if cursor is undefined
// Pre: !isEmpty(L)
int index(List L);

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L);

// back()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
int back(List L);

// length()
// Returns the length of L.
int length(List L);

// get()
// Returns the cursor of L, if it exists
// Pre: !isEmpty(L)
int get(List L);

// moveFront()
// Moves the cursor at the front of the list
void moveFront(List L);

// moveBack()
// Moves the cursor at the back of the list
void moveBack(List L);

// movePrev()
// Moves the cursor in the previous position in the list
void movePrev(List L);

// moveNext()
// Moves the cursor in the next position in the list
void moveNext(List L);

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L);


// Manipulation procedures ----------------------------------------------------

// append()
// Places new data element at the end of L
void append(List L, int data);

// prepend()
// Places new data element at the beginning of L
void prepend(List L, int data);

// deleteFront()
// Deletes element at front of L
// Pre: !isEmpty(L)
void deleteFront(List L);

// deleteBack()
// Deletes element at back of L
// Pre: !isEmpty(L)
void deleteBack(List L);

// delete()
// Deletes the element pointed to by the cursor
void delete(List L);

// insertBefore
// Inserts a new element before the cursor
void insertBefore(List L, int data);

// insertAfter
// Inserts a new element after the cursor
void insertAfter(List L, int data);


// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L);

// copyList()
// returns a copy of the current list
List copyList(List L);

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B);

#endif
