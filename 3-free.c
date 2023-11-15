#include "shell.h"

/**
 * freeStringArray - Frees a string array.
 *
 * @pp: Pointer to the string array.
 */

void freeStringArray(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * freePointer - Frees a pointer.
 *
 * @ptr: Pointer to be freed.
 *
 * Return: Depends on the condition.
 */

int freePointer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * freeLinkedList - Frees a linked list.
 *
 * @head_ptr: Pointer to the head of the linked list.
 */

void freeLinkedList(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

/**
 * freeInfo - Frees the information.
 *
 * @info: Pointer to the information.
 * @all: Depends on the condition.
 */

void freeInfo(info_t *info, int all)
{
	freeStringArray(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeLinkedList(&(info->env));
		if (info->history)
			freeLinkedList(&(info->history));
		if (info->alias)
			freeLinkedList(&(info->alias));
		freeStringArray(info->environ);
			info->environ = NULL;
		freePointer((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * reallocateMemory - Reallocates a block of memory.
 *
 * @ptr: Pointer to the previous allocated block.
 * @old_size: Size in bytes of the previous block.
 * @new_size: Size in bytes of the new block.
 *
 * Return: Pointer to the old block.
 */

void *reallocateMemory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

