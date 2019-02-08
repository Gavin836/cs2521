#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <float.h>
#include <limits.h>

#include "Graph.h"

// wgraph_adjmatrix.c

// since 0 is a valid weight, can't use it for "no edge"
// need a distinguished value to indicate "no edge"
#define NO_EDGE FLT_MAX  // imaginary distinguished float value

typedef struct GraphRep {
    int    nV;    // #vertices
    int    nE;    // #edges
    float **edges; // matrix of weights
} GraphRep;

// check whether two vertices are connected
int neighbours (Graph g, Vertex v, Vertex w)
{
    assert (validV (g, v) && validV (g, w));
    return (g->edges[v][w] != NO_EDGE);
}

// make new graph with nV vertices
Graph newGraph (int nV)
{
    assert (nV >= 0);
    int i, j;
    float **e = malloc (nV * sizeof (float *));
    assert (e != NULL);
    for (i = 0; i < nV; i++) {
        e[i] = malloc (nV * sizeof (float));
        assert (e[i] != NULL);
        for (j = 0; j < nV; j++)
            e[i][j] = NO_EDGE;
    }
    Graph g = malloc (sizeof (GraphRep));
    assert (g != NULL);
    g->nV = nV;
    g->nE = 0;
    g->edges = e;
    return g;
}

// free memory allocated to graph
void dropGraph (Graph g)
{
    assert (g != NULL);
    int i;
    for (i = 0; i < g->nV; i++)
        free (g->edges[i]);
    free (g->edges);
    free (g);
}

// show "printable" representation of graph
void showGraph (Graph g, char **city)
{
    assert (g != NULL);
    printf ("V=%d, E=%d\n", g->nV, g->nE);
    int i, j;
    for (i = 0; i < g->nV; i++) {
        int nshown = 0;
        for (j = i + 1; j < g->nV; j++) {
            float wt = g->edges[i][j];
            if (wt != NO_EDGE) {
                printf ("%s-%0.1f-%s ", city[i], wt, city[j]);
                nshown++;
            }
        }
        if (nshown > 0)
            printf ("\n");
    }
}

// add new edge to a graph
void insertE (Graph g, Edge e)
{
    assert (g != NULL);
    Vertex v = e.src, w = e.dest;
    assert (validV (g, v) && validV (g, w));
    if (g->edges[v][w] == NO_EDGE)
        g->nE++;
    g->edges[v][w] = e.weight;
}

// remove an edge from a graph
void removeE (Graph g, Edge e)
{
    assert (g != NULL);
    Vertex v = e.src, w = e.dest;
    assert (validV (g, v) && validV (g, w));
    if (g->edges[v][w] == NO_EDGE)
        return;
    g->edges[v][w] = NO_EDGE;
    g->edges[w][v] = NO_EDGE;
    g->nE--;
}

// returns #vertices & array of edges
int edges (Graph g, Edge *es, int nE)
{
    assert (g != NULL && es != NULL);
    assert (nE >= g->nE);
    int i, j, n = 0;
    for (i = 0; i < g->nV; i++) {
        for (j = i + 1; j < g->nV; j++) {
            if (g->edges[i][j] != NO_EDGE) {
                assert (n < nE);
                es[n++] = mkEdge (g, i, j, g->edges[i][j]);
            }
        }
    }
    return n;
}

// is a vertex valid in a given Graph?
int validV (Graph g, Vertex v)
{
    return (g != NULL && v >= 0 && v < g->nV);
}

// make an Edge value
Edge mkEdge (Graph g, Vertex v, Vertex w, float weight)
{
    assert (validV (g, v) && validV (g, w));
    return (Edge) { .src = v, .dest = w, .weight = weight };
}
// compare Edge weights
float compareE (Edge e1, Edge e2)
{
    return e1.weight - e2.weight;
}
