////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- A Queue ADT implementation, using linked lists.
//
// 2018-12-01	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// YYYY-mm-dd	Your Name Here <zNNNNNNN@student.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "item.h"
#include "queue.h"
#include "testable.h"

void wtest_single(void);
void wtest_double(void);
void wtest_10(void);

typedef struct queue queue;
typedef struct queue_node queue_node;

struct queue {
    size_t n_items;
	queue_node *head, *tail;
};

struct queue_node {
	Item item;
	queue_node *next;
};

static queue_node *queue_node_new (Item);

/** Create a new, empty Queue. */
queue *queue_new (void)
{
	queue *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate queue");
	(*new) = (queue) { .n_items = 0, .head = NULL, .tail = NULL };
	return new;
}

/** Destroy a Queue, releasing all resources associated with it. */
void queue_drop (queue *q)
{
	assert (q != NULL);
	for (queue_node *curr = q->head; curr != NULL; curr = curr->next)
		free (curr);
    free (q);
}

/** Add an item to the end of a Queue.
 * Sometimes referred to as "enqueue" or "unshift". */
void queue_en (queue *q, Item it)
{
	queue_node *node = queue_node_new (it);
	
	if (q->head != NULL) {
		q->tail->next = node;
		q->tail = node;
	
	} else {
		q->tail = node;
		q->head = node;	
	}
	
	q->n_items++;
}

/** Remove an item from the front of a Queue.
 * Sometimes referred to as "dequeue" or "shift". */
Item queue_de (queue *q)
{
    assert(q->n_items > 0);
    
	Item it = q->head->item;
    queue_node *del = q->head;
	
	if (q->n_items == 1) {
	    q->head = NULL;
	    q->tail = NULL;
	
	} else {
	    q->head = q->head->next;
	}
	
    free (del);		
	q->n_items--;
	
	return it;
}

/** Get the number of items in a Queue. */
size_t queue_size (queue *q)
{
	assert (q != NULL);
	return q->n_items;
}

static queue_node *queue_node_new (Item it)
{
	queue_node *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate queue_node");
	(*new) = (queue_node) { .item = it, .next = NULL };
	return new;
}

void white_box_tests (void)
{
	// ... you need to write these!
	wtest_single();
	wtest_double();
	wtest_10();
}


void wtest_single(void){
    puts("White testing single node queue");
    Queue q = queue_new();
    Item it = 0;
    
    queue_en(q, it);
    assert(q->head->item == it);
    assert(q->tail->item == it);
    assert(q->head->next == NULL);
    assert(q->n_items == 1);
   
    assert(queue_de(q) == 0);
    assert(q->head == NULL);
    assert(q->tail == NULL);
    assert(q->n_items == 0);
    
    queue_drop(q);
}
void wtest_double(void){
    puts("White testing double node queue");
    Queue q = queue_new();
    Item it = 0;
    
    queue_en(q, it);

    it = 1;
    queue_en(q, it);
    assert(q->head->item == 0);
    assert(q->head->next == q->tail);
    assert(q->tail->item == 1);
    assert(q->n_items == 2);
    
    assert(queue_de(q) == 0);
    assert(q->head->item == 1);
    assert(q->tail->item == 1);
    assert(q->head->next == q->tail->next);
    assert(q->tail->next == NULL);
    assert(q->n_items == 1);
    
    assert(queue_de(q) == 1);
    assert(q->head == NULL);
    assert(q->tail == NULL);
    assert(q->n_items == 0);
    
    queue_drop(q);
}

void wtest_10(void) {
    puts("White testing 10 node queue");
    Queue q = queue_new();
    
    int i = 0;
    Item it = 0;
    
    while(i < 10) {
        queue_en(q, it);
        it++;
        i++;
    }
    
    assert(q->head->item == 0);
    assert(q->tail->item == 9);
    assert(q->n_items == (size_t) 10);
    
    i = 0;   
    while(i < 10) {
        assert(queue_de(q) == i);
        i++;
    }
    assert(q->n_items == (size_t) 0);
    
    queue_drop(q);
}



