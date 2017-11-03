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

		if(binary_search(currentnode, word, *cap_used)==0){ // FOUND
				// is it last then mark final!
		}
		else{ // not inside add
			if(*maxcap == *cap_used){	// if full double
				ind->root = enlarge_node(currentnode, maxcap);
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
		return ARG_ERROR;
	}
	 
	if(deleting_this == NULL){

		printf("NO NGRAM\n");
		return ARG_ERROR;
	}

	int* to_be_deleted;  // position of deletion targets in each level of the trie
	int level,cap_used , position_found = -1,
	  size_of_Ngram = deleting_this->currentsize;
	
	trie_node * currentnode = ind->root;
	cap_used = ind->added;
	trie_node **deleted_nodes = malloc(sizeof(trie_node*)*size_of_Ngram);
	to_be_deleted = malloc(sizeof(int)*size_of_Ngram);
	
	if(deleted_nodes == NULL || to_be_deleted == NULL){

		printf("MEMERROR\n");
		return MEMERR;
	}

	for(level=0; level < size_of_Ngram; level++){

			char* word = deleting_this->wordBuffer[level];
			position_found = binary_search(currentnode, word, cap_used);

			if(position_found >= 0){ // FOUND

				to_be_deleted[level] = position_found;			// mark position for later deletion
				deleted_nodes[level] = currentnode;
				cap_used = currentnode[position_found].added;	//	prepare for next iteration and go down one level
				currentnode = currentnode[position_found].children;
			}
			else{ // Ngram isn't in trie free allocated space and stop delete

				free(to_be_deleted);
				return NOTFOUND;
			}
	}
	delete_ngram_subfunction(ind, deleted_nodes, to_be_deleted, size_of_Ngram);
	free(to_be_deleted);

	return OK_SUCCESS;
}

// whole ngram has been found and will be deleted
void 	delete_ngram_subfunction(trie* ind,trie_node** deleted_nodes, int * to_be_deleted, int maxlevel){

	int level  = maxlevel - 1;
	trie_node * currentnode = deleted_nodes[level];
	currentnode[ to_be_deleted[level] ].final = false;

	for(; level >= 0; level--){

		currentnode = deleted_nodes[level];
		int position_found = to_be_deleted[level];

		if( currentnode[position_found].added > 0){	 
			// other n grams pass from here can't delete, nor upper level
			// thus deletion stop here
			return;
		}
		else{	//
			if( currentnode[position_found].children != NULL ) {

				free(currentnode[position_found].children);
			}

			int move;

			if(level==0){	// root case

				move = (ind->added-position_found)*sizeof(trie_node);
				ind->added--;
			}
			else{		

				trie_node* parentnode = deleted_nodes[level - 1];
				move = (parentnode->added-(position_found+1))*sizeof(trie_node);	//
				parentnode->added--;
			}

			if(move > 0){	// if deleted element is 

				memmove(&(currentnode[position_found]),&(currentnode[position_found+1]), move);
			}
			else if (move == 0){	// if deleted element is in last place just reset it

				currentnode[position_found].word[0]		= '\0';
				currentnode[position_found].final 		= false;
				currentnode[position_found].capacity 	= 0;
				currentnode[position_found].added 		= 0;
				currentnode[position_found].children 	= NULL;
			}
			else{	// position if bigger than size of 

				printf("why?\n");
			}
		}
	}
}

// quesstion try 1

char* search(trie* ind, Ngram* Qgram){

	int ngramsize = Qgram->currentsize;
	int i,j,k,child_position,ngram_length,capacity;
	trie_node* wut = ind->root;
	capacity = ind->added;

	for(j=1;j<ngramsize;j++){
		for(i=j;i<ngramsize;i++){
			child_position=-1;
			ngram_length=-1;

			child_position=binary_search(wut,Qgram->wordBuffer[i],capacity);

			if(child_position>=0){
			    ngram_length++;
			        if(wut->final){
			        		// nmz auto to for dn xreiazetai 
			        		// aplws ektupwse wordBUffer[j]
			         	for(k=0;k<=ngram_length;k++){
			        		printf("%s",Qgram->wordBuffer[k]);
			        	}
			        }
			 // etsi nmz katevaineis ena epipedo ... pairneis ta paidia tou komvou pou thes
			wut= wut[child_position].children;	// get the children

			}else{
				break;
			}



		}

	}

	return NULL;
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