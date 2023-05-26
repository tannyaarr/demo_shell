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

	if (_strcmp(data->args[0], "setenv") == 0)
	{
		handle_setenv(data);
			return;
	}
	else if (_strcmp(data->args[0], "unsetenv") == 0)
	{
		handle_unsetenv(data);
			return;
	}

	pid = fork();
	if (pid == 0)
	{
		path = get_command_path(data);
		if (path == NULL)
			exit_with_error("%s: command not found\n", data->args[0]);

		execute_command_child(data, path);
	}
	else if (pid < 0)
		exit_with_error("fork");

	if (!is_builtin_command(data->args[0]))
		wait_for_child(pid, &status);
}

/**
 * handle_setenv - Handle setenv command
 * @data: Struct to store data
 * Return: void
 */

void handle_setenv(shell_data *data)
{
	if (data->num_args != 3)
		exit_with_error("Usage: setenv VARIABLE VALUE\n");

	if (setenv(data->args[1], data->args[2], 1) != 0)
		perror("setenv");
}

/**
 * handle_unsetenv - Handle unsetenv command
 * @data: Struct to store data
 * Return: void
 */

void handle_unsetenv(shell_data *data)
{
	if (data->num_args != 2)
		exit_with_error("Usage: unsetenv VARIABLE\n");

	if (unsetenv(data->args[1]) != 0)
		perror("unsetenv");
}

/**
 * execute_command_child - Execute command in child process
 * @data: Struct to store data
 * @path: Command path
 * Return: void
 */

void execute_command_child(shell_data *data, char *path)
{
	execve(path, data->args, environ);
	perror("execve");
	exit(EXIT_FAILURE);
}

/**
 * exit_with_error - Print error message and exit with failure
 * @format: Format string
 * ...: Variable arguments
 * Return: void
 */

void exit_with_error(const char *format, ...)
{
	va_list args;

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	exit(EXIT_FAILURE);
}
