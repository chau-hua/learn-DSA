#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

void insertion_sort_double_ll(void)
{
    // create a list of some integers
    node *head = NULL;
    add_head(&head, 10);
    add_head(&head, 2);
    add_head(&head, 13);
    add_head(&head, 40);
    add_head(&head, 25);

    print_list(head);
    insertion_sort(head);
    print_list(head);
    clear_list(&head);
}

void find_max_sum_array(void)
{
    int array[5] = {10, 2, 13, 40, 25};
    int num = (sizeof(array)) / (sizeof(int));
    printf("num = %d\n", num);
    int max = array[0];
    int sum = 0;

    print_array(array, num);
    find_max_array_recursive(array, num, 1, &max);
    printf("Max array = %d\n", max);

    sum_array_recursive(array, num, 0, &sum);
    printf("Sum array = %d\n", sum);
}

void find_max_sum_ll(void)
{
    // create a list of some integers
    node *head = NULL;
    int max;
    int sum = 0;

    add_head(&head, 10);
    add_head(&head, 2);
    add_head(&head, 13);
    add_head(&head, 40);
    add_head(&head, 25);

    print_list(head);
    max = head->data;
    find_max_ll_recursive(head->next, &max);
    printf("Max linked list = %d\n", max);

    sum_ll_recursive(head, &sum);
    printf("Sum linked list = %d\n", sum);
    clear_list(&head);
}

int main()
{
    int term_prog = 0;
    int menu;

    while(!term_prog)
    {
        printf("1: Insertion sort with double linked list\n");
        printf("2: Find Max and Sum in array\n");
        printf("3: Find Max and Sum in linked list\n");
        printf("4: Terminate program\n");
        printf("Menu : ");
        scanf("%d", &menu);

        switch(menu)
        {
            case 1:
                insertion_sort_double_ll();
                break;

            case 2:
                find_max_sum_array();
                break;

            case 3:
                find_max_sum_ll();
                break;

            case 4:
                term_prog = 1;
                break;

            default:
                break;
        }
        printf("---------------------------------\n");
        printf("\n");
    }

  return 0;
}