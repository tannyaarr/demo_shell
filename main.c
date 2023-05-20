#include "shell.h"

/**
 * run_shell_command - Execute the shell command
 * @data: Pointer to the shell data structure
 * Return: void
 */

void run_shell_command(shell_data *data)
{
	int status;

	if (strcmp(data->args[0], "exit") == 0)
	{
		if (data->num_args == 1)
			exit(EXIT_SUCCESS);
		else if (data->num_args == 2)
		{
			status = atoi(data->args[1]);
			exit(status);
		} else
		{
			fprintf(stderr, "Usage: exit [status]\n");
		}
	}
	else if (strcmp(data->args[0], "env") == 0)
	{
		print_env();
	}
	else
	{
		execute_command(data);
	}
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

	init_shell_data(&data);

	program_name = argv[0];
	last_slash = strrchr(program_name, '/');
	if (last_slash != NULL)
	{
		program_name = last_slash + 1;
	}

	if (argc == 1)
	{
		while (1)
		{
			printf("($) ");
			fflush(stdout);
			if (read_shell_input(&data) == -1)
			{
				free_shell_data(&data);
				exit(EXIT_FAILURE);
			}
			run_shell_command(&data);
		}
	}
	else
	{
		run_file_command(program_name, argv[1], &data);
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
	size_t buf_size = 0;

	file = fopen(file_name, "r");

	if (file == NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	while ((chars_read = getline(&data->line, &buf_size, file)) != -1)
	{
		printf("(%s) ", program_name);
		fflush(stdout);

		tokenize(data);
		run_shell_command(data);
	}

	fclose(file);
}

