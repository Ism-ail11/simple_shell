#include "shell.h"

/**
 * printString - Prints an input string.
 *
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */

void printString(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		printChar(str[i]);
		i++;
	}
}

/**
 * printChar - Writes the character 'c' to stderr.
 *
 * @c: The character to print.
 *
 * Return: On success, returns 1.
 * On error, returns -1 and sets errno appropriately.
 */

int printChar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * printCharToFD - Writes the character 'c' to the given file descriptor.
 *
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, returns 1.
 * On error, returns -1 and sets errno appropriately.
 */

int printCharToFD(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * printStringToFD - Prints an input string to the given file descriptor.
 *
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */

int printStringToFD(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += printCharToFD(*str++, fd);
	}
	return (i);
}

/**
 * errAtoi - Converts a string to an integer.
 *
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers in the string,
 * the converted number otherwise,
 * -1 on error.
 */

int errAtoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
