#include "library.h"



//for taking in the input in interactive mode
char* input(){
    char* buffer;
    size_t size = 32;
    size_t amountChar;
    buffer = (char* )malloc(size);
   amountChar =  getline(&buffer,&size, stdin);

    return buffer;
}
//tokenizing the input
char** tokenizingInput(char* input){
    char** token;
    char* buffer;
    size_t size = 32;
    int i = 0;
    token = (char**)malloc(size);
    buffer = strtok(input," ");

    while(buffer != NULL){
        token[i] = buffer;
        i++;
    }

    if ( i >= size){
        token = realloc(token,size * 2);
    }
    buffer = strtok(NULL, " ");
    token[i] = NULL;
    printf("%s",token[10]);

    return token;
}






int batch(){
    return 0;

}

int interactive(){
tokenizingInput(input());



    return 0;
}


int main(int argc, char** argv){

    if(argc == 1){
        interactive();
    }
    if ( argc == 2){
        batch();
    }
    if (argc >= 3){
        puts("too many arguments");
        exit(3);
    }
    
   

    
   return 0;
}