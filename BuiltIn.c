#include "library.h"

//changes the directory
int cd(char** input){ //working , have to do full path, like ../Project_0 to change dir

    if(chdir(input[1]) == -1){
        printf("%s",strerror(errno));
    }

    char cwd[1000];
    printf("\n%s\n",getcwd(cwd,sizeof(cwd)));
    return 0;
}


//Not working the execute function
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
        puts("Not working");
        puts("this directory doesn't exist");

        return -1; 
    }
    struct dirent* directory;
    //reads what is in the directory
    directory = readdir(d);
    
    //while the directory is not empty
    while(directory != NULL){
        printf("%s\t\t",directory->d_name);
        //prints the directory

    
        directory = readdir(d); 
    }
    closedir(d);
    puts(" ");

    return 0;
}

//prints out comment
int echo(char** input){ //working but  //doesnt work the first time?????
    int i = 1;
    while(input[i] != NULL){
        printf("%s ",input[i]);
        i++;
    }
    puts("builtin echo");
    return 0;
}
//prints the envrionment strings
int environ(char** input){ //working
    int i = 0;
    while(input[i] != NULL){
        
        //printf("%s:%s\n",(input[i]),getenv(input[i]));
        printf("%s\n",input[i]);
        i++;
    }

    return 0;
}
//quits out of the shell
int quit(){//working
    exit(1);
}




//uses the more builtin to open the help folder
int help(){//working

    char* bin = "/bin/";
    char binPath[1000];
    strcpy(binPath,bin);
    char*help[] = {"more", "help.txt",NULL};
    strcat(binPath,help[0]);
    
    pid_t pid = fork();
    if(pid == -1){
        printf("%s",strerror(errno));
        return -1;
    }
    
    if(pid == 0){// in the child
        //puts("i am the child");
        puts("working up till this point");
        execv(binPath,help);
        printf("%s",strerror(errno));
        exit(1);      //execute the external built in with the path and the certain argument

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



