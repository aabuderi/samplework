// Adam Buderi 1451707
// pa2
// List.c- contains the methods used by the list datatype
//----------------------------------------------------------------
#include <stdlib.h>
#include<stdio.h>
#include<stdlib.h>
#include <assert.h>

#include "List.h"



int length(List L);
//int index(List L);
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


//Node declaration-------------------------------------------------------------
	typedef struct NodeObj{
		struct NodeObj* next;
		struct NodeObj* prev;
		int data;
	}NodeObj;
	
//private Node type
typedef NodeObj* Node;

//List declaration-------------------------------------------------------------	
typedef struct ListObj{
	Node top;
	Node bot;
	int length;
	int cursor;
}ListObj;


Node newNode(int data);
void freeNode(Node* pN);
List newList(void);
void freeList(List* pL);

// Constructors-Destructors ---------------------------------------------------
	Node newNode(int data){
		Node new = malloc(sizeof(NodeObj));
		new->data = data;
		new->prev = NULL;
		new->next = NULL;
		return new;
	}
	
// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}
	
List newList(void){
	List newList = malloc( sizeof( ListObj));
	assert(newList);
	newList->top = NULL;
	newList->bot = NULL;
	newList->length = 0;
	newList->cursor = -1;
	return (newList);
}

//freeList()
//emptys the list and frees all associated nodes
void freeList(List* pL){
	if(pL!=NULL && *pL!=NULL) { 
		/*while( !isEmpty(*pL) ) {
		//	printf("inside freeListWhileloop\n");
		   deleteBack(*pL); 
		}*/
		clear(*pL);
	//printf("outside freeListWhileloop\n");
	    free(*pL);
	    *pL = NULL;
	}
}

// Access functions -----------------------------------------------------------

// isEmpty()
// Returns true if List is empty, false otherwise.
int isEmpty(List L) { 
	if( L->length == 0 ) return 1; 
	else return 0;   
}

// length()
// Returns length of List.
int length(List L){
	return L->length;
}

//int index()
// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
int index(List L){
	if(L->cursor < L->length){
		return L->cursor;
	}
	else if( L->cursor > L->length ) L->cursor = -1;
	else if( L->cursor == -1) return -1;
	return -1;
}

// front()
// Returns top element.
// Pre: !this.isEmpty()
int front(List L){
	if( isEmpty(L) ){
		printf("error: front() called on empty list.");
		exit(1);
	}
	return L->top->data;
}

// back()
// returns the last element
// Pre: length()>0
int back(List L){
	if(isEmpty(L) ){
		printf("error: back() called on empty list");
		exit(1);
	}
	return L->bot->data;
}

// get()
// returns cursor element
//Pre: length >0, index >= 0
int get(List L){
	if (length(L) < 1 || L->cursor < 0){
		printf("List error: get called on empty list or undefined cursor");
		exit(1);
	}
	Node temp = L->top;
	int tracker = 0;
	while( tracker < L->cursor ){
		temp = temp->next;
		tracker += 1;
	}		
	return temp->data;
}

// equals()
//  Returns true if B is a List storing
// the same integer sequence as A.
int equals(List A, List B){
	Node tempA = A->top;
	Node tempB = B->top;
	while(tempA != NULL && tempB != NULL){
		if(tempA->data != tempB->data){
			return 0;
		}
		tempA = tempA->next;
		tempB = tempB->next;
	}
	if(tempA == NULL && tempB == NULL) return 1;
	else return 0;
}

// Manipulation procedures ----------------------------------------------------

void clear(List L){
	while( !isEmpty(L) ) { 
		   deleteBack(L); 
	}
	L->top = NULL;
	L->bot = NULL;
	L->length = 0;
    L->cursor = -1;
	
	return;
}

// moveFront
// If List is non-empty, places the cursor under the front element
// otherwise does nothing.
void moveFront(List L){
	if( !(L->length == 0) ){
		L->cursor = 0;
		return;
	}
	else
		return;
}

// moveBack()
//If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
	if( !(L->length == 0) ){
		L->cursor = L->length - 1;
	}
	else
		return;
}

//movePrev
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L){
	if( L->cursor != -1){
		if( L->cursor > -1 ){
			L->cursor -= 1;
		}
	}
}

//moveNext
//If cursor is defined and not at back, moves cursor one step toward 
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing
void moveNext(List L){
	if( L-> cursor != -1 ){
		if( L->cursor < L->length ){
			L->cursor += 1;
		}
		else if( L->cursor >= L->length){
			L->cursor = -1;
		}
	}
}

// prepend
// Insert new element into this List.  If List is non-empty, 
// insertion takes place before front element.
void prepend(List L, int data){
	Node N = newNode(data);
	if( length(L) == 0 ) L->bot = N;
	else if( length(L) > 0 ){
		L->top->prev = N;
		N->next = L->top;
	}
	
	L->top = N;
	L->length += 1;
}

//void apppend (int data)
//Insert new element into this List.  If List is non-empty, 
// insertion takes place after back element.
void append(List L, int data){
	Node N = newNode(data);
	if( length(L) >1 ){
		L->bot->next = N;
		N->prev = L->bot;
	}
	else if( length(L) == 1 ){
		L->top->next = N;
		N->prev = L->top;
	}
	else if( length(L) == 0 ){
		L->top = N;
	}
	L->bot = N;
	L->length += 1;
}

//void insertBefore(int data)
// Insert new element before cursor.
//Pre: length()>0, index() >=0
void insertBefore(List L, int data){
	if ( length(L) < 0 ){
		printf("List error: insertBefore called on empty list");
		exit( 1);
	}
	if ( index(L) < 0 ){
		printf("List error: insertBefore called on undefined cursor");
		exit(1);
	}
	Node nuevo = newNode(data);
	Node temp = L->top;
	int tracker = 0;
	while( tracker < L->cursor ){
		temp = temp->next;
		// iterate to the node the cursor is on
		tracker += 1;
	}
	nuevo->next = temp;
	if( temp->prev != NULL ){
		temp->prev->next = nuevo;
	}
	if(L->cursor == 0) L->top = nuevo;
	nuevo->prev = temp->prev;
	temp->prev = nuevo;
	L->length += 1;
	moveNext(L);
}

//void insertAfter(int data)
// Insert new element before cursor.
//Pre: length()>0, index() >=0
void insertAfter(List L, int data){
	if ( length(L) < 1 || index(L) < 1 ){
	   printf("List error: insertBefore called on improperly sized|formatted list\n");
		exit(1);
	}
	Node nuevo = newNode(data);
	Node temp = L->top;
	int tracker = 0;
	while( tracker < L->cursor ){
		temp = temp->next;
		// iterate to the node the cursor is on
		tracker += 1;
	}
	nuevo->prev = temp;
	nuevo->next = temp->next;
	if((L->length-1) != L->cursor) temp->next->prev = nuevo;
	if((L->length-1) == L->cursor) L->bot= nuevo;
	temp->next = nuevo;
	L->length += 1;
}

//deleteFront()
// Deletes the front element. Pre: length()>0
void deleteFront(List L){
	if ( length(L) < 1 ){
		printf("List error: deleteFront called on improperly sized list\n");
		exit(1);
	}
	Node X = L->top;
	if(L->length > 1){ 
	    L->top = L->top->next;
	    L->top->prev = NULL;
	}
	else if(L->length == 1){
		L->top = NULL;
    }
	X->next = NULL;
	freeNode(&X);
	X = NULL;
	L->length -= 1;
}

//deleteBack()
// Deletes the back element. Pre: length()>0
void deleteBack(List L){
	if ( length(L) < 1 ){
		printf("List error: deleteBack called on improperly sized list\n");
		exit(1);
	}
	Node X = L->bot;
	L->bot = L->bot->prev;
	freeNode(&X);
	L->length -= 1;
	if(L->bot != NULL) L->bot->next = NULL;	
}

// void delete()
// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index() >=0
void delete(List L){
	Node temp = L->top;
	int tracker = 0;
	while( tracker < L->cursor ){
		temp = temp->next;
		// iterate to the node the cursor is on
		tracker += 1;
	}
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	temp->prev = NULL;
	temp->next = NULL;
	freeNode(&temp);
	temp = NULL;
	L->length -= 1;
	L->cursor = -1;
}


// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){

	if( L == NULL ){
      printf("Queue Error: calling printList() on NULL Queue reference\n");
      exit(1);
    }
	Node temp = L->top;
    while(temp != NULL){
		
		//fprintf(out, "inside printList\n");
        fprintf(out,"%d ", temp->data);
        temp = temp->next; 
    }
	return;
}


List copyList(List L){
	List C = newList();
	Node temp = L->top;

	while(temp != NULL){
        append(C, temp->data);
        temp = temp->next;
    }
	return C;
	
}	
	
