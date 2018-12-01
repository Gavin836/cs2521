// COMP2521 19T0 ... lab 01: a linked list implementation
//
// 2018-11-24	Jashank Jeremy <jashank.jeremy@unsw.edu.au>
// YYYY-mm-dd	Your Name Here <zNNNNNNN@student.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

// Remove `__unused' tags from your functions before flight.
#define __unused __attribute__((unused))

#include "lists.h"

/** Traverses and prints the list. */
void list_print (link list)
{
	link curr = list;
	while (curr != NULL) {
		printf ("[%d]->", curr->item);
		curr = curr->next;
	}
	puts ("|");
}

/** Create a new node, initialised with the item provided.
 * Return a pointer to node (link) */
link node_new (Item it)
{
    link new = malloc(sizeof(node));
    new->item = it;
    new->next = NULL;
	
	return new;
}

/** Insert a new node into a given non-empty list.
 * The node is inserted directly after the head of the list. */
void list_insert_next (link list, link node)
{   

    assert(list != NULL);
    
    link temp;
    temp = list->next;
    list->next = node;
    node->next = temp;
   
}

/** Return the sum of all items in list */
int list_sum_items (link list)
{   
    if (list == NULL) {
        return 0;
    }
    
    int sum = list->item;
    
    //First node is null 
	link curr = list;
	
	while (curr->next != NULL ) {
	   curr = curr->next;
	   sum += curr->item;	   
	}
	
	return sum;
}

/** Frees all memory used in the list */
void list_drop (link list)
{
    // Segment circular lists
    link head = list;
   
    while (list->next != NULL) {
        
        if (list->next == head) {
            list->next = NULL;
            break;
        }
        
        list = list->next;
    }
    
    // Drop sequential lists
    list = head;
    link new_head = list->next;
    
    while (list != NULL) {
        free (list);
        
        list = new_head;
        
        if (new_head != NULL) {
            new_head = list->next;
        }    
    }    
}


/** Create a circular list with the specified number of nodes,
 * with each link storing data from 1 to the number of nodes. */
link clist_new (int n_nodes)
{
    if (n_nodes == 0) {
        return NULL;
    }
    
    if (n_nodes == 1) {
        link new = node_new(1);
        new->next = new;
        
        return new;
    }
    
    link new = node_new(1);
    link head = new;
    Item it = 2;
    
    for (int i = 1; i < n_nodes; i++) {
        
        //Find tail
        while (new->next != NULL) {            
            new = new->next;
        }
        
        new->next = node_new(it);
      
        it++;
    }
    
    new->next->next = head;
    
	return head;
}

/** print the data in a circular fashion starting from any node */
void clist_print (link clist)
{
    if (clist == NULL) {
        printf("Empty\n");
    
    } else {
    
        link head = clist;
        printf ("[%d]->", clist->item);
        
        clist = clist->next;    
        
        while(head != clist){
            printf ("[%d]->", clist->item);
            clist = clist->next;
        }
        puts(" Loop");
    }
}


/** Create a double-linked list which contains the same values,
 * in the same order as 'list' */
dlink dlist_new_from_list (link list)
{
    // Empty list
    if (list == NULL) {
        return NULL;
    }
    
    // Find no of links;
    link link_head = list;
    int no_links = 0;
    
    while (list != NULL) {
        no_links++;
        list = list->next;
    }
    
    //Create chain
    dlink new_dlink = NULL;
    dlink dlink_prev = NULL;
    dlink dlink_head = NULL;
   
    list = link_head;
    Item it = list->item;
    
    for (int i = 0; i < no_links; i++) {

        // First link vs. last link vs. intermediate links
        if (i == 0) {
            new_dlink = malloc(sizeof(dnode));
            new_dlink->next = NULL;
            new_dlink->prev = NULL;
            new_dlink->item = it;
            
            dlink_head = new_dlink;
            dlink_prev = new_dlink;
        
        } else if (i == (no_links - 1)) {
            new_dlink->next = malloc(sizeof(dnode));
            new_dlink = new_dlink->next;
            new_dlink->next = NULL;
            new_dlink->prev = dlink_prev;
            new_dlink->item = it;
            
            
        
        } else {
            new_dlink->next = malloc(sizeof(dnode));
            new_dlink = new_dlink->next;
            new_dlink->next = NULL;
            new_dlink->prev = dlink_prev;
            new_dlink->item = it;
            
            dlink_prev = new_dlink;
        }
       
        if (list->next != NULL) {        
            list = list->next;
            it = list->item;
        }
        
    }
    
    list = link_head;
    list_drop(list);
    
	return dlink_head;
}

/** Print a doubly-linked list. */
void dlist_print (dlink list)
{
    if (list == NULL) {
    
    } else if (list->next == NULL) {
        printf("|->");
	    printf ("[%d]->", list->item);
	    puts("|");
    
    } else {
    
        dlink curr = list;
        dlink temp = list->next;
	    while (temp != NULL) {
		    printf ("[%d]->", curr->item);
            
            curr = temp;
            temp = temp->next;
            
	    }
	    printf("[%d]->", curr->item);
	
        curr = curr->prev;
        printf("(Reverse)->");
        
        while (curr != NULL) {
            printf ("[%d]->", curr->item);
            curr = curr->prev;
        }
        
    	puts("|");

    }

}

/** Frees all the memory used in the double-linked list */
void dlist_drop (dlink list)
{
    assert(list != NULL);
    
    if (list->next == NULL) {
        free(list);
    
    } else {
        list = list->next;
        
        while (list->next != NULL) {
            free(list->prev);
            list = list->next;
        }
        
        free(list->prev);
        free(list);
    }
}
