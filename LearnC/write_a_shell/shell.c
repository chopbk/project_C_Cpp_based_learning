
/***************************************************************************//**
  @file         shell.c
  @author       Tamnd12
  @date         31 May 2019
  *******************************************************************************/
#include "shell.h"

int void main(int argc,char **argc)
{
    // Load config files, if any.

    //run command loop
    shell_loop();

    //perform any shutdown/cleanup
    return EXIT_SUCCESS;
}

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
        free(agrs);
    } while(status);
}