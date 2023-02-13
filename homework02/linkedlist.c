#include "linkedlist.h"

/* Create new list */
list_t *list_create(list_cmp_cb_t cmp, list_del_cb_t del)
{
	list_t *new;

	new = (list_t *)malloc(sizeof(list_t));
	if(new == NULL)
		return NULL;

	list->count = 0;
	list->head = NULL;
	list->tail = NULL;
	list->cmp = cmp;
	list->del = del;

	return list;
}

/* Free list */
void list_free(list_t *list)
{
	free(list);
}

/* Allocate new listnode */
node_t *listnode_new()
{
	node_t *node;

	node = (node_t *)malloc(sizeof(node_t));
	return node;
}

/* Free listnode */
void listnode_free(node_t *node)
{
	free(node);
}

/* Add new data to the list */
node_t *listnode_add(list_t *list, void *val)
{
	node_t *n;
	node_t *new;

	new = listnode_new();
	if(!new)
		return NULL;

	new->data = val;


	for(n = list->tail; n; n = n->prev)
	{
		if((list->cmp(val, n->data)) >= 0)
		{
			new->prev = n;
			new->next = n->next;

			if(n->next)
				n->next->prev = new;
			else
				list->tail = new;
			n->next = new;
			list->count++;
			return new;
		}
	}

	new->next = NULL;
	new->prev = NULL
	list->head = new;
	list->tail = new;
	list->count++;

	return new;
}