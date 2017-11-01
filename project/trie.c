#include "trie.h"

// creates a node
trie_node* create_trie_node(){

	trie_node* created = malloc(sizeof(trie_node)*STARTNODESIZE);

	if(created==NULL){
		printf("MEMERROR\n");
		return NULL;
	}
	int i;
	for(i=0;i<STARTNODESIZE;i++){
		created[i].word[0] 	= '\0';
		created[i].final 		= false;
		created[i].children 	= NULL;
		created[i].capacity 	= 0;
		created[i].added 		= 0;		
	}
	return created;
}

trie_node*	enlarge_node(trie_node* mynode,int* mysize){

	if(mynode==NULL){
		printf("no node... creating node\n");

		return create_trie_node();
	}
	trie_node* enlargednode = realloc(mynode,(*mysize)*sizeof(trie_node));
	if(enlargednode == NULL){
		printf("MEMERROR");
		return NULL;
	}
	*mysize *=2;
	return enlargednode;
}

// creates empty Trie
trie* init_Trie(){

	trie* created = malloc(sizeof(trie));

	if(created==NULL){
		printf("MEMERROR\n");
		return NULL;
	}

	created->root = NULL;
	 /*create_trie_node();

	if(created->root==NULL){
		printf("MEMERROR\n");
		free(created);
		return NULL;
	}*/
	created->added 		= 0; //STARTNODESIZE;
	created->capacity	= 0;
	created->treesize 	= 0;
	created->Ngrams 	= 0;

	return created;
}

//
int  insert_ngram(trie* ind,Ngram* adding_this){
	
	if(ind==NULL){
		printf("NO TRIE\n");
		return -1;
	}
	
	if(adding_this==NULL){
		printf("NO NGRAM\n");
		return -2;
	}

	trie_node * currentnode = ind->root, *nextnode = NULL;
	int  i, level = 0;
	int*  maxcap = &ind->capacity, *cap_used = &ind->added;  	// needed?

	for(i=0; i< adding_this->currentsize; i++){
		char* word = adding_this->wordBuffer[i];

		if(binary_search(currentnode, word, cap_used)==0){ // FOUND
				// is it last then mark final!
		}
		else{ // not inside add
			if(*maxcap == *cap_used){	// if full double
				ind->root = enlarge_node(ind->root, ind->capacity);
			}

			// add it and sort it 
		}

	}

	return 0;
}

//return position where word was found 
// else -1 if nothing was found
int binary_search(trie_node * currentnode, char* word,int mysize){
	int small = 0, big = mysize, middle = (small+big)/2;
	
	while (small <= big) {
	      
	      	if (strcmp(currentnode[middle].word, word) == 0){ 			//FOUND
	      		printf("%s found at location %d.\n", word, middle+1);
	      		return middle;	 
	      	}  
	      	else if (strcmp(currentnode[middle].word, word) < 0){
	         	big = middle + 1;
	        	
	      	}
	      	else
	         	small = middle - 1;
	 
	      middle = (small + big)/2;
	}

	return -1; 	
}


int  delete_ngram(trie* ind,Ngram* deleting_this){

	return 0;
}


char* search(trie* ind, Ngram* searching_this){

	return 0;
}




// helps in destruction of trie different than delete_ngram
void delete_node(trie_node* node){
	
	if(node!=NULL){
		int i =0;
		for(; i < node->capacity; i++){

			delete_node(&(node->children[i]));
		}
		free(node);
	}
}
// destroys whole trie
void delete_index(trie** ind){
	if(*ind!= NULL){
		int  i;
		for(i=0;i<(*ind)->capacity; i++){
			delete_node(&((*ind)->root[i]));
		}
		free(*ind);
	}
}