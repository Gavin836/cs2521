////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- Test a binary search tree implementation.
//
// 2018-12-08	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// YYYY-mm-dd	Your Name Here <zNNNNNNN@student.unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "item_int.h"
#include "btree.h"
#include "testable.h"

void test_leaf1(void);
void test_leaf3(void);

int main (void)
{
	white_box_tests ();

	// add more tests of your own!
    test_leaf1();
    //test_leaf3();
    
	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}

void test_leaf1(void){
    Item it = int_item_new(5);
    btree_node tree = btree_node_new(it);
    
    assert(btree_size(tree) == 1);
}

void test_leaf3(void){
    Item it = int_item_new(5);
    btree_node tree = btree_node_new(it);
    
    it = int_item_new(10);
    btree_insert(tree, it);
    
    it = int_item_new(1);
    btree_insert(tree, it);
    
    assert(btree_size(tree) == 3);
}

