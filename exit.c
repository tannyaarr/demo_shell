#include "shell.h"

/**
 * shell_exit - Exit the shell
 * @args: Array of arguments
 * Return: 1 to indicate the shell should exit
 */
int shell_exit(char **args)
{
    int status = 0;

    if (args[1] != NULL)
        status = atoi(args[1]);

    exit(status);
}
