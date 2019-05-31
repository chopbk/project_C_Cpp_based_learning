
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