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






int cd(char* input);
int help();
int pause();
int quit();
int echo(char* input);
int clear();
int dir(char* input);
int environ(char** input);
