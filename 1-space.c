#include "shell.h"

/**
 * _splitString - Splits a string into words.
 *
 * @str: The input string.
 * @d: The delimiter.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */

char **_splitString(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) || (str[i] != d && !str[i + 1]) ||
		str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
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
 * _strDuplicate - Allocates memory and copies a string.
 *
 * @str: Input string.
 *
 * Return: Depends on the condition.
 */

char *_strDuplicate(const char *str)
{
	int i;
	int len;
	char *new;

	if (str == NULL)
		return (NULL);
	len = _strlen((char *)str);
	new = (char *) malloc(len + 1 * sizeof(char));
	if (new == NULL)
		return (NULL);
	for (i = 0; i < len; i++)
	{
		new[i] = str[i];
	}
	new[i] = '\0';
	return (new);
}


/**
 * convertStringToInt -> Convert string to integer
 *
 * @s: Input
 *
 * Return: Integer Converted
 */

int convertStringToInt(char *s)
{
	int i;
	int sin;
	unsigned int digit;

	i = 0;
	sin = 1;
	digit = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sin *= -1;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			digit = (digit * 10) + (s[i] - '0');
		}
		else if (digit > 0)
			break;
		i++;
	}
	return (digit * sin);
}
