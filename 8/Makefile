# COMP2521 19T0 ... lab 8 makefile

CC	 = gcc
CFLAGS = -g

.PHONY: all
all:	words words2 mkwords

mkwords:	mkwords.c
test_tree.o:  Tree.o Item.o test.o

words:		words.o Tree.o Item.o
words.o:	words.c Tree.h Item.h
Tree.o:		Tree.c Tree.h Item.h

words2:		CFLAGS+=-pg
words2:		LDFLAGS+=-pg
words2:		words2.o HashTable.o List.o Item.o
words2.o:	words2.c HashTable.h Item.h
HashTable.o:	HashTable.c HashTable.h Item.h List.h
List.o:		List.c Item.h List.h

Item.o:		Item.c Item.h

.PHONY: clean
clean:
	-rm -f mkwords mkwords.o
	-rm -f words words.o Tree.o
	-rm -f words2 words2.o HashTable.o List.o
	-rm -f Item.o
	-rm -f gmon.out

.PHONY: give
give:
	give cs2521 lab08 Tree.c lab08.txt HashTable.c
