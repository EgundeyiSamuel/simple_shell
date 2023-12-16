/**
 * error_code - invokes the appropriate error function based on the error code
 * @data: data structure holding arguments
 * @code: error value
 * Return: error value
 */
int error_code(shell_data *data, int code)
{
	char *message = NULL;

	switch (code)
	{
	case -1:
	message = handleEnvError(data);
	break;
	case 126:
	message = handlePathError126(data);
	break;
	case 127:
	message = handleCmdNotFoundError(data);
	break;
	case 2:

	if (_strcmp("exit", data->arguments[0]) == 0)
	message = displayExitShellMessage(data);
	else if (_strcmp("cd", data->arguments[0]) == 0)
	message = handleError(data);
	break;
	}

	if (message)
	{
	write(STDERR_FILENO, message, _strlen(message));
	free(message);
	}

	data->statusCode = code;
	return (code);
}

/**
 * findBuiltIn - retrieves the function pointer
 * corresponding to the built-in command
 * @cmd: command string
 * Return: function pointer to the built-in command, or NULL if not found
 */
int (*findBuiltIn(char *cmd))(shell_data *) {
	built_in builtIns[] = {
		{ "env", executeEnv },
		{ "exit", exitShell },
		{ "setenv", setEnvironmentVariable },
		{ "unsetenv", deleteEnvironmentVariable },
		{ "cd", changeDirectory },
		{ "help", getHelp },
		{ NULL, NULL }
	};

	int i;

	for (i = 0; builtIns[i].name; i++)
	{
		if (_strcmp(builtIns[i].name, cmd) == 0)
			return (builtIns[i].functionPointer);
	}

	return (NULL);
}
