#include <string.h>
#include <dirent.h>

#include "header.h"

//The checkRedirect file is used to see if redirection is to be implemented based upon user input. If redirection
//of STDIN or STDOUT is seen the value of how many arguments before first redirect is returned
//. If piping is supposed to be executed then the value -1 is returned. Otherwise, 0 is
//returned to signify no redirection is necessary.

int checkRedirect(char *argv[], int argc, char *cmdargv[]) {
    int hasRedirect = 0;
    int counter = 0;

    for (int i = 0; i < argc; i++) {

        //If redirect is seen within the arguments passed by the user then the arguments before the redirect are
        //recorded and stored in a new char *[] called cmdargv. This is done to separate the commands of redirection
        //to be executed individually.

        if (strcmp(argv[i], ">") == 0 || strcmp(argv[i], ">>") == 0 || strcmp(argv[i], "<") == 0) {
            if (argv[i-1] != NULL && argv[i+1] != NULL && argc >= 3) {
                for(int y = 0; y < counter; y++) {
                    cmdargv[y] = argv[y];
                }
                hasRedirect = 1;
            } else {
              break;
            }
        }

        //If the piping character is passed within user input then the value of -1 is passed to signify and handle
        //this type of redirection later down the line.

        else if (strcmp(argv[i], "|") == 0) {
            if (argv[i-1] != NULL && argv[i+1] != NULL && argc >= 3) {
                hasRedirect = -1;
            } else {
                break;
            }
        }
        if (hasRedirect != 1) {
            counter++;
        }
    }

    //Counter signifies the argument count for redirection to the left of the redirection character.

    if (hasRedirect == 1) {
        return counter;
    } else if (hasRedirect == -1){
       return hasRedirect;
    } else {
        return 0;
    }
}