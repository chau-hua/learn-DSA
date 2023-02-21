#include <stdio.h>
#include "tree.h"

tree_node *root;

void new_employee_add()
{
    char name[NAME_LEN];
    int parent_id, id, sales;
    tree_node *parent_node, *new_node;

    fflush(stdin);
    printf("Enter id of parent employee: ");
    scanf("%d", &parent_id);
    parent_node = employee_lookup_by_id(parent_id);
    if(parent_node == NULL)
    {
        printf("Cannot find parent employee id %d\n", parent_id);
        return;
    }
    else if (parent_node->num_child >= MAX_CHILDREN)
    {
        printf("Cannot add new employee\n");
        return;
    }

    getchar();
    printf("Enter name of new employee: ");
	scanf("%[^\n]", name);
    printf("Enter id of new employee: ");
	scanf("%d", &id);
    printf("Enter sales of new employee: ");
	scanf("%d", &sales);
    new_node = create_node(name, id, sales);
    parent_node->children[parent_node->num_child] = new_node;
    parent_node->num_child++;
}

void calculate_employee_income()
{
    int id, sum;
    tree_node *node;

    printf("Enter employee ID: ");
    scanf("%d", &id);

    node = employee_lookup_by_id(id);
    if(node == NULL)
    {
        printf("Cannot find employee id %d\n", id);
        return;
    }

    sum = post_order(node);
    printf("Employee ID %d income: %d\n", id, sum);
}

void dump_all_employee()
{
    print_pre_order(root);
}

int main(int argc, const char * argv[])
{
    int menu, ret, term_prog = 0;

    root = create_node("VHT", 0, 0);
	
	while(!term_prog)
	{
        printf("1: Add a new employee information\n");
        printf("2: Calculate employee's income\n");
        printf("3: Dump all employee information\n");
        printf("4: Terminate program\n");
		printf("Enter menu: ");
		scanf("%d", &menu);

		switch(menu)
		{
			case 1: /* Add a new employee information */
                new_employee_add();
				break;

			case 2: /* Calculate employee's income */
                calculate_employee_income();
				break;

			case 3: /* Dump all employee information */
                dump_all_employee();
				break;

			case 4: /* Terminate program */
				term_prog = 1;
				break;

			default:
				printf("Please enter menu from 1->4\n");
				break;
		}
		
		if(term_prog)
			break;
		printf("----------------------------------------------------\n");
		printf("\n");
	}

	return 0;
}
