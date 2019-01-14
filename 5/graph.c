// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "Graph.h"
#include "Queue.h"

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	Edge new = {v,w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge(Graph g, Vertex v, Vertex w, int wt)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] == 0) {
		g->edges[v][w] = wt;
		g->edges[w][v] = wt;
		g->nE++;
	}
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] != 0) {
		g->edges[v][w] = 0;
		g->edges[w][v] = 0;
		g->nE--;
	}
}

// create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	int v, w;
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nV = nV; new->nE = 0;
	new->edges = malloc(nV*sizeof(int *));
	assert(new->edges != 0);
	for (v = 0; v < nV; v++) {
		new->edges[v] = malloc(nV*sizeof(int));
		assert(new->edges[v] != 0);
		for (w = 0; w < nV; w++)
			new->edges[v][w] = 0;
	}
	return new;
}

// free memory associated with graph
void dropGraph(Graph g)
{
	assert(g != NULL);
	// not needed for this lab
}

// display graph, using names for vertices
void showGraph(Graph g, char **names)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d %s\n",v,names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf("\t%s (%d)\n",names[w],g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath(Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert(g != NULL);
	
	Queue searchQueue = newQueue();
	bool *visited = calloc((size_t)g->nV, sizeof(bool));
	Vertex *sTree = calloc((size_t)g->nV, sizeof(int));
	
	//Intialise the array to -1
	for (int j = 0; j < g->nV; j++){
		visited[j] = false;
		sTree[j] = -1;
	}
    
    int count = 0;
	Vertex it;
	QueueJoin(searchQueue, src);
    sTree[src] = src;
    visited[src] = true;
    
	while (!QueueIsEmpty(searchQueue)) {
		it = QueueLeave(searchQueue);

		for (int i = 0; i < g->nV; i++) {
			if (g->edges[it][i] > 0 && visited[i] == false) {

				if (g->edges[it][i] < max) {
				    QueueJoin(searchQueue, i);
				    visited[i] = true;
				    sTree[i] = it;
				}

			}
		}
	    //showQueue(searchQueue);
	}
	/*
	printf("Max %d, Source %d, Dest %d\n", max, src, dest);
	for (int k = 0; k < g->nV; k++) {
	    printf("%d | %d\n", k, sTree[k]);
	}
	*/
	
	if (sTree[dest] != -1) {
        //Count hops
        count = 2;                              //start and end cities
        Vertex curr = dest;
        while (sTree[curr] != src) {
            count++;
            curr = sTree[curr];
        }
        //Set flight path
        path[0] = src;
        curr = sTree[dest];
        
        for (int j = 2; j < count; j++) {
            path[count - j] = curr;
            curr = sTree[curr]; 
        }
        
        path[count - 1] = dest;
	}

	free(visited);
	dropQueue(searchQueue);
	
	if (count > 0) return count;

	return 0;
}

#if 0
void graph_bfs (Graph g, vertex v,
        size_t *count, vertex pre[], vertex st[])
{
        Queue s = queue_new ();
        queue_en (s, (edge){ v, v });
        while (queue_size (s) > 0) {
                edge e = queue_de (s);
                if (pre[e.w] != -1) continue;
                pre[e.w] = (*count)++; st[e.w] = e.v;
                printf ("%d\n", e.w);
                for (int i = 0; i < g->nV; i++) {
                        if (has_edge (g, e.w, i) && pre[i] == -1)
                                queue_en (s, (edge){ e.w, i });
                }
        }
}
#endif

