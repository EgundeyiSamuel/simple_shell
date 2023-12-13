#include "samd.h"

/**
 * exec_command - finds built-ins and commands
 *
 * @shell_data: relevant data(arguments)
 * Return: 1 success.
 */

int exec_command(Shell_data *shell_data)
{
	int (*builtin)(Shell_data *shell_data);

	if (shell_data->args[0] == NULL)
		return (1);
	builtin = getBuiltin(shell_data->args[0]);

	if (builtin != NULL)
		return (builtin(shell_data));

	return (executeExternalCommand(shell_data));
}

/**
 * exit_samd - exits the shell samd
 *
 * @shell_data: data (status)
 * Return: 0 on success.
 */
int exit_samd(Shell_data *shell_data)
{
	unsigned int exitStatus;
	int isDigit;
	int stringLength;
	int isBigNumber;

	if (shellData->args[1] != NULL)
	{
		exitStatus = _atoi(shell_data->args[1]);
		isDigit = _isdigit(shell_data->args[1]);
		stringLength = _strlen(shell_data->args[1]);
		isBigNumber = exitStatus > (unsigned int)INT_MAX;

		if (!isDigit || stringLength > 10 || isBigNumber)
		{
			reportError(shell_data, 2);
			shell_data->status = 2;
			return (1);
		}

		shell_data->status = (exitStatus % 256);
	}

	return (0);
}
