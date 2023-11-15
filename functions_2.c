#include "shell.h"

/**
 * myHistory - Displays the history list, one command per line,
 * preceded with line numbers starting at 0.
 *
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */

int myHistory(info_t *info)
{
	printList(info->history);
	return (0);
}

/**
 * myEnv - Prints the current environment.
 *
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */

int myEnv(info_t *info)
{
	printListStr(info->env);
	return (0);
}

/**
 * getEnvVariable - Gets the value of an environment variable.
 *
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 *
 * Return: The value of the environment variable.
 */

char *getEnvVariable(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = startsWith(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * mySetEnv - Initializes a new environment variable
 * or modifies an existing one.
 *
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */

int mySetEnv(info_t *info)
{
	if (info->argc != 3)
	{
		printString("Incorrect number of arguements\n");
		return (1);
	}
	if (setEnv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * myUnsetEnv - Removes an environment variable.
 *
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0.
 */

int myUnsetEnv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		printString("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetEnv(info, info->argv[i]);

	return (0);
}
