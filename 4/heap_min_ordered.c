#include <stdbool.h>
#include <stdlib.h>

#include "heap_min_ordered.h"

/**
 * Returns 1 if the tree-based heap is in min-heap order.
 * You may assume an empty tree is in min-heap order.
 * You may assume a single node is in min-heap order.
 */
bool heap_min_ordered_p (node *tree)
{
    //Return true for empty nodes/tree
	if (tree == NULL) return true;
	
	if (heap_min_ordered_p(tree->left) == true && heap_min_ordered_p(tree->right) == true) {
	    
	    if ((tree->left == NULL || tree->left->item >= tree->item) && 
	        (tree->right == NULL || tree->right->item >= tree->item)) {
	        
	        return true;
        }
	}   
		
	return false;
}
