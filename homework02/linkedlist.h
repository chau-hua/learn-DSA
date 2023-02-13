#include "lib.h"

typedef int (*list_del_cb_t) (void *val);
typedef int (*list_cmp_cb_t) (void *val1, void *val2);

typedef struct listnode 
{
  node_t *next;
  node_t *prev;
  void *data;
}node_t;

typedef struct list
{
	unsigned int count;
	node *head;
	node *tail;
	list_cmp_cb_t cmp;
	list_del_cb_t del;
}list_t;