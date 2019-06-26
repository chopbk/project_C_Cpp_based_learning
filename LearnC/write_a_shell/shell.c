
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


/********************builtin shell command*****************/
/*
  List of builtin commands and function, followed by their corresponding functions.
 */
char *builtin_str[] = {
	"cd",
	"help",
	"exit"
};

int (*builtin_func[]) (char **) = {
	&shell_cd,
	&shell_help,
	&shell_exit
};
/**
 * @Description: This function return the number of builtins
 */
int shell_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}
/**
 * @Description: This function excute cd command
 */
int shell_cd(char * *args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "shell: expected argument to \"cd\"\n");
	}
	else 
	{
		if (chdir(args[1]) != 0)
		{
			perror("lsh");
		}
	}
	return 1;
}
/**
 * @Description: This function excute help command
 */
int shell_help(char **args)
{
  int i;
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < shell_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}
/**
 * @Description: This function excute exit  command
 */
int shell_exit(char **args)
{
  return 0;
}

int shell_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < shell_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return shell_launch(args);
}

		

