#include "library.h"


int cd(){

    char cwd[1000];

    printf("\n%s\n",getcwd(cwd,sizeof(cwd)));
    return 0;
}

int cdWithPath(char* pathname){
    //chdir(pathname);
    return 0;
}

int environment(){
   // printf("%s",environ());
    return 0;
}

int quit(){
    exit(1);
    return 0;
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

    if ( getchar() == '\n'){
        return 0;
    }
return 0;
}



