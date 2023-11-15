#include "shell.h"

/**
 * listToStrings - Converts a linked list of strings into an array of strings.
 *
 * @head: Pointer to the first node of the linked list.
 *
 * Return: Array of strings.
 */

char **listToStrings(list_t *head)
{
	list_t *node = head;
	size_t i = listLen(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * printList - Prints all elements of a linked list of strings.
 *
 * @h: Pointer to the first node of the linked list.
 *
 * Return: Size of the linked list.
 */

size_t printList(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convertNumber(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * nodeStartsWith - Returns the node whose string starts
 * with a given prefix and next character.
 *
 * @node: Pointer to the head node of the linked list.
 * @prefix: String to match as a prefix.
 * @c: The next character after the prefix to match.
 *
 * Return: Pointer to the matching node or NULL if not found.
 */

list_t *nodeStartsWith(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = startsWith(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getNodeIndex - Gets the index of a node in a linked list.
 *
 * @head: Pointer to the head node of the linked list.
 * @node: Pointer to the node.
 *
 * Return: Index of the node or -1 if not found.
 */

ssize_t getNodeIndex(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * duplicateChars - Duplicates a range of characters from a string.
 *
 * @pathstr: The source string.
 * @start: Starting index of the range.
 * @stop: Stopping index of the range.
 *
 * Return: Pointer to a new buffer containing the duplicated characters.
 */

char *duplicateChars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}
