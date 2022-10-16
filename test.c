#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h> 



int environt(char** input){ //NOT FUCKING WORKING
    int i = 0;
    while(input[i]!= NULL){
        
        printf("%s: %s\n",(input[i]),getenv(input[i]));
        i++;
    }

    return 0;
}
int pause(){ 
    int check = 1;
    while ( check == 1){

        if (getchar() !='\n'){
            continue;
        }else{

            check = 2;
        }
        
        
    }

return 0;
}
int quit(){
    exit(1);
}
int dir(char** input){

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

int echo(char** input){
    int i = 0;
    while(input[i] != NULL){
        printf("%s ",input[i]);
        i++;
        
    }
    return 0;
}


int main(int argc, char **argv, char** envp){

    char *built[] = {"cd","clear","dir","environment","help","echo","puase","quit", NULL};
    char *special[] = {">",">>","<","|","&"};
    char *test[] = {"dir",".vscode"};
    // printf("%d",(&special)[1]- special);
    // printf("%d",sizeof(built)/sizeof(built[0]));

    //environt(envp);
    //pause();

    //quit();
    puts("hello world");
    //dir(test);
    //echo(built);

    
    
    return 0;
}
