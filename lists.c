#include "shell.h"

/**
 * add_node_at_beginning - Adds a node at the beginning of the list
 * @head: Address of pointer to the head node
 * @str: String field of the node
 * @num: Node index used by history
 *
 * Return: Pointer to the new head node
 */
list_t *add_node_at_beginning(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return NULL;

	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return NULL;

	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;

	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return NULL;
		}
	}

	new_head->next = *head;
	*head = new_head;

	return new_head;
}

/**
 * add_node_at_end - Adds a node at the end of the list
 * @head: Address of pointer to the head node
 * @str: String field of the node
 * @num: Node index used by history
 *
 * Return: Pointer to the new node
 */
list_t *add_node_at_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *current_node;

	if (!head)
		return NULL;

	current_node = *head;
	new_node = malloc(sizeof(list_t));

	if (!new_node)
		return NULL;

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return NULL;
		}
	}

	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;

		current_node->next = new_node;
	}
	else
		*head = new_node;

	return new_node;
}

/**
 * print_list_strings - Prints only the str element of a list_t linked list
 * @head: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t print_list_strings(const list_t *head)
{
	size_t size = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		size++;
	}

	return size;
}

/**
 * delete_node_at_index - Deletes a node at a given index
 * @head: Address of pointer to the first node
 * @index: Index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return 0;

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return 1;
	}

	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return 1;
		}
		i++;
		prev_node = node;
		node = node->next;
	}

	return 0;
}

/**
 * free_list - Frees all nodes of a list
 * @head_ptr: Address of pointer to the head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
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

