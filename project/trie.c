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

	if(mynode==NULL){	// Node was- uninitialized
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
	         	big = middle - 1;
	        	
	      	}
	      	else
	         	small = middle + 1;
	 
	      middle = (small + big)/2;
	}

	return -1; 	
}


int  delete_ngram(trie* ind,Ngram* deleting_this){

	if(ind == NULL){
		printf("NO TRIE\n");
		return -1;
	}
	 
	if(deleting_this == NULL){
		printf("NO NGRAM\n");
		return -2;
	}

	int* to_be_deleted;  // position of deletion targets in each level of the trie
	int level,cap_used , position_found = -1,
	  size_of_Ngram = deleting_this->currentsize;
	
	trie_node * currentnode = ind->root;
	cap_used = ind->added;
	// **to_be_deleted = malloc(sizeof(trie_node*)*size_of_Ngram);
	to_be_deleted = malloc(sizeof(int)*size_of_Ngram);
	
	if(/*to_be_deleted == NULL ||*/ to_be_deleted == NULL){
		printf("MEMERROR\n");
		return MEMERR;
	}

	for(level=0; level < size_of_Ngram; level++){

			char* word = deleting_this->wordBuffer[level];
			position_found = binary_search(currentnode, word, cap_used);

			if(position_found >= 0){ // FOUND

				to_be_deleted[level] = position_found;			// mark position for later deletion
				cap_used = currentnode[position_found].added;	//	prepare for next iteration and go down one level
				currentnode = currentnode[position_found].children;
			}
			else{ // Ngram isn't in trie free malloced space and stop delete 
				free(to_be_deleted);
				return -1;
			}
	}
	delete_ngram_subfunction(ind, to_be_deleted);
	free(to_be_deleted);

	return OK_SUCCESS;
}

// whole ngram has been found and will be deleted
void 	delete_ngram_subfunction(trie* ind, int * to_be_deleted, int maxlevel){

	
	trie_node * currentnode = ind->root;
	int level, cap_used = ind->added;

	for(level = maxlevel-1; level >= 0; level--){
		int position_found = to_be_deleted[level];
		int size_children = currentnode[position_found].added;
		if(size_children > 1){
			printf("hue\n");
		}
		else{
			printf("hue\n");
		}

	}

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