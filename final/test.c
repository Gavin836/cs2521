#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Graph.h"

// make some assumptions on much data is supplied
#define MAXCITIES 40
#define MAXNAME   20

int main(void) {
    Graph world;           // graph of world/distances
	FILE *data;            // file handle
	char  name[MAXNAME+2]; // input buffer to hold city name lines
	int   ncities;         // how many cities
	char *city[MAXCITIES]; // array of up to MAXCITIES city names
	int   maxflt;          // max length of flights
	
	// get array of city names (assumes < MAXCITIES names)
	if ((data = fopen("ha30_name.txt","r")) == NULL) {
		perror("Couldn't open file: ha30_name.txt");
	}
	ncities = 0;
	while (fgets(name,MAXNAME,data) != NULL) {
		name[strlen(name)-1] = '\0';
		city[ncities] = strdup(name);
		ncities++;
	}
	fclose(data);

	// make empty Graph
	world = newGraph(ncities);

	// get distances and populate Graph edges
	if ((data = fopen("ha30_dist.txt","r")) == NULL) {
		perror("Couldn't open file: ha30_dist.txt");
	}
	int n=0, fromCity, toCity, distance;
	Edge curr;
	while (fscanf(data,"%d",&distance) == 1) {
		fromCity = n / ncities;
		toCity = n % ncities;
		// convert miles to km
		curr = mkEdge(world, toCity, fromCity, distance);
		insertE(world, curr);
		n++;
	}
	fclose(data);
	
	showGraph(world, city);
	dropGraph(world);
	
	return 0;
}
