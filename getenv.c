#include "shell.h"

/**
 * get_environment_strings - Returns a copy of environment strings
 * @info: Structure containing potential arguments.
 *
 * Return: String array copy of the environment.
 */
char **get_environment_strings(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return info->environ;
}

/**
 * unset_environment_variable - Removes an environment variable
 * @info: Structure containing potential arguments.
 * @variable: The name of the environment variable to remove.
 *
 * Return: 1 on successful deletion, 0 otherwise.
 */
int unset_environment_variable(info_t *info, char *variable)
{
	list_t *node = info->env;
	size_t index = 0;
	char *p;

	if (!node || !variable)
		return 0;

	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return info->env_changed;
}

/**
 * set_environment_variable - Initializes a new environment variable
 *                           or modifies an existing one.
 * @info: Structure containing potential arguments.
 * @variable: The name of the environment variable.
 * @value: The value of the environment variable.
 *
 * Return: Always 0.
 */
int set_environment_variable(info_t *info, char *variable, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return 0;

	buf = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buf)
		return 1;

	_strcpy(buf, variable);
	_strcat(buf, "=");
	_strcat(buf, value);

	node = info->env;
	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return 0;
		}
		node = node->next;
	}

	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;

	return 0;
}
 
