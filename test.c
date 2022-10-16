#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int redirection(char** input, int ReOuput, int ReInput, int ReAppend, int currentLocation);
int externalBuiltin(char** input);




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
int clear(){
    printf("\e[1;1H\e[2J");
    return 0;
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
    puts(" ");
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

int redirection(char** input, int ReOuput, int ReInput, int ReAppend, int currentLocation){



    

    
    int OutputFile;
    int InputFile;

    //for >
    if(ReOuput == 1){
        printf("%s",input[currentLocation+1]);
        input[currentLocation] = NULL;
        OutputFile = open(input[currentLocation+1],O_WRONLY | O_CREAT | O_TRUNC,0777);
        puts("this is working");
        printf("%s",input[currentLocation+1]);
        puts("is it working now?");
        dup2(OutputFile,STDOUT_FILENO);
    }
    //for >>
    else if(ReAppend == 1){
        OutputFile = open(input[currentLocation+1],O_WRONLY | O_CREAT | O_APPEND,0777);
        dup2(OutputFile,STDOUT_FILENO);
        
    }
    //for <
    else if(ReInput== 1){
        InputFile = open(input[currentLocation+1],O_RDONLY, 0777);
        dup2(InputFile,STDOUT_FILENO);

    }

    return 0;
}



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
           // token[i] == NULL;
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


   



int main(int argc, char **argv, char** envp){

    char *built[] = {"cd","clear","dir","environment","help","echo","puase","quit", NULL};
    char *special[] = {">",">>","<","|","&"};
    char *test[] = {"dir",".vscode"};
    // printf("%d",(&special)[1]- special);
    // printf("%d",sizeof(built)/sizeof(built[0]));

    //environt(envp);
    //pause();

    //quit();
    //puts("hello world");
    //dir(test);
    //echo(built);
    int i = 0;
    char cwd[1000];
    printf("\n%s\n",getcwd(cwd,sizeof(cwd)));
    //need to add the while(1) to keep the file running
    //while(1){
        printf("UserShell>");
        char* inputLine = input();
        printf("%s",inputLine);
        char** tokenize = tokenizingInput(inputLine); 
        printf("%s",tokenize[2]);
        //checking(tokenize);

    //}
    
    
    
    return 0;
}
