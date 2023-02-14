#include "linkedlist.h"

/* Create new list */
list_t *list_create(list_cmp_cb_t cmp, list_del_cb_t del)
{
	list_t *new;

	new = (list_t *)malloc(sizeof(list_t));
	if(new == NULL)
		return NULL;

	new->count = 0;
	new->head = NULL;
	new->tail = NULL;
	new->cmp = cmp;
	new->del = del;

	return new;
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

	new->next = list->head;
	if(list->head)
		list->head->prev = new;
	else
		list->tail = new;
	list->head = new;
	list->count++;

	return new;
}

void listnode_delete(list_t *list, void *val)
{
	node_t *node;
	
	if((!list) || (!node))
		return;
	
	for(node = list->head; node; node = node->next)
	{
		if(node->data == val)
		{
			if(node->prev)
				node->prev->next = node->next;
			else
				list->head = node->next;
			
			if(node->next)
				node->next->prev = node->prev;
			else
				list->tail = node->prev;
			
			list->count--;
			if(list->del)
				list->del(node->data);
		
			listnode_free(node);
			return;
		}
	}
	
	return;
}

