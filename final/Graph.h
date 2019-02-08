#include <stdio.h>

// wgraph.h

// visible data structures for Graphs
typedef struct GraphRep *Graph;
// vertices denoted by integers 0..N-1
typedef int Vertex;
// edges are end-points + weight
typedef struct { Vertex src; Vertex dest; float weight; } Edge;
// auxiliary operations on graphs
int validV(Graph,Vertex); // validity check
Edge mkEdge(Graph, Vertex, Vertex, float); // edge creation
int neighbours(Graph, Vertex, Vertex); // edge existence
float compareE(Edge e1, Edge e2); // compare edge weights
// core operations on graphs
// make new graph with nV vertices
Graph newGraph(int nV);
// free memory allocated to graph
void dropGraph(Graph);
// show "printable" representation of graph
void showGraph(Graph, char **city);
// add new edge to a graph
void insertE(Graph, Edge);
// remove an edge from a graph
void removeE(Graph, Edge);
// returns #vertices & array of edges
int edges(Graph, Edge *, int);

typedef Graph MSTree; // an MST is a specialised Graph

// EOF
