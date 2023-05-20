#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * execute_command - Execute shell command
 * @data: Struct to store data
 * Return: void
 */

void execute_command(shell_data *data)
{
	pid_t pid;
	int status;
	char *path;

	pid = fork();

	if (pid == 0)
	{
		path = get_path(data, data->args[0]);

		if (path == NULL)
		{
			fprintf(stderr, "%s: command not found\n", data->args[0]);
			exit(EXIT_FAILURE);
		}

		execve(path, data->args, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}

	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		do

		{
			if (waitpid(pid, &status, WUNTRACED) == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
		}

		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
