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

int main (void)
{
    //whitebox_tests();
    
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
    //size_t no_lines;
    //size_t no_bytes;
    
    new = textbuffer_new("");
    //no_lines = textbuffer_lines(new);
    //no_bytes = textbuffer_lines(new);
    
    assert(new == NULL);
    puts(" -passed!");
}

static void test_textbuffer_one (void){
    printf("Single newline buffer test");
    Textbuffer new;
    //size_t no_lines;
    //size_t no_bytes;
    
    new = textbuffer_new("\n");
    //no_lines = textbuffer_lines(new);
    //no_bytes = textbuffer_lines(new);
    
    assert(new != NULL);
    //assert(no_lines == 1);
    //assert(no_bytes == 1);
    
    textbuffer_drop(new);
    puts(" -passed!");
}

static void test_textbuffer_two (void){
    printf("Two newlines buffer test");
    Textbuffer new;
    //size_t no_lines;
    //size_t no_bytes;
    
    new = textbuffer_new("\n\n");
    //no_lines = textbuffer_lines(new);
    //no_bytes = textbuffer_lines(new);
   
    assert(new != NULL);
    //assert(no_lines == 2);
    //assert(no_bytes == 2);
       
    textbuffer_drop(new);
    puts(" -passed!");
}


