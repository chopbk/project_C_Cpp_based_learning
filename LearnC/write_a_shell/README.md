# Tutorial - Write a Shell in C

## Basic lifetime of a shell

A shell does three main things in its lifetime.

- Initialize: In this step, a typical shell would read and execute its configuration files. These change aspects of the shell’s behavior.
- Interpret: Next, the shell reads commands from stdin (which could be interactive, or a file) and executes them.
- Terminate: After its commands are executed, the shell executes any shutdown commands, frees up any memory, and terminates.

In this shell, just call the looping function and then terrminate, not use any configuration files and not use any shutdown command. 
