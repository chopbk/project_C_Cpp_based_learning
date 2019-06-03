# Tutorial - Write a Shell in C

## Basic lifetime of a shell

A shell does three main things in its lifetime.

- Initialize: In this step, a typical shell would read and execute its configuration files. These change aspects of the shell’s behavior.
- Interpret: Next, the shell reads commands from stdin (which could be interactive, or a file) and executes them.
- Terminate: After its commands are executed, the shell executes any shutdown commands, frees up any memory, and terminates.

In this shell, just call the looping function and then terrminate, not use any configuration files and not use any shutdown command. 

## Basic loop of a shell
a simple way to handle commands is with three steps:

- Read: Read the command from standard input.
- Parse: Separate the command string into a program and arguments.
- Execute: Run the parsed command.

```

void shell_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = shell_read_line();
    args = shell_split_line(line);
    status = shell_execute(args);

    free(line);
    free(args);
  } while (status);
}

```
Within the loop, we print a prompt, call a function to read a line, call a function to split the line into args, and execute the args. Finally, we free the line and arguments that we created earlier. Note that we’re using a status variable returned by shell_execute() to determine when to exit.