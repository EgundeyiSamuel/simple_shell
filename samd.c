#include "ssh.h"

/**
 *main - prompt display function
 *
 * Return: Returns (0)
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
	/* Displaying the prompts*/
	printf("(^^) ");

	/* Read the command from the user*/
	if (fgets(command, sizeof(command), stdin) == NULL)
	{
		/* Handling end of file condition (Ctrl+D)*/
		printf("\nExiting SAMD shell. Goodbye!\n");
	break;
	}
	/* Remove the newline character*/
	command[strcspn(command, "\n")] = '\0';

	/* Execute the command*/
	execute_command(command);
	}

	return (0);
}
