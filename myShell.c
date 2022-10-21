#include "library.h"

char ** environment;
char* curDirect;
int executing(char** token);

//for taking in the input in interactive mode
char* input(){
    char* buffer;
    size_t size = 0;

    getline(&buffer,&size, stdin); //stores what is inputted into buffer
    int length = strlen(buffer);
    if (buffer[length - 1] == '\n'){
        buffer[length - 1] = '\0';
    } 
    return buffer;
}

//tokenizing the input
char** tokenizingInput(char* input){
    char changes[strlen(input)];
    strcpy(changes,input);
    char** token;
    char* buffer;
    size_t size = 100;
    int i = 0;
    token = (char**)malloc(size);

    buffer = strtok(changes," \t"); //remove the extra spaces
    while(buffer != NULL){//add the tokenize strings into an array of pointers
        token[i] = buffer;
        buffer = strtok(NULL, " \t");
        i++;
    }
    // if ( i >= size){//increase the size of the array
    //     token = realloc(token,size * 2);
    // }

    token[i] = NULL;

    return token; //token now has an array of commands
}

int externalBuiltin(char** input){ //cant call commands from other directories

    char* bin = "/bin/";
    char binPath[1000];
    strcpy(binPath,bin);
    strcat(binPath,input[0]);

    pid_t pid = fork();
    if(pid == -1){
        printf("%s",strerror(errno));
        return -1;
    }

    if(pid == 0){// in the child
        //puts("i am the child");
        //execv
        execvp(input[0],input);
        printf("%s",strerror(errno));
        exit(1);      //executing the external built in with the path and the certain argument

    }else{//in the parent
        wait(NULL);
        //puts("i am the parent");
    
   // wait for the child to finish
    }

    return 0;   
}

int externalBuiltin2(char** input){ //SINce we can use EXECVP THIS IS POINTLESS


    char* bin = "/bin/";
    char binPath[1000];
    strcpy(binPath,bin);
    strcat(binPath,input[0]);

    pid_t pid = fork();
    if(pid == -1){
        printf("%s",strerror(errno));
        return -1;
    }

    if(pid == 0){   // in the child
        //puts("i am the child");
        //execv
        int NotWorking = 0;
        NotWorking = execv(binPath,input);
            //printf("%s",strerror(errno));

        if(NotWorking == -1){
            char currentDirect[1000];
            
            strcat(curDirect,"/");
            strcpy(currentDirect,curDirect);
            strcat(currentDirect,input[0]);
            //strcat(curDirect,"./");
            execv(currentDirect,input);
            printf("%s",strerror(errno));

        }
    
        exit(1);      //executing the external built in with the path and the certain argument

    }else{//in the parent
        wait(NULL);
        //puts("i am the parent");
    
   // wait for the child to finish
    }

    return 0;   
}
//append the file path to the end of bin and then run the command

//check if its in bin, then check if its in the directory

//--------------------------------------------------------------------------------//
//char *built[] = {"cd","clear","dir","environ","help","echo","puase","quit"};
//char *special[] = {">",">>","<","|","&"};
//--------------------------------------------------------------------------------//



int checking(char** token){
       
    int i = 0;
    char** originalToken = token;
    int outputFile = 0;
    int inputFile = 0;
    int AppendFile = 0;
    int currentLocation = 0;
    int Originalstdin = dup(STDIN_FILENO);
    int Originalstdou = dup(STDOUT_FILENO);
    

    //first check for speical characters
    while(token[i] != NULL){

        //for outputing to another file
        if( strcmp( token[i], ">")== 0){
            if (token[i + 1] == NULL){
                puts("invalid argument");
                return 0;
            }
            //token[i] = NULL;
            outputFile = 1;
            currentLocation = i;
            //call redirection(with the apporiate flags)
            //function to set the file desciptors
            redirection(token,outputFile,inputFile,AppendFile,currentLocation);
            
        }
        //for appending to another file
        else if(strcmp( token[i], ">>")== 0){
            if (token[i + 1] == NULL){
                puts("invalid argument");
                return 0;
            }
            //token[i] = NULL;
            AppendFile = 1;
            currentLocation = i;
            redirection(token,outputFile,inputFile,AppendFile,currentLocation);
            
        }
        //for inputing into another file            //not working right now
        else if(strcmp( token[i], "<")== 0){
            if (token[i + 1] == NULL){
                puts("invalid argument");
                return 0;
            }
            //token[i] = NULL;
            inputFile = 1;
            currentLocation = i;
            redirection(token,outputFile,inputFile,AppendFile,currentLocation);
        }

        else if( strcmp(token[i], "|") == 0){ //the piping works but not he inputs
            if (token[i + 1] == NULL){
                puts("invalid argument");
                return 0;
            }

            currentLocation = i;
            
            char* input2[1000];
            //char** input2 = malloc( 1000 * sizeof(char*));
            int j = currentLocation + 1;
            int k = 0;
            while(token[j] != NULL){
                input2[k] = token[j];
                j++;
                k++;
            }
            input2[k] = NULL;
            token[currentLocation] = NULL;
            
            piping(token,input2);
            //working but still printing to terminal    

        }
        else if( strcmp(token[i], "&") == 0){
    
            //run the background function
            //everything before the & execute
            //forking and having the child run the command and but then never call exit() 
        }
            
            

        i++;
       
    }

    //next have to check if there are builtins with the special characters
    //could make this into a seperate function and call this function inside of checking special
    //this way this could be called inside of my pipe
        // if(strcmp(token[0], "cd") == 0){
        //     //run the change cd function
        //     cd(token);

        // }
        // else if(strcmp(token[0], "clear") == 0){
        //     clear();
            
        // }
        // else if(strcmp(token[0], "dir") == 0){
        //     dir(token);
            
        // }
        // else if(strcmp(token[0], "environ") == 0){
        //     environ(environment);
    
        // }
        // else if(strcmp(token[0], "help") == 0){
        //     help();
            
        // }
        // else if(strcmp(token[0], "echo") == 0){
        //     echo(token);
            
        // }
        // else if(strcmp(token[0], "pause") == 0){
        //     pause();
            
        // }
        // else if(strcmp(token[0], "quit") == 0){
        //     quit();

            
            
        // }
        // else{
        //     //run the extranalbuiltin command 
        //     externalBuiltin2(token);
        // }
    //set the file descriptors back to normal
    executing(originalToken);
    dup2(Originalstdou, STDOUT_FILENO);
    dup2(Originalstdin, STDIN_FILENO);
    close(Originalstdou);
    close(Originalstdin);


    return 0;   
}



int executing(char** token){
    if(strcmp(token[0], "cd") == 0){
            //run the change cd function
            cd(token);

        }
        else if(strcmp(token[0], "clear") == 0){
            clear();
            
        }
        else if(strcmp(token[0], "dir") == 0){
           // printf("%s\n",token[1]);
            dir(token);//not working correctly , issue with the char** passed through the function
            
        }
        else if(strcmp(token[0], "environ") == 0){
            environ(environment);
    
        }
        else if(strcmp(token[0], "help") == 0){
            help();
            
        }
        else if(strcmp(token[0], "echo") == 0){
            echo(token);//not working correctly
            
        }
        else if(strcmp(token[0], "pause") == 0){
            pause();
            
        }
        else if(strcmp(token[0], "quit") == 0){
            quit();
            
            
        }
        else{
            //run the extranalbuiltin command 
            externalBuiltin(token);
        }

    return 0;
}


int batch(char* input){

    // FILE* file;
    // file = open(input,"O_readit");
    // char buffer[100];
    

    return 0;

}

int interactive(){
    char cwd[1000];
    while(1){
        curDirect = getcwd(cwd,sizeof(cwd));
        printf("\n%s\n",curDirect);
        printf("UserShell>");
        char* inputLine = input();
        char** tokenize = tokenizingInput(inputLine);
        checking(tokenize);
        //executing(tokenize);  
    }
    
    return 0;   
}


int main(int argc, char** argv, char**envp){

    if(argc == 1){
        environment = envp;
        interactive(); //can take inputs in from stdin
    }
    if ( argc == 2){
        batch(argv[1]); //executing commands from a file
    }
    if (argc >= 3){
        puts("too many arguments");
        exit(3);
    }

   return 0;
}

//
// int main(int argc, char** argv, char**envp) {
//     char* command = "dir";
//     char* argument_list[] = {"dir", NULL};

//     char** = ["dir",NULL];

//     printf("Before calling execvp()\n");

//     // Calling the execvp() system call
//     int status_code = execvp(command, argument_list);

//     if (status_code == -1) {
//         printf("Process did not terminate correctly\n");
//         exit(1);
//     }

//     printf("This line will not be printed if execvp() runs correctly\n");

//     return 0;
// }
//
//


