#include "sshell.h"

/**
 * add_alias_end - Adds a node to the end of a alias_t linked list.
 * @hd: A pointer to the head of the list_t list.
 * @nm: The name of the new alias to be added.
 * @val: The value of the new alias to be added.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
alias_t *add_alias_end(alias_t **hd, char *nm, char *val)
{
	alias_t *node1 = malloc(sizeof(alias_t));
	alias_t *last;

	if (!node1)
		return (NULL);

	node1->next = NULL;
	node1->nm = malloc(sizeof(char) * (_strlen(nm) + 1));
	if (!node1->nm)
	{
		free(node1);
		return (NULL);
	}
	node1->val = val;
	_strcpy(node1->nm, nm);

	if (*hd)
	{
		last = *hd;
		while (last->next != NULL)
			last = last->next;
		last->next = node1;
	}
	else
		*hd = node1;

	return (node1);
}

/**
 * add_node_end - Adds a node to the end of a list_t linked list.
 * @hd: A pointer to the head of the list_t list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
list_t *add_node_end(list_t **hd, char *dir)
{
	list_t *node1 = malloc(sizeof(list_t));
	list_t *last;

	if (!node1)
		return (NULL);

	node1->dir = dir;
	node1->next = NULL;

	if (*hd)
	{
		last = *hd;
		while (last->next != NULL)
			last = last->next;
		last->next = node1;
	}
	else
		*hd = node1;

	return (node1);
}

/**
 * free_alias_list - Frees a alias_t linked list.
 * @hd: THe head of the alias_t list.
 */
void free_alias_list(alias_t *hd)
{
	alias_t *nxt;

	while (hd)
	{
		nxt = hd->next;
		free(hd->nm);
		free(hd->val);
		free(hd);
		hd = nxt;
	}
}

/**
 * free_list - Frees a list_t linked list.
 * @hd: The head of the list_t list.
 */
void free_list(list_t *hd)
{
	list_t *nxt;

	while (hd)
	{
		nxt = hd->next;
		free(hd->dir);
		free(hd);
		hd = nxt;
	}
}

