#include "shell.h"

/**
 * _strchr - Locates a character in a string.
 *
 * @s: String to search in.
 * @c: Character to locate.
 *
 * Return: Depends on the condition.
 */

char *_strchr(char *s, char c)
{
	int i;

	for (i = 0; s[i] >= '\0'; i++)
	{
		if (s[i] == c)
			return (s + i);
	}
	return ('\0');
}

/**
 * _strcpy - Copies a string from source to destination.
 *
 * @dest: Destination string.
 * @src: Source string.
 *
 * Return: The destination string.
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strlen - Computes the length of a string.
 *
 * @s: Input string.
 *
 * Return: The length of the string.
 */

int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		continue;
	}
	return (i);
}

/**
 * _strcat - Appends the source string to the destination string.
 *
 * @dest: Destination string.
 * @src: Source string.
 *
 * Return: The destination string.
 */

char *_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = _strlen(dest);
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - Compares two strings.
 *
 * @s1: First string to compare.
 * @s2: Second string to compare.
 *
 * Return: 0 if the strings are equal,
 * a positive or negative value if they are different.
 */

int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

