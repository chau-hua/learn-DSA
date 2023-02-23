#include <stdio.h>
#include "avl.h"

int main(int argc, const char * argv[])
{
    int a[] = {5, 3, 6, 4, 1, 7, 9, 8, 10, 12, -10, -5, -3, 2, 11};
    //int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    node* root = NULL;
    for (int i = 0; i < 15; i++)
    {
        root = insert_node(root, a[i]);
    }
    printf("Balance factor: %d\n", balance_factor(root));
    in_order(root);
    
    printf("\n");
    
    root = delete_node(root, 2);
    root = delete_node(root, 4);
    root = delete_node(root, 3);
    
    in_order(root);
    printf("\n");
    root = delete_node(root, -10);
    in_order(root);
    printf("\n");
    
    root = delete_node(root, 6);
    root = delete_node(root, 8);
    root = delete_node(root, 7);
    
    in_order(root);
    printf("\n");
    
    root = delete_node(root, 12);
    in_order(root);
    
    
    printf("\nClear tree\n");
    
    
    clear_avl(&root);
    return 0;
}