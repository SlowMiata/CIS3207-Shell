
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
    char* array[] = {"hello","extra","world","|", "1", "2", "3", NULL};
   // printf("%s",array[0]);
   


        char** input2 = malloc( 100 * sizeof(char*));
        int j = 2;
        int k = 0;
        while(array[j] != NULL){
            input2[k] = array[j];
            j++;
            k++;
        }
        printf("\n[%s] this is before calling piping \n",input2[0]);//the issue is here, its returning NULL

    
    

    return 0;
}

// int main(int argc, char** argv, char**envp) {
//     char* command = "ls";
//     char* argument_list[] = {"ls", "-al", NULL};

//     //char** arugment
//     //argument[0]

//     printf("Before calling execvp()\n");

//     // Calling the execvp() system call
//     int status_code = execvp(argument_list[0], argument_list);

//     if (status_code == -1) {
//         printf("Process did not terminate correctly\n");
//         exit(1);
//     }

//     printf("This line will not be printed if execvp() runs correctly\n");

//     return 0;
// }
