////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 ... assignment 1: Textbuffer ADT
//
// 2018-12-14	Gavin Wang  <z5206647@unsw.edu.au>

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
void remove_from_tb (Textbuffer tb, Sentence curr);
Sentence find_pos(Textbuffer tb, size_t pos);

void whitebox_tests (void);
static void wtest_one (void);
static void wtest_two (void);
static void wtest_three (void);
static void wtest_two_lines (void);
static void wtest_insert (void);
static void wtest_cut (void);

Textbuffer textbuffer_new (const char *text){
    
    //Catch empty strings or no new lines.
    if (strcmp(text, "") == 0) {
        puts("Empty string. Please input text");
        return NULL;
    
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

void add_sentence (Textbuffer tb, char *string) {
    
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
    
    Sentence curr = tb->head;
    
    if (curr != NULL) { 
        //Free all "sentences" from "textbuffer"
        while (curr != tb->tail) {
            curr = curr->next;
            free(curr->prev->string);        
            free(curr->prev);
        }
        
        free(tb->tail->string);
        free(tb->tail);
    }
    
    free(tb);    
}


size_t textbuffer_lines (Textbuffer tb){

    if (tb == NULL) return 0;
    
    return tb->no_sentences;
}

size_t textbuffer_bytes (Textbuffer tb){
    if ((tb == NULL) || (tb->head == NULL)) return 0;
    
    Sentence curr = tb->head;
    Sentence curr_buf = NULL;
    
    if (tb->no_sentences > 1) 
        curr_buf = tb->head->next;
    
    //Initialise to all new line characters and NUL terminator
    size_t count = textbuffer_lines(tb);
    
    while(curr_buf != NULL) {
        count = count + strlen(curr->string);
        curr = curr->next;
        curr_buf = curr_buf->next;
    }
    
    if (tb->no_sentences > 1) {
        count = count + strlen(curr->string);
    
    } else {
        count = count + strlen(tb->head->string);
    }
    
    return count;
}

char *textbuffer_to_str (Textbuffer tb){

    if ((tb == NULL) || (tb->head == NULL)) return NULL;
    
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
    
    // Find the address of the sentences, then remove them from buffer
    Sentence p1 = find_pos(tb, pos1);
    Sentence p2 = find_pos(tb, pos2);
    
    sentence temp1 = *p1;
    sentence temp2 = *p2;
    
    remove_from_tb(tb, p1);
    remove_from_tb(tb, p2);
    
    // Copy of the object
    
    // Case where the nodes are sequential
    if (p1->next == p2) {
        // When only two nodes exist swap them.
        if ((tb->head == NULL) && (tb->tail == NULL)) {
            p1->next = NULL;
            p1->prev = p2;
            p2->next = p1;
            p2->prev = NULL;
        
        // Adding sequential nodes to the buffer
        } else {
            p2->next = p1;
            p2->prev = temp1.prev;
            
            p1->next = temp2.next;
            p1->prev = p2;
            
            if (p2->prev != NULL) 
                p2->prev->next = p2;
            
            if (p1->next != NULL) 
                p1->next->prev = p1;
        }
    
    // Case to swap when sentences are not sequential   
    } else {
        p1->next = p2->next;
        p1->prev = p2->prev;
        
        if (p1->next != NULL) 
            p1->next->prev = p1;
        
        if (p1->prev != NULL)
            p1->prev->next = p1;
        
        p2->next = temp1.next;
        p2->prev = temp1.prev;
        
        if (p2->next != NULL) 
            p2->next->prev = p2;
            
        if (p2->prev != NULL)
            p2->prev->next = p2;        
    }
    
    tb->no_sentences += 2;
    
    //Update head and tail if needed
    if (temp1.prev == NULL) 
        tb->head = p2;
        
    if (temp2.next == NULL)
        tb->tail = p1;  
}

// Given a pos and texbuffer the function will return a point to the sentence
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

// Function removes curr from the tb by removing all links to curr. Doesn't free
void remove_from_tb (Textbuffer tb, Sentence curr) {
    assert(tb->no_sentences > 0);
    
    // Modify links pointing to curr
    if ((curr->next == NULL) && (curr->prev == NULL)){
        tb->head = NULL;
        tb->tail = NULL;
    
    } else if (curr->next == NULL) {       
        curr->prev->next = NULL;
        tb->tail = curr->prev;
    
    } else if (curr->prev == NULL) {
        curr->next->prev = NULL;
        tb->head = curr->next;
    
    } else {
        curr->next->prev = curr->prev;
        curr->prev->next = curr->next;
    }

    tb->no_sentences--;
}

void textbuffer_insert (Textbuffer tb1, size_t pos, Textbuffer tb2){
    
    if (pos > (tb1->no_sentences - 1)) {
        perror("Position is out of bounds");
        abort();
    
    // Ensure we are inserting two DIFFERENT buffers
    } else if (tb1 != tb2) {
    
        Sentence curr = find_pos(tb1, pos);
        
        //Insert at the start
        if (curr == tb1->head) {
            tb2->tail->next = tb1->head;
            tb1->head->prev = tb2->tail;
            tb1->head = tb2->head;
        
        // Insert at the end;
        } else if (pos == tb1->no_sentences) {
            tb1->tail->next = tb2->head;
            tb2->head->prev = tb1->tail;
            tb1->tail = tb2->tail; 
            
        // Insert elsewhere
        } else {
            tb2->tail->next = curr;
            curr->prev->next = tb2->head;
            tb2->head->prev = curr->prev;
            curr->prev = tb2->tail;
        }
        
        tb1->no_sentences += tb2->no_sentences;
        
        //Drop tb2 wrapper
        free(tb2);
    }
  
}
void textbuffer_paste (Textbuffer tb1, size_t pos, Textbuffer tb2){
    //Duplicate tb2
    char *str = textbuffer_to_str(tb2);
    
    Textbuffer tb2_copy = textbuffer_new(str);
    free(str);
    
    textbuffer_insert(tb1, pos, tb2_copy);   
}

Textbuffer textbuffer_cut (Textbuffer tb, size_t from, size_t to){
    
    if ((to > tb->no_sentences) || (from > to)) {
        puts("Positions are out of range");
        abort();
    }   
    
    // Allocate enough memory to store the tb as a string    
    char *str = calloc(1, textbuffer_bytes(tb) + 1);
    Sentence curr = find_pos(tb, from);
    Sentence curr_to = find_pos(tb, to);

    // Increment through sentences and storing in "str" and then removing from buf.
    if (from == to) {
        strcat(str, curr->string);
        strcat(str, "\n");
        remove_from_tb(tb, curr);
        free(curr);
    
    } else {
        // Increment preemptively to enable freeing memory
        curr = curr->next;
       
        while (curr != curr_to){
            strcat(str, curr->prev->string);
            strcat(str, "\n");  
            remove_from_tb(tb, curr->prev);
            free(curr->prev);
            curr = curr->next;
        }
        
        // Second last element i.e curr_to->prev
        strcat(str, curr->prev->string);
        strcat(str, "\n");  
        remove_from_tb(tb, curr->prev);
        free(curr->prev);
        
        // Final element i.e curr_to
        strcat(str, curr->string);
        strcat(str, "\n");  
        remove_from_tb(tb, curr);
        free(curr);       
    }

    return textbuffer_new(str);
}

Textbuffer textbuffer_copy (Textbuffer tb, size_t from, size_t to){
    // Duplicate tb 
    char *str = textbuffer_to_str(tb);
    Textbuffer new = textbuffer_new(str);
    
    // Produce new buffer
    Textbuffer new2 = textbuffer_cut(new, from, to);
    
    free(str);
    free(new);
    
    return new2;
}

void textbuffer_delete (Textbuffer tb, size_t from, size_t to){   
    
    Sentence curr = find_pos(tb, from);
    Sentence curr_to = find_pos(tb, to);
    
    if (from == to) {
        remove_from_tb(tb, curr);
        free(curr);
    
    } else if (from < to) {
        // Increment preemptively to enable freeing memory
        curr = curr->next;
       
        while (curr != curr_to){
            remove_from_tb(tb, curr->prev);
            free(curr->prev);
            curr = curr->next;
        }
        
        // Second last element i.e curr_to->prev
        remove_from_tb(tb, curr->prev);
        free(curr->prev);
        
        // Final element i.e curr_to
        remove_from_tb(tb, curr);
        free(curr);       
    
    }

}

ssize_t textbuffer_search (Textbuffer tb, char *match, bool rev){
    
    Sentence curr = NULL;
    ssize_t sent;
    
    if (rev == false) {
        curr = tb->head;
        sent = 0;
        
        // Increment through sentences to find match
        while (sent < (ssize_t) tb->no_sentences) {
            
            if (strstr(curr->string, match) != NULL) 
                return sent;
                
            curr = curr->next;
            sent++;
        }
        
    } else {
        curr = tb->tail;
        sent = (ssize_t)tb->no_sentences;
       
        // Reverse through sentences to find match 
        while (sent > 0) {
            
            if (strstr(curr->string, match) != NULL) 
                return sent - 1;
                
            curr = curr->prev;
            sent--;
        }        
    }
    
    return -1;
}


void textbuffer_replace (Textbuffer tb, char *match, char *replace){
    Sentence curr = NULL;
    ssize_t index;
    char *new_str = NULL;
    char *insert_pos = NULL;
    char *match_ptr = NULL;
    char *curr_str = NULL;
    char *curr_str_copy = NULL;
   
    int *index_check = calloc(1, 4 * tb->no_sentences);
    
    // Find the index of the matching sentences
    if (strcmp(match, "") != 0)
    while ((index = textbuffer_search(tb, match, false)) != -1) {   
        
        // Ensure that sentences that have already been FULLY replaced are 
        // not replaced again
        
        if (index_check[index] == 1) break;
        
        curr = find_pos(tb, (size_t) index);
        curr_str = strdup(curr->string);
        curr_str_copy = curr_str;
        
        //Allocate more than enough space
        new_str = calloc(1, strlen(curr_str) + strlen(replace) + 1);
        insert_pos = new_str;
        
        // Increment through all matches in the string. Code referenced from 
        // "The Paramagnetic Croissant". 
        // (https://stackoverflow.com/questions/32413667/replace-all-occurrences-of-a-substring-in-a-string-in-c)
        
        while (1) {
            match_ptr = strstr(curr_str, match);
            
            // Add trailing text
            if (match_ptr == NULL) {
                strcpy(insert_pos, curr_str);
                break;
            }
            
            // Portion before match
            memcpy(insert_pos, curr_str, (size_t) (match_ptr - curr_str));
            insert_pos += (match_ptr - curr_str);
            
            // Replacement portion
            memcpy(insert_pos, replace, strlen(replace));
            insert_pos += strlen(replace);
            
            curr_str = match_ptr + strlen(match);
        }
        
        // Free temp string and resize "new_str". Reassign the modified string
        new_str = realloc(new_str, strlen(new_str) + 1);
        free(curr_str_copy);
        free(curr->string);
       
        curr->string = new_str;   
        index_check[index] = 1;     
    }
    
    free(index_check);
}

void white_box_tests (void) {
   
    wtest_one();
    wtest_two();
    wtest_three();
   
    wtest_two_lines();
    
    wtest_insert();
    wtest_cut();
}

static void wtest_one (void){
    printf("Whitebox one element");
    
    Textbuffer new = textbuffer_new("Single\n");
    
    assert(textbuffer_lines(new) == 1);  
    assert(textbuffer_bytes(new) == 7);    
    assert(textbuffer_search(new, "Single", false) == 0);
    assert(new->head == new->tail);
    assert(strcmp(new->head->string, "Single") == 0);
    
    assert(new->head->next == NULL);
    assert(new->head->prev == NULL);
    
    assert(strcmp(new->head->string, "Single") == 0);
    
    textbuffer_replace(new, "Sin", "Prin");
    assert(strcmp(new->head->string, "Pringle") == 0);
    
    textbuffer_replace(new, "old", "new");
    assert(strcmp(new->head->string, "Pringle") == 0);
    
    textbuffer_drop(new);
    
    puts(" -passed!");
}

static void wtest_two (void){
    printf("Whitebox two element");
    
    Textbuffer new = textbuffer_new("Single\nDouble\n");
    
    assert(textbuffer_lines(new) == 2);  
    assert(textbuffer_bytes(new) == 14);
    assert(textbuffer_search(new, "Double", true) == 1);
    assert(textbuffer_search(new, "Double", false) == 1);
    assert(new->head == new->tail->prev);
    assert(new->tail == new->head->next);
    
    assert(new->head->prev == NULL);
    assert(strcmp(new->head->string, "Single") == 0);
   
    assert(new->tail->next == NULL);
    assert(strcmp(new->tail->string, "Double") == 0);
    
    assert(strcmp(new->head->string, "Single") == 0);
    assert(strcmp(new->tail->string, "Double") == 0);
    
    textbuffer_replace(new, "Dou", "");
    assert(strcmp(new->tail->string, "ble") == 0);
    assert(textbuffer_bytes(new) == 11);
    assert(new->no_sentences == 2);
    
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

    assert(strcmp(new->head->string, "Single") == 0);
    assert(strcmp(new->head->next->string, "Double") == 0);
    assert(strcmp(new->tail->string, "Triple") == 0);
    
    textbuffer_delete(new, 1, 1);
    assert(strcmp(new->head->string, "Single") == 0);
    assert(strcmp(new->tail->string, "Triple") == 0);
    assert(new->no_sentences == 2);
    assert(textbuffer_bytes(new) == 14);
    
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

static void wtest_insert (void){
    printf("Two and three element insert/paste test");
    Textbuffer new = textbuffer_new("1\n");
    Textbuffer new2 = textbuffer_new("2\n");
    
    textbuffer_insert(new, 0, new2);
    assert(new->no_sentences == 2);
    
    assert(strcmp(new->tail->string, "1") == 0);
    assert(strcmp(new->head->string, "2") == 0);
    assert(strcmp(new->head->next->string, "1") == 0);
    assert(new->tail == new->head->next);
    assert(new->tail->prev == new->head);
    
    // 2 - 3 - 1 
    new2= textbuffer_new("3\n");
    textbuffer_paste(new, 1, new2);
    assert(new->no_sentences == 3);
    
    assert(strcmp(new->tail->string, "1") == 0);
    assert(strcmp(new->head->string, "2") == 0);
    assert(strcmp(new->head->next->string, "3") == 0);
    assert(new->tail == new->head->next->next);
    assert(new->head == new->tail->prev->prev);
    
    textbuffer_drop(new);
    textbuffer_drop(new2);
    puts(" -passed!");
}

static void wtest_cut (void){
    printf("Five element cut/copy test");
    Textbuffer new = textbuffer_new("1\n2\n3\n4\n5\n");
    Textbuffer new2 = textbuffer_cut(new, 4,4);
    
    assert(new2->no_sentences == 1);
    assert(new2->head->prev == NULL);
    assert(strcmp(new2->head->string, "5") == 0);
    assert(strcmp(new2->tail->string, "5") == 0);
    assert(new2->head == new2->tail);
    
    assert(new->no_sentences == 4);
    assert(strcmp(new->tail->string, "4") == 0);
    assert(new->tail->next == NULL);
    
    // Copy
    Textbuffer new3 = textbuffer_copy(new, 0, 3);
    
    assert(new->no_sentences == 4);
    assert(new->head == new->tail->prev->prev->prev);
    assert(strcmp(new->head->string, "1") == 0);
    assert(new->tail == new->head->next->next->next);
    assert(strcmp(new->tail->string, "4") == 0);
    
    assert(new3->no_sentences == 4);
    assert(new3->head == new3->tail->prev->prev->prev);
    assert(strcmp(new3->head->string, "1") == 0);
    assert(new3->tail == new3->head->next->next->next);
    assert(strcmp(new3->tail->string, "4") == 0);
    
    textbuffer_drop(new);
    textbuffer_drop(new2);
    textbuffer_drop(new3);
    
    puts(" -passed!");
}
