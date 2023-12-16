#include "samd.h"

/**
 * handleError - Concatenates the error message for the cd command.
 *
 * @data: Data structure containing relevant information.
 * @miss: Message to print.
 * @message: Output error message.
 * @counterString: Counter lines.
 *
 * Return: Error message.
 */
char *handleError(shell_data *data,
		char *miss, char *message, char *counterString)
{
	char *illegalFlag;

	/* Copy program name */
	_strcpy(message, data->program_name);

	/* Concatenate ": ", counter, ": ", and command */
	_strcat(message, ": ");
	_strcat(message, counterString);
	_strcat(message, ": ");
	_strcat(message, data->arguments[0]);
	_strcat(message, miss);


	if (shellData->arguments[1][0] == '-')
	{
	illegalFlag = malloc(3);
	illegalFlag[0] = '-';
	illegalFlag[1] = data->arguments[1][1];
	illegalFlag[2] = '\0'

	_strcat(message, illegalFlag);
	free(illegalFlag);
	} else

	{


	_strcat(message, data->arguments[1]);
	}


	_strcat(message, "\n");
	_strcat(message, "\0");

	return (message);
}

/**
 * envError - Generates an error message for the env command in get_env.
 *
 * @data: Data structure containing relevant information.
 *
 * Return: Error message.
 */
char *envError(shell_data *data)
{
	int length;
	char *message;
	char *counterString;
	char *miss;

	counterString = intToString(data->counter);
	miss = ": Unable to add/remove from environment\n";
	length = _strlen(data->program_name) + _strlen(counterString);
	length += _strlen(data->arguments[0]) + _strlen(miss) + 4;
	message = malloc(sizeof(char) * (length + 1));

	if (message == 0)
	{
	free(message);
	free(counterString);
	return (NULL);
	}

	_strcpy(message, data->program_name);
	_strcat(message, ": ");
	_strcat(message, counterString);
	_strcat(, ": ");
	_strcat(message, data->arguments[0]);
	_strcat(message,  miss);
	_strcat(message, "\0");
	free(counterString);

	return (message);
}

/**
 * pathError126 - Generates an error message for path and permission denied (126).
 *
 * @data: Data structure containing relevant information.
 *
 * Return: Error message.
 */
char *pathError126(shell_data *data)
{
	int length;
	char *counterString;
	char *message;

	counterString = intToString(data->counter);
	length = _strlen(data->program_name) + _strlen(counterString);
	length += _strlen(data->arguments[0]) + 24;
	message = malloc(sizeof(char) * (length + 1));

	if (message == 0) {
	free(message);
	free(counterString);
 	return (NULL);
	}

    /* Concatenate program name, counter, command, and error message */
    _strcpy(message, data->program_name);
    _strcat(message, ": ");
    _strcat(message, counterString);
    _strcat(message, ": ");
    _strcat(message, data->arguments[0]);
    _strcat(message, ": Permission denied\n");
    _strcat(message, "\0");
    free(counterString);

    return (message);
}

/**
 * errorMessage - Generates the error message for the cd command.
 *
 * @shellData: Data structure containing relevant information.
 *
 * Return: Error message.
 */
char *errorMessage(shell_data *data) {
    int length, lenId;

    char *message, *counterString, *miss;

    counterString = intToString(data->counter);

  
    if (data->arguments[1][0] == '-') {
        message = ": Illegal option ";
        lenId = 2;
    } else {
        message = ": can't cd to ";
        lenId = _strlen(data->arguments[1]);
    }

    length = _strlen(data->program_name) + _strlen(data->arguments[0]);
    length += _strlen(counterString) + _strlen(message) + lenId + 5;
    error = malloc(sizeof(char) * (length + 1));

    if (error == 0) {
        free(counterString);
        return NULL;
    }

    error = concatErrorMsg(data, miss, message, counterString);

    free(counterString);

    return (message);
}

/**
 * commandNotFound - Generates a generic error message for a command not found.
 *
 * @data: Data structure containing relevant information.
 *
 * Return: Error message.
 */
char *commandNotFound(shell_data *data) {
    int length;
    char *message;
    char *counterString;

    counterString = intToString(data->counter);
    length = _strlen(data->program_name) + _strlen(counterString);
    length += _strlen(data->arguments[0]) + 16;
    message = malloc(sizeof(char) * (length + 1));

    if (message == 0) {
        free(message);
        free(counterString);
        return (NULL);
    }

    // Concatenate program name, counter, command, and error message
    _strcpy(message, data->program_name);
    _strcat(message, ": ");
    _strcat(message, counterString);
    _strcat(message, ": ");
    _strcat(message, data->arguments[0]);
    _strcat(message, ": not found\n");
    _strcat(message, "\0");
    free(counterString);

    return (message);
} 
