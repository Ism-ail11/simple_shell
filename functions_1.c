#include "shell.h"

/**
 * splitString - Splits a string into words
 * ignoring repeated delimiters.
 *
 * @str: The input string.
 * @d: The delimiter string.
 *
 * Return: A pointer to an array of strings
 * or NULL on failure.
 */

char **splitString(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!isDelimiter(str[i], d) && (isDelimiter(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (isDelimiter(str[i], d))
			i++;
		k = 0;
		while (!isDelimiter(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * isInteractiveMode - Returns true
 * if the shell is in interactive mode.
 *
 * @info: Pointer to the parameter structure.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */

int isInteractiveMode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isDelimiter - Checks if a character is a delimiter.
 *
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * Return: 1 if true, 0 if false.
 */

int isDelimiter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * myExit - Exits the shell.
 *
 * @info: Structure containing potential arguments.
 * Used to maintain a constant function prototype.
 *
 * Return: Exits with a given exit status.
 * (0) if info.argv[0] != "exit".
 */

int myExit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = errAtoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			printError(info, "Illegal number: ");
			printString(info->argv[1]);
			printChar('\n');
			return (1);
		}
		info->err_num = errAtoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * myHelp - Displays help information.
 *
 * @info: Structure containing potential arguments.
 * Used to maintain a constant function prototype.
 *
 * Return: Always returns 0.
 */

int myHelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
