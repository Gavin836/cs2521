////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- Test a Stack ADT implementation.
//
// 2018-11-29	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// YYYY-mm-dd	Your Name Here <z5206647@student.unsw.edu.au>

#define DEFAULT_SIZE 10

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "stack.h"
#include "testable.h"

static void test_empty_stack (void);
static void test_one_item_stack (void);
static void test_thirty_pop(void);
static void test_thirty_shrink_pop(void);


int main (void)
{
	white_box_tests ();

	test_empty_stack ();
	test_one_item_stack ();
	test_thirty_pop();
	test_thirty_shrink_pop();

	// add more tests of your own!
    
	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}

static void test_empty_stack (void)
{
	puts ("Test 1: testing an empty stack.");
	Stack s = stack_new ();
	assert (stack_size (s) == 0);
	stack_drop (s);
}

static void test_one_item_stack (void)
{
	puts ("Test 2: testing a stack with one item.");
	Stack s = stack_new ();
	stack_push (s, 1);

	assert (stack_size (s) == 1);

	assert (stack_pop (s) == 1);
	assert (stack_size (s) == 0);

	stack_drop (s);
}

static void test_thirty_pop(void) {
    puts("Test 3: Testing pop after 30 elements");
    Stack s = stack_new();
    Item item;
    
    for (int i = 0; i <= DEFAULT_SIZE * 3; i++) {
        item = i;
        stack_push(s, item);
    }

    assert(stack_pop(s) == 30);
    stack_drop(s);
}

static void test_thirty_shrink_pop(void) {
    puts("Test 3: Testing pop after 30 elements, then popping down to 9");
    Stack s = stack_new();
    Item item = 0;
    
    int i = 0;
    for (i = 0; i <= DEFAULT_SIZE * 3; i++) {
        item = i;
        stack_push(s, item);
    }
    
    i--;
    while (i > 9) {
        item = stack_pop(s);
        i--;
    }

    assert(item == 10);
    stack_drop(s);
}
