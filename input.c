#include "shell.h"

/**
 * get_input - Read a line of input from stdin
 * Return: Pointer to the input string
 *
 */
char *get_input(void)
{
    char *buffer = malloc(sizeof(char) * MAX_BUFFER);
    size_t bufsize = MAX_BUFFER;
    ssize_t characters;

    if (!buffer)
    {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    characters = getline(&buffer, &bufsize, stdin);

    if (characters == -1)
    {
        if (isatty(STDIN_FILENO))
            printf("\n");
        exit(EXIT_SUCCESS);
    }

    if (buffer[characters - 1] == '\n')
        buffer[characters - 1] = '\0';

    return (buffer);
}

/**
 * split_input - Split a string into tokens
 * @input: Input string
 * Return: Array of tokens
 */
char **split_input(char *input)
{
    char **tokens = malloc(sizeof(char *) * MAX_ARGS);
    char *token;
    int i = 0;

    if (!tokens)
    {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, " ");

    while (token)
    {
        tokens[i] = token;
        i++;
        token = strtok(NULL, " ");
    }

    tokens[i] = NULL;
    return (tokens);
}
