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
void test_neg_bst(void);

int main (void)
{
	white_box_tests ();

	// add more tests of your own!
    test_leaf1();
    test_leaf3();
    
    test_neg_bst();
    
	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}

void test_leaf1(void){
    Item it = int_item_new(5);
    BTreeNode Tree = NULL;
    Tree = btree_insert(Tree, it);
    
    assert(Tree != NULL);
    assert(btree_search(Tree, it) != NULL);
    
    assert(btree_size(Tree) == 1);
    assert(btree_size_leaf(Tree) == 1);
    
    assert(btree_count_if(Tree, even_p) == 0);
    assert(btree_count_if(Tree, odd_p) == 1);
    assert(btree_count_if(Tree, negative_p) == 0);
    
    btree_drop(Tree);
}

void test_leaf3(void){
    Item it = int_item_new(5);
    BTreeNode Tree = NULL;
    Tree = btree_insert(Tree, it);

    
    it = int_item_new(10);
    Tree = btree_insert(Tree, it);
    
    it = int_item_new(1);
    Tree = btree_insert(Tree, it);  
    
    assert(btree_size(Tree) == 3);
    assert(btree_size_leaf(Tree) == 2);
    
    assert(btree_count_if(Tree, even_p) == 1);
    assert(btree_count_if(Tree, odd_p) == 2);
    assert(btree_count_if(Tree, negative_p) == 0);
    
    btree_drop(Tree);
}

void test_neg_bst(void){
    Item it = int_item_new(-5);
    BTreeNode Tree = NULL;
    Tree = btree_insert(Tree, it);

    
    it = int_item_new(-10);
    Tree = btree_insert(Tree, it);
    
    it = int_item_new(1);
    Tree = btree_insert(Tree, it);  
    
    assert(btree_size(Tree) == 3);
    assert(btree_size_leaf(Tree) == 2);
    
    assert(btree_count_if(Tree, even_p) == 1);
    assert(btree_count_if(Tree, odd_p) == 2);
    assert(btree_count_if(Tree, negative_p) == 2);
    
    btree_drop(Tree);

}
