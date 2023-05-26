#include "shell.h"

/**
 * shell_env - Print the current environment variables
 * @args: Array of arguments
 * Return: 1 on success, 0 on failure
 */
int shell_env(char **args)
{
    int i = 0;

    if (args[1] != NULL)
    {
        fprintf(stderr, "env: too many arguments\n");
        return (0);
    }

    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }

    return (1);
}

/**
 * shell_setenv - Initialize or modify an environment variable
 * @args: Array of arguments
 * Return: 1 on success, 0 on failure
 */
int shell_setenv(char **args)
{
    if (args[1] == NULL || args[2] == NULL || args[3] != NULL)
    {
        fprintf(stderr, "setenv: invalid arguments\n");
        return (0);
    }

    if (setenv(args[1], args[2], 1) == -1)
    {
        perror("setenv");
        return (0);
    }

    return (1);
}

/**
 * shell_unsetenv - Remove an environment variable
 * @args: Array of arguments
 * Return: 1 on success, 0 on failure
 */
int shell_unsetenv(char **args)
{
    if (args[1] == NULL || args[2] != NULL)
    {
        fprintf(stderr, "unsetenv: invalid arguments\n");
        return (0);
    }

    if (unsetenv(args[1]) == -1)
    {
        perror("unsetenv");
        return (0);
    }

    return (1);
}

/**
 * replace_variables - Replace variables in a command
 * @command: Command string
 * Return: Replaced command string
 */
char *replace_variables(char *command)
{
    char *replaced = malloc(strlen(command) * 2 + 1);
    char *replaced_ptr = replaced;
    char *command_ptr = command;
    char *variable_start;
    char *variable_end;
    char variable_name[MAX_VARIABLE_NAME];
    char variable_value[MAX_VARIABLE_VALUE];
    int variable_length, last_status = 0;
    char *env_value;

    if (!replaced)
    {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    while (*command_ptr != '\0')
    {
        if (*command_ptr == '$')
        {
            variable_start = command_ptr + 1;
            variable_end = variable_start;
            while (isalnum(*variable_end) || *variable_end == '_')
                variable_end++;

            variable_length = variable_end - variable_start;
            strncpy(variable_name, variable_start, variable_length);
            variable_name[variable_length] = '\0';

            if (strcmp(variable_name, "$") == 0)
            {
                sprintf(variable_value, "%d", getpid());
            }
            else if (strcmp(variable_name, "?") == 0)
            {
                sprintf(variable_value, "%d", last_status);
            }
            else
            {
                env_value = getenv(variable_name);

                if (env_value)
                    strncpy(variable_value, env_value, MAX_VARIABLE_VALUE);
                else
                    variable_value[0] = '\0';
            }

            strcat(replaced_ptr, variable_value);
            replaced_ptr += strlen(variable_value);
            command_ptr = variable_end;
        }
        else
        {
            *replaced_ptr = *command_ptr;
            replaced_ptr++;
            command_ptr++;
        }
    }

    *replaced_ptr = '\0';

    return replaced;
}


