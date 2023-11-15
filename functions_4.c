#include "shell.h"

/**
 * printError - Prints an error message.
 *
 * @info: Pointer to the parameter & return info struct.
 * @estr: String containing the specified error type.
 */

void printError(info_t *info, char *estr)
{
	printString(info->fname);
	printString(": ");
	printDecimal(info->line_count, STDERR_FILENO);
	printString(": ");
	printString(info->argv[0]);
	printString(": ");
	printString(estr);
}

/**
 * printDecimal - Prints a decimal (integer) number (base 10).
 *
 * @input: The input number.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */

int printDecimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = printChar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convertNumber - Converts a number to a string representation
 * in a given base.
 *
 * @num: The number to convert.
 * @base: The base to convert to.
 * @flags: Argument flags.
 *
 * Return: The converted string.
 */

char *convertNumber(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * removeComments - Replaces the first instance of '#' with '\0'.
 *
 * @buf: The address of the string to modify.
 */

void removeComments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

/**
 * getInput - Gets a line of input without the newline character.
 *
 * @info: Pointer to the parameter struct.
 *
 * Return: The number of bytes read.
 */

ssize_t getInput(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = inputBuf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		checkChain(info, buf, &j, i, len);
		while (j < len)
		{
			if (isChain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

