////////////////////////////////////////////////////////////////////////
// COMP2521 19t0 ... the Fury of Dracula
// Map.c: an implementation of a Map type
// You can change this as much as you want!
//
// 2017-11-30   v1.0    Team Dracula <cs2521@cse.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "map.h"
#include "places.h"

#define MAX_SEAS 2
#define NO_TRANS 3

typedef struct vNode *VList;
struct vNode {
	LocationID  v;    // ALICANTE, etc
	TransportID type; // ROAD, RAIL, BOAT
	VList       next; // link to next node
};

struct map {
	int nV; // #vertices
	int nE; // #edges
	VList connections[NUM_MAP_LOCATIONS]; // array of lists
};

static void addConnections(Map);
VList find_vlist(Map g, LocationID find, int max);
int find_connect(VList main, LocationID find);

// Create a new empty graph (for a map)
// #Vertices always same as NUM_PLACES
Map
newMap (void)
{
	Map g = malloc (sizeof *g);
	if (g == NULL) err (EX_OSERR, "couldn't allocate Map");

	(*g) = (struct map){
		.nV = NUM_MAP_LOCATIONS,
		.nE = 0,
		.connections = { NULL }
	};

	addConnections (g);
	return g;
}

// Remove an existing graph
void disposeMap (Map g)
{
	// wait, what?
	if (g == NULL) return;

	for (int i = 0; i < g->nV; i++) {
		VList curr = g->connections[i];
		while (curr != NULL) {
			VList next = curr->next;
			free (curr);
			curr = next;
		}
	}
	free (g);
}

static VList insertVList (VList L, LocationID v, TransportID type)
{
	VList new = malloc (sizeof(struct vNode));
	if (new == NULL) err (EX_OSERR, "couldn't allocate vNode");

	(*new) = (struct vNode){
		.v = v,
		.type = type,
		.next = L
	};
	return new;
}

static int inVList (VList L, LocationID v, TransportID type)
{
	for (VList cur = L; cur != NULL; cur = cur->next)
		if (cur->v == v && cur->type == type)
			return 1;

	return 0;
}

// Add a new edge to the Map/Graph
static void addLink (Map g, LocationID start, LocationID end, TransportID type)
{
	assert (g != NULL);

	// don't add edges twice
	if (inVList (g->connections[start], end, type)) return;

	g->connections[start] = insertVList(g->connections[start],end,type);
	g->connections[end] = insertVList(g->connections[end],start,type);
	g->nE++;
}

static const char *typeToString (TransportID t)
{
	switch (t) {
	case ROAD: return "road";
	case RAIL: return "rail";
	case BOAT: return "boat";
	default:   return "????";
	}
}

// Display content of Map/Graph
void showMap (Map g)
{
	assert (g != NULL);

	printf ("V=%d, E=%d\n", g->nV, g->nE);
	for (int i = 0; i < g->nV; i++)
		for (VList n = g->connections[i]; n != NULL; n = n->next)
			printf ("%s connects to %s by %s\n",
					idToName (i), idToName (n->v), typeToString (n->type));
}

// Return count of nodes
int numV (Map g)
{
	assert (g != NULL);
	return g->nV;
}

// Return count of edges of a particular type
int numE (Map g, TransportID type)
{
	assert (g != NULL);
	assert (0 <= type && type <= ANY);

	int nE = 0;
	for (int i = 0; i < g->nV; i++)
		for (VList n = g->connections[i]; n != NULL; n = n->next)
			if (n->type == type || type == ANY)
				nE++;

	return nE;
}

// Add edges to Graph representing map of Europe
static void addConnections (Map g)
{
#define IS_SENTINEL(x) ((x).v == -1 && (x).w == -1 && (x).t == ANY)
	for (int i = 0; ! IS_SENTINEL (CONNECTIONS[i]); i++)
		addLink (g, CONNECTIONS[i].v, CONNECTIONS[i].w, CONNECTIONS[i].t);
}

int connections (Map g, LocationID start, LocationID end, TransportID type[])
{
	assert (g != NULL);
	
	int no_conn = 0;
    LocationID seas[MAX_SEAS] = {0};
	int sea_index = 0;
	
	//Find the approprite list of connections

	VList curr = g->connections[start];
    
    // Direct connections
	while (curr != NULL) {
	    
	    //If start is a port and end is also a port, keep track of the sea.
	    if ((curr->type == BOAT) && (idToType(start) == LAND) && (idToType(end) == LAND)) {
	        seas[sea_index] = curr->v;
	        sea_index++;
	    }
	    
	    if (curr->v == end) {
	        type[no_conn] = curr->type;
	        no_conn++;
	    }
	    
	    curr = curr->next;
	}
	
	// Determine whether the ports are connected
	if (sea_index > 0 && no_conn < NO_TRANS) {
	    
	    //Increment through the seas to determine if it connects to end's port
	    for (int i = 0; i < sea_index; i++) {

	        curr = g->connections[seas[i]];
	        
	        if (find_connect(curr, end)) {
	            type[no_conn] = curr->type;
	            no_conn++;
	            break;
	        }
	    }   
	    
	}
	
	return no_conn;
}

//Find if the "find" exists within the "main" vlist
int find_connect(VList main, LocationID find){
    while (main != NULL) {     
        if (main->v == find) return 1;
        
        main = main->next;
    }
    
    return 0;
}

