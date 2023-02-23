#ifndef avl_h
#define avl_h

#include <stdlib.h>
#include <stdio.h>

typedef struct str_node node;
struct str_node
{
    int key;
    node* left;
    node* right;
    int height;
};

node* create_node(const int key);
void clear_avl(node** root);
void in_order(node *root);
int max(const int a, const int b);

int get_height(node* n);        // return height of node n
int left_height(node* n);       // return height of left subtree of node n
int right_height(node* n);      // return height of right subtree of node n

node* l_rotation(node* n);      // left rotation on node n
node* r_rotation(node* n);      // right rotation on node n
node* lr_rotation(node* n);     // left-right rotation on node n
node* rl_rotation(node* n);     // right-left rotation on node n

int balance_factor(node* n);            // return balance factor of node n
node* rebalance_rightsubtree(node* n);  // rebalance right subtree of node n
node* rebalance_leftsubtree(node* n);   // rebalance left subtree of node n

node* find_min(node* root);             // return node with minimum key in tree

node* insert_node(node* root, const int key);
node* delete_node(node* root, const int key);
#endif /* avl_h */