#include "shell.h"

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



/**
 * set_env_variable - Initialize a new environment
 * variable or modify an existing one
 * @variable: The name of the environment variable
 * @value: The value to be assigned to the environment variable
 * Return: void
 */
void set_env_variable(const char *variable, const char *value)
{
	if (setenv(variable, value, 1) != 0)
	{
		fprintf(stderr, "Failed to set environment variable: %s\n", variable);
	}
}



/**
 * unset_env_variable - Remove an environment variable
 * @variable: The name of the environment variable to be removed
 * Return: void
 */
void unset_env_variable(const char *variable)
{
	if (unsetenv(variable) != 0)
	{
		fprintf(stderr, "Failed to unset environment variable: %s\n", variable);
	}
}


/**
 * is_builtin_command - Check if command is a built-in command
 * @command: Command name
 * Return: 1 if built-in, 0 otherwise
 */

int is_builtin_command(const char *command)
{
	return ((_strcmp(command, "setenv") == 0 ||
				_strcmp(command, "unsetenv") == 0));
}
