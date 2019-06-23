
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
  char *line = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for use
  /**
   * Function getline() reads an entire line from stream, storing the address of
   * the buffer containing the text into *lineptr.  The buffer is null-
   * terminated and includes the newline character, if one was found
  */
  getline(&line, &bufsize, stdin);
  return line;
}

/**
 * @Description: This function Parsing the line command
 */
char **shell_split_line(char *line)
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

/**
 * @Description: This function launch a shell
 */
int shell_lauch(char **args)
{
	pid_t pid, wpid;
	int status;
	pid = fork();
	if(pid == 0){
		//child process
		if(execvp(args[0], args) == -1){
			perror("shell error");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		// Error forking
		perror("shell error");
	} else {
		// Parrent process
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}


