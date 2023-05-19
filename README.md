# LinxTermC
A C-based Linux terminal emulation project.

#What I learned
- Experience with process creation, management, and communication between **parent and child processes**.
- **Makefile** creation to automate the compilation and building process. Compile and link shell program and manage dependencies.
- In the context of the shell, handle zombie processes by implementing proper **signal handling**, specifically the SIGCHLD signal. By registering a signal handler for SIGCHLD, the shell can receive notifications about child process termination and properly clean up the zombie processes.
- The core functionality of the shell involves creating child processes to execute user-entered commands. **Forking** is used to create these child processes. 
- Understanding the sequence of forking and **executing, exec()**, new programs helps you correctly set up and execute user commands within the shell.
