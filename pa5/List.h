//Adam Buderi 1451707
//pa2
//----------------------------------------------------------------
//List.h header file for List.c
//----------------------------------------------------------------

#include <stdio.h>
//#include <string.h>

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// Struct declaration----------------------------------------------------------


typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------
List newList(void);
void freeList(List* pL);


// Access functions -----------------------------------------------------------
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
int equals(List A, List B);
int isEmpty(List L);

// Manipulation procedures ----------------------------------------------------
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);


// Other operations -----------------------------------------------------------
void printList(FILE* out, List L);
List copyList(List L);

#endif