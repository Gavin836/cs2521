#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node *Node;
typedef struct node {
	int item;
	Node next;
	Node prev;
} node;

typedef struct list *List;
typedef struct list {
	Node head, tail;
	int n_items;
} list;

void list_add(List list, int item);
void list_delete(List list, int item);
void list_drop(List list);
List list_new(void);

int main (void){
	//tests

}

List list_new(void) {
	List new = malloc(sizeof(list));
	new->head = NULL;
	new->tail = NULL;
	new->n_items = 0;

	return new;
}

void list_add(List l, int item){
	Node new_node = malloc(sizeof(node));
	new_node->prev = l->head;
	new_node->next = NULL;

	if(l->head != NULL) l->head->next = new_node;
	if (l->head == NULL) l->head = new_node;
	if (l->tail == NULL) l->tail = new_node;
	
	l->n_items++;
	
}

void list_delete (List l, int item){
	int i = 0;
	Node curr = l->head;
	
	if (l->n_items == 1) {
		free(l->head);
		l->head = NULL;
		l->tail = NULL;
	
	} else {
        while (curr != NULL && (i < l->n_items)) {         
	        if (curr->item = item) break;		
	        curr = curr->next;
        {	

        if (curr == l->head) {
	        l->head == curr->prev;
	        if (l->head == NULL) l->tail = NULL;

	        free(curr);		
        
        } else if (curr == l->tail) {
	        l->tail == curr->next;
	        if (l->tail == NULL) l->head = NULL;

	        free(curr);	
        
        } else {
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
            free(curr);
        }
	}
	l->n_items--;

}

void list_drop (List l) {
    Node curr = l->head;
    Node curr_buf = l->head->next;
    
    while (curr_buf != NULL) {
        free(curr);
        curr = curr_buf;
        curr_buf = curr_buf->next;
    }
    
    free(curr);
    free(l);
}



































