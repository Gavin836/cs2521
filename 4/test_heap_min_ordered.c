#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "heap_min_ordered.h"

static void test_ordered_minheaps(void);
static void test_unordered_minheaps(void);

int main (void)
{
	// Stops output being buffered;
	// we get all printf output before crashes/aborts
	setbuf (stdout, NULL);

	test_ordered_minheaps();
	test_unordered_minheaps();

	puts ("\nAll tests passed. You are awesome!");
	return EXIT_SUCCESS;
}


static void test_ordered_minheaps (void)
{
	node *tree = NULL;
	puts ("ordered: test 1: empty tree");
	assert (heap_min_ordered_p (tree));

	tree = malloc (sizeof *tree);
	(*tree) = (node) { .item = 9, .left = NULL, .right = NULL };

	puts ("ordered: test 2: tree size 1");
	assert (heap_min_ordered_p (tree));

	node *leaf = malloc (sizeof *leaf);
	(*leaf) = (node) { .item = 15, .left = NULL, .right = NULL };
	tree->left = leaf;

	puts ("ordered: test 3: tree size 2");
	assert (heap_min_ordered_p (tree));

	// ... add more tests! ...
 
    node *leaf_1 = malloc (sizeof *leaf);
    assert(leaf_1 != NULL);
	(*leaf_1) = (node) { .item = 10, .left = NULL, .right = NULL };
	tree->right = leaf_1;

	puts ("ordered: test 4: tree size 3");
	assert (heap_min_ordered_p (tree));
    
    node *leaf_2 = malloc (sizeof *leaf);
	(*leaf_2) = (node) { .item = 20, .left = NULL, .right = NULL };
	tree->left->left = leaf_2;

	puts ("ordered: test 5: tree size 4");
	assert (heap_min_ordered_p (tree));
	
	free (leaf);
	free (leaf_1);
	free (leaf_2);
	free (tree);
}

static void test_unordered_minheaps (void)
{
	node *tree = malloc (sizeof *tree);
	(*tree) = (node) { .item = 9, .left = NULL, .right = NULL };

	node *leaf = malloc (sizeof *leaf);
	(*leaf) = (node) { .item = 8, .left = NULL, .right = NULL };
	tree->left = leaf;

	puts ("unordered: test 1: tree size 2");
	assert (! heap_min_ordered_p (tree));

	// ... add more tests! ...
    node *leaf_1 = malloc (sizeof *leaf);
	(*leaf_1) = (node) { .item = 10, .left = NULL, .right = NULL };
	tree->right = leaf_1;

	puts ("unordered: test 2: tree size 3");
	assert (! heap_min_ordered_p (tree));
	
	node *leaf_2 = malloc (sizeof *leaf);
	(*leaf_2) = (node) { .item = 50, .left = NULL, .right = NULL };
	tree->left->left = leaf_2;

	puts ("unordered: test 3: tree size 4");
	assert (! heap_min_ordered_p (tree));
	
	node *leaf_3 = malloc (sizeof *leaf);
	(*leaf_3) = (node) { .item = 55, .left = NULL, .right = NULL };
	tree->left->right = leaf_3;

	puts ("unordered: test 4: tree size 5");
	assert (! heap_min_ordered_p (tree));
	
	free (leaf);
	free (leaf_1);
	free (leaf_2);
	free (leaf_3);
	free (tree);
}
