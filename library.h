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


//builtin
int cd(char** input);
int help();
int pause();
int quit();
int echo(char** input);
int clear();
int dir(char** input);
int environ(char** input);

//executing
int externalBuiltin(char** input);
int executing(char** token);
int interactive();

//specials
int redirection(char** input, int ReOuput, int ReInput, int ReAppend, int currentLocation);
int piping(char** input, char** input2);
int background(char** input);