////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 ... assignment 1: Textbuffer ADT
//
// 2018-12-02	Gavin Wang  <z5206647@unsw.edu.au>

#include <stdio.h>
#include <assert.h>
#include "textbuffer.h"

//Structs implmentation
typedef struct sentence *Sentence;
typedef struct sentence {
      Sentence next;
      Sentence prev;
      char *string;
}sentence;

typedef struct textbuffer {
    Sentence head;
    Sentence tail;
    int no_sentences; 
}textbuffer;

//Prototypes
void add_sentence(Textbuffer tb, char *string);

static void whitebox_tests (void);
static void wtest_one (void);
static void wtest_two (void);
static void wtest_three (void);

Textbuffer textbuffer_new (const char *text){
    int i;
    
    //Catch empty strings or no new lines.
    if (strcmp(text, "") == 0) {
        puts("Empty string. Please input text");
        return NULL;
    
    } else {
        i = 0;
        
        while (1) {
            
            if (text[i] == '\0') {
                puts("No newline character. Please try again");
                return NULL;
                
            } else if (text[i] == '\n') {
                break;
            }
            
            i++;           
        }    
    }
    
    //Initialise textbuffer and it's attributes
    Textbuffer tb_new = calloc(1, sizeof(textbuffer));
    char *string = strdup(text);
    char *copy = string;
    char *string_sep = strsep(&string, "\n");
    
    //String_buf used to prevent the trailing "" from being included
    char *string_buf = strsep(&string, "\n");
    char *string_buf2;
        
    while ((string_buf2 = strsep(&string, "\n")) != NULL) {
        add_sentence(tb_new, string_sep);
        string_sep = string_buf;
        string_buf = string_buf2;
    }
    
    add_sentence(tb_new, string_sep);
      
    free(copy);
    
    return tb_new;
}

void add_sentence(Textbuffer tb, char *string) {
    
    // Produce "sentence" struct
    char *temp = strdup(string);
    assert(temp != NULL);
    Sentence new_sentence = calloc(1, sizeof(sentence));
    assert(new_sentence != NULL);
    new_sentence->string = temp;
    
    //If empty intialise "textbuffer", otherwise, add new sentence
    if (tb->head == NULL) { 
        tb->head = new_sentence;
        tb->tail = new_sentence;      
        tb->no_sentences = 1;        
    
    } else {
        tb->tail->next = new_sentence;
        new_sentence->prev = tb->tail;
        tb->tail = new_sentence;
        tb->no_sentences++;
    }    
    
}

void textbuffer_drop (Textbuffer tb){
    assert(tb->no_sentences > 0);
    
    Sentence curr = tb->head;
    
    //Free all "sentences" from "textbuffer"
    while (curr != tb->tail) {
        curr = curr->next;
        free(curr->prev->string);        
        free(curr->prev);
    }
    
    free(tb->tail->string);
    free(tb->tail);
    
    free(tb);    
}



static void whitebox_tests (void) {
    wtest_one();
    wtest_two();
    wtest_three();
}

static void wtest_one (void){
    printf("Whitebox one element");
    
    Textbuffer new = textbuffer_new("Single\n");
    
    assert(strcmp(new->head->string, "Single") == 0);
    assert(new->no_sentences == 1);  
    assert(new->head == new->tail);
    
    assert(new->head->next == NULL);
    assert(new->head->prev == NULL);
     
    puts(" -passed!");
}

static void wtest_two (void){
    printf("Whitebox two element");
    
    Textbuffer new = textbuffer_new("Single\nDouble\n");
    
    assert(new->no_sentences == 2);  
    assert(new->head == new->tail->prev);
    assert(new->tail == new->head->next);
    
    assert(new->head->prev == NULL);
    assert(strcmp(new->head->string, "Single") == 0);
    
    assert(new->tail->next == NULL);
    assert(strcmp(new->tail->string, "Double") == 0);
    
    puts(" -passed!");
}

static void wtest_three (void){
    printf("Whitebox three element");
    
    Textbuffer new = textbuffer_new("Single\nDouble\nTriple\n");
    
    assert(new->no_sentences == 3);  
    assert(new->head == new->tail->prev->prev);
    assert(new->tail == new->head->next->next);
    
    assert(new->head->prev == NULL);
    assert(new->head->next == new->tail->prev->prev);
    assert(strcmp(new->head->string, "Single") == 0);
    
    assert(strcmp(new->head->next->string, "Double") == 0);
    
    assert(new->tail->next == NULL);
    assert(strcmp(new->tail->string, "Triple") == 0);
    
    puts(" -passed!");
}
