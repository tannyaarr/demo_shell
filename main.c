#include "shell.h"

/**
 * run_shell_command - Execute the shell command
 * @data: Pointer to the shell data structure
 * Return: void
 */

void run_shell_command(shell_data *data)
{
	int status;

	if (_strcmp(data->args[0], "cd") == 0)
	{
		cd_command(data);
		return;
	}

	else if (_strcmp(data->args[0], "exit") == 0)
	{
		if (data->num_args == 1)
			exit(EXIT_SUCCESS);
		else if (data->num_args == 2)
		{
			status = atoi(data->args[1]);
			exit(status);
		}
		else
		{
			fprintf(stderr, "Usage: exit [status]\n");
			return;
		}
	}
	else if (_strcmp(data->args[0], "env") == 0)
	{
		print_env();
		return;
	}

	execute_command(data);
	free_shell_data(data);
	init_shell_data(data);
}

/**
 * main - Entry point of the shell program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 * Return: 0 on success, otherwise an error code.
 */

int main(int argc, char **argv)
{
	char *program_name, *last_slash;
	shell_data data;
	int interactive_mode = isatty(STDIN_FILENO);

	init_shell_data(&data);

	program_name = argv[0];
	last_slash = strrchr(program_name, '/');
	if (last_slash != NULL)
		program_name = last_slash + 1;

	if (argc > 1)
	{
		interactive_mode = 0;
		run_file_command(program_name, argv[1], &data);
	}
	else
	{
		while (interactive_mode)
		{
			printf("($) ");
			fflush(stdout);

			if (read_shell_input(&data) == -1)
			{
				free_shell_data(&data);
				exit(EXIT_FAILURE);
			}

			if (data.line == NULL)
				break;

			run_shell_command(&data);
		}
	}

	return (0);
}


/**
 * run_file_command - File command function
 * @program_name: name of program
 * @file_name: name of file
 * @data: shell data
 * Return: void
 */

void run_file_command(const char *program_name,
		const char *file_name, shell_data *data)
{
	FILE *file;
	ssize_t chars_read;

	if (file_name == NULL)
	{
		fprintf(stderr, "%s: 0: Can't open %s\n", program_name, file_name);
		exit(EXIT_FAILURE);
	}

	file = fopen(file_name, "r");
	if (feof(file))
		return;

	if (file == NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	while ((_getline(data)) != -1)
	{
		printf("(%s) ", program_name);
		fflush(stdout);

		chars_read = strlen(data->line);
		if (chars_read > 0 && data->line[chars_read - 1] == '\n')
			data->line[chars_read - 1] = '\0';

		tokenize(data);
		run_shell_command(data);

		if (data->args[0] != NULL && _strcmp(data->args[0], "exit") == 0)
			break;
	}

	fclose(file);
}

/**
 * read_shell_input - reads shell input
 * @data: Struct to store data
 * Return: 0 if successful, -1 on error or end of input
 */
int read_shell_input(shell_data *data)
{
	ssize_t chars_read;

	if (data->line != NULL)
	{
		free(data->line);
		data->line = NULL;
	}

	chars_read = _getline(data);
	if (chars_read == -1)
	{
		free_shell_data(data);
		return (-1);
	}

	if (chars_read == 0)
		return (-1);

	if (data->line != NULL && data->line[0] != '\0')
	{
		if (data->line[chars_read - 1] == '\n')
			data->line[chars_read - 1] = '\0';
		tokenize(data);
		return (0);
	}

	return (-1);
}

