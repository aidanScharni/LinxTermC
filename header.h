void getInput(char *argv[], int inputVar[]);
int builtIn (char *argv[], int argc);
void redirect(char *argv[], int argc);
int checkRedirect(char *argv[], int argc, char *cmdargv[]);
void willPipe(char *argv[], int argc);
void execCmds(char *argv[], int argc, int backGround);
