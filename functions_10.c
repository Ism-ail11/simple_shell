#include "shell.h"

/**
 * replaceVariables - Replaces variables in the tokenized string.
 *
 * @info: Pointer to the parameter struct.
 *
 * Return: 1 if variables are replaced, 0 otherwise.
 */

int replaceVariables(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replaceString(&(info->argv[i]),
				_strDuplicate(convertNumber(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replaceString(&(info->argv[i]),
				_strDuplicate(convertNumber(getpid(), 10, 0)));
			continue;
		}
		node = nodeStartsWith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replaceString(&(info->argv[i]),
				_strDuplicate(_strchr(node->str, '=') + 1));
			continue;
		}
		replaceString(&info->argv[i], _strDuplicate(""));

	}
	return (0);
}
