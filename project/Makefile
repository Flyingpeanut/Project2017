CC= gcc
CFLAGS= -g -Wall
LFLAGS= -lpthread
all:  Ngram main

Ngram:	Ngram.c Ngram.h
	gcc  -g -Wall -c  Ngram.c 

main: main.c header.h Ngram.o
	gcc  -g -Wall  main.c Ngram.o -o  myexe 

clean: 
	$(RM) myexe *.o *~



