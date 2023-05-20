#include "shell.h"

/**
 * init_shell_data - SHell data initialization
 * @data: Struct to store data
 * Return: void
 */

void init_shell_data(shell_data *data)
{
	data->paths[0] = "/bin";
	data->paths[1] = "/usr/bin";
	data->paths[2] = NULL;

	data->line = NULL;
	data->num_args = 0;
}

/**
 * read_shell_input - reads shell input
 * @data: Struct to store data
 * Return: void
 */


int read_shell_input(shell_data *data)
{
	ssize_t chars_read;

	chars_read = _getline(data);

	if (chars_read == -1)
	{
		data->line = NULL;
		return (-1);
	}
	else if (chars_read == 0)
	{
		data->line = NULL;
		return (-1);
	}

	tokenize(data);
	return (0);
}

/**
 * free_shell_data - Free memory of shell data
 * @data: Struct to store data
 * Return: void
 */

void free_shell_data(shell_data *data)
{
	if (data->line != NULL)
	{
		free(data->line);
		data->line = NULL;
	}
}

/**
 * print_env - Print environment
 * Return: void
 */

void print_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
