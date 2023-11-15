#include "shell.h"

/**
 * unsetAlias - Removes an alias.
 *
 * @info: Pointer to the parameter structure.
 * @str: String representing the alias to be removed.
 *
 * Return: 0 if the alias was successfully unset, 1 if there was an error.
*/

int unsetAlias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = deleteNode(&(info->alias),
		getNodeIndex(info->alias, nodeStartsWith(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * setAlias - Creates or modifies an alias.
 *
 * @info: Pointer to the parameter structure.
 * @str: String representing the alias to be set.
 *
 * Return: 0 if the alias was successfully set, 1 if there was an error.
*/


int setAlias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unsetAlias(info, str));

	unsetAlias(info, str);
	return (endNode(&(info->alias), str, 0) == NULL);
}

/**
 * printAlias - Displays an alias.
 *
 * @node: Alias node to be printed.
 *
 * Return: 0 if the alias was successfully printed, 1 if there was an error.
 */

int printAlias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * myAlias - Simulates the "alias" built-in command (man alias).
 *
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */

int myAlias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			printAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			setAlias(info, info->argv[i]);
		else
			printAlias(nodeStartsWith(info->alias, info->argv[i], '='));
	}

	return (0);
}

/**
 * replaceAlias - Replaces aliases in the tokenized string.
 *
 * @info: The parameter structure.
 *
 * Return: 1 if any aliases were replaced, 0 otherwise.
 */

int replaceAlias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nodeStartsWith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strDuplicate(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}
