#include "shell.h"

/**
 * _getline - gets line from stream
 * @data: shell data
 * Return: number of characters read
 */

ssize_t _getline(shell_data *data)
{
	static char buffer[READ_BUF_SIZE];
	static int pos = -1;
	ssize_t chars_read = 0;
	char *start, *end;

	if (pos == -1)
	{
		chars_read = read(STDIN_FILENO, buffer, READ_BUF_SIZE);
		if (chars_read == -1)
			return (-1);
		else if (chars_read == 0)
			return (0);
		pos = 0;
	}

	start = &buffer[pos];
	end = memchr(start, '\n', chars_read - pos);
	if (end != NULL)
	{
		*end = '\0';
		data->line = realloc(data->line, pos + (end - start) + 1);
		if (data->line == NULL)
			return (-1);
		memcpy(data->line + pos, start, end - start + 1);
		pos = -1;
		return (end - start + 1);
	}

	data->line = realloc(data->line, pos + chars_read + 1);
	if (data->line == NULL)
		return (-1);
	memcpy(data->line + pos, buffer, chars_read);
	pos += chars_read;
	return (chars_read);
}
