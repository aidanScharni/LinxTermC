#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "header.h"

//The getInput function is used to parse information passed from the user. The commands passed by the user
//are stored in a char *[] that trails with a NULL value. Background processes are signified by either 1 or 2. If
//a one is returned than there are & values within the user input. Although, if a value of 2 is returned then
//the process ends in an &.

void getInput(char *argv[], int inputVar[]) {

    int backGround = 0, i = 0;
    size_t n = 1024;
    char *buff = malloc(sizeof(char) * n);

    getline(&buff, &n, stdin);

    //The stroke function is used to separate each individual value passed by the user.

    char *argument = strtok(buff, " \t\n");

    while (argument != NULL) {

        //The first if statement is used to replace all instances of "&" with NULL. This was done as part of the
        //attempt to implement background processes. The idea being that each section of code before a & could
        //be executed indecently. Also identifies that background command was passed.

        if (strcmp(argument, "&") == 0) {
            argv[i++] = NULL;
            backGround = 1;
        }

        //Each argument is stored in teh argv array.

        else {
        argv[i++] = argument;
        }

        argument = strtok(NULL, " \t\n");

        //This if statement was also implemented for background execution. In replacing all the & values with null
        //and having the argv array by default end in NULL it would be hard to tell if an & was passed at the end of
        //the command. Therefore, the background value of 2 signifies that there may be background signals within the
        //command, the command is ended by an &.

        if (argument == NULL && argv[i - 1] == NULL) {
            backGround = 2;
        }
    }

    //Ensures that even if an & is not passed the commands stored in argv will end with a NULL value.

    if (backGround == 0) {
        argv[i] = NULL;
    }

    //Store both the argc and background value to be passed to main.

    inputVar[0] = i;
    inputVar[1] = backGround;
}
