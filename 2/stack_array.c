////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- A Stack ADT implementation, using arrays.
//
// 2018-11-29	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// YYYY-mm-dd   Your Name Here <z5206647@student.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "item.h"
#include "stack.h"
#include "testable.h"

#define DEFAULT_SIZE 10

typedef struct stack stack;

struct stack {
	size_t n_items;
	size_t capacity;
	Item *items;
};

/** Create a new, empty Stack. */
stack *stack_new (void)
{
	stack *new = malloc (sizeof *new);
	if (new == NULL)
		err (EX_OSERR, "couldn't allocate stack");

	(*new) = (stack) { .n_items = 0, .capacity = DEFAULT_SIZE };

	new->items = calloc (DEFAULT_SIZE, sizeof(Item));
	if (new->items == NULL)
		err (EX_OSERR, "couldn't allocate stack items");

	return new;
}

/** Destroy a Stack. */
void stack_drop (stack *s)
{
	assert (s != NULL);
	free (s->items);
	free (s);
}

/** Add an item to the top of a Stack. */
void stack_push (stack *s, Item it)
{
	assert (s != NULL);
	
	if (s->n_items == s->capacity) {
	    s->items = realloc(s->items, 2 * s->capacity * sizeof(Item));
	    s->capacity = 2*s->capacity;	    
	}
	
	s->items[s->n_items] = it;
	s->n_items++;
}

/** Remove an item from the top of a Stack. */
Item stack_pop (stack *s)
{
	assert (s != NULL);
	Item it;
	
	if ((s->capacity > DEFAULT_SIZE) && (s->programn_items < s->capacity / 4)) {	
        s->n_items = s->capacity / 2;
        s->items = realloc(s->items, s->capacity);
    }
    
	if (s->n_items == 0) {
	    perror("stack underflow");
	    abort();
	    
	} else {
	    it = s->items[s->n_items - 1];
	    s->n_items--;
	}
	
	return it;DEFAULT_SIZE
}

/** Get the number of items in a Stack. */
size_t stack_size (stack *s)
{
	assert (s != NULL);
	return s->n_items;
}

void white_box_tests (void)
{
	// ... you need to write these!
    test_single();
    test_realloc();
    test_reducesize();	
    
    puts("All tests passed!");
}

void test_single(void) {
    puts("Single item test");
    stack *new = stack_new;
    Item it = 0;
    
    stack_push(new, it);
    
    assert(s->capacity == 10);
    assert(s->n_items == 1);
    assert(*(s->item) == 0)    
}

void test_realloc(void) {
    puts("Realloc at 10 items test");
    stack *new = stack_new;
    Item item;
    
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        item = i;
        stack_push(new, item);
    }
    
    assert(s->capacity == 20);
    assert(s->n_items == DEFAULT_SIZE);
    assert(*(s->item) == DEFAULT_SIZE);   
}

void test_reducesize (void) {
    stack *new = stack_new;
    Item item;
    
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        item = i;
        stack_push(new, item);
    }
    
    item = 0;
    while (i > 5) {
        stack_pop(new);
        i--;
    }
}
