#include "shell.h"

/**
 * run_shell_command - Execute the shell command
 * @data: Pointer to the shell data structure
 * Return: void
 */

void run_shell_command(shell_data *data)
{
	pid_t pid;
	int status;

	if (data->args[0] == NULL || strcmp(data->args[0], "") == 0)
		return;

	if (strcmp(data->args[0], "cd") == 0)
	{
		cd_command(data);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		execvp(data->args[0], data->args);
		perror("execvp");
		exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
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
 */
void run_file_command(const char *program_name,
		const char *file_name, shell_data *data)
{
	FILE *file;
	char line[READ_BUF_SIZE];

	file = fopen(file_name, "r");
	if (file == NULL)
	{
		perror(program_name);
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), file) != NULL)
	{
		line[strcspn(line, "\n")] = '\0';
		data->line = line;
		tokenize(data);
		run_shell_command(data);
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
