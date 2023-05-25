#include "shell.h"

/**
 * is_executable - Check if a file is executable
 * @path: Path to the file
 * Return: 1 if the file is executable, 0 otherwise
 */
int is_executable(char *path)
{
    struct stat st;

    if (stat(path, &st) == 0 && st.st_mode & S_IXUSR)
        return (1);

    return (0);
}

/**
 * handle_signals - Handle signals
 * @signal: Signal number
 */
void handle_signals(int signal)
{
    if (signal == SIGINT)
    {
        putchar('\n');
        printf("$ ");
        fflush(stdout);
    }
}


/**
 * execute_command - Execute an external command
 * @args: Array of arguments
 * Return: 0 on success, -1 on failure
 */
int execute_command(char **args)
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Fork error");
        return (-1);
    }

    if (child_pid == 0)
    {
        if (execve(args[0], args, environ) == -1)
        {
            perror("Execution error");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(child_pid, &status, WUNTRACED);
    }

    return (0);
}
