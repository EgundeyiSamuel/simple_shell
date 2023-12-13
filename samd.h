#ifndef SAMD_H
#define SAMD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <limits.h>
#include <libgen.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/* ##_______ command prototype ________## */
void execute_command(char *command);

/**/
  typedef struct {
	  char** args;
	  int status;
}shell_data;

/*to change directory */
char* _strdup(const char *str);
void set_env_var(const char *name, const char *value, shell_data *shell_data);
void error_code(shell_data *shell_data, int code);
void cd_pd(shell_data *shell_data);

#endif
