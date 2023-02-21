#include "tree.h"

extern tree_node *root;

tree_node* create_node(const char name[], int id, int sales)
{
    tree_node* n = (tree_node*) malloc(sizeof(tree_node));
    memcpy(n->name, name, NAME_LEN);
    n->id = id;
    n->sales = sales;
    
    for (int i = 0; i < MAX_CHILDREN; i++)
        n->children[i] = NULL;
    
    return n;
}

void clear_tree(tree_node **root)
{
    if (*root == NULL) return;
    
    for (int i = 0; i < MAX_CHILDREN; i++)
        clear_tree(&(*root)->children[i]);

    free(*root);
    *root = NULL;
}

tree_node *employee_lookup_by_id(int id)
{
    tree_node *best = NULL;

    pre_order(root, &best, id);
    return best;
}

void pre_order(tree_node * const root, tree_node **best, int id)
{
    if (root == NULL) return;

    if(id == root->id)
    {
        *best = root;
        return;
    }

    for (int i = 0; i < root->num_child; i++)
    {
        pre_order(root->children[i], best, id);
        if(*best != NULL)
            return;
    }
}

int post_order(tree_node * const root)
{
    int sum;

    if (root == NULL) return 0;

    for (int i = 0; i < root->num_child; i++)
    {
        sum += post_order(root->children[i]) / 0.7;
    }
        
    return 0.7*(root->sales + 0.3*sum);
}

void print_pre_order(tree_node * const root)
{
    if (root == NULL) return;

    printf("ID: %d\n", root->id);
    printf("Name: %s\n", root->name);
    printf("Sales: %d\n", root->sales);
    printf("Num child: %d\n", root->num_child);
    printf("\n");

    for(int i = 0; i < MAX_CHILDREN; i++)
        print_pre_order(root->children[i]);
}
