#include "shell.h"

/**
* tokenize - tokenize a string into an array of strings
* @data: shell data struct
* Return: void
*/

void tokenize(shell_data *data)
{
	const char *delim = " \t\n";
	char *token;

	data->num_args = 0;
	token = strtok(data->line, delim);

	while (token != NULL && data->num_args < MAX_ARGS - 1)
	{
		data->args[data->num_args++] = token;
		token = strtok(NULL, delim);
	}

	data->args[data->num_args] = NULL;
}
