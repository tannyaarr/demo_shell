#include "shell.h"
#include <stddef.h>

/**
 * _strpbrk - Locates the first occurrence of any character from the 'accept'
 *            string in the 'str' string.
 * @str: The string to be searched.
 * @accept: The string containing the characters to match.
 *
 * Return: A pointer to the first occurrence in 'str' of any character from
 *         'accept', or NULL if no match is found.
 */
char *_strpbrk(const char *str, const char *accept)
{
	const char *s1 = str;
	const char *s2;

	while (*s1)
	{
		s2 = accept;
		while (*s2)
		{
			if (*s1 == *s2)
				return ((char *)s1);
			s2++;
		}
		s1++;
	}

	return (NULL);
}


/**
 * tokenize - tokenize a string into an array of strings
 * @data: shell data struct
 * Return: void
 */

void tokenize(shell_data *data)
{
    const char *delim = " \t\n";
    char *line = data->line;
    int num_args = 0;
    char *token, *token_start, *token_end;
    size_t token_length;

    while (*line && num_args < MAX_ARGS - 1)
    {
        while (*line && strchr(delim, *line))
            line++;

        if (*line == '#')
        {
            data->args[num_args] = NULL;
            return;
        }

        if (*line == '\0')
            break;

        token_start = line;
        token_end = strpbrk(line, delim);

        if (token_end == NULL)
            token_end = line + strlen(line);

        token_length = token_end - token_start;
        if (token_length > 0)
        {
            token = malloc(token_length + 1);
            strncpy(token, token_start, token_length);
            token[token_length] = '\0';

            data->args[num_args++] = token;

            if (num_args == MAX_ARGS - 1)
                break;
        }

        line = token_end;
    }

    data->args[num_args] = NULL;
}
