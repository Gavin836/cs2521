////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- A Queue ADT implementation, using arrays.
//
// 2018-12-01	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// YYYY-mm-dd   Your Name Here <zNNNNNNN@student.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "item.h"
#include "queue.h"
#include "testable.h"

#define DEFAULT_SIZE 10

void wtest_twoI(void);

typedef struct queue queue;

struct queue {
	size_t n_items;
	size_t capacity;
	Item *items;
    int head;
    int tail;
};

/** Create a new, empty Stack.  $ O(1) $. */
queue *queue_new (void)
{
	queue *new = malloc (sizeof *new);
	if (new == NULL)
		err (EX_OSERR, "couldn't allocate queue");
	(*new) = (queue) { .n_items = 0, .capacity = DEFAULT_SIZE };

	new->items = calloc (DEFAULT_SIZE, sizeof(Item));
	if (new->items == NULL)
		err (EX_OSERR, "couldn't allocate queue items");
    /*
    new->head = calloc(1, sizeof(int));
    new->tail = calloc(1, sizeof(int));
   
    if ((new->head == NULL)|| (new->tail == NULL))
		err (EX_OSERR, "couldn't allocate index");
    */
    
	return new;
}

/** Destroy a Queue.  $ O(1) $. */
void queue_drop (queue *q)
{
	assert (q != NULL);
	free (q->items);
	//free (q->head);
	//free (q->tail);
	free (q);
}

#if 0
/** Add an item to the end of a Queue.  $ O(1) $.
 * Sometimes referred to as "enqueue" or "unshift". */
void queue_en (queue *q, Item it)
{    
	assert (q != NULL);
	assert (q->n_items < q->capacity);
	
    if (q->n_items == 0) {
        *(q->head) = q->items;
        *(q->tail) = *(q->head);
    	**(q->tail) = it;
    
    } else {
	    *(q->tail) = *q->tail + sizeof(Item);
        **(q->tail) = it;
    }
	
	q->n_items++;
}

/** Remove an item from the front of a Queue.  $ O(n) $.
 * Sometimes referred to as "dequeue" or "shift". */
Item queue_de (queue *q)
{
	assert (q != NULL);
	if (q->n_items == 0) {
		fprintf (stderr, "queue underflow!\n");
		abort();
	}

	// shift the elements across
	Item it = **(q->head);
	**(q->head) = 0;
	*(q->head) = *(q->head) + sizeof(Item);
	
	q->n_items--;
	
	return it;
}
#endif


/** Add an item to the end of a Queue.  $ O(1) $.
 * Sometimes referred to as "enqueue" or "unshift". */
void queue_en (queue *q, Item it)
{    
	assert (q != NULL);
	assert (q->n_items < q->capacity);
	
    if (q->n_items == 0) {
        q->head = 0;
        q->tail = 0;
    
    } else {
        if (q->tail == 9) {
            q->tail = 0;
        } else {
	        q->tail++;
        }
    }
	q->items[q->tail] = it;
	
	q->n_items++;
}

/** Remove an item from the front of a Queue.  $ O(n) $.
 * Sometimes referred to as "dequeue" or "shift". */
Item queue_de (queue *q)
{
	assert (q != NULL);
	if (q->n_items == 0) {
		fprintf (stderr, "queue underflow!\n");
		abort();
	}

	// shift the elements across
	Item it = q->items[q->head];
	q->items[q->head] = 0;
	
	if (q->head == 9) {
	    q->head = 0;
	} else {
	    q->head++;
	}
	
	q->n_items--;
	
	return it;
}

/** Get the number of items in a Queue.  $ O(1) $. */
size_t queue_size (queue *q)
{
	assert (q != NULL);
	return q->n_items;
}

void white_box_tests (void)
{
	// ... you need to write these!
	wtest_twoI();
}

void wtest_twoI(void) {
    puts("White testing double node queue");
    Queue q = queue_new();
    Item it = 0;
    
    queue_en(q, it);
    assert(q->items[q->head] == 0);
    assert(q->head == q->tail);
    assert(q->n_items == 1);
    
    it = 1;
    queue_en(q, it);
    assert(q->items[q->head] == 0);
    assert(q->items[q->tail] == 1);
    assert(q->n_items == 2);
    
    assert(queue_de(q) == 0);
    assert(q->items[q->head] == 1);
    assert(q->head == q->tail);
    assert(q->n_items == 1);
    
    assert(queue_de(q) == 1);
    assert(q->n_items == 0);
    
    queue_drop(q);
}
