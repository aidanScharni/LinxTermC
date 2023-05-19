SRC_DIR := ../src

myshell: $(SRC_DIR)/builtIn.o $(SRC_DIR)/checkRedirect.o $(SRC_DIR)/redirect.o $(SRC_DIR)/getInput.o $(SRC_DIR)/willPipe.o $(SRC_DIR)/execCmds.o $(SRC_DIR)/main.o
	gcc $(SRC_DIR)/builtIn.o $(SRC_DIR)/checkRedirect.o $(SRC_DIR)/redirect.o $(SRC_DIR)/getInput.o $(SRC_DIR)/willPipe.o $(SRC_DIR)/execCmds.o $(SRC_DIR)/main.o -o myshell

$(SRC_DIR)/checkRedirect.o: $(SRC_DIR)/checkRedirect.c
	gcc -c $(SRC_DIR)/checkRedirect.c -o $(SRC_DIR)/checkRedirect.o

$(SRC_DIR)/main.o: $(SRC_DIR)/main.c
	gcc -c $(SRC_DIR)/main.c -o $(SRC_DIR)/main.o

$(SRC_DIR)/builtIn.o: $(SRC_DIR)/builtIn.c
	gcc -c $(SRC_DIR)/builtIn.c -o $(SRC_DIR)/builtIn.o

$(SRC_DIR)/redirect.o: $(SRC_DIR)/redirect.c
	gcc -c $(SRC_DIR)/redirect.c -o $(SRC_DIR)/redirect.o

$(SRC_DIR)/getInput.o: $(SRC_DIR)/getInput.c
	gcc -c $(SRC_DIR)/getInput.c -o $(SRC_DIR)/getInput.o

$(SRC_DIR)/willPipe.o: $(SRC_DIR)/willPipe.c
	gcc -c $(SRC_DIR)/willPipe.c -o $(SRC_DIR)/willPipe.o

$(SRC_DIR)/execCmds.o: $(SRC_DIR)/execCmds.c
	gcc -c $(SRC_DIR)/execCmds.c -o $(SRC_DIR)/execCmds.o

OBJECTS := $(SRC_DIR)/builtIn.o $(SRC_DIR)/checkRedirect.o $(SRC_DIR)/redirect.o $(SRC_DIR)/getInput.o $(SRC_DIR)/willPipe.o $(SRC_DIR)/execCmds.o $(SRC_DIR)/main.o

myshell: $(OBJECTS)
	gcc $(OBJECTS) -o myshell

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	gcc -c $< -o $@

run: myshell
	./myshell

clean:
	rm $(SRC_DIR)/*.o myshell