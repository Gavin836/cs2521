////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 ... assignment 1: Textbuffer ADT
//
// 2018-12-14	Gavin Wang <z5206647@unsw.edu.au>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "textbuffer.h"

static void test_textbuffer_empty (void);
static void test_textbuffer_one (void);
static void test_textbuffer_two (void);
static void test_textbuffer_sent2 (void);
static void test_textbuffer_sent3 (void);
static void test_multi_buf(void);
static void test_cut (void);
static void test_replace (void);

int main (void)
{   
    white_box_tests();
    
    puts("");
    puts("BLACK BOX TESTS");
    
    
	//Testcases for basic operations using a single textbuffer
    test_textbuffer_empty();
	test_textbuffer_one();
	test_textbuffer_two();
	
	
	test_textbuffer_sent2();
	test_textbuffer_sent3();
	test_multi_buf();
	test_cut();
	test_replace();

	puts("All tests passed!");
	
	return EXIT_SUCCESS;
}


static void test_textbuffer_empty(void) {
    printf("Empty buffer test");
    Textbuffer new;
    
    new = textbuffer_new("");
    
    assert(new == NULL);
    assert(textbuffer_lines(new) == 0);
    assert(textbuffer_bytes(new) == 0);
    assert(textbuffer_to_str(new) == NULL);
    puts(" -passed!");
}

static void test_textbuffer_one (void){
    printf("Single newline buffer test");
    Textbuffer new;
    
    new = textbuffer_new("\n");
    
    assert(new != NULL);
    assert(textbuffer_lines(new) == 1);
    assert(textbuffer_bytes(new) == 1);
    
    char *str = textbuffer_to_str(new);
    assert(strcmp(str,"\n") == 0);
    free(str);
    
    textbuffer_delete(new, 0, 0);
    assert(textbuffer_lines(new) == 0);
    assert(textbuffer_bytes(new) == 0);
    
    textbuffer_drop(new);
    puts(" -passed!");
}

static void test_textbuffer_two (void){
    printf("Two newlines buffer test");
    Textbuffer new;
    
    new = textbuffer_new("\n\n");
   
    assert(new != NULL);
    assert(textbuffer_lines(new));
    assert(textbuffer_bytes(new) == 2);
    assert(textbuffer_search(new, "", false) == 0);
    assert(textbuffer_search(new, "", true) == 1);
    
    char *str = textbuffer_to_str(new);
    assert(strcmp(str,"\n\n") == 0);
    free(str);
    
    textbuffer_delete(new, 0, 1);
    assert(textbuffer_lines(new) == 0);
    assert(textbuffer_bytes(new) == 0); 
      
    textbuffer_drop(new);
    puts(" -passed!");
}

static void test_textbuffer_sent2 (void){
    printf("Two sentence buffer test");
    Textbuffer new;
    
    new = textbuffer_new("First sentence\nSecond sentence\n");
    
    textbuffer_swap(new, 0, 1);
    assert(textbuffer_lines(new) == 2);
    assert(textbuffer_bytes(new) == 31);
    
    char *str = textbuffer_to_str(new);
    assert(strcmp(str, "Second sentence\nFirst sentence\n") == 0);
    free(str);
    assert(textbuffer_search(new, "Third sentence", false) == -1);
    assert(textbuffer_search(new, "First sentence", false) == 1);
    assert(textbuffer_search(new, "First sentence", true) == 1);
    assert(textbuffer_search(new, "Second sentence", true) == 0);
    
    textbuffer_swap(new, 1, 0);
    str = textbuffer_to_str(new);
    assert(strcmp(str, "First sentence\nSecond sentence\n") == 0);
    assert(textbuffer_search(new, "Third sentence", false) == -1);
    assert(textbuffer_search(new, "First sentence", false) == 0);
    assert(textbuffer_search(new, "First sentence", true) == 0);
    assert(textbuffer_search(new, "Second sentence", true) == 1);
    free(str);
    
    textbuffer_drop(new);
    puts(" -passed!");
}

static void test_textbuffer_sent3 (void){
    printf("Three sentence buffer test");
    Textbuffer new;
    
    new = textbuffer_new("First sentence\nSecond sentence\nThird sentence\n");
    
    textbuffer_swap(new, 0, 2);
    assert(textbuffer_lines(new) == 3);
    assert(textbuffer_bytes(new) == 46);
    
    char *str = textbuffer_to_str(new);
    assert(strcmp(str, "Third sentence\nSecond sentence\nFirst sentence\n") == 0);
    assert(textbuffer_search(new, "Third sentence", false) == 0);
    assert(textbuffer_search(new, "First sentence", false) == 2);
    assert(textbuffer_search(new, "First sentence", true) == 2);
    assert(textbuffer_search(new, "Second sentence", true) == 1);
    free(str);
    
    textbuffer_swap(new, 2, 1);
    str = textbuffer_to_str(new);
    assert(strcmp(str, "Third sentence\nFirst sentence\nSecond sentence\n") == 0);
    free(str);
    
    textbuffer_swap(new, 0, 1);
    str = textbuffer_to_str(new);
    assert(strcmp(str, "First sentence\nThird sentence\nSecond sentence\n") == 0);
    assert(textbuffer_search(new, "Third sentence", false) == 1);
    assert(textbuffer_search(new, "First sentence", false) == 0);
    assert(textbuffer_search(new, "First sentence", true) == 0);
    assert(textbuffer_search(new, "Second sentence", true) == 2);
    free(str);
    
    textbuffer_drop(new);
    puts(" -passed!");
}

static void test_multi_buf(void){
    printf("Multiple buffers test");
    Textbuffer new, new2;
    
    new = textbuffer_new("1.First\n1.Second\n");
    assert(textbuffer_lines(new) == 2);
    assert(textbuffer_bytes(new) == 17);
        
    new2 = textbuffer_new("2.First\n2.Second\n");
    assert(textbuffer_bytes(new) == 17);
    
    textbuffer_insert (new, 1, new2);
    char *str = textbuffer_to_str(new);
    assert(strcmp(str, "1.First\n2.First\n2.Second\n1.Second\n") == 0);
    
    free(str);
    
    textbuffer_drop(new);
    puts(" -passed!");
}

static void test_cut (void){
    printf("Two and three element cut test");
    Textbuffer new = textbuffer_new("1\n2\n3\n");
    Textbuffer new2 = textbuffer_cut(new, 0, 1);
    
    char *str = textbuffer_to_str(new);
    assert(strcmp(str, "3\n") == 0);
    assert(textbuffer_lines(new) == 1);
    free(str);
    
    str = textbuffer_to_str(new2);
    assert(strcmp(str, "1\n2\n") == 0);
    assert(textbuffer_lines(new2) == 2);
    free(str);
    
    Textbuffer new3 = textbuffer_cut(new2, 0, 1);
    
    assert(strcmp(textbuffer_to_str(new3), "1\n2\n") == 0);
    assert(textbuffer_lines(new3) == 2);
    assert(textbuffer_lines(new2) == 0);
    assert(textbuffer_to_str(new2) == NULL);

    
    textbuffer_drop(new);
    textbuffer_drop(new2);
    puts(" -passed!");
}

static void test_replace (void){
    printf("Replacing test");
    
    char *str; 
    
    Textbuffer new = textbuffer_new("rep\nFrep\nFrepE\nFrep\nEND\n");
    
    textbuffer_replace(new, "", "EMPTY");
    str = textbuffer_to_str(new);
    assert(strcmp(str, "rep\nFrep\nFrepE\nFrep\nEND\n") == 0);
    free(str);
    
    textbuffer_replace(new, "rep", "_");
    str = textbuffer_to_str(new);
    assert(strcmp(str, "_\nF_\nF_E\nF_\nEND\n") == 0);   
    free(str);   
     
    textbuffer_drop(new);
    
    
    new = textbuffer_new("ABC");
    textbuffer_replace(new, "ABC", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    str = textbuffer_to_str(new);
    assert(strcmp(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n") == 0);    
    free(str);
    
    textbuffer_drop(new);
    
    new = textbuffer_new("ABC");
    textbuffer_replace(new, "ABC", "");
    str = textbuffer_to_str(new);
    assert(strcmp(str, "\n") == 0);
    assert(textbuffer_lines(new) == 1);    
    free(str);
    
    textbuffer_drop(new);
           
    new = textbuffer_new("ABC");
    textbuffer_replace(new, "DEF", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    str = textbuffer_to_str(new);
    assert(strcmp(str, "ABC\n") == 0);   
    free(str);
    
    textbuffer_replace(new, "", "EMPTY");
    str = textbuffer_to_str(new);
    assert(strcmp(str, "ABC\n") == 0);
    free(str);
    
    textbuffer_drop(new);
    
    
    
    puts(" -passed!");
}
