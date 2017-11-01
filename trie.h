#ifndef __Trie__
#define	 __Trie__

#include "header.h"
#include "Ngram.h"

#define STARTNODESIZE  10

typedef struct trie_node trie_node;

struct trie_node{

	char 		word[WORDLIMIT];
	bool 		final;
	trie_node* 	children;
	int 		capacity;
	int 		added;

};


typedef struct trie{
	
	trie_node* 	root;
	int 		capacity;
	int 		added;
	int 		treesize;
	int 		Ngrams;

}trie;

trie* init_Trie();
trie_node* create_trie_node();
//OK SUCCESS?!

int  insert_ngram(trie* ind,Ngram* adding_this);

int  delete_ngram(trie* ind,Ngram* deleting_this);

char* search(trie* ind, Ngram* searching_this);

void delete_index(trie** ind);
void delete_node(trie_node* node);

#endif
