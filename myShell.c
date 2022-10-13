#include "library.h"


//for taking in the input in interactive mode
char* input(){
    char* buffer;
    size_t size = 64;

    
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

/*int externalBuiltin(char* input){

    char* bin = "/bin/";


    pid_t pid = fork();

    if(pid == 0){// in the child
       // execv();
       //execute the external built in with the path and the certain argument

    }else{//in the parent
    wait for the child to finish

    }

    
    return 0;
}*/

char *built[] = {"cd","clear","dir","environment","help","echo","puase","quit"};
char *special[] = {">",">>","<","|","&"};

int checking(char**token){//checks for built-in and for special commands
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


int batch(char* input){

    FILE* file;
    file = fopen(input,"rb");
    char buffer[100];
    

    return 0;

}

char** tokenize;
int interactive(){
    char cwd[1000];
    printf("\n%s\n",getcwd(cwd,sizeof(cwd)));
    return 0;
    
    printf("UserShell>");
    char* inputLine = input();
    tokenize = tokenizingInput(inputLine);    
    
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