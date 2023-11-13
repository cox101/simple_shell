#include "shell.h"

/**
 * print_environment - Prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int print_environment(info_t *info)
{
    print_list_str(info->environment);
    return (0);
}

/**
 * get_environment_variable - Gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: Environment variable name
 *
 * Return: The value of the environment variable
 */
char *get_environment_variable(info_t *info, const char *name)
{
    list_t *node = info->environment;
    char *value;

    while (node)
    {
        value = starts_with(node->str, name);
        if (value && *value)
            return value;
        node = node->next;
    }
    return NULL;
}

/**
 * set_environment_variable - Initializes a new environment variable
 *                            or modifies an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int set_environment_variable(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return 1;
    }
    if (_setenv(info, info->argv[1], info->argv[2]))
        return 0;
    return 1;
}

/**
 * unset_environment_variable - Removes an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int unset_environment_variable(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return 1;
    }
    for (i = 1; i <= info->argc; i++)
        _unsetenv(info, info->argv[i]);

    return 0;
}

/**
 * populate_environment_list - Populates the environment linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_environment_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info->environment = node;
    return 0;
}
