// Adam Buderi 1451707
// pa4
// Graph.c- contains the methods used by the Graph datatype
//----------------------------------------------------------------

//includes--------------------------------------------------------
#include <stdlib.h>
#include<stdio.h>
#include <assert.h>
#include "Graph.h"
#include "List.h"



//Helper Function decclaration
void visit(Graph G, int u, int * time,List S);

//graph declaration-----------------------------------------------
typedef struct GraphObj{
	int order; //nmber of vertices
	int size;
	List * neighbors;
	int * colors; //-1 is white, 0 is grey, 1 is black
	int * parent;
	int * discover;
	int * finish;
}GraphObj;

/***Constructors-Destructors ***/
Graph newGraph(int n){
	int arrayLength = n+1;
	Graph newGraph = malloc(sizeof( GraphObj ));
	assert(newGraph);
	newGraph->neighbors = (List *) malloc(arrayLength * sizeof(List));
	for(int i =1;i<arrayLength;i++){
		newGraph->neighbors[i] = newList();
	}
	newGraph->colors = (int *) malloc(arrayLength * sizeof(int));
	newGraph->parent = (int *) malloc(arrayLength * sizeof(int));
	newGraph->discover = (int *) malloc(arrayLength * sizeof(int)) ;
	newGraph->finish = (int *) malloc(arrayLength * sizeof(int)) ;
	newGraph->order = n;
	newGraph->size = 0;
	return newGraph;
}
 
void freeGraph(Graph* pG){
	if(pG != NULL && *pG != NULL){
		
		for(int i=1; i<((*pG)->order+1); i++){
			freeList( &( (*pG)->neighbors[i]));
		}
		free( (*pG)->neighbors);
		free( (*pG)->parent);
		free(  (*pG)->discover);
		free( (*pG)->colors);
		free( (*pG)->finish);
		(*pG)->order = 0;
		(*pG)->size = 0;
		free(*pG);
		
	}
}

Graph transpose(Graph G){
	Graph transposeGraph = newGraph(G->order);
	int listArrayLength = G->order + 1;
	int neighbor;
	List adjacency;
	for(int i =1;i<listArrayLength;i++){
		adjacency = G->neighbors[i];
		moveFront(adjacency);
		while(index(adjacency)!= -1){
			neighbor = get(adjacency);
			addArc(transposeGraph, neighbor, i);
			moveNext(adjacency);
		}
	}
	return transposeGraph;
}

Graph copyGraph(Graph G){
	Graph newCopy = newGraph(G->order);
	int listArrayLength = G->order + 1;
	List adjacency;
	int neighbor;
	for(int i =1; i<listArrayLength; i++){
		adjacency = G->neighbors[i];
		moveFront(adjacency);
		while(index(adjacency)!= -1){
			neighbor = get(adjacency);
			addArc(newCopy, i, neighbor);
			moveNext(adjacency);
		}
	}
	return newCopy;
}

/*** Access functions ***/

int getOrder(Graph G){
	return G->order;
}

int getSize(Graph G){
	return G->size;
}



//pre: 1<= u <= getOrder(G)
int getParent(Graph G, int u){
	if( !(1<= u) && !(u<= getOrder(G))){
		printf("error: precondition 1<= u <= getOrder(G) not met.");
		exit(1);
	}
	return G->parent[u];
}


int getDiscover(Graph G, int u){
	if( !(1<= u) && !(u<= getOrder(G))){
		printf("error: precondition 1<= u <= getOrder(G) not met.");
		exit(1);
	}
	return G->discover[u];
}

int getFinish(Graph G, int u){
	if( !(1<= u) && !(u<= getOrder(G))){
		printf("error: precondition 1<= u <= getOrder(G) not met.");
		exit(1);
	}
	return G->finish[u];
}



/*** Manipulation procedures ***/
void makeNull(Graph G){
	for(int i=1; i<(G->order+1); i++){
			while(!isEmpty(G->neighbors[i])){
				deleteBack(G->neighbors[i]);
			}
	}
	G->size = 0;
}

void addEdge( Graph G, int u, int v){
	if((1>u || u>getOrder(G)) ){
		printf("error: vertex u is outside of the order of the graph\n");
		exit(1);
	}
	if((1>v || v> getOrder(G)) ){
		printf("error: vetex v is outside of the order of the graph\n");
		exit(1);
	}	
	int vertex;
	if(isEmpty(G->neighbors[u])) prepend(G->neighbors[u], v); //add v to u's adjacency list
	else{
		moveFront(G->neighbors[u]);
		while(index(G->neighbors[u]) > -1){
			vertex = get(G->neighbors[u]);
			if(vertex > v){
				insertBefore(G->neighbors[u], v);
				
				break;
			}
			else if(vertex == v){
				break;
			} 
			moveNext(G->neighbors[u]);
			if(index(G->neighbors[u]) == -1){
				if( back(G->neighbors[u]) < v){
					append(G->neighbors[u],v);
					break;
				}
			}
		}
	}	if(isEmpty(G->neighbors[v])) prepend(G->neighbors[v], u); //add v to u's adjacency list
	else{
		moveFront(G->neighbors[v]);
		while(index(G->neighbors[v]) > -1){
			vertex = get(G->neighbors[v]);
			if(vertex > u){
				insertBefore(G->neighbors[v], u);
				
				break;
			}
			else if(vertex == u){
				break;
			} 
			moveNext(G->neighbors[v]);
			if(index(G->neighbors[v]) == -1){
				if( back(G->neighbors[v]) < u){
					append(G->neighbors[v],u);
					break;
				}
			}
		}
	}
	G->size += 1;
	}

void addArc( Graph G, int u, int v){
	if((1>u || u>getOrder(G)) ){
		printf("error: vertex u is outside of the order of the graph\n");
		exit(1);
	}
	if((1>v || v> getOrder(G)) ){
		printf("error: vetex v is outside of the order of the graph\n");
		exit(1);
	}
	int vertex;
	if(isEmpty(G->neighbors[u])) prepend(G->neighbors[u], v); //add v to u's adjacency list
	else{
		moveFront(G->neighbors[u]);
		while(index(G->neighbors[u]) > -1){
			vertex = get(G->neighbors[u]);
			if(vertex > v){
				insertBefore(G->neighbors[u], v);
				G->size += 1;
				break;
			}
			else if(vertex == v){
				break;
			} 
			moveNext(G->neighbors[u]);
			if(index(G->neighbors[u]) == -1){
				if( back(G->neighbors[u]) < v){
					append(G->neighbors[u],v);
					break;
				}
			}
		}
	}
	
}
/* Pre:  length(S)==getOrder(G) */
void DFS(Graph G, List S){
	if(!(length(S) == getOrder(G))){
		printf("error: List S is not the same length as the order of G\n");
		exit(1);
	}
	int time = 0;
	int i;
	for( i = 1; i <= getOrder(G); i++){
		G->colors[i] = WHITE;
		G->parent[i] = NIL;
	}
	moveFront(S);
	int u;

	for( i=1; i<=getOrder(G);i++){		//process the list in the order of the stack
		u = get(S);
		if(G->colors[u] == WHITE){
			visit(G, u, &time, S); 
		}
		moveNext(S);
	}

	for(i=1; i <= getOrder(G); i++){
		deleteFront(S);				//delete the previous stack from the list hopefully, as each run of DFS will process and
	}    							//re add n elements to the stack
	moveFront(S);
	for(i=1;i <= getOrder(G); i++){ //reorder S 
		prepend(S, get(S));
		moveNext(S);
		moveNext(S);
	}
	for(i=1; i <= getOrder(G); i++){
		deleteBack(S);				
	} 
}

void visit(Graph G, int u, int * time, List S){
	*time = *time + 1;	//white vertex has just been disccovered
	G->discover[u] = *time;
	G->colors[u] = GREY;
	List adjacency = G->neighbors[u];
	moveFront(adjacency);
	int i;
	while(index(adjacency) > -1){	//explore adjacency list of u
		i = get(adjacency);
		if(G->colors[i] == WHITE){
			G->parent[i] = u;
			visit(G, i, time, S);
		}
		moveNext(adjacency);
	}
	G->colors[u] = BLACK;		//u is processed
	append(S, u);	//u is pushed onto the stack
	//printf("calling printList in DFS visit	");
	//printList(stdout, S);
	*time = *time + 1;
	G->finish[u] = *time;
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	
	for(int i = 1; i < (G->order +1); i++){
		fprintf(out, "%d: ", i);
		printList(out, G->neighbors[i]);
		fprintf(out, "\n");
	}
}
