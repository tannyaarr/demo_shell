#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
* get_path - Get the full path of command
* @data: pointer to shell_data struct
* @command: command line argument
* Return: path of command
*/
char *get_path(shell_data *data, const char *command)
{
        char *path = data->path;
        char *path_env = strdup(path);
        char *token = strtok(path_env, ":");
        char *full_path = malloc(PATH_MAX_LENGTH);

        while (token != NULL)
        {
                snprintf(full_path, PATH_MAX_LENGTH, "%s/%s", token, command);
                if (access(full_path, F_OK) != -1)
                {
                        free(path_env);
                        return full_path;
                }
                token = strtok(NULL, ":");
        }

        free(path_env);
        free(full_path);
        return NULL;
}

