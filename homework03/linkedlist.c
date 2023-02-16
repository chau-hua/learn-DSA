#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

node* create_node(const int data)
{
    node *n = (node*) malloc(sizeof(node));
    n->data = data;
    n->next = NULL;
    n->prev = NULL;
    return n;
}
int is_empty(node* const head)
{
    return head == NULL;
}

void add_head(node **head, const int data)
{
    node *n = create_node(data);
    if (is_empty(*head)) *head = n;
    else
    {
        n->next = *head;
        (*head)->prev = n;
        *head = n;
    }
    
}
void remove_head(node **head)
{
    if (is_empty(*head)) return;
    else if ((*head)->next == NULL)
    {
        free(*head);
        *head = NULL;
    }
    else
    {
        node *p = *head;
        *head = p->next;
        (*head)->prev = NULL;
        free(p);
    }
}

void print_list(node* const head)
{
    if (is_empty(head)) printf("Empty list!\n");
    else
    {
        node *p = head;
        while (p != NULL)
        {
            printf("[%d]->", p->data);
            p = p->next;
        }
        printf("[]\n");
    }
}

void clear_list(node **head)
{
    if (is_empty(*head)) return;
    while (*head != NULL)
    {
        node *p = *head;
        *head = p->next;
        free(p);
    }
}

void insertion_sort(node *head)
{
    if (is_empty(head)) return;      // 0 items
    if (head->next == NULL) return;  // 1 items

    node *p = head->next;
    while (p != NULL)
    {   
        int temp = p->data;
        node *prev = p->prev;
        while (prev != NULL && prev->data > temp)
        {
            swap_node(&prev, &prev->next);
            prev = prev->prev;
        }

        p = p->next;
    }
    
}

void swap_node(node **p, node **q)
{
    int temp = (*p)->data;
    (*p)->data = (*q)->data;
    (*q)->data = temp;
}

void print_array(int a[], int n)
{
    int i;

    for(i = 0; i < n; i++)
        printf("[%d] ", a[i]);
    printf("\n");
}

void find_max_array_recursive(int array[], int num, int i, int *max)
{
    if(i >= num)
        return;
    if((*max) < array[i])
        *max = array[i];
    find_max_array_recursive(array, num, ++i, max);
}

void sum_array_recursive(int array[], int num, int i, int *sum)
{
    if(i >= num)
        return;
    *sum += array[i];
    sum_array_recursive(array, num, ++i, sum);
}

void find_max_ll_recursive(node *node, int *max)
{
    if(node == NULL)
        return;
    if((*max) < node->data)
        *max = node->data;
    find_max_ll_recursive(node->next, max);
}

void sum_ll_recursive(node *node, int *sum)
{
    if(node == NULL)
        return;
    *sum += node->data;
    sum_ll_recursive(node->next, sum);
}