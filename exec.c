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
    char *command_path;

    pid = fork();
    if (pid == -1)
    {
        exit_with_error("Fork error");
    }
    else if (pid == 0)
    {
        command_path = get_command_path(data);

        if (command_path == NULL)
        {
            fprintf(stderr, "%s: command not found\n", data->args[0]);
            exit(127);
        }

        if (execve(command_path, data->args, environ) == -1)
        {
            fprintf(stderr, "%s: execution error\n", data->args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait_for_child(pid, &status);
        if (WIFEXITED(status))
        {
            status = WEXITSTATUS(status);
            return;
        }
    }
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
