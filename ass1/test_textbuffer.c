////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 ... assignment 1: Textbuffer ADT
//
// 2018-12-02	Gavin Wang <z5206647@unsw.edu.au>

#include <assert.h>
#include <stdlib.h>

#include "textbuffer.h"

void test_textbuffer_new (void);

int main (void)
{
	// your tests go here!
	//Create testbuffer tests
    test_testbuffer_new();
	
	
	return EXIT_SUCCESS;
}

void test_textbuffer_new(void) {
    assert(textbuffer_new("") == NULL);
    assert(textbuffer_new("Single\n") != NULL);
    assert(textbuffer_new("Double\nDouble\n") != NULL
}
