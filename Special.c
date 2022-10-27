#include "library.h"




int redirection(char** input, int ReOuput, int ReInput, int ReAppend, int currentLocation){//still need adjustments, doesnt work the first time it is inputted

    int OutputFile;
    int InputFile;

    //for >
    if(ReOuput == 1){
        //printf("%s",input[currentLocation+1]);
        input[currentLocation] = NULL;
        OutputFile = open(input[currentLocation+1],O_WRONLY | O_CREAT | O_TRUNC,0777);
        dup2(OutputFile,STDOUT_FILENO);
    }
    //for >>
    else if(ReAppend == 1){
        input[currentLocation] = NULL;
        OutputFile = open(input[currentLocation+1],O_WRONLY | O_CREAT | O_APPEND,0777);
        dup2(OutputFile,STDOUT_FILENO);
        
    }
    //for <
    else if(ReInput== 1){
        input[currentLocation] = NULL;
        InputFile = open(input[currentLocation+1],O_RDONLY, 0777);
        dup2(InputFile,STDIN_FILENO);

    }
    return 0;
}


int piping(char** input, char** input2){
    int NotWorking = 0;
    int NotWorking2 = 0;

    int fd[2];
    if(pipe(fd) == -1){
        exit(1);
    }

    pid_t pid1 = fork();
    if (pid1 < 0){
        return -1;
    }

    if(pid1 == 0){
        //proccess 1
        //The left side of the pipe
        //changes the output
        dup2(fd[1],STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        
       // execv() the left side of the '|'


        // NotWorking = execvp(input[0],input);
        // if(NotWorking == -1){
        //     executing(input);
        // }
        NotWorking = executing(input);
        if(NotWorking == -1){
            execvp(input[0],input);
            printf("%s",strerror(errno));
        }

        exit(1);
    
    }

       //
       //execvp() the right side of the '|'
       //somehow check if i can run it in the builtin or the external
       //if execv returns from the the PWD
       //then use call execv from the /bin/
       //just like the externalbuiltin2

       //execv(path to ls, "ls")

    else{
        //in parent
        //for the right right side of the pipe
        pid_t pid2 = fork();
        if (pid1 < 0){
            return 2;
        }

        if(pid2 == 0){
            //proccess 2
            dup2(fd[0],STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            NotWorking2 = execvp(input2[0],input2);
            if(NotWorking2 == -1){
                executing(input2);
            }
            exit(1);
        }
        
        else{
            close(fd[0]);
            close(fd[1]);
            waitpid(pid1,NULL,0);
            waitpid(pid2,NULL,0);

        }
    }

    return 0;
}

int background(char** input){
    return 0;
}

