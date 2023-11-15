#include "shell.h"

/**
 * findPath - Finds the full path of a command in the PATH string.
 *
 * @info: Pointer to the info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Return: Full path of the command if found, or NULL if not found.
 */

char *findPath(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && startsWith(cmd, "./"))
	{
		if (isCommand(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicateChars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (isCommand(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	} return (NULL);
}

/**
 * _memset - Fills a block of memory with a constant byte.
 *
 * @s: Pointer to the memory area.
 * @b: The byte to fill the memory with.
 * @n: The number of bytes to be filled.
 *
 * Return: A pointer to the memory area @s.
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * startsWith - Checks if a string starts with a given substring.
 *
 * @haystack: The string to search.
 * @needle: The substring to find.
 *
 * Return: Address of the next character
 * after the substring in @haystack,
 * or NULL if not found.
 */

char *startsWith(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * isChain - Tests if the current character in the buffer is a chain delimiter.
 *
 * @info: Pointer to the parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in @buf.
 *
 * Return: 1 if the character is a chain delimiter, 0 otherwise.
 */

int isChain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * checkChain - Checks if we should continue chaining based on the last status.
 *
 * @info: Pointer to the parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in @buf.
 * @i: Starting position in @buf.
 * @len: Length of @buf.
 *
 * Return: Void.
 */

void checkChain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}
