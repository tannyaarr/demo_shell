#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdarg.h>
#include <limits.h>


#define MAX_ARGS 10
#define MAX_PATHS 10
#define PATH_MAX_LENGTH 100
#define READ_BUF_SIZE 1024

extern char **environ;

/**
 * struct shell_data - Shell data structure
 * @paths: Array of paths
 * @line: Pointer to the input line
 * @args: Array of arguments
 * @num_args: Number of arguments
 */

typedef struct shell_data
{
	char *path;
	char *line;
	char *args[MAX_ARGS];
	int num_args;
} shell_data;

char *get_path(struct shell_data *data, const char *command);
void tokenize(struct shell_data *data);
void print_env(void);
void free_shell_data(shell_data *data);
void execute_command(shell_data *data);
int read_shell_input(shell_data *data);
void init_shell_data(shell_data *data);
ssize_t _getline(shell_data *data);
void run_shell_command(shell_data *data);
void run_file_command(const char *program_name,
		const char *file_name, shell_data *data);
char *get_command_path(shell_data *data);
void wait_for_child(pid_t pid, int *status);
char *_strpbrk(const char *str, const char *accept);
int append_to_line(shell_data *data, char *input,
		ssize_t size, ssize_t *total_chars_read);
void set_env_variable(const char *variable, const char *value);
void unset_env_variable(const char *variable);
void handle_setenv(shell_data *data);
void handle_unsetenv(shell_data *data);
void execute_command_child(shell_data *data, char *path);
void exit_with_error(const char *format, ...);
int is_builtin_command(const char *command);
void cd_command(shell_data *data);
char *_strncpy(char *dest, const char *src, size_t n);
size_t _strlen(const char *s);
char *_strchr(const char *s, int c);
int _strcmp(const char *s1, const char *s2);


#endif /* SHELL_H */
