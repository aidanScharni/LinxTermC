#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "header.h"

//The redirect function is used to redirect the STDIN and STDOUT according to user input. This function utilizes
//the dup2 command to alter file descriptors to the appropriate locations.

void redirect(char *argv[], int argc) {
    char error_message[30] = "An error has occurred \n";

    for (int i =0 ; i < argc; i++)

        //******   redirect >>   ******
        if (strcmp(argv[i], ">>") == 0) {
            if ((i + 1) < argc && argc >= 3) {

                //The double arrow signifies the redirection of STDOUT is to append the file that is passed.

                int file = open(argv[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0777);

                if (file < -1) {
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    return;
                }

                //The dup2 command makes it possible to redirect the STDOUT to the designated file that is passed.

                int file2 = dup2(file, STDOUT_FILENO);

                if (file2 < -1) {
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    return;
                }
                close(file);
            } else {
                write(STDERR_FILENO, error_message, strlen(error_message));
                return;
            }

            //******   redirect >   ******
        } else if (strcmp(argv[i], ">") == 0) {
            if ((i + 1) < argc && argc >= 3) {

                //The single arrow also redirects STDOUT, but unlike the doubel arrow the output truncates
                //the file that is passed.

                int file = open(argv[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);

                if (file < -1) {
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    return;
                }

                //Very similar to the previous redirection dup2 is utilized to redirect STDOUT to the designated
                //file

                int file2 = dup2(file, STDOUT_FILENO);

                if (file2 < -1) {
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    return;
                }
                close(file);
            } else {
                write(STDERR_FILENO, error_message, strlen(error_message));
                return;
            }

            //******   redirect <   ******
        } else if (strcmp(argv[i], "<") == 0) {
            if ((i + 1) < argc && argc >= 3) {

                //The single arrow to the left now redirects STDIN to come from a designated file. Therefore,
                //we only need to read from the file that is passed.

                int file = open(argv[i + 1], O_RDONLY, 0777);

                if (file < -1) {
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    return;
                }

                close(0);

                //Instead of redirecting STDOUT with dup2 now we redirect STDIN with dup2 from the designated file.

                int file2 = dup2(file, STDIN_FILENO);

                if (file2 < -1) {
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    return;
                }

                close(file);

            } else {
                write(STDERR_FILENO, error_message, strlen(error_message));
                return;
            }
        }
}
