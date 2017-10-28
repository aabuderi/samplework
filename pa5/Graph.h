//Graph.h
//header file for Graph.c in pa4
#include <stdlib.h>
#include<stdio.h>
#include <assert.h>
//macro definitions-----------------------------------------------
#define WHITE -1
#define GREY 0
#define BLACK 1
#define INF -30
#define NIL -20
#include "List.h"

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

typedef struct GraphObj* Graph;

/***Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/

int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge( Graph G, int u, int v);
void addArc( Graph G, int u, int v);
void DFS( Graph G, List S);
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif