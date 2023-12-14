#include "samd.h"

/**
 *execute_command -takes a command as a parameter
 *
 *@command: The shell command to be executed
 *
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;

	/* fork a child process*/
	pid = fork();

	if (pid < 0)
	{
		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* child process*/
		execlp(command, command, (char *)NULL);
		/*if execlp fails*/
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
		else
		{

			/* parent process*/
			waitpid(pid, &status, 0);

			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			{
				printf("Error: command '%s' not found.\n", command);
			}
		}
}
