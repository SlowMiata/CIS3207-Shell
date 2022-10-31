ReadMe for Project_2: Creating a shell program
Tu Ha
10/31/2022

Purpose:

    The purpose of this project is to create my own linux Shell that have its own builtin functions such as cd, quit, and pause, as well running external commands such as grep and ls. The shell can also handle special characters such as '>' for redirection and '|' for piping.
    The shell itself can either run from batch mode or run in interactive mode.

Project Process:
    First I worked interactive mode. I stored the commands into a function and using another function tokenized everything.
    After that I worked on creating all the builtins and making sure each of them worked individually before connecting it to the rest of my code.
    Then I created a function that would check for the builtin using strcmp and execute the specified function if the token matched. I would later
    spilt the checking function into two functions, one for checking and one for executing since I have to check for special characters.
    The checking function purpose was to see if there were speical characters in the commandline. If there was one, it would set my preset variables to 1 (my flags), meaning the speical character was found. I then created a function for redirection, that would take in the flags and change the file desciptors as needed to. After that was done, I created a function for piping, and using pipe() and fork(), I could execute two commands. Lastly, I worked on getting batch mode working, since batch mode was similar to interactive mode, I just made some adjustments and got batch mode wokring. Many times in my program, I had to change functions around and add more condition statements as I implemented more and more things into my code.

Troubles and errors:
    In the beginning I had troubles with passing my char** tokens. I find working with pointers is very hard to do. My code was working when I hard coded my tokens but not when running it in interactive mode. Eventually, the bugs disappeared, and everthing worked. I also had lots of bugs where the first commands I put into my shell wouldn't run, but after that if I type the commands in again it would run. But I was also able to fix that as well. The only part of the shell that doesn't work is background processing. I believe that I have an idea of how to get it to work but again im having the issues with passing in my tokens in as parameters. I do fork() a child process to run the commands, and then not have the parent call wait, in order to have the background process run. 
    

In-depth explaination of the code:
    myShell.c(main code)
        main()
            In my main, I store the current working directory as well as storing the enviroment strings for later on.
            the main also decides to run interactive mode or batch mode. When calling the program, if there are no additional arguments then the program runs in interactive mode, if there is one argument, then it runs in batch mode.

        Interactive()
            In this function, I call three of my functions()
            input(), which stores the command line as a string
            tokenizingInput() which takes in the string from input() and tokenizes it
            checking() which takes in tokenizingInput() and see if there are special characters

        input()
            using getline, I get the commmands and store them into a string and return the string
        
        tokenizing()
            taking in the string from input(), I use strtok to remove extra white spaces and have it stored into an array of strings and then return that array of strings.
            This array of strings is used in all future functions.

        checking()
            using a while loop and strcmp, this function checks if the tokenized command line has an speical characters, and if it does it raises flags corresponding to the character for later. If there are redirection characters, it calls my rediction function, and if there is a piping function it calls my piping function. It also sets the special characters to NULL, so that my other functions can run properly.

        executing()
            This is where all my builtin get called, using strcmp if the first token matches the name, the function gets called. If nothing matches then my external function gets called.

        externalBuiltin()
            this commands, sets the path the /bin/ and executes the command using execvp() in a child process that I called from fork()
        
    Builtin.c
        cd()
            this function changes the directory using  chdir()
            and also gives the PWD
        
        dir()
            this function lists the files and subdirectories of a specified directory using DIRENT
            This function is similar to Project_0, tucp
        
        echo()
            echo() prints out the comment that the user types into the command line and also remove extra white spaces by simply using prinft().
        
        quit()
            same as the exit command, simply exits the shell using exit()

        help()
            this function opens my readme_doc which is help manual for all the built ins in this program. It uses fork() to execvp 'more' on my readme_doc. The function also include the PWD of the file that the readme_doc is located in, so no matter what directory you are in you can always call help().
        
        pause()
            this pauses the shell until the user hits enter. This was achieved by using getchar()
        
        clear()
            this clears the screen using a speical printf statment "\e[1;1H\e[2J"
    

    Special.c
        redirection()
            this function takes my redicrection flags. If the flags == 1
            open the file as input or output depending one flag, and using dup2() I would change the file desciptors.
            The file descriptors get set back to their original one in my checking() function once everything called, so the user can call new commands.
        
        piping()
            This functions pipe my file descriptors and then also forks twice. The first child is the left side of pipe and is what going to input into the second command. The process first check if it is a command from my builtin function, if it is then it runs taht function. If it is not then it execvp. The second child is for the right side of the pipe. it takes in the left side as an input and execute accordingly to that input.

        
        







