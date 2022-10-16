#include "library.h"


int cd(char** input){ //working
    if(chdir(input[1]) == -1){
        strerror(errno);
    }

    char cwd[1000];
    printf("\n%s\n",getcwd(cwd,sizeof(cwd)));
    return 0;

}

int dir(char** input){//working

    DIR* d;
    if(input[1] == NULL){
        d = opendir(".");
    }else{
        d = opendir(input[1]);
    } 
     if (d == NULL){
        puts("this directory doesn't exist");

        return -1; 
    }
    struct dirent* directory;
    //reads what is in the directory
    directory = readdir(d);
    
    //while the directory is not empty
    while(directory != NULL){
        printf("%s\t\t",directory->d_name);

    
        directory = readdir(d); 
    }
    closedir(d);

    return 0;
}

// int echo(char* input){//working but need working with parameters

//     char copy[strlen(input)];
//     strcpy(copy,input);
    

//     char* buffer;
//     buffer = strtok(copy," \t");
//     while(buffer != NULL){
//         printf("%s ",buffer);
//         buffer = strtok(NULL, " \t");
//     }
//     puts(" ");

//     return 0;
// }

int echo(char** input){ //working
    int i = 0;
    while(token[i] != NULL){
        printf("%s ",token[i]);
        i++;
    }
    return 0;
}

int enviro(char** input){ //working
    int i = 0;
    while(input[i] != NULL){
        
        printf("%s:%s",(input[i]),getenv(input[i]));
        i++;
    }

    return 0;
}

int quit(){//working
    exit(1);
}

int help(){ //need to use exec() 

    FILE* file;
    file = fopen("help.txt","r");
    if(file == NULL){
        strerror(errno);
    }
    return 0;
}


int pause(){ //working

    while ( getchar() !='\n'){
        
    }
return 0;
}



