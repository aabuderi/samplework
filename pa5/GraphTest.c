// Adam Buderi 1451707
// pa3
// GraphTest.c- Tests the Graph datatype (incorporates GraphClient.c)
//----------------------------------------------------------------

//includes--------------------------------------------------------
#include <stdlib.h>
#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#include "Graph.h"


int main(int argc, char* argv[]){
	List S = newList();
	for(i=1; i<=8; i++) append(S, i);
	Graph A = newGraph(8);
	addArc(A, 1, 2);
	addArc(A, 2, 3);
	addArc(A, 2, 5);
	addArc(A, 2, 6);
	addArc(A, 3, 4);
	addArc(A, 3, 7);
	addArc(A, 4, 3);
	addArc(A, 4, 8);
	addArc(A, 5, 1);
	addArc(A, 5, 6);
	addArc(A, 6, 7);
	addArc(A, 7, 6);
	addArc(A, 7, 8);
	addArc(A, 8, 8);
	printf("addArc passed. starting with access functions\n");
	printf("order: %d  size: %d \n", getOrder(A), getSize(A));
	printGraph(stdout, A);

	printf("access functions passed. starting with DFS\n");
	
	
	DFS(A, S);
	fprintf(stdout, "\n");
    fprintf(stdout, "x:  d  f  p\n");
    for(i=1; i<=n; i++){
		parent=getParent(G, i);
	 	if(parent<=0) parent=0;
	    printf("%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), parent);
    }
	printf("DFS passed. starting with\n");
	List path = newList();
	getPath(path, A, 3);
	printList(stdout, path);//2 1 3
	printf("\n");
	
	printf("getPath passed. starting with getParent()\n");
	printf("%d\n", getParent(A, 3)); //1
	
	printf("getParent passed. Starting with getDist()\n");
	printf("%d\n", getDist(A, 3)); //2
	
	printf("getDist() passed. Starting with makeNull()\n");
	makeNull(A);
	
	printf("makeNull passed. Starting with freeGraph()\n");
	freeGraph(&A); //freeing null graph
	freeGraph(&B); //freeing non-null graph
	
	int i, s, max, min, d, n=35;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Print adjacency list representation of G
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);

   return(0);
	
}