#include "library.h"
extern char* originalDirect;

//changes the directory
int cd(char** input){ //working  have to do full path, like ../Project_0 to change dir
    if(input[1] != NULL){
        if(chdir(input[1]) == -1){
        puts("invalid directory");
        }
    }
    
    //setenv(PWD,cwd,1)
    char cwd[1000];
    printf("PWD:%s\n",getcwd(cwd,sizeof(cwd)));
    setenv("PWD",cwd,1);
    return 0;
}

int dir(char** input){//working , have to do full path, like ./../etc to get the directory 
    //if no arugment is passed, prints the current directory
   
    DIR* d;
    if(input[1] == NULL){
        d = opendir("./");
    }
    else{
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
    closedir(d);
    puts(" ");

    return 0;
}

//prints out comment
int echo(char** input){ //working
    int i = 1;
    while(input[i] != NULL){
        printf("%s ",input[i]);
        i++;
    }
    puts(" ");
    return 0;
}
//prints the envrionment strings
int environ(char** input){ //working
    int i = 0;
    while(input[i] != NULL){
        
        printf("%s\n",input[i]);
        i++;
    }

    return 0;
}
//quits out of the shell
int quit(){//working
    puts("leaving MyShell");
    exit(1);
}

//uses the more builtin to open the help folder
int help(){//working
    char helpFile[1000];
    strcpy(helpFile,originalDirect);
    strcat(helpFile,"/readme_doc");

    char* bin = "/bin/";
    char binPath[1000];
    strcpy(binPath,bin);
    char*help[] = {"more", helpFile ,NULL};
    strcat(binPath,help[0]);
    
    pid_t pid = fork();
    if(pid == -1){
        printf("%s",strerror(errno));
        return -1;
    }
    if(pid == 0){// in the child
        execv(binPath,help);
        printf("%s",strerror(errno));
        exit(1);   

    }else
    {//in the parent
        wait(NULL);
        // wait for the child to finish
    }
    return 0;
}
//pauses the shell
int pause(){ //working

    while ( getchar() !='\n'){
        
    }
    return 0;
}
//clears the terminal screen   
int clear(){
    printf("\e[1;1H\e[2J");
    return 0;
}



