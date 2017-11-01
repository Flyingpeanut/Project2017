#include "trie.h"


trie_node* create_trie_node(){

	trie_node* created = malloc(sizeof(trie_node)*STARTNODESIZE);

	if(created==NULL){
		printf("MEMERROR\n");
		return NULL;
	}

	created->word[0] = '\0';
	created->final = false;
	created->children = NULL;
	created->size = 0;

	return created;
}

trie* init_Trie(){

	trie* created = malloc(sizeof(trie));

	if(created==NULL){
		printf("MEMERROR\n");
		return NULL;
	}

	created->root = create_trie_node();

	if(created->root==NULL){
		printf("MEMERROR\n");
		free(created);
		return NULL;
	}
	created->rootsize 	= STARTNODESIZE;
	created->treesize 	= 0;
	created->Ngrams 	= 0;

	return created;
}

void delete_node(trie_node* node){
	
	if(node!=NULL){
		int i =0;
		for(; i < node->size; i++){

			delete_node(&(node->children[i]));
		}
		free(node);
	}
}

void delete_index(trie** ind){
	if(*ind!= NULL){
		int  i;
		for(i=0;i<(*ind)->rootsize; i++){
			delete_node(&((*ind)->root[i]));
		}
		free(*ind);
	}
}