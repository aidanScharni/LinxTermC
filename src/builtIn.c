#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

#include "../headers/header.h"


//The builtIn file is used to check if a command is a builtin function and, if command is builtin, execute accordingly.

extern char **environ;

int builtIn (char *argv[], int argc) {
    char error_message[30] = "An error has occurred \n";

    //******   cd command   ******
    if (strcmp(argv[0], "cd") == 0) {

        //If the argc is set to 1 this means no flags were passed with the cd command and therefore only the
        //current working directory will be returned.

        if (argc == 1) {
            char buffer[1024];
            getcwd(buffer, 1024);
            printf("%s\n", buffer);
        }

        //If a flag is passed, signified by argc being equal to 2, then the current directory will be changed to
        //the passed directory. It is important to note that the PWD environment variable is altered.

        else if (argc == 2) {
            if (chdir(argv[1]) == -1) {
                write(STDERR_FILENO, error_message, strlen(error_message));
            } else {
                char buffer[1024];
                getcwd(buffer, 1024);
                setenv("PWD", buffer, 1);
            }
        } else {
            write(STDERR_FILENO, error_message, strlen(error_message));
        }
        return 1;
    }

    //******   clr command   ******
    if (strcmp(argv[0], "clr") == 0) {
        printf("\e[1;1H\e[2J");
        return 1;
    }

    //******   dir command   ******
    if (strcmp(argv[0], "dir") == 0) {
        if (argc >= 3) {
            write(STDERR_FILENO, error_message, strlen(error_message));
        }

        //If the dir command is passed with exactly one argument then the contents of the directory that was passed
        //is printed on the terminal. This is done by using the dirent struct in a similar fashion to previous lab.

        else if (argc == 2) {
            struct dirent **nameList;

            int n = scandir(argv[1],&nameList,NULL, alphasort);

            if (n == -1) {
                write(STDERR_FILENO, error_message, strlen(error_message));
            } else {
                for (int i =0; i < n; i++) {
                    printf("%s \n", nameList[i]->d_name);
                }
            }
        }

        //If no flags are passed with the dir command then the contents of the current directory are printed.

        else if (argc == 1) {
            struct dirent **nameList;

            char buffer[1024];
            getcwd(buffer, 1024);

            int n = scandir(buffer,&nameList,NULL, alphasort);

            for (int i =0; i < n; i++) {
                printf("%s \n", nameList[i]->d_name);
            }
        }

        return 1;
    }

    //******   environ command   ******
    if (strcmp(argv[0], "environ") == 0) {
        for (int i = 0; environ[i] != NULL; i++) {
            printf("%s\n", environ[i]);
        }
        return 1;
    }

    //******   echo command   ******
    if (strcmp(argv[0], "echo") == 0) {

        //Because the getInput function utilizes the strtok command to parse spaces, tabs, and new line characters
        //the echo command will return following arguments seperated by a single space.

        for (int i = 1; argv[i] != NULL; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
        return 1;
    }

    //******   pause command   ******
    if (strcmp(argv[0], "pause") == 0) {

        //The pause command will stop prompting the user for input until the enter key is hit.

        getchar();
        return 1;
    }

    //******   help command   ******
    if (strcmp(argv[0], "help") == 0) {

        //The help command is the only builtin command that utilizes the fork and execvp functions.
        //Here the more functionality is used to properly open a document in the child process.

        int pid = fork();
        if (pid == 0) {
            char *fileName[] = {"more", "readme_doc.txt", NULL};
            execvp(fileName[0], fileName);
        } else {
            wait(0);
        }
        return 1;
    }

    //******   quit command   ******
    if (strcmp(argv[0], "quit") == 0) {
        exit(0);
    }

    return 0;
}
