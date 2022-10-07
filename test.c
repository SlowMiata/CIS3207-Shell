#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nDir: %s\n", cwd);
}

void main(void){
    int i = 0;
    
    while( i < 2){


        printf("user> ");

        printDir();
        i++;
    }
}



