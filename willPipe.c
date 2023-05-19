#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>

#include "header.h"

//The willPipe function not only handles the redirects for proper pipping, but also handles the execution
//of those commands. The pipe redirection is designed as the output of the command to the left of the pipe
//becomes the input for the command to the right of the pipe.

void willPipe(char *argv[], int argc) {
    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);

    for (int i = 0; i < argc; i++) {
        if  (strcmp(argv[i], "|") == 0) {
            argv[i] = NULL;
            int fd[2];
            if (pipe(fd) == -1) {
                return;
            }

            int pid1 = fork();

            if  (pid1 < 0) {
                return;
            }

            //In the first fork the left hand side of teh pipe is handled. This is done by redirecting the
            //STDIN of the command to the read end of the pipe(fd[0]).

            if (pid1 == 0) {
                char *tempArgv[100];
                int z = 0;
                for (int y = i + 1; y < argc; y++) {
                    tempArgv[z] = argv[y];
                    z += 1;
                }

                tempArgv[z] = NULL;

                close(fd[1]);

                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);

                int builtInCommand = builtIn(tempArgv, z -1);

                if (builtInCommand == 0) {
                    execvp(tempArgv[0], tempArgv);
                }
            }

            int pid2 = fork();

            if(pid2 < 0) {
                return;
            }

            //In the second fork the left hand side of the pipe is handled. This is done by redirecting the
            //STDOUT of the command to the write end of the pipe(fd[1]).

            if (pid2 == 0) {
                char *tempArgv2[100];
                int b = 0;
                for (int a = 0; a < i; a++) {
                    tempArgv2[b] = argv[a];
                    b += 1;
                }

                tempArgv2[b] = NULL;

                close(fd[0]);

                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);

                int builtInCommand = builtIn(tempArgv2, b - 1);

                if (builtInCommand == 0) {
                    execvp(tempArgv2[0], tempArgv2);
                }
            }

            //In the end both ends of the pipe are closed and the file descriptors for STDIN and STDOUT are
            //set back to their default values.

            close(fd[0]);
            close(fd[1]);

            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);

            dup2(saved_stdout, STDOUT_FILENO);
            dup2(saved_stdin,STDIN_FILENO);

            close(saved_stdout);
            close(saved_stdin);
        }
    }
}