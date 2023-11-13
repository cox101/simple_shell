#include "shell.h"

/**
 * display_history - Displays the history list, one command per line,
 *                   preceded with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int display_history(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * remove_alias - Removes an alias identified by a string
 * @info: Parameter struct
 * @alias_str: The string representing the alias
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(info_t *info, char *alias_str)
{
    char *equal_sign, original_char;
    int ret;

    equal_sign = _strchr(alias_str, '=');
    if (!equal_sign)
        return (1);

    original_char = *equal_sign;
    *equal_sign = '\0';

    ret = delete_node_at_index(&(info->alias),
                               get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));

    *equal_sign = original_char;
    return (ret);
}

/**
 * set_alias - Sets an alias to a string
 * @info: Parameter struct
 * @alias_str: The string representing the alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *alias_str)
{
    char *equal_sign;

    equal_sign = _strchr(alias_str, '=');
    if (!equal_sign)
        return (1);

    if (!*++equal_sign)
        return (remove_alias(info, alias_str));

    remove_alias(info, alias_str);
    return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_alias_entry - Prints an alias string
 * @alias_node: The alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias_entry(list_t *alias_node)
{
    char *equal_sign = NULL, *alias_str = NULL;

    if (alias_node)
    {
        equal_sign = _strchr(alias_node->str, '=');
        for (alias_str = alias_node->str; alias_str <= equal_sign; alias_str++)
            _putchar(*alias_str);
        _putchar('\'');
        _puts(equal_sign + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * manage_alias - Mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int manage_alias(info_t *info)
{
    int i = 0;
    char *equal_sign = NULL;
    list_t *alias_node = NULL;

    if (info->argc == 1)
    {
        alias_node = info->alias;
        while (alias_node)
        {
            print_alias_entry(alias_node);
            alias_node = alias_node->next;
        }
        return (0);
    }

    for (i = 1; info->argv[i]; i++)
    {
        equal_sign = _strchr(info->argv[i], '=');
        if (equal_sign)
            set_alias(info, info->argv[i]);
        else
		print_alias_entry(node_starts_with(info->alias, info->argv[i], '='));
    }
    return (0);
}

