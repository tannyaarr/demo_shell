#include "shell.h"

/**
 * _getline - gets line from stream
 * @data: shell data
 * Return: number of characters read
 */

ssize_t _getline(shell_data *data)
{
	char input[READ_BUF_SIZE];
	size_t length;

	if (fgets(input, READ_BUF_SIZE, stdin) == NULL)
		return (-1);

	length = strlen(input);
	if (length > 0 && input[length - 1] == '\n')
	{
		input[length - 1] = '\0';
		length--;
	}

	data->line = malloc(length + 1);
	if (data->line == NULL)
		return (-1);

	strcpy(data->line, input);
	return (length);
}
