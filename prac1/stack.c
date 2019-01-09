#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
#define NONE -1

typedef struct stack *Stack;
typedef struct stack {
    int item;
    Stack prev;
} stack;

Stack stack_new(void);
int stack_pop (Stack s);
void stack_push (Stack s, int it);
int stack_peep(Stack s);
void stack_free(Stack s);

void single_push(void);
void triple_push(void);

int main(void) {
    //Tests
    single_push();
    return 0;
}

Stack stack_new (void) {
    Stack new = calloc(1, sizeof(stack));
    assert(new != NULL);
    
    (*new) = (stack) {
        .item = NONE,
        .prev = NULL
    };
    
    
    return new;
}

void stack_push(Stack s, int it){
    Stack new_node = stack_new();
    assert(new_node != NULL);
    
    new_node->prev = s;
    new_node->item = it;
    
    printf("%p\n", &s);
    
    s = new_node;
        printf("%p", &s);
}

int stack_pop(Stack s) {
    Stack prev = s->prev;
    int tmp = s->item;
    free(s);
    s = prev;
    
    return tmp;    
}

int stack_peep(Stack s){
    assert(s->item != NONE);
    return s->item;
}

void stack_free (Stack s) {
    Stack tmp;
    
    while (s != NULL) {
        tmp = s;
        s = s->prev;
        free(tmp);
    }
}

void single_push (void) {
    Stack s = stack_new();
    assert(s != NULL);
    
    stack_push(s, 1);
    
    assert(s->item == 1);
    
}



