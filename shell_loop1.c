#include "shell.h"

/**
 * shellLoop - Main loop of the shell program.
 *
 * @info: Pointer to the info struct.
 * @av: Argument vector.
 *
 * Return: 0 on success, -1 on failure.
 */

int shellLoop(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clearInfo(info);
		if (isInteractiveMode(info))
			_puts("$ ");
		printChar(BUF_FLUSH);
		r = getInput(info);
		if (r != -1)
		{
			setInfo(info, av);
			builtin_ret = findBuiltin(info);
			if (builtin_ret == -1)
				findCommand(info);
		}
		else if (isInteractiveMode(info))
			_putchar('\n');
		freeInfo(info, 0);
	}
	writeHistory(info);
	freeInfo(info, 1);
	if (!isInteractiveMode(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	} return (builtin_ret);
}

