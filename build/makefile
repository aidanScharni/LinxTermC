myshell: builtIn.c checkRedirect.c redirect.c getInput.c main.c willPipe.c execCmds.c
	gcc builtIn.c checkRedirect.c redirect.c getInput.c willPipe.c execCmds.c -o myshell main.c

checkRedirect: checkRedirect.c
	gcc -c checkRedirect.c

main: main.c
	gcc -c main.c

builtIn: builtIn.c
	gcc -c builtIn.c

redirect: redirect.c
	gcc -c redirect.c

getInput: getInput.c
	gcc -c getInput.c

willPipe: willPipe.c
	gcc -c willPipe.c

execCmds: execCmds.c
	gcc -c execCmds.c

clean:
	rm  *.o myshell
