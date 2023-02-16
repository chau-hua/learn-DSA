#ifndef linked_list_h
#define linked_list_h

typedef struct str_node * link;
struct str_node
{
    int data;
    link next;
    link prev;
};

typedef struct str_node node;

node* create_node(const int data);
int is_empty(node* const head);
void add_head(node **head, const int data);
void remove_head(node **head);
void print_list(node* const head);
void clear_list(node **head);
void insertion_sort(node *head);
void swap_node(node **p, node **q);

void print_array(int a[], int n);
void find_max_array_recursive(int array[], int num, int i, int *max);
void sum_array_recursive(int array[], int num, int i, int *sum);

void find_max_ll_recursive(node *node, int *max);
void sum_ll_recursive(node *node, int *sum);
#endif /* linked_list_h */