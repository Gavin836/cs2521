////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 ... assignment 1: Textbuffer ADT
//
// 2018-12-02	Gavin Wang  <z5206647@unsw.edu.au>

#include "textbuffer.h"

// your implementation goes here.
typedef struct sentence *Sentence;
typedef struct sentence {
      Sentence next;
      Sentence prev;
      char *string;
}sentence;

typedef struct text_buffer {
    Sentence head;
    Sentence tail;
    int no_sentences; 

}text_buffer;



Textbuffer textbuffer_new (const char *text){

}

void textbuffer_drop (Textbuffer tb){

}


