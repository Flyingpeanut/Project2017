// quesstion try 1
#include "question.h"
#include "Ngram.h"
#include "trie.h"
#include "header.h"

void question(trie_node* wut,int ngramsize,Ngram* Qgram){
int i,j,k,child_position,ngram_length;

for(j=1;j<ngramsize;j++){
for(i=j;i<ngramsize;i++){
child_position=-1;
ngram_length=-1;

child_position=binary_search(wut,Qgram->wordBuffer[i],wut->capacity);

if(child_position>=0){
    ngram_length++;
        if(wut->final){

         for(k=0;k<=ngram_length;k++){
         printf("%s",Qgram->wordBuffer[k]);}
             }

wut=&wut->children[child_position];
}else{
break;
}



}

}

}



