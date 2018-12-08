////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 -- Test a Queue ADT implementation.
//
// 2018-12-01	Jashank Jeremy <jashankj@cse.unsw.edu.au>
// YYYY-mm-dd	Your Name Here <zNNNNNNN@student.unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "queue.h"
#include "testable.h"

static void test_single (void);
static void test_double (void);
static void test_ten (void);

int main (void)
{
	white_box_tests ();
    
	// add more tests of your own!
    test_single();
    test_double();
    test_ten();
                
	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}

static void test_single (void) {
    puts("Testing single node queue");
    Queue q = queue_new();
    Item it = 0;
    
    queue_en(q, it);
    assert(queue_size(q) == (size_t) 1);
    
    assert(queue_de(q) == 0);
    assert(queue_size(q) == 0);
    
    queue_en(q, it);
    assert(queue_size(q) == (size_t) 1);
    
    assert(queue_de(q) == 0);
    assert(queue_size(q) == 0);
    
    queue_drop(q);
}

static void test_double (void) {
    puts("Testing double node queue");
    Queue q = queue_new();
    Item it = 0;
    
    queue_en(q, it);
    it = 1;
    queue_en(q, it);
    assert(queue_size(q) == (size_t) 2);
    
    assert(queue_de(q) == 0);
    assert(queue_de(q) == 1);
    assert(queue_size(q) == 0);
    
    queue_drop(q);
}


static void test_ten (void) {
    puts("Testing 10 nodes queue");
    Queue q = queue_new();
    
    int i = 0;
    Item it = 0;
    
    while(i < 10) {
        queue_en(q, it);
        it++;
        i++;
    }
    
    assert(queue_size(q) == (size_t) 10);
   
    i = 0;   
    while(i < 10) {
        assert(queue_de(q) == i);
        i++;
    }
    assert(queue_size(q) == (size_t) 0);
    
    queue_drop(q);
}
