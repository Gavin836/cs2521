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
void test_three(link list);

void test_circular0(int no);
void test_circular1(int no);
void test_circular2(int no);
void test_circular3(int no);

void create_dlink_zero (void);
void create_dlink_one (void);
void create_dlink_two (void);
void create_dlink_three (void);

int main (void)
{
	// Creates an empty list, and then prints it.
	link list = NULL;
	list_print (list);

	// You should write some tests here. (And remove this comment.)
        
    test_zero(list);
    test_one(list);
    test_two(list);
    test_three(list);
    
    test_circular0(0);
    test_circular1(1);
    test_circular2(2);
    test_circular3(3);
    
    create_dlink_zero();
    create_dlink_one();
    create_dlink_two();
    create_dlink_three();
    
    printf("Tests successful!\n");      
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
    list_drop(list);
    
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
    list_drop(list);
    
}

void test_three (link list) {
    Item item_one = 1;
    link new_node = node_new(item_one);
    list = new_node;
    
    Item item_two = 2;
    new_node = node_new(item_two);
    list_insert_next(list, new_node);
   
    Item item_three = 3;
    new_node = node_new(item_three);
    list_insert_next(list, new_node);
    
    list_print (list);
    assert(list_sum_items(list) == 6);
    list_drop(list);   
}

void test_circular0(int no){
    clist_print(NULL);
    assert(clist_new(no) == NULL);
}
void test_circular1(int no){
    link circular1 = clist_new (no);
    
    clist_print(circular1);
    assert(circular1->item == 1);
    assert(circular1->next == circular1);
    list_drop(circular1);
}

void test_circular2(int no){
    link circular2 = clist_new(no);
    
    clist_print(circular2);
    assert(circular2->item == 1);
    assert(circular2->next->item == 2);
    assert(circular2->next->next == circular2);
    list_drop(circular2);
}

void test_circular3(int no){
    link circular3 = clist_new(no);
    
    clist_print(circular3);
    assert(circular3->item == 1);
    assert(circular3->next->item == 2);
    assert(circular3->next->next->item == 3);
    assert(circular3->next->next->next == circular3);
    list_drop(circular3);
}

void create_dlink_zero (void) {
    dlist_print(NULL);
    assert(dlist_new_from_list(NULL) == NULL);
}

void create_dlink_one (void) {
    Item item_one = 1;
    link list = node_new(item_one);
    
    dlink new_dlist = dlist_new_from_list(list);
    
    dlist_print(new_dlist);
    assert(new_dlist->item == 1);
    assert(new_dlist->next == NULL);
    assert(new_dlist->prev == NULL);
    
    dlist_drop(new_dlist);
}

void create_dlink_two (void) {
    link list = NULL;
    Item item_one = 1;
    link new_node = node_new(item_one);
    list = new_node;
    
    Item item_two = 2;
    new_node = node_new(item_two);
    list_insert_next(list, new_node);
    
    dlink new_dlist = dlist_new_from_list(list);
    
    dlist_print(new_dlist);
    assert(new_dlist->item == 1);
    assert(new_dlist->prev == NULL);
    assert(new_dlist->next->item == 2);
    assert(new_dlist->next->prev == new_dlist);
    assert(new_dlist->next->next == NULL);
    
    dlist_drop(new_dlist);
}
void create_dlink_three (void) {
    link list = NULL;
    Item item_one = 1;
    link new_node = node_new(item_one);
    list = new_node;
    
    Item item_two = 2;
    new_node = node_new(item_two);
    list_insert_next(list, new_node);
   
    Item item_three = 3;
    new_node = node_new(item_three);
    list_insert_next(list, new_node);
    
    dlink new_dlist = dlist_new_from_list(list);
    
    dlist_print(new_dlist);
    assert(new_dlist->item == 1);
    assert(new_dlist->prev == NULL);
    assert(new_dlist->next->item == 3);
    assert(new_dlist->next->prev == new_dlist);
    assert(new_dlist->next->next->item == 2);
    assert(new_dlist->next->next->next == NULL);
    assert(new_dlist->next->next->prev == new_dlist->next);
    
    dlist_drop(new_dlist);
}
