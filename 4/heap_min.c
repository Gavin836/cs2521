#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "heap_min.h"

/**
 * Return `true` if the array heap with a sepcified number of items is
 * in heap order.  You must assume that the heap items are in indexes
 * 1..heap_size, and that index 0 is empty and not used to store items.
 */
 

bool heap_min_p (int heap[], size_t heap_size)
{
    // Begin at the first child of the root
	for (int i = 2; (size_t)i <= heap_size; i++) {
	    
	    if (heap[i] < heap[i / 2]) return false;
	    
	}
	
	return true;
}



#if 0
// More efficient
bool heap_min_p (int heap[], size_t heap_size)
{
    
    int i = 0;
    int val = 0;
    
    while ( (int)heap_size > pow(i + 1, 2) ){
        val = pow(i,2);
        i++;
    }
	
	return true;
}
#endif
