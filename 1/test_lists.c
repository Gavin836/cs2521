// COMP2521 19T0 ... lab 01: test a linked list implementation
//
// YYYY-mm-dd	Your Name Here <zNNNNNNN@student.unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "lists.h"

void test_zero(link list);
void test_one(link list);
void test_two(link list);

int main (void)
{
	// Creates an empty list, and then prints it.
	link list = NULL;
	list_print (list);

	// You should write some tests here. (And remove this comment.)
    test_zero(list);
    test_one(list);
    test_two(list);
    
	return EXIT_SUCCESS;
}


// Addition function tests
void test_zero(link list) {
    
    list_print (list);
    assert(list_sum_items(list) == 0);

}

void test_one(link list) {
    
    Item item_one = 1;
    link new_node = node_new(item_one);
    list = new_node;
    list_print (list);
    
    assert(list_sum_items(list) == 1);
    
}

void test_two (link list) {
    Item item_one = 1;
    link new_node = node_new(item_one);
    list = new_node;
    
    Item item_two = 2;
    new_node = node_new(item_two);
    list_insert_next(list, new_node);
    
    list_print (list);
    assert(list_sum_items(list) == 3);
    
}
