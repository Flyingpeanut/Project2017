#include "header.h" 
#include "Ngram.h"

int wholeLine(FILE* file, char** line, int* size);

int main(int argc, char* argv[]){
    
	char   inputFile[WORDLIMIT];
    char   queryfile[WORDLIMIT];
   // char   word[WORDLIMIT];
    FILE * input;
    int option;
    if(argc<5){
        printf("\n\nNot Enough Arguments\n\n");
        return ARG_ERROR;
    }

	while ((option=getopt(argc, argv, "i:q:")) != -1){

            switch(option){
            case'i':
                strcpy(inputFile,optarg);
            case'q':
                strcpy(queryfile,optarg);
                break;                			           
            default:
                printf("Argument %s not recognizable and it is ignored\n", optarg);
                break;
            }
    }
    input   = fopen(inputFile,"r");
    if (input==NULL) {
        printf("Cannot open txt file\n");
        return FILEOPENINGERROR;
    }
    
    int size=0;
    char * inputline = malloc(sizeof(char)*LINELIMIT);
    int     linesize = LINELIMIT;
    Ngram *  myNgram;
    createNgram(&myNgram);
   // printf("TESTING NGRAM\n");
    while(wholeLine(input ,&inputline,&linesize)!=-1){    // reads a line (hopefully)
        size++;
        printf("I JUST ReAD : %s splliting : ", inputline);
        char *token ;
        char *state;

        for (token = strtok_r(inputline, " \n", &state);
             token != NULL;
             token = strtok_r(NULL, " \n", &state))
        {
            addinNgram(myNgram,token);
        }

         printf("PRINTING NGRAM\n");
        printNgram(myNgram);

        // do shit with Ngram!!!


        printf(" Reseting NGRAM\n");
        resetNgram(myNgram);
    }
    printf("Finished reading input file of %d lines\n", size);
    
    FILE* work   = fopen(queryfile,"r");
    if (work==NULL) {
        printf("Cannot open work file\n");
        return FILEOPENINGERROR;
    }
    int queries     = 0;
    int deletions   = 0;
    int additions   = 0;
    while(wholeLine(work, &inputline, &linesize)!= -1){    // reads a line (hopefully)
        
        printf("I JUST ReAD : %s ", inputline);
        char *token ;
        char *state;
        char *type;
        type = strtok_r(inputline, " \n", &state);
        for (token = strtok_r(NULL, " \n", &state); 
            token != NULL; token = strtok_r(NULL, " \n", &state)){
   
            addinNgram(myNgram,token);
        }


        if(strcmp(type,QUERY)==0){
            printf("found QUERY");
            queries++;
        }
        else if (strcmp(type,ADD)==0){
            printf("found ADD");  
            additions++; 
        }
        else if (strcmp(type,DELETE)==0){
            printf("found DELETE\n");  
            deletions++;
        }
        else if (strcmp(type,FINAL)==0){
            printf("found FINAL\n");  
            break;
        }
        else{
            printf("NOT VALID COMMAND\n");
            break;
        }
       //  printf("PRINTING NGRAM\n");
        printNgram(myNgram);

        // do shit with Ngram!!!

        // reseting Ngram for next use
        resetNgram(myNgram);
    }
     printf("Finished parsing work file of %d queries, %d additions, %d deletions\n", queries, additions, deletions);

   // printf(" Deleting NGRAM\n");
    deleteNgram(&myNgram);
    return 0;
}


int wholeLine(FILE* file, char** line, int* size){
    int newsize = *size;
    *line[0] = '\0';

   char readBuf[LINELIMIT];

   if(feof(file)){
        return -1;
   }

   while (!feof(file))
   {
    fgets(readBuf, LINELIMIT, file);
     
    strcat(*line, readBuf);
    
  //  printf("line : %s, readbuf: %s", *line, readBuf);
    //printf(".%c. .%c.\n\n",readBuf[strlen(readBuf)-1],readBuf[strlen(readBuf)]);
    
    if (readBuf[strlen(readBuf)-1] != '\n')  // an o teleutaios xarakthras dn einai allagh grammhs 3anadiavase 
     {
       newsize += LINELIMIT;
       *line = realloc(line, newsize);
       if(*line == NULL){
            *size = newsize;
            return -1;
       }
     }
     else
       break;
   }
   *size = newsize;
   return 0;
}