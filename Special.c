#include "library.h"

int redirection(char** input, int ReOuput, int ReInput, int ReAppend, int currentLocation){

    int Originalstdin = dup(STDIN_FILENO);
    int Originalstdou = dup(STDOUT_FILENO);
    
    //for >
    pid_t pid = fork();
    if(pid == -1){
        printf("%s",strerror(errno));
        return -1;
    }

    if(pid == 0){// in the child
        puts("i am the child");

        


        int file = open("filename.txt",O_WRONLY | O_CREAT,0777);
        if(file == -1){
            printf("%s",strerror(errno));
        }

        dup2(file,STDOUT_FILENO);
        close(file);
        
    
        printf("%s",strerror(errno));
        exit(1);      


    }else{//in the parent
        wait(NULL);// wait for the child to finish
        puts("i am the parent");
    
   
    }


    
    return 0;
}

int pipe(){
    
    return 0;
}

//strchar