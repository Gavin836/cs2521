#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "heap_min.h"

static void test_valid_minheaps (void);
static void test_invalid_minheaps (void);

int main (void)
{
	// Stops output being buffered;
	// we get all printf output before crashes/aborts
	setbuf (stdout, NULL);

	test_valid_minheaps ();
	test_invalid_minheaps ();

	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}


static void test_valid_minheaps (void)
{
	int heap1[] = { 0, 2, 10 };

	puts ("valid minheaps: test 1: 2,10");
	assert (heap_min_p (heap1, 2));
    
	// ... add more tests! ...
    int heap2[] = {0, 1, 2, 3, 4, 5, 6};
    puts("valid minheaps: test 2: 1,2,3,4,5,6");
	assert (heap_min_p (heap2, 6));
	
	int heap3[] = {0, 5, 6, 8, 7, 8, 9, 20};
    puts("valid minheaps: test 4: 5,6,8,7,8,9,20");
	assert (heap_min_p (heap3, 7));
    
    int heap4[] = {0, 1};
    puts("valid minheaps: test 3: 1");
	assert (heap_min_p (heap4, 1));
}

static void test_invalid_minheaps (void)
{
	int heap1[] = { 0, 10, 7, 6 };

	puts ("invalid minheaps: test 1: 10,7,6");
	assert (! heap_min_p (heap1, 3));

	// ... add more tests! ...
	int heap2[] = { 0, 5, 4, 3 };

	puts ("invalid minheaps: test 2: 5,4,3");
	assert (! heap_min_p (heap2, 3));
	
	int heap3[] = {0, 5, 6, 8, 7, 8, 9, 7};
	puts("invalid minheaps: test 4: 5,6,8,7,8,9,7");
	assert (!heap_min_p (heap3, 7));
	
	int heap4[] = {0, 5, 4, 6, 7, 8, 9, 7};
	puts("invalid minheaps: test 5: 5,4,6,7,8,9,7");
	assert (!heap_min_p (heap4, 7));
}
