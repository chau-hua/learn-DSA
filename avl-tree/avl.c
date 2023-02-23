#include "avl.h"

node* create_node(const int key)
{
    node* n = (node*) malloc(sizeof(node));
    n->key = key;
    n->left = n->right = NULL;
    n->height = 0;
    return n;
}

void clear_avl(node** root)
{
    if (*root == NULL) return;
    clear_avl(&(*root)->left);
    clear_avl(&(*root)->right);
    free(*root);
    *root = NULL;
}
int get_height(node *n)
{
    if (n == NULL) return 0;
    
    int lh = left_height(n);
    int rh = right_height(n);
    
    return max(lh, rh);
}

int left_height(node *n)
{
    if (n->left == NULL) return 0;
    else return 1 + n->left->height;
}
int right_height(node *n)
{
    if (n->right == NULL) return 0;
    else return 1 + n->right->height;
}

int balance_factor(node* n)
{
    if (n == NULL) return 0;
    
    int lh = left_height(n);
    int rh = right_height(n);
    
    return lh - rh;
}

int max(const int a, const int b)
{
    return a > b ? a : b;
}

node* l_rotation(node* n)
{
    node *m = n->right;
    n->right = m->left;
    m->left = n;
    n->height = get_height(n);
    m->height = get_height(m);
    return m;
}

node* r_rotation(node* n)
{
    node *m = n->left;
    n->left = m->right;
    m->right = n;
    n->height = get_height(n);
    m->height = get_height(m);
    return m;
}

node* lr_rotation(node* n)
{
    // left rotation on left subtree
    n->left = l_rotation(n->left);
    // right rotation on n
    n = r_rotation(n);
    return n;
}
node* rl_rotation(node* n)
{
    // right rotation on right subtree
    n->right = r_rotation(n->right);
    // left rotation on n
    n = l_rotation(n);
    return n;
}
node* rebalance_rightsubtree(node* root)
{
    if (balance_factor(root) < 2) return root;

    if (balance_factor(root->left) >= 0) return r_rotation(root);
    
    else return lr_rotation(root);
}
node* rebalance_leftsubtree(node* root)
{
    if (balance_factor(root) > -2) return root;
    if (balance_factor(root->right) <= 0) return l_rotation(root);
    else return rl_rotation(root);
}

node* insert_node(node* root, const int key)
{
    if (root == NULL) return create_node(key);
    
    if (root->key < key) // insert to right subtree
    {
        // insert node on right subtree
        root->right = insert_node(root->right, key);
        // rebalance on left subtree
        root = rebalance_leftsubtree(root);
    }
    else // insert to left subtree
    {
        // insert node on left subtree
        root->left = insert_node(root->left, key);
        // rebalance on right subtree
        root = rebalance_rightsubtree(root);
    }
    root->height = get_height(root);
    return root;
}

node* delete_node(node* root, const int key)
{
    if (root == NULL) return NULL;
    
    if (root->key < key)
    {
        root->right = delete_node(root->right, key);
        root = rebalance_rightsubtree(root);
    }
    else if (root->key > key)
    {
        root->left = delete_node(root->left, key);
        root = rebalance_leftsubtree(root);
    }
    else // delete node at root
    {
        if (root->right != NULL)
        {
            node* m = find_min(root->right);
            root->key = m->key;
            root->right = delete_node(root->right, root->key);
            root = rebalance_rightsubtree(root);
        }
        else
        {
            node* temp = root->left;
            free(root);
            return temp;
        }
    }
    root->height = get_height(root);
    return root;
}

node* find_min(node* root)
{
    if (root->left == NULL) return root;
    return find_min(root->left);
}

void in_order(node *root)
{
    if (root == NULL) return;
    in_order(root->left);
    printf("%d ", root->key);
    in_order(root->right);
}