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

	
	if(ind->capacity == ind->added){
		ind->root = enlarge_node(ind->root, &(ind->capacity));
	}
	
	trie_node * currentnode = ind->root, nextnode = NULL;
	int 	first, last, middle, i, level = 0,
	mysize = ind->capacity, 
	used = ind->added;  	// needed?

	for(i=0; i< adding_this->currentsize; i++){
		char* word = adding_this->wordBuffer[i];
		
		first = 0;
		last = used;	
	   	middle = (first+last)/2;
	 
	   while (first <= last) {
	      
	      	if (strcmp(currentnode[middle].word, word) == 0){ //FOUND
	      		printf("%s found at location %d.\n", word, middle+1);
	      		//// if it exists 
			
					// if there no more words make "final" true (mark that it part of a Ngram)
			
					// if there are more words just go to the next word
				 
	      	}  
	      	else if (strcmp(currentnode[middle].word, word) < 0){
	         	
	        	
	      	}
	      	else
	         	last = middle - 1;
	 
	      middle = (first + last)/2;
	   }
   	  if (first > last)
      printf("Not found! %d is not present in the list.\n", search);
 
		//search if word exists in this level 

			
			// if it doesn't exist
					// add it - sort it , if last mark it final


	}

	return 0;
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