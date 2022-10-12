#include "library.h"


int cd(char* input){

    char cwd[1000];

    printf("\n%s\n",getcwd(cwd,sizeof(cwd)));
    return 0;
}

int dir(){
    
    return 0;
}



int environment(){
   // printf("%s",environ());
    return 0;
}

int quit(){
    exit(1);
}

int help(){

    FILE* file;
    file = fopen("help.txt","r");
    if(file == NULL){
        strerror(errno);
    }
    return 0;
}


int pause(){

    while ( getchar() !='\n'){
        
    }

return 0;
}



