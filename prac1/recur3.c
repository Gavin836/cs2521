#include <stdlib.h>
#include <stdio.h>

typedef struct node *Node;
struct node {
	int it;
	Node next;
}

typedef struct node node;

Node fac (int n);


int main (void) {
	Node fac5 = fac(5);
	
	return 0;
}

Node fac (int n) {
	Node new = malloc(sizeof(node));
	new->it = n;
	new->next = NULL;

	for (int i= 0; i <) {


	}

}
