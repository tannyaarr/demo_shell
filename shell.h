#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_ARGS 64
#define MAX_PATH 1024
#define MAX_BUFFER 1024
typedef struct alias_t {
	char *name;
	char *value;
	struct alias_t *next;
} Alias;

Alias *alias_list = NULL;
char *prev_dir = NULL;

extern char **environ;

int shell_cd(char **args);
int shell_exit(char **args);
int shell_env(char **args);
int shell_setenv(char **args);
int shell_unsetenv(char **args);
int shell_alias(char **args);
int check_builtins(char **args);
int execute_command(char **args);
char *find_command(char *command);
int is_executable(char *path);
char *get_input(void);
char **split_input(char *input);
int count_arguments(char **args);
void handle_signals(int signal);

#endif /* SHELL_H */
