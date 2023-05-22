#include "shell.h"

/**
 * cd_command - Change the current directory of the process
 * @data: Pointer to the shell data structure
 * Return: void
 */
void cd_command(shell_data *data)
{
	char *directory;
	char current_directory[PATH_MAX];

	if (data->num_args == 1 || strcmp(data->args[1], "~") == 0)
		directory = getenv("HOME");
	else if (strcmp(data->args[1], "-") == 0)
		directory = getenv("OLDPWD");
	else
		directory = data->args[1];

	if (directory == NULL)
	{
		fprintf(stderr, "cd: Directory not found\n");
		return;
	}

	if (chdir(directory) != 0)
	{
		perror("cd");
		return;
	}

	if (getcwd(current_directory, sizeof(current_directory)) != NULL)
	{
		if (setenv("PWD", current_directory, 1) != 0)
		{
			perror("setenv");
			return;
		}
	}
	else
	{
		perror("getcwd");
		return;
	}
}
