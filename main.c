#include "shell.h"


/**
 * main - Simple Shell entry point
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 * @env: Array of environment variables
 * Return: Exit status
 */
int main(int argc, char **argv, char **env)
{
    char *input, **args;
    int interactive = 1, i;

    (void)argc;

    if (!isatty(STDIN_FILENO))
        interactive = 0;

    environ = env;

    signal(SIGINT, handle_signals);
    signal(SIGTSTP, SIG_IGN);

    if (argv[1])
        return (batch_mode(argv[1]));

    while (1)
    {
        if (interactive)
            printf("$ ");

        input = get_input();
        args = split_input(input);

        if (args[0] != NULL)

            if (check_builtins(args))
            {
                free(input);
                free(args);
                continue;
            }

            if (execute_command(args) == -1)
            {
                perror("Execution failed");
                free(input);
                free(args);
                continue;
            }
        }

        free(input);
        free(args);
    }

    return (EXIT_SUCCESS);
}
