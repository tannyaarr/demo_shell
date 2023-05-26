#include "shell.h"

/**
 * count_arguments - Count the number of arguments
 * @args: Array of arguments
 * Return: Number of arguments
 */
int count_arguments(char **args)
{
    int count = 0;

    while (args[count] != NULL)
        count++;

    return (count);
}

/**
 * check_builtins - Check for built-in commands and execute them
 * @args: Array of arguments
 * Return: 1 if a built-in command is executed, 0 otherwise
 */
int check_builtins(char **args)
{

    if (strcmp(args[0], "exit") == 0)
        return (shell_exit(args));

    if (strcmp(args[0], "env") == 0)
        return (shell_env(args));

    if (strcmp(args[0], "setenv") == 0)
        return (shell_setenv(args));

    if (strcmp(args[0], "unsetenv") == 0)
        return (shell_unsetenv(args));

    if (strcmp(args[0], "cd") == 0)
        return (shell_cd(args));

    if (strcmp(args[0], "alias") == 0)
        return (shell_alias(args));

    return (0);
}

/**
 * find_command - Find the full path of a command
 * @command: Command name
 * Return: Full path of the command, or NULL if not found
 */
char *find_command(char *command)
{
    char *path, *token, *command_path;
    struct stat st;

    Alias *alias = alias_list;
    while (alias != NULL)
    {
        if (strcmp(alias->name, command) == 0)
            return (alias->value);
        alias = alias->next;
    }

    if (is_executable(command))
        return (command);

    path = strdup(getenv("PATH"));
    token = strtok(path, ":");

    while (token != NULL)
    {
        command_path = malloc(strlen(token) + strlen(command) + 2);
        strcpy(command_path, token);
        strcat(command_path, "/");
        strcat(command_path, command);

        if (stat(command_path, &st) == 0)
        {
            free(path);
            return (command_path);
        }

        free(command_path);
        token = strtok(NULL, ":");
    }

    free(path);
    return (NULL);
}

#include "shell.h"

/**
 * free_args - Free the memory allocated for the arguments array
 * @args: Arguments array
 */
void free_args(char **args)
{
    int i;

    if (args == NULL)
        return;

    for (i = 0; args[i] != NULL; i++)
        free(args[i]);

    free(args);
}

/**
 * execute_builtin - Execute a builtin command
 * @args: Arguments array
 * Return: 1 if the command is a builtin, 0 otherwise
 */
int execute_builtin(char **args)
{
    int status = 0;

    if (args == NULL || args[0] == NULL)
        return 0;

    if (strcmp(args[0], "cd") == 0)
        status = shell_cd(args);
    else if (strcmp(args[0], "exit") == 0)
        status = shell_exit(args);
    else if (strcmp(args[0], "env") == 0)
        status = shell_env(args);
    else if (strcmp(args[0], "setenv") == 0)
        status = shell_setenv(args);
    else if (strcmp(args[0], "unsetenv") == 0)
        status = shell_unsetenv(args);
    else if (strcmp(args[0], "alias") == 0)
        status = shell_alias(args);
    else
        return 0;

    return status;
}

