#ifndef tree_h
#define tree_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 10
#define NAME_LEN     24

typedef struct str_tree_node * child;

struct str_tree_node
{
    char name[NAME_LEN];
    int id;
    int sales;
    int num_child;
    child children[MAX_CHILDREN];
};

typedef struct str_tree_node tree_node;

tree_node* create_node(const char name[], int id, int sales);
void clear_tree(tree_node **root);
tree_node *employee_lookup_by_id(int id);
void pre_order(tree_node * const root, tree_node **best, int id);
int post_order(tree_node * const root);
void print_pre_order(tree_node * const root);

#endif /* tree_h */