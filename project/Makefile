CC= gcc
CFLAGS= -g -Wall
LFLAGS= -lpthread
all:  Ngram  trie main 

Ngram: Ngram.c Ngram.h
	gcc  -g -Wall -c  Ngram.c 

trie: trie.c trie.h
	gcc -g -Wall -c trie.c

main: main.c header.h Ngram.o trie.o
	gcc  -g -Wall  main.c Ngram.o  trie.o -o  myexe 

clean: 
	$(RM) myexe *.o *~



