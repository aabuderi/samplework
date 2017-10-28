//Adam Buderi 1451707
//pa4
//FindPath.c
//implements pa4 FindPath algorithm
//----------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Graph.h"
#define MAX_LEN 160 

int main(int argc, char * argv[]){
	
	int n, u, v, i;
    FILE *in, *out;
    char line[MAX_LEN];
 
    // check command line for correct number of arguments
    if( argc != 3 ){
       printf("Usage: %s <input file> <output file>\n", argv[0]);
       exit(1);
    }
   
    // open files for reading and writing 
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in==NULL ){
       printf("Unable to open file %s for reading\n", argv[1]);
       exit(1);
    }
    if( out==NULL ){
       printf("Unable to open file %s for writing\n", argv[2]);
       exit(1);
    }
	
	//section reads first line and initializes the graph
	fgets(line, MAX_LEN, in);
	sscanf(line, "%d ", &n);
	Graph G = newGraph(n);
	List topSortStack = newList();
	for( i = 1; i <=n; i++){		//create the initial stack that allows DFS to be run the first time
		append(topSortStack, i);
	}
	
	/* read each line of input file, then add corresponding arcs to graph */
    while( fgets(line, MAX_LEN, in) != NULL)  {
		sscanf(line, "%d %d", &u, &v);
		if(u ==0 && v==0)break;
		else 
			addArc(G, u, v);
	}
	fprintf(out,"Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n");
	//done with part one of findComponents

	//part 2 of findComponents
	DFS(G, topSortStack);

	Graph gTrans = transpose(G);
	DFS(gTrans, topSortStack);


	
	
	int counter=0, pop;
	i=1;
	List componentList = newList();
	moveFront(topSortStack);
	while(index(topSortStack) != -1){	//count the number of connected components in G
		pop = get(topSortStack);
		if(getParent(gTrans, pop) == NIL) counter++;
		moveNext(topSortStack);
	}
	fprintf(out, "G contains %d strongly connected components:\n", counter);
	moveBack(topSortStack);
	while(index(topSortStack) != -1){	//print the connected components of G
		pop = get(topSortStack);
		movePrev(topSortStack);
		prepend(componentList, pop);
		if(getParent(gTrans,pop) == NIL){
			fprintf(out, "Component %d: ", i++);
			printList(out, componentList);
			fprintf(out, "\n");
			clear(componentList);
		}
	}
	
	freeList(&componentList);
	freeList(&topSortStack);
	freeGraph(&G);
	freeGraph(&gTrans);
	fclose(in);
	fclose(out);
}