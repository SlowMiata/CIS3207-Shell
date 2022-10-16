#include "library.h"


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

int externalBuiltin(char** input){

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
        puts("i am the child");
        execv(binPath,input);
        printf("%s",strerror(errno));
        exit(1);      //execute the external built in with the path and the certain argument

    }else{//in the parent
        wait(NULL);
        puts("i am the parent");
    
   // wait for the child to finish
    }

    return 0;   
}
//--------------------------------------------------------------------------------//
char *built[] = {"cd","clear","dir","environ","help","echo","puase","quit"};
char *special[] = {">",">>","<","|","&"};
//--------------------------------------------------------------------------------//

// int executing(char** input){
//     /*
//     int PipeFlag = 0;
//     int StdoutFlag = 0;
//     int StdinFlag = 0;
//     int ExternalFlag = 0;
//     int BuiltInFlag = 0;

//     first check if there are speical characters in the input
//         if there are set the the flag to one
//         then check if the first token is external
//             if it is, set the externtalFlag = 1
//         if the first token is equal to one of the builtin
//             set the flag to 1;



    
//     */
//     return 0;
// }

int checking(char**token){
    int i = 0;
    int outputFile = 0;
    int inputFile = 0;
    int AppendFile = 0;
    int currentLocation = 0;
    char* beforeSpeical[] = {NULL};
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
            token[i] = NULL;
            outputFile = 1;
            currentLocation = i;
            //call redirection(with the apporiate flags)
            //function to set the file desciptors
            redirection(token,outputFile,inputFile,AppendFile,currentLocation);
            
        }
        //for appending to another file
        else if(strcmp( token[i], "<<")== 0){
            if (token[i + 1] == NULL){
                puts("invalid argument");
                return 0;
            }
            token[i] = NULL;
            AppendFile = 1;
            currentLocation = i;
            redirection(token,outputFile,inputFile,AppendFile,currentLocation);
            
        }
        //for inputing into another file
        else if(strcmp( token[i], ">")== 0){
            if (token[i + 1] == NULL){
                puts("invalid argument");
                return 0;
            }
            token[i] = NULL;
            inputFile = 1;
            currentLocation = i;
            redirection(token,outputFile,inputFile,AppendFile,currentLocation);
            
        }

        i++;
        //going to have add pipe and background in here
    }
    //next have to check if there are builtins with the special characters
    
        if(strcmp(token[0], "cd") == 0){
            //run the change cd function
            //cd(token);

        }
        else if(strcmp(token[0], "clear") == 0){
            clear();
            
        }
        else if(strcmp(token[0], "dir") == 0){
            dir(token);
            
        }
        else if(strcmp(token[0], "environ") == 0){

            //enviro(token);
    
            
        }
        else if(strcmp(token[0], "help") == 0){
           // help();
            
        }
        else if(strcmp(token[0], "echo") == 0){
            //echo(token);
            
        }
        else if(strcmp(token[0], "pause") == 0){
           // pause();
            
        }
        else if(strcmp(token[0], "quit") == 0){
            quit();
            
        }
        else{
            //run the extranalbuiltin command;
            externalBuiltin(token);

        }
    //set the file descriptors back to normal
    
    dup2(Originalstdou, STDOUT_FILENO);
    dup2(Originalstdin, STDIN_FILENO);
    close( Originalstdou);
    close(Originalstdin);


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
    printf("\n%s\n",getcwd(cwd,sizeof(cwd)));
    //need to add the while(1) to keep the file running
    printf("UserShell>");
    char* inputLine = input();
    char** tokenize = tokenizingInput(inputLine); 

    return 0;   
}


int main(int argc, char** argv, char**envp){

    if(argc == 1){
        interactive(); //can take inputs in from stdin
    }
    if ( argc == 2){
        batch(argv[1]); //execute commands from a file
    }
    if (argc >= 3){
        puts("too many arguments");
        exit(3);
    }
   return 0;
}