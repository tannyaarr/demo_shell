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
	int i = 0;
	char *path;
	char *full_path = malloc(PATH_MAX_LENGTH);

	while ((path = data->paths[i++]) != NULL)
	{
		snprintf(full_path, PATH_MAX_LENGTH, "%s/%s", path, command);
		if (access(full_path, F_OK) != -1)
		{
			return (full_path);
		}
	}
	free(full_path);
	return (NULL);
}
