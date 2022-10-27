#include "library.h"
char ** environment;
char* curDirect;
char* originalDirect;
int pipeFound = 0;


//for taking in the input in interactive mode
char* input(){
    char* buffer;
    size_t size = 0;
    

    getline(&buffer,&size, stdin); //stores what is inputted into buffer

    if(strcmp(buffer,"\n")== 0){
        interactive();
    }

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
    
    }

    return 0;   
}


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

        else if( strcmp(token[i], "|") == 0){ //the piping work
            if (token[i + 1] == NULL){
                puts("invalid argument");
                return 0;
            }
            pipeFound = 1;
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

        }
        else if(strcmp(token[i], "&") == 0){
    
            //run the background function
            //everything before the & execute
            //forking and having the child run the command and but then never call exit() 
        }
      

        i++;
    }
    if(pipeFound == 0){
        executing(originalToken);

    }
    
    dup2(Originalstdou, STDOUT_FILENO);
    dup2(Originalstdin, STDIN_FILENO);
    close(Originalstdou);
    close(Originalstdin);


    return 0;   
}

int executing(char** token){

    if(strcmp(token[0], "cd") == 0){
            //run the change cd function
           return cd(token);

        }
    else if(strcmp(token[0], "clear") == 0){
       return clear();
        
    }
    else if(strcmp(token[0], "dir") == 0){
        // if(dir(token) == -1){
        //     return 0;
        // }
       return dir(token); 
        
    }
    else if(strcmp(token[0], "environ") == 0){
       return environ(environment);

    }
    else if(strcmp(token[0], "help") == 0){
       return help();
        
    }
    else if(strcmp(token[0], "echo") == 0){
       return echo(token);
        
    }
    else if(strcmp(token[0], "pause") == 0){
      return pause();
        
    }
    else if(strcmp(token[0], "quit") == 0){
       return quit();
        
    }
    // else if(pipeFound == 0){
    //     externalBuiltin(token);
    // }
    else if(pipeFound == 0){
        externalBuiltin(token);
    }
    

    return -2;
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
        printf("UserShell>");
        char* inputLine = input();
        char** tokenize = tokenizingInput(inputLine);
        checking(tokenize);
        pipeFound = 0; 
    }
    
    return 0;   
}


int main(int argc, char** argv, char**envp){

    if(argc == 1){
        environment = envp;
        char cwd[1000];
        originalDirect = getcwd(cwd,sizeof(cwd));
        interactive(); //can take inputs in from stdin
    }
    if ( argc == 2){
        batch(argv[1]); //executing commands from a file
        //fgets
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


