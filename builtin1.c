#include "shell.h"

/**
 * _myhistory - displays the history list, one command per line,
 *               preceded with line numbers starting at 0.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * unset_alias - unsets an alias from the alias list
 * @info: Parameter struct.
 * @str: The string alias.
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
    char *equals, saved_char;
    int ret;

    equals = _strchr(str, '=');
    if (!equals)
        return (1);

    saved_char = *equals;
    *equals = 0;

    ret = delete_node_at_index(&(info->alias),
                               get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

    *equals = saved_char;
    return (ret);
}

/**
 * set_alias - sets an alias to a string
 * @info: Parameter struct.
 * @str: The string alias.
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
    char *equals;

    equals = _strchr(str, '=');
    if (!equals)
        return (1);

    if (!*++equals)
        return (unset_alias(info, str));

    unset_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: The alias node.
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
    char *equals, *alias;

    if (node)
    {
        equals = _strchr(node->str, '=');
        for (alias = node->str; alias <= equals; alias++)
            _putchar(*alias);

        _putchar('\'');
        _puts(equals + 1);
        _puts("'\n");

        return (0);
    }

    return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int _myalias(info_t *info)
{
    int i = 0;
    char *equals = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return (0);
    }

    for (i = 1; info->argv[i]; i++)
    {
        equals = _strchr(info->argv[i], '=');

        if (equals)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}

