#include "shell.h"

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
		path = get_command_path(data);
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
		wait_for_child(pid, &status);
	}
}

/**
 * get_command_path -Get shell command path
 * @data: Struct to store data
 * Return: shell command
 */

char *get_command_path(shell_data *data)
{
	char *path;

	if (data->args[0][0] == '/')
	{
		return (data->args[0]);
	}
	else
	{
		path = get_path(data, data->args[0]);
		return ((path != NULL) ? path : NULL);
	}
}

/**
 * wait_for_child - Wait function for parent process
 * @pid: process ID
 * @status: return value
 * Return: void
 */

void wait_for_child(pid_t pid, int *status)
{
	while (waitpid(pid, status, WUNTRACED) == -1)
	{
		if (errno != EINTR)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	}
}

