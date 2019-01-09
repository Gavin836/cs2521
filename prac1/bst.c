#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct tree *Tree;
typedef struct tree {
	int item;
	Tree left, right;
} tree;

Tree tree_new (int item);
Tree tree_search (Tree root, int item);
void tree_drop (Tree tree);
void tree_add (Tree root, int item);

int main (void) {
	Tree new = tree_new(1);

	assert(new->item == 1);
	assert(new->left == NULL);
	assert(new->right == NULL);
	
	tree_add(new, -1);
	assert(new->left->item == -1);

	tree_drop(new);
}

Tree tree_new (int item) {
	Tree new = malloc(sizeof(tree));
	(*new) = (tree) {
		.item = item,
		.left = NULL,
		.right = NULL
	};

	return new;
}


void tree_add (Tree root, int item){
	Tree curr = root;
	
	while (curr != NULL) {
		if (item > curr->item) {
			curr = curr->right;
		} else {
			curr = curr->left;
		}

	}
	Tree new_node = tree_new(item);
	curr = new_node;
	        
}

Tree tree_search (Tree root, int item) {
	if (root == NULL) return NULL;
	if (root->item > item) return tree_search(root->left, item);
	if (root->item < item) return tree_search(root->right, item);	

	return root;
}


void tree_drop (Tree tree) { 
	if (tree->left != NULL) tree_drop(tree->left);
	if (tree->right != NULL) tree_drop(tree->right);
	
	free(tree);
}
