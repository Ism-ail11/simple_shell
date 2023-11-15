#include "shell.h"

/**
 * setInfo - Initializes the info_t struct.
 *
 * @info: Struct address.
 * @av: Argument vector.
 */

void setInfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = splitString(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strDuplicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replaceAlias(info);
		replaceVariables(info);
	}
}

/**
 * getHistoryFile - Retrieves the history file.
 *
 * @info: Parameter struct.
 *
 * Return: Allocated string containing the history file.
 */

char *getHistoryFile(info_t *info)
{
	char *buf, *dir;

	dir = getEnvVariable(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * writeHistory - Creates a file or appends to an existing file for history.
 *
 * @info: The parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */

int writeHistory(info_t *info)
{
	ssize_t fd;
	char *filename = getHistoryFile(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		printStringToFD(node->str, fd);
		printCharToFD('\n', fd);
	}
	printCharToFD(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * buildHistoryList - Adds an entry to the history linked list.
 *
 * @info: Structure containing potential arguments.
 * @buf: Buffer.
 * @linecount: The history linecount.
 *
 * Return: Always 0.
 */

int buildHistoryList(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	endNode(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumberHistory - Renumbers the history linked list after changes.
 *
 * @info: Structure containing potential arguments.
 *
 * Return: The new histcount.
 */

int renumberHistory(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
