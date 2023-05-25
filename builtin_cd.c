#include "shell.h"

/**
 * shell_cd - Change the current directory
 * @args: Array of arguments
 * Return: 1 on success, 0 on failure
 */
int shell_cd(char **args)
{
    char *new_dir;
    char cwd[MAX_PATH];

    if (args[1] == NULL || strcmp(args[1], "~") == 0)
        new_dir = getenv("HOME");
    else if (strcmp(args[1], "-") == 0)
        new_dir = prev_dir;
    else
        new_dir = args[1];

    if (new_dir == NULL)
    {
        perror("cd");
        return (1);
    }

    if (chdir(new_dir) == -1)
    {
        perror("cd");
        return (1);
    }

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        setenv("PWD", cwd, 1);
        prev_dir = strdup(cwd);
    }

    return (0);
}
