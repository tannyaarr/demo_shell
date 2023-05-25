#include "shell.h"

/**
 * shell_alias - Manage aliases
 * @args: Array of arguments
 * Return: 1 on success, 0 on failure
 */
int shell_alias(char **args)
{
	int i;
	char *name, value;

    if (args[1] == NULL)
    {
        Alias *alias = alias_list;
        while (alias != NULL)
        {
            printf("%s='%s'\n", alias->name, alias->value);
            alias = alias->next;
        }
        return (1);
    }

    i = 1;
    while (args[i] != NULL)
    {
        name = args[i];
        value = strchr(name, '=');

        if (value == NULL)
        {
            Alias *alias = find_alias(name);
            if (alias == NULL)
            {
                fprintf(stderr, "alias: %s not found\n", name);
                return (0);
            }
            printf("%s='%s'\n", alias->name, alias->value);
        }
        else
        {
            *value = '\0';
            value++;
            create_alias(name, value);
        }

        i++;
    }

    return (1);
}

/**
 * find_alias - Find an alias by name
 * @name: Alias name
 * Return: Pointer to the alias, or NULL if not found
 */
Alias *find_alias(char *name)
{
    Alias *alias = alias_list;

    while (alias != NULL)
    {
        if (strcmp(alias->name, name) == 0)
            return (alias);
        alias = alias->next;
    }

    return (NULL);
}

/**
 * create_alias - Create a new alias
 * @name: Alias name
 * @value: Alias value
 */
void create_alias(char *name, char *value)
{
    Alias *alias = malloc(sizeof(Alias));

    if (!alias)
    {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    alias->name = strdup(name);
    alias->value = strdup(value);
    alias->next = alias_list;
    alias_list = alias;
}

/**
 * free_aliases - Free the linked list of aliases
 */
void free_aliases()
{
    Alias *alias = alias_list;
    Alias *next;

    while (alias != NULL)
    {
        next = alias->next;
        free(alias->name);
        free(alias->value);
        free(alias);
        alias = next;
    }
}
