#ifndef SAMD_H
#define SAMD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/* ##_______ command prototype ________## */
void execute_command(char *command);


#endif
