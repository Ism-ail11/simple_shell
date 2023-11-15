#include "shell.h"

/**
 * _putchar - Writes the character 'c' to stdout.
 *
 * @c: The character to be printed.
 *
 * Return: On success, returns 1.
*/

int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _puts - Prints a string.
 *
 * @str: Input string to be printed.
 */

void _puts(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}
}

/**
 * _isalpha - Checks if a character is an alphabetic character.
 *
 * @c: Character to be checked.
 *
 * Return: 1 if the character is an alphabetic character,
 * 0 otherwise.
 */

int _isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (1);
	}
	else if (c >= 'A' &&  c <= 'Z')
	{
		return (1);
	}
	else
		return (0);
}

/**
 * _strncpy - Copies a specified number of characters
 * from the source string to the destination string.
 *
 * @dest: Destination string.
 * @src: Source string.
 * @n: Number of characters to be copied.
 *
 * Return: The destination string.
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

/**
 * _strncat - Appends a specified number of elements
 * from the source string to the destination string.
 *
 * @dest: Destination string.
 * @src: Source string.
 * @n: Number of elements to be appended.
 *
 * Return: The destination string.
 */

char *_strncat(char *dest, char *src, int n)
{
	int i;
	int j;

	i = _strlen(dest);
	for (j = 0; dest[j] != '\0' && j < n; j++)
	{
		dest[i] = src[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

