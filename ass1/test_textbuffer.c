////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 ... assignment 1: Textbuffer ADT
//
// 2018-12-02	Gavin Wang <z5206647@unsw.edu.au>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "textbuffer.h"

static void test_textbuffer_empty (void);
static void test_textbuffer_one (void);
static void test_textbuffer_two (void);
void whitebox_tests(void);

int main (void)
{
    whitebox_tests();
    
	//Testcases for basic operations using a single textbuffer
    test_textbuffer_empty();
	test_textbuffer_one();
	test_textbuffer_two();
	
	//Test not conclude on /n
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
    
    char *str = textbuffer_to_str(new);
    assert(strcmp(str,"\n\n") == 0);
    free(str);
        
    textbuffer_drop(new);
    puts(" -passed!");
}


