#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*******************DEFINE MACRO****************************/
#define SHELL_RL_BUFSIZE 1024
#define SHELL_TOK_BUFSIZE 64
#define SHELL_TOK_DELIM " \t\r\n\a"
/*******************END****************************/

/*******************DEFINE FUNCTION****************************/
void shell_loop(void);
char *shell_read_line(void);
int shell_execute(char **args);
char **lsh_split_line(char *line);
/*******************END****************************/