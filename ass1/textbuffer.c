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
    size_t no_sentences; 
}textbuffer;

//Prototypes
void add_sentence(Textbuffer tb, char *string);
Sentence find_pos(Textbuffer tb, size_t pos);

void whitebox_tests (void);
static void wtest_one (void);
static void wtest_two (void);
static void wtest_three (void);
static void wtest_two_lines (void);

Textbuffer textbuffer_new (const char *text){
    int i;
    
    //Catch empty strings or no new lines.
    if (strcmp(text, "") == 0) {
        //puts("Empty string. Please input text");
        return NULL;
    
    } else {
        i = 0;
        
        while (1) {
            
            if (text[i] == '\0') {
                //puts("No newline character. Please try again");
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

size_t textbuffer_lines (Textbuffer tb){

    if (tb == NULL) return 0;
    
    return tb->no_sentences;
}

size_t textbuffer_bytes (Textbuffer tb){
    if (tb == NULL) return 0;
    
    Sentence curr = tb->head->next;
    
    //Initialise to all new line characters
    size_t count = textbuffer_lines(tb);
    
    while(curr != NULL) {
        count = count + strlen(curr->prev->string);
        curr = curr->next;
    }
    
    count = count + strlen(tb->head->string);
    
    return count;
}

char *textbuffer_to_str (Textbuffer tb){

    if(tb == NULL) return NULL;
    
    char *str = calloc(1, textbuffer_bytes(tb) + 1);
    
    Sentence curr = tb->head;
    
    while (curr->next != NULL) {
        curr = curr->next;
        strcat(str, curr->prev->string);
        strcat(str, "\n");
    }
    
    strcat(str, curr->string);
    strcat(str, "\n");
    
    return str;
}

void textbuffer_swap (Textbuffer tb, size_t pos1, size_t pos2){
    if (textbuffer_lines(tb) < pos1 || textbuffer_lines(tb) < pos2){
        puts("Ensure positions are within the doucument");
        abort();
    }   
    
    size_t temp_size;
    if (pos2 < pos1) {
        temp_size = pos1;
        pos1 = pos2;
        pos2 = temp_size;
    }

    Sentence p1 = find_pos(tb, pos1);
    Sentence p1_n = p1->next;
    Sentence p1_p = NULL;
    
    Sentence p2 = find_pos(tb, pos2);
    Sentence p2_p = p2->prev;
    Sentence p2_n = NULL;
    
    Sentence temp_sent = p2;
    
    //Determine whether head and tail pointer need to be changed
    if (p1 == tb->head) {
        tb->head = p2;
    
    } else {
        p1_p = p1->prev;   
    }
    
    if (p2 == tb->tail) {
        tb->tail = p1;  
    
    } else {
        p2_n = p2->next;
    } 

    //Modify links
    assert(p1_n != NULL);
    p1_n->prev = p2;
    
    if (p1->prev != NULL)
        p1_p->next = p2;
    
    assert(p2_p != NULL);
    p2_p->next = p1;
    
    if (p2_n != NULL)
        p2_n->prev = p1;
    
    p2->next = p1_n;
    p2->prev = p1_p;
    
    p1->next = temp_sent->next;
    p2->prev = temp_sent->prev;
         
}

Sentence find_pos(Textbuffer tb, size_t pos) {
    assert(pos < tb->no_sentences);
    
    int i = 0;
    Sentence curr = tb->head;
    
    while (i < (int) pos) {
        curr = curr->next;
        i++;
    }
    
    return curr;
}


void white_box_tests (void) {
    wtest_one();
    wtest_two();
    wtest_three();
    wtest_two_lines();
}

static void wtest_one (void){
    printf("Whitebox one element");
    
    Textbuffer new = textbuffer_new("Single\n");
    
    assert(textbuffer_lines(new) == 1);  
    assert(textbuffer_bytes(new) == 7);    
    assert(new->head == new->tail);
    assert(strcmp(new->head->string, "Single") == 0);
    
    assert(new->head->next == NULL);
    assert(new->head->prev == NULL);
    
    char *string = textbuffer_to_str(new);
    assert(strcmp(string, "Single\n") == 0);
    free(string);
    
    textbuffer_drop(new);
    
    puts(" -passed!");
}

static void wtest_two (void){
    printf("Whitebox two element");
    
    Textbuffer new = textbuffer_new("Single\nDouble\n");
    
    assert(textbuffer_lines(new) == 2);  
    assert(textbuffer_bytes(new) == 14);
    assert(new->head == new->tail->prev);
    assert(new->tail == new->head->next);
    
    assert(new->head->prev == NULL);
    assert(strcmp(new->head->string, "Single") == 0);
   
    assert(new->tail->next == NULL);
    assert(strcmp(new->tail->string, "Double") == 0);

    char *string = textbuffer_to_str(new);
    assert(strcmp(string, "Single\nDouble\n") == 0);
    free(string);
    
    textbuffer_drop(new);
    
    puts(" -passed!");
}

static void wtest_three (void){
    printf("Whitebox three element");
    
    Textbuffer new = textbuffer_new("Single\nDouble\nTriple\n");
    
    assert(textbuffer_lines(new) == 3);  
    assert(textbuffer_bytes(new) == 21);
    assert(new->head == new->tail->prev->prev);
    assert(new->tail == new->head->next->next);
    
    assert(new->head->prev == NULL);
    assert(new->head->next == new->tail->prev);
    assert(strcmp(new->head->string, "Single") == 0);
    
    assert(strcmp(new->head->next->string, "Double") == 0);
    
    assert(new->tail->next == NULL);
    assert(strcmp(new->tail->string, "Triple") == 0);

    char *string = textbuffer_to_str(new);
    assert(strcmp(string, "Single\nDouble\nTriple\n") == 0);
    free(string);

    textbuffer_drop(new);
    
    puts(" -passed!");
}

static void wtest_two_lines (void){
    printf("Two sentence swap test");
    Textbuffer tb;
    
    tb = textbuffer_new("Line 0\nLine 1\n");
    
    textbuffer_swap(tb, 0, 1);
    assert(strcmp(tb->head->string, "Line 1") == 0);
    assert(strcmp(tb->tail->string, "Line 0") == 0);
    assert(tb->head->prev == NULL);
    assert(tb->head->next == tb->tail);
    assert(tb->tail->next == NULL);
    assert(tb->tail->prev == tb->head);
    
    textbuffer_swap(tb, 1, 0);
    assert(strcmp(tb->head->string, "Line 0") == 0);
    assert(strcmp(tb->tail->string, "Line 1") == 0);
    assert(tb->head->prev == NULL);
    assert(tb->head->next == tb->tail);
    assert(tb->tail->next == NULL);
    assert(tb->tail->prev == tb->head);
    
    textbuffer_drop(tb);
    puts(" -passed!");
}
