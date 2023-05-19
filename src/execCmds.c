#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

#include "../headers/header.h"

//execCmds is a very important funciton that is responsible for the execution of commands passed by the user.
//Most of the execution of commands is abstracted into other files but most the execution of external commands
//including ls, cat, grep, and others is done here with the help of execvp and fork.

void execCmds(char *argv[], int argc, int backGround) {
    char error_message[30] = "An error has occurred \n";
    if (argv[0] != NULL) {
        char *cmdargv[100];
        int cmdargc = 0;
        int builtInCommand = 0;
        cmdargc = checkRedirect(argv, argc, cmdargv);

        //If cmdargc is greater than 0 this signifies that redirection had been passed. Therefore, before we
        //execute the builtin commands we must redirect STDIN and STDOUT according to the redirection
        //command that was passed.

        if (cmdargc > 0) {
            int saved_stdout = dup(STDOUT_FILENO);
            int saved_stdin = dup(STDIN_FILENO);
            redirect(argv, argc);
            builtInCommand = builtIn(cmdargv, cmdargc);
            dup2(saved_stdout, STDOUT_FILENO);
            dup2(saved_stdin, STDIN_FILENO);
            close(saved_stdout);
            close(saved_stdin);
        }

        //If the cmdargc is equal to -1 then this signifies that the pipe command was passed by the user. Therefore,
        //the willPipe command is called which will not properly redirect input and output for pipe but also execute
        //the commands

        else if (cmdargc == -1) {
            willPipe(argv, argc);
        }

        //If the cmdargc is equal to 0 that signifies that no redirection command was passed and that the program can
        //simply execute the builtin commands with STDIN and STDOUT.

        else {
            builtInCommand = builtIn(argv, argc);
        }

        //If the commands passed were not recognized as builtin commands then the execvp commands will be used
        //to execute external functionality.

        if (builtInCommand == 0) {
            int cpid;
            cpid = fork();
            if (cpid == 0) {
                redirect(argv, argc);
                if (cmdargc > 0) {

                    //If redirection was implemented with the use of an external command the execution of the argv
                    //must be seperated into individual commands.

                    cmdargv[cmdargc] = NULL;
                    if (execvp(cmdargv[0], cmdargv) < 0) {
                        write(STDERR_FILENO, error_message, strlen(error_message));
                    }
                } else {
                    if (execvp(argv[0], argv) < 0) {
                        write(STDERR_FILENO, error_message, strlen(error_message));
                    }
                }
            }
            else {
                waitpid(cpid, NULL, 0);
            }
        }
    }
}
