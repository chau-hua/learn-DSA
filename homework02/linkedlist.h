#include "lib.h"

typedef int (*list_del_cb_t) (void *val);
typedef int (*list_cmp_cb_t) (void *val1, void *val2);

typedef struct listnode 
{
  struct listnode *next;
  struct listnode *prev;
  void *data;
}node_t;

typedef struct list
{
	unsigned int count;
	node_t *head;
	node_t *tail;
	list_cmp_cb_t cmp;
	list_del_cb_t del;
}list_t;

list_t *list_create(list_cmp_cb_t cmp, list_del_cb_t del);
void list_free(list_t *list);
node_t *listnode_new();
void listnode_free(node_t *node);
node_t *listnode_add(list_t *list, void *val);
void listnode_delete(list_t *list, void *val);
