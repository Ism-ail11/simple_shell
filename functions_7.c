#include "shell.h"

/**
 * addNode - Adds a node to the start of a linked list.
 *
 * @head: Address of the pointer to the head node.
 * @str: The string to be stored in the node.
 * @num: The index value associated with the node.
 *
 * Return: Pointer to the new head node.
 */

list_t *addNode(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strDuplicate(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * endNode - Adds a node to the end of a linked list.
 *
 * @head: Address of the pointer to the head node.
 * @str: The string to be stored in the node.
 * @num: The index value associated with the node.
 *
 * Return: Pointer to the new node.
 */

list_t *endNode(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strDuplicate(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * printListStr - Prints only the "str" field of each node in a linked list.
 *
 * @h: Pointer to the first node.
 *
 * Return: Size of the linked list.
 */

size_t printListStr(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * deleteNode - Deletes a node at the specified index in a linked list.
 *
 * @head: Address of the pointer to the first node.
 * @index: Index of the node to be deleted.
 *
 * Return: 1 on success, 0 on failure.
 */

int deleteNode(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * listLen - Calculates the length of a linked list.
 *
 * @h: Pointer to the first node.
 *
 * Return: Size of the linked list.
 */

size_t listLen(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}
