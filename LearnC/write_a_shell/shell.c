
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

/**
 * @Description: This function perform a loop with three steps
 *  - Read: Read the command from standard input
 *  - Parse: Separate the command string into a program and arguments.
 *  - Execute: Run the parsed command.
 */
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
/**
 * @Description: This function read character from user and return a buffer
 */
char * shell_read_line(void)
{
  int bufsize = SHELL_RL_BUFSIZE;
  int position = 0;
  char *buffer = malooc(sizeof(char) * bufsize);
  int c;

  if(!buffer)
  {
    fprintf(stderr, "shell: allocation error\n");
    exit(EXIT_FAILURE);
  }
  while(1) {
    //read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return
    if(c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    //If we have exeeded the buffer, reallocate.
    if(position >= bufsize){
      bufsize += SHELL_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
        if(!buffer)
        {
          fprintf(stderr, "shell: allocation error\n");
          exit(EXIT_FAILURE);
        }
    }
  }
}

/**
 * @Description: This function Parsing the line command
 */
char **lsh_split_line(char *line)
{
  int bufsize = SHELL_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize *sizeof(char*));
  char *token;
  if(!tokens) {
    fprintf(stderr, "allocation error\n");
    exit(EXIT_FAILURE);
  }
  token = strstok(line, SHELL_TOK_DELIM);
  while(token != NULL)
  {
    tokens[position++] = token;
    if(position > bufsize)
    {
      bufsize += SHELL_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if(!tokens) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, SHELL_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;

}
