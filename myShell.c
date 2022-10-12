#include "library.h"


//for taking in the input in interactive mode
char* input(){
    char* buffer;
    size_t size = 32;

    
    buffer = (char* )malloc(size);
    getline(&buffer,&size, stdin); //stores what is inputted into buffer
    int length = strlen(buffer);
    if (buffer[length - 1] == '\n'){
        buffer[length - 1] = '\0';
    } 
    return buffer;
}



//tokenizing the input
char** tokenizingInput(char* input){
    char* token[] = {NULL};
    char ** t = token;
    char* buffer;
    size_t size = 32;
    int i = 0;
    t = (char**)malloc(size);
    buffer = strtok(input," "); //remove the extra spaces
    while(buffer != NULL){//add the tokenize strings into an array of pointers
        t[i] = buffer;
        buffer = strtok(NULL, " ");
        i++;
    }
    if ( i >= size){//increase the size of the array
        t = realloc(t,size * 2);
    }
    
    t[i] = NULL;
    printf("%s\n",t[0]);

    return t; //token now has an array of commands
}

// int externalBuiltin(char* input){

//     char* bin = "/bin/";


//     pid_t pid = fork();

//     if(pid == 0){
//        // execv();

//     }


    
//     return 0;
// }

char *built[] = {"cd","clear","dir","environment","help","echo","puase","quit"};
char *special = {">",">>","<","|","&"};

int checking(char**token){
    int j;
    while(token !=NULL){
        for(int i = 0; i < 5; i++){
        if(strcmp(token[0],special[i])== 0){
            puts("please add an argument beforehand");
            exit(1);        
        }
        }

        for(int i = 0; i < 8; i++){
            

            if(strcmp(token[j],built[i])==0){

                
            }


        }
        j++;
           

    }
    return 0;
}




int batch(){

    return 0;

}

char** tokenize;
int interactive(){
    printf("UserShell>");
    char* inputLine = input();
    tokenize = tokenizingInput(inputLine);
    return 0;
}


int main(int argc, char** argv){

    if(argc == 1){
        interactive(); //can take inputs in from stdin
    }
    if ( argc == 2){
        batch(); //execute commands from a file
    }
    if (argc >= 3){
        puts("too many arguments");
        exit(3);
    }
    
   

    
   return 0;
}