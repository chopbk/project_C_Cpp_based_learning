#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void shell_loop(void);
char *shell_read_line(void);
int shell_execute(char **args);