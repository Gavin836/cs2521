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

void test_single(void);
void test_realloc(void);
void test_reducesize(void);	

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
	    s->capacity = 2 * s->capacity;	  
	    Item *Ptr = s->items;
	    s->items = realloc(s->items, s->capacity * sizeof(Item));
	    
	    //Ensure realloc succeeds
	    assert(s->items != NULL);
	    assert(s->items != Ptr);
	}
	
	s->items[s->n_items] = it;
	s->n_items++;
}

/** Remove an item from the top of a Stack. */
Item stack_pop (stack *s)
{
	assert (s != NULL);

    if (s->n_items == 0) {
	    perror("stack underflow");
	    abort();
	    
	}
	
	Item it;
	int i = 0;
	
	if ((s->capacity > DEFAULT_SIZE) && (s->n_items < s->capacity / 4)) {	
        s->capacity = s->capacity / 2;
        Item *new_item = calloc(1, sizeof(Item) * s->capacity);
        
        while (i < (int) s->capacity) {
            new_item[i] = s->items[i];
            i++;
        }
        
        free(s->items);
        
        s->items = new_item;

    }
    
    it = s->items[s->n_items - 1];
    s->items[s->n_items - 1] = 0;
    s->n_items--;

	
	return it;
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
    stack *s = stack_new();
    Item it = 0;
    
    stack_push(s, it);
    
    assert(s->capacity == 10);
    assert(s->n_items == 1);
    assert(*(s->items) == 0) ;   
    
    stack_drop(s);
}

void test_realloc(void) {
    puts("Realloc after pushing with 40 items test");
    stack *s = stack_new();
    Item item;
    
    for (int i = 0; i <= DEFAULT_SIZE * 4; i++) {
        item = i;
        stack_push(s, item);
    }

    assert(s->capacity == 80);
    assert(s->n_items == (DEFAULT_SIZE * 4 + 1));
    assert(s->items[40] == DEFAULT_SIZE * 4);   
    
    stack_drop(s);
}

void test_reducesize (void) {
    printf("Reducing size of stack from 20 -> 10\n");
    stack *s = stack_new();
    Item item = 0;
    int i;
    
    for (i = 0; i <= DEFAULT_SIZE; i++) {
        item = i;
        stack_push(s, item);
    }
    
    assert(s->capacity == 20);
    assert(s->n_items == 11);
    assert(s->items[10] == 10);
    
    //0-1-2-3-4-5-6-7-8-9-10
    item = stack_pop(s);
    assert(item == 10);
    assert(s->items[10] == 0);
    assert(s->items[9] == 9);
    assert(s->n_items == 10);
    
    item = stack_pop(s);    //9
    item = stack_pop(s);    //8    
    item = stack_pop(s);    //7
    item = stack_pop(s);    //6
    item = stack_pop(s);    //5
    item = stack_pop(s);    //4
    item = stack_pop(s);    //3
    
    assert(item == 3);
    assert(s->n_items == 3);
    assert(s->capacity == 10);
    assert(s->items[3] == 0);
    assert(s->items[2] == 2);
    
    stack_drop(s);
}
