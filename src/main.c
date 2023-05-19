#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#include "../headers/header.h"

//The main file is split into two sections. The first section handles batch mode and the second handles standard user
//mode. In both modes commands are parsed and executed accordingly. Execution depends upon weather commands are
//builtin, redirection is used, piping is used, and if the command is to be run in the background.

int main(int cmdArgc, char *argumentArr[]) {
    int argc = 0;
    char *argv[1024];

    //Set environment variables.

    setenv("PATH", "/bin/", 1);
    char buffer[1024];
    getcwd(buffer, 1024);
    strcat(buffer, "/myshell");
    setenv("SHELL", buffer, 1);

    //******   batch mode   ******
    if (cmdArgc == 2) {
        /*
        FILE *batch; // read pointer
        char *line = calloc (80, sizeof (char));
        char c;
        int backGround = 0;
        int i=0;
        int y = 0;

        batch = fopen(argumentArr[1], "r"); // open batchfile


        do {
            c = fgetc(batch);  // read file 1 char at a time until '\n' or EOF
            if (c == '\n') {
                //line[i] = NULL;
                y++;
            } else {
                line[i] = c;
            }
            i++;
        }while (c != EOF);

        printf("%s", line);

        fclose(batch);

        char *token = strtok(line, " \n\t");

        while(y > 0) {
            while (token != NULL){
                if (strcmp(token, "\n") == 0) {
                    argc++;
                    argv[argc] = NULL;
                }else {
                    argc++;
                    argv[argc] = token;
                }
                token = strtok(NULL, " \n\t");
            }
            execCmds(argv,argc,backGround);
            y--;
        }
*/

        FILE *batch;

        size_t n = 1024;
        char *buff = malloc(sizeof(char) * n);

        int backGround = 0;

        //First the file that was passed must be opened and checked to ensure that it does exist.

        batch = fopen(argumentArr[1], "r");

        if (batch == NULL) {
            printf("Please enter a valid text file to read from.\n");
            exit(1);
        }

        //Once in bash mode with a valid file, each line within the file is read and parsed at a time.

        while ((getline(&buff, &n, batch)) != -1) {
            int i = 0;

            char *argument = strtok(buff, " \n\t");

            while (argument != NULL) {
                argv[i++] = argument;
                argument = strtok(NULL, " \n\t");
            }

            argv[i] = NULL;
            argc = i;

            dup2(0, STDIN_FILENO);
            dup2(1, STDOUT_FILENO);

            execCmds(argv, argc, backGround);
            /*
            int cpid = fork();
            if (cpid == 0) {
                fclose(batch);
                execCmds(argv, argc, backGround);
                exit(0);
            } else {
                waitpid(cpid, NULL, 0);
            }
             */

            //After each line is parsed the line can be directly executed. This mode of execution treats
            //each line within the batch file as its own user input.

        }

        //******   user mode    ******
    } else if (cmdArgc == 1) {

        //Within the standard mode the user will continuously be prompted to input commands.

        while (1) {
            int backGround = 0;
            int inputVar[2];

            printf("%s myshell> ", getcwd(buffer, 1024));

            //The getInput function is utilized for parsing the input by the user. The commands passed by the
            //user are stored within a char *[] with a trailing NULL value.

            getInput(argv, inputVar);

            //The getInput function also returns values for the argc and a flag to determine if the commands
            //should be run in the background.

            backGround = inputVar[1];
            argc = inputVar[0];

            //If the not part of the command passed by the user is to be run by the user, that is no "&" value was
            //passed.

            if (backGround == 0) {
            execCmds(argv, argc, backGround);
            }

            //Otherwise if an "&" value was passed the program would execute any commands before each "&"
            //in the background.

            else {
                char *bgargv[100];
                int bgargc;
                int i = 0;
                int y = 0;
                while (i < argc) {
                    if (argv[i] != NULL) {
                        bgargv[y] = argv[i];
                        y++;
                        i++;
                    } else if (argv[i] == NULL && (argv[i + 1] != NULL || backGround == 1)) {
                        bgargv[y] = argv[i];
                        bgargc = y;
                        y = 0;

                        int cpid = fork();
                        if (cpid == 0) {
                            setpgid(0,0);
                            execCmds(bgargv, bgargc, backGround);
                            exit(0);
                        }
                        i++;
                    }  else {
                        bgargv[y] = argv[i];
                        bgargc = y;
                        y = 0;

                        execCmds(bgargv, bgargc, backGround);
                    }
                }
            }
        }
    }
}



